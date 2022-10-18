#!/bin/bash
# Job séquentiel
#
#SBATCH --job-name=JobSeq
#SBATCH -o JobSeq_%j.out
#SBATCH -e JobSeq_%j.err
#SBATCH --account=xxxx
#SBATCH --time=0-00:02:00
#SBATCH --ntasks=1

sleep 5
./helloworld.out
