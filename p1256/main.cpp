#include <iostream>

using namespace std;

int n, m, k;
string result;

void input()
{
    cin >> n >> m >> k;
}

long long calculatePerm(int numA, int numZ)
{
    if (numA + numZ <= 0)
        return 1;

    long long result = 1;
    int under = min(numA, numZ);

    for (int i = numA + numZ; i > max(numA, numZ); i--)
    {
        result *= i;
        while (true)
        {
            if (under == 0)
                break;
            if (result % under == 0)
                result /= under--;
            else
                break;
        }

        if (result > 100000000000000)
            return result;
    }

    return result;
}

string find(int n, int m, int k)
{
    if(n == 0 && m == 0)
        return "";

    if (n > 0)
    {
        long long perm = calculatePerm(n - 1, m);
        if (k > perm)
        {
            return "z" + find(n, m - 1, k - perm);
        }
        else
        {
            return "a" + find(n - 1, m, k);
        }
    }
    else
    {
        long long perm = calculatePerm(n, m - 1);
        return "z" + find(n, m - 1, k - perm);
    }
}

void process()
{
    if (calculatePerm(n, m) < k)
    {
        result = "-1";
        return;
    }

    result = find(n, m, k);
}

void output()
{
    cout << result << endl;
}

int main()
{
    input();
    process();
    output();
    cin >> n;
}


// for seminar

void swap(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void perm(int *set, int n, int k, int depth)
{
    if(depth == k)
    {
        for(int i = 0; i < k; i++)
        {
            cout << set[i];
        }
        cout << endl;

        return;
    }

    for(int i = depth; i < n; i++)
    {
        swap(set[depth], set[i]);
        perm(set, n, k, depth + 1);
        swap(set[depth], set[i]);
    }
}

void perm(int n, int k)
{
    int *set = new int[n];
    for (int i = 0; i < n; i++)
    {
        set[i] = i + 1;
    }

    perm(set, n, k, 0);

    delete set;
}

// int main()
// {
//     int a;
//     perm(4, 3);
//     cin >> a;
// }