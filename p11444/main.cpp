#include <iostream>

using namespace std;

class Matrix2D
{
private:
    static constexpr int SIZE = 2;
    static constexpr long long REMAINDER = 1'000'000'007;

public:
    long long matrix[SIZE][SIZE];

    Matrix2D(long long a00, long long a01, long long a10, long long a11)
    {
        matrix[0][0] = a00 % REMAINDER;
        matrix[0][1] = a01 % REMAINDER;
        matrix[1][0] = a10 % REMAINDER;
        matrix[1][1] = a11 % REMAINDER;
    }

    Matrix2D operator* (const Matrix2D& mat)
    {
        long long a00;
        long long a01;
        long long a10;
        long long a11;

        a00 = matrix[0][0] * mat.matrix[0][0] + matrix[0][1] * mat.matrix[1][0];
        a01 = matrix[0][0] * mat.matrix[0][1] + matrix[0][1] * mat.matrix[1][1];
        a10 = matrix[1][0] * mat.matrix[0][0] + matrix[1][1] * mat.matrix[1][0];
        a11 = matrix[1][0] * mat.matrix[0][1] + matrix[1][1] * mat.matrix[1][1];

        return Matrix2D(a00, a01, a10, a11);
    }

    Matrix2D pow(long long num)
    {
        if(num == 0)
            return Matrix2D(1, 0, 0, 1);
        if(num == 1)
            return *this;

        Matrix2D powered = pow(num/2);
        if(num % 2 == 0)
        {
            return powered * powered;
        }
        else
        {
            return powered * powered * *this;
        }
    }
};

long long n;
long long result;

void input()
{
    cin >> n;
}

void process()
{
    result = Matrix2D(1, 1, 1, 0).pow(n-1).matrix[0][0];
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

//O(n) 예시

// int fibonacci(int n)
// {
//     if(n <= 0)
//         return 0;
//     if(n == 1)
//         return 1;
//     return fibonacci(n-1) + fibonacci(n-2);
// }

// int fibonacci(int n)
// {
//     return fibonacci(n, 1, 0);
// }

// int fibonacci(int n, int prevFibo, int prevPrevFibo)
// {
//     if(n < 2)
//         return prevFibo;

//     return fibonacci(n-1, prevFibo + prevPrevFibo, prevFibo);
// }

// int fibonacci(int n)
// {
//     int prev = 1;
//     int prevPrev = 0;
//     for(int i = 0; i < n; i++)
//     {
//         int temp = prev;
//         prev = prev + prevPrev;
//         prevPrev = temp;
//     }

//     return prev;
// }

// int memo[100];

// int fibonacci(int n)
// {
//     if(n == 0)
//         return memo[0];

//     int f = memo[n];
//     if(f == 0)
//     {
//         f = fibonacci(n-1) + fibonacci(n-2);
//         memo[n] = f;
//     }
//     return f;
// }

// 제곱 O(log n)
// int pow(int base, int ex)
// {
//     if(ex == 0)
//         return 1;

//     int powered = pow(base, ex/2);
//     if(ex % 2 == 0)
//     {
//         return powered * powered;
//     }
//     else
//     {
//         return powered * powered * base;
//     }
// }