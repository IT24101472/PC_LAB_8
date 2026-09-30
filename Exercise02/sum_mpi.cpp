#include <cstdio>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long N = 10000000;

    long long chunk = N / size;
    long long start = rank * chunk + 1;
    long long end = (rank == size - 1) ? N : (rank + 1) * chunk;

    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    long long local_sum = 0;

    for (long long i = start; i <= end; i++)
    {
        local_sum += i;
    }

    long long total_sum = 0;

    MPI_Reduce(
        &local_sum,
        &total_sum,
        1,
        MPI_LONG_LONG,
        MPI_SUM,
        0,
        MPI_COMM_WORLD
    );

    double end_time = MPI_Wtime();
    double elapsed = end_time - start_time;

    double max_time;

    MPI_Reduce(
        &elapsed,
        &max_time,
        1,
        MPI_DOUBLE,
        MPI_MAX,
        0,
        MPI_COMM_WORLD
    );

    printf("Rank %d: %lld to %lld -> Local sum = %lld\n",
           rank, start, end, local_sum);

    if (rank == 0)
    {
        printf("Total sum = %lld\n", total_sum);
        printf("Execution time = %.8f seconds\n", max_time);
    }

    MPI_Finalize();
    return 0;
}
