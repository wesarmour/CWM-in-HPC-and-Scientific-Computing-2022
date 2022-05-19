// In this assignment you will see how different mapping of threads
// to data cab affect the performance. 
// 
// Your task is to write two kernels for vector addition each 
// accessing data differently and choose how many threads and blocs
// to use.
// 
// In your first kernel each thread will process M elements of the 
// resulting vector C. Each thread will access data with step 1. That
// is thread 0 of the first block will access data for C_0 up to C_(M-1).
// Next thread will access data for C_M up to C_(2*M-1) ... thread T 
// will access C_(thread_id*M) up to C_((thread_id+1)*M-1).

// In the second kernel threads will access elements with step M. 
// That is for thread 0: C_0, C_M, C_(2*M), ... ,C_((M-1)*M).
// In general threads with id i will access C_(f*M+i) for all 
// integers 0 < f < M.


// NOTE: You should finish your vector addition assignment first, before 
//       doing this one.

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>

#define M 32

//----------------------------------------------------------------------
// TASK 1: Write kernel for vector addition where threads access data with 
// step 1 and will calculate M elements of the vector C in total.
//
// To calculate the index of the data which given thread should operate
// on use pre-set variables threadIdx, blockIdx, blockDim and gridDim.



__global__ void vector_add_uncoalesced(float *d_C, float *d_A, float *d_B){
  // write your kernel here
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// TASK 2: Write kernel for vector addition where threads access data with 
// step M and will calculate M elements of the vector C in total.
//
// To calculate the index of the data which given thread should operate
// on use pre-set variables threadIdx, blockIdx, blockDim and gridDim.


// write your kernel here
__global__ void vector_add_coalesced(float *d_C, float *d_A, float *d_B){
  // write your kernel here

}
//----------------------------------------------------------------------







struct GpuTimer {
  cudaEvent_t start;
  cudaEvent_t stop;

  GpuTimer() {
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
  }

  ~GpuTimer() {
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
  }

  void Start() {
    cudaEventRecord(start, 0);
  }

  void Stop() {
    cudaEventRecord(stop, 0);
  }

  float Elapsed() {
    float elapsed;
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsed, start, stop);
    return elapsed;
  }
};




int main(void) {
  GpuTimer timer;
  size_t N = 67108864;
  
  float *h_A, *h_B, *h_C;

  h_A = (float*) malloc(N*sizeof(*h_A));
  h_B = (float*) malloc(N*sizeof(*h_B));
  h_C = (float*) malloc(N*sizeof(*h_C));
	
  for(size_t f=0; f<N; f++) {
    h_A[f] = f + 1.0;
    h_B[f] = f + 1.0;
    h_C[f] = 0;
  }

  int deviceid = 0;
  int devCount;
  cudaGetDeviceCount(&devCount);
  if(deviceid<devCount) cudaSetDevice(deviceid);
  else return(1);

  float *d_A, *d_B, *d_C;

  cudaMalloc(&d_A, N*sizeof(*d_A));
  cudaMalloc(&d_B, N*sizeof(*d_B));
  cudaMalloc(&d_C, N*sizeof(*d_C));
  
  cudaMemcpy(d_A, h_A, N*sizeof(*h_A), cudaMemcpyHostToDevice);
  cudaMemcpy(d_B, h_B, N*sizeof(*h_B), cudaMemcpyHostToDevice);
  
  timer.Start();
  for(int f=0; f<10; f++){
    //----------------------------------------------------------------------
    // TASK 3: Configure vector_add_coalesced. You must take into account
	//         how many elements are processed per thread
	
	// put your code here
	
	//----------------------------------------------------------------------
  }
  timer.Stop();
  printf("Vector addition with coalesced memory access execution time: %f\n", timer.Elapsed()/10.0);
  
  
  timer.Start();
  for(int f=0; f<10; f++){
    //----------------------------------------------------------------------
    // TASK 4: Configure vector_add_uncoalesced. You must take into account
	//         how many elements are processed per thread
	
	// put your code here
	
	//----------------------------------------------------------------------
  }
  timer.Stop();
  printf("Vector addition with uncoalesced memory access execution time: %f\n", timer.Elapsed()/10.0);

  cudaMemcpy(h_C, d_C, N*sizeof(float), cudaMemcpyDeviceToHost);
  
  if(N<10){
	  printf("Check:\n");
	  for(int f=0; f<10; f++){
		  printf("Is %f + %f = %f?\n", h_A[f], h_B[f], h_C[f]);
	  }
  }
  
  cudaFree(d_A);
  cudaFree(d_B);
  cudaFree(d_C);
  free(h_A);
  free(h_B);
  free(h_C); 
  
  return(0);
}

