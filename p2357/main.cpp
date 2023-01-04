#include <iostream>

using namespace std;

constexpr int MAX_NUM_DATA = 100'000;

int numOfData;
int numOfQueries;

int numbers[MAX_NUM_DATA + 1 ];
int minimum[MAX_NUM_DATA * 4];
int maximum[MAX_NUM_DATA * 4];

int calculateMid(int a, int b)
{
    return a + (b - a) / 2;
}

void initSegTree(int node, int nodeIntervalStart, int nodeIntervalEnd)
{
    if(nodeIntervalStart == nodeIntervalEnd)
    {
        maximum[node] = numbers[nodeIntervalStart];
        minimum[node] = numbers[nodeIntervalStart];
        return;
    }

    int mid = calculateMid(nodeIntervalStart, nodeIntervalEnd);
    initSegTree(node * 2, nodeIntervalStart, mid);
    initSegTree(node * 2 + 1, mid + 1, nodeIntervalEnd);

    maximum[node] = max(maximum[node * 2], maximum[node * 2 + 1]);
    minimum[node] = min(minimum[node * 2], minimum[node * 2 + 1]);
}

int calculateMax(int node, int nodeIntervalStart, int nodeIntervalEnd, int targetIntervalStart, int targetIntervalEnd)
{
    if(targetIntervalEnd < nodeIntervalStart || nodeIntervalEnd < targetIntervalStart)
    {
        return -1;
    }

    if(targetIntervalStart <= nodeIntervalStart && nodeIntervalEnd <= targetIntervalEnd)
    {
        return maximum[node];
    }

    int mid = calculateMid(nodeIntervalStart, nodeIntervalEnd);

    return max(calculateMax(node * 2, nodeIntervalStart, mid, targetIntervalStart, targetIntervalEnd),
        calculateMax(node * 2 + 1, mid + 1, nodeIntervalEnd, targetIntervalStart, targetIntervalEnd));
}

int calculateMax(int start, int end)
{
    return calculateMax(1, 1, numOfData, start, end);
}

int calculateMin(int node, int nodeIntervalStart, int nodeIntervalEnd, int targetIntervalStart, int targetIntervalEnd)
{
    if(targetIntervalEnd < nodeIntervalStart || nodeIntervalEnd < targetIntervalStart)
    {
        return 1'000'000'001;
    }

    if(targetIntervalStart <= nodeIntervalStart && nodeIntervalEnd <= targetIntervalEnd)
    {
        return minimum[node];
    }

    int mid = calculateMid(nodeIntervalStart, nodeIntervalEnd);

    return min(calculateMin(node * 2, nodeIntervalStart, mid, targetIntervalStart, targetIntervalEnd),
        calculateMin(node * 2 + 1, mid + 1, nodeIntervalEnd, targetIntervalStart, targetIntervalEnd));
}

int calculateMin(int start, int end)
{
    return calculateMin(1, 1, numOfData, start, end);
}

void initSegTree()
{
    initSegTree(1, 1, numOfData);
}

void process()
{
    scanf("%d %d", &numOfData, &numOfQueries);
    for(int i = 1; i <= numOfData; i++)
    {
        scanf("%d", &numbers[i]);   
    }

    initSegTree();
    
    for(int i = 0; i < numOfQueries; i++)
    {
        int start, end;
        scanf("%d %d", &start, &end);

        printf("%d %d\n", calculateMin(start, end), calculateMax(start, end));

    }
}

int main()
{
    process();

    return 0;
}