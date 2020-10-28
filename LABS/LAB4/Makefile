# module load mpi/mpich-x86_64
# mpicc <filename>.ext
mc = mpicc 
flags = -lm -o

main: main.o matrix.o
	$(mc) -o main main.c matrix.c -lm
main.o: main.c matrix.h
	$(mc) -c main.c -g -lm
matrix.o: matrix.c matrix.h
	$(mc) -c matrix.c -g -lm
clean:
	rm -f *.o main