#include <iostream>

using namespace std;

int t;
int n;
int m;
int k;
bool board[50][50];
bool visited[50][50];
int result;

void visit(int i, int j)
{
    if(i != 0 && board[i-1][j] && !visited[i-1][j])
    {
        visited[i-1][j] = true;
        visit(i-1, j);
    }
    if(i < 49 && board[i+1][j] && !visited[i+1][j])
    {
        visited[i+1][j] = true;
        visit(i+1, j);
    }
    if(j < 49  && board[i][j+1] && !visited[i][j+1])
    {
        visited[i][j+1] = true;
        visit(i, j+1);
    }
    if(j != 0 & board[i][j-1] && !visited[i][j-1])
    {
        visited[i][j-1] = true;
        visit(i, j-1);
    }
    
}

void input()
{
    result = 0;

    for(int i = 0; i < 50; i++)
        for(int j = 0; j < 50; j++)
        {
            board[i][j] = false;
            visited[i][j] = false;
        }

    cin >> n >> m >> k;
    for(int i = 0; i < k; i++)
    {
        int x, y;
        cin >> x >> y;
        board[x][y] = true;
    }
}

void process()
{
    for(int i = 0; i < 50; i++)
        for(int j = 0; j < 50; j++)
        {
            if(board[i][j] && !visited[i][j])
            {
                visit(i, j);
                result++;
            }
        }

}

void output()
{
    cout << result << endl;
}

int main()
{
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        input();
        process();
        output();
    }
}