#!/bin/bash

###########################################################
# USER PARAMETERS

## 4 CPUs
CPUs=1

## Profiling option
## Note: NVPROF does not work with devices with compute capability 8.0 or higher 
USE_NSYS=true
USE_NCOMP=true
USE_NVPROF=false
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
	nsys profile --trace=cuda,nvtx,osrt,mpi --backtrace=dwarf --cuda-memory-usage=true --sampling-period=1000000 mpirun -np $numnodes $PWD/bin/xspecfem3D
elif [ "$USE_NCOMP" == true ]; then
	echo profiling using Nsight Compute
	sudo mpirun -np $numnodes --allow-run-as-root /usr/local/cuda-11.2/bin/ncu --target-processes all --kernel-id ::regex:^.*forward:"1|100|200|400|800|1000" --set full -f -o profile $PWD/bin/xspecfem3D
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

