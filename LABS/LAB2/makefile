# Justin Ventura & Blaine Mason
# COSC420, Lab 2: makefile

# module load mpi/mpich-x86_64
# mpicc <filename>.ext
# mpiexec ./a.out <args> -n <# nodes>
mc = mpicc 
flags = -lm -o
me = mpiexec -n 

gamer:
	$(mc) main.c matrix.c -o main
	$(me) $(a1) ./main $(a2) $(a3)
clean:
	rm -f *.o