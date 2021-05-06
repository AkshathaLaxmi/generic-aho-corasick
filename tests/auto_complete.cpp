#include "aho_corasick.hpp"
#include <bits/stdc++.h>

int main()
{
    string text = "hel";
    vector<string> patterns = {"hello", "dog", "hell", "cat", "a", "hel", "help", "helps", "helping"};
    AhoCorasick<string, char> search = AhoCorasick<string, char>(patterns);
    vector<string> result = search.AutoComplete(text);
    for (string r : result)
    {
        cout << r << endl;
    }
    return 0;
}
