#include <iostream>
#include <string>

using namespace std;

constexpr int MAX_LENGTH = 1'000'000;

int kmp[MAX_LENGTH];
string text;
string pattern;

int resultCount;
int result[MAX_LENGTH];

void input()
{
    getline(cin, text);
    getline(cin, pattern);
}

void init()
{
    kmp[0] = -1;

    int pos = 1; 
    int candidate = 0;
    for(; pos < pattern.size();)
    {
        if(pattern[pos] == pattern[candidate])
            kmp[pos] = kmp[candidate];
        else
        {
            kmp[pos] = candidate;
            while(candidate >= 0 && pattern[pos] != pattern[candidate])
            {
                candidate = kmp[candidate];
            }
        }
        candidate++;
        pos++;
    }
    
    kmp[pos] = candidate;
}

void search()
{
    for(int i = 0, j = 0; i < text.size();)
    {
        if(pattern[j] == text[i])
        {
            i++;
            j++;
            if(j == pattern.size())
            {
                result[resultCount++] = i - j + 1;
                j = kmp[j];
            }
        }
        else
        {
            j = kmp[j];
            if(j < 0)
            {
                i++;
                j++;
            }
        }
    }
}

void process()
{
    init();
    search();
}

void output()
{
    printf("%d\n", resultCount);
    for(int i = 0; i < resultCount; i++)
    {
        printf("%d\n", result[i]);
    }
}

int main()
{
    input();
    process();
    output();

    return 0;
}