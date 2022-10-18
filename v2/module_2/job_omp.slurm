#!/bin/bash
# Job OpenMP
#
#SBATCH -J JobOmp  
#SBATCH -o JobOmp_%j.out  
#SBATCH -e JobOmp-%j.err  
#SBATCH --account=xxxx
#SBATCH -t 0-00:10:00 
#SBATCH --ntasks=1 
#SBATCH --cpus-per-task=6 

#module purge
#module load intel
 
if [ -n "$SLURM_CPUS_PER_TASK" ]; then
  omp_threads=$SLURM_CPUS_PER_TASK
else
  omp_threads=1
fi
export OMP_NUM_THREADS=$omp_threads

nt=$(printf "%03d" ${SLURM_CPUS_PER_TASK})
./helloworld_omp.out &> out_${nt}t_${SLURM_JOB_ID}.txt 
