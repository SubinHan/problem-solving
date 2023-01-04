#include <iostream>
#include <vector>
#include <stack>

using namespace std;

constexpr int MAX_EXPRESSION_LENGTH = 19;
constexpr int MAX_NUMBERS_SIZE = MAX_EXPRESSION_LENGTH / 2 + 1;
constexpr int MAX_OPERATORS_SIZE = MAX_EXPRESSION_LENGTH / 2;
int numbers[MAX_NUMBERS_SIZE];
char operators[MAX_OPERATORS_SIZE];
bool isBound[MAX_OPERATORS_SIZE];

constexpr char PLUS = '+';
constexpr char MINUS = '-';
constexpr char TIMES = '*';

int maxResult = INT32_MIN;

struct Expression
{
    int length;
    int numbers[MAX_NUMBERS_SIZE];
    char operators[MAX_OPERATORS_SIZE];

    Expression(int length, int* numbers, char* operators)
    {
        this->length = length;
        for(int i = 0; i < length / 2 + 1; i++)
        {
            this->numbers[i] = numbers[i];
            this->operators[i] = operators[i];
        }
    }
};

vector<Expression> expressions;

int lengthOfExpression;

void input()
{
    scanf("%d\n", &lengthOfExpression);
    
    bool isNumber = true;
    
    for(int i = 0; i < lengthOfExpression; i++)
    {
        char c;
        scanf("%c", &c);
        if(isNumber)
        {
            numbers[i / 2] = c - '0';
        }
        else
        {
            operators[i / 2] = c;
        }
        isNumber = !isNumber;
    }
}

int perform(int a, char op, int b)
{
    if(op == TIMES)
    {
        return a * b;
    }
    if(op == PLUS)
    {
        return a + b;
    }
    if(op == MINUS)
    {
        return a - b;
    }
    return 0;
}

int perform(Expression expression)
{
    int numPointer = 0;
    int opPointer = 0;
    stack<int> numStack;
    stack<char> opStack;

    numStack.push(expression.numbers[numPointer++]);

    for(;numPointer + opPointer < expression.length - 1;)
    {
        char op = expression.operators[opPointer++];
        if(op == TIMES)
        {
            int front = numStack.top();
            numStack.pop();
            int back = expression.numbers[numPointer++];
            numStack.push(front * back);
            continue;
        }

        if(opStack.empty())
        {
            opStack.push(op);
            numStack.push(expression.numbers[numPointer++]);
            continue;
        }

        char prevOp = opStack.top();
        opStack.pop();
        int back = numStack.top();
        numStack.pop();
        int front = numStack.top();
        numStack.pop();
        numStack.push(perform(front, prevOp, back));

        opStack.push(op);
        numStack.push(expression.numbers[numPointer++]);
    }

    if(!opStack.empty())
    {
        char prevOp = opStack.top();
        opStack.pop();
        int back = numStack.top();
        numStack.pop();
        int front = numStack.top();
        numStack.pop();

        numStack.push(perform(front, prevOp, back));
    }

    return numStack.top();
}

void generateExpressions(Expression expression)
{
    int originOpIndex = 0;
    int currentOpIndex = 0;
    for(;originOpIndex < lengthOfExpression / 2;)
    {
        if(isBound[originOpIndex])
        {
            originOpIndex++;
            continue;
        }

        if(originOpIndex > 0 && isBound[originOpIndex - 1])
        {
            originOpIndex++;
            currentOpIndex++;
            continue;
        }
        if(originOpIndex < lengthOfExpression / 2 && isBound[originOpIndex + 1])
        {
            originOpIndex++;
            currentOpIndex++;
            continue;
        }
        
        int front = expression.numbers[currentOpIndex];
        int back = expression.numbers[currentOpIndex + 1];
        char op = expression.operators[currentOpIndex];
        int result = perform(front, op, back);

        int newNumbers[MAX_NUMBERS_SIZE];
        char newOperators[MAX_OPERATORS_SIZE];
        int newLength = expression.length - 2;
        int i = 0;
        for(; i < currentOpIndex; i++)
        {
            newNumbers[i] = expression.numbers[i];
            newOperators[i] = expression.operators[i];
        }
        newNumbers[i] = result;
        for(;i < newLength / 2; i++)
        {
            newOperators[i] = expression.operators[i+1];
            newNumbers[i+1] = expression.numbers[i+2];
        }
        
        isBound[originOpIndex] = true;
        Expression bound {newLength, newNumbers, newOperators};
        expressions.push_back(bound);
        generateExpressions(bound);
        isBound[originOpIndex] = false;

        originOpIndex++;
        currentOpIndex++;
    }
}

void process()
{
    Expression given{lengthOfExpression, numbers, operators};
    expressions.push_back(given);
    

    generateExpressions(given);

    for(auto iter = expressions.begin(); iter != expressions.end(); iter++)
    {
        int result = perform(*iter);
        if(maxResult < result)
            maxResult = result;
    }

}

void output()
{
    printf("%d", maxResult);
}

int main()
{
    input();
    process();
    output();

    return 0;
}