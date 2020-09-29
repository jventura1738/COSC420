# Makefile

# Makefile variables:
gc = g++ -c -std=c++11
go = g++ -o

main: list.o main.o
	$(go) main list.o main.o

main.o: list.cpp main.cpp
	$(gc) main.cpp

list.o: list.h list.cpp
	$(gc) list.cpp

clean:
	rm -rf *.o main