CC=g++
CPPFLAGS=-g -Wall -std=c++17

all: main

main: main.o json_parser.o
	$(CC) $(CPPFLAGS) -o $@ $^

main.o: main.cpp
	$(CC) $(CPPFLAGS) -c $<

json_parser.o: json_parser.cpp json_parser.hpp
	$(CC) $(CPPFLAGS) -c $<

.PHONY: clean
clean:
	rm -f main main.o
