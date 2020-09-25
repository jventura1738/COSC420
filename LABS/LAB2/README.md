# COSC420 Lab-2

by Justin Ventura & Blaine Mason

## How to run the program:
<code>make gamer a1=<# of Nodes> a2=<Rows of A> a3=<Cols of A> a4=<Rows of B> a5=<Cols of B></code>

## Questions to answer:

### (a) What is the theoretical time complexity of your algorithms (best and worst case), in terms of the input size?

- For the inner product, it simply requires N/P time, where N is the # of elements in each vector, and P is the # of nodes/processes being run.  So the best and worst case will always be O(N/P) or simply O(N).  

- For the matrix addition and subtraction, the time will again take (N * K)/P where N := A.rows and K := A.cols, and P is the n # of nodes/processes being run.  So again, the best and worst cases will always be O((N * K)/P) or just O(N).

- For matrix transpose, this is just O(N) as it has not been parallelized.

- For matrix multiplication, it will require (N * M * K)/P time, where N := A.rows, M := Bt.rows, K := A.cols, and P is the # of nodes/processes being run.  The best and worst case will be N(N * M * K/P), or if we would like to be sneaky: O( (max(N, K, M))^3 / P )... hehe ;)

### (b) According to the data, does adding more nodes perfectly divide the time taken by the program?

### (c) What are some real-world software examples that would need the above routines? Why? Would they benefit greatly from using your distributed code?

I learned in my linear algebra class that a lot of 3D graphics are numerically represented by matrices and vectors in the background.  For example, a matrix transformation (multiplication, addition, tranpose, etc.) could be used to rotate or move some 3D object in a direction.  I am now aware of the specifics, but that is the basic idea behind 3D graphics.  Now, they would benefit from the parallelization.  When matrices get large, being able to save time by factors of P (more or less) in the real world is crucial to a projects success.  A game server or web application that runs slow is never ideal, and in many cases, deters customers.  So this justifies spending the extra money and time to save whatever time they can from parallelization.

### (d) How could the code be improved in terms of usability, efficiency, and robustness?

I'm sure there must be better way to parallelize matrix multiplication, but for now we still need to think about it.
