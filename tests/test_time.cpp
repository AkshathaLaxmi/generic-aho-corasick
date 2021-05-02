#include "aho_corasick.hpp"
#include <bits/stdc++.h>
using namespace std;

string gen_random_string(int length)
{
    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                        'r', 's', 't', 'u', 'v', 'w', 'x',
                        'y', 'z'};

    stringstream result;
    for (int index = 0; index < length; ++index)
    {
        result << (int)(letters[rand() % 26]);
    }
    return result.str();
}

int main()
{
    int str_length = 10000000;
    string sequence = gen_random_string(str_length);

    int max_pattern_length = 20;
    int pattern_num = 10000;
    vector<string> patterns;

    for (int i = 0; i < pattern_num; ++i)
    {
        int temp_length = rand() % max_pattern_length;
        string temp = gen_random_string(temp_length);
        patterns.emplace_back(temp);
    }
    AhoCorasick<string, char> search = AhoCorasick<string, char>(patterns);
    search.MatchPattern(sequence);
    return 0;
}
