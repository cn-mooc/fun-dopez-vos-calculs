#!/bin/bash
# Job MPI
#
#SBATCH -J JobMpi  
#SBATCH -o JobMpi-%j.out  
#SBATCH -e JobMpi-%j.err  
#SBATCH --time=0-00:60:00 
#SBATCH --ntasks=4
#SBATCH --ntasks-per-node=1 
 
#module purge
#module load intel intelmpi

srun ./helloworld_mpi.out
