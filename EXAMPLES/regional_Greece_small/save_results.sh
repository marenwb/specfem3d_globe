#!/bin/bash
#
# script to copy results from profiling to PROFILING_RESULTS folder in top directory
#
##########################################################################

currentdir=`pwd`

cd PROFILING_RESULTS/$1
mkdir RUN_$2
cd RUN_$2
mkdir OUTPUT_FILES

cd $currentdir 

cp $currentdir/OUTPUT_FILES/* $currentdir/PROFILING_RESULTS/$1/RUN_$2/OUTPUT_FILES/
if [ "$3" = "systems" ]; then
	cp $currentdir/report1.qdrep $currentdir/PROFILING_RESULTS/$1/RUN_$2/
	rm -rf report1.qdrep
else
	cp $currentdir/profile.ncu-rep $currentdir/PROFILING_RESULTS/$1/RUN_$2/
	rm -rf profile.ncu-rep
fi

echo results copied to $currentdir/PROFILING_RESULTS/$1/RUN_$2/
