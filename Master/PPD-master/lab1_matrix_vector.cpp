// Example program
#include "pch.h"
#include <iostream>
#include <string>
#include <omp.h>
#include <time.h>
using namespace std;




int main()
{
	// Rows and columns
	int N = 1000;
	int M = 1000;

	// Define Matrix
	int *matrice;
	matrice = new int[N*M];
	
	// Result Vector
	int *res_vec;
	res_vec = new int[N];

	// Define Vector
	int *vector;
	vector = new int[N];

	// Initialise Matrix
	for (int i = 0; i < N; i++) {
		// Initialise Vector
		vector[i] = rand() %100;
		for (int j = 0; j < M; j++) {
			// Random values
			matrice[i*N + j] = rand() % 100;
		}
	}



	// set number of threads
	omp_set_num_threads(4);

	//CLOCK
	clock_t start, end;
	start = clock();

	// Print Vector
	#pragma omp parallel for
		for (int i = 0; i < N; ++i)
		{
			int thread_id = omp_get_thread_num();
			for (int j = 0; j < N; ++j)
			{
				// multiplication
				res_vec[i] += matrice[i*N+j] * vector[j];
			}
			cout << "\n";
			cout << "Thread id " << thread_id << "\n";

		}
	

	end = clock();
	cout << "Time required for execution: "
		<< (double)(end - start) / CLOCKS_PER_SEC
		<< " seconds." << "\n\n";
	return 0;
}
