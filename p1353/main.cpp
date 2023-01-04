#include <iostream>
#include <cmath>

using namespace std;

long long s, p;
int result;

void input()
{
    cin >> s >> p;
}

void process()
{
    long long i = 1;
    while(true)
    {
        double piece = (double)s / (double)i;
        if(piece < 2)
        {
            result = -1;
            break;
        }

        double max = pow(piece, i);

        if(p <= max)
        {
            result = i;
            break;
        }
        i++;        
    }
    
    if(p == 1 && s == 1)
        result = 1;
    
    if(s > p)
        result = 2;
}

void output()
{
    cout << result;
    cin >> s;
}

int main()
{
    input();
    process();
    output();
}