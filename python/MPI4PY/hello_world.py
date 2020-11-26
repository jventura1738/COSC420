# Justin Ventura COSC420

"""

MPI4PY Testing File.

"""

import numpy as np      # Ol' Reliable.
from mpi4py import MPI  # Imports


# Main.
if __name__ == '__main__':
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    if rank == 0:
        print('Hello from the root node!')
    else:
        print(f'Hello from node {rank}!')

    if rank == 0:
        print(f'Pi is approx: {np.pi}')
