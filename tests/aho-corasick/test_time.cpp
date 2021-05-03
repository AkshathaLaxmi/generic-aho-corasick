#include "aho_corasick.hpp"
#include "kmp.hpp"
#include <chrono>
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

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
    int str_length = 1000;
    string sequence = gen_random_string(str_length);

    int max_pattern_length = 10;
    int pattern_num = 1000000;
    vector<string> patterns;

    for (int i = 0; i < pattern_num; ++i)
    {
        int temp_length = rand() % max_pattern_length;
        string temp = gen_random_string(temp_length);
        patterns.emplace_back(temp);
    }

    auto start = high_resolution_clock::now();
    AhoCorasick<string, char> search = AhoCorasick<string, char>(patterns);
    search.MatchPattern(sequence);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Aho Corasick: " << duration.count() << " milliseconds" << endl;

    start = high_resolution_clock::now();
    AhoCorasick<string, char> kSearch = AhoCorasick<string, char>(patterns);
    kSearch.MatchPattern(sequence);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "KMP Search: " << duration.count() << " milliseconds" << endl;

    return 0;
}
