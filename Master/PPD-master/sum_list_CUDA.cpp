__global__ void sum( float *data, float *data_output, intsize ) { 
__shared__ float sdata[BLOCK_SIZE]; 
unsigned intindex = blockIdx.x* blockDim.x+ threadIdx.x; unsigned inttid= threadIdx.x;
if( index >= size ) return;
sdata[tid] = data[index];
 __syncthreads(); 
 if( tid== 0 ) {
  for( unsigned inti= 1; i< blockDim.x; i++ ) {
   sdata[tid] += sdata[i];
    } 
    data_output[ blockIdx.x] = sdata[0];
}
}