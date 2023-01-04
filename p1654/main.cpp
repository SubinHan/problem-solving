#include <iostream>

using namespace std;

constexpr int MAX_NUM_CABLES = 10000;
constexpr int MAX_LENGTH_CABLES = INT32_MAX;

int numOfCables;
int target;
int cables[MAX_NUM_CABLES];
int result;

void input()
{
    scanf("%d %d", &numOfCables, &target);
    for(int i = 0; i < numOfCables; i++)
    {
        scanf("%d", &cables[i]);
    }
}

long long calculateCountOfCutCables(int length)
{
    long long countOfCutCables = 0;
    for(int i = 0; i < numOfCables; i++)
    {
        countOfCutCables += cables[i] / length;
    }
    
    return countOfCutCables;
}

int binarySearch(int target)
{
    int low = 1;
    int high = MAX_LENGTH_CABLES;
    int result = 1;

    while(low <= high)
    {
        int mid = low + (high - low) / 2;
        
        long long countOfCutCables = calculateCountOfCutCables(mid);

        if(countOfCutCables < target)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
            result = mid;
        }
    }
    return result;
}

void process()
{
    long long countOfCutCables = calculateCountOfCutCables(INT32_MAX);
    if(countOfCutCables >= target)
    {
        result = INT32_MAX;
        return;
    }

    result = binarySearch(target);
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