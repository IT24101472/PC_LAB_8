#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const long long TOTAL_POINTS = 10000000;
    long long local_points = TOTAL_POINTS / size;

    if (rank == size - 1)
        local_points += TOTAL_POINTS % size;

    unsigned int seed = time(NULL) + rank;

    long long local_inside = 0;

    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    for (long long i = 0; i < local_points; i++)
    {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;

        if ((x * x + y * y) <= 1.0)
            local_inside++;
    }

    long long total_inside = 0;

    MPI_Reduce(
        &local_inside,
        &total_inside,
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

    if (rank == 0)
    {
        double pi = 4.0 * total_inside / TOTAL_POINTS;

        printf("Points inside circle = %lld\n", total_inside);
        printf("Calculated Pi = %.8f\n", pi);
        printf("Execution time = %.8f seconds\n", max_time);
    }

    MPI_Finalize();
    return 0;
}
