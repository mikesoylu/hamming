all:
	clang++ -o hamming *.cpp
debug:
	clang++ -o hamming -Wall -g -DDEBUG *.cpp
