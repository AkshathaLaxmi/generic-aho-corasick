# Akshatha
all:
	sudo cp include/aho_corasick.hpp /usr/include/c++/10.2.0/; sudo cp include/aho_corasick_node.hpp /usr/include/c++/10.2.0/; sudo cp kmp/kmp.hpp /usr/include/c++/10.2.0/

clean:
	sudo rm /usr/include/c++/10.2.0/aho_corasick.hpp; sudo rm /usr/include/c++/10.2.0/aho_corasick_node.hpp; sudo rm /usr/include/c++/10.2.0/kmp.hpp
# Sparsh
# all:
# 	sudo cp include/aho_corasick.hpp /usr/include/c++/9/; sudo cp include/aho_corasick_node.hpp /usr/include/c++/9/

# clean:
# 	sudo rm /usr/include/c++/9/aho_corasick.hpp; sudo rm /usr/include/c++/9/aho_corasick_node.hpp