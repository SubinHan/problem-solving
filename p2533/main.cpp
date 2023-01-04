#include <iostream>
#include <list>
#include <vector>
#include <stack>

using namespace std;

constexpr int MAX_NUM_VERTICES = 1'000'000;

int sizeOfTree;
vector<int> friends[MAX_NUM_VERTICES + 1];
bool visited[MAX_NUM_VERTICES + 1];
bool isEa[MAX_NUM_VERTICES + 1];
stack<int> s;
int result;

void input()
{
    scanf("%d", &sizeOfTree);

    for (int i = 0; i < sizeOfTree - 1; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        friends[a].push_back(b);
        friends[b].push_back(a);
    }
}

void myInput()
{
    sizeOfTree = 1000000;
    for (int i = 1; i < sizeOfTree; i++)
    {
        int a, b;
        a = i;
        b = i + 1;
        friends[a].push_back(b);
        friends[b].push_back(a);
    }
}

void findLeafAndRemoveItsParent(int vertex)
{
    visited[vertex] = true;
    int numFriend = 0;
    int parent = 0;

    if(isEa[vertex])
    {
        for (int child : friends[vertex])
        {
            if(!visited[child])
            {
                s.push(child);
            }
        }
        return;
    }

    bool isDone = true;
    for (int child : friends[vertex])
    {
        if (!isEa[child])
        {
            isDone = false;
            break;
        }
    }
    if(isDone)
    {
        return;
    }



    s.push(vertex);

    for (int child : friends[vertex])
    {
        if (visited[child])
            continue;
        s.push(child);
    }

    numFriend = 0;
    for (int child : friends[vertex])
    {
        if (isEa[child])
            continue;
        numFriend++;
        parent = child;
    }

    if (numFriend == 1)
    {
        isEa[parent] = true;
        result++;
        return;
    }
}

void process()
{
    s.push(1);
    while (!s.empty())
    {
        int v = s.top();
        s.pop();
        if (v == 0)
            continue;

        findLeafAndRemoveItsParent(v);
    }
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