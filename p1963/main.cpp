#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX_PRIME 10001

bool isPrime[MAX_PRIME];
vector<int> graph[MAX_PRIME];
int a, b;
int visited[MAX_PRIME];

void calculatePrimeNumbers()
{
    for (int i = 2; i < MAX_PRIME; i++)
    {
        isPrime[i] = true;
    }

    for (int i = 2; i * i < MAX_PRIME; i++)
    {
        if (!isPrime[i])
            continue;

        for (int j = i * i; j < MAX_PRIME; j += i)
        {
            isPrime[j] = false;
        }
    }
}

void makeGraph()
{
    for (int num = 1000; num < MAX_PRIME; num++)
    {
        if (!isPrime[num])
            continue;

        int digit[] = {1000, 100, 10, 1};

        for (int j = 0; j < 4; j++)
        {
            int originDigit = num / digit[j] % 10;
            for (int k = 0; k < 10; k++)
            {
                if (k == originDigit)
                    continue;

                int target = num + (k - originDigit) * digit[j];

                if (isPrime[target])
                    graph[num].push_back(target);
            }
        }
    }
}

void input()
{
    scanf("%d %d", &a, &b);
}

void initVisited()
{
    for (int i = 0; i < MAX_PRIME; i++)
        visited[i] = -1;
}

bool hasVisited(int a)
{
    return visited[a] != -1;
}

void visit(int toVisit, int count)
{
    visited[toVisit] = count;
}

void process()
{
    initVisited();
    queue<int> q;

    visited[a] = 0;
    q.push(a);

    while (!q.empty())
    {
        int popped = q.front();
        q.pop();

        printf("%d\n", popped);

        if (popped == b)
            break;

        for (vector<int>::iterator iter = graph[popped].begin(); iter != graph[popped].end(); iter++)
        {
            if (hasVisited(*iter))
                continue;

            visit(*iter, visited[popped] + 1);
            q.push(*iter);
        }
    }
}

void output()
{
    if (visited[b] == -1)
        printf("Impossible\n");
    else
        printf("%d\n", visited[b]);
}

int main()
{
    calculatePrimeNumbers();
    makeGraph();

    int n;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        input();
        process();
        output();
    }

    cin >> n;

    return 0;
}