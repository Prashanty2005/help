#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>> &board, int row, int col, int n)
{
  // Check column
  for (int i = 0; i < row; i++)
    if (board[i][col] == 1)
      return false;

  // Check left diagonal
  for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
    if (board[i][j] == 1)
      return false;

  // Check right diagonal
  for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
    if (board[i][j] == 1)
      return false;

  return true;
}

void printBoard(vector<vector<int>> &board, int n)
{
  cout << "\nSolution:\n";
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (board[i][j] == 1)
        cout << "Q ";
      else
        cout << ". ";
    }
    cout << endl;
  }
}

void solve(int row, vector<vector<int>> &board, int n, int &count)
{
  if (row == n)
  {
    count++;
    printBoard(board, n);
    return;
  }

  for (int col = 0; col < n; col++)
  {
    if (isSafe(board, row, col, n))
    {
      board[row][col] = 1;

      solve(row + 1, board, n, count);

      // Backtrack
      board[row][col] = 0;
    }
  }
}

int main()
{
  int n;
  cout << "Enter value of N: ";
  cin >> n;

  vector<vector<int>> board(n, vector<int>(n, 0));
  int count = 0;

  solve(0, board, n, count);

  cout << "\nTotal solutions: " << count << endl;

  return 0;
}