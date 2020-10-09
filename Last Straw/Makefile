main: BigIntegerSingleFile.o test.o
	g++ -o test test.o BigIntegerSingleFile.o

test.o: test.c
	gcc -c -g test.c
BigIntegerSingleFile.o: BigIntegerSingleFile.cpp
	g++ -c -g BigIntegerSingleFile.cpp

clean: 
	rm *.o 