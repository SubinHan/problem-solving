#include <iostream>

using namespace std;

constexpr int MAX_NUM = 1'000'000;
constexpr int MOD = 1'000'000'007;

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
    segment[node] = (initSegmentTree(node * 2, start, mid) * initSegmentTree(node * 2 + 1, mid + 1, end)) % MOD;
    return segment[node];
}

long long updateElement(int targetIndex, long long num, int node, int start, int end)
{
    if(start == end)
    {
        segment[node] = num;
        return num;
    }

    int mid = calculateMid(start, end);

    if(targetIndex <= mid)
    {
        long long updated = updateElement(targetIndex, num, node * 2, start, mid);
        segment[node] = updated * segment[node * 2 + 1] % MOD;
        return segment[node];
    }
    else
    {
        long long updated = updateElement(targetIndex, num, node * 2 + 1, mid + 1 , end);
        segment[node] = updated * segment[node * 2] % MOD;
        return segment[node];
    }  
}

long long calculateProduct(int node, int searchingIndexStart, int searchingIndexEnd, int productIndexStart, int productIndexEnd)
{
    if(productIndexStart <= searchingIndexStart && searchingIndexEnd <= productIndexEnd)
    {
        return segment[node];
    }

    long long result = 1;

    int mid = calculateMid(searchingIndexStart, searchingIndexEnd);
    if(productIndexStart <= mid)
    {
        result *= calculateProduct(node * 2, searchingIndexStart, mid, productIndexStart, productIndexEnd);
        result %= MOD;
    }
    if(productIndexEnd > mid)
    {
        result *= calculateProduct(node * 2 + 1, mid + 1, searchingIndexEnd, productIndexStart, productIndexEnd);
        result %= MOD;
    }

    return result;
}

long long calculateProduct(int start, int end)
{
    return calculateProduct(1, 1, numOfNumbers, start, end);
}

void changeElement(int index, long long num)
{
    numbers[index] = num;
    
    updateElement(index, num, 1, 1, numOfNumbers);
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
            printf("%lld\n", calculateProduct(b, c));
        }
    }
}

int main()
{
    process();

    return 0;
}