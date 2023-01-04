#include <iostream>
#include <string>

using namespace std;

constexpr int MAX_NUM = 1000;
constexpr int NUM_CHAR = 26;
constexpr int MAX_LENGTH = 15;

int numOfInput;

class TrieNode
{
private:
    bool finish;
    TrieNode *node[NUM_CHAR];
    TrieNode *room;

public:
    TrieNode()
    {
        for (int i = 0; i < NUM_CHAR; i++)
        {
            node[i] = nullptr;
            room = nullptr;
        }
    }

    TrieNode *insert(char *s)
    {
        if (*s == '\0')
        {
            if(room == nullptr)
            {
                room = new TrieNode();
            }
            return room;
        }

        int current = *s - 'A';
        if (node[current] == nullptr)
            node[current] = new TrieNode();
        return node[current]->insert(s + 1);
    }

    void print(int level, string before)
    {
        if (room)
        {
            for (int j = 0; j < level; j++)
            {
                printf("--");
            }
            printf("%s\n", before.c_str());
            room->print(level + 1, "");
        }

        for (int i = 0; i < NUM_CHAR; i++)
        {
            if (node[i] == nullptr)
                continue;

            string cur = before + (char)('A' + i);

            node[i]->print(level, cur);
        }
    }
};

TrieNode root;

void input()
{
    scanf("%d", &numOfInput);
    for (int i = 0; i < numOfInput; i++)
    {
        int level;
        scanf("%d", &level);
        TrieNode *before = &root;
        for (int j = 0; j < level; j++)
        {
            char s[MAX_LENGTH + 1];
            scanf("%s", s);

            before = before->insert(s);
        }
    }
}

void output()
{
    root.print(0, "");
}

int main()
{
    input();
    output();

    return 0;
}