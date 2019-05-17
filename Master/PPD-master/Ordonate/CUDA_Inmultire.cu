#include <iostream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

//inmultirea a doua matrici
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

//inmultirea a doi vectori
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

//inmultirea unei matrici cu un vectori
__global__ void mat_vec(float *a, float *b, float *c, int N)
{
	int idx = blockIdx.x*blockDim.x + threadIdx.x;
    int col = blockIdx.y*blockDim.y + threadIdx.y;
	
	if (idx) 
	{
		for(int i=0;i<N;++i)
			c[idx]+=a[idx*N+ i] * b[idx];
	}
} 

int main()
{
    int N = 1024;
    float *a_h, *a_d, *b_h,*b_d,*c_h,*c_d; //declararea matricilor pe host si device
    float *va_h, *va_d, *vb_h, *vb_d, *vc_h, *vc_d; //declararea vectorilor pe host si device
	float *ma_h, *ma_d, *mb_h, *mb_d, *mc_h, *mc_d; //declararea vectorilor pe host si device

//alocarea in memorie pe host si device
    int size = N * N * sizeof(float);
    int v_size = N * sizeof(float);
	int m_size = N * sizeof(float);
	
    a_h = (float*)malloc(size);
    b_h = (float*)malloc(size);
    c_h = (float*)malloc(size);

    va_h = (float*)malloc(v_size);
    vb_h = (float*)malloc(v_size);
    vc_h = (float*)malloc(v_size);
	
	ma_h= (float*)malloc(size);
	mb_h= (float*)malloc(size);
	mc_h= (float*)malloc(size);
	

    cudaMalloc((void**)&a_d, size);
    cudaMalloc((void**)&b_d, size);
    cudaMalloc((void**)&c_d, size);

    cudaMalloc((void**)&va_d, v_size);
    cudaMalloc((void**)&vb_d, v_size);
    cudaMalloc((void**)&vc_d, v_size);
	
	cudaMalloc((void**)&ma_d, m_size);
    cudaMalloc((void**)&mb_d, m_size);
    cudaMalloc((void**)&mc_d, m_size);
	

//initializarea numarului de threaduri si blocks
    dim3 n_threads(32,32,1);
    dim3 n_blocks(32,32,1);
    dim3 v_threads(32, 1, 1);
    dim3 v_blocks(32, 1, 1);
	dim3 m_threads(32,1,1); 
	dim3 m_blocks(32,1,1); //block(N/32,M/32,1) - inmultite valorile de la thread si block trebuie sa dea nr. de pixeli care imi trebuie mie

//popularea vectorilor si matricilor
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

//copierea de pe host pe device a datelor
    cudaMemcpy(a_d, a_h, size, cudaMemcpyHostToDevice);
    cudaMemcpy(b_d, b_h, size, cudaMemcpyHostToDevice);
    cudaMemcpy(va_d, va_h, v_size, cudaMemcpyHostToDevice);
    cudaMemcpy(vb_d, vb_h, v_size, cudaMemcpyHostToDevice);

//apelarea functiilor de inmultire
    mat_mul << <n_blocks, n_threads >> > (a_d, b_d, c_d, N);
    vec_mul << <v_blocks, v_threads >> > (va_d, vb_d, vc_d, N);
	mat_vec << <m_blocks, m_threads >> > ();
//copierea de pe device pe host a matricii/vectorului rezultant
    cudaMemcpy(c_h, c_d, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(vc_h, vc_d, v_size, cudaMemcpyDeviceToHost);

//afisarea vectorului rezultant
    for (int i = 0; i < N; ++i)
    {
        std::cout << vc_h[i] << " ";
    }

//afisarea matricei rezultante
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << c_h[i*N + j] << " ";
        }
        std::cout << std::endl;
    }

//cuda cleanup
    free(a_h);
    free(b_h);
    free(c_h);
    cudaFree(a_d);
    cudaFree(b_d);
    cudaFree(c_d);
	
    return 0;
}

