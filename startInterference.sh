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
if [ "$SLURM_NTASKS" == "4" ]; then
	TASKDIST="100 100 100 100 100 100 100 100"
fi

echo $TASKDIST

./MPI_Manager $@ &
sleep 2
for i in 1 2 3 4 5
do
	$MATRIX_PATH $1 $TASKDIST > $2$i &
	sleep 60
done

exit