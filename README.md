# MPI Master-Slave Architecture

This project implements a basic Master-Slave architecture using MPI in C++. 
The master process distributes tasks to slave processes, collects their results, and performs any final processing.

## Prerequisites

- MPI library installed on your machine. You can use Open MPI or MPICH.

## Compilation

```bash
make
```
## Execution
```bash
mpirun -np 4 ./mpi_master_slave.exe
```

- **mpirun**:   This command is used to launch MPI applications.
- **-np <Number of processes>**: This option specifies the number of processes

