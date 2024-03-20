#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <omp.h>
#include "parallel_word_counter.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: ./search words1.txt num_threads" << std::endl;
        return 1;
    }

    std::string file_name = argv[1];
    int num_threads = std::atoi(argv[2]);

    std::vector<std::string> words = {"the", "around", "graphics", "from", "by", "be", "any", "mount", "hello", "word"};

    double t1 = omp_get_wtime();

    ParallelWordCounter word_counter(words, file_name, num_threads);
    std::vector<int> counts = word_counter.count();

    double t2 = omp_get_wtime();

    for (int i = 0; i < words.size(); i++)
        std::cout << words[i] << ": " << counts[i] << std::endl;
    std::cout << std::endl;

    std::cout << "Time: " << (t2 - t1) * 1000 << "ms" << std::endl;

    return 0;
}
