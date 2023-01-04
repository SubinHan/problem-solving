#include <iostream>

using namespace std;

constexpr int MAX_NUM_JEWELS = 100'000;
constexpr int MAX_VALUE_JEWELS = 2000;
constexpr int TRIALS = 50;
constexpr double ROUND = 0.00005;

int n, m;
int jewels[MAX_NUM_JEWELS];

int result;

void input()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> jewels[i];
    }
}

void process()
{
    double low = 0.0;
    double high = MAX_VALUE_JEWELS;
    double target;

    for (int t = 0; t < TRIALS; t++)
    {
        double accumulate = 0.0;
        double backAccumulate = 0.0;
        double min = MAX_VALUE_JEWELS;
        int minIndex = MAX_NUM_JEWELS + 1;
        target = (low + high) / 2;
        for (int i = 0; i < m - 1; i++)
        {
            double diff = target - jewels[i];
            accumulate += diff;
        }

        bool found = false;
        for (int i = m - 1; i < n; i++)
        {
            double diff = target - jewels[i];
            accumulate += diff;

            double backDiff = target - jewels[i - m + 1];
            backAccumulate += backDiff;

            if (min > backDiff - backAccumulate)
            {
                min = backDiff - backAccumulate;
            }

            if (accumulate + min < 0)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            low = target;
        }
        else
        {
            high = target;
        }
    }

    result = (target + ROUND) * 1000;
}

void output()
{
    cout << result << endl;
}

int main()
{
    input();
    process();
    output();

    return 0;
}