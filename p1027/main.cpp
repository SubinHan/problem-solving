#include <iostream>

using namespace std;

#define MAX_NUMBER 50

int n;
long long h[MAX_NUMBER];
int result;

void input()
{
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> h[i];
    }
    result = 0;
}

int calculateVisibleLeft(long long h[], int index)
{
    int count = 0;
    for(int i = 0; i < index; i++)
    {
        count++;
        for(int j = i+1; j < index; j++)
        {
            if((h[index]-h[i])*(index-j) >= (h[index]-h[j])*(index-i))
            {
                count--;
                break;
            }    
        }
    }

    return count;
}

int calculateVisibleRight(long long h[], int index, int size)
{
    int count = 0;
    for(int i = size-1; i > index; i--)
    {
        count++;
        for(int j = i-1; j > index; j--)
        {
            if((h[index]-h[i])*(index-j) <= (h[index]-h[j])*(index-i))
            {
                count--;
                break;
            }    
        }
    }

    return count;
}
int calculateVisible(long long h[], int size, int index)
{
    int left = 0;
    int right = 0;

    if(index > 0)
    {
        left = calculateVisibleLeft(h, index);
    }
    if(index < size - 1)
    {
        right = calculateVisibleRight(h, index, size);
    }

    return left + right;
}

void process()
{
    for(int i = 0; i <n; i++)
    {
        int visible = calculateVisible(h, n, i);
        if(result < visible)
            result = visible;
    }
}

void output()
{
    cout << result;
}

int main()
{
    input();
    process();
    output();
    cin >> n;
}