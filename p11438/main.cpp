#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

constexpr int MAX_NUM_NODES = 100'000;

int numOfNodes;
int numOfQueries;

vector<int> links[MAX_NUM_NODES + 1];
int parent[MAX_NUM_NODES + 1];
int level[MAX_NUM_NODES + 1];

bool visited[MAX_NUM_NODES + 1];
int lca[20][MAX_NUM_NODES + 1];

void treeInput()
{
    scanf("%d", &numOfNodes);
    for(int i = 1; i < numOfNodes; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        links[a].push_back(b);
        links[b].push_back(a);
    }
}

void dfs(int node)
{
    visited[node] = true;
    for(auto child : links[node])
    {
        if(visited[child])
            continue;
        parent[child] = node;
        level[child] = level[node] + 1;
        lca[0][child] = node;
        dfs(child);
    }
}

void makeTree()
{
    dfs(1);
}

void makeLca()
{
    for(int i = 1; i < 20; i++)
    {
        for(int j = 1; j <= numOfNodes; j++)
        {
            lca[i][j] = lca[i-1][lca[i-1][j]];
        }
    }
}

int findLca(int a, int b)
{
    if(level[a] > level[b])
    {
        int temp = a;
        a = b;
        b = temp;
    }



    for(int i = 17; level[b] - level[a] != 0; i--)
    {
        int diffTest = pow(2, i);

        int diff = level[b] - level[a];
        if(diff >= diffTest)
        {
            b = lca[i][b];
        }
    }

    if(a == b)
        return a;

    for(int i = 19; i >= 0; i--)
    {
        if(lca[i][a] != lca[i][b])
        {
            a = lca[i][a];
            b = lca[i][b];
        }
    }

    return parent[a];
}

int main()
{
    treeInput();
    makeTree();
    makeLca();

    scanf("%d", &numOfQueries);
    for(int i = 0; i < numOfQueries; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d", findLca(a, b));
    }

    return 0;
}