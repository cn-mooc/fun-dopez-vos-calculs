#!/bin/bash
#SBATCH --job-name=singularity       # name of job
#SBATCH --account=ici                # account name, please change with the account related with your login 
#SBATCH --ntasks=1                   # total number of processes (= number of GPUs here)
#SBATCH --hint=nomultithread         # hyperthreading is deactivated
#SBATCH --time=00:05:00              # maximum execution time requested (HH:MM:SS)
#SBATCH --output=resultat.out        # name of output file
#SBATCH --error=resultat.err         # name of error file (here, appended with the output file
#SBATCH --partition=gpus             # specify gpu partitin, this is a Liger partition please change on another infra
#SBATCH --nodelist=turing04          # specify a node, here this is a Liger Node please change on another infra
#SBATCH --gres=gpu:1                 # specify the type of gpu and the number, here this is a Liger gres config please change on another infra

# cleans out the modules loaded in interactive and inherited by default 
module purge

# load Singularity
module load singularity   

# echo of launched commands
set -x
echo "--- STARTED: `date`"

# check if we have GPUs running
nvidia-smi

singularity exec --nv --bind ./:/tmp/ /softs/singularity/containers/ai/ngc-tf2.3-fat_latest.sif python3 /tmp/mon_code.py

echo "--- ENDED: `date`"
