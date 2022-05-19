

/* 1d routines */
char   *alloc_1d_char  ( int ndim1 );
int    *alloc_1d_int   ( int ndim1 );
float  *alloc_1d_float ( int ndim1 );
double *alloc_1d_double( int ndim1 );

void free_1d( void *p );

/* 2d routines */
char   **alloc_2d_char  ( int ndim1, int ndim2 );
int    **alloc_2d_int   ( int ndim1, int ndim2 );
float  **alloc_2d_float ( int ndim1, int ndim2 );
double **alloc_2d_double( int ndim1, int ndim2 );

void free_2d_char  ( char   **p );
void free_2d_int   ( int    **p );
void free_2d_float ( float  **p );
void free_2d_double( double **p );

/* 3d routines */
char   ***alloc_3d_char  ( int ndim1, int ndim2, int ndim3 );
int    ***alloc_3d_int   ( int ndim1, int ndim2, int ndim3 );
float  ***alloc_3d_float ( int ndim1, int ndim2, int ndim3 );
double ***alloc_3d_double( int ndim1, int ndim2, int ndim3 );

void free_3d_char  ( char   ***p, int ndim1 );
void free_3d_int   ( int    ***p, int ndim1 );
void free_3d_float ( float  ***p, int ndim1 );
void free_3d_double( double ***p, int ndim1 );
