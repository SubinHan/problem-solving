#include <iostream>
#include <string>
#include <cmath>

using namespace std;

constexpr int DIGIT = 10;

string number;
long long result[DIGIT];

void input()
{
    cin >> number;
}

int charToInt(char c)
{
    return c - '0';
}

int strToInt(string s)
{
    int result = 0;
    int pow = 1;

    for (int i = s.length() - 1; i >= 0; i--)
    {
        result += pow * charToInt(s[i]);
        pow *= DIGIT;
    }

    return result;
}

void process()
{
    for (int i = 0; i < number.length(); i++)
    {
        char currentDigitChar = number[i];
        int currentDigitInt = charToInt(currentDigitChar);

        string front = number.substr(0, i);
        string back = number.substr(i + 1);

        if (strToInt(front) != 0)
        {
            if (currentDigitInt == 0)
            {
                result[0] += (strToInt(front) - 1) * pow(DIGIT, back.length()) + strToInt(back) + 1;
            }
            else
            {
                result[0] += (strToInt(front)) * pow(DIGIT, back.length());
            }
        }

        for (int j = 1; j < DIGIT; j++)
        {
            if (j < currentDigitInt)
            {
                result[j] += (strToInt(front) + 1) * pow(DIGIT, back.length());
            }
            else if (j == currentDigitInt)
            {
                result[j] += strToInt(front) * pow(DIGIT, back.length()) + strToInt(back) + 1;
            }
            else
            {
                int frontNum = strToInt(front);
                if (frontNum == 0)
                    continue;
                result[j] += (strToInt(front)) * pow(DIGIT, back.length());
            }
        }
    }
}

void output()
{
    for (int i = 0; i < DIGIT; i++)
    {
        printf("%lld ", result[i]);
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