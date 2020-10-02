# Justin Ventura

gc = gcc -c
go = gcc -o

main: rel_prime.o
	$(go) main rel_prime.o

rel_prime.o: rel_prime.c
	$(gc) rel_prime.c

clean:
	rm -rf *.o main