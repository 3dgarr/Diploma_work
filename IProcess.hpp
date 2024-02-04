# ifndef IPROCESS_HPP
# define IPROCESS_HPP

#include <mpi.h>

#define TAG_TASK 1
#define TAG_RESULT 2

class IProcess 
{
	public:
		virtual ~IProcess() {}
		virtual void run() = 0;
};


# endif// IPROCESS_HPP