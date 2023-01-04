#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_NUM_QUESTIONS = 1000;

int numOfQuestions;
int numOfCategories;
int numOfAnswers;
int bonus;

int countQuestionsInCategory[MAX_NUM_QUESTIONS];

struct question
{
    int point;
    int category;
};

bool comparator(question a, question b)
{
    if (a.category == b.category)
    {
        return a.point > b.point;
    }
    return a.category < b.category;
}

question questions[MAX_NUM_QUESTIONS];

int dynamic[MAX_NUM_QUESTIONS + 1];

void input()
{
    cin >> numOfQuestions >> numOfCategories >> numOfAnswers >> bonus;

    for (int i = 0; i < numOfQuestions; i++)
    {
        scanf("%d %d", &questions[i].point, &questions[i].category);
        countQuestionsInCategory[questions[i].category]++;
    }
}

void process()
{
    sort(questions, questions + numOfQuestions, comparator);

    int startIndex = 0;
    for (int i = 1; i <= numOfCategories; i++)
    {
        for (int j = numOfAnswers; j > 0; j--)
        {
            int sumPoints = 0;
            for (int k = 1; k <= min(j, countQuestionsInCategory[i]); k++)
            {
                sumPoints += questions[startIndex + k - 1].point;
                if (dynamic[j] < dynamic[j - k] + sumPoints)
                {
                    dynamic[j] = dynamic[j - k] + sumPoints;
                }
            }

            if (j >= countQuestionsInCategory[i])
            {
                if (dynamic[j] < dynamic[j - countQuestionsInCategory[i]] + sumPoints + bonus)
                    dynamic[j] = dynamic[j - countQuestionsInCategory[i]] + sumPoints + bonus;
            }
        }
        startIndex += countQuestionsInCategory[i];
    }
}

void output()
{
    cout << dynamic[numOfAnswers] << endl;
}

int main()
{
    input();
    process();
    output();

    return 0;
}