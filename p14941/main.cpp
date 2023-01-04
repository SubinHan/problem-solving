#include <iostream>
#include <vector>

using namespace std;

#define MAX_NUM 100001

bool isPrime[MAX_NUM];
vector<int> primes;
int a, b;
long long result;
long long accumulate[MAX_NUM];

void preprocess()
{
    for (int i = 2; i < MAX_NUM; i++)
    {
        isPrime[i] = true;
    }

    for (int i = 2; i * i < MAX_NUM; i++)
    {
        if (!isPrime[i])
            continue;

        for (int j = i * i; j < MAX_NUM; j += i)
        {
            isPrime[j] = false;
        }
    }

    primes.push_back(0);
    for (int i = 2; i < MAX_NUM; i++)
    {
        if (isPrime[i])
            primes.push_back(i);
    }

    accumulate[0] = 0;
    accumulate[1] = 2;

    for (int i = 2; i < primes.size(); i++)
    {
        int p = primes[i];
        accumulate[i] = accumulate[i - 2] + primes[i];
    }
}

int calculate(int aIndex, int bIndex)
{
    if (aIndex > bIndex)
    {
        return 0;
    }

    if (aIndex % 2 == 0)
    {
        if (bIndex % 2 == 0)
        {
            return (accumulate[bIndex] - accumulate[aIndex - 2]) * 3 - (accumulate[bIndex - 1] - accumulate[aIndex - 1]);
        }
        else
        {
            return (accumulate[bIndex - 1] - accumulate[aIndex - 2]) * 3 - (accumulate[bIndex] - accumulate[aIndex - 1]);
        }
    }
    else
    {
        if (aIndex == 1)
        {
            return (accumulate[(bIndex - 1) / 2 * 2 + 1]) * 3 - (accumulate[bIndex / 2 * 2]);
        }
        else
        {
            if (bIndex % 2 == 0)
            {
                return (accumulate[bIndex - 1] - accumulate[aIndex - 2]) * 3 - (accumulate[bIndex] - accumulate[aIndex - 1]);
            }
            else
            {
                return (accumulate[bIndex] - accumulate[aIndex - 2]) * 3 - (accumulate[bIndex - 1] - accumulate[aIndex - 1]);
            }
        }
    }
}

int binarySearch(int num)
{
    int low = 0;
    int high = primes.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (primes[mid] < num)
            low = mid + 1;
        else if (primes[mid] > num)
            high = mid - 1;
        else
            return mid;
    }
    return low;
}

void input()
{
    scanf("%d %d", &a, &b);
}

void process()
{
    int aIndex, bIndex;

    aIndex = binarySearch(a);
    bIndex = binarySearch(b);

    if (b < primes.at(bIndex))
    {
        bIndex--;
    }

    result = calculate(aIndex, bIndex);
}

void output()
{
    printf("%d\n", result);
}

int main()
{
    int n;
    cin >> n;
    preprocess();
    for (int i = 0; i < n; i++)
    {
        input();
        process();
        output();
    }

    return 0;
}