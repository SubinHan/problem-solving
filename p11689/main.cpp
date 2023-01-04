#include <iostream>
#include <set>
#include <cmath>

using namespace std;

unsigned long long n;
unsigned long long c;
unsigned long long result;
set<unsigned long long> factors;

void input()
{
    cin >> n;
    result = n;
}

unsigned long long division(unsigned long long n)
{
    unsigned long long max = sqrt(n);
    for(unsigned long long i = 2; i <= max; i++)
    {
        if(n % i == 0)
        {
            return i;
        }
    }
    return n;
}

void divide()
{
    for(set<unsigned long long>::iterator iter = factors.begin(); iter != factors.end();)
    {
        if(result % *iter == 0)
        {
            result /= *iter;
            factors.erase(iter++);
        }
        else
        {
            iter++;
        }
    }
}

void process()
{
    if(n == 1)
        return;
    
    c = n;
    while(true)
    {   
        unsigned long long factor = division(c);
        if(factor != c)
        {
            c /= factor;
            factors.insert(factor);
            continue;
        }
        factors.insert(c);
        break;
    }

    for(set<unsigned long long>::iterator iter = factors.begin(); iter != factors.end(); iter++)
    {
        if(result % *iter == 0)
        {
            result /= *iter;
            result *= *iter - 1;
        }
        else
        {
            result *= *iter - 1;
            result /= *iter;
        }
    }


}

void output()
{
    cout << result;
}

int main()
{
    input();
    process();
    output();
    cin >> n;
}