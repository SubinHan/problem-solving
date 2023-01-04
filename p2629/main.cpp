#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int MAX_NUM_OF_WEIGHTS = 31;
constexpr int MAX_TARGET_WEIGHT = 40501;
constexpr int MAX_MEASURABLE_WEIGHT = 15000;
constexpr int MAX_NUM_OF_MARBLES = 8;

int numOfWeights;
int weights[MAX_NUM_OF_WEIGHTS];
int numOfMarbles;
int marbles[MAX_NUM_OF_MARBLES];

bool dynamic[MAX_TARGET_WEIGHT];

void input()
{
    scanf("%d", &numOfWeights);
    for(int i = 0; i < numOfWeights; i++)
    {
        scanf("%d", &weights[i]);
    }   

    scanf("%d", &numOfMarbles);
    for(int i = 0; i < numOfMarbles; i++)
    {
        scanf("%d", &marbles[i]);
    }
}

void process()
{
    dynamic[0] = true;
    int maxTarget = 0;
    for(int i = 0; i < numOfMarbles; i++)
    {
        maxTarget = max(marbles[i], maxTarget);
    }

    for(int i = 0; i < numOfWeights; i++)
    {
        vector<int> clone;
        for(int j = 0; j <= MAX_MEASURABLE_WEIGHT; j++)
        {
            if(dynamic[j])
                clone.push_back(j);
        }

        for(vector<int>::iterator iter = clone.begin(); iter != clone.end(); iter++)
        {
            dynamic[*iter + weights[i]] = true;
            dynamic[abs(*iter - weights[i])] = true;
        }
    }

}

void output()
{
    for(int i = 0; i < numOfMarbles; i++)
    {
        if(dynamic[marbles[i]])
        {
            printf("Y ");
        }
        else
        {
            printf("N ");
        }
    }
    printf("\n");
}

int main()
{
    input();
    process();
    output();

    return 0;
}