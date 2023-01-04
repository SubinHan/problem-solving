#include <iostream>
#include <stack>

#include <algorithm>

using namespace std;

constexpr int MAX_NUM_POINTS = 100'000;

struct Point
{
    int x;
    int y;

    Point operator- (Point p)
    {
        return Point{x - p.x, y - p.y};
    }
};

Point points[MAX_NUM_POINTS];
int numOfPoints;
stack<Point> convexHull;

long long calculateCrossProduct(Point v1, Point v2)
{
    return (long long)v1.x * (long long)v2.y - (long long)v1.y * (long long)v2.x;
}

bool ccw(Point p1, Point p2, Point p3)
{
    Point v1 = p2 - p1;
    Point v2 = p3 - p2;

    return calculateCrossProduct(v1, v2) > 0;
}


bool compare(Point p1, Point p2)
{
    Point v1 = p1 - points[0];
    Point v2 = p2 - points[0];

    long long crossProduct = calculateCrossProduct(v1, v2);

    if(crossProduct != 0)
        return crossProduct > 0;

    if(p1.y != p2. y)
        return p1.y < p2.y;

    return p1.x < p2.x;
}

void input()
{
    scanf("%d", &numOfPoints);

    for(int i = 0; i < numOfPoints; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        points[i].x = x;
        points[i].y = y;
    }
}

void process()
{
    int minY = 0;
    for(int i = 0; i < numOfPoints; i++)
    {
        if(points[i].y < points[minY].y || 
            (points[i].y == points[minY].y && points[i].x < points[minY].x))
        {
            minY = i;
        }
    }
    swap(points[0], points[minY]);

    sort(points + 1, points + numOfPoints, compare);

    int next = 0;
    Point top, nextToTop;

    while(next < numOfPoints)
    {
        while(convexHull.size() > 1)
        {
            top = convexHull.top();
            convexHull.pop();
            nextToTop = convexHull.top();

            if(ccw(nextToTop, top, points[next]))
            {
                convexHull.push(top);
                break;
            }
        }
        convexHull.push(points[next++]);
    }
}

void output()
{
    printf("%d", convexHull.size());
}

int main()
{
    input();
    process();
    output();

    return 0;
}