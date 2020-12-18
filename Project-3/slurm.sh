#!/bin/sh

#SBATCH --job-name=SA  
#SBATCH --nodes=10
#SBATCH --ntasks-per-node=10
#SBATCH --mem=10gb
#SBATCH --time=20:00:00    # Time limit in the form hh:mm:ss
#SBATCH --output=out/%j.log

module load mpi/mpich-3.2-x86_64

time mpiexec python parallel.py
