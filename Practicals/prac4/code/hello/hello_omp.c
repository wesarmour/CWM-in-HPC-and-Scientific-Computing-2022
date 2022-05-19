# include <stdio.h>
# include <omp.h>

int main(void)
{
  int nt; // number of threads
  int it; // thread id (0 to nt-1)

  # pragma omp parallel default(none) private(nt,it)
  {
    // retrieve size of thread pool
    nt = omp_get_num_threads();
    // retrieve thread id
    it = omp_get_thread_num();
    // print message
    printf("Hello world from thread %d of %d\n", it, nt);
  }
  return 0;
}

