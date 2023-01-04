#include <iostream>

using namespace std;

constexpr int MAX_NUM_PLAYER = 16;

int numOfPlayers;
int guilty[MAX_NUM_PLAYER];
int guiltyMatrix[MAX_NUM_PLAYER][MAX_NUM_PLAYER];
int eunjin;

bool isDead[MAX_NUM_PLAYER];
int currentNumOfPlayer;

int result;

void input()
{
    cin >> numOfPlayers;
    for (int i = 0; i < numOfPlayers; i++)
    {
        cin >> guilty[i];
    }

    for (int i = 0; i < numOfPlayers; i++)
    {
        for (int j = 0; j < numOfPlayers; j++)
        {
            cin >> guiltyMatrix[i][j];
        }
    }
    cin >> eunjin;
    currentNumOfPlayer = numOfPlayers;
}

void kill(int number)
{
    isDead[number] = true;
    currentNumOfPlayer--;
}

void revive(int number)
{
    isDead[number] = false;
    currentNumOfPlayer++;
}

void killByMafia(int number)
{
    kill(number);

    for (int i = 0; i < numOfPlayers; i++)
    {
        guilty[i] += guiltyMatrix[number][i];
    }
}

void restoreKilledByMafia(int number)
{
    revive(number);

    for (int i = 0; i < numOfPlayers; i++)
    {
        guilty[i] -= guiltyMatrix[number][i];
    }
}

void killByCivilians(int number)
{
    kill(number);
}

void restoredKilledByCivilians(int number)
{
    revive(number);
}


bool isNight(int currentNumberOfPlayers)
{
    return currentNumberOfPlayers % 2 == 0;
}

int findMostGuilty()
{
    int maxIndex = -1;
    int max = -1000;
    for (int i = 0; i < numOfPlayers; i++)
    {
        if (isDead[i])
            continue;

        if (guilty[i] > max)
        {
            max = guilty[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}

int simulate()
{
    int numOfNights = ((numOfPlayers / 2 * 2 + 1) - currentNumOfPlayer) / 2;

    if (isDead[eunjin])
    {
        return numOfNights;
    }

    if (currentNumOfPlayer == 1)
    {
        return numOfNights;
    }

    if (isNight(currentNumOfPlayer))
    {
        int max = -1000;
        for(int i = 0; i < numOfPlayers; i++)
        {
            if(isDead[i])
                continue;
            if(i == eunjin)
                continue;
            killByMafia(i);
            int result = simulate();
            restoreKilledByMafia(i);
            if(max < result)
                max = result;
        }
        return max;
        
    }
    else
    {
        int target = findMostGuilty();
        killByCivilians(target);
        int result = simulate();
        restoredKilledByCivilians(target);
        return result;
    }
}

void process()
{
    result = simulate();
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

    return 0;
}