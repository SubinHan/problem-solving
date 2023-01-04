#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

constexpr int MAX_NUM = 100'000;

struct Line
{
    int start;
    int end;
};

struct compare
{
    bool operator()(Line a, Line b)
    {  
        return a.start > b.start;
    }
};

bool compare2(Line a, Line b)
{
    if (a.end == b.end)
        return a.start < b.start;
    return a.end < b.end;
}

int numOfLines;
Line lines[MAX_NUM];
int dist;

priority_queue<Line, vector<Line>, compare> sweeping;
int maxResult;

void input()
{
    scanf("%d", &numOfLines);
    for(int i = 0; i < numOfLines; i++)
    {
        int s, e;
        scanf("%d %d", &s, &e);
        if(e < s)
        {
            int t = s;
            s = e;
            e = t;
        }
        lines[i] = Line{s, e};
    }
    scanf("%d", &dist);
}

void process()
{
    sort(lines, lines + numOfLines, compare2);

    for(int i = 0; i < numOfLines; i++)
    {
        if(lines[i].end - lines[i].start > dist)
            continue;

        while(!sweeping.empty() && !(lines[i].end <= sweeping.top().start + dist))
        {
            sweeping.pop();
        }
        sweeping.push(lines[i]);

        if(maxResult < sweeping.size())
            maxResult = sweeping.size();
    }
}

void output()
{
    printf("%d", maxResult);
}

int main()
{
    input();
    process();
    output();

    return 0;
}