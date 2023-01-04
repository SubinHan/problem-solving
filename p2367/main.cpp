#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <algorithm>

using namespace std;

constexpr int MAX_NUM_KIND_FOOD = 100;

int numPeople;
int maxDishesPerPerson;
int numKindFood;
int maxDishesPerFood[MAX_NUM_KIND_FOOD];
int result;

class Edge
{
private:
    int from;
    int to;
    int flow;
    int capacity;

public:
    Edge(int from, int to, int capacity) : from{from}, to{to}, flow{0}, capacity{capacity} {}
    int other(int vertex)
    {
        return vertex == to ? from : to;
    }

    int residualCapacityTo(int vertex)
    {
        return vertex == to ? capacity - flow : flow;
    }

    void addResidualFlowTo(int vertex, int delta)
    {
        vertex == to ? flow += delta : flow -= delta;
    }
};

class Graph
{
private:
    int size;
    vector<vector<Edge*>> adj;

public:
    Graph(int size) : size(size), adj(size) {}

    void addEdge(int from, int to, int capacity)
    {
        auto edge = new Edge(from, to, capacity);
        adj[from].push_back(edge);
        adj[to].push_back(edge);
    }

    int getSize()
    {
        return size;
    }

    auto getEdges(int v)
    {
        return adj[v];
    }
};

unique_ptr<Graph> g;

void input()
{
    cin >> numPeople >> maxDishesPerPerson >> numKindFood;
    for (int i = 0; i < numKindFood; i++)
    {
        cin >> maxDishesPerFood[i];
    }

    g = make_unique<Graph>(2 + numPeople + numKindFood);

    for (int i = 0; i < numPeople; i++)
    {
        int numCookable{};
        cin >> numCookable;

        for (int j = 0; j < numCookable; j++)
        {
            int cookable{};
            cin >> cookable;
            g->addEdge(i, numPeople + cookable - 1, 1);
        }
    }

    for (int i = 0; i < numPeople; i++)
    {
        int s = numPeople + numKindFood;
        g->addEdge(s, i, maxDishesPerPerson);
    }

    for (int i = 0; i < numKindFood; i++)
    {
        int t = numPeople + numKindFood + 1;
        g->addEdge(numPeople + i, t, maxDishesPerFood[i]);
    }
}

class FordFulkerson
{
private:
    vector<Edge*> edgeTo;
    vector<bool> visited;
    vector<int> level, work;
    int flow;

public:
    FordFulkerson(Graph& g, const int s, const int t) : edgeTo(g.getSize()), visited(g.getSize()), flow{0}
    {
        while (hasAugmentingPath(g, s, t))
        {
            int bottle = INT32_MAX;
            for (int v = t; v != s; v = edgeTo[v]->other(v))
                bottle = min(bottle, edgeTo[v]->residualCapacityTo(v));

            for(int v = t; v != s; v = edgeTo[v]->other(v))
                edgeTo[v]->addResidualFlowTo(v, bottle);
            
            flow += bottle;
        }
    }

    bool hasAugmentingPath(Graph &g, const int s, const int t)
    {
        visited = vector<bool>(visited.size());

        queue<int> q;
        q.push(s);
        visited[s] = true;
        while (!q.empty())
        {
            int v = q.front();
            q.pop();

            for (auto e : g.getEdges(v))
            {
                int w = e->other(v);
                if (!visited[w] && e->residualCapacityTo(w) > 0)
                {
                    edgeTo[w] = e;
                    visited[w] = true;
                    q.push(w);
                }
            }
        }

        return visited[t];
    }

    int getFlow()
    {
        return flow;
    }
};

void process()
{
    FordFulkerson ff(*g, g->getSize() - 2, g->getSize() - 1);
    result = ff.getFlow();
}

void output()
{
    cout << result << endl;
}

int main()
{
    input();
    process();
    output();

    return 0;
}