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
	
	// Result constant
	int a = 0, b = 0;

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
	
	#pragma omp parallel for
	for (int i = 0; i < N; ++i)
	{
		int thread_id = omp_get_thread_num();
		
		b+=vector[i]; //suma elementelor din vectorul 1D
		
		for (int j = 0; j < N; ++j)
		{
			res_vec[i] += matrice[i*N+j]; //suma elementelor de pe o linie
			a+=matrice[i*N+j]; //suma elementelor din intreaga matrice
			cout<<res_vec[i]<< " "; //afisarea sumei elementelor de pe fiecare linie, sub forma de vector
		}
		cout << "Thread id " << thread_id << "\n";

	}
		
	cout<<a<<" "<<b; //afisarea sumei elementelor din matrice (a), respectiv din vector (b)
	
	end = clock();
	cout << "Time required for execution: "
		<< (double)(end - start) / CLOCKS_PER_SEC
		<< " seconds." << "\n\n";
	
	return 0;
}