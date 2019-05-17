// Example program
#include "pch.h"
#include <iostream>
#include <string>
#include <omp.h>
#include <time.h>
using namespace std;

float get_random_number(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}


int main()
{
	
	int counter = 0;
	int numbers = 10'000'000;

	const float a = -1.f;
	const float b = 1.f;
	const float cx = 0.f;
	const float cy = 0.f;
	const float radius = 1.f;
	float pi = 0.f;

	//CLOCK
	clock_t start, end;
	start = clock();
	#pragma omp parallel for
	{
		for (int i = 0; i < numbers; ++i)
		{
			float rand_x = get_random_number(a, b);
			float rand_y = get_random_number(a, b);

			float distance = sqrt((double)(rand_x - 0.0)*(rand_x - 0.0) + (rand_y - 0.0)*(rand_y - 0.0));
			if (distance < radius)
			{
				counter += 1;
			}

			// Estimating Pi
			pi = 4 * (counter / (float)(numbers));
		}
	}
	end = clock();
	cout << "Time required for execution: "
		<< (double)(end - start) / CLOCKS_PER_SEC
		<< " seconds." << "\n\n";
	cout << "Pi estimation ..\n" << pi;
	return 0;
}
