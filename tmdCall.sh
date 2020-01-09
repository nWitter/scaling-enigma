#!/bin/bash
#########################
#

echo "Starting"

#./enigma_loop > enix.out &
./timingThread > tmdt.out &
wait
exit 0


