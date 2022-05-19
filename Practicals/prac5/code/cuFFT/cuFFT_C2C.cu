
#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>

// We have to include cuFFT library
#include <cufft.h>

#define NX 256
#define BATCH 1

// cuFFT can do 1D, 2D and 3D Fourier transformations using fast Fourier transform (FFT) algorithm.
// cuFFT is also very flexible regarding input data format. This can be captured together with type
// of FFT transformation we are interested in by cuFFT plan. The cuFFT plan could be created by many
// different functions provided by NVIDIA, where the most advance is 'cufftPlanMany'. In this 
// assignment we will use much simpler function. This is 'cufftPlan1d' which is only for one dimensional
// ffts.

void Do_FFT_C2C_forward(cufftComplex *d_fft_output, cufftComplex *d_input_data, int size_of_one_fft, int number_of_ffts){
	// We first declare cuFFT plan, which we must create before executing any FFT. We also
	// declare variable 'error' which is used to catch errors.
	cufftHandle plan;
	cufftResult error;
	
	// Here we are creating cuFFT plan, where we state what kind of transform we want.
	// In this case we are doing transformation from complex numbers to complex numbers. 
	// To tell this to cuFFT we need to pass CUFFT_C2C parameter to the cufftPlan1d. 
	// Parameters we pass to the 'cufftPlan1d' are:
	// 'plan' - is a variable where cufft stores parameters about fft we want to perform.
	// 'size_of_one_fft' - is size of one FFT we want to perform
	// 'type' - we are using CUFFT_C2C, but there are other options. CUFFT_C2R or CUFFT_R2C where R mean real and C means complex numbers
	// 'number_of_ffts' - tells cuFFT how many fft of size 'size_of_one_fft' we want to calculate.
	//
	// This plan is independent on any data, provided that data size does not change, we can create one plan
	// and use it many times
	error = cufftPlan1d(&plan, size_of_one_fft, CUFFT_C2C, number_of_ffts);
	if (CUFFT_SUCCESS != error){
		printf("CUFFT error: Plan creation failed");
		return;	
	}
	
	// This calls a function which performs fft on GPU. It is a C wrapper around
	// GPU kernel. This way user does not need to decide what number of threads 
	// and blocks should be used, cuFFT does it on its own.
	//
	// cufftExecC2C is also configurable. We can ask it to perform a forward ffts
	// by passing parameter CUFFT_FORWARD. This means we are transforming our series
	// from time-domain to frequency-domain. If we want to perform inverse transformation
	// (from frequency-domain to time-domain) we need to pass CUFFT_INVERSE.
	//
	// cuFFT can also calculate fft in-place, meaning that input array is used
	// for output as well. 
	cufftExecC2C(plan, d_input_data, d_fft_output, CUFFT_FORWARD);
	
	// This deallocate resources taken by the cuFFT plan
	cufftDestroy(plan);
}

//------------------------------------------------
// TASK: write a function which will perform 1D FFT using cuFFT, as in function
// 'Do_FFT_C2C_forward', which will calculate inverse fft and it will calculate
// it in-place.
void Do_FFT_C2C_inverse_inplace(cufftComplex *d_fft_in_out, int size_of_one_fft, int number_of_ffts){
    //write your function here

}


int main(void) {
	int size_of_one_fft = 16;
	int number_of_ffts  = 1;
	size_t size = size_of_one_fft*number_of_ffts;
	
	// device initialization
	int deviceid = 0;
	int devCount;
	cudaGetDeviceCount(&devCount);
	if(deviceid<devCount) cudaSetDevice(deviceid);
	else return(1);
	
	// declare, allocate and initiate host
	cufftComplex *h_input_data, *h_fft_output;
	h_input_data = (cufftComplex *) malloc(size*sizeof(*h_input_data));
	h_fft_output = (cufftComplex *) malloc(size*sizeof(*h_fft_output));
	
	for(int f=0; f<size_of_one_fft; f++){
		h_input_data[f].x = sin(4.0*31.25*((float) f));
		h_input_data[f].y = 0;
	}
	
	
	// data type used by cuFFT library.
	// it is in fact float2 which means { {float,float} , {float,float} , ... }
	cufftComplex *d_input_data, *d_fft_output;
	cudaMalloc((void**)&d_input_data, size*sizeof(cufftComplex));
	cudaMalloc((void**)&d_fft_output, size*sizeof(cufftComplex));
	// if you have data in a float2 array you can do (cufftComplex *) your_array
	
	// transfer data to the device
	cudaMemcpy(d_input_data, h_input_data, size*sizeof(cufftComplex), cudaMemcpyHostToDevice);
	// call function which will do FFT
	Do_FFT_C2C_forward(d_fft_output, d_input_data, size_of_one_fft, number_of_ffts);
	// transfer transformed series back to host
	cudaMemcpy(h_fft_output, d_fft_output, size*sizeof(cufftComplex), cudaMemcpyDeviceToHost);
	
	printf("Result of FFT transform:\n");
	for(int f=0; f<size_of_one_fft; f++){
		printf("[%0.3f] ",h_fft_output[f].x*h_fft_output[f].x + h_fft_output[f].y*h_fft_output[f].y);
	}
	printf("\n--------------\n");
	
	
	// Let's perform inverse transformation of the result from previous transformation.
	// Furthermore, we can do fft inplace. This means that fft can write results of them
	// transformation into input array.
	Do_FFT_C2C_inverse_inplace(d_fft_output, size_of_one_fft, number_of_ffts);
	cudaMemcpy(h_fft_output, d_fft_output, size*sizeof(cufftComplex), cudaMemcpyDeviceToHost);
	
	printf("Difference between initial input and current output:\n");
	for(int f=0; f<size_of_one_fft; f++){
		// cuFFT calculates non-normalized fft, this means that ifft(fft(X))=N*X, where N is fft size
		// this is why we need to divide cuFFT results by size_of_one_fft
		printf("[%0.3f,%0.3f] ", h_fft_output[f].x/16.0 - h_input_data[f].x, h_fft_output[f].y/16.0 - h_input_data[f].y);
	}
	printf("\n--------------\n");	
	
	// device deallocations
	cudaFree(d_input_data);
	cudaFree(d_fft_output);
	
	// host deallocation
	free(h_input_data);
	free(h_fft_output);
	
	cudaDeviceReset();
	return(0);
}
