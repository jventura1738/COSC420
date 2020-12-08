# This Will be the Graph Class for the implementation of the
# Traveling Salesman Problem
import matplotlib.pyplot as plt


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
        return f"Graph has nodes: {self.nodes} \n and edges: {self.edges}"

    def plot(self):
        plt.plot(
            [self.nodes[i].x for i in range(0, len(self.nodes))],
            [self.nodes[i].y for i in range(0, len(self.nodes))],
            "bo")
        print(len(self.edges))
        for i in range(0, len(self.edges)):
            plt.plot(self.edges[i][0].x, self.edges[i][1].y,
                     label=str(self.edges[i][2]))
        plt.show()
