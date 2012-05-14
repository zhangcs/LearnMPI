#include "mpi.h"
#include <stdio.h>

#define SIZEM 2
#define SIZEN 10

int main(int argc, char *argv[])
{
    // Purpose: To test BLOCKING send and recv, and collective scatter
    // Send each row of a from 0 to higher rank processors, each of which is stored in b
    // Then distribute rows of a to each processor!!!
 
    int numtasks, rank, ierr; 
    int tag = 1, i, j; 
    float a[SIZEM][SIZEN], b[SIZEN];

    MPI_Status stat;
    MPI_Datatype rowtype = 0;

    // Parallel part starts from here ...
    ierr = MPI_Init(&argc,&argv); // initialize MPI

    if ( ierr != MPI_SUCCESS ) {
        printf("Error starting MPI program. Terminating.\n");
        MPI_Abort(MPI_COMM_WORLD, ierr);
    }
  
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks); // get number of processes
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); // get my rank

    MPI_Type_contiguous(SIZEN, MPI_FLOAT, &rowtype);
    MPI_Type_commit(&rowtype);

    // Send rows of a matrix from proc 0 to the other proc's
    if ( numtasks == SIZEM ) {

        // Initialize matrix a on each processor
        for ( i=0; i<SIZEM; i++ ) {
            for ( j=0; j<SIZEN; j++ ) {
                a[i][j] = i * SIZEN + j;
            }
        }
        
        if ( rank == 0 ) {
            // Send data to higher rank processors
            for ( i=1; i<numtasks; i++ )
                MPI_Send(&a[i][0], 1, rowtype, i, tag, MPI_COMM_WORLD);
        }
        else {
            MPI_Recv(b, SIZEN, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, &stat);
        }

        for ( i=0; i<SIZEN; i++ ) {
            printf("Before scatter: rank = %d, b[%d] = %e\n", rank, i, b[i]);
        }

        // Scatter the matrix rows to each processors (including 0!!!)
        MPI_Scatter(a, SIZEN, MPI_FLOAT, b, SIZEN, MPI_FLOAT, 0, MPI_COMM_WORLD);

        for ( i=0; i<SIZEN; i++ ) {
            printf("After scatter: rank = %d, b[%d] = %e\n", rank, i, b[i]);
        }

    }

    else {
        printf("ERROR: Need %d processors!\n", SIZEN);
    }

    MPI_Type_free(&rowtype);
    MPI_Finalize(); // Finalize MPI
    // Parallel part ends now!

    return 0;
}
