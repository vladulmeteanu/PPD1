
#include <iostream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void mat_mul(float *a, float *b, float *c, int N) 
{
    int row = blockIdx.x*blockDim.x + threadIdx.x;
    int col = blockIdx.y*blockDim.y + threadIdx.y;

    if (row < N && col < N) 
    {
        for (int i = 0; i < N; ++i) 
        {
            c[row*N + col] += a[row*N + i] * b[i*N + col];
        }
    }
}

__global__ void vec_mul(float *a, float *b, float *c, int N)
{
    int idx = blockDim.x*blockIdx.x+threadIdx.x;

    if (idx < N)
    {
        for (int i = 0; i < N; ++i)
        {
            c[idx] += a[i] * b[idx];
        }
    }
}

int main()
{
    int N = 1024;
    float *a_h, *a_d, *b_h,*b_d,*c_h,*c_d;
    float *va_h, *va_d, *vb_h, *vb_d, *vc_h, *vc_d;

    int size = N * N * sizeof(float);
    int v_size = N * sizeof(float);
    a_h = (float*)malloc(size);
    b_h = (float*)malloc(size);
    c_h = (float*)malloc(size);

    va_h = (float*)malloc(v_size);
    vb_h = (float*)malloc(v_size);
    vc_h = (float*)malloc(v_size);

    cudaMalloc((void**)&a_d, size);
    cudaMalloc((void**)&b_d, size);
    cudaMalloc((void**)&c_d, size);

    cudaMalloc((void**)&va_d, v_size);
    cudaMalloc((void**)&vb_d, v_size);
    cudaMalloc((void**)&vc_d, v_size);

    dim3 n_threads(32,32,1);
    dim3 n_blocks(32,32,1);
    dim3 v_threads(32, 1, 1);
    dim3 v_blocks(32, 1, 1);

    for(int i = 0; i < N; ++i) 
    {
        va_h[i] = 1;
        vb_h[i] = 1;
        for (int j = 0; j < N; ++j) 
        {
            a_h[i*N + j] = 1;
            b_h[i*N + j] = 1;
        }
    }

    cudaMemcpy(a_d, a_h, size, cudaMemcpyHostToDevice);
    cudaMemcpy(b_d, b_h, size, cudaMemcpyHostToDevice);
    cudaMemcpy(va_d, va_h, v_size, cudaMemcpyHostToDevice);
    cudaMemcpy(vb_d, vb_h, v_size, cudaMemcpyHostToDevice);

    mat_mul << <n_blocks, n_threads >> > (a_d, b_d, c_d, N);
    vec_mul << <v_blocks, v_threads >> > (va_d, vb_d, vc_d, N);

    cudaMemcpy(c_h, c_d, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(vc_h, vc_d, v_size, cudaMemcpyDeviceToHost);

    for (int i = 0; i < N; ++i)
    {
        std::cout << vc_h[i] << " ";
    }

   /* for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << c_h[i*N + j] << " ";
        }
        std::cout << std::endl;
    }*/

    return 0;
}
