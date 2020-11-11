# Justin Ventura COSC420

# module load mpi/mpich-x86_64
# mpicc <filename>.ext
mc = gcc
flags = -lm -Wall -Werror

main: main.o matrix.o
	$(mc) -o main main.c matrix.c

main.o: main.c matrix.h
	$(mc) -c main.c

matrix.o: matrix.c matrix.h
	$(mc) -c matrix.c

clean:
	rm -f *.o main