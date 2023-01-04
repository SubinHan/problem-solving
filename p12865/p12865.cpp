#include <iostream>
#include <vector>

using namespace std;

int n, k;
int result;
int weight[100];
int value[100];
int dynamic[100001];

void input()
{
    cin >> n >> k;
    for(int i = 0; i < n; i++)
    {
        cin >> weight[i] >> value[i];
    }

    for(int i = 1; i <= k; i++)
    {
        dynamic[i] = 0;
    }

    result = 0;
}

void process()
{
    for (int i = 0; i < n; i++)
    {
        for(int j = k; j >= weight[i]; j--)
        {
            if(dynamic[j-weight[i]] + value[i] > dynamic[j])
            {
                dynamic[j] = dynamic[j-weight[i]] + value[i];
            }
        }
    }
}

void output()
{
    int max = 0;
    for(int i = 1; i <= k; i++)
    {
        if(dynamic[i] > max)
            max = dynamic[i];
    }
    cout << max << endl;
}

int main()
{
    input();
    process();
    output();
    cin >> result;
}