#include <iostream>

using namespace std;

constexpr int MAX_NUM_ELEMENTS = 100'000;

int numOfElements;
int numOfQueries;
int numbers[MAX_NUM_ELEMENTS + 1];

int segmentTree[MAX_NUM_ELEMENTS * 4];

void numberInput()
{
    scanf("%d", &numOfElements);
    for(int i = 0; i < numOfElements; i++)
    {
        scanf("%d", &numbers[i + 1]);
    }
}

int calculateMid(int a, int b)
{
    return a + (b - a) / 2;
}

int makeSegmentTree(int node, int nodeIntervalStart, int nodeIntervalEnd)
{
    if(nodeIntervalStart == nodeIntervalEnd)
    {
        segmentTree[node] = nodeIntervalStart;
        return segmentTree[node];
    }

    int mid = calculateMid(nodeIntervalStart, nodeIntervalEnd);

    int left = makeSegmentTree(node * 2, nodeIntervalStart, mid);
    int right = makeSegmentTree(node * 2 + 1, mid + 1, nodeIntervalEnd);

    if(numbers[left] <= numbers[right])
    {
        segmentTree[node] = left;
        return segmentTree[node];
    }

    segmentTree[node] = right;
    return segmentTree[node];
}

void makeSegmentTree()
{
    makeSegmentTree(1, 1, numOfElements);
}

int findMin(int node, int nodeIntervalStart, int nodeIntervalEnd, int targetIntervalStart, int targetIntervalEnd)
{
    if(targetIntervalEnd < nodeIntervalStart || nodeIntervalEnd < targetIntervalStart)
    {
        return -1;
    }

    if(targetIntervalStart <= nodeIntervalStart && nodeIntervalEnd <= targetIntervalEnd)
    {
        return segmentTree[node];
    }

    int mid = calculateMid(nodeIntervalStart, nodeIntervalEnd);
    int left = findMin(node * 2, nodeIntervalStart, mid, targetIntervalStart, targetIntervalEnd);
    int right = findMin(node * 2 + 1, mid + 1, nodeIntervalEnd, targetIntervalStart, targetIntervalEnd);

    if(left == -1)
        return right;
    
    if(right == -1)
        return left;

    if(numbers[left] <= numbers[right])
        return left;
    
    return right;
}

int findMin(int a, int b)
{
    return findMin(1, 1, numOfElements, a, b);
}

int updateTree(int node, int nodeIntervalStart, int nodeIntervalEnd, int targetIndex, int number)
{
    if(targetIndex < nodeIntervalStart || nodeIntervalEnd < targetIndex)
    {
        return segmentTree[node];
    }

    if(nodeIntervalStart == nodeIntervalEnd)
    {
        numbers[targetIndex] = number;
        return segmentTree[node];
    }

    int mid = calculateMid(nodeIntervalStart, nodeIntervalEnd);
    int left = updateTree(node * 2, nodeIntervalStart, mid, targetIndex, number);
    int right = updateTree(node * 2 + 1 , mid + 1, nodeIntervalEnd, targetIndex, number);
    
    if(numbers[left] <= numbers[right])
    {
        segmentTree[node] = left;
        return segmentTree[node];
    }

    segmentTree[node] = right;
    return segmentTree[node];
}

void updateTree(int index, int number)
{
    updateTree(1, 1, numOfElements, index, number);
}

bool isQuery(int a)
{
    return a == 2;
}

int main()
{
    numberInput();
    makeSegmentTree();

    scanf("%d", &numOfQueries);
    for(int i = 0; i < numOfQueries; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        if(isQuery(a))
        {
            printf("%d\n", findMin(b, c));
            continue;
        }

        updateTree(b, c);

    }

    return 0;
}