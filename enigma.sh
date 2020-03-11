#!/bin/bash
##########################
#SBATCH --job-name=interference-test
#SBATCH -o ./eni%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --partition=mpp2_inter
#SBATCH --time=00:04:00
#
#
# Args: matrix_size, output file, interfNodePercentage, interferenceSlow
#


module load slurm_setup

#solved in program
export KMP_AFFINITY="scatter"
#export OMP_PROC_BIND=true
#export OMP_PLACES=cores

export I_MPI_PIN_DOMAIN=node
export I_MPI_PIN=1
export I_MPI_ADJUST_BARRIER=1

echo "tasks " $SLURM_NTASKS
echo "cores per task " $SLURM_CPUS_PER_TASK
echo "args: " $@

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

MPI_EXPORT_VARS='-genvlist PATH,CPLUS_INCLUDE_PATH,C_INCLUDE_PATH,CPATH,INCLUDE,LD_LIBRARY_PATH,LIBRARY_PATH,I_MPI_PIN,I_MPI_DEBUG,I_MPI_PIN_DOMAIN,I_MPI_TMI_NBITS_RANK,OMP_NUM_THREADS,OMP_PLACES,OMP_PROC_BIND,I_MPI_FABRICS,MIN_ABS_LOAD_IMBALANCE_BEFORE_MIGRATION,MIN_LOCAL_TASKS_IN_QUEUE_BEFORE_MIGRATION,MIN_REL_LOAD_IMBALANCE_BEFORE_MIGRATION,MAX_TASKS_PER_RANK_TO_MIGRATE_AT_ONCE,PERCENTAGE_DIFF_TASKS_TO_MIGRATE,I_MPI_ADJUST_BARRIER,KMP_AFFINITY'

#start interference in different thread
chmod +x startInterference.sh

mpiexec -n 8 ${MPI_EXPORT_VARS} ./startInterference.sh 700 output/8-7_8-$1-$2.out -a 8 -i $1 -f

echo "end"
exit 0