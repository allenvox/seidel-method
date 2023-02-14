all: main
.PHONY: main
main: main.cpp
	g++ -Wall -Wextra -o $@ $^