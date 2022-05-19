INC := -I${CUDA_HOME}/include
LIB := -L${CUDA_HOME}/lib64 -lcudart -lcuda

GCC = g++
NVCC = ${CUDA_HOME}/bin/nvcc

NVCCFLAGS = -O3 -arch=sm_35 --ptxas-options=-v -Xcompiler -Wextra -lineinfo

GCC_OPTS =-O3 -Wall -Wextra $(INC)

EXCFILE = vectoradd


all: clean compile

compile: Makefile
	$(NVCC) -o $(EXCFILE) vectoradd.cu $(LIB) $(NVCCFLAGS) 

clean:	
	rm -f *.o $(ANALYZE)


