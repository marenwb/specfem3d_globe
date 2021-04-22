#!/bin/bash

###########################################################
# USER PARAMETERS

## 4 CPUs
CPUs=4

## Profiling option
USE_NSYS=false
USE_NCOMP=false
USE_NVPROF=true
###########################################################


BASEMPIDIR=`grep ^LOCAL_PATH DATA/Par_file | cut -d = -f 2 `

# script to run the mesher and the solver
# read DATA/Par_file to get information about the run
# compute total number of nodes needed
NPROC_XI=`grep ^NPROC_XI DATA/Par_file | cut -d = -f 2 `
NPROC_ETA=`grep ^NPROC_ETA DATA/Par_file | cut -d = -f 2`
NCHUNKS=`grep ^NCHUNKS DATA/Par_file | cut -d = -f 2 `

# total number of nodes is the product of the values read
numnodes=$(( $NCHUNKS * $NPROC_XI * $NPROC_ETA ))

if [ ! "$numnodes" == "$CPUs" ]; then
  echo "error: Par_file for $numnodes CPUs"
  exit 1
fi

mkdir -p OUTPUT_FILES

# backup files used for this simulation
cp DATA/Par_file OUTPUT_FILES/
cp DATA/STATIONS OUTPUT_FILES/
cp DATA/CMTSOLUTION OUTPUT_FILES/


##
## mesh generation
##
sleep 2

echo
echo `date`
echo "starting MPI mesher on $numnodes processors"
echo

mpirun -np $numnodes $PWD/bin/xmeshfem3D

# checks exit code
if [[ $? -ne 0 ]]; then exit 1; fi

echo "  mesher done: `date`"
echo

# backup important files addressing.txt and list*.txt
cp OUTPUT_FILES/*.txt $BASEMPIDIR/


##
## forward simulation
##

# set up addressing
#cp $BASEMPIDIR/addr*.txt OUTPUT_FILES/
#cp $BASEMPIDIR/list*.txt OUTPUT_FILES/

sleep 2

echo
echo `date`
echo starting run in current directory $PWD
echo

# profiling can be enabled or disabled setting variable at top of file
# nvtx requires paranoid level <2 which is not set; will be added to trace automatically because of mpi

if [ "$USE_NSYS" == true ]; then
	echo profiling using Nsight Systems
	nsys profile --trace=cuda,nvtx,osrt,mpi --cuda-memory-usage=true mpirun -np $numnodes $PWD/bin/xspecfem3D
elif [ "$USE_NCOMP" == true ]; then
	echo profiling using Nsight Compute
	sudo ncu --target-processes=all -f -o profile mpirun -np $numnodes $PWD/bin/xspecfem3D
elif [ "$USE_NVPROF" == true ]; then
	echo profiling using Nvprof
	nvprof --profile-child-processes mpirun -np $numnodes $PWD/bin/xspecfem3D
else
	echo running without profiling
	mpirun -np $numnodes $PWD/bin/xspecfem3D
fi

# checks exit code
if [[ $? -ne 0 ]]; then exit 1; fi

echo "finished successfully"
echo `date`

