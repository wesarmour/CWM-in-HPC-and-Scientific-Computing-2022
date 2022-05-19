#======================================================================#
#                                                                      #
#      name:     Makefile                                              #
#                                                                      #
#======================================================================#

# serial compiler
CC  = gcc

# flags
CFLAGS = -O3 -mavx -std=c99 -Wall -Wextra -pedantic
CFLAGS_OMP = -fopenmp
LIB        = -lm

# includes
INCS =

# rules
default:	all

all:    	integral integral_omp

integral:	integral.c
		$(CC) $(INCS) $(CFLAGS) -o integral integral.c $(LIB) 

integral_omp:	integral_omp.c
		$(CC) $(INCS) $(CFLAGS) $(CFLAGS_OMP) -o integral_omp integral_omp.c $(LIB) 

clean:
		/bin/rm -f *.o *.c~ *.h~ makefile~ integral integral_mpi integral_omp
