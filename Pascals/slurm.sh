#!/bin/bash

#BATCH --job-name=Pascals   
#SBATCH --nodes=20
#SBATCH --ntasks-per-node=20
#SBATCH --mem=12gb
#SBATCH --time=10:00:00    # Time limit in the form hh:mm:ss
#SBATCH --output=out/%j.log

module load mpi/mpich-3.2-x86_64

# For a C MPI project
mpirun ~/Documents/Github/Shared/COSC420/Pascals/main 
