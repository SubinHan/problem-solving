#include <iostream>

using namespace std;

constexpr int MAX_NUM_GUITAR = 500;
constexpr int MAX_SERIAL_NUMBER = 100000;
constexpr int SLIDING_WINDOW_SIZE = 2;

int numTestCases;
int numGuitars, target;
int serial[MAX_NUM_GUITAR];
int dynamic[SLIDING_WINDOW_SIZE][MAX_SERIAL_NUMBER];

void input()
{
    scanf("%d %d", &numGuitars, &target);

    for(int i = 0; i < numGuitars; i++)
    {
        scanf("%d", &serial[i]);
    }
}

void swap(int& a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void init()
{
    for(int i = 0; i < SLIDING_WINDOW_SIZE; i++)
    {
        for(int j = 0; j < MAX_SERIAL_NUMBER; j++)
        {
            dynamic[i][j] = -1;
        }
    }
}

void process()
{
    init();

    int previous = 0;
    int current = 1;

    dynamic[previous][0] = 0;
    dynamic[previous][serial[0] % target] = 1;

    for(int i = 1; i < numGuitars; i++)
    {
        for(int j = 0; j < target; j++)
        {
            int modIfContain = (j + serial[i]) % target;

            if(dynamic[previous][j] == -1)
                continue;

            if(dynamic[current][modIfContain] <= dynamic[previous][j])
            {
                dynamic[current][modIfContain] = dynamic[previous][j] + 1;
            }
            if(dynamic[current][j] < dynamic[previous][j])
            {
                dynamic[current][j] = dynamic[previous][j];
            }
        }

        swap(previous, current);
    }
}

void output()
{
    printf("%d\n", max(dynamic[0][0], dynamic[1][0]));
}

int main()
{
    cin >> numTestCases;

    for (int i = 0; i < numTestCases; i++)
    {
        input();
        process();
        output();
    }

    return 0;
}