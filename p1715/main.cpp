#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    int numBunch;
    cin >> numBunch;
    priority_queue<int, vector<int>, greater<int>> bunches;

    for(int i = 0; i < numBunch; i++)
    {
        int numCards;
        cin >> numCards;
        bunches.push(numCards);
    }

    int answer = 0;
    
    while(bunches.size() > 1)
    {
        int first = bunches.top();
        bunches.pop();
        int second = bunches.top();
        bunches.pop();
        int sum = first + second;
        answer += sum;
        bunches.push(sum);
    }

    cout << answer << endl;

    return 0;
}