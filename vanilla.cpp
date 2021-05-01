#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Node
{

public:
    char ch;
    int parent;
    int next[26];
    int cached[26];
    int link;
    bool isLeaf;
    Node(char ch = '$', int parent = 0)
    {
        memset(this->next, -1, 26 * sizeof(int));
        memset(this->cached, -1, 26 * sizeof(int));
        this->ch = ch;
        this->parent = parent;
        this->isLeaf = false;
        this->link = -1;
    }
};

int getTransition(vector<Node> &trie, int currentNode, char ch);
int getFallback(vector<Node> &trie, int currentNode);

vector<Node> buildTrie(vector<string> patterns)
{
    vector<Node> result(1);
    Node root = Node();
    int indexToInsert = 1;
    result.emplace_back(root);

    for (string pattern : patterns)
    {
        int currentNode = 0;
        for (char ch : pattern)
        {
            int index = ch - 'a';
            if (result[currentNode].next[index] == -1)
            {
                Node newNode = Node(ch, currentNode);
                result[currentNode].next[index] = indexToInsert++;
                result.emplace_back(newNode);
            }
            currentNode = result[currentNode].next[index];
        }
        result[currentNode].isLeaf = true;
    }
    return result;
}

int getFallback(vector<Node> &trie, int currentNode)
{
    if (trie[currentNode].link == -1)
    {
        if (currentNode == 0 || trie[currentNode].parent == 0)
        {
            trie[currentNode].link = 0;
        }
        else
        {
            trie[currentNode].link = getTransition(trie, getFallback(trie, trie[currentNode].parent), trie[currentNode].ch);
        }
    }
    return trie[currentNode].link;
}

int getTransition(vector<Node> &trie, int currentNode, char ch)
{
    int index = ch - 'a';
    if (trie[currentNode].cached[index] == -1)
    {
        if (trie[currentNode].next[index] != -1)
        {
            trie[currentNode].cached[index] = trie[currentNode].next[index];
        }
        else if (currentNode == 0)
        {
            trie[currentNode].cached[index] = 0;
        }
        else
        {
            trie[currentNode].cached[index] = getTransition(trie, getFallback(trie, currentNode), ch);
        }
    }
    return trie[currentNode].cached[index];
}

void matchPattern(vector<Node> trie, string text)
{
    int currentNode = 0;
    for (char ch : text)
    {
        currentNode = getTransition(trie, currentNode, ch);
        cout << currentNode << endl;
        if (trie[currentNode].isLeaf)
        {
            // cout << currentNode << endl;
        }
    }
}

int main()
{

    string text = "gcatcg";
    vector<string> patterns = {"acc", "atc", "cat", "gcg"};

    vector<Node> trie = buildTrie(patterns);
    cout << "Trie build" << endl;
    matchPattern(trie, text);

    return 0;
}
