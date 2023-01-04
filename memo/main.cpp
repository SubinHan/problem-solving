#include <iostream>

using namespace std;

int solution(int n, int multi, int add, int p)
{
    
    if(n < 1)
        return 0;
    
    if(multi == 0)
    {        
        if(add == 0 && n == 1)
            return 1;
        return 0;
    }
    
    int result = 0;
    if(multi > 0)
    {
        for(int i = max(0, 2 - p); i <= add; i++)
        {
            if((n - i) % 3 == 0)
            {
                result += solution((n - i) / 3, multi - 1, add - i, (i + p) - 2);
            }
        }
        
    }
    
    return result;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n) {
    int count = 0;
    for(int i = 3; i < n; i *= 3)
    {
        count++;
    }
    
    return solution(n, count, count * 2, 0);
}

int main()
{
    cout << solution(15);

    return 0;
}