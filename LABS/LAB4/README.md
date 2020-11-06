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

- Our algorithm runs in time O(((n/p)^3 + (n/p))LIMIT) and LIMIT is established by the user, but mainly the algorithm is dependant on the speed of matrix multiplication. In general, there will be (n/p) occuring several times, due to file read and write, as well as normalization in general.  For simplicity we know it depends on limit so it will be denoted as (n/p).  

### (b) According to the data, does adding more nodes perfectly divide the time taken by the program?
No, the reading and writing that occurs in both file implementations require plently of MPI overhead.  Also, it may be a matrix vector multiplication, but the method for it still has to be called.  So, although the time depends on how long you limit it to take till convergence, the node count increased would only improve the speedup of the file reading. Matrix multiplication will always have a strong overhead, and we know dividing perfectly does not speed that up.

### (c) What are some real-world software examples that would need the above routines? Why? Would they benefit greatly from using your distributed code?
The program project two, the file I/O and matrix logic will both be used in the programming of RING. The File I/O is used in the same iterative manner to avoid collectives, only allowing nodes to read the data they need.  The HITS and Page Rank algorithm both will rely on the logic mapped out in this lab, so we hope to use this in our development of RING.  Also, if a numerical linear algebra class wanted to observe special cases of this convergence, they could test large matricies on our code. 

### (d) How could the code be improved in terms of usability, efficiency, and robustness?
 Our memory management could have been better, also the naming and organization could use a tocuh up.  This is planned to occur in the project, where we will refine this class to ensure all edge cases are handled.  We are glad the lab is used in this project becuase it gives us an opportunity to work on both at the same time, but due to the length of time we were given, we could not polish everything by turn in. 
