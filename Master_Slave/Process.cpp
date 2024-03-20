#include "Process.hpp"

Process::Process(int processRank, int processSize, int n)
	:	rank(processRank), 
		size(processSize), 
		N(n){}