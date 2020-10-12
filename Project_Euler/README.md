# Project Euler Parallelism

Project 1: COSC420.

by Justin Ventura and Blaine Mason

## Preface

This project was one for the history books.  Over the course of the project we logged around 70-80 total hours working on solving, programming, and testing the problems we chose.  Although we only are submitting three problems, we came up with code(slow, but would yield the result) to solve serveral other problems across the range given.  There were certainly times when we felt on top of the world and times we felt buried alive.


## Problem 145: How many reversible numbers are there below one-billion
**Description**
Some positive integers n have the property that the sum [ n + reverse(n) ] consists entirely of odd (decimal) digits. For instance, 36 + 63 = 99 and 409 + 904 = 1313. We will call such numbers reversible; so 36, 63, 409, and 904 are reversible. Leading zeroes are not allowed in either n or reverse(n).
There are 120 reversible numbers below one-thousand.
How many reversible numbers are there below one-billion (10^9)?

**Approach**
At first glance this problem seemed rather trivial. So, we were unsure if we wanted to even attempt to solve it, but after going through iterations on the board we realized it could be parallelized.  We both wanted to use blocking to solve this problem faster.  In theory one node is extremely slow in testing a number if it is reversible, every digit in the sum is odd, and no trailing zeros exist for all numbers between 1 and 1,000,000,000. Say we use 10 nodes, that splits the problem up into the following:
Node: 0 Numbers: 0 - 100000000 
Node: 1 Numbers: 100000000 - 200000000 
Node: 2 Numbers: 200000000 - 300000000  
Node: 3 Numbers: 300000000 - 400000000  
Node: 4 Numbers: 400000000 - 500000000 
Node: 5 Numbers: 500000000 - 600000000   
Node: 6 Numbers: 600000000 - 700000000                                                                             
Node: 7 Numbers: 700000000 - 800000000                                                                                
Node: 8 Numbers: 800000000 - 900000000                                                                                                                                    
Node: 9 Numbers: 900000000 - 1000000000

**Solving the Problem**
After lecture on Tuesday() we rushed into the lab to see if we could figure this one out.  Justin had recalled a program he wrote to test if a number was palindromic, so we used that for our solution.  We wrote an algorithm and tested our base cases, but we got too cocky and after testing for our end result, we forgot about the rule of trailing zeros.  That test took a total of three hours to run, and after parallelizing it and optimizing we found a solution in ~15 seconds.  Test cases and numerical results follow.  The algorithm in parallel is O($\frac{n}{p}$).

**1 Node or Serial**

Sum: 608720

real    0m11.385s

user    0m11.369s

sys     0m0.014s

**10 Nodes**

Sum: 608720

real    0m1.472s

user    0m14.424s

sys     0m0.132s

**20 Nodes**

Sum: 608720

real    0m1.038s

user    0m19.957s

sys     0m0.425s 

**24 Nodes**

Sum: 608720

real    0m0.898s

user    0m20.584s

sys     0m0.369s

## Problem 211: Divisor Square Sum

**Description**
For a positive integer n, let σ2(n) be the sum of the squares of its divisors. For example,

σ2(10) = 1 + 4 + 25 + 100 = 130.
Find the sum of all n, 0 < n < 64,000,000 such that σ2(n) is a perfect square.

**Approach**
Originally, our plan was to find all the factors of a given number n, square each factor, add them, and check if it is a perfect square.  Brute force attempts are often slow, so we knew this would not be the best way.  We took this as an opportunity to highlight the advantage of parallization.  Initially we found all the factors of a given number n by testing its divisibility with numbers 1-n.  That was O(n), and was not fast since it needed to be run 64,000,000 times.  After doing some research we found a method for only having to search from 1-sqrt(n), which carries the same logic as our first prime lab.

**Solving the Problem**
Writing the algorithm took around three hours, but the tests were embarrasingly slow.  This is because we ran on the cluster first the O(n) search, for a N=1,000,000 and it never finished after a day.  So, after several tests with our O(sqrt(n)) method it ran N=1,000,000 quickly on the machine we were using in the lab.  Finally, after testing it on 10 nodes, after 45 minutes we found the correct answer!  With the optimization to the factorization the algorithm in parallel is O($\frac{n\sqrt{n}}{p}$). 

**1 Node or Serial**

**10 Nodes**
Node: 0 Numbers: 1.000000 - 6400001.000000
0 count is: 106866310.000000
Node: 1 Numbers: 6400000.000000 - 12800000.000000
1 count is: 151267355.000000
Node: 2 Numbers: 12800000.000000 - 19200000.000000
2 count is: 200570985.000000
Node: 3 Numbers: 19200000.000000 - 25600000.000000
3 count is: 177820311.000000
Node: 4 Numbers: 25600000.000000 - 32000000.000000
4 count is: 258151556.000000
Node: 5 Numbers: 32000000.000000 - 38400000.000000
5 count is: 214096872.000000
Node: 6 Numbers: 38400000.000000 - 44800000.000000
6 count is: 119876205.000000
Node: 7 Numbers: 44800000.000000 - 51200000.000000
7 count is: 234894492.000000
Node: 8 Numbers: 51200000.000000 - 57600000.000000
8 count is: 212511333.000000
Node: 9 Numbers: 57600000.000000 - 64000000.000000
9 count is: 246309266.000000
Sum: 1922364685.000000

