#!/bin/bash

#SBATCH --job-name=Matrix   
#SBATCH --ntasks=30
#SBATCH --mem=12gb
#SBATCH --time=00:05:00    # Time limit in the form hh:mm:ss
#SBATCH --output=out/%j.log

module load mpi/mpich-3.2-x86_64

# For a C MPI project
mpirun ~/Documents/Github/Shared/COSC420/LABS/LAB2/main 1000 1000 10000 1000 
