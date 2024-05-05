#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <omp.h>
#include "ParallelWordCounter.hpp"

int main(int argc, char* argv[]) 
{
    if (argc < 3) 
	{
        std::cerr << "Usage: ./search words.txt <num_threads>" << std::endl;
        return 1;
    }

	std::cout << "----------------------" << std::endl;
	std::cout << "|Open MP  Word Search|" << std::endl;
	std::cout << "----------------------\n" << std::endl;

    std::string file_name = argv[1];
    int num_threads = std::atoi(argv[2]);

    std::vector<std::string> words = {"the", "around", "graphics", "from", "by", "be", "any", "mount", "hello", "word"};

    double t1 = omp_get_wtime();

    ParallelWordCounter word_counter(words, file_name, num_threads);
    std::vector<int> counts = word_counter.count();

    double t2 = omp_get_wtime();

    for (size_t i = 0; i < words.size(); i++)
        std::cout << words[i] << ": " << counts[i] << std::endl;
    std::cout << std::endl;

    std::cout << "Time: " << (t2 - t1) * 1000 << "ms" << std::endl;

    return 0;
}
