#include "ParallelWordCounter.hpp"
#include "WordCounter.hpp"

ParallelWordCounter::ParallelWordCounter(const std::vector<std::string>& words, const std::string& filename)
    : wordsToSearch(words), filename(filename)
{}

std::vector<int> ParallelWordCounter::count() 
{
    std::vector<int> counts(wordsToSearch.size(), 0);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int wordsPerProcess = wordsToSearch.size() / size;
    int startWord = rank * wordsPerProcess;
    int endWord = (rank == size - 1) ? wordsToSearch.size() : startWord + wordsPerProcess;

    // Create shared memory for storing counts
    int* sharedCounts = nullptr;
    MPI_Win win;
    MPI_Win_allocate_shared(sizeof(int) * wordsToSearch.size(), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &sharedCounts, &win);

    // Create word counter instance
    WordCounter word_counter(filename);

    // Count words and store counts in shared memory
    for (int i = startWord; i < endWord; i++) 
    {
        word_counter.setWord(wordsToSearch[i]);
        int count = word_counter.count();
        sharedCounts[i] = count;
    }

    // Synchronize shared memory
    MPI_Win_fence(0, win);

    // Gather counts from all processes
    MPI_Allreduce(MPI_IN_PLACE, sharedCounts, wordsToSearch.size(), MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // Copy shared counts to local vector
	if (rank == 0)
	{
		for (size_t i = 0; i < wordsToSearch.size(); i++) 
		{
			counts[i] = sharedCounts[i];
		}
	}
    // Release shared memory
    MPI_Win_free(&win);

    return counts;
}
