#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>>&board,int row,int col,int n){
    for(int i=0;i<n;i++){
        if(board[i][col]==1)
        return 0;
    }

    for(int i=row-1,j=col-1;i>=0 && j>=0;i--,j--){
        if(board[i][j]==1)
        return 0;
    }

    for(int i=row-1,j=col+1;i>=0&&j<n;i--,j++){
        if(board[i][j]==1)
        return 0;
    }

    return 1;
}

void printBoard(int count,vector<vector<int>>&board,int n){
    cout<<count<<"st solution:"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j]==1)
            cout<<"Q";
            
            else
            cout<<".";
        }
        cout<<endl;
    }
    cout<<endl;
}
void find_ans(int row,vector<vector<int>>&board,int n,int &count){
    if(row==n){
        count++;
        printBoard(count,board,n);
        return;
    }

    for(int j=0;j<n;j++){

        if(isSafe(board,row,j,n)){

            board[row][j]=1;
            find_ans(row+1,board,n,count);
            board[row][j]=0;
        }
    }
}

int main(){
    int n;
    cout<<"enter the length of maze:";
    cin>>n;

    vector<vector<int>>maze(n,vector<int>(n,0));
    int count=0;
    find_ans(0,maze,n,count);
    cout<<endl;
    cout<<"total solutions:"<<count;
}