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
  //printf("K %d, N is %d", K, N);


  
  double **X;
  double *Y;

  X = (double**)malloc(sizeof(double*)*K);
  Y = (double*)malloc(sizeof(double)*K);
  
  
  //allocate matrix memory
  for (i=0; i<K; i++)
    {
      X[i] = (double*)malloc(sizeof(double)*K);
    }
  
  getTrainingData(argv[1], X, Y, N, K);
  //getTestData(argv[2]);

  free(X[i]);

  return 0;
}
