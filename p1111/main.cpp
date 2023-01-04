#include <iostream>

using namespace std;

constexpr int MAX_NUM = 50;

int n;
int num[MAX_NUM];

int result;

void input()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
}

void processAndOutput()
{
    if (n == 1)
    {
        cout << "A" << endl;
        return;
    }

    if (n == 2)
    {
        if (num[0] - num[1] == 0)
        {
            cout << num[0] << endl;
            return;
        }

        if (num[0] == 0)
        {
            cout << num[1] + num[1] << endl;
            return;
        }
        cout << "A" << endl;
        return;
    }

    if (num[0] - num[1] == 0)
    {
        if (num[1] - num[2] == 0)
        {
            for(int i = 3; i < n; i++)
                if(num[i] != num[0])
                {
                    cout << "B" << endl;
                    return;
                }
            cout << num[0] << endl;
            return;
        }
        cout << "B" << endl;
        return;
    }

    long long a = (num[1] - num[2]) / (num[0] - num[1]);
    long long b = num[1] - (num[0] * a);

    long long next = num[0] * a + b;
    for (int i = 1; i < n; i++)
    {
        if(num[i] != next)
        {
            cout << "B" << endl;
            return;
        }
        next = num[i] * a + b;
    }
    cout << next << endl;
}

int main()
{
    input();
    processAndOutput();
    int a = 0;
}