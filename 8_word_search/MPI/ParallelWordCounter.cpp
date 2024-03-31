#include "ParallelWordCounter.hpp"
#include "WordCounter.hpp"
#include <mpi.h>
#include <iostream>

ParallelWordCounter::ParallelWordCounter(const std::vector<std::string>& words, const std::string& filename)
    :	words(words), 
		filename(filename) 
{}

std::vector<int> ParallelWordCounter::count() 
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int words_per_process = words.size() / size;
    int extra_words = words.size() % size;

    std::vector<int> counts(words_per_process, 0);
    int start_index = rank * words_per_process;
    int end_index = start_index + words_per_process;
    if (rank < extra_words)
        end_index++;

    for (int i = start_index; i < end_index; i++) {
        WordCounter word_counter(words[i], filename);
        counts[i - start_index] = word_counter.count();
    }

    // Gathering all counts
    std::vector<int> all_counts(words.size());
    MPI_Gather(counts.data(), counts.size(), MPI_INT, all_counts.data(), counts.size(), MPI_INT, 0, MPI_COMM_WORLD);

    return all_counts;
}
