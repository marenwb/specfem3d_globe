#!/bin/bash
#
# script to copy results from profiling to RESULTS folder in top directory
#
##########################################################################

currentdir=`pwd`

cd RESULTS/$1
mkdir RUN_$2
cd RUN_$2
mkdir OUTPUT_FILES

cd $currentdir 

cp $currentdir/OUTPUT_FILES/* $currentdir/RESULTS/$1/RUN_$2/OUTPUT_FILES/
cp $currentdir/report1.qdrep $currentdir/RESULTS/$1/RUN_$2/
cp $currentdir/report1.sqlite $currentdir/RESULTS/$1/RUN_$2/

echo results copied to specfem3d_globe/EXAMPLES/regional_Greece_small/RESULTS/RUN_$1/
