#include <iostream>

using namespace std;

constexpr int START = 0;
constexpr int END = 21;
constexpr int NUM_TRIALS = 10;
constexpr int NUM_PAWNS = 4;

int dices[NUM_TRIALS];
int pawns[NUM_PAWNS];

class Space
{
public:
    int index;
    Space* next = nullptr;
    Space* blueNext = nullptr;
    int score = 0;

public:
    bool canMove(int numMoves)
    {
        if(index == END)
            return false;

        Space* nextPos = next;

        if(nextPos->index == END)
            return true;

        if(blueNext)
        {
            nextPos = blueNext;
        }
        for(int i = 1; i < numMoves; i++)
        {
            nextPos = nextPos->next;
            if(nextPos->index == END)
                return true;
        }

        return !isTherePawn(nextPos->index);
    }
    
    int getMovedPos(int numMoves)
    {
        Space* nextPos = next;


        if(nextPos->index == END)
            return END;

        if(blueNext)
        {
            nextPos = blueNext;
        }
        for(int i = 1; i < numMoves; i++)
        {
            nextPos = nextPos->next;
            if(nextPos->index == END)
                return END;
        }

        return nextPos->index;
    }

private:
    bool isTherePawn(int index)
    {
        for(int i = 0; i < NUM_PAWNS; i++)
        {
            if(index == pawns[i])
                return true;
        }
        return false;
    }
};

Space board[35];

int score;
int maxScore = 0;

void makeBoard()
{
    for(int i = 0; i < 35; i++)
    {
        board[i].index = i;
    }

    for(int i = 0; i < 21; i++)
    {
        board[i].next = &board[i+1];
        board[i].score = i * 2;
    }

    board[5].blueNext = &board[22];    
    for(int i = 22; i < 25; i++)
    {
        board[i].next = &board[i+1];
        board[i].score = (i - 22) * 3 + 13;
    }

    board[25].score = 25;
    board[25].next = &board[31];

    board[15].blueNext = &board[26];
    for(int i = 26; i < 29; i++)
    {
        board[i].next = &board[i+1];
        board[i].score = 54 - i;
    }
    board[28].next = &board[25];

    board[10].blueNext = &board[29];
    board[29].score = 22;
    board[29].next = &board[30];
    board[30].score = 24;
    board[30].next = &board[25];

    board[31].next = &board[32];
    board[31].score = 30;
    board[32].next = &board[20];
    board[32].score = 35;
}

void input()
{
    makeBoard();
    for(int i = 0; i < NUM_TRIALS; i++)
    {
        cin >> dices[i];
    }
}

void move(int indexToMove, int numMoved)
{
    if(!board[pawns[indexToMove]].canMove(dices[numMoved]))
        return;

    int prevPos = pawns[indexToMove];
    int nextPos = board[pawns[indexToMove]].getMovedPos(dices[numMoved]);
    pawns[indexToMove] = nextPos;
    score += board[nextPos].score;

    if(numMoved == NUM_TRIALS - 1)
    {
        if(maxScore < score)
            maxScore = score;
        score -= board[nextPos].score;
        pawns[indexToMove] = prevPos;
        return;
    }   

    for(int i = 0; i < NUM_PAWNS; i++)
    {
        move(i, numMoved + 1);
    }
    score -= board[nextPos].score;
    pawns[indexToMove] = prevPos;
}

void process()
{
    move(0, 0);
}

void output()
{
    cout << maxScore << endl;
}

int main()
{
    input();
    process();
    output();

    return 0;
}