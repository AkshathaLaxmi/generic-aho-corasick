# generic-aho-corasick
Generic implementation of Aho Corasick pattern matching algorithm.

Time complexity - O((n + m)(1 + logm) + z), where
    n - total number of elements in the input sequence string
    m - sum of length of patterns
    z - number of occurrences of pattern in sequence

### Instructions to run
   1. Change the version in the Makefile to the C++ version on your system.
   2. Run the command `make`
   3. Compile any of the test cases.
   4. Execute `./a.out`

### How to call the Aho-Corasick pattern match function?
   - Create an object of the type AhoCorasick, specifying the type of container for the input sequence and the type of individual items in that container.
       - These types will also correspond to the individual patterns.
   - Call the function MatchPattern on the created object with the vector containing patterns.
   - The function will return a `map` with the key as the position at which pattern was found in the sequence and the value as a list of patterns that were found at the respective index.

### Performance
   Implemented a generic KMP algorithm (Time Complexity - O(n*k + m) where k is total number of pattern strings) to notice the optimizations provided by Aho-Corasick algorithm.
   
   ![Aho-Corasick and KMP](https://user-images.githubusercontent.com/47936078/117105845-7b4bca00-ad9c-11eb-97af-42cf45d04d32.png)
   
   Generic Aho-Corasick performs better than generic KMP.
