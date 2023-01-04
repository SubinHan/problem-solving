#include <iostream>

using namespace std;

constexpr int MAX_NUM_POINTS = 1'000;

int numOfPoints;

class Point
{
public:
    int x;
    int y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

Point points[MAX_NUM_POINTS];
int resultIndex;

void input()
{
    scanf("%d", &numOfPoints);
    for(int i = 0; i < numOfPoints; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        points[i] = Point(x, y);
    }
}

int calculateDistance(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void process()
{
    int minOfMaxes = INT32_MAX;
    for(int i = 0; i < numOfPoints; i++)
    {
        int maxDistance = 0;
        for(int j = 0; j < numOfPoints; j++)
        {
            int distance = calculateDistance(points[i], points[j]);
            if(maxDistance < distance)
            {
                maxDistance = distance;
            }
        }
        if(minOfMaxes > maxDistance)
        {
            minOfMaxes = maxDistance;
            resultIndex = i;
        }
    }
}

void output()
{
    printf("%d %d", points[resultIndex].x, points[resultIndex].y);
}

int main()
{
    input();
    process();
    output();

    return 0;
}