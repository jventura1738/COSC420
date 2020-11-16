# module load mpi/mpich-x86_64
# mpicc <filename>.ext
mc = mpicc 
flags = -lm 

main: unique.o matrix.o
	$(mc) -o ligma UniqueWords.c matrix.c $(flags)
matrix.o: data.c matrix.h
	$(mc) -c matrix.c -g $(flags)
matrix.o: matrix.c matrix.h
	$(mc) -c matrix.c -g $(flags)
clean:
	rm -f *.o 