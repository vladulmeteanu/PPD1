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

	// Define Matrix
	int *matrice;
	matrice = new int[N*M];
	
	// Result Vector
	int *res_vec;
	res_vec = new int[N];
	
	// Initialise Matrix
	for (int i = 0; i < N; i++) {
		// Initialise Vector
		vector[i] = 0; //putem sa punem orice altceva
		for (int j = 0; j < M; j++) {
			// Random values
			matrice[i*N + j] = i; //putem sa populam matricea cum vrem
		}
	}
	
	omp_set_num_threads(8);
	
#pragma omp parallel for
	for(int i =0; i < N; i++)
	{
		for(int j=0; j< M; j++)
		{
			res_vec[i] += matrice[i*N + j];
		}
	}	
	
	return 0;
}