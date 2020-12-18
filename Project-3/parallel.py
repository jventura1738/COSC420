import numpy as np
import matplotlib.pyplot as plt
import random as rand
import math
import copy
from itertools import permutations
from mpi4py import MPI
from tqdm import tqdm
import pickle

# Vertex Class
class Vertex:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def distance(self, other):
        d = np.sqrt((other.x - self.x)**2 + (other.y - self.y)**2)
        # print(f"The distance from {self} to {other} is {d}")
        return d

    def __repr__(self):
        return f"({self.x},{self.y})"

    def __getitem__(self, index):
        x = self.x
        y = self.y
        return x, y


# This Will be the Graph Class for the implementation of the
# Traveling Salesman Problem
class Graph:
    def __init__(self):
        self.nodes = []
        self.edges = []

    def add_node(self, node):
        if(node in self.nodes):
            return "You are adding a node that already exists you nerd."
        else:
            self.nodes.append(node)

    def add_edge(self, one, two):
        if((one, two) in self.edges):
            return "That edge already exists"
        else:
            self.edges.append((one, two, one.distance(two)))

    def __repr__(self):
        return f"Graph has nodes: {self.nodes} \nGraph has edges: {self.edges}"

    def plot(self):
        plt.plot(
            [self.nodes[i].x for i in range(0, len(self.nodes))],
            [self.nodes[i].y for i in range(0, len(self.nodes))],
            "bo")
        for i in range(0, len(self.edges)):
            plt.plot([self.edges[i][j].x for j in range(0, 2)],
                     [self.edges[i][j].y for j in range(0, 2)],
                     color="k")
        plt.savefig('test.png')
        plt.rcParams['figure.figsize'] = [15, 10]
        plt.show()

    def get_total_distance(self):
        total = 0
        for i in range(0, len(self.edges)):
            total += self.edges[i][2]
        return total

# A method to provide information about a tour given the nodes
def describe_tour(g, start):
    temp_graph = copy.deepcopy(g)
    tour = []
    for i in range(start, len(temp_graph.nodes) + start):
        if(i >= len(g.nodes)):
            tour.append(temp_graph.nodes[np.abs(len(temp_graph.nodes) - i)])
        else:
            tour.append(g.nodes[i])
    # print(tour)
    for i in range(0, len(tour)):
        if (i == len(tour) - 1):
            temp_graph.add_edge(tour[i], tour[0])
        else:
            temp_graph.add_edge(tour[i], tour[i+1])
    """
    for i in range(0, len(tour)):
        if(i == len(tour) - 1):
            print(f"{tour[i]} -> {tour[0]} \n")
        else:
            print(f"{tour[i]} -> ", end='')
    """
    temp_graph.plot()
    return temp_graph

# Calculates the total tour length
def get_distance(nodes):
    total = 0
    for i in range(0, len(nodes)):
        total += nodes[i - 1].distance(nodes[i])
    return total

# Brute force solution to TSP
def bf(nodes):
    min_length = get_distance(nodes)
    min_path = nodes
    for path in permutations(nodes):
        length = get_distance(path)
        if length < min_length:
            min_length = length
            min_path = path
    return min_path

# Serial SA Method
def anneal(nodes):
    initial_temp = 90
    final_temp = .1
    alpha = .995
    current_temp = initial_temp
    current_state = nodes
    solution = current_state
    while(current_temp > final_temp):
        neighbor = np.random.permutation(current_state)
        cost = get_distance(current_state) - get_distance(neighbor)
        if(np.random.uniform(0, 1) < np.exp(cost/current_temp)):
            solution = neighbor
        current_temp -= alpha
    return solution


# Annealing step for parallel implementation
def anneal_step(current_solution, best_solution, current_temp):
    new_solution = np.random.permutation(current_solution)
    delta = get_distance(current_solution) - get_distance(new_solution)
    if((delta > 0) or (np.random.uniform(0, 1) < np.exp((delta/current_temp)))
       ):
        current_solution = new_solution
        if(get_distance(new_solution) < get_distance(best_solution)):
            best_solution = new_solution
    return best_solution


def main():
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    world_size = comm.Get_size()
    if(rank == 0 and world_size == 1):
        verts = []
        n = int(input("Enter number of cities: "))
        for i in range(1, n+1):
            temp = Vertex(rand.randint(0,50+n), rand.randint(0,50+n))
            verts.append(temp)
        graph = Graph()
        for i in range(0,len(verts)):
            graph.add_node(verts[i])
        with open("test.txt", "wb") as fp:   #Pickling
            pickle.dump(verts, fp)
        print("Now run with nodes >= 3")
        return 0
    with open("test.txt", "rb") as fp:   # Unpickling
        verts = pickle.load(fp)
    sum_ = 0
    graph = Graph()
    for i in range(0, len(verts)):
        graph.add_node(verts[i])

    E = 5000
    L = int((5*E)/world_size)
    initial_solution = np.random.permutation(graph.nodes)
    current_solution = initial_solution
    best_solution = initial_solution
    t = 90
    current_temp = t
    if(rank == world_size - 1):
        pbar = tqdm(total=t)
    while(current_temp > .1):
        for i in range(1, L):
            best_solution = anneal_step(current_solution, best_solution, t)
            # print(best_solution)
        if(rank == 0):
            comm.isend(best_solution, 1)
        else:
            best_solution_rec = comm.recv(source=rank - 1)
            if(get_distance(best_solution_rec) < get_distance(best_solution)):
                best_solution = copy.deepcopy(best_solution_rec)
                current_solution = copy.deepcopy(best_solution_rec)
            if(rank < world_size - 1):
                comm.isend(best_solution, rank + 1)
        if(rank == world_size - 1):
            pbar.update(.995)
        current_temp -= .995
    if(rank == world_size - 1):
        pbar.close()
        pbar.clear()
    # Print Results
    if(rank == world_size - 1):
        anneal_ = Graph()
        for i in range(0, len(best_solution)):
            anneal_.add_node(best_solution[i])
        anneal_graph = describe_tour(anneal_, 0)
        print(anneal_graph.get_total_distance())


if __name__ == "__main__":
    main()
