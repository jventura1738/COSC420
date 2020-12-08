import numpy as np


class Vertex:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def distance(self, other):
        d = np.sqrt((other.x - self.x)**2 + (other.y - self.y)**2)
        print(f"The distance from {self} to {other} is {d}")
        return d

    def __repr__(self):
        return f"({self.x},{self.y})"

    def __getitem__(self, index):
        x = self.x
        y = self.y
        return x, y
