#include <iostream>
#include <vector>
#include <queue>

using namespace std;

constexpr int MAX_NUM_NODES = 500;

int numOfEdges;
int numOfNodes;
int s;
int e;

vector<pair<int, int>> graph[MAX_NUM_NODES];
bool visited[MAX_NUM_NODES];
int dist[MAX_NUM_NODES];
vector<int> from[MAX_NUM_NODES];
bool available[MAX_NUM_NODES][MAX_NUM_NODES];

void input()
{
    for(int i = 0; i < numOfNodes; i++)
    {
        graph[i].clear();
        from[i].clear();
        for(int j = 0; j < numOfNodes; j++)
        {
            available[i][j] = true;
        }
    }


    scanf("%d %d", &s, &e);

    for(int i = 0; i < numOfEdges; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        graph[a].emplace_back(b, c);
    }
}

class compare
{
public:
    bool operator()(const int& a, const int &b)
    {
        return dist[a] > dist[b];
    }
};

void dijkstra(int start, int end)
{
    for(int i = 0; i < numOfNodes; i++)
    {
        dist[i] = INT32_MAX;
        visited[i] = false;
    }
    dist[start] = 0;

    priority_queue<int, vector<int>, compare> q;
    q.push(start);

    while(!q.empty())
    {
        int v = q.top();
        q.pop();

        if(visited[v])
            continue;
        
        visited[v] = true;

        for(auto w : graph[v])
        {
            if(!available[v][w.first])
                continue;

            int newDist = dist[v] + w.second;

            if(dist[w.first] == dist[v] + w.second)
            {
                from[w.first].push_back(v);
            }

            if(dist[w.first] > dist[v] + w.second)
            {
                dist[w.first] = dist[v] + w.second;
                from[w.first].clear();
                from[w.first].push_back(v);
            }

            q.push(w.first);
        }
    }
}

void removePaths(int v)
{
    visited[v] = true;
    for(int w : from[v])
    {
        available[w][v] = false;
        if(visited[w])
            continue;
        removePaths(w);
    }
}

void process()
{
    dijkstra(s, e);
    for(int i = 0; i < numOfNodes; i++)
    {
        visited[i] = false;
    }
    removePaths(e);
    dijkstra(s, e);
}

void output()
{
    if(dist[e] == INT32_MAX)
    {
        printf("-1\n");
        return;
    }
    
    printf("%d\n", dist[e]);
}

int main()
{
    while(true)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        if(a == 0 && b == 0)
            break;

        numOfNodes = a;
        numOfEdges = b;

        input();
        process();
        output();

    }
    return 0;
}