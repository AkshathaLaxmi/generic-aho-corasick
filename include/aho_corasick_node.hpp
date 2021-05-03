#ifndef _AHO_CORASICK_NODE_H_
#define _AHO_CORASICK_NODE_H_

#include <map>
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
    int patternIndex;

    Node();
    Node(T value, int parent = 0);
};

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
