# Justin Ventura

gc = gcc -c
go = gcc -o

main: totient_max.o
	$(go) main totient_max.o

totient_max.o: totient_max.c
	$(gc) totient_max.c

clean:
	rm -rf *.o main