#!/bin/bash
#########################
#

echo "Starting"

./timingThread > tmdt.out &
./enigma_loop > enix.out &
wait
exit 0


