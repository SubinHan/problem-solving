#include <iostream>
#include <float.h>
#include <math.h>
#include <limits>

using namespace std;
typedef std::numeric_limits< double > dbl;

int t;
int x, y;
int dist;
long long sum[50000];
int result;

void input()
{
    cin >> x >> y;
    dist = y - x;
}

void process()
{
    for(int i = 0;;i++)
    {
        if(sum[i] < dist && dist <= sum[i+1])
        {
            result = i*2;
            if(dist <= sum[i+1] - i)
                result--;
            break;
        }
    }
}

void output()
{
    cout << result << endl;
}

int main()
{
    for(long i = 0; i < 46343; i++)
    {
        sum[i] = i * i - i;
    }

    cin >> t;
    for (int i = 0; i < t; i++)
    {
        input();
        process();
        output();
    }
}