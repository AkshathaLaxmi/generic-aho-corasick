#ifndef _KMP_H_
#define _KMP_H_

#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Algorithm:
// Step - 1: Preprocess the pattern. Make an array that stores the size of the longest prefix which
//           is also a suffix for pattern[0:i]
// Step - 2: Searching
//           Start comparison of pat[j] with j = 0 with characters of current window of sequence
//           Keep matching characters txt[i] and pat[j] and keep incrementing i and j while pat[j] and sequence[i] keep matching
//           When mismatch occurs -
//               It is known that characters pat[0:j-1] match with sequence[i-j:i-1]
//               preprocess[j-1] will tell us how many positions we can skip to start searching in the new window

template <typename T, typename V>
class KMP
{
    vector<T> patterns;
    map<typename T::iterator, vector<T>> result;
    vector<typename T::iterator> iterators;

    void preprocessor(T pattern, int pat_len, int* preprocess);
    void search(T pattern);
    void kmpSearch(T &sequence);

    public:
        KMP(vector<T> patterns);
        map<typename T::iterator, vector<T>> MatchPattern(T &sequence);
};

template<typename T, typename V>
void KMP<T, V>::preprocessor(T pattern, int pat_len, int *preprocess)
{
    int longest_pref_len = 0;

    preprocess[0] = 0;

    for (int i = 1; i < pat_len;)
    {
        if (pattern[i] == pattern[longest_pref_len])
        {
            preprocess[i] = ++longest_pref_len;
            ++i;
        }
        else
        {
            if (longest_pref_len != 0)
            {
                longest_pref_len = preprocess[longest_pref_len - 1];
            }
            else
            {
                preprocess[i] = 0;
                ++i;
            }
        }
    }
}

template<typename T, typename V>
void KMP<T, V>::search(T pattern)
{
    int pat_len = pattern.size();
    int iterator_size = this->iterators.size();

    int preprocess[pat_len];

    preprocessor(pattern, pat_len, preprocess);

    int j = 0;
    for (int iteratorIndex = 0; iteratorIndex < iterator_size;) {
        
        typename T::iterator it = this->iterators[iteratorIndex];
        V value = *it;
        
        if (pattern[j] == value) {
            ++j;
            ++iteratorIndex;
            if (iteratorIndex < iterator_size) {
                it = this->iterators[iteratorIndex];
                value = *it;
            }
        }


        if (j == pat_len) {
            typename T::iterator patternStart = this->iterators[iteratorIndex - pat_len + 1];
            if (this->result.find(patternStart) == this->result.end()) {
                vector<T> temp;
                this->result[patternStart] = temp;
            }
            this->result[patternStart].push_back(pattern);
            j = preprocess[j - 1];
        }

        else if (iteratorIndex < iterator_size && pattern[j] != value) {
            if (j != 0)
            {
                j = preprocess[j - 1];
            }
            else
            {
                ++iteratorIndex;
            }
        }
    }
}

template<typename T, typename V>
void KMP<T, V>::kmpSearch(T &sequence)
{
    typename T::iterator sequenceBegin = sequence.begin();
    typename T::iterator sequenceEnd = sequence.end();
    for (typename T::iterator it = sequenceBegin; it != sequenceEnd; ++it) {
        this->iterators.push_back(it);
    }
    for (T pattern : this->patterns)
    {
        this->search(pattern);
    }
}

template<typename T, typename V>
KMP<T, V>::KMP(vector<T> patterns)
{
    this->patterns = patterns;
}

template<typename T, typename V>
map<typename T::iterator, vector<T>> KMP<T, V>::MatchPattern(T &sequence)
{
    this->kmpSearch(sequence);
    return this->result;
}

#endif
