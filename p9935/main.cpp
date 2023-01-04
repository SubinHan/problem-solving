#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main()
{
    string str, bomb;
    cin >> str >> bomb;
    
    stack<char> s;
    for (char c : str)
    {
        s.push(c);
        if(s.size() < bomb.size())
            continue;

        stack<char> popped;
        for(int i = 0; i < bomb.size(); i++)
        {
            popped.push(s.top());
            s.pop();
            
            if(popped.top() != bomb[bomb.size() - i - 1])
            {
                while(!popped.empty())
                {
                    s.push(popped.top());
                    popped.pop();
                }
                break;
            }
        }     
    }

    if(s.empty())
    {
        cout << "FRULA" << endl;
        return 0;
    }

    stack<char> reversed;
    while(!s.empty())
    {
        reversed.push(s.top());
        s.pop();
    }

    while(!reversed.empty())
    {
        cout << reversed.top();
        reversed.pop();
    }

    cout << endl;
    return 0;
}
    
