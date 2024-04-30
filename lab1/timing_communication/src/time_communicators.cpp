#include "mpi.h"
#include <iostream>
#include <unistd.h>

int main() {
    MPI_Init(nullptr, nullptr);
    
    int size;
    int my_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(size == 1) {
        throw std::logic_error("Number of processes == 1, please provide \
                                2 or more for correct functionality");
    }

    double start = 0;
    
    if(my_rank == 0) {
        start = MPI_Wtime();
        MPI_Send(&start, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);

        double end = MPI_Wtime();

        std::cout << "Time taken to send the message and unblock = " << end - start << std::endl;
    }
    else if(my_rank == 1) {
        MPI_Status stat;
        MPI_Recv(&start, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &stat);

        double end = MPI_Wtime();
        sleep(1);
        std::cout << "Time taken to recieve the message = " << end - start << std::endl; 
    }


    MPI_Finalize();
    return 0;
}
