#include <iostream>

using namespace std;

constexpr int MAX_NUM_EVENTS = 1'000;

int gridSize;
int numOfEvents;

int dynamic[MAX_NUM_EVENTS + 1][MAX_NUM_EVENTS + 1];

class Point
{
public:
    int x;
    int y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

Point events[MAX_NUM_EVENTS + 1];

int result;

void input()
{
    scanf("%d", &gridSize);
    scanf("%d", &numOfEvents);
    for(int i = 1; i <= numOfEvents; i++)
    {
        scanf("%d %d", &events[i].x, &events[i].y);
    }
}

int calculateDistance(Point p1, Point p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

Point getFirstPolicePoint(int event)
{
    if(event == 0)
        return Point(1, 1);
    else
        return events[event];
}

Point getSecondPolicePoint(int event)
{
    if(event == 0)
        return Point(gridSize, gridSize);
    else
        return events[event];
}

int dfs(int lastEventOfFirstPolice, int lastEventOfSecondPolice)
{
    if(dynamic[lastEventOfFirstPolice][lastEventOfSecondPolice] != -1)
        return dynamic[lastEventOfFirstPolice][lastEventOfSecondPolice];

    int nextEvent = max(lastEventOfFirstPolice, lastEventOfSecondPolice) + 1;
    Point targetPoint = events[nextEvent];
    Point firstPolice;
    Point secondPolice;

    if(lastEventOfFirstPolice == 0)
        firstPolice = Point(1, 1);
    else
        firstPolice = events[lastEventOfFirstPolice];

    if(lastEventOfSecondPolice == 0)
        secondPolice = Point(gridSize, gridSize);
    else
        secondPolice = events[lastEventOfSecondPolice];

    int distanceToFirst = calculateDistance(firstPolice, targetPoint);
    int distanceToSecond = calculateDistance(secondPolice, targetPoint);

    if(nextEvent == numOfEvents)
    {
        if(distanceToFirst >= distanceToSecond)
        {
            dynamic[lastEventOfFirstPolice][lastEventOfSecondPolice] = distanceToSecond;
        }
        if(distanceToFirst <= distanceToSecond)
        {
            dynamic[lastEventOfFirstPolice][lastEventOfSecondPolice] = distanceToFirst;
        }

        return dynamic[lastEventOfFirstPolice][lastEventOfSecondPolice];
    }

    int firstMovedResult = dfs(nextEvent, lastEventOfSecondPolice) + distanceToFirst;
    int secondMovedResult = dfs(lastEventOfFirstPolice, nextEvent) + distanceToSecond;
    
    dynamic[lastEventOfFirstPolice][lastEventOfSecondPolice] = min(firstMovedResult, secondMovedResult);
    return dynamic[lastEventOfFirstPolice][lastEventOfSecondPolice];
}

void process()
{
    for(int i = 0; i < MAX_NUM_EVENTS + 1; i++)
    {
        for(int j = 0; j < MAX_NUM_EVENTS + 1; j++)
        {
            dynamic[i][j] = -1;
        }
    }

    result = dfs(0, 0);    
}

void printTrace()
{
    for(int i = 0, first = 0, second = 0; i < numOfEvents; i++)
    {
        int next = max(first, second) + 1;
        if(dynamic[next][second] + calculateDistance(getFirstPolicePoint(first), events[next]) > dynamic[first][next] + calculateDistance(getSecondPolicePoint(second), events[next]) )
        {
            printf("2\n");
            second = next;
        }
        else
        {
            printf("1\n");
            first = next;
        }
    }
}

void output()
{
    printf("%d\n", result);
    printTrace();
}

int main()
{
    input();
    process();
    output();

    return 0;
}