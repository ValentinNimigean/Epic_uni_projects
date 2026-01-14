#include <mpi.h>
#include <iostream>
#include <unistd.h>
#include "dsm.h"

void handle_update(std::string var, int val) {
    int rank; MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::cout << "[Node " << rank << "] CALLBACK: " << var << " updated to " << val << std::endl;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != PREDEFINED_NODES) {
        if (rank == 0) {
            std::cerr << "ERROR: This system is predefined to run with " 
                      << PREDEFINED_NODES << " nodes. You started it with " 
                      << size << "." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    DSM dsm(rank, size);
    dsm.set_callback(handle_update);

    dsm.write("VAR_A", rank * 100);
    dsm.write("VAR_A", rank);
    

    for (int i = 0; i < 4000; ++i) {
        dsm.sync();

        if (i == 1000) {
            dsm.compare_and_exchange("VAR_B", 0, rank);
        }

      
        usleep(1000); 
    }

    
    for (int i = 0; i < size; ++i) {
        if (rank == i) {
            std::cout << "[Node " << rank << "] FINAL VALUES:" << std::endl;
            std::cout << "  VAR_A: " << dsm.read("VAR_A") << std::endl;
            std::cout << "  VAR_B: " << dsm.read("VAR_B") << std::endl;
            std::flush(std::cout);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    if (rank == 0) std::cout << "Simulation complete. Finalizing..." << std::endl;
    MPI_Finalize();
    return 0;
}