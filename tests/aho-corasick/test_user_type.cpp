#include "aho_corasick.hpp"
#include <bits/stdc++.h>

class TestClass
{
    char id;

public:
    TestClass(char id = '$')
    {
        this->id = id;
    }
    bool operator==(TestClass const &rhs) const
    {
        return id == rhs.id;
    }
    bool operator<(TestClass const &rhs) const
    {
        return id < rhs.id;
    }
    bool operator>(TestClass const &rhs) const
    {
        return id > rhs.id;
    }
};

int main()
{
    vector<TestClass> text = {TestClass('g'), TestClass('c'), TestClass('a'), TestClass('t'), TestClass('c'), TestClass('g')};
    vector<vector<TestClass>> patterns = {{TestClass('a'), TestClass('c'), TestClass('c')}, {TestClass('a'), TestClass('t'), TestClass('c')}, {TestClass('c'), TestClass('a'), TestClass('t')}, {TestClass('g'), TestClass('c'), TestClass('g')}, {TestClass('c'), TestClass('a')}};
    AhoCorasick<vector<TestClass>, TestClass> search = AhoCorasick<vector<TestClass>, TestClass>(patterns);
    map<vector<TestClass>::iterator, vector<vector<TestClass>>> result = search.MatchPattern(text);
}
