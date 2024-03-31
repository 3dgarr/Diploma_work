#ifndef PARALLELWORDCOUNTER_H
#define PARALLELWORDCOUNTER_H

#include <vector>
#include <string>

class ParallelWordCounter 
{
	private:
		std::vector<std::string> words;
		std::string filename;

	public:
		ParallelWordCounter(const std::vector<std::string>& words, const std::string& filename);

		std::vector<int> count();
};

#endif // PARALLELWORDCOUNTER_H
