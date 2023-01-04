#include <iostream>
#include <queue>

using namespace std;

constexpr int MAX_SIZE = 50;

int width;
int height;

char board[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int dynamic[MAX_SIZE][MAX_SIZE];
int result;
bool canMoveForever;

void input()
{
    cin >> height >> width;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            cin >> board[i][j];
        }
    }
}

bool isOver(int x, int y)
{
    return x < 0 || x >= width || y < 0 || y >= height;
}

bool isHole(char c)
{
    return c == 'H';
}

inline int charToNum(char c)
{
    return c - '0';
}

int dfs(int x, int y)
{
    if(canMoveForever)
        return 1;

    if(isOver(x, y))
        return 1;

    if(isHole(board[y][x]))
        return 1;
    
    if(visited[y][x])
    {
        canMoveForever = true;
        return 1;
    }

    if(dynamic[y][x] != 0)
    {
        return dynamic[y][x];
    }
    
    visited[y][x] = true;
    
    int tileNum = charToNum(board[y][x]);
    int lengths[4];

    lengths[0] = dfs(x, y - tileNum);
    lengths[1] = dfs(x, y + tileNum);
    lengths[2] = dfs(x - tileNum, y);
    lengths[3] = dfs(x + tileNum, y);

    int maxLength = 0;

    for(int i = 0; i < 4; i++)
    {
        if(lengths[i] > maxLength)
        {
            maxLength = lengths[i];
        }
    }

    visited[y][x] = false;
    dynamic[y][x] = maxLength + 1;
    return maxLength + 1;    
}

void process()
{
    result = dfs(0, 0) - 1;
}

void output()
{
    if(canMoveForever)
        cout << -1 << endl;
    else
        cout << result << endl;
}

int main()
{
    input();
    process();
    output();

    return 0;
}