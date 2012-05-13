#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
 
  int  numtasks, rank, ierr; 

  printf ("Hello, World!\n");

  // Parallel part starts from here ...
  ierr = MPI_Init(&argc,&argv); // initialize MPI

  if (ierr != MPI_SUCCESS) {
    printf ("Error starting MPI program. Terminating.\n");
    MPI_Abort(MPI_COMM_WORLD, ierr);
  }
  
  MPI_Comm_size(MPI_COMM_WORLD,&numtasks); // get number of processes

  MPI_Comm_rank(MPI_COMM_WORLD,&rank); // get my rank

  if (rank !=0 ) {
    printf ("Hi! My rank is %d.\n",rank);
  }
  else {// rank == 0 
    printf ("Hi! My rank is %d. Altogether there are %d processors!\n", rank, numtasks);
  }

  MPI_Finalize(); // finalize MPI
  // Parallel part ends now!

  printf ("I am back again!\n");

  return 0;
}
