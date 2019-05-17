#include "pch.h"
#include <iostream>
#include <string>
#include <omp.h>
#include <time.h>
using namespace std;

int main(){
	int N = 10;
	int *vec_1 = new int[N];
	int *vec_2 = new int[N];
	int *res = new int[N];

	for (int i = 0; i < N; ++i)
	{
		vec_1[i] = rand() %10;
		vec_2[i] = rand() %10;
	}

	for (int i = 0; i < N; ++i)
	{
		res[i] = vec_1[i]+vec_2[i];
		cout<< vec_1[i] <<" + "<< vec_2[i] <<"\n";
		cout<< res[i] <<" ";
	}
	return 0;
}