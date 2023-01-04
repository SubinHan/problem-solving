#include <iostream>
#include <string>

using namespace std;

constexpr int MAX_LENGTH = 1'000'000;
constexpr int SPACE = 52;
constexpr int NUM_CHAR = 53;

int dfa[NUM_CHAR][MAX_LENGTH + 1];
string text;
string pattern;

int resultCount;
int result[MAX_LENGTH + 1];

void input()
{
    getline(cin, text);
    getline(cin, pattern);
}

int convertToNumber(char c)
{
    if(c == ' ')
        return SPACE;

    if(c <= 'Z')
        return c - 'A';
    
    return c - 'a' + 26;
}

void init()
{
    dfa[convertToNumber(pattern[0])][0] = 1;
    int i = 0, j = 1;
    for(; j < pattern.length(); j++)
    {
        for(int c = 0; c < NUM_CHAR; c++)
        {
            dfa[c][j] = dfa[c][i];
        }
        dfa[convertToNumber(pattern[j])][j] = j + 1;
        i = dfa[convertToNumber(pattern[j])][i];
    }
    for(int c = 0; c < NUM_CHAR; c++)
    {
        dfa[c][pattern.length()] = dfa[c][i];
    }

}

void search()
{
    int i = 0, j = 0;
    for(; i < text.length(); i++)
    {
        j = dfa[convertToNumber(text[i])][j];
        if(j == pattern.length())
        {
            result[resultCount++] = i - pattern.length() + 2;
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