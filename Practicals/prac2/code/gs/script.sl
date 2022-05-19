#!/bin/bash
# set the number of nodes and processes per node
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1

# set max wallclock time
#SBATCH --time=00:10:00
#SBATCH --gres=gpu:1

# set name of job
#SBATCH --job-name gs

# Use this to set the order and number of vectors
rm -f in
echo 1000 >   in
echo 1000 >>  in

./gs < in

rm -f in
