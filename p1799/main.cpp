#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_BOARD_SIZE = 10;

int boardSize;
bool board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
bool visitedUR[MAX_BOARD_SIZE * 2];
bool visitedUL[MAX_BOARD_SIZE * 2];
int result;

void input()
{
    cin >> boardSize;
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            cin >> board[i][j];
        }
    }
}

int manhattan(int rStart, int cStart, int rEnd, int cEnd)
{
    return abs((rEnd - rStart)) + abs((cEnd - cStart));
}

int dfs(int line, int count)
{
    if(line >= boardSize * 2)
    {
        return count;
    }

    int maxCount = 0;
    visitedUR[line] = true;
    for(int i = 0; i < boardSize - abs(line - boardSize + 1); i++)
    {
        const int r = max(0, line - (boardSize - 1)) + i;
        const int c = min(line, boardSize - 1) - i;
        int UL = manhattan(r, c, 0, boardSize - 1);
        if(!visitedUL[UL] && board[r][c])
        {
            visitedUL[UL] = true;
            maxCount = max(dfs(line + 2, count + 1), maxCount);
            visitedUL[UL] = false;
        }
    }
    visitedUR[line] = false;

    return max(dfs(line + 2, count), maxCount);
    
}

void process()
{
    int white = dfs(0, 0);
    int black = dfs(1, 0);

    result = white + black;
}

void output()
{  
    cout << result << endl;
}

int main()
{
    input();
    process();
    output();

    return 0;
}