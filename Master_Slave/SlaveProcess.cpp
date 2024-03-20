#include "SlaveProcess.hpp"

SlaveProcess::SlaveProcess(int processRank, int processSize, int n)
	: Process(processRank, processSize, n) {}


void SlaveProcess::run()
{
	int my_task;
	MPI_Recv(&my_task, 1, MPI_INT, 0, TAG_TASK, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	int partial_result = 0;
	for (int i = 1; i <= N; ++i) 
	{
		// Simulate some work

		partial_result += my_task * i;
	}

	MPI_Send(&partial_result, 1, MPI_INT, 0, TAG_RESULT, MPI_COMM_WORLD);
}