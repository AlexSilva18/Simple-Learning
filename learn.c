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

  X = (double**)malloc(sizeof(double*)*N);
  Y = (double*)malloc(sizeof(double)*N);
  X_transpose = (double**)malloc(sizeof(double*)*(K+1));
  X_inverse = (double**)malloc(sizeof(double*)*N);
  
  //allocate memory for matrix X
  for (i=0; i<N; i++)
    {
      X[i] = (double*)malloc(sizeof(double)*(K+1));
      X_inverse[i] = (double*)malloc(sizeof(double)*(N*2));
    }

  //allocate memory for matrix X_transpose
  for (i=0; i< (K+1); i++)
    {
      X_transpose[i] = (double*)malloc(sizeof(double)*N);
    }
  
  getTrainingData(file, X, Y, N, K);
  //getTestData(argv[2]);
  transposeMatrix(X, X_transpose, N, K);
  invertMatrix(X, X_transpose, X_inverse, N, K);
  print(X, Y, X_transpose, X_inverse, N, K);

  
  for (i=0; i<N; i++)
    {
      free(X[i]);
      free(X_inverse[i]);
    }

  for (i=0; i<(K+1); i++)
    {
      free(X_transpose[i]);
    }
  
  free(X);
  free(Y);
  free(X_transpose);
  free(X_inverse);

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

void invertMatrix(double **X,double **X_transpose, double **X_inverse, int N, int K)
{
  int i, j,k;
  
   for(i=0; i<N; i++)
    {
      //printf("i= %d\n", i);
      for(j = 0; j< N; j++)
	{
	  //printf("j= %d\n", j);
	  for(k=0; k<(K+1); k++)
	    {
	      //printf("X[%d][%d] = %lf\n",i, k, X[i][k]);
	      //printf("X_transpose[%d][%d] = %lf\n",k, j, X_transpose[k][j]);
	      //printf("\n");
	      X_inverse[i][j] += X[i][k] * X_transpose[k][j];
	    }
	  //printf("x_inverse[%d][%d] >>> %lf\n",i,j,X_inverse[i][j]);
	}
    }
      printf("X_inverse\n");
   //print X_inverse
   for (i=0; i<N; i++)
    {
      for (j=0;j<N; j++)
	{
	  printf("%lf\t", X_inverse[i][j]);
	  if (j == (N-1))
	    {
	      printf("\n");
	    }
	}
    }

   printf("\n");
   printf("X_inverse + I\n");
   // add Aaug = augmented matrix to the end of X
   for(i=0; i<N; i++)
    {
      for(j=N; j<(N*2); j++)
	{
	  if ((i+N)==j)
	    X_inverse[i][j] = 1.0;
	  else
	    {
	      X_inverse[i][j] = 0;
	    }
	}  
    }

      
   //print X_inverse + I
  for (i=0; i<N; i++)
    {
      for (j=0;j<(N*2); j++)
	{
	  printf("%lf\t", X_inverse[i][j]);
	  if (j == ((N*2)-1))
	    {
	      printf("\n");
	    }
	}
    }


   
   //X_inverse[0][0] = (X_inverse[0][0] - ((X_inverse[0][0]/X_inverse[1][0])*X_inverse[1][0])) + 1;
   //X_inverse[1][0] = (X_inverse[1][0] - ((X_inverse[1][0]/X_inverse[0][0])*X_inverse[0][0]));
  /*double temp;
  int a = 0;
  for(j=0;j<(N*2);j++)
    {
      //set first to 1
      if (X_inverse[0][0] != 1)
	{
	  printf("step1\n");
	  temp = X_inverse[0][0];
	  while (a<N*2)
	    {
	      X_inverse[0][a] = (X_inverse[0][a] / temp);
	      ++a;
	    }
	  a=0;
	}
    }

  printf("N is %d\n",N);
  for (i=0;i<(N-1);i++)
    {
      for (j=1;j<(N);j++)
	{
	  printf("X_inverse[%d][%d] / X_inverse[%d][%d]\n",j,i,i,i);
	  double temp1 = X_inverse[j][i] / X_inverse[i][i];
	  printf("temp is : %lf\n", temp1);
	  for (k=0;k<(N*2);k++)
	    {
	      X_inverse[j][k] = X_inverse[j][k] - (temp1 * X_inverse[i][i]);
	    }
	}

    }*/
  
  //Row operations Upper Triangle
  double temp;
  int a = 0;
  for(i=0; i<N; i++)
    {
      k = 0;

      //printf("i = %d\n", i);
      //set first to 1
      if (X_inverse[i][i] != 1 && X_inverse[i][i] != 0)
	{
	  //printf("enter pivot\n");
	  //printf("step1\n");
	  temp = X_inverse[i][i];
	  a = 0;
	  while (a<(N*2))
	    {
	      X_inverse[i][a] = (X_inverse[i][a] / temp);
	      ++a;
	    }
	}
      
      if (X_inverse[i][i] == 1.0)
	{
	  while (k+1 < N)
	    {
	      //printf("enter loop\n");
	      a = 0;
	      if (i+1 >= N)
		{
		  break;
		}
	      //printf("step1\n");
	      k = (k+i+1);
	      //printf("k is %d\n", k);
	      
	      double temp1 = (-1 * X_inverse[k][i]) / X_inverse[i][i];
	      //printf("step2\n");
	      //printf("%lf\n", temp1);
	      while (a < N*2)
		{
		  //printf("\n%lf + (%lf *  %lf) \n", X_inverse[k][a],temp1, X_inverse[i][a]);
		  X_inverse[k][a] = X_inverse[k][a] + (temp1 * X_inverse[i][a]) ;
		  ++a;
		}
	    }
	}
    }

  //Row operations Lower Triangle
  for(i=N-1; i>=0; i--)
    {
      k = i;
      
      printf("i = %d\n", i);
      printf("k = %d\n", k);
      if (X_inverse[i][i] == 1.0)
	{
	  while (k > 0)
	    {
	      printf("enter loop\n");
	      a = 0;
	      printf("step1\n");
	      k =(k-1);
	      printf("k is %d\n", k);
	      
	      double temp1 = (-1 * X_inverse[k][i]) / X_inverse[i][i];
	      printf("step2\n");
	      printf("%lf\n", temp1);
	      while (a < N*2)
		{
		  printf("\n%lf + (%lf *  %lf) \n", X_inverse[k][a],temp1, X_inverse[i][a]);
		  X_inverse[k][a] = X_inverse[k][a] + (temp1 * X_inverse[i][a]) ;
		  ++a;
		}
	    }
	}
    }
  /*else if( (i == j) && X_inverse[i][j] != 1.0)
		    {
		      printf("step1\n");
		      temp = X_inverse[i][j];
		      while (j <N*2)
			{
			  //printf("X_inverse[%d][%d] = %lf\n",i,j,X_inverse[i][j]);
			  //printf("operation X_inverse[%d][%d] /  %lf\n",i,j,temp);
			  X_inverse[i][j] = (X_inverse[i][j] / temp);
			  ++j;
			}
		    }*/
  //	} 
//}
  // allocate memory for gauss-jordan operations
  // set X_inverse equal to X
  // add Aaug = augmented matrix to the end of X
  /* Row operations that are allows:
           - divide the entire row by a constant
	   - subtract a row by another row
	   - subtract a row by another row multiplied by a constant
  */

  
}

