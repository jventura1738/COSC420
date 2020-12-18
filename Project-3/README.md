# Traveling Salesman Problem: Simulated Annealing in Parallel.

by Justin Ventura & Blaine Mason

[ Python, MPI4PY, Jupyter Notebook. ]

### How to run:

<code>
x, y, z.
</code>

## Problem Description:

Imagine a salesman planning to market some product in various locations on some network (with only vertices at start).  His/her goal is to visit a set of some cities, and to do so such that he spends minimal time traveling (assume shorter distance is *always* optimal for simplicity).  This clearly becomes a problem easily solved with graph theory.  The idea is to formulate edges between all vertices with the following constraints:

- He want to start and end in the same city.
- He must visit each city exacly once.
- His goal is to travel minimal distance.

At first, this sounds like an easy problem: why not just brute force all possible networks that meet these requirements keeping track of the graph with minimal distance?  This is a valid solution, however unrealistic in a real world scenario where there may be a large number of cities.  This drastically would affect the computation required for this brute force method.  With $n$ cities, there are $n!$ possible permutations possible to calculate, which is a problem.  To put in perspective how 'bad' this algorithm would perform, note that just 12 cities would result in 479001600 possible configurations!  If you keep pushing N larger, you will very quickly reach a point where the algorithm would run astronomically longer than your lifetime (not even your great great great great grand kids would see it finish).  We have to come up with something better.

## A Possible Solution.

The idea of better simulation with the Monte-Carlo in this context is to start with some random configuration, calculate the distance.  Once this is done, the idea is to make a random change in the graph (in this case, change the path between two random nodes), then if the change decreases distance, then we 'greedily' choose that change as our new graph.  This repeats for some iterations.  That is the basic idea, but one can easily see the potential for getting trapped in a 'local minimum' in terms of distance.  So the solution is to introduce some probability and a metric of 'energy' (or temperature as the keyword 'anneal' suggests)!

## Simulated Annealing.

With the previous algorithm in mind, we can attempt to avoid these 'local minima' by now introducing a probability of accepting a move even if it worsens our solution.  However, this probability is not static; it will be based on some 'temperature.'  Say we set the initial temperature to be 90: now say we find a move that increases distance, instead of ignoring it, we randomly decide if we take it anyways with some probability.  The higher the temperature, the more likely we will be to take the new 'non-optimal' move.  Naturally, the temperature will decrease over time (iterations), so that we aren't randomly shuffling the graph over and over (this would be just as bad, if not worse, than the brute force method!) repeatedly with no 'intelligence.'  This repeats until we reach the designated final temperature.  This is better than $O(N!)$ for sure, but the drawback is that we are not guaranteed the optimal solution by the time the algorithm finishes.  While we are likely to have a close-to-optimal solution with high probability, can we possibily improve upon this?
