#include "aho_corasick.hpp"
#include <bits/stdc++.h>

using namespace std;

void test_vectors()
{
    vector<vector<int>> text = {{2, 3, 4}, {5, 7, 3}, {4, 5, 2}, {100, 44, 56}, {5, 7, 3}, {2, 3, 4}};
    vector<vector<vector<int>>> patterns = {{{4, 5, 2}, {5, 7, 3}, {5, 7, 3}}, {{4, 5, 2}, {100, 44, 56}, {5, 7, 3}}, {{5, 7, 3}, {4, 5, 2}, {100, 44, 56}}, {{2, 3, 4}, {5, 7, 3}, {2, 3, 4}}};
    AhoCorasick<vector<vector<int>>, vector<int>> search = AhoCorasick<vector<vector<int>>, vector<int>>(patterns);
    map<vector<vector<int>>::iterator, vector<vector<vector<int>>>> result = search.MatchPattern(text);

    for (pair<vector<vector<int>>::iterator, vector<vector<vector<int>>>> item : result)
    {
        cout << "Iterator start: " << item.first - text.begin() << endl;
    }
}

void test_sets()
{
    vector<set<int>> text = {{2, 3, 4}, {5, 7, 3}, {4, 5, 2}, {100, 44, 56}, {5, 7, 3}, {2, 3, 4}};
    vector<vector<set<int>>> patterns = {{{4, 5, 2}, {5, 7, 3}, {5, 7, 3}}, {{4, 5, 2}, {100, 44, 56}, {5, 7, 3}}, {{5, 7, 3}, {4, 5, 2}, {100, 44, 56}}, {{2, 3, 4}, {5, 7, 3}, {2, 3, 4}}};
    AhoCorasick<vector<set<int>>, set<int>> search = AhoCorasick<vector<set<int>>, set<int>>(patterns);
    map<vector<set<int>>::iterator, vector<vector<set<int>>>> result = search.MatchPattern(text);
}

int main()
{
    test_vectors();
    test_sets();
    return 0;
}
