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
	#pragma omp parallel 
	{
		// iteration number
		int N = 10;

		// current thread
		int thread_id = omp_get_thread_num();

		// total threads
		int thread_len = omp_get_num_threads();
		cout << "Thread length is : "<<thread_len<<"\n";

		// loop start index
		int istart = thread_id * N / thread_len;
		// loop end index
		int iend = (thread_id + 1)*N / thread_len;
		for (int i = istart; i < iend; ++i)
		{
		
			//cout << vector[i]<<" ";
			cout << vector[i] << " ";
				

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