real    40m15.857s

user    397m50.976s

sys     4m39.295s

**20 Nodes**

Node: 0 Numbers: 1.000000 - 3200001.000000                                                 
0 count is: 44799541.000000                                                                                           
Node: 1 Numbers: 3200000.000000 - 6400000.000000                                                                     
1 count is: 62066769.000000
Node: 2 Numbers: 6400000.000000 - 9600000.000000                                                                      
2 count is: 94404954.000000                                                                                           
Node: 3 Numbers: 9600000.000000 - 12800000.000000                                                                     
3 count is: 56862401.000000                                                                                           
Node: 4 Numbers: 12800000.000000 - 16000000.000000                                                                    
4 count is: 97773862.000000                                                                                          
Node: 5 Numbers: 16000000.000000 - 19200000.000000                                                                   
5 count is: 102797123.000000                                                                                          
Node: 6 Numbers: 19200000.000000 - 22400000.000000                                                                    
6 count is: 83486565.000000                                                                                           
Node: 7 Numbers: 22400000.000000 - 25600000.000000                                                                    
7 count is: 94333746.000000                                                                                           
Node: 8 Numbers: 25600000.000000 - 28800000.000000                                                                    
8 count is: 107389119.000000                                                                                          
Node: 9 Numbers: 28800000.000000 - 32000000.000000                                                                    
9 count is: 150762437.000000                                                                                          
Node: 10 Numbers: 32000000.000000 - 35200000.000000                                                                   
10 count is: 103918318.000000                                                                                         
Node: 11 Numbers: 35200000.000000 - 38400000.000000                                                                   
11 count is: 110178554.000000         
Node: 12 Numbers: 38400000.000000 - 41600000.000000                                                                   
12 count is: 77854485.000000                                                                                          
Node: 13 Numbers: 41600000.000000 - 44800000.000000                                                                   
13 count is: 42021720.000000                                                                                          
Node: 14 Numbers: 44800000.000000 - 48000000.000000                                                                   
14 count is: 136530213.000000                                                                                         
Node: 15 Numbers: 48000000.000000 - 51200000.000000                                                                   
15 count is: 98364279.000000                                                                                          
Node: 16 Numbers: 51200000.000000 - 54400000.000000                                                                   
16 count is: 156295419.000000                                                                                         
Node: 17 Numbers: 54400000.000000 - 57600000.000000                                                                   
17 count is: 56215914.000000                                                                                          
Node: 18 Numbers: 57600000.000000 - 60800000.000000                                                                   
18 count is: 59748234.000000                                                                                          
Node: 19 Numbers: 60800000.000000 - 64000000.000000                                                                   
19 count is: 186561032.000000

Sum: 1922364685.000000

real    22m56.424s

user    453m2.036s

sys     5m17.033s 

**24 Nodes**

## Problem 433: Steps in Euclid's Algorithm.

**Description**
Let E(x0, y0) be the number of steps it takes to determine the greatest common divisor of x0 and y0 with Euclid's algorithm. More formally:

x1 = y0, y1 = x0 mod y0

xn = y(n-1), y(n) = x(n-1) mod y(n-1)

E(x0, y0) is the smallest n such that y(n) = 0.

We have E(1,1) = 1, E(10,6) = 3 and E(6,10) = 4.

Define S(N) as the sum of E(x,y) for 1 ≤ x,y ≤ N.

We have S(1) = 1, S(10) = 221 and S(100) = 39826.

Find S(5·10^6).

**Approach**
In order to solve this problem, the first step was to understand and implement the Euclidean Algorithm for finding the GCD (greatest common divisor) of a number.  The algorithm is quite simple, and has a very nice recursive solution to it.  With a slight modification (adding a counter to track the number of steps taken in the algorithm), we were able to come up with a brute force solution.  Once we came up with our solution, we began parallelizing by splitting the range of numbers to different nodes.

**Solving the Problem**
Writing the algorithm was pretty simple, as it has a nice recursive solution to it.  Once that was finished, we needed to parallelize the code since the brute force method is astronomically slow.  The total number of calculations required is pretty insane for the brute force method: O(N^2 * logN).  The N^2 comes from the fact that x, y pairs span from (1, 1), (1, 2), ... (2, 1), (2, 2), ... (N, 1) ... (1, N) ... (N, N), and that for each unique pair, the Euclidean Algorithm requires O(log N) calculations.  To parallelize, we took the basic approach of splitting the inner loop into blocks (the y coord of the pairs) for the nodes to have a distributed amount, then we used MPI file views to have the nodes report the results to a datafile.  Once the nodes were all done, the root would reduce the local sums to the final result, and that would be both printed to the console and written to a file.  

**Results**
As of 10/11/20 @ 3:31PM, our brute force solution is still running.  We have tested many cases with various #'s of nodes, and various N's.  It has always been correct, and there is no way the final result we are still waiting is wrong.  We are having the nodes print results to a file so that when it is finished, even if the MPI_Reduce overflows, we can sum the 24 node results ourselves and not have to false results due to overflow.  With full confidence, I believe that my algorithm is complete and works, despite being pretty slow.

### What was Learned
This was certainly more than just a project.  It was a test of confidence, patience, and will.  
