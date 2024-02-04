# ifndef SLAVE_PROCESS_HPP
# define SLAVE_PROCESS_HPP

#include "Process.hpp"

class SlaveProcess : public Process 
{
	public:
		SlaveProcess(int processRank, int processSize, int n);

		void run() override ;
};


# endif// SLAVE_PROCESS_HPP