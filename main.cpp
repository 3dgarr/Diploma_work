
#include <iostream>
#include <mpi.h>

#define TAG_TASK 1
#define TAG_RESULT 2

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        std::cerr << "This program requires at least 2 processes: one master and one slave." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    const int N = 100;

    if (rank == 0) {
        // Master process
        for (int i = 1; i < size; ++i) {
            // Send a task to each slave
            MPI_Send(&i, 1, MPI_INT, i, TAG_TASK, MPI_COMM_WORLD);
        }

        // Receive and process results from slaves
        for (int i = 1; i < size; ++i) {
            int partial_result;
            MPI_Recv(&partial_result, 1, MPI_INT, i, TAG_RESULT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Received result from process " << i << ": " << partial_result << std::endl;
        }
    } else {
        // Slave process
        int my_task;
        MPI_Recv(&my_task, 1, MPI_INT, 0, TAG_TASK, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Perform the task
        int partial_result = 0;
        for (int i = 1; i <= N; ++i) {
            // Replace this with your actual task
            partial_result += my_task * i;
        }

        // Send the partial result back to the master
        MPI_Send(&partial_result, 1, MPI_INT, 0, TAG_RESULT, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
