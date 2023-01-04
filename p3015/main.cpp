#include <iostream>
#include <stack>

using namespace std;

constexpr int MAX_NUM_HUMANS = 500'000;

int numOfHumans;
int humans[MAX_NUM_HUMANS];

stack<pair<int, int>> s;
int top;

long long result;

void input()
{
    scanf("%d", &numOfHumans);
    for(int i = 0; i < numOfHumans; i++)
    {
        scanf("%d", &humans[i]);
    }
}

bool decreased(int index)
{
    return humans[index - 1] > humans[index];
}

void process()
{
    s.push(make_pair(humans[0], 1));
    for(int i = 1; i < numOfHumans; i++)
    {
        if(decreased(i))
        {
            result++;
            auto [height, count] = s.top();
            if(height == humans[i])
            {
                s.pop();
                s.push(make_pair(height, count + 1));
                continue;
            }
            s.push(make_pair(humans[i], 1));
        }
        else
        {
            while(!s.empty())
            {
                auto [height, count] = s.top();

                if(height > humans[i])
                {
                    result++;
                    s.push(make_pair(humans[i], 1));
                    break;
                }

                s.pop();

                result += count;

                if(height == humans[i])
                {
                    if(!s.empty())
                        result++;
                    s.push(make_pair(height, count + 1));
                    break;
                }
            }

            if(s.empty())
            {
                s.push(make_pair(humans[i], 1));
            }
        }
    }
}

void output()
{
    printf("%lld\n", result);
}

int main()
{
    input();
    process();
    output();

    return 0;
}