#include <iostream>
#include <vector>

using namespace std;

constexpr int MAX_NUM_ELEMENTS = 5'000;
constexpr int MAX_SUM = 800'000;

int target;
int numOfElements;
int numbers[MAX_NUM_ELEMENTS];
string result;

bool pairSum[MAX_SUM];

void input()
{
    scanf("%d %d", &target, &numOfElements);
    for(int i = 0; i < numOfElements; i++)
    {
        scanf("%d", &numbers[i]);
    }
}

void process()
{
    result = "NO";

    for(int i = 0; i < numOfElements - 1; i++)
    {
        for(int j = i + 1; j < numOfElements; j++)
        {
            int remain = target - numbers[i] - numbers[j];
            if(remain < 3)
                continue;
            if(pairSum[remain])
            {
                result = "YES";
                return;
            }
        }

        for(int j = 0; j < i; j++)
        {
            pairSum[numbers[i] + numbers[j]] = true;
        }
    }
}

void output()
{
    cout << result << endl;
}

int main()
{
    input();
    process();
    output();

    return 0;
}