void print(double **X, double *Y, double **X_transpose,double **X_inverse, int N, int K)
{
  int i,j;

   //Print matrix X
  /*for (i=0; i<N; i++)
    {
      for (j=0;j<K+1; j++)
	{
	  printf("%lf\t", X[i][j]);
	  if (j == K)
	    {
	      printf("\n");
	    }
	}
    }*/
  
  //Print matrix Y
  /*for (i = 0; i<N; i++)
    {
      printf("%lf\t", Y[i]);
    }*/

  printf("\n");
   //Print matrix X_transpose
  /*for (i=0; i<(K+1); i++)
    {
      for (j=0;j<N; j++)
	{
	  printf("%lf\t", X_transpose[i][j]);
	  if (j == (N-1))
	    {
	      printf("\n");
	    }
	}
    }*/

  printf("\n");
  //print X_inverse
  /*for (i=0; i<N; i++)
    {
      for (j=0;j<N; j++)
	{
	  printf("%lf\t", X_inverse[i][j]);
	  if (j == (N-1))
	    {
	      printf("\n");
	    }
	}
    }*/
   printf("\n");
   
   //print X_inverse + I
  for (i=0; i<N; i++)
    {
      for (j=0;j<(N*2); j++)
	{
	  printf("%lf\t", X_inverse[i][j]);
	  if (j == ((N*2)-1))
	    {
	      printf("\n");
	    }
	}
    }

  
}
