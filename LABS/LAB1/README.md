# COSC420 Lab-1

by Justin Ventura & Blaine Mason

## How to run the program:
First enter: <code> make clean </code>\
Enter into the terminal: <code> make run_Hello a1=<# nodes you wish to spawn></code>\
Enter into the terminal: <code> make run_Prime a1=<# of nodes you wish to spawn> a2="N you want to test for primality" </code>

## Questions to answer:

### (a) What is the theoretical time complexity of your sorting algorithms (best and worst case), in terms of the input size?

Given an input size N, the worst case would be O((√N / p) + s * p) where p is the number of nodes and s is the setup time for each node.  This essentially boils down to O(√N) for worst case.  Best case would be O(1 + s * p), since a factor could be found within the first iteration.  The s * p stems from the fact that for each node you have a setup time as usual.  Once again, this boils down to be O(1) if we are talking about the raw algorithm.

### (b) According to the data, does adding more nodes perfectly divide the time taken by the program?

Please see the data.pdf in this directory: this may come as a surprise to some, but more nodes does not mean a perfect division of time.  This is because (especially for trivial/quick algorithms) the setup times for the nodes begins to burden the time complexity overall.  In our example, 1-4 nodes performed pretty well, but any more than that just ends up being a burden.  This is especially true when more nodes are allocated than the machine has cores.

### (c) Justify/prove the fact that one needs only check up to √N in the brute force primality test.

Please see the attached JV_BM_proof for our justification.

### (d) How could the code be improved in terms of usability, efficiency, and robustness?

As of now, I am unaware of any ways where this could be made any better.  
