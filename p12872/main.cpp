#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_NUM = 100;
constexpr int MOD = 1'000'000'007;

int numMusic;
int cooltime;
int length;

long long dynamic[MAX_NUM + 1][MAX_NUM + 1];

int result;

void input()
{
    cin >> numMusic >> cooltime >> length;
}

void process()
{
    dynamic[1][1] = numMusic;

    for(int i = 2; i <= length; i++)
    {
        for(int j = 1; j <= numMusic; j++)
        {
            dynamic[i][j] = (dynamic[i-1][j] * max(0, j - cooltime) + dynamic[i-1][j-1] * (numMusic - (j-1))) % MOD; 
        }
    }
}

void output()
{
    cout << dynamic[length][numMusic] << endl;
}

int main()
{
    input();
    process();
    output();

    return 0;
}