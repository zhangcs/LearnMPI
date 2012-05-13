#include "mpi.h"
#include <stdio.h>

#define SIZEM 2
#define SIZEN 10

int main(int argc, char *argv[])
{
 
    int numtasks, rank, ierr; 
    int source = 0, tag = 1, i, j; 
    float a[SIZEM][SIZEN], b[SIZEM];

    MPI_Status stat;
    MPI_Datatype rowtype = 0;

    // Parallel part starts from here ...
    ierr = MPI_Init(&argc,&argv); // initialize MPI

    if (ierr != MPI_SUCCESS) {
        printf ("Error starting MPI program. Terminating.\n");
        MPI_Abort(MPI_COMM_WORLD, ierr);
    }
  
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks); // get number of processes
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); // get my rank

    MPI_Type_contiguous(SIZEN, MPI_FLOAT, &rowtype);
    MPI_Type_commit(&rowtype);

    // Send rows of a matrix from proc 0 to the other proc's
    if ( numtasks == SIZEM ) {

        if ( rank == 0 ) {
            // Initialize matrix a
            for ( i=0; i<SIZEM; i++ ) {
                for ( j=0; j<SIZEN; j++ ) {
                    a[i][j] = j;
                }
            }
            // Send data to higher rank processors
            for ( i=1; i<numtasks; i++ )
                MPI_Send(&a[i][0], 1, rowtype, i, tag, MPI_COMM_WORLD);
        }
        else {
            MPI_Recv(b, SIZEN, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &stat);
        }

        for ( i=0; i<SIZEN; i++ ) {
            printf("rank = %d, b[%d] = %e\n", rank, i, b[i]);
        }

    }

    else {
        printf("ERROR: Need %d processors!\n", SIZEN);
    }

    MPI_Type_free(&rowtype);
    MPI_Finalize(); // finalize MPI
    // Parallel part ends now!

    return 0;
}
