#ifndef _AHO_CORASICK_H_
#define _AHO_CORASICK_H_

#include "aho_corasick_node.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <stack>

template <typename T, typename V>
class AhoCorasick
{
    vector<Node<V>> trie; // Contains the trie in the form of a vecto where each Node hold a value of type V and has children and parent indices
    vector<T> patterns;   // Contains the list of the patterns that are supposed to be matched

    void BuildTrie();                            // Method to build the trie using the patterns ( preprocessing stage )
    int getFallback(int currentNode);            // Method to get the fallback transition to the longest suffix if pattern match fails
    int getTransition(int currentNode, V value); // Method to get the transition from current state to next element in the sequence

public:
    map<typename T::iterator, vector<T>> MatchPattern(T &sequence);
    vector<T> AutoComplete(T &sequence);
    AhoCorasick(vector<T> patterns);
};

template <typename T, typename V>
void AhoCorasick<T, V>::BuildTrie()
{
    Node<V> root = Node<V>();   // Initializes the root node
    this->trie.push_back(root); // Pushed the root node into the empty trie

    int patternSize = this->patterns.size();
    // Iterates over each pattern
    for (int patternIndex = 0; patternIndex < patternSize; ++patternIndex)
    {
        T pattern = this->patterns[patternIndex];
        int currentNode = 0;
        // Iterates over each element in the pattern
        for (V value : pattern)
        {
            // If node doesn't exist in map, adds new node to trie
            if (this->trie[currentNode].next.find(value) == this->trie[currentNode].next.end())
            {
                this->trie[currentNode].next[value] = this->trie.size();
                this->trie.emplace_back(value, currentNode);
            }
            // Transitions to the next node corresponding the currentValue
            currentNode = this->trie[currentNode].next[value];
        }
        // Marks the last node of the pattern and stores the pattern index to determine pattern size later on
        this->trie[currentNode].patternIndex = patternIndex;
    }
}

template <typename T, typename V>
int AhoCorasick<T, V>::getFallback(int currentNode)
{
    // Check is value id cached, is not, updates cahe
    if (this->trie[currentNode].link == -1)
    {
        // If the node is root node or an immediate child of rootnode, fallback node is always root node
        // This is because the length of the longest suffix exclusive of the current state is 0
        if (currentNode == 0 || this->trie[currentNode].parent == 0)
        {
            this->trie[currentNode].link = 0;
        }
        // Else gets the fallback node of the parent and tries to transition to the current values
        // Recursive process till the fallback node becomes root or the longest suffix is found
        else
        {
            this->trie[currentNode].link = this->getTransition(this->getFallback(this->trie[currentNode].parent), this->trie[currentNode].value);
        }
    }
    // Returns cached value
    return this->trie[currentNode].link;
}

template <typename T, typename V>
int AhoCorasick<T, V>::getTransition(int currentNode, V value)
{
    // Check is value id cached, is not, updates cahe
    if (this->trie[currentNode].cached.find(value) == this->trie[currentNode].cached.end())
    {
        // Checks if normal transition exists, if yes...transitions to this node
        if (this->trie[currentNode].next.find(value) != this->trie[currentNode].next.end())
        {
            this->trie[currentNode].cached[value] = this->trie[currentNode].next[value];
        }
        // else, if current node is root node, can transition directly to root node
        else if (currentNode == 0)
        {
            trie[currentNode].cached[value] = 0;
        }
        // or else get the fallback node of the current node and tries to transition to "value"
        // If transition doesn't exist, recusrsively gets fallback till transition is possible or reaches root node
        else
        {
            trie[currentNode].cached[value] = this->getTransition(this->getFallback(currentNode), value);
        }
    }
    // Returns cached value
    return this->trie[currentNode].cached[value];
}

template <typename T, typename V>
map<typename T::iterator, vector<T>> AhoCorasick<T, V>::MatchPattern(T &sequence)
{
    // Stores result as a map of iterator:vector<Pattern Type>
    // As multiple patterns can start at same positon
    map<typename T::iterator, vector<T>> result;

    // Starts matching at root node
    int currentNode = 0;
    typename T::iterator sequenceBegin = sequence.begin();
    typename T::iterator sequenceEnd = sequence.end();

    vector<typename T::iterator> iterators;
    // Stores iterators of all positions for future use
    for (typename T::iterator it = sequenceBegin; it != sequenceEnd; ++it)
    {
        iterators.push_back(it);
    }

    int iteratorsLength = iterators.size();

    // Iterates through the sequence to be searched
    for (int iteratorIndex = 0; iteratorIndex < iteratorsLength; ++iteratorIndex)
    {
        typename T::iterator it = iterators[iteratorIndex];
        V value = *it;
        // Performs transitions with the alue at the index in the sequence
        currentNode = this->getTransition(currentNode, value);
        // If there is a pattern match, ie. index != -1, adds it to the result
        if (this->trie[currentNode].patternIndex != -1)
        {
            int patternIndex = this->trie[currentNode].patternIndex;
            int matchedPatternSize = this->patterns[patternIndex].size();
            typename T::iterator patternStart = iterators[iteratorIndex - matchedPatternSize + 1];
            // Checks if the iterator entry already exists, if not..adds one
            if (result.find(patternStart) == result.end())
            {
                vector<T> temp;
                result[patternStart] = temp;
            }
            // Adds the pattern that matched to the map
            result[patternStart].push_back(this->patterns[patternIndex]);
        }
    }
    return result;
}

// Stores the patterns and starts the preprocessing
template <typename T, typename V>
AhoCorasick<T, V>::AhoCorasick(vector<T> patterns)
{
    this->patterns = patterns;
    this->BuildTrie();
}

#endif

template <typename T, typename V>
vector<T> AhoCorasick<T, V>::AutoComplete(T &sequence)
{
    stack<int> indexStack;
    vector<T> result;
    int currentNode = 0;
    bool isMatched = true;
    for (V value : sequence)
    {
        if (this->trie[currentNode].next.find(value) == this->trie[currentNode].next.end())
        {
            isMatched = false;
            break;
        }
        currentNode = this->trie[currentNode].next[value];
    }

    if (!isMatched)
        return result;

    indexStack.push(currentNode);

    while (!indexStack.empty())
    {
        int poppedIndex = indexStack.top();
        indexStack.pop();
        if (this->trie[poppedIndex].patternIndex >= 0)
        {
            result.push_back(this->patterns[this->trie[poppedIndex].patternIndex]);
        }
        for (auto mapItem : this->trie[poppedIndex].next)
        {
            indexStack.push(mapItem.second);
        }
    }

    return result;
}
