
INC	:= -I$(CUDA_HOME)/include -I.
LIB	:= -L$(CUDA_HOME)/lib64 -lcudart -lcublas -lcufft

NVCCFLAGS	:= -lineinfo -arch=sm_35 --ptxas-options=-v --use_fast_math

all:		simpleCUBLAS simpleCUFFT simpleCUFFT_interesting

simpleCUBLAS:	simpleCUBLAS.cpp Makefile
		g++ simpleCUBLAS.cpp -o simpleCUBLAS $(INC) $(LIB)

simpleCUFFT:	simpleCUFFT.cu Makefile
		nvcc simpleCUFFT.cu -o simpleCUFFT $(INC) $(NVCCFLAGS) $(LIB)

simpleCUFFT_interesting:    simpleCUFFT_interesting.cu Makefile
		nvcc simpleCUFFT_interesting.cu -o simpleCUFFT_interesting $(INC) $(NVCCFLAGS) $(LIB)

clean:
		rm -f simpleCUBLAS simpleCUFFT simpleCUFFT_interesting
