# ifndef MASTER_PROCESS_HPP
# define MASTER_PROCESS_HPP

#include "Process.hpp"

class MasterProcess : public Process 
{
	public:
		MasterProcess(int processRank, int processSize, int n);
		void run() override; 
};


# endif// MASTER_PROCESS_HPP