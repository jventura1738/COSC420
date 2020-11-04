# COSC420 Lab-4

by Justin Ventura & Blaine Mason

## How to run the program:
<code>make</code>
<code>mpiexec -n "insert numbr of nodes" ./main</code>
## Questions to answer:

### (a) What is the theoretical time complexity of your algorithms (best and worst case), in terms of the input size?

- For the inner product, it simply requires N/P time, where N is the # of elements in each vector, and P is the # of nodes/processes being run.  So the best and worst case will always be O(N/P) or simply O(N).  

- For the matrix addition and subtraction, the time will again take (N * K)/P where N := A.rows and K := A.cols, and P is the n # of nodes/processes being run.  So again, the best and worst cases will always be O((N * K)/P) or just O(N).

- For matrix transpose, this is just O(N) as it has not been parallelized.

- For matrix multiplication, it will require (N * M * K)/P time, where N := A.rows, M := Bt.rows, K := A.cols, and P is the # of nodes/processes being run.  The best and worst case will be N(N * M * K/P), or if we would like to be sneaky: O( (max(N, K, M))^3 / P )... hehe ;)

- For Gauss Jordan it will require O(N^3) in serial, per intuition, but in parallel I am unsure.  I am estimating the algorithm will take K * R/P * C time, s.t. K = #rows R/P = #rows/#nodes C = #cols so in total it would run just under N^3 assuming square matricies.  

### (b) According to the data, does adding more nodes perfectly divide the time taken by the program?
Up to a factor, yes adding more nodes divides the time.  The catch is that once a certain threshold is met there is a limit on speed up.  For n=500 around 15 was where the data capped in terms of speedup.  For n=800 around 20 is were the speedup did as much as it could.

### (c) What are some real-world software examples that would need the above routines? Why? Would they benefit greatly from using your distributed code?
Any site or program that performs rref or matrix inversion.  As we mentioned in the previous lab, computer graphics make use of large matricies and performing operations on them.  Having an algorithm like Gauss Jordan in parallel can help speed up those operations.  Games that run in high resolutions make take advantage of parallelization for large matrix operations that need to perform almost instantly.  I am unsure if that is more focused on the processes in the GPU, but at least some of it is done on the processor.

### (d) How could the code be improved in terms of usability, efficiency, and robustness?
 We believe overall that the codes computation of send counts and displacements could use some tidying up.  As the dimensions increase the computations take longer, so like matrix multiplication, there probably is some way of making the code more efficient. 
