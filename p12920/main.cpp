#include <iostream>
#include <vector>

using namespace std;

constexpr int MAX_N = 101;
constexpr int MAX_M = 10001;

int n, m;
int weight[MAX_N], value[MAX_N], amount[MAX_N];

int dynamic[MAX_M];

void input()
{
    cin >> n >> m;
    for(int i = 0; i < n; i++)
    {
        cin >> weight[i] >> value[i] >> amount[i];
    }
}

void process()
{
    vector<int> newWeight;
    vector<int> newValue;

    for(int i = 0; i < n; i++)
    {
        for(int j = 1; j < amount[i]; j *= 2)
        {
            newWeight.push_back(weight[i] * j);
            newValue.push_back(value[i] * j);
            amount[i] -= j;
        }
        if(amount[i] > 0)
        {
            newWeight.push_back(weight[i] * amount[i]);
            newValue.push_back(value[i] * amount[i]);
        }
    }

    for (int i = 0; i < newWeight.size(); i++)
    {
        for(int j = MAX_M; j >= newWeight[i]; j--)
        {
            if(dynamic[j-newWeight[i]] + newValue[i] > dynamic[j])
            {
                dynamic[j] = dynamic[j-newWeight[i]] + newValue[i];
            }
        }
    }
}

void output()
{
    cout << dynamic[m] << endl;
}

int main()
{
    input();
    process();
    output();

    return 0;
}