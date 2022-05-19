
/*

  integral_omp.c  -- trapezoidal rule function integration: OpenMP version

 */


# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "omp.h"


// ------------------------------------------------------------------- //
//                                                                     //
//     f -- function to integrate                                      //
//                                                                     //
// ------------------------------------------------------------------- //

double f (double x) {
  return 2.0*sqrt(1.0-x*x);
}


// ------------------------------------------------------------------- //
//                                                                     //
//     trapInt_OMP -- function for trapezoidal integration             //
//                    (OpenMP threaded version)                        //
//                                                                     //
// ------------------------------------------------------------------- //

double trapInt_OMP (double a, double b, int N) {

  int    n;                      // interval iterator
  double h;                      // interval length
  double v;                      // integral value
  double x;                      // integral variable

  // complete the body of the function
  // ... //

  return v;
}


// ------------------------------------------------------------------- //
//                                                                     //
//                             M  A  I  N                              //
//                                                                     //
// ------------------------------------------------------------------- //

int main (void) {

  // main variables
  int    N;
  double a,b,v;

  // timing variables
  double time_start, time_end;


  //
  // ----- read input
  //
  printf ("Where should the integration start?\n");
  if( scanf  ("%lf", &a ) == EOF ) exit( EXIT_FAILURE );
  printf ("And where should the integration end?\n");
  if( scanf  ("%lf", &b ) == EOF ) exit( EXIT_FAILURE );
  printf ("And how many intervals should the area be divided into?\n");
  if( scanf  ("%d",  &N ) == EOF ) exit( EXIT_FAILURE );

  
  //
  // ----- integral calculation
  //
  // start time
  time_start = omp_get_wtime ( );

  // evaluate the integral
  v = trapInt_OMP (a, b, N);

  // end time
  time_end = omp_get_wtime ( );


  //
  // ----- print sum
  //
  printf(" process time      = %e s\n", time_end - time_start);
  printf(" value of integral = %e\n", v);

  return 0;
}

/*
  end
 */
