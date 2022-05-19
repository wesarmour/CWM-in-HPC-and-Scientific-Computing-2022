#!/bin/bash

#SBATCH --nodes=1
#SBATCH --ntasks-per-node=16
#SBATCH --time=00:05:00
#SBATCH --job-name=heat

module purge
module load gcc/4.9.2

./heat < heat.inp
