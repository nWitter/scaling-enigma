#!/bin/bash
#########################
#
MATRIX_PATH=../chameleon-apps/applications/matrix_example/main


TASKDIST="100"
if [ "$SLURM_NTASKS" == "2" ]; then
	TASKDIST="100 100"
fi
if [ "$SLURM_NTASKS" == "4" ]; then
	TASKDIST="100 100 100 100"
fi

./MPI_Manager $@ &
#$MATRIX_PATH $1 $TASKDIST > $2 &

exit