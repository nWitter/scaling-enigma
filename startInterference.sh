#!/bin/bash
#########################
#
MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

echo $@
echo "starting"
./MPI_Manager $@ &
sleep 2

TSK="100"
if [[ $SLURM_NTASKS == "2" ]]; then
	TSK="100 100"
fi
if [[ $SLURM_NTASKS == "4" ]]; then
	TSK="100 100 100 100"
fi
if [[ $SLURM_NTASKS == "8" ]]; then
	TSK="100 100 100 100 100 100 100 100"
fi
if [[ $SLURM_NTASKS == "16" ]]; then
	TSK="100 100 100 100 100 100 100 100 100 100 100 100 100 100 100 100"
fi

$MATRIX_PATH $1 $TSK > $2

exit