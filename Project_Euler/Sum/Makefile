# module load mpi/mpich-x86_64
# mpicc <filename>.ext
# mpiexec ./a.out <args> -n <# nodes>
mc = mpicc 
flags = -lm -o

main:
	$(mc) main.c -o main
clean:
	rm -f *.o
	rm -f main