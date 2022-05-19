#======================================================================#
#                                                                      #
#      name:     Makefile                                              #
#                                                                      #
#======================================================================#

# serial compiler
CC  = gcc

# MPI compiler wrapper
MPI_CC = mpicc

# flags
CFLAGS = -O3 -mavx -std=c99 -Wall -Wextra -pedantic
CFLAGS_OMP = -fopenmp

# libraries
LIBS = -lm

# rules
default:	all
all:    	heat heat_omp

heat:		heat.o
		$(CC) $(CFLAGS) -o heat heat.o $(LIBS)

heat_omp:	heat_omp.o
		$(CC) $(CFLAGS) $(CFLAGS_OMP) -o heat_omp heat_omp.o $(LIBS)


heat.o:		heat.c
		$(CC) $(CFLAGS) -c heat.c

heat_omp.o:	heat_omp.c
		$(CC) $(CFLAGS) $(CFLAGS_OMP) -c heat_omp.c

clean:
		/bin/rm -f *.o *.c~ *.h~ makefile~ heat heat_omp 

