#include "MasterProcess.hpp"
#include <mpi.h>
#include <iostream>

MasterProcess::MasterProcess(int processRank, int processSize, int n)
	: Process(processRank, processSize, n) {}


void MasterProcess::run() 
{
	for (int i = 1; i < size; ++i) {
		MPI_Send(&i, 1, MPI_INT, i, TAG_TASK, MPI_COMM_WORLD);
	}

	for (int i = 1; i < size; ++i) {
		int partial_result;
		MPI_Recv(&partial_result, 1, MPI_INT, i, TAG_RESULT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		std::cout << "Received result from process " << i << ": " << partial_result << std::endl;
	}
}