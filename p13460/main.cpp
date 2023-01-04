#include <iostream>
#include <utility>
#include <queue>

using namespace std;

constexpr char EMPTY = '.';
constexpr char WALL = '#';
constexpr char HOLE = 'O';
constexpr char RED = 'R';
constexpr char BLUE = 'B';

constexpr int MAX_SIZE = 15;

int n, m;
char board[MAX_SIZE][MAX_SIZE];
int result = -1;

class MarbleState
{
public:
    MarbleState() = delete;
    MarbleState(int redX, int redY, int blueX, int blueY, int count) : redX(redX), redY(redY), blueX(blueX), blueY(blueY), count(count) {}

    MarbleState nextState(int deltaX, int deltaY)
    {
        int originRedX = redX;
        int originRedY = redY;
        int originBlueX = blueX;
        int originBlueY = blueY;

        if (shouldSimulateRedFirst(deltaX, deltaY))
        {
            if (isThereRed())
                moveRed(deltaX, deltaY);
            if (isThereBlue())
                moveBlue(deltaX, deltaY);
        }
        else
        {
            if (isThereBlue())
                moveBlue(deltaX, deltaY);
            if (isThereRed())
                moveRed(deltaX, deltaY);
        }

        MarbleState result = MarbleState(redX, redY, blueX, blueY, count + 1);
        redX = originRedX;
        redY = originRedY;
        blueX = originBlueX;
        blueY = originBlueY;
        return result;
    }

    bool isFinished()
    {
        return !(isThereBlue() && isThereRed());
    }

    bool isThereBlue()
    {
        return !(blueX == -1 && blueY == -1);
    }

    bool isThereRed()
    {
        return !(redX == -1 && redY == -1);
    }

    bool isOver()
    {
        return count > 10;
    }

    bool equalsIgnoreCount(MarbleState target)
    {
        return redX == target.redX && redY == target.redY && blueX == target.blueX && blueY == target.blueY;
    }

    int getCount()
    {
        return count;
    }

private:
    void moveRed(int deltaX, int deltaY)
    {
        pair<int, int> pointRed = simulateNextPosition(redX, redY, deltaX, deltaY);
        redX = pointRed.first;
        redY = pointRed.second;
    }

    void moveBlue(int deltaX, int deltaY)
    {
        pair<int, int> pointBlue = simulateNextPosition(blueX, blueY, deltaX, deltaY);
        blueX = pointBlue.first;
        blueY = pointBlue.second;
    }

    pair<int, int> simulateNextPosition(int pointX, int pointY, int deltaX, int deltaY)
    {
        while (true)
        {
            int nextX = pointX + deltaX;
            int nextY = pointY + deltaY;
            char nextObject = board[nextX][nextY];

            if (nextObject == HOLE)
            {
                return make_pair(-1, -1);
            }
            if (isThereMarble(nextX, nextY))
            {
                return make_pair(pointX, pointY);
            }
            if (nextObject != EMPTY)
            {
                return make_pair(pointX, pointY);
            }

            pointX = nextX;
            pointY = nextY;
        }
    }

    bool isThereMarble(int x, int y)
    {
        if (redX == x && redY == y)
            return true;
        if (blueX == x && blueY == y)
            return true;
        return false;
    }

    bool shouldSimulateRedFirst(int deltaX, int deltaY)
    {
        if (deltaX > 0)
        {
            return redX > blueX;
        }
        if (deltaX < 0)
        {
            return redX < blueX;
        }
        if (deltaY > 0)
        {
            return redY > blueY;
        }
        if (deltaY < 0)
        {
            return redY < blueY;
        }
        return true;
    }

private:
    int redX;
    int redY;
    int blueX;
    int blueY;
    int count;
};

void input()
{
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        cin >> board[i];
    }
}

MarbleState getStartStateAndRemoveMarbles()
{
    int redX, redY, blueX, blueY;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j] == RED)
            {
                redX = i;
                redY = j;
                board[i][j] = EMPTY;
            }
            if (board[i][j] == BLUE)
            {
                blueX = i;
                blueY = j;
                board[i][j] = EMPTY;
            }
        }
    }

    return MarbleState(redX, redY, blueX, blueY, 0);
}

int bfs(queue<MarbleState> states)
{
    int deltaX[4] = {-1, 1, 0, 0};
    int deltaY[4] = {0, 0, -1, 1};

    while (!states.empty())
    {
        MarbleState popped = states.front();
        states.pop();

        for (int i = 0; i < 4; i++)
        {
            MarbleState next = popped.nextState(deltaX[i], deltaY[i]);

            if (popped.equalsIgnoreCount(next))
                continue;

            if (next.isOver())
                continue;

            if (next.isFinished())
            {
                if (next.isThereBlue())
                {
                    result = next.getCount();
                    return;
                }
                continue;
            }

            states.push(next);
        }
    }
}

void process()
{
    MarbleState startState = getStartStateAndRemoveMarbles();

    queue<MarbleState> states;
    states.push(startState);

    result = bfs(states);
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

    cin >> n;
    return 0;
}