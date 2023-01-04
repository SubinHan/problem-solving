#include <iostream>

using namespace std;

int n, m;
int result;

int euclid(int p, int q)
{
    if(p % q == 0)
        return q;
    else return euclid(q, p % q);
}

void input()
{
    result = 0;
    cin >> n >> m;
}

void process()
{
    result = m - euclid(n, m);
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

/*
[1] 케이크를 단순히 분배하는 방법: n개의 케이크를 각각 m개씩 나눈다!
그렇다면 n*(m-1)번의 칼질으로 분배할 수 있음

하지만 이는 비효율적..

다시 생각해보자:
n개의 케이크가 쭉 늘어서 있다고 생각해보자. 케이크는 잘려있지 않고, 길쭉한 n의 길이의 케이크이다.
이를 m명에게 분배하려면, m개의 조각으로 나누어야 할 것이다.
즉, m-1번 칼질을 해야 한다.

하지만 실제로는, 길쭉한 케이크는 n등분 되어있다.
만약 m개로 나누는 과정에서, n등분 되어있는 부분과 일치하는 부분에 칼질을 해야한다면
이는 칼질을 아낄 수 있다.
이는 곧, n과 m의 최대공약수에 따라 결정된다.
(같은 길이의 케이크를 n등분, m등분 할 때 겹치는 곳)

따라서 m - gcd(n,m) 회만큼 칼질을 하게 된다..
*/