#include<vector>
#include<iostream>
#include<queue>

using namespace std;

void dfs(int s,vector<vector<int>>&adj,vector<int>&visit){
    cout<<s<<" ";
    visit[s]=1;
    for(int i=0;i<adj[s].size();i++){
        int ele = adj[s][i];
        if(!visit[ele]){
            dfs(ele,adj,visit);
        }
    }
}
void bfs(int s,vector<vector<int>>&adj,vector<int>&visit){
    queue<int>q;
    visit[s]=1;
    q.push(s);

    while(!q.empty()){
        int top=q.front();
        q.pop();

        cout<<top<<" ";

        for(int i=0;i<adj[top].size();i++){
            int ele = adj[top][i];
            if(!visit[ele]){
                visit[ele]=1;
                q.push(ele);
            }
        }
    }

}
int main(){
    int n;
    cout<<"enter number of nodes:";
    cin>>n;
    vector<vector<int>>adj(n);

    for(int i=0;i<n;i++){
        cout<<"enter the vertices of "<<i<<"th edge";
        int m,k;
        cin>>m;
        cin>>k;

        adj[m].push_back(k);
        adj[k].push_back(m);
    }

    int p;
    cout<<"enter what to do:"<<endl;
    cout<<"1.bfs";
    cout<<"2.dfs";
    cin>>p;
    vector<int>visit(n);
    if(p==1)
    bfs(0,adj,visit);
    if(p==2)
    dfs(0,adj,visit);
}