#include <iostream>
#include <vector>

using namespace std;

constexpr int MAX_NUM = 1'000'000;

int numOfNumbers;
int numOfChanges;
int numOfQuestions;

long long numbers[MAX_NUM];

class SegmentTree
{
    struct Node
    {
        long long value;
        long long lazy;
    };

public:
    SegmentTree(long long numbers[], int size)
    {
        treeSize = size * 4;
        tree = vector<Node>(treeSize);
        this->numbers = vector<long long>(numbers, numbers + size);

        initSegmentTree(size);
    }

    void addNumberFromTo(long long num, int start, int end)
    {
        int startNode = 1;
        int searchStart = 1;
        int searchEnd = numbers.size();

        addNumberFromTo(num, startNode, searchStart, searchEnd, start, end);
    }

    long long calculateSum(int start, int end)
    {
        int nodeStart = 1;
        int searchStart = 1;
        int searchEnd = numbers.size();

        return calculateSum(nodeStart, searchStart, searchEnd, start, end);
    }

private:
    int calculateMid(int start, int end)
    {
        return start + (end - start) / 2;
    }

    void initSegmentTree(int size)
    {
        int nodeStart = 1;
        int rangeStart = 1;
        int rangeEnd = size;

        initSegmentTree(nodeStart, rangeStart, rangeEnd);
    }

    long long initSegmentTree(int node, int start, int end)
    {
        if (start == end)
        {
            tree[node].value = (long long)numbers[start-1];
            return tree[node].value;
        }

        int mid = calculateMid(start, end);

        long long left = initSegmentTree(node * 2, start, mid);
        long long right = initSegmentTree(node * 2 + 1, mid + 1, end);

        tree[node].value = left + right;
        return tree[node].value;
    }

    void updateTree(int node, int nodeIntervalStart, int nodeIntervalEnd, int target, int diff)
    {
        if (nodeIntervalStart > target || nodeIntervalEnd < target)
            return;
        
        if (nodeIntervalStart == nodeIntervalEnd)
        {
            tree[node] += diff;
            return;
        }

        tree[node].value += diff;
        int mid = calculateMid(nodeIntervalStart, nodeIntervalEnd);
        updateTree(node * 2, nodeIntervalStart, mid, target, diff);
        updateTree(node * 2 + 1, mid + 1, nodeIntervalEnd, target, diff);
    }

    void addNumberFromTo(long long num, int node, int searchingStart, int searchingEnd, int targetStart, int targetEnd)
    {
        updateLazy(node, searchingStart, searchingEnd);

        if (targetEnd < searchingStart || searchingEnd < targetStart)
        {
            return;
        }

        if (targetStart <= searchingStart && searchingEnd <= targetEnd)
        {
            int rangeSize = searchingEnd - searchingStart + 1;
            tree[node].value += num * rangeSize;

            if(searchingStart != searchingEnd)
            {
                tree[node * 2].lazy += num;
                tree[node * 2 + 1].lazy += num;
            }
            return;
        }

        int mid = calculateMid(searchingStart, searchingEnd);
        addNumberFromTo(num, node * 2, searchingStart, mid, targetStart, targetEnd);
        addNumberFromTo(num, node * 2 + 1, mid + 1, searchingEnd, targetStart, targetEnd);

        tree[node].value = tree[node * 2].value + tree[node * 2 + 1].value;
    }

    long long calculateSum(int node, int nodeIntervalStart, int nodeIntervalEnd, int targetIntervalStart, int targetIntervalEnd)
    {
        updateLazy(node, nodeIntervalStart, nodeIntervalEnd);

        if (targetIntervalEnd < nodeIntervalStart || nodeIntervalEnd < targetIntervalStart)
        {
            return 0;
        }

        if (targetIntervalStart <= nodeIntervalStart && nodeIntervalEnd <= targetIntervalEnd)
        {
            return tree[node].value;
        }

        int mid = calculateMid(nodeIntervalStart, nodeIntervalEnd);
        long long left = calculateSum(node * 2, nodeIntervalStart, mid, targetIntervalStart, targetIntervalEnd);
        long long right = calculateSum(node * 2 + 1, mid + 1, nodeIntervalEnd, targetIntervalStart, targetIntervalEnd);

        return left + right;
    }

    void updateLazy(int node, int nodeRangeStart, int nodeRangeEnd)
    {
        if (tree[node].lazy != 0)
        {
            int rangeSize = nodeRangeEnd - nodeRangeStart + 1;
            tree[node].value += tree[node].lazy * rangeSize;

            if (nodeRangeStart != nodeRangeEnd)
            {
                tree[node * 2].lazy += tree[node].lazy;
                tree[node * 2 + 1].lazy += tree[node].lazy;
            }

            tree[node].lazy = 0;
        }
    }

private:
    vector<long long> numbers;
    vector<Node> tree;
    int treeSize;
};

bool isChange(int command)
{
    return command == 1;
}

void process()
{
    scanf("%d %d %d", &numOfNumbers, &numOfChanges, &numOfQuestions);
    for (int i = 0; i < numOfNumbers; i++)
    {
        scanf("%lld", &numbers[i]);
    }

    SegmentTree segmentTree = SegmentTree(numbers, numOfNumbers);

    int numOfCommands = numOfChanges + numOfQuestions;

    for (int i = 0; i < numOfCommands; i++)
    {
        int prefix;
        scanf("%d", &prefix);

        if (isChange(prefix))
        {
            int rangeStart, rangeEnd;
            long long numToAdd;

            scanf("%d %d %lld", &rangeStart, &rangeEnd, &numToAdd);

            segmentTree.addNumberFromTo(numToAdd, rangeStart, rangeEnd);
        }
        else
        {
            int rangeStart, rangeEnd;
            scanf("%d %d", &rangeStart, &rangeEnd);

            printf("%lld\n", segmentTree.calculateSum(rangeStart, rangeEnd));
        }
    }
}

int main()
{
    process();

    return 0;
}

long long calculateSum(int numbers[], int a, int b)
{
    long long result = 0;

    for(int i = a; i <= b; i++)
    {
        result += numbers[i];
    }

    return result;
}

int constexpr N = 1;

long long numbers[N];
long long prefixSums[N + 1];

void precompute()
{
    prefixSums[0] = 0;
    for(int i = 1; i < N; i++)
    {
        prefixSums[i] += prefixSums[i-1] + numbers[i-1];
    }
}

long long calculatePrefix(int start, int end)
{
    if(start > end)
        ;// throw exception
    return prefixSums[end + 1] - prefixSums[start - 1];
}