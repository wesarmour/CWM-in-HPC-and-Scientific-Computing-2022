// In this assignment you will write a kernel for decimation of an integer 
// array by factor of two (which sums two neighbouring integer numbers into
// one). More description is in notes for this practical.

// Your tasks are:
// 1) to calculate decimation by factor of two using GPU and store 
//    the result to the host.
// 2) to calculate decimation by factor of four using GPU and store 
//    the result to the host.
// To do that you have to:
// 1) write the host code to manage memory, data initialization and data 
//    transfers
// 2) write GPU kernel which is appropriate for the tasks
// 3) configure grid for your GPU kernel

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>

int Compare_results(int *GPU_output, int *h_input, size_t size, int DIT_factor){
	int itemp;
	size_t half_size;
	int error = 0;
	int nErrors = 0;
	int cislo = 0;
	
	half_size = size/DIT_factor;
	for(size_t f=0; f<half_size; f++){
		itemp=0;
		for(int t=0; t<DIT_factor; t++){
			itemp = itemp + h_input[f*DIT_factor + t];
		}
		error = (GPU_output[f]-itemp);
		if(error!=0 && cislo<20) {
			printf("f: %d; error: %d; GPU: %d; CPU: %d\n", f, error, GPU_output[f], itemp);
			cislo++;
		}
		if(error!=0) nErrors++;
	}
	
	return(nErrors);
}

void Check_errors(int *GPU_sum2, int *GPU_sum4, int *h_input, size_t size){
	int nErrors = 0;
	printf("Checking result for sum of two elements...\n");
	nErrors = Compare_results(GPU_sum2, h_input, size, 2);
	if(nErrors>0) printf("Correct solution and your solution does not match!\n");
	else printf("Your solution is correct!\n");
	
	printf("Checking result for sum of four elements...\n");
	nErrors = Compare_results(GPU_sum4, h_input, size, 4);
	if(nErrors>0) printf("Correct solution and your solution does not match!\n");
	else printf("Your solution is correct!\n");	
}

//----------------------------------------------------------------------
// TASK: Write your decimation GPU kernel
// When writing your kernel think carefully what each thread needs to read
// and what is it writes out and to where.
// Also consider what other threads might be reading and writing and where.

// put your kernel here

//----------------------------------------------------------------------



int main(void) {
	// Size of the array
	size_t N = 67108864;
	// Declaration of arrays used in this practical
	int *h_GPU_sum2, *h_GPU_sum4, *h_input;
	
	// memory allocation
	h_GPU_sum2 = (int*) malloc(N*sizeof(*h_GPU_sum2));
	h_GPU_sum4 = (int*) malloc(N*sizeof(*h_GPU_sum4));
	h_input       = (int*) malloc(N*sizeof(*h_input));
	if(h_GPU_sum2==NULL || h_GPU_sum4==NULL || h_input==NULL) return(1);
	
	// initiate host data
	for(size_t f=0; f<N; f++) {
		h_input[f] = f;
	}
	
	//----------------------------------------------------------------------
	// TASK: Write host code
	// Do not forget to initialize the device.
	// Remember that configuration of your grid depends on how you have 
	// written your decimation kernel
	
	// finish the host code here
	
	
	//----------------------------------------------------------------------
	
	Check_errors(h_GPU_sum2, h_GPU_sum4, h_input, N);
	
	// free memory on the host and the device
	free(h_GPU_sum2);
	free(h_GPU_sum4);
	free(h_input);
	
	cudaDeviceReset();
	return (0);
}
