// Example program
#include "pch.h"
#include <iostream>
#include <string>
#include <omp.h>
#include <time.h>
using namespace std;

sum = 0;
#pragma omp parallel for shared(sum, a) reduction(+: sum)
for (auto i = 0; i < 10; i++)
{
    sum += a[i]
}