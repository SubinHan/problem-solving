#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string expression;
int answer;

vector<string> split(string input, char delimeter)
{
    vector<string> result;
    stringstream ss(input);
    string splitted;
    while (getline(ss, splitted, delimeter))
        result.push_back(splitted);

    return result;
}

vector<string> split2(string input, char delimeter)
{
    vector<string> result;

    int start{0};
    int end{0};
    
    end = input.find(delimeter);
    // find() returns string::npos if cannot find the given character.
    while (end != string::npos) 
    {
        // string.substr(index, length);
        string splitted = input.substr(start, end - start);
        result.push_back(splitted);
        start = end + 1;
        end = input.find(delimeter, start);
    }
    result.push_back(input.substr(start, input.size() - start));

    return result;
}

int computeAddition(string expression)
{
    int result{0};

    vector<string> terms = split2(expression, '+');
    for (string each : terms)
    {
        result += stoi(each);
    }

    return result;
}

int main()
{
    cin >> expression;

    vector<string> subtractionTerms = split2(expression, '-');

    answer = computeAddition(subtractionTerms[0]);

    for (auto iter = subtractionTerms.begin() + 1; iter < subtractionTerms.end(); iter++)
    {
        answer -= computeAddition(*iter);
    }

    cout << answer << endl;

    return 0;
}