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
	int *res_vec1;
	res_vec1 = new int[N];
	int *res_vec2;
	res_vec2 = new int [N];
	
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
		
		if(vector[j]%2==0)	//orice conditie, in cazul de fata se cauta numerele pare in vector
		{
			res_vec2[i]=vector[i];
			cout<<res_vec2[i]<<" ";
		}
		
		for (int j = 0; j < N; ++j)
		{
			if(matrice[i*N+j]%2==0) //orice conditie, in cazul de fata se cauta numerele pare in matrice
			{
				res_vec1[i]=matrice[i*N+j];
				cout<<res_vec[i]<< " ";
			}
			
		}
		cout << "Thread id " << thread_id << "\n";

	}
	
	return 0;
}