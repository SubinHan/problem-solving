#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_NUM_HIKERS = 1000;
constexpr int MAX_POLLUTION = 3100;

int numOfHikers;

struct hiker
{
    int pollution;
    int threshold;
};

bool comparator(hiker a, hiker b)
{
    return a.pollution + a.threshold < b.pollution + b.threshold;
}

hiker hikers[MAX_NUM_HIKERS];
int dynamic[MAX_POLLUTION + 1];
int resultDrunken;
int resultPollution;

void input()
{
    cin >> numOfHikers;  
    for (int i = 0; i < numOfHikers; i++)
    {
        scanf("%d %d", &hikers[i].pollution, &hikers[i].threshold);
    }

}

void process()
{
    sort(hikers, hikers + numOfHikers, comparator);

    for (int i = 0; i < numOfHikers; i++)
    {
        for (int j = MAX_POLLUTION; j >= hikers[i].pollution; j--)
        {
            if (hikers[i].threshold <= j - hikers[i].pollution)
                continue;
            if (dynamic[j] < dynamic[j - hikers[i].pollution] + 1)
            {
                dynamic[j] = dynamic[j - hikers[i].pollution] + 1;
            }
        }
    }

    int max = 0;
    int minPollution = 0;
    for (int i = 1; i < MAX_POLLUTION; i++)
    {
        if (dynamic[i] > max)
        {
            max = dynamic[i];
            minPollution = i;
        }
    }
    resultDrunken = max;
    resultPollution = minPollution;
}

void output()
{
    cout << resultDrunken << " " << resultPollution << endl;
}

int main()
{
    input();
    process();
    output();

    return 0;
}