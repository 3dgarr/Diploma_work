#include <iostream>
#include <mpi.h>

#define TAG_TASK 1
#define TAG_RESULT 2

// Interface representing common operations for processes
class IProcess {
public:
    virtual ~IProcess() {}
    virtual void run() = 0;
};

// Base class for processes
class Process : public IProcess {
protected:
    int rank;
    int size;
    const int N;

public:
    Process(int processRank, int processSize, int n)
        : rank(processRank), size(processSize), N(n) {}
};

// Master process class
class MasterProcess : public Process {
public:
    MasterProcess(int processRank, int processSize, int n)
        : Process(processRank, processSize, n) {}

    void run() override {
        for (int i = 1; i < size; ++i) {
            MPI_Send(&i, 1, MPI_INT, i, TAG_TASK, MPI_COMM_WORLD);
        }

        for (int i = 1; i < size; ++i) {
            int partial_result;
            MPI_Recv(&partial_result, 1, MPI_INT, i, TAG_RESULT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Received result from process " << i << ": " << partial_result << std::endl;
        }
    }
};

// Slave process class
class SlaveProcess : public Process {
public:
    SlaveProcess(int processRank, int processSize, int n)
        : Process(processRank, processSize, n) {}

    void run() override {
        int my_task;
        MPI_Recv(&my_task, 1, MPI_INT, 0, TAG_TASK, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int partial_result = 0;
        for (int i = 1; i <= N; ++i) {
            // Replace this with your actual task
            partial_result += my_task * i;
        }

        MPI_Send(&partial_result, 1, MPI_INT, 0, TAG_RESULT, MPI_COMM_WORLD);
    }
};

// Master-Slave System class
class MasterSlaveSystem {
public:
    MasterSlaveSystem(int argc, char** argv);
    ~MasterSlaveSystem();

    void run();

private:
    int rank;
    int size;
    const int N;
    IProcess* process;

    void createProcess();
};

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

void MasterSlaveSystem::run() {
    process->run();
}

MasterSlaveSystem::~MasterSlaveSystem() {
    delete process;
    MPI_Finalize();
}

int main(int argc, char** argv) {
    MasterSlaveSystem system(argc, argv);
    system.run();

    return 0;
}
