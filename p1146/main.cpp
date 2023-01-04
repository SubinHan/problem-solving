#include <iostream>

#define MAX_N 100
#define MOD 1000000

using namespace std;

int n;
int memo[MAX_N][MAX_N];
int result;

void input()
{
    cin >> n;

    for(int i = 0; i < MAX_N; i++)
    {
        for(int j = 0; j < MAX_N; j++)
        {
            memo[i][j] = -1;
        }
    }

    result = 0;
}

int calculateNumCases(int forward, int backward)
{
    if(memo[forward][backward] != -1)
        return memo[forward][backward];
    
    if(forward == 0 && backward > 0)
        return 0;
    if(forward == 0 && backward == 0)
        return 1;
    
    int result = 0;

    for(int i = 0; i < forward; i++)
    {
        result += calculateNumCases(backward + i, forward - i - 1);
        result %= MOD;
    }

    memo[forward][backward] = result;
    return result;
}

void process()
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j)
                continue;
            if(i < j) 
            {
                result += calculateNumCases(j - 1, n - j - 1);
                result %= MOD;
            }
            if(i > j)
            {
                result += calculateNumCases(n  - j - 2, j);
                result %= MOD;
            }           
        }
    }

    if(n == 1)
        result = 1;
    if(n == 2)
        result = 2;
}

void output()
{
    cout << result;
}

int main()
{
    input();
    process();
    output();
}