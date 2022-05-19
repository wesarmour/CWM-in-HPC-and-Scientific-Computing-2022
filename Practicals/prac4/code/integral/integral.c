
/*

  integral.c  -- trapezoidal rule function integration: serial version

 */


# include <stdio.h>
# include <stdlib.h>
# include <math.h>


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
//     trapInt -- function for trapezoidal integration                 //
//                                                                     //
// ------------------------------------------------------------------- //

double trapInt (double a, double b, int N) {

  int    n;                     // interval iterator
  double h;                     // interval length
  double v;                     // integral value
  double x;                     // integral variable

  // interval length
  h = (b - a) / ((double) N);

  // initial and final point only count with weight half
  v = (f(a) + f(b)) / 2.0;

  // add the inner points
  for (n=1; n<=N-1; n++) {
    x = a + n*h;
    v = v + f(x);
  }

  // scale by the interval width
  v *= h;

  return v;
}


// -------------------------------------------------------------------- //
//                                                                      //
//     wall_clock_time -- wall clock time function                      //
//                                                                      //
// -------------------------------------------------------------------- //

double wall_clock_time (void) {

  # include <sys/time.h>
  # define MILLION 1000000.0

  double secs;
  struct timeval tp;

  gettimeofday (&tp,NULL);
  secs = (MILLION * (double) tp.tv_sec + (double) tp.tv_usec) / MILLION;
  return secs;

}


// ------------------------------------------------------------------- //
//                                                                     //
//                             M  A  I  N                              //
//                                                                     //
// ------------------------------------------------------------------- //

int main(void) {

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
  // ----- compute integral summing intervals 1 to N
  //

  // start time
  time_start = wall_clock_time ( );

  // evaluate the integral
  v = trapInt (a, b, N);

  // end time
  time_end = wall_clock_time ( );


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
