/* Parallel matrix-vector multiplication with 1D block decomposition
 * We assume the matrix a and vector x have already been distributed.
 */
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

void MatrixVectorMultiply(int n, double *a, double *x, double *y, MPI_Comm comm)
{
  int i, j;
  int nlocal;   /* Number of locally stored rows of A */
  double *xbuf; /* Buffer that will store entire vector x */
  int npes, myrank;
  MPI_Status status;

  printf("In MatrixVectorMultiply\n");
  MPI_Comm_size(comm, &npes);
  MPI_Comm_rank(comm, &myrank);

  /* Allocate memory for x buffer */
  xbuf = (double *)malloc(n * sizeof(double));

  nlocal = n / npes;

  printf("Local A:\n");
  for (i = 0;i < nlocal;i++) {
    for (j = 0;j < n; j++){
      printf("%f\t", a[i*n +j]);
    }
    printf("\n");
  }

  printf("\nLocal X:\n");
  for (i = 0; i < nlocal; i++)
  {
    printf("%f\t", x[i]);
  }
  printf("\n");
  /* Gather entire vector x on each processor */
  /********************************************/
  MPI_Allgather(x, nlocal, MPI_DOUBLE, xbuf, n, MPI_DOUBLE, comm);
  /********************************************/

  // print x buffer
  printf("xbuf:\n");
  for (i = 0; i < n; i++)
  {
    printf("%f\t", xbuf[i]);
  }
  printf("\n");

  /* Perform local matrix-vector multiplication */
  for (i = 0; i < nlocal; i++)
  {
    y[i] = 0;
    for (j = 0; j < n; j++)
      y[i] += a[i * n + j] * xbuf[j];
  }

  free(xbuf);
}
