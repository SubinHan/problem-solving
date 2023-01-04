#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

constexpr int MAX_NUM_VERTICES = 40'000;
constexpr int MAX_NUM_QUERIES = 10'000;

vector<pair<int ,int>> graph[MAX_NUM_VERTICES + 1];
bool visited[MAX_NUM_VERTICES + 1];

int numOfNodes;
int numOfQueries;
int maxLevel = 0;

pair<int, long long> parents[MAX_NUM_VERTICES + 1][20];
int depth[MAX_NUM_VERTICES + 1];
int height;

void init(int nodeIndex, int level)
{
    if(maxLevel < level)
        maxLevel = level;
    
    for(auto child : graph[nodeIndex])
    {
        if(visited[child.first])
            continue;

        visited[child.first] = true;
        parents[child.first][0] = make_pair(nodeIndex, child.second);
        depth[child.first] = level + 1;

        init(child.first, level + 1);
    }
}

void input()
{
    scanf("%d", &numOfNodes);
    for(int i = 0; i < numOfNodes - 1; i++)
    {
        int a, b, distance;
        scanf("%d %d %d", &a, &b, &distance);
        graph[a].push_back(make_pair(b, distance));
        graph[b].push_back(make_pair(a, distance));
    }
}

long long calculateDistance(int a, int b)
{
    long long result = 0;

    if(depth[a] < depth[b])
    {
        swap(a, b);
    }

    for(int i = height - 1; i >= 0; i--)
    {
        if(pow(2, i) <= depth[a] - depth[b])
        {
            result += parents[a][i].second;
            a = parents[a][i].first;
        }
    }

    if(a == b)
        return result;
    
    for(int i = height - 1; i >= 0; i--)
    {
        if(parents[a][i].first != parents[b][i].first)
        {
            result += parents[a][i].second;
            result += parents[b][i].second;
            a = parents[a][i].first;
            b = parents[b][i].first;
        }
    }

    result += parents[a][0].second;
    result += parents[b][0].second;

    return result;
}

void processQueries()
{
    visited[1] = true;
    init(1, 1);
    height = (int)ceil(log(maxLevel)/log(2)) + 1;

    for(int j = 1; j <= height; j++)
    {
        for(int i = 1; i <= numOfNodes; i++)
        {
            parents[i][j] = make_pair(parents[parents[i][j-1].first][j-1].first, parents[parents[i][j-1].first][j-1].second + parents[i][j-1].second);
        }
    }

    scanf("%d", &numOfQueries);
    for(int i = 0; i < numOfQueries; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        long long result = calculateDistance(a, b);
        printf("%lld\n", result);
    }
}

int main()
{
    input();
    processQueries();

    return 0;
}