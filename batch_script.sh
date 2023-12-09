#!/bin/bash

# Load OpenMPI module
/usr/share/Lmod/8.2.7/libexec/Log_modules load openmpi/4.0.5-gcc10.2.0

# Loop for different numbers of processes
for np in 1 2 4 8
do
    echo "Running with $np processes..."
    
    # Run matrix-vector multiplication with mpirun
    mpirun -n $np ./mvm 32000

    # Print completion message and time taken
    echo "Job completed"
done
