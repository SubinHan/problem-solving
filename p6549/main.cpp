#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_NUM_RECTANGLES = 100'000;

int numOfRectangles;

class MyRectangle
{
public:
    int x;
    int height;

    MyRectangle(int x = -1, int height = -1) : x(x), height(height) {}
};

class Node
{
public:
    int left;
    int middle;
    int right;

    Node(int left = 0, int middle = 0, int right = 0) : left(left), middle(middle), right(right) {}
};

MyRectangle rectangles[MAX_NUM_RECTANGLES];

Node segmentTree[MAX_NUM_RECTANGLES * 4];
long long maxResult;

void initTree()
{
    for(int i = 0; i < MAX_NUM_RECTANGLES * 4; i++)
    {
        segmentTree[i] = Node();
    }
}

int calculateMid(int a, int b)
{
    return a + (b - a) / 2;
}

Node addRectangle(int node, int nodeIntervalStart, int nodeIntervalEnd, int target)
{
    if(target < nodeIntervalStart || nodeIntervalEnd < target)
    {
        return segmentTree[node];
    }

    if(nodeIntervalStart == nodeIntervalEnd)
    {
        segmentTree[node].left = 1;
        segmentTree[node].middle = 1;
        segmentTree[node].right = 1;
        return segmentTree[node];
    }

    int mid = calculateMid(nodeIntervalStart, nodeIntervalEnd);

    Node left = addRectangle(node * 2, nodeIntervalStart, mid, target);
    Node right = addRectangle(node * 2 + 1, mid + 1, nodeIntervalEnd, target);

    segmentTree[node].left = left.left;
    if(left.left == mid - nodeIntervalStart + 1)
    {
        segmentTree[node].left += right.left;
    }

    segmentTree[node].right = right.right;
    if(right.right == nodeIntervalEnd - mid)
    {
        segmentTree[node].right += left.right;
    }

    segmentTree[node].middle = max(max(left.middle, right.middle), left.right + right.left);

    return segmentTree[node];
}

int calculateMax()
{
    return max(max(segmentTree[1].left, segmentTree[1].middle), segmentTree[1].right);
}

void addRectangle(int n)
{
    addRectangle(1, 1, numOfRectangles, n);
}

void input(int numOfInput)
{
    maxResult = 0;

    for (int i = 0; i < numOfRectangles; i++)
    {
        int height;
        scanf("%d", &height);

        rectangles[i] = MyRectangle(i + 1, height);
    }
}

bool compare(MyRectangle a, MyRectangle b)
{
    return a.height > b.height;
}

void process()
{
    initTree();
    sort(rectangles, rectangles + numOfRectangles, compare);

    for(int i = 0; i < numOfRectangles; i++)
    {
        addRectangle(rectangles[i].x);
        long long result = (long long)calculateMax() * (long long)rectangles[i].height;
        if(maxResult < result)
            maxResult = result;
    }
}

void output()
{
    printf("%lld\n", maxResult);
}

int main()
{
    while (true)
    {
        scanf("%d", &numOfRectangles);

        if (numOfRectangles == 0)
            break;

        input(numOfRectangles);
        process();
        output();
    }

    return 0;
}