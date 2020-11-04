# module load mpi/mpich-x86_64
# mpicc <filename>.ext
mc = mpicc 
flags = -lm -Wall -Werror

main: main.o matrix.o
	$(mc) -o main main.c matrix.c $(flags)
	rm -f Ax
main.o: main.c matrix.h
	$(mc) -c main.c -g $(flags)
matrix.o: matrix.c matrix.h
	$(mc) -c matrix.c -g $(flags)
clean:
	rm -f *.o main