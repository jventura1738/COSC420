main: BigIntegerSingleFile.o test.o
	./mpipp.sh -o test test.o BigIntegerSingleFile.o

test.o: test.c
	gcc -c -g test.c
BigIntegerSingleFile.o: BigIntegerSingleFile.cpp
	g++ -c  BigIntegerSingleFile.cpp -g

clean: 
	rm *.o 
