#include <cstdio>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int value = 100;

    if (rank == 0)
    {
        printf("Rank 0 sending value to Rank 1\n");

        MPI_Send(
            &value,
            1,
            MPI_INT,
            1,
            0,
            MPI_COMM_WORLD
        );
    }
    else if (rank == 1)
    {
        printf("Rank 1 waiting for message from Rank 2...\n");

        MPI_Recv(
            &value,
            1,
            MPI_INT,
            2,          // MISMATCH: actual sender is Rank 0
            0,
            MPI_COMM_WORLD,
            MPI_STATUS_IGNORE
        );

        printf("Rank 1 received %d\n", value);
    }

    MPI_Finalize();
    return 0;
}
