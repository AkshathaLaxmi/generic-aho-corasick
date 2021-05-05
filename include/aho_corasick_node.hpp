#ifndef _AHO_CORASICK_NODE_H_
#define _AHO_CORASICK_NODE_H_

#include <map>
using namespace std;

// Used to store single node in the trie of the patterns
template <typename T>
class Node
{
public:
    T value;            // Stores the value at the node, null by default
    int parent;         // Store the index of the parent node of the trie
    map<T, int> next;   // Store the mapping of value to child nodes
    map<T, int> cached; // Used to cache 'next' values to avoid recomputation
    int link;           // Stores the index of the fallback if the transition fails
    int patternIndex;   // Store the index of the pattern in the pattern vector if it is the last elemtn in the pattern

    Node();                        // Used by the root node since value is null
    Node(T value, int parent = 0); // Used by all non root nodes
};

// Constructors for creating a node in the Trie
template <typename T>
Node<T>::Node(T value, int parent)
{
    this->value = value;
    this->parent = parent;
    this->link = -1;
    this->patternIndex = -1;
}

template <typename T>
Node<T>::Node()
{
    this->parent = 0;
    this->link = -1;
    this->patternIndex = -1;
}

#endif
