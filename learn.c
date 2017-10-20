#include "learn.h"

int main(int argc, char *argv[])
{

  FILE *file = fopen(argv[1], "r");
  int i = 0;
  int N, K = 0;
  
  if (argc != 3)
    {
      fprintf(stderr, "Incorrect Input\n");
    }

  
  if (file == NULL)
    {
      printf("0\n");
    }

  fscanf(file, "%d\n", &K);
  fscanf(file, "%d\n", &N);
  printf("K %d, N is %d\n", K, N);


  
  double **X, **X_transpose, **X_inverse, *Y;

  X = (double**)malloc(sizeof(double*)*(N));
  Y = (double*)malloc(sizeof(double)*N);
  X_transpose = (double**)malloc(sizeof(double*)*(K+1));
  //allocate X_inverse HERE
  
  //allocate memory for matrix X
  for (i=0; i<N; i++)
    {
      X[i] = (double*)malloc(sizeof(double)*(K+1));
    }

    //allocate memory for matrix X_transpose
  for (i=0; i< (K+1); i++)
    {
      X_transpose[i] = (double*)malloc(sizeof(double)*N);
    }

    //allocate X_inverse HERE
  
  getTrainingData(file, X, Y, N, K);
  //getTestData(argv[2]);
  transposeMatrix(X, X_transpose, N, K);
  print(X, Y, X_transpose, N, K);

  
  for (i=0; i<N; i++)
    {
      free(X[i]);
    }

  for (i=0; i<(K+1); i++)
    {
      free(X_transpose[i]);
    }
  
  free(X);
  free(Y);
  free(X_transpose);

  return 0;
}


void getTrainingData(FILE *fp, double **X, double *Y, int N, int K)
{
  int i, j;

  for (i=0; i<N; i++)
    {
      X[i][0] = 1.0;
      for (j=1; j < (K+1); j++)
	{
	  fscanf(fp,"%lf,", &X[i][j]);
	}
      fscanf(fp,"%lf,", &Y[i]);
    }

   
}

void transposeMatrix(double **X, double **X_transpose, int N, int K)
{
  int i, j;

  for (i=0; i<N; i++)
    {
      for (j = 0; j< (K+1); j++)
	{
	  X_transpose[j][i] = X[i][j];
	}
    }
  
  
}

void invertMatrix(double **X, double **X_inverse, int N, int K)
{
  // allocate memory for gauss-jordan operations
  // set X_inverse equal to X
  // add Aaug = augmented matrix to the end of X
  /* Row operations that are allows:
           - divide the entire row by a constant
	   - subtract a row by another row
	   - subtract a row by another row multiplied by a constant
  */
}

void print(double **X, double *Y, double **X_transpose, int N, int K)
{
  int i,j;

   //Print matrix X
  for (i=0; i<N; i++)
    {
      for (j=0;j<K+1; j++)
	{
	  printf("%lf\t", X[i][j]);
	  if (j == K)
	    {
	      printf("\n");
	    }
	}
    }
  
  //Print matrix Y
  /*for (i = 0; i<N; i++)
    {
      printf("%lf\t", Y[i]);
    }*/

  printf("\n");
   //Print matrix X_transpose
  for (i=0; i<(K+1); i++)
    {
      for (j=0;j<N; j++)
	{
	  printf("%lf\t", X_transpose[i][j]);
	  if (j == (N-1))
	    {
	      printf("\n");
	    }
	}
    }
  
}
