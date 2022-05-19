#!/bin/bash

#SBATCH --nodes=1
#SBATCH --ntasks-per-node=16
#SBATCH --time=00:05:00
#SBATCH --job-name=integral

module purge
module load gcc/4.9.2

export OMP_NUM_THREADS=16

./integral_omp < integral.inp
