#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Algorithm:
// Step - 1: Preprocess the pattern. Make an array that stores the size of the longest prefix which
//           is also a suffix for pattern[0:i]
// Step - 2: Searching
//           Start comparison of pat[j] with j = 0 with characters of current window of text
//           Keep matching characters txt[i] and pat[j] and keep incrementing i and j while pat[j] and text[i] keep matching
//           When mismatch occurs - 
//               It is known that characters pat[0:j-1] match with text[i-j:i-1]
//               preprocess[j-1] will tell us how many positions we can skip to start searching in the new window


template<typename T>
class KMP {
    vector<T> patterns;
    T text;

    void preprocessor(T pattern, int pat_len, int* preprocess) {
        int longest_pref_len = 0;
        
        preprocess[0] = 0;

        for(int i = 1; i < pat_len;) {
            if(pattern[i] == pattern[longest_pref_len]) {
                preprocess[i] = ++longest_pref_len;
                ++i;
            }
            else {
                if(longest_pref_len != 0) {
                    longest_pref_len = preprocess[longest_pref_len - 1];
                }
                else {
                    preprocess[i] = 0;
                    ++i;
                }
            }
        }
    }

    void search(T pattern) {
        int pat_len = pattern.size();
        int text_len = this->text.size();

        int preprocess[pat_len];

        preprocessor(pattern, pat_len, preprocess);

        int j = 0;
        for(int i = 0; i < text_len; ) {
            if(pattern[j] == this->text[i]) {
                ++j;
                ++i;
            }

            if(j == pat_len) {
                cout << i << '\n';
                j = preprocess[j - 1];
            }

            else if (i < text_len && pattern[j] != this->text[i]) {
                if (j != 0) {
                    j = preprocess[j - 1];
                }
                else {
                    ++i;
                }
            }
        }
    }

    void kmpSearch() {
        for (T pattern: this->patterns) {
            this->search(pattern);
        }
    }

public:

    KMP(vector<T> patterns) {
        this->patterns = patterns;
    }

    void MatchPattern(T text) {
        this->text = text;
        this->kmpSearch();
    }
};

int main() {
    // string text = "gcatcg";
    // vector<string> patterns = {"acc", "atc", "cat", "gcg"};

    vector<vector<int>> text = {{2, 3, 4}, {5, 7, 3}, {4, 5, 2}, {100, 44, 56}, {5, 7, 3}, {2, 3, 4}};
    vector<vector<vector<int>>> patterns = {{{4, 5, 2}, {5, 7, 3}, {5, 7, 3}}, {{4, 5, 2}, {100, 44, 56}, {5, 7, 3}}, {{5, 7, 3}, {4, 5, 2}, {100, 44, 56}}, {{2, 3, 4}, {5, 7, 3}, {2, 3, 4}}};
    KMP<vector<vector<int>>> search = KMP<vector<vector<int>>>(patterns);
    search.MatchPattern(text);
    return 0;
}
