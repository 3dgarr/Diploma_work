# ifndef MASTER_SLAVE_SYSTEM_HPP
# define MASTER_SLAVE_SYSTEM_HPP

# include <iostream>
# include <mpi.h>

#define TAG_TASK 1
#define TAG_RESULT 2

class MasterSlaveSystem 
{
	public:
		MasterSlaveSystem(int argc, char** argv);
		~MasterSlaveSystem();

		void run();

	private:
		void masterProcess();
		void slaveProcess();

	private:
		int rank;
		int size;
		const int N = 100;
};


#endif// MASTER_SLAVE_SYSTEM_HPP