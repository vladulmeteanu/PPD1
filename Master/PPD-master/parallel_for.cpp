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
	int N = 10;
	int M = 10;

	// Define Vector 
	float *vector;
	vector = new float[N*M];

	// Inistialise Vector
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			// Random values
			vector[i*N + j] = rand() % 100;
		}
	}

	// set number of threads
	omp_set_num_threads(4);

	//CLOCK
	clock_t start, end;
	start = clock();

	// Print Vector
	#pragma omp parallel for
	{
		// current thread
		int thread_id = omp_get_thread_num();

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				//cout << vector[i]<<" ";
				cout << vector[i*N + j] << " ";
				

			}
			cout << "\n";
			cout << "Thread id " << thread_id << "\n";
		}
	}

	end = clock();
	cout << "Time required for execution: "
		<< (double)(end - start) / CLOCKS_PER_SEC
		<< " seconds." << "\n\n";
	return 0;
}
