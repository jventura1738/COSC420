#!/bin/sh

#SBATCH --job-name=Divisors   
#SBATCH --nodes=5
#SBATCH --ntasks-per-node=4
#SBATCH --mem=12gb
#SBATCH --time=20:00:00    # Time limit in the form hh:mm:ss
#SBATCH --output=out/%j.log

module load mpi/mpich-3.2-x86_64

# For a C MPI project
mpirun ~/Documents/Github/Shared/COSC420/Sum/main
