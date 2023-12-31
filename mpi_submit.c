#!/bin/bash
#SBATCH -N 1
#SBATCH -p GPU-shared
#SBATCH -t 0:30:00
#SBATCH --gpus=v100-32:2

#echo commands to stdout
set -x

cd /jet/home/sbrowne/CS4175/PA4
module load gcc/10.2.0
module load openmpi/4.0.5-gcc10.2.0 

for np in 1 2 4 8; do
    echo "Running with $np processes..."
    mpirun -n $np ./mvm 32000
done

echo "Job completed"
