# module load mpi/mpich-x86_64
# mpicc <filename>.ext
mc = mpicc 
flags = -lm 

main: main.o matrix.o
	$(mc) -o run main.c matrix.c $(flags)
main.o: main.c 
	$(mc) -c main.c -g $(flags)
matrix.o: matrix.c matrix.h
	$(mc) -c matrix.c -g $(flags)
clean:
	rm -f *.o 