#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <mpi.h>
#include "ParallelWordCounter.hpp"

int main(int argc, char* argv[]) 
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 2) 
    {
        if (rank == 0) {
            std::cerr << "Usage: ./search words.txt" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    std::string file_name = argv[1];

    std::vector<std::string> words = {"the", "around", "graphics", "from", "by", "be", "any", "mount", "hello", "word"};

    double t1 = MPI_Wtime();

    ParallelWordCounter word_counter(words, file_name);
    std::vector<int> counts = word_counter.count();

    double t2 = MPI_Wtime();

    if (rank == 0) 
	{
		std::cout << "----------------------" << std::endl;
		std::cout << "|MPI       Word Search|" << std::endl;
		std::cout << "----------------------\n" << std::endl;
        for (size_t i = 0; i < words.size(); i++)
            std::cout << words[i] << ": " << counts[i] << std::endl;
        std::cout << std::endl;
        std::cout << "Time: " << (t2 - t1) * 1000 << "ms" << std::endl;
    }

    MPI_Finalize();

    return 0;
}
