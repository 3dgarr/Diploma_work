#include "ParallelWordCounter.hpp"
#include "WordCounter.hpp"
#include <mpi.h>

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

    for (int i = startWord; i < endWord; i++) 
    {
        WordCounter word_counter(wordsToSearch[i], filename);
        counts[i] = word_counter.count();
    }

    // Gather counts from all processes
    std::vector<int> globalCounts(wordsToSearch.size(), 0);
    MPI_Allreduce(&counts[0], &globalCounts[0], wordsToSearch.size(), MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    return globalCounts;
}
