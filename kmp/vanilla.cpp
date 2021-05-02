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

void preprocessor(string pattern, int pat_len, int* preprocess) {
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

void search(string text, string pattern) {
    int pat_len = pattern.size();
    int text_len = text.size();

    int preprocess[pat_len];

    preprocessor(pattern, pat_len, preprocess);

    int j = 0;
    for(int i = 0; i < text_len; ) {
        if(pattern[j] == text[i]) {
            ++j;
            ++i;
        }

        if(j == pat_len) {
            cout << "Pattern: " << pattern << " found at: " << i << '\n';
            j = preprocess[j - 1];
        }

        else if (i < text_len && pattern[j] != text[i]) {
            if (j != 0) {
                j = preprocess[j - 1];
            }
            else {
                ++i;
            }
        }
    }
}

void kmpSearch(string text, vector<string> patterns) {
    for (string pattern: patterns) {
        search(text, pattern);
    }
}

int main() {
    string text = "gcatcg";
    vector<string> patterns = {"acc", "atc", "cat", "gcg"};

    kmpSearch(text, patterns);
    return 0;
}
