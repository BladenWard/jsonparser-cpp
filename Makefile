CC=g++
CPPFLAGS=-g -Wall -std=c++11

all: main

main: main.o
	$(CC) $(CPPFLAGS) -o main main.o

%.o: %.cpp .hpp
	$(CC) $(CPPFLAGS) -c $<

.PHONY: clean
clean:
	rm -rf *.o main

