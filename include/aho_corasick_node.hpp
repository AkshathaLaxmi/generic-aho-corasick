#ifndef _AHO_CORASICK_NODE_H_
#define _AHO_CORASICK_NODE_H_

#include <unordered_map>
using namespace std;

template <typename T>
class Node
{
public:
    T value;
    int parent;
    unordered_map<T, int> next;
    unordered_map<T, int> cached;
    int link;
    int isPattern;

    Node();
    Node(T value, int parent = 0);
};

template <typename T>
Node<T>::Node(T value, int parent)
{
    this->value = value;
    this->parent = parent;
    this->isPattern = false;
    this->link = -1;
}

template <typename T>
Node<T>::Node()
{
    this->parent = 0;
    this->link = -1;
    this->isPattern = false;
}

#endif
