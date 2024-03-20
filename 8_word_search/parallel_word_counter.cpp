#include "parallel_word_counter.hpp"
#include "word_counter.hpp"
#include <omp.h>

ParallelWordCounter::ParallelWordCounter(const std::vector<std::string>& words, const std::string& filename, int num_threads)
    : words(words), filename(filename), num_threads(num_threads) {}

std::vector<int> ParallelWordCounter::count() {
    std::vector<int> counts(words.size(), 0);

    #pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < words.size(); i++) {
        WordCounter word_counter(words[i], filename);
        counts[i] = word_counter.count();
    }

    return counts;
}
