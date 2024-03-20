#include "MasterSlaveSystem.hpp"
#include "MasterProcess.hpp"
#include "SlaveProcess.hpp"

MasterSlaveSystem::MasterSlaveSystem(int argc, char** argv)
    : N(100), process(nullptr) {
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        std::cerr << "This program requires at least 2 processes: one master and one slave." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    createProcess();
}

void MasterSlaveSystem::createProcess() 
{
	if (rank == 0)
	{
	    process = new MasterProcess(rank, size, N);
	}
	else
	{
		process = new SlaveProcess(rank, size, N);
	}
}

void MasterSlaveSystem::run() 
{
    process->run();
}

MasterSlaveSystem::~MasterSlaveSystem() 
{
    delete process;
    MPI_Finalize();
}
