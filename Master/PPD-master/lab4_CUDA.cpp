#include <stdio.h>
#include <iostream>
using namespace std;
//KERNEL DEFINE
// a - memory space in GPU
// n,m matrix size
const pi = 3.14f;
__global__ void kernel(float *a,float *b,int n,int m){

        int row = blockIdx.x*blockDim.x +threadIdx.x;
        int col = blockIdx.y*blockDim.y +threadIdx.y;
        if (row < N && col < M)
    {
        a[row*N + col] = powf(sinf(2*PI*row/N), 2) + powf(cosf(2*PI*col/M), 2);
        b[row*N + col] = powf(cosf(2 * PI*row / N), 2) + powf(sinf(2 * PI*col / M), 2);
    }
}
int main(){
    //Matrix Dimensions
    int n = 256;
    int m = 256;

    float* result;
    //Matrix
    float *a,*b;

    // Alocarea
    a = new float[n*m];
    b = new float[n*m];

    // Define vars for GPU
    float *aA,*bB,*cC;

    //CUDA ALLOC
    cudaMalloc((void**)&aA,n*m*sizeof(float));
    cudaMalloc((void**)&bB,n*m*sizeof(float));
    cudaMalloc((void**)&cC,n*m*sizeof(float));

    // Kernel config
    dim3 nThreadsPerBlock(32,32,1);
    dim3 nBlocks(n/32,m/32,1);

    //EXECUTIE
    kernel<<<nBlocks,nThreadsPerBlock>>>( aA,bB,cC n, m);
    // Device to Host
    cudaMemcpy(a,aA,n*m*sizeof(float), cudaMemcpyDeviceToHost);
    cudaMemcpy(b,bB,n*m*sizeof(float), cudaMemcpyDeviceToHost);

    for(int i = 0; i<n;i++){
        cout<<a[n*i+m]<<" ";
        cout<<b[n*i+m]<<" ";
    }
    return 0;
}