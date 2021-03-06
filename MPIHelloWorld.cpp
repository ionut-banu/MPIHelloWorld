// MPIHelloWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mpi.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int p;			// number of processors
	int id;		// ID of processors
	int m, rec_m;		// adresses of the sent/received message sent by each processor
								//int ssucc, rsucc;
	MPI_Status status;

	MPI_Init(NULL, NULL);

	// Get the number of processors - Fundamental 
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	printf("Number of processors %d .", p);
	//Get the rank / id - Fundamental
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	printf("Processor id: %d .", id);

	m = 2 * id + 1;

	if (id % 2 == 0)
	{
		MPI_Send(&m, 1, MPI_INT, (id + 1) % p, 0, MPI_COMM_WORLD);
		MPI_Recv(&rec_m, 1, MPI_INT, (id - 1 + p) % p, 0, MPI_COMM_WORLD, &status);
	}
	else
	{
		MPI_Recv(&rec_m, 1, MPI_INT, (id - 1 + p) % p, 0, MPI_COMM_WORLD, &status);
		MPI_Send(&m, 1, MPI_INT, (id + 1) % p, 0, MPI_COMM_WORLD);
	}
	printf("Processor %d sent message %d and received message %d.",id, m, rec_m);
	MPI_Finalize();
}
