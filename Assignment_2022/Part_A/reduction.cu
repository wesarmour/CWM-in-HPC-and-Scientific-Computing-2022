#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>


#define NUM_ELS 1024

__global__ void reduction(float *d_input, float *d_output)
{
    // Allocate shared memory

    __shared__  float smem_array[NUM_ELS];

    int tid = threadIdx.x;

    // first, each thread loads data into shared memory

    smem_array[tid] = d_input[tid];

    // next, we perform binary tree reduction

    for (int d = blockDim.x/2; d > 0; d /= 2) {
      __syncthreads();  // ensure previous step completed 
      if (tid<d)  smem_array[tid] += smem_array[tid+d];
    }

    // finally, first thread puts result into global memory

    if (tid==0) d_output[0] = smem_array[0];
}



////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////

int main( int argc, const char** argv) 
{
    int num_els, num_threads, mem_size;

    float *h_data;
    float *d_input, *d_output;

    // initialise card


    num_els     = NUM_ELS;
    num_threads = num_els;
    mem_size    = sizeof(float) * num_els;

    // allocate host memory to store the input data
    // and initialize to integer values between 0 and 1000

    h_data = (float*) malloc(mem_size);
      
    for(int i = 0; i < num_els; i++) {
        h_data[i] = ((float)rand()/(float)RAND_MAX);
    }

    // allocate device memory input and output arrays

    cudaMalloc((void**)&d_input, mem_size);
    cudaMalloc((void**)&d_output, sizeof(float));

    // copy host memory to device input array

    cudaMemcpy(d_input, h_data, mem_size, cudaMemcpyHostToDevice);

    // execute the kernel

    reduction<<<1,num_threads>>>(d_input,d_output);

    // copy result from device to host

    cudaMemcpy(h_data, d_output, sizeof(float), cudaMemcpyDeviceToHost);

    // check results

    printf("reduction error = %f\n",h_data[0]/NUM_ELS);

    // cleanup memory

    free(h_data);
    cudaFree(d_input);
    cudaFree(d_output);

    // CUDA exit -- needed to flush printf write buffer

    cudaDeviceReset();
}

