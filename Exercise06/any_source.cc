#include <cstdio>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int value;

    if (rank == 0)
    {
        value = 100;

        MPI_Send(
            &value,
            1,
            MPI_INT,
            2,
            0,
            MPI_COMM_WORLD
        );

        printf("Rank 0 sent %d to Rank 2\n", value);
    }

    else if (rank == 1)
    {
        value = 200;

        MPI_Send(
            &value,
            1,
            MPI_INT,
            2,
            0,
            MPI_COMM_WORLD
        );

        printf("Rank 1 sent %d to Rank 2\n", value);
    }

    else if (rank == 2)
    {
        MPI_Status status;

        for (int i = 0; i < 2; i++)
        {
            MPI_Recv(
                &value,
                1,
                MPI_INT,
                MPI_ANY_SOURCE,
                0,
                MPI_COMM_WORLD,
                &status
            );

            printf(
                "Rank 2 received %d from Rank %d\n",
                value,
                status.MPI_SOURCE
            );
        }
    }

    MPI_Finalize();
    return 0;
}
