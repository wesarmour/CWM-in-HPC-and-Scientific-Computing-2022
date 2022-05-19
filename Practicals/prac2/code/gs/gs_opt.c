
  /* 

     Program to demonstrate two Gram-Schmidt methods
     1) Modified Gram-Schmidt
     2) Iterated Classical Gram-Schmidt 

  */



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "array_alloc.h"
#include "timer.h"

double check_orthonorm( int, int, double ** );
void   modified_gs( int, int, double ** );
void   iterated_classical_gs( int, int, double ** );

int main( void ) {

  double **q, **q_copy;

  int n, m;
  int n_read;
  int i, j;

  /* Read in the input and check it */
  fprintf( stdout, "Order of Vectors?\n" );
  n_read = fscanf( stdin , "%i", &n );
  if( n_read != 1 ) {
    fprintf( stdout, "Failed to read in the order of the vectors\n" );
    return EXIT_FAILURE;
  }

  fprintf( stdout, "Number of Vectors?\n" );
  n_read = fscanf( stdin , "%i", &m );
  if( n_read != 1 ) {
    fprintf( stdout, "Failed to read in the number of vectors\n" );
    return EXIT_FAILURE;
  }

  if( m > n ) {
    fprintf( stdout, "Number of vectors must NOT be larger than the order of the vectors\n" );
    return EXIT_FAILURE;
  }
  
  /* Allocate vectors */
  q = alloc_2d_double( m, n );
  if( !q ) {
    fprintf( stdout, "Allocation of q failed\n" );
    return EXIT_FAILURE;
  }
  q_copy = alloc_2d_double( m, n );
  if( !q_copy ) {
    fprintf( stdout, "Allocation of q failed\n" );
    return EXIT_FAILURE;
  }

  /* Initialise vectors */
  for( i = 0; i < n; i++ ) {
    for( j = 0; j < m; j++ ) {
      q[ j ][ i ] = ( (double) rand() ) / RAND_MAX ;
      q_copy[ j ][ i ] = q[ j ][ i ];
    }
  }

  /* Orthogonolise the vectors using the modified gram schmidt method */
  modified_gs( n, m, q );

  /* Copy back the initial vectors so both algorithms act on the same set */
  for( i = 0; i < n; i++ ) {
    for( j = 0; j < m; j++ ) {
      q[ j ][ i ] = q_copy[ j ][ i ];
    }
  }

  /* Orthogonolise the vectors using the iterated classical gram schmidt method */
  iterated_classical_gs( n, m, q );

  /* Tidy up */
  free_2d_double( q_copy );
  free_2d_double( q );

  return EXIT_SUCCESS;

}

double check_orthonorm( int n, int m, double **q ) {

  /* Function to check the orthonormality of a set of m vectors of order n */

  double s, max_s;

  int i, j, k;

  max_s = -1.0;
  for( k = 0; k < m; k++ ){
    for(  i = 0; i < m; i++ ){
      /* Calculate the dot product of q_k with q_i */
      s = 0.0;
      for( j = 0; j < n; j++ ){
	s += q[ k ][ j ] * q[ i ][ j ];
      }
      /* if k is the same as i we expect the value to be one, not zero */
      if( k == i ) {
	s = s - 1.0;
      }
      /* Find the largest magnitude non-zero value for the dot products */
      s = fabs( s );
      if( s > max_s ) {
	max_s = s;
      }
    }
  }

  return max_s;

}

void modified_gs( int n, int m, double **q ) {

  /* Modified Gram-Schmidt algorithm */

  double s;
  double start, finish;
  double sqrt_s_inv;

  int i, j, k;

  start = timer();
  for( k = 0; k < m; k++ ) {
    for( i = 0; i < k; i++ ) {
      /* s = q_i(T) * q_k */
      s = 0.0;
      for( j = 0; j < n; j++ ) {
	s += q[ i ][ j ] * q[ k ][ j ];
      }
      /* q_k = q_k - s*q_i */
      for( j = 0; j < n; j++ ) {
	q[ k ][ j ] = q[ k ][ j ] - s * q[ i ][ j ];
      }
    }
    /* s = q_k(T) * q_k */
    s = 0.0;
    for( j = 0; j < n; j++ ) {
      s += q[ k ][ j ] * q[ k ][ j ];
    }
    /* q_k = q_k / Sqrt( s ) */
    sqrt_s_inv = 1.0 / sqrt( s );
    for( j = 0; j < n; j++ ) {
      q[ k ][ j ] = q[ k ][ j ] * sqrt_s_inv;
    }
  }
  finish = timer();
  fprintf( stdout, 
	   "Maximum error in orthonormalisation for MGS : %20.16f\n", check_orthonorm( n, m, q ) );
  fprintf( stdout, "Time for MGS : %9.4f\n", finish - start );

}

void iterated_classical_gs( int n, int m, double **q ) {

  /* Iterated classical Gram-Schmidt */

  double *p, *tmp;

  double s, s_old;
  double start, finish;
  double sqrt_s_inv;

  int i, j, k;

  start = timer();
  p = alloc_1d_double( m );
  if( !p ) {
    fprintf( stdout, "Allocation of p failed\n" );
  }
  tmp = alloc_1d_double( n );
  if( !tmp ) {
    fprintf( stdout, "Allocation of tmp failed\n" );
  }
  for( k = 0; k < m; k++ ) {
    /* s^0 = q_k(T) * q_k */
    s_old = 0.0;
    for( j = 0; j < n; j++ ) {
      s_old += q[ k ][ j ] * q[ k ][ j ];
    }
    for(;;) {
      /* p^i = Q_k(T) * q_k^(i-1) */
      for( i = 0; i < k; i++ ){ 
	p [ i ] = 0.0;
	for( j = 0; j < n; j++ ) {
	  p[ i ] += q[ i ][ j ] * q[ k ][ j ];
	}
      }
      /* tmp = Q_k * p^i */
      for( j = 0; j < n; j++ )
	tmp[ j ] = 0.0;
      for( i = 0; i < k; i++ ){ 
	for( j = 0; j < n; j++ ) {
	  tmp[ j ] += q[ i ][ j ] * p[ i ];
	}
      }
      /* q_k^i = q_k^i - tmp */
      for( j = 0; j < n; j++ ) {
	q[ k ][ j ] = q[ k ][ j ] - tmp[ j ];
      }
      /* s^0 = q_k(T)^i * q_k^i */
      s = 0.0;
      for( j = 0; j < n; j++ ) {
	s += q[ k ][ j ] * q[ k ][ j ];
      }
      if( s > 0.25 * s_old ) {
	break;
      }
      s_old = s;
    }
    /* q_k = q_k^i / Sqrt( s ) */
    sqrt_s_inv = 1.0 / sqrt( s );
    for( j = 0; j < n; j++ ) {
      q[ k ][ j ] = q[ k ][ j ] * sqrt_s_inv;
    }
  }
  free_1d( tmp );
  free_1d( p );
  finish = timer();
  fprintf( stdout, 
	   "Maximum error in orthonormalisation for ICGS: %20.16f\n", check_orthonorm( n, m, q ) );
  fprintf( stdout, "Time for ICGS: %9.4f\n", finish - start );
  
}
