#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_N = 101;
constexpr int MAX_C = 10100;

int n, m;
int dynamic[MAX_C];

int memory[MAX_N];
int cost[MAX_N];

int result;

void input()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &memory[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &cost[i]);
    }

    for (int i = 0; i < MAX_C; i++)
    {
        dynamic[i] = 0;
    }
}

void process()
{
    int size = 0;
    for (int i = 0; i < n; i++)
        size += cost[i];

    for (int i = 0; i < n; i++)
    {
        for (int j = size; j >= cost[i]; j--)
        {
            dynamic[j] = max(dynamic[j], dynamic[j - cost[i]] + memory[i]);
        }
    }
}

void output()
{
    for (int i = 0; i < MAX_C; i++)
    {
        if (dynamic[i] >= m)
        {
            cout << i << endl;
            break;
        }
    }
}

int main()
{
    input();
    process();
    output();

    cin >> n;

    return 0;
}