# Justin Ventura & Blaine Mason
# COSC420, RGB_116: makefile

# module load mpi/mpich-x86_64
# mpicc <filename>.ext
# mpiexec ./a.out <args> -n <# nodes>
mc = mpicc 
flags = -lm -o
me = mpiexec -n 

gamer:
	$(mc) main.c $(flags) main 
clean:
	rm -f *.o