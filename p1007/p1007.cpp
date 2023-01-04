#include <iostream>
#include <float.h>
#include <math.h>
#include <limits>

using namespace std;
typedef std::numeric_limits< double > dbl;

int t;
int n;
class Point{
public:
    int x;
    int y;

    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y){}

    Point operator-(Point& p)
    {
        return Point(x - p.x, y - p.y);
    }

    Point operator-()
    {
        return Point(-x, -y);
    }

    Point operator+(Point& p)
    {
        return Point(x + p.x, y + p.y);
    }
};

Point points[20];
double result;
bool visited[20];
Point sumVector;

double getSize(Point p)
{
    return sqrt((double)p.x*(double)p.x+(double)p.y*(double)p.y);
}

void calcSum()
{
    for(int i = 0; i < n; i++)
    {
        sumVector = sumVector + points[i];
    }
}

Point calcMinRecur(Point sum, int remain, int index)
{
    if(remain == 0)
    {
        return sumVector - sum - sum;
    }

    Point answer(INT_MAX, INT_MAX);
    for (int i = index; i < n; i++)
    {
        if (visited[i])
            continue;

        visited[i] = true;
        Point temp = calcMinRecur(sum + points[i], remain-1, i+1);
        if(getSize(answer) > getSize(temp))
            answer = temp;
        visited[i] = false;
    }

    return answer;
}

void input()
{
    sumVector.x = 0; 
    sumVector.y = 0;
    for(int i = 0; i < n; i++)
    {
        visited[i] = false;
    }
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
    }
}

void process()
{
    double min = DBL_MAX; 
    double sum = 0.f;

    calcSum();
    result = getSize(calcMinRecur(Point(0,0), n/2, 0));
}

void output()
{
    cout.precision(dbl::max_digits10);
    cout << result << endl;
}

int main()
{
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        input();
        process();
        output();
    }
}