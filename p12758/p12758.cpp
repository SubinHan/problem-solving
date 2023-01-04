#include <iostream>
#include <math.h>

#define MAX_OBJECT 300
#define MAX_HEIGHT 1000000

int t;
int n;
int h[MAX_OBJECT];
unsigned long long result;

using namespace std;

class Memo
{
public:
    int height[1000];
    unsigned long long num[1000];
    int size = 0;

    void calculate(int height, Memo next)
    {
        unsigned long long num_result = 0;
        for(int i = 0; i < next.size; i++)
        {
            if(height <= next.height[i])
            {
                num_result += next.num[i] % 1000000007LLU;
            }
        }

        this->add(height, num_result);
    }

    void add(int height, unsigned long long num)
    {
        this->height[size] = height;
        this->num[size] = num;
        size++;
    }
};

Memo memo[MAX_OBJECT];

void input()
{
    cin >> n;
    for (int j = 0; j < n; j++)
    {
        cin >> h[j];
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < memo[i].size; j++)
        {
            memo[i].num[j] = 0LLU;
            memo[i].height[j] = 0;
        }
        memo[i].size = 0;
    }
}

void process()
{
    int m = sqrt(h[n-1]);
    for(int i = 1; i <= m; i++)
    {
        if (h[n-1] % i == 0)
        {
            memo[n-1].add(i, 1LLU);
            if (h[n-1] / i != i)
            {
                memo[n-1].add(h[n-1] / i, 1LLU);
            }
        }
    }

    for (int i = n - 2; i >= 0; i--)
    {
        int m = sqrt(h[i]);
        for (int j = 1; j <= m; j++)
        {
            if(h[i] % j == 0)
            {
                memo[i].calculate(j, memo[i+1]);
                if(h[i] / j != j)
                {
                    memo[i].calculate(h[i] / j, memo[i+1]);
                }
            }
        }
    }
}

void output()
{
    result = 0LLU;
    for(int i = 0; i < memo[0].size; i++)
    {
        result += memo[0].num[i] % 1000000007LLU ;
    }
    cout << result % 1000000007LLU << endl;
}

int main()
{
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        input();
        process();
        output();
    }

    return 0;
}