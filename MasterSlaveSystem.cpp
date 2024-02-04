#include "MasterSlaveSystem.hpp"


MasterSlaveSystem::MasterSlaveSystem(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        std::cerr << "This program requires at least 2 processes: one master and one slave." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
}

MasterSlaveSystem::~MasterSlaveSystem() {
    MPI_Finalize();
}

void MasterSlaveSystem::run() {
    if (rank == 0) {
        masterProcess();
    } else {
        slaveProcess();
    }
}

void MasterSlaveSystem::masterProcess() {
    for (int i = 1; i < size; ++i) {
        MPI_Send(&i, 1, MPI_INT, i, TAG_TASK, MPI_COMM_WORLD);
    }

    for (int i = 1; i < size; ++i) {
        int partial_result;
        MPI_Recv(&partial_result, 1, MPI_INT, i, TAG_RESULT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Received result from process " << i << ": " << partial_result << std::endl;
    }
}

void MasterSlaveSystem::slaveProcess() {
    int my_task;
    MPI_Recv(&my_task, 1, MPI_INT, 0, TAG_TASK, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int partial_result = 0;
    for (int i = 1; i <= N; ++i) {
        // Replace this with your actual task
        partial_result += my_task * i;
    }

    MPI_Send(&partial_result, 1, MPI_INT, 0, TAG_RESULT, MPI_COMM_WORLD);
}
