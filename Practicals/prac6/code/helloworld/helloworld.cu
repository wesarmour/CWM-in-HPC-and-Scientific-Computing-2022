// In this assignment you will write a basic kernel where every thread 
// will write out to console string "Hello world!".
// You will also initialize GPU using cudaSetDevice() and also launch
// your "Hello world" kernel.

#include <stdio.h>
#include <stdlib.h>
// we have to include few more things
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>

//----------------------------------------------------------------------
// TASK 2: Write a "Hello world" kernel
// 
// Remember that kernel is defined by __global__ and inside it looks like
// a serial code for CPU. For printing out to console you can use printf().

// write your kernel here

//----------------------------------------------------------------------

int main(void) {
  //----------------------------------------------------------------------
  // TASK 1: Initiate GPU using cudaSetDevice()
  //
  // You can also try to write a check if there is a device with that id,
  // so the code behaves nicely when it fails
  
  // write you GPU initialization here

  //----------------------------------------------------------------------

  
  
  //----------------------------------------------------------------------
  // TASK 3: execute your "Hello world" kernel on 1 block with 5 threads 
  //         using execution configuration syntax.
  // 
  // You may use whatever syntax version you prefer, a simplified one 
  // dimensional or full three dimensional call using dim3 data type.
  
  // execute your "Hello world" kernel here
  
  //----------------------------------------------------------------------
 
  cudaDeviceReset(); 
  return (0);
}
