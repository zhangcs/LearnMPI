#PBS -l nodes=2:ppn=2
#PBS -l walltime=0:10:00
#PBS -j oe
#PBS -q lionxc-math

# change the current working directory to the directory where
# the executable file
cd ~/prog/mpi


echo "------------------------------------------------------"
echo "PBS: job started on `hostname`"
echo "PBS: starting time: `date`"
echo "PBS: qsub is running on" $PBS_O_HOST
echo "PBS: originating queue is" $PBS_O_QUEUE
echo "PBS: executing queue is" $PBS_QUEUE
echo "PBS: working directory is" $PBS_O_WORKDIR
echo "PBS: execution mode is"s $PBS_ENVIRONMENT
echo "PBS: job identifier is" $PBS_JOBID
echo "PBS: job name is" $PBS_JOBNAME
echo "------------------------------------------------------"
echo " "

# run the executable file
mpirun ./mmult

echo " "
echo "------------------------------------------------------"
echo "PBS: job finished on `hostname`"
echo "PBS: end time: `date`"
echo "------------------------------------------------------"
