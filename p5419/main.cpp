#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_NUM_POINTS = 75000;

int numPoints;

struct Point
{
    int x;
    int y;
};

bool compare1(Point a, Point b)
{
    if(a.y < b.y)
        return true;
    if(a.y > b.y)
        return false;
    return a.x > b.x;
}

bool compare2(Point a, Point b)
{
    if(a.x < b.x)
        return true;
    if(a.x > b.x)
        return false;
    return a.y > b.y;
}

Point points[MAX_NUM_POINTS];
long long segmentTree[MAX_NUM_POINTS * 4];
long long result;

void input()
{
    result = 0;
    for(int i = 0; i < MAX_NUM_POINTS * 4; i++)
    {
        segmentTree[i] = 0;
    }

    scanf("%d", &numPoints);
    for(int i = 0; i < numPoints; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        points[i] = Point{x, y};
    }
}

int calculateMid(int a, int b)
{
    return a + (b - a) / 2;
}

void updateTree(int node, int nodeIntervalStart, int nodeIntervalEnd, int target)
{
    if(target < nodeIntervalStart || nodeIntervalEnd < target)
        return;
    
    segmentTree[node]++;

    if(nodeIntervalStart == nodeIntervalEnd)
        return;

    int mid = calculateMid(nodeIntervalStart, nodeIntervalEnd);
    updateTree(node * 2, nodeIntervalStart, mid, target);
    updateTree(node * 2 + 1, mid + 1, nodeIntervalEnd, target);
}

void increaseNode(int target)
{
    updateTree(1, 1, numPoints, target);
}

long long calculateSum(int node, int nodeIntervalStart, int nodeIntervalEnd, int targetIntervalStart, int targetIntervalEnd)
{
    if(targetIntervalEnd < nodeIntervalStart || nodeIntervalEnd < targetIntervalStart)
        return 0;
    
    if(targetIntervalStart <= nodeIntervalStart && nodeIntervalEnd <= targetIntervalEnd)
    {
        return segmentTree[node];
    }

    int mid = calculateMid(nodeIntervalStart, nodeIntervalEnd);
    long long left = calculateSum(node * 2, nodeIntervalStart, mid, targetIntervalStart, targetIntervalEnd);
    long long right = calculateSum(node * 2 + 1, mid + 1, nodeIntervalEnd, targetIntervalStart, targetIntervalEnd);
    return left + right;
}

long long calculateSum(int targetIntervalStart, int targetIntervalEnd)
{
    return calculateSum(1, 1, numPoints, targetIntervalStart, targetIntervalEnd);
}

void process()
{
    sort(points, points + numPoints, compare1);
    for(int i = 0; i < numPoints; i++)
    {
        points[i].y = i + 1;
    }
    sort(points, points + numPoints, compare2);

    for(int i = 0; i < numPoints; i++)
    {
        result += calculateSum(points[i].y, numPoints);
        increaseNode(points[i].y);
    }
}

void output()
{  
    printf("%lld\n", result);
}

int main()
{
    int numTestCases;

    cin >> numTestCases;
    for (int i = 0; i < numTestCases; i++)
    {
        input();
        process();
        output();
    }
    return 0;
}