#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int numOfRectangles;

struct RectangleSide
{
    int x;
    int y1;
    int y2;
    bool isLeftSide;
};

vector<RectangleSide> rectangleSides;

constexpr int MAX_HEIGHT = 30'000;

struct Node
{
    int value;
    int lazy;

    Node() : value(0), lazy(0){}
};

Node side[4 * MAX_HEIGHT];
Node length[4 * MAX_HEIGHT];
int maxY;
int result;

void input()
{
    scanf("%d", &numOfRectangles);

    for(int i = 0; i < numOfRectangles; i++)
    {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        rectangleSides.push_back(RectangleSide{x1, y1 + 1, y2, true});
        rectangleSides.push_back(RectangleSide{x2, y1 + 1, y2, false});

        maxY = max(maxY, y2);
    }
}

bool compareTo(RectangleSide a, RectangleSide b)
{
    return a.x < b.x;
}

int calculateMid(int a, int b)
{
    return a + (b - a) / 2;
}

void updateTree(int diff, int node, int nodeIntervalStart, int nodeIntervalEnd, int targetIntervalStart, int targetIntervalEnd)
{
    if(targetIntervalEnd < nodeIntervalStart || nodeIntervalEnd < targetIntervalStart)
    {
        return;
    }

    if(targetIntervalStart <= nodeIntervalStart && nodeIntervalEnd <= targetIntervalEnd)
    {
        side[node].value += diff;

        if(side[node].value > 0)
        {
            length[node].value = nodeIntervalEnd - nodeIntervalStart + 1;
        }
        else
        {
            if(nodeIntervalStart == nodeIntervalEnd)
            {
                length[node].value = 0;
                return;
            }
            length[node].value = length[node * 2].value + length[node * 2 + 1].value;
        }

        return;
    }

    int mid = calculateMid(nodeIntervalStart, nodeIntervalEnd);
    updateTree(diff, node * 2, nodeIntervalStart, mid, targetIntervalStart, targetIntervalEnd);
    updateTree(diff, node * 2 + 1, mid + 1, nodeIntervalEnd, targetIntervalStart, targetIntervalEnd);

    if(side[node].value > 0)
    {
        length[node].value = nodeIntervalEnd - nodeIntervalStart + 1;
        return;
    }

    if(nodeIntervalStart == nodeIntervalEnd)
    {
        length[node].value = 0;
        return;
    }

    length[node].value = length[node * 2].value + length[node * 2 + 1].value;
}

void addSide(int y1, int y2)
{
    updateTree(1, 1, 1, maxY, y1, y2);
}

void subtractSide(int y1, int y2)
{
    updateTree(-1, 1, 1, maxY, y1, y2);
}

void process()
{
    sort(rectangleSides.begin(), rectangleSides.end(), compareTo);

    int prevSumOfSides = 0;
    int prevX = 0;
    int deltaX;

    for(auto iter = rectangleSides.begin(); iter != rectangleSides.end(); iter++)
    {
        deltaX = iter->x - prevX;
        result += prevSumOfSides * deltaX;
        prevX = iter->x;

        if(iter->isLeftSide)
        {
            addSide(iter->y1, iter->y2);
        }
        else
        {
            subtractSide(iter->y1, iter->y2);
        }

        prevSumOfSides = length[1].value;
    }
}

void output()
{
    printf("%d\n", result);
}

int main()
{
    input();
    process();
    output();

    return 0;
}