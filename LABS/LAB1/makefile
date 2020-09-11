# Justin Ventura & Blaine Mason
# COSC420, Lab 1: makefile

# module load mpi/mpich-x86_64
# mpicc <filename>.ext
# mpiexec ./a.out <args> -n <# nodes>
mc = mpicc 
flags = -lm -o
me = mpiexec -n 

run_Prime: Prime
	-$(me) $(a1) ./Prime.o $(a2)
run_Hello: Hello
	$(me) $(a1) ./Hello.o
Hello: hello.c
	$(mc) hello.c $(flags) Hello.o
Prime: Lab-1-prime.c
	$(mc) Lab-1-prime.c $(flags) Prime.o
clean:
	rm -f *.o
