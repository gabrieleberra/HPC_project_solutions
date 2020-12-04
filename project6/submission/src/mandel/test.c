// testing stuf in MPI
#include <stdio.h>
#include <mpi.h>


int main (int argc, char *argv[])
{
    int my_rank, size;
    int send_buf, recv_buf;
    int ierr;

    MPI_Status  status;
    MPI_Request request;
    MPI_Comm comm;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    int gridSize[2] = {0,0};
    MPI_Dims_create(size, 2, gridSize);
    printf("Dim x: %i  and Dim y: %i \n", gridSize[1], gridSize[0] );

    int periods[2] = {1,1};
    MPI_Cart_create(MPI_COMM_WORLD, 2, gridSize, periods, 0, &comm);

    int coords[2];
    MPI_Cart_coords(comm, my_rank, 2, coords);
    printf("ProcID: %i has \nCoordiate x: %i and Coordinate y: %i \n", my_rank, coords[1], coords[0]);

    MPI_Comm_rank(comm, &my_rank);
    printf("I am MPI process %d.\n", my_rank);

    MPI_Finalize();
    return 0;
}
