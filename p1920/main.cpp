#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_NUM = 100000;

int numOfNumbers;
int numOfQueries;
int numbers[MAX_NUM];
int queries[MAX_NUM];

void input()
{
    scanf("%d", &numOfNumbers);
    for (int i = 0; i < numOfNumbers; i++)
    {
        scanf("%d", &numbers[i]);
    }

    scanf("%d", &numOfQueries);
    for (int i = 0; i < numOfQueries; i++)
    {
        scanf("%d", &queries[i]);
    }
}

int binarySearch(int target)
{
    int low = 0;
    int high = numOfNumbers - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (numbers[mid] > target)
        {
            high = mid - 1;
        }
        else if (numbers[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

void processAndOutput()
{
    sort(numbers, numbers + numOfNumbers);
    for (int i = 0; i < numOfQueries; i++)
    {
        printf("%d\n", binarySearch(queries[i]));
    }
}

int main()
{
    input();
    processAndOutput();

    return 0;
}