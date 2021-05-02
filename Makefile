all:
	sudo cp include/aho_corasick.hpp /usr/include/c++/9; sudo cp include/aho_corasick_node.hpp /usr/include/c++/9

clean:
	sudo rm /usr/include/c++/9/aho_corasick.hpp; sudo rm /usr/include/c++/9/aho_corasick_node.hpp