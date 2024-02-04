# ifndef MASTER_SLAVE_SYSTEM_HPP
# define MASTER_SLAVE_SYSTEM_HPP

# include <iostream>
# include <mpi.h>

class IProcess;


class MasterSlaveSystem {
public:
    MasterSlaveSystem(int argc, char** argv);
    ~MasterSlaveSystem();

    void run();

private:
    int rank;
    int size;
    const int N;
    IProcess* process;

    void createProcess();
};


#endif// MASTER_SLAVE_SYSTEM_HPP