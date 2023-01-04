#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_CUT_NUM = 10001;
constexpr int TRIALS = 100;

int l, k, c;
int cut[MAX_CUT_NUM];
int result;
int resultIndex;

void input()
{
    cin >> l >> k >> c;
    for (int i = 0; i < k; i++)
    {
        cin >> cut[i];
    }
}

int findCutIndex(int targetCutLength, int remainLogLength)
{
    bool isFound = false;

    for(int i = k - 1; i >= 0; i--)
    {
        if(cut[i] > remainLogLength)
            continue;
        
        int cutLogLength = remainLogLength - cut[i];

        if(cutLogLength <= targetCutLength)
            isFound = true;
            
        if(cutLogLength > targetCutLength)
            if(isFound)
                return i + 1;
            else
                return -1;
    }

    return 0;
}

void process()
{
    sort(cut, cut + k);

    int low = l / (max(k, c) + 1);
    int high = l;
    int mid;
    int smallestFirstCut = l;

    while (low <= high)
    {
        mid = (low + high) / 2;
        bool isCutable = true;

        int lastCut = l;
        for (int j = 0; j < min(k, c); j++)
        {
            int cutIndex = findCutIndex(mid, lastCut);
            if (cutIndex == -1)
            {
                isCutable = false;
                break;
            }
            lastCut = cut[cutIndex];

            if (cutIndex == 0)
                break;
            
        }

        if(lastCut > mid)
            isCutable = false;

        if(isCutable)
        {
            result = mid;
            resultIndex = lastCut;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

}

void output()
{
    cout << result << " " << resultIndex << endl;
}

int main()
{
    input();
    process();
    output();

    cin >> k;

    return 0;
}