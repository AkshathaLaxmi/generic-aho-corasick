#include <iostream>
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Node
{
public:
    T value;
    int parent;
    map<T, int> next;
    map<T, int> cached;
    int link;
    bool isPattern;

    Node()
    {
        this->parent = 0;
        this->isPattern = false;
        this->link = -1;
    }

    Node(T value, int parent = 0)
    {
        this->value = value;
        this->parent = parent;
        this->isPattern = false;
        this->link = -1;
    }
};

template <typename T, typename V>
class AhoCorasick
{
    vector<Node<V>> trie;
    vector<T> patterns;

    void BuildTrie()
    {
        Node<V> root = Node<V>();
        this->trie.push_back(root);

        for (T pattern : this->patterns)
        {
            int currentNode = 0;
            for (V value : pattern)
            {
                if (this->trie[currentNode].next.find(value) == this->trie[currentNode].next.end())
                {
                    this->trie[currentNode].next[value] = this->trie.size();
                    this->trie.emplace_back(value, currentNode);
                }
                currentNode = this->trie[currentNode].next[value];
            }
            this->trie[currentNode].isPattern = true;
        }
    }

    int getFallback(int currentNode)
    {
        if (this->trie[currentNode].link == -1)
        {
            if (currentNode == 0 || this->trie[currentNode].parent == 0)
            {
                this->trie[currentNode].link = 0;
            }
            else
            {
                this->trie[currentNode].link = this->getTransition(this->getFallback(this->trie[currentNode].parent), this->trie[currentNode].value);
            }
        }
        return this->trie[currentNode].link;
    }

    int getTransition(int currentNode, V value)
    {
        if (this->trie[currentNode].cached.find(value) == this->trie[currentNode].cached.end())
        {
            if (this->trie[currentNode].next.find(value) != this->trie[currentNode].next.end())
            {
                this->trie[currentNode].cached[value] = this->trie[currentNode].next[value];
            }
            else if (currentNode == 0)
            {
                trie[currentNode].cached[value] = 0;
            }
            else
            {
                trie[currentNode].cached[value] = this->getTransition(this->getFallback(currentNode), value);
            }
        }
        return this->trie[currentNode].cached[value];
    }

public:
    void MatchPattern(T sequence)
    {
        int currentNode = 0;
        for (V value : sequence)
        {
            currentNode = this->getTransition(currentNode, value);
            if (this->trie[currentNode].isPattern)
            {
                cout << currentNode << endl;
            }
        }
    }

    AhoCorasick(vector<T> patterns)
    {
        this->patterns = patterns;
        this->BuildTrie();
    }
};

int main()
{

    vector<vector<int>> text = {{2, 3, 4}, {5, 7, 3}, {4, 5, 2}, {100, 44, 56}, {5, 7, 3}, {2, 3, 4}};
    vector<vector<vector<int>>> patterns = {{{4, 5, 2}, {5, 7, 3}, {5, 7, 3}}, {{4, 5, 2}, {100, 44, 56}, {5, 7, 3}}, {{5, 7, 3}, {4, 5, 2}, {100, 44, 56}}, {{2, 3, 4}, {5, 7, 3}, {2, 3, 4}}};
    AhoCorasick<vector<vector<int>>, vector<int>> search = AhoCorasick<vector<vector<int>>, vector<int>>(patterns);
    search.MatchPattern(text);
    return 0;
}
