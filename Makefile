
all: test5

test5: test5.cpp ListLinked.cpp ListLinked.h
	g++ -g -Wall -o test5 test5.cpp
