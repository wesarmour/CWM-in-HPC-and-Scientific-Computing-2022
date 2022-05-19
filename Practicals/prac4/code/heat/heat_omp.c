
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef _OPENMP
#include "omp.h"
#endif

#define MAX( A, B ) ( (A) > (B) ? (A) : (B) )
#define PI 3.14159265358979323846264338327950288419716939937510582

int main( void ) {

  /* Example program to solve the heat equation in 1D in serial */

  double nu;
  double *u, *uo;
  double du, du_loc;
  double rms;

  int n, n_time_steps;
  int L;
  int j, t;

  /* Read in the input data */
  /* Note the problem size read in is the number of points we can vary
     We will need to increase it by 2 to allow space for the boundary points */
  printf( "How big is the problem?\n" );
  if( scanf( "%d", &n ) != 1 ) {
    printf( "Error when reading in the problem size\n" );
    exit( EXIT_FAILURE );
  }
  printf( "How many timesteps?\n" );
  if( scanf( "%d", &n_time_steps ) != 1 ) {
    printf( "Error when reading in the number of time steps\n" );
    exit( EXIT_FAILURE );
  }
  printf( "Value of nu (positive and less than 0.5)?\n" );
  if( scanf( "%lf", &nu ) != 1 ) {
      printf( "Error when reading in the calue of nu\n" );
      exit( EXIT_FAILURE );
  }
  if( nu > 0.5 || nu < 0.0 ) {
    printf( "Sorry, the scheme implemented is unstable for nu=%f\n", nu );
    printf( "Please try again with 0<=nu<=0.5\n" );
    exit( EXIT_FAILURE );
  }

  /* Set the length of the box */
  L = n + 1;

  /* Increase n to allow space for the boundary points, one at the start and 
     one at the end */
  n = n + 2;

  /* Allocate memory for the arrays */
  u  = malloc( n * sizeof( *u  ) );
  if( !u ) {
    printf( "Failed to allocate the array u" );
    exit( EXIT_FAILURE );
  }
  uo = malloc( n * sizeof( *uo ) );
  if( !uo ) {
    printf( "Failed to allocate the array u" );
    exit( EXIT_FAILURE );
  }
  
  /* Now set the boundary conditions and initial values. These values are chosen 
     so we can compare with an exact solution of the equation to check our solution is 
     correct */

  /* Set the boundary conditions, i.e. the edges.
     As these are set by the physics these should not be changed 
     again by the program */
  u [ 0     ] = 0.0;
  uo[ 0     ] = 0.0;
  u [ n - 1 ] = 0.0;
  uo[ n - 1 ] = 0.0;

  /* Initial values to be solved on the grid */
  /* ... */
  for( j = 1; j < n - 1; j++ ){
    u[ j ] = sin( j * PI / L );
  }

  /* All set up so now solve the equations at each time step*/

  /* Start of the parallel region - make sure that you enclose all the parallel
     stuff in braces !! */
#pragma omp parallel default( none ) private( t, j, du_loc ) shared( n, n_time_steps, nu, u, uo, du )
  {

    /* Time loop */
    for (t=0; t<n_time_steps; t++) {
      
      /* Store old solution */
#pragma omp for
      for (j=1; j<n-1; j++) {
	uo[j] = u[j];
      }
      
      /* Now solve the equation */

      /* du is used to track the maximum change in u */
      du = 0.0;
      /* Make sure the shared variable is set on all threads before we continue */
#pragma omp barrier
      /* C is a stupid language and has no min function. So simulate it for the openmp reduction
	 Do it this way to avoid a synchronisation of the loop at every iteration */
      du_loc = 0.0;
#pragma omp for
      for (j=1; j<n-1; j++) {
	/* Finite difference scheme */
	u[j] = uo[j] + nu*(uo[j-1]-2.0*uo[j]+uo[j+1]);
	/* Calculate the maximum change in u */
	du_loc = MAX( du_loc, fabs( u[ j ] - uo[ j ] ) );
      }
      /* Now find the maximum value of du across the threads */
#pragma omp critical
      {
	du = MAX( du, du_loc );
      }
      /* Make sure that all threads have the correct value of du */
#pragma omp barrier
      
      /* Occasionally report the maximum change as the temperature distribution 
	 relaxes */
      /* Make sure only thread zero does the printning - again using
	 conditional compilation to allow the program to compile when omp is NOT specified */
#ifdef _OPENMP
      if( omp_get_thread_num() == 0 ) {
#endif
	if( t%10 == 0 || t == n_time_steps - 1 )
	  printf( "At timestep %5i the maxmimum change in the solution is %-#14.8g\n",
		  t, du );
#ifdef _OPENMP
      }
#endif
	
    }

  }

  /* Check the solution against the exact, analytic answer */
  rms = 0.0;
  /* ... */
    for (j=1; j<n-1; j++) {
      du = u[ j ] - sin( j * PI / L ) *  exp( - n_time_steps * nu * PI * PI / ( L * L ) );
      rms += du*du;
    }
  printf( "The RMS error in the final solution is %-#14.8g\n", sqrt(rms/((double) n)) );

  return EXIT_SUCCESS;

}
