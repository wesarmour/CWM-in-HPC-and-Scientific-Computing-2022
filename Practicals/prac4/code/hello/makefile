#======================================================================#
#                                                                      #
#      name:     Makefile                                              #
#                                                                      #
#======================================================================#

# serial compiler
CC  = gcc

# flags
CFLAGS = -std=c99 -Wall -Wextra -pedantic
CFLAGS_OMP = -fopenmp


# rules
default:	all

all:    	hello_omp

hello_omp:	hello_omp.o
		$(CC) $(CFLAGS) $(CFLAGS_OMP) -o hello_omp hello_omp.o

hello_omp.o:	hello_omp.c
		$(CC) $(CFLAGS) $(CFLAGS_OMP) -c hello_omp.c

.PHONY:		clean
clean:
		/bin/rm -f *.o *.c~ *.h~ makefile~ hello_mpi hello_omp
