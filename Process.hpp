# ifndef PROCESS_HPP
# define PROCESS_HPP

# include "IProcess.hpp" 

class Process : public IProcess 
{
	public:
		Process(int processRank, int processSize, int n);

	protected:
		int rank;
		int size;
		const int N;
};



# endif// PROCESS_HPP