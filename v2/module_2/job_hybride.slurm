#!/bin/bash
 
#SBATCH -J JobHybrid  
#SBATCH -o JobHybrid_%j.out  
#SBATCH -e JobHybrid_%j.err  
#SBATCH --account=xxxx
#SBATCH -t 0-00:10:00 
#SBATCH --ntasks=4 
#SBATCH --ntasks-per-node=2
#SBATCH --cpus-per-task=12 

#module purge
#module load intel intelmpi

if [ -n "$SLURM_CPUS_PER_TASK" ]; then
  omp_threads=$SLURM_CPUS_PER_TASK
else
  omp_threads=1
fi
export OMP_NUM_THREADS=$omp_threads


nc=$(printf "%07d" ${SLURM_NTASKS})
nt=$(printf "%03d" ${SLURM_CPUS_PER_TASK})
srun ./helloworld_hybride.out &> out_${nc}c_${nt}t_${SLURM_JOB_ID}.txt 
