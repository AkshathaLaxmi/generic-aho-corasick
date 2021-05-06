#include "aho_corasick.hpp"
#include <bits/stdc++.h>

int main()
{
    vector<vector<int>> text = {{1, 2}, {2, 3}, {3, 4}};
    vector<vector<vector<int>>> patterns = {{{1, 2}, {2, 3}, {3, 4}, {6, 2}}, {{1, 2}, {2, 3}, {3, 4}, {3, 4, 5}}, {{1, 3}}};
    AhoCorasick<vector<vector<int>>, vector<int>> search = AhoCorasick<vector<vector<int>>, vector<int>>(patterns);
    vector<vector<vector<int>>> result = search.AutoComplete(text);
    cout << result.size() << endl;
    // for (vector<vector<int>> r : result)
    // {
    //     cout << r << endl;
    // }
    return 0;
}
