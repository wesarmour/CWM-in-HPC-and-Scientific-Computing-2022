INC := -I${CUDA_HOME}/include
# TASK: add cuFFT library into LIB variable
LIB := -L${CUDA_HOME}/lib64 -lcudart -lcuda -lcufft

GCC = g++
NVCC = ${CUDA_HOME}/bin/nvcc

NVCCFLAGS = -O3 -arch=sm_35 --ptxas-options=-v -Xcompiler -Wextra -lineinfo

GCC_OPTS =-O3 -Wall -Wextra $(INC)

EXCFILE = cuFFT_C2C


all: clean compile

compile: Makefile
	$(NVCC) -o $(EXCFILE) cuFFT_C2C.cu $(LIB) $(NVCCFLAGS) 

clean:	
	rm -f *.o $(ANALYZE)


