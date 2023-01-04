#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define MAX_DIGIT 52
#define MAX_N 50
#define BASE 36

class BigNumber {
private:
    int digit[MAX_DIGIT];
    int numDigit;

public:
    BigNumber()
    {
        for(int i = 0; i < MAX_DIGIT; i++)
        {
            digit[i] = 0;
        }
        numDigit = 0;
    }

    BigNumber(string number) : BigNumber()
    {
        numDigit = number.size();

        for(int i = 0; i < number.size(); i++)
        {
            digit[numDigit - i - 1] = toInt(number[i]);
        }
    }

    BigNumber(BigNumber &number) : BigNumber()
    {
        copy(&number.digit[0], &number.digit[0] + MAX_DIGIT, &digit[0]);
        numDigit = number.numDigit;
    }

    BigNumber& operator=(const BigNumber& number)
    {
        copy(&number.digit[0], &number.digit[0] + MAX_DIGIT, &digit[0]);
        numDigit = number.numDigit;

        return *this;
    }

    BigNumber operator+(const BigNumber &number)
    {
        BigNumber result(*this);
        for(int i = 0; i < number.numDigit; i++)
        {
            result.digit[i] += number.digit[i];
        }

        result.correct();
        
        return result;
    }

    bool operator>(const BigNumber &number)
    {
        if(numDigit > number.numDigit)
            return true;
        
        if(numDigit < number.numDigit)
            return false;

        int i;
        for(i = numDigit-1; i > 0; i--)
        {
            if(digit[i] != number.digit[i])
                break;
        }
        
        if(digit[i] > number.digit[i])
            return true;
        return false;
    }

    bool operator<(const BigNumber &number)
    {
        if(numDigit < number.numDigit)
            return true;
        
        if(numDigit > number.numDigit)
            return false;

        int i;
        for(i = numDigit-1; i > 0; i--)
        {
            if(digit[i] != number.digit[i])
                break;
        }
        
        if(digit[i] < number.digit[i])
            return true;
        return false;
    }

    static BigNumber sum(BigNumber numbers[], int arraySize)
    {
        BigNumber result;

        for(int i = 0; i < arraySize; i++)
        {
            result = result + numbers[i];
        }

        return result;
    }

    void add(int pos, int num)
    {
        digit[pos] += num;
        correct();
    }

    string toString()
    {
        string result;
        if(numDigit == 0)
            return "0";

        for(int i = 0; i < numDigit; i++)
        {
            result = toChar(digit[i]) + result;
        }
        return result;
    }

    static int toInt(char c)
    {
        if(isLowerThanTen(c))
        {
           return c - '0';
        }
        return c - 'A' + 10;
    }
    
    static char toChar(int n)
    {
        if(n < 10)
        {
            return n + '0';
        }
        return n + 'A' - 10;
    }
private:
    static bool isLowerThanTen(char c)
    {
        if('0' <= c && c <= '9')
            return true;
        return false;
    }
    void correct()
    {
        for(int i = 0; i < MAX_DIGIT-1; i++)
        {
            if(digit[i] >= BASE)
            {
                int carry = digit[i] / BASE;
                digit[i] = digit[i] % BASE;
                digit[i+1] += carry;
            }
        }

        for(int i = MAX_DIGIT-1; i >= 0; i--)
        {
            if(digit[i] > 0)
            {
                numDigit = i+1;
                break;
            }
        }
    }
};

int n;
string nums[MAX_N];
int k;
string result;

void input()
{
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    cin >> k;
}

void convertToZ(int num)
{
    char target = BigNumber::toChar(num);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < nums[i].size(); j++)
        {
            if(nums[i][j] == target)
                replace(nums[i].begin(), nums[i].end(), target, 'Z');
        }
    }
}

void process()
{
    BigNumber freq[BASE];

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < nums[i].size(); j++)
        {
            int given = BigNumber::toInt(nums[i][j]);
            freq[given].add(nums[i].size() - j - 1, 35-given);
        }
    }

    for(int i = 0; i < k; i++)
    { 
        BigNumber* max = &freq[0];
        int maxIndex = 0;
        for(int j = 1; j < BASE; j++)
        {
            if(*max < freq[j])
            {
                max = &freq[j];
                maxIndex = j;
            }
        }
        convertToZ(maxIndex);
        *max = BigNumber();        
    }

    BigNumber* numbers = new BigNumber[n];
    for(int i = 0; i < n; i++)
    {
        numbers[i] = BigNumber(nums[i]);
    }

    result = BigNumber::sum(numbers, n).toString();
    delete numbers;
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
}