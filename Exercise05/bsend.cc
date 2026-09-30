#include <cstdio>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int value = 100;

    int buffer_size = MPI_BSEND_OVERHEAD + sizeof(int);
    char buffer[buffer_size];

    MPI_Buffer_attach(buffer, buffer_size);

    if (rank == 0)
    {
        printf("Rank 0 buffered sending value %d to Rank 1\n", value);

        MPI_Bsend(
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
        MPI_Recv(
            &value,
            1,
            MPI_INT,
            0,
            0,
            MPI_COMM_WORLD,
            MPI_STATUS_IGNORE
        );

        printf("Rank 1 received value %d\n", value);
    }

    MPI_Buffer_detach(&buffer, &buffer_size);

    MPI_Finalize();
    return 0;
}
