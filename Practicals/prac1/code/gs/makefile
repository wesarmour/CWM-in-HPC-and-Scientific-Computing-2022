.SUFFIXES: 
.SUFFIXES: .f90 .c

PROG =	gs

SRCS =	array_alloc.c gs_opt.c timer.c

OBJS =	array_alloc.o gs_opt.o timer.o

LIBS =	-lm

CC = icc
CFLAGS = -O0
LDFLAGS = 

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f $(PROG) $(OBJS) *.mod

.SUFFIXES: $(SUFFIXES) .f90

.f90.o:
	$(F90) $(F90FLAGS) -c $<

gs_base.o: array_alloc.h timer.h
