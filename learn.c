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


  
  double **X;
  double *Y;

  X = (double**)malloc(sizeof(double*)*K+1);
  Y = (double*)malloc(sizeof(double)*K);
  
  
  //allocate matrix memory
  for (i=0; i<K+1; i++)
    {
      X[i] = (double*)malloc(sizeof(double)*N);
    }
  
  getTrainingData(file, X, Y, N, K);
  //getTestData(argv[2]);

  for (i=0; i<K+1; i++)
    {
      free(X[i]);
    }
  
  free(X);
  free(Y);

  return 0;
}


void getTrainingData(FILE *fp, double **X, double *Y, int N, int K)
{
  int i, j;

  for (i = 0; i < N; i++)
    {
      X[i][0] = 1;
    }
  

  for (i=0; i<N; i++)
    {
      for (j=0;j<K+1; j++)
	{
	  printf("%lf\t", X[i][j]);
	  if (j== K)
	    {
	      printf("\n");
	    }
	  
	}
    }
    
  
  
      /*for (i=0; i<N; i++)
    {
      X[i][0] = 1;
      for (j=1; j<( K+1); j++)
	{
	  //fscanf(fp,"%lf,", &X[i][j]);
	  //fscanf(fp,"%lf", &Y[i]);
	}
      
	}*/

  /*X[0][0] = 1;
  X[1][0] = 1;
  X[2][0] = 1;
  X[3][0] = 1;
  X[4][0] = 1;
  X[5][0] = 1;
  printf("%lf\t\n", X[0][0]);
  printf("%lf\t\n", X[1][0]);
  printf("%lf\t\n", X[2][0]);
  printf("%lf\t\n", X[3][0]);
  printf("%lf\t\n", X[4][0]);
  printf("%lf\t\n", X[5][0]);*/
  
  
  /*for (i=0; i<N; i++)
    {
      for (j=0;j<K+1; j++)
	{
	  printf("%lf\t", X[i][j]);
	  if (j== K)
	    {
	      printf("\n");
	    }
	  
	}
    }*/
  
  
}
