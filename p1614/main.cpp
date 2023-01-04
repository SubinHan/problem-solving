#include <iostream>

using namespace std;

int k;
long long n;
long long result;

void input()
{
    scanf("%d %d", &k, &n);
}

void process()
{
    if (k == 1 || k == 5)
    {
        result += 8 * n;
        result += k - 1;
        return;
    }
    
    if (n % 2 == 0)
    {
        result += 4 * n;
        result += k - 1;
        return;
    }

    result += 4 * n;
    result += 5 - k;
}

void output()
{
    printf("%lld", result);
}

int main()
{
    input();
    process();
    output();

    return 0;
}