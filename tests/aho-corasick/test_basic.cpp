#include "aho_corasick.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    string text = "gcatcg";
    vector<string> patterns = {"acc", "atc", "cat", "gcg", "ca"};
    AhoCorasick<string, char> search = AhoCorasick<string, char>(patterns);
    map<string::iterator, vector<string>> result = search.MatchPattern(text);
    for (pair<string::iterator, vector<string>> item : result)
    {
        cout << "Iterator start: " << item.first - text.begin() << endl;
        for (string i : item.second)
        {
            cout << i << endl;
        }
    }
    return 0;
}
