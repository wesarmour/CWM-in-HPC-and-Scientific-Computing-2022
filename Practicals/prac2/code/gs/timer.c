
#include <stdlib.h>
#include <sys/time.h>

double timer( void )
{

  struct timeval t;

  gettimeofday( &t, NULL );

  return t.tv_sec + t.tv_usec / 1000000.0;

}
