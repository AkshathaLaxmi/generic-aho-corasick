#ifndef _AHO_CORASICK_H_
#define _AHO_CORASICK_H_

#include "aho_corasick_node.hpp"
#include <iostream>
#include <vector>
#include <map>

template <typename T, typename V>
class AhoCorasick
{
    vector<Node<V>> trie;
    vector<T> patterns;

    void BuildTrie();
    int getFallback(int currentNode);
    int getTransition(int currentNode, V value);

public:
    map<typename T::iterator, vector<T>> MatchPattern(T &sequence);
    AhoCorasick(vector<T> patterns);
};

template <typename T, typename V>
void AhoCorasick<T, V>::BuildTrie()
{
    Node<V> root = Node<V>();
    this->trie.push_back(root);

    int patternSize = this->patterns.size();
    for (int patternIndex = 0; patternIndex < patternSize; ++patternIndex)
    {
        T pattern = this->patterns[patternIndex];
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
        this->trie[currentNode].patternIndex = patternIndex;
    }
}

template <typename T, typename V>
int AhoCorasick<T, V>::getFallback(int currentNode)
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

template <typename T, typename V>
int AhoCorasick<T, V>::getTransition(int currentNode, V value)
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

template <typename T, typename V>
map<typename T::iterator, vector<T>> AhoCorasick<T, V>::MatchPattern(T &sequence)
{
    map<typename T::iterator, vector<T>> result;

    int currentNode = 0;
    typename T::iterator sequenceBegin = sequence.begin();
    typename T::iterator sequenceEnd = sequence.end();

    vector<typename T::iterator> iterators;
    for (typename T::iterator it = sequenceBegin; it != sequenceEnd; ++it)
    {
        iterators.push_back(it);
    }

    int iteratorsLength = iterators.size();

    for (int iteratorIndex = 0; iteratorIndex < iteratorsLength; ++iteratorIndex)
    {
        typename T::iterator it = iterators[iteratorIndex];
        V value = *it;
        currentNode = this->getTransition(currentNode, value);
        if (this->trie[currentNode].patternIndex != -1)
        {
            int patternIndex = this->trie[currentNode].patternIndex;
            int matchedPatternSize = this->patterns[patternIndex].size();
            typename T::iterator patternStart = iterators[iteratorIndex - matchedPatternSize + 1];
            if (result.find(patternStart) == result.end())
            {
                vector<T> temp;
                result[patternStart] = temp;
            }
            result[patternStart].push_back(this->patterns[patternIndex]);
        }
    }
    return result;
}

template <typename T, typename V>
AhoCorasick<T, V>::AhoCorasick(vector<T> patterns)
{
    this->patterns = patterns;
    this->BuildTrie();
}

#endif
