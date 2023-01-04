#include <iostream>

using namespace std;

constexpr int MAX_NUM = 1'000'000;

long long numbers[MAX_NUM + 1];

int numOfNumbers;
int numOfChanges;
int numOfQueries;

long long segment[MAX_NUM * 4];

int calculateMid(int start, int end)
{
    return start + (end - start) / 2;
}

long long initSegmentTree(int node, int start, int end)
{
    if (start == end)
    {
        segment[node] = numbers[start];
        return segment[node];
    }

    int mid = calculateMid(start, end);
    segment[node] = initSegmentTree(node * 2, start, mid) + initSegmentTree(node * 2 + 1, mid + 1, end);
    return segment[node];
}

long long changeElement(int targetIndex, long long num, int node, int start, int end)
{
    if(start == end)
    {
        long long diff = num - segment[node];
        segment[node] = num;
        return diff;
    }

    int mid = calculateMid(start, end);
    if(targetIndex <= mid)
    {
        long long diff = changeElement(targetIndex, num, node * 2, start, mid);
        segment[node] += diff;
        return diff;
    }
    else
    {
        long long diff = changeElement(targetIndex, num, node * 2 + 1, mid + 1, end);
        segment[node] += diff;
        return diff;
    }
}

long long calculateSum(int node, int searchingIndexStart, int searchingIndexEnd, int sumIndexStart, int sumIndexEnd)
{
    if(sumIndexStart <= searchingIndexStart && searchingIndexEnd <= sumIndexEnd)
    {
        return segment[node];
    }

    int mid = calculateMid(searchingIndexStart, searchingIndexEnd);

    long long result = 0;

    if(sumIndexStart <= mid)
    {
        result += calculateSum(node * 2, searchingIndexStart, mid, sumIndexStart, sumIndexEnd);
    }
    if(sumIndexEnd > mid)
    {
        result += calculateSum(node * 2 + 1, mid + 1, searchingIndexEnd, sumIndexStart, sumIndexEnd);
    }

    return result;
}

long long calculateSum(int start, int end)
{
    return calculateSum(1, 1, numOfNumbers, start, end);
}

void changeElement(int index, long long num)
{
    int start = 1;
    int end = numOfNumbers;
    int node = 1;

    changeElement(index, num, node, start, end);
}

bool isChangeCommand(int a)
{
    return a == 1;
}

void process()
{
    scanf("%d %d %d", &numOfNumbers, &numOfChanges, &numOfQueries);
    for (int i = 1; i <= numOfNumbers; i++)
    {
        scanf("%lld", &numbers[i]);
    }
    initSegmentTree(1, 1, numOfNumbers);

    int numOfCommands = numOfChanges + numOfQueries;
    for (int i = 0; i < numOfCommands; i++)
    {
        long long a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);

        if(isChangeCommand(a))
        {
            changeElement(b, c);
        }
        else
        {
            printf("%lld\n", calculateSum(b, c));
        }
    }
}

int main()
{
    process();

    return 0;
}