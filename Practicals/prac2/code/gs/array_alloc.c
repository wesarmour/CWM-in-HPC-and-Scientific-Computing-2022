
/* 

   Simple wrappers for allocating arrays so that the elements are contiguous in memory 

   The following data types are supported: char, int, float, double 

   The following dimensionality of arrays is supported: 1, 2, 3

   The naming convention for routines is

   alloc_<dimensionality>_<type>

   where <dimensionality is of the form nd, where n is the number of dimensions, and 
   <type> is the data type 

   Each function returns a pointer with the appropriate degree of indirection for the 
   dimensionality required. On error NULL is returned.

   The arguments to the functions are the dimensions in natural order.

*/

#include <stdlib.h>

char *alloc_1d_char( int ndim1 ) {

  return malloc( ndim1 * sizeof( char ) );

}

int *alloc_1d_int( int ndim1 ) {

  return malloc( ndim1 * sizeof( int ) );

}

float *alloc_1d_float( int ndim1 ) {

  return malloc( ndim1 * sizeof( float ) );

}

double *alloc_1d_double( int ndim1 ) {

  return malloc( ndim1 * sizeof( double ) );

}

void free_1d( void *p ) {

  free( p );

}

char  **alloc_2d_char ( int ndim1, int ndim2 ) {

  char  **array2 = malloc( ndim1 * sizeof( char  * ) );

  int i;

  if( array2 != NULL ){

    array2[0] = malloc( ndim1 * ndim2 * sizeof( char  ) );

    if( array2[ 0 ] != NULL ) {

      for( i = 1; i < ndim1; i++ )
	array2[i] = array2[0] + i * ndim2;

    }

    else {
      free( array2 );
      array2 = NULL;
    }     

  }

  return array2;

}

int **alloc_2d_int( int ndim1, int ndim2 ) {

  int **array2 = malloc( ndim1 * sizeof( int * ) );

  int i;

  if( array2 != NULL ){

    array2[0] = malloc( ndim1 * ndim2 * sizeof( int ) );

    if( array2[ 0 ] != NULL ) {

      for( i = 1; i < ndim1; i++ )
	array2[i] = array2[0] + i * ndim2;

    }

    else {
      free( array2 );
      array2 = NULL;
    }

  }

  return array2;

}

float **alloc_2d_float( int ndim1, int ndim2 ) {

  float **array2 = malloc( ndim1 * sizeof( float * ) );

  int i;

  if( array2 != NULL ){

    array2[0] = malloc( ndim1 * ndim2 * sizeof( float ) );

    if( array2[ 0 ] != NULL ) {

      for( i = 1; i < ndim1; i++ )
	array2[i] = array2[0] + i * ndim2;

    }

    else {
      free( array2 );
      array2 = NULL;
    }

  }

  return array2;

}

double **alloc_2d_double( int ndim1, int ndim2 ) {

  double **array2 = malloc( ndim1 * sizeof( double * ) );

  int i;

  if( array2 != NULL ){

    array2[0] = malloc( ndim1 * ndim2 * sizeof( double ) );

    if( array2[ 0 ] != NULL ) {

      for( i = 1; i < ndim1; i++ )
	array2[i] = array2[0] + i * ndim2;

    }

    else {
      free( array2 );
      array2 = NULL;
    }

  }

  return array2;

}


void free_2d_char( char **p ) {

  free( p[ 0 ] );
  free( p );

}

void free_2d_int( int **p ) {

  free( p[ 0 ] );
  free( p );

}

void free_2d_float( float **p ) {

  free( p[ 0 ] );
  free( p );

}

void free_2d_double( double **p ) {

  free( p[ 0 ] );
  free( p );

}

char  ***alloc_3d_char ( int ndim1, int ndim2, int ndim3 ) {

  char  *space = malloc( ndim1 * ndim2 * ndim3 * sizeof( char ) );

  char ***array3 = malloc( ndim1 * sizeof( char ** ) );

  int i, j;

  if( space == NULL || array3 == NULL )
    return NULL;

  for( j = 0; j < ndim1; j++ ) {
    array3[ j ] = malloc( ndim2 * sizeof( char * ) );
    if( array3[ j ] == NULL )
      return NULL;
    for( i = 0; i < ndim2; i++ ) 
      array3[ j ][ i ] = space + j * ( ndim3 * ndim2 ) + i * ndim3;
  }

  return array3;

}

int   ***alloc_3d_int  ( int ndim1, int ndim2, int ndim3 ) {

  int   *space = malloc( ndim1 * ndim2 * ndim3 * sizeof( int  ) );

  int  ***array3 = malloc( ndim1 * sizeof( int  ** ) );

  int i, j;

  if( space == NULL || array3 == NULL )
    return NULL;

  for( j = 0; j < ndim1; j++ ) {
    array3[ j ] = malloc( ndim2 * sizeof( int * ) );
    if( array3[ j ] == NULL )
      return NULL;
    for( i = 0; i < ndim2; i++ ) 
      array3[ j ][ i ] = space + j * ( ndim3 * ndim2 ) + i * ndim3;
  }

  return array3;

}

float  ***alloc_3d_float ( int ndim1, int ndim2, int ndim3 ) {

  float  *space = malloc( ndim1 * ndim2 * ndim3 * sizeof( float ) );

  float  ***array3 = malloc( ndim1 * sizeof( float ** ) );

  int i, j;

  if( space == NULL || array3 == NULL )
    return NULL;

  for( j = 0; j < ndim1; j++ ) {
    array3[ j ] = malloc( ndim2 * sizeof( float * ) );
    if( array3[ j ] == NULL )
      return NULL;
    for( i = 0; i < ndim2; i++ ) 
      array3[ j ][ i ] = space + j * ( ndim3 * ndim2 ) + i * ndim3;
  }

  return array3;

}

double ***alloc_3d_double( int ndim1, int ndim2, int ndim3 ) {

  double *space = malloc( ndim1 * ndim2 * ndim3 * sizeof( double) );

  double ***array3 = malloc( ndim1 * sizeof( double** ) );

  int i, j;

  if( space == NULL || array3 == NULL )
    return NULL;

  for( j = 0; j < ndim1; j++ ) {
    array3[ j ] = malloc( ndim2 * sizeof( double* ) );
    if( array3[ j ] == NULL )
      return NULL;
    for( i = 0; i < ndim2; i++ ) 
      array3[ j ][ i ] = space + j * ( ndim3 * ndim2 ) + i * ndim3;
  }

  return array3;

}

void free_3d_char( char ***p, int ndim1 ) {

  int i;

  free( p[ 0 ][ 0 ] );

  for( i = 0; i < ndim1; i++ )
      free( p[ i ] );

  free( p );

}

void free_3d_int( int ***p, int ndim1 ) {

  int i;

  free( p[ 0 ][ 0 ] );

  for( i = 0; i < ndim1; i++ )
      free( p[ i ] );

  free( p );

}

void free_3d_float( float ***p, int ndim1 ) {

  int i;

  free( p[ 0 ][ 0 ] );

  for( i = 0; i < ndim1; i++ )
      free( p[ i ] );

  free( p );

}

void free_3d_double( double ***p, int ndim1 ) {

  int i;

  free( p[ 0 ][ 0 ] );

  for( i = 0; i < ndim1; i++ )
      free( p[ i ] );

  free( p );

}

