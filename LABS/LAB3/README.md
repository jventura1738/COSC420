 
# COSC420 Lab-3

by Justin Ventura & Blaine Mason

## How to run the program:
<code>make</code>
<code>mpiexec -n 4 ./main</code>
## Questions to answer:

### (a) What is the theoretical time complexity of your algorithms (best and worst case), in terms of the input size?

- For the inner product, it simply requires N/P time, where N is the # of elements in each vector, and P is the # of nodes/processes being run.  So the best and worst case will always be O(N/P) or simply O(N).  

- For the matrix addition and subtraction, the time will again take (N * K)/P where N := A.rows and K := A.cols, and P is the n # of nodes/processes being run.  So again, the best and worst cases will always be O((N * K)/P) or just O(N).

- For matrix transpose, this is just O(N) as it has not been parallelized.

- For matrix multiplication, it will require (N * M * K)/P time, where N := A.rows, M := Bt.rows, K := A.cols, and P is the # of nodes/processes being run.  The best and worst case will be N(N * M * K/P), or if we would like to be sneaky: O( (max(N, K, M))^3 / P )... hehe ;)

### (b) According to the data, does adding more nodes perfectly divide the time taken by the program?
No, in our program the inner product will continue to run in parallel, but with the inner product the more nodes the slower the program runs(As we discussed in lecture).  I have a feeling there is a better way that exists to perform this computation, but I am satisfied with the learning processes of overcoming different roadblocks.

### (c) What are some real-world software examples that would need the above routines? Why? Would they benefit greatly from using your distributed code?


### (d) How could the code be improved in terms of usability, efficiency, and robustness?
 
