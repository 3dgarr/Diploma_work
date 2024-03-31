#include "ParallelWordCounter.hpp"
#include "WordCounter.hpp"
#include <omp.h>

ParallelWordCounter::ParallelWordCounter(const std::vector<std::string>& words, const std::string& filename, int num_threads)
    :	wordsToSearch(words), 
		filename(filename), 
		num_threads(num_threads) 
{}

std::vector<int> ParallelWordCounter::count() 
{
    std::vector<int> counts(wordsToSearch.size(), 0);

    #pragma omp parallel for num_threads(num_threads)
    for (size_t i = 0; i < wordsToSearch.size(); i++) 
	{
        WordCounter word_counter(wordsToSearch[i], filename);
        counts[i] = word_counter.count();
    }

    return counts;
}
