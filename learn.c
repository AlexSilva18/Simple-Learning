#include "learn.h"

int main(int argc, char *argv[])
{

  FILE *file = fopen(argv[1], "r");
  FILE *file2 = fopen(argv[2],"r");
  int i,N, K, N2 = 0;
  
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
  fscanf(file2, "%d\n", &N2);
  //printf("K %d, N is %d\n", K, N);


  
  double **X, **X_transpose, **X_inverse, *Y, *W, **attributes, *price;

  X = (double**)malloc(sizeof(double*)*N);
  Y = (double*)malloc(sizeof(double)*N);
  X_transpose = (double**)malloc(sizeof(double*)*(K+1));
  X_inverse = (double**)malloc(sizeof(double*)*(K+1));
  W = (double*)malloc(sizeof(double)*(K+1));
  attributes = (double**)malloc(sizeof(double*)*N2);
  price = (double*)malloc(sizeof(double)*N2);
  
  //allocate memory for matrix X
  for (i=0; i<N; i++)
    {
      X[i] = (double*)malloc(sizeof(double)*(K+1));
      //X_inverse[i] = (double*)malloc(sizeof(double)*(N*2));
      
    }

  for (i=0; i<N2; i++)
    {
      attributes[i] = (double*)malloc(sizeof(double)*K);
    }

  //allocate memory for matrix X_transpose
  for (i=0; i< (K+1); i++)
    {
      X_transpose[i] = (double*)malloc(sizeof(double)*N);
      X_inverse[i] = (double*)malloc(sizeof(double)*(K+1));
    }
  
  getTrainingData(file, X, Y, N, K);
  getTestData(file2, attributes, N2, K);
  transposeMatrix(X, X_transpose, N, K);
  invertMatrix(X, X_transpose, X_inverse, N, K);
  getWeight(X_inverse, X_transpose, Y, W, N, K);
  getPrice(price, W, attributes, N, K, N2);
  print(X, Y, X_transpose, X_inverse, W, attributes, price, N, K, N2);

  
  for (i=0; i<N; i++)
    {
      free(X[i]);
    }
  
  for (i=0;i<N2; i++)
    {
      free(attributes[i]);
    }

  for (i=0; i<(K+1); i++)
    {
      free(X_transpose[i]);
      free(X_inverse[i]);
    }
  
  free(X);
  free(Y);
  free(X_transpose);
  free(X_inverse);
  free(W);
  free(attributes);
  free(price);

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

void getTestData(FILE *fp, double **attributes, int N2, int K)
{
  int i, j;
  //printf("N2 is : %d\n", N2);
  for (i=0; i<N2; i++)
    {
      for (j=0; j < K; j++)
	{
	  fscanf(fp,"%lf,", &attributes[i][j]);
	  //printf("attributes[%d][%d] = %lf\n",i,j,attributes[i][j]);
	  //printf("attributes[%d][%d] \n",i,j);
	}
      //printf("\n");
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
  double **temp_inverse;
  
  temp_inverse = (double**)malloc(sizeof(double*)*(K+1));

  //allocate memory for matrix X
   for (i=0; i<(K+1); i++)
    {
      temp_inverse[i] = (double*)malloc(sizeof(double)*(K+1)*2);
    }

  for(i=0; i<(K+1); i++)
    {
      for(j = 0; j< (K+1); j++)
	{
	  for(k=0; k<N; k++)
	    {
	      //X_inverse[i][j] += X[i][k] * X_transpose[k][j];
	      //printf("temp_inverse[%d][%d] += X_transpose[%d][%d] * X[%d][%d]\n", i, j, i, k, k, j);
	      temp_inverse[i][j] += X_transpose[i][k] *  X[k][j];
	    }
	}
    }
  /*printf("\nX_transpose * X is:\n");
   //print X_inverse
   for (i=0; i<(K+1); i++)
    {
      for (j=0;j<(K+1); j++)
	{
	  printf("%lf\t", temp_inverse[i][j]);
	  if (j == (K))
	    {
	      printf("\n");
	    }
	}
    }*/

   //printf("\n");
   //printf("temp_inverse[2][1] is >> %lf\n", temp_inverse[2][1]);
   

   // add Aaug = augmented matrix to the end of X
   for(i=0; i<(K+1); i++)
    {
      for(j=(K+1); j<((K+1)*2); j++)
	{
	  if ((i+(K+1))==j)
	    temp_inverse[i][j] = 1.0;
	  else
	    {
	      temp_inverse[i][j] = 0;
	    }
	}  
    }
   
      
   //print X_inverse + I
   /*printf("X_inverse + I\n");
   for (i=0; i<(K+1); i++)
    {
      for (j=0;j<((K+1)*2); j++)
	{
	  printf("%lf\t", temp_inverse[i][j]);
	  if (j == (((K+1)*2)-1))
	    {
	      printf("\n");
	    }
	}
    }*/
  
  //Row operations Upper Triangle
  double temp;
  int a = 0;
  for(i=0; i<(K+1); i++)
    {
      k = 0;

      //printf("i = %d\n", i);
      //set first to 1
      if (temp_inverse[i][i] != 1 && temp_inverse[i][i] != 0)
	{
	  //printf("enter pivot\n");
	  //printf("step1\n");
	  temp = temp_inverse[i][i];
	  a = 0;
	  while (a<((K+1)*2))
	    {
	      temp_inverse[i][a] = (temp_inverse[i][a] / temp);
	      ++a;
	    }
	}
      
      if (temp_inverse[i][i] == 1.0)
	{
	  k = i;
	  while (k+1 < (K+1))
	    {
	      a = 0;
	      //printf("round %d\n", i);
	      //printf(">%d + %d + 1\n", k, i);
	      //k = (k+i+1);
	      ++k;
	      //printf("k == %d\n\n",k);
	      if (k >= (K+1))
		{
		  break;
		}
	      //printf("step1\n");
	      //printf("k is %d\n", k);
	      //printf("(K+1) = %d / N = %d\n", k, N);
	      double temp1 = (-1 * temp_inverse[k][i]) / temp_inverse[i][i];
	      //printf("step2\n");
	      //printf("%lf\n", temp1);
	      while (a < (K+1)*2)
		{
		  //printf("\n%lf + (%lf *  %lf) \n", temp_inverse[k][a],temp1, temp_inverse[i][a]);
		  temp_inverse[k][a] = temp_inverse[k][a] + (temp1 * temp_inverse[i][a]) ;
		  ++a;
		}
	    }
	}
    }

  /*printf("\nUpper Triangle\n");
   for (i=0; i<(K+1); i++)
    {
      for (j=0;j<((K+1)*2); j++)
	{
	  printf("%lf\t", temp_inverse[i][j]);
	  if (j == (((K+1)*2)-1))
	    {
	      printf("\n");
	    }
	}
    }*/

  
  
  //Row operations Lower Triangle
   for(i=K; i>=0; i--)
     {
       k = i;
       
       //printf("i = %d\n", i);
       //printf("k = %d\n", k);
       if (temp_inverse[i][i] == 1.0)
	{
	  while (k > 0)
	    {
	      //printf("enter loop\n");
	      a = 0;
	      //printf("step1\n");
	      
	      //printf("round %d\n", i);
	      //printf(">%d + %d + 1\n", k, i);
	      //k = (k+i+1);
	      k =(k-1);
	      //printf("k == %d\n\n",k);
	      //printf("k is %d\n", k);
	      
	      double temp1 = (-1 * temp_inverse[k][i]) / temp_inverse[i][i];
	      //printf("step2\n");
	      //printf("%lf\n", temp1);
	      while (a < (K+1)*2)
		{
		  //printf("\n%lf + (%lf *  %lf) \n", X_inverse[k][a],temp1, X_inverse[i][a]);
		  temp_inverse[k][a] = temp_inverse[k][a] + (temp1 * temp_inverse[i][a]) ;
		  ++a;
		}
	    }
	}
    }

   /*printf("\nLower Triangle\n");
   for (i=0; i<(K+1); i++)
    {
      for (j=0;j<((K+1)*2); j++)
	{
	  printf("%lf\t", temp_inverse[i][j]);
	  if (j == (((K+1)*2)-1))
	    {
	      printf("\n");
	    }
	}
    }*/
  /*printf("temp_inverse is:\n");
   for (i=0; i<N; i++)
	{
	  for (j=0;j<(N*2); j++)
	    {
	      printf("%lf\t", temp_inverse[i][j]);
	      if (j == ((N*2)-1))
		{
		  printf("\n");
		}
	    }
	}*/
  

  /*printf("\nrow operations complete\n");
   //print X_inverse + I
  for (i=0; i<N; i++)
    {
      for (j=0;j<(N*2); j++)
	{
	  printf("%lf\t", temp_inverse[i][j]);
	  if (j == ((N*2)-1))
	    {
	      printf("\n");
	    }
	}
    }*/
  
  //printf("before switch\n");
  //set X_inverse to inverted matrix
   for(i=0; i<(K+1); i++)
    {
      for(j=(K+1); j<(K+1)*2; j++)
	{
	  //printf("X_inverse[%d][%d - %d + 1] = temp_inverse[%d][%d]\n", i, j, K, i, j);
	  X_inverse[i][j-(K+1)] = temp_inverse[i][j];
	}  
    }

   
   /*printf("\nX_inverse is:\n");
  for (i=0; i<(K+1); i++)
	{
	  for (j=0;j<(K+1); j++)
	    {
	      printf("%lf\t", X_inverse[i][j]);
	      if (j == K)//-1))
		{
		  printf("\n");
		}
	    }
	}*/

  for (i=0; i<(K+1); i++)
    {
      free(temp_inverse[i]);
    }
  free(temp_inverse);
}

void getWeight(double **X_inverse, double **X_transpose, double *Y, double *W, int N, int K)
{
  int i,j,k;
  double **temp_m;

  //printf("step0\n");
  temp_m = (double**)malloc(sizeof(double*)*(K+1));

  //printf("step1\n");
  //printf("the variable N is : %d\n", N);
  for (i=0; i<(K+1); i++)
    {
      //temp_matrix[i] = (double*)malloc(sizeof(double)*N);
      temp_m[i] = (double*)malloc(sizeof(double)*(N));
    }

  //printf("step2\n");
  for(i=0; i<(K+1); i++)
    {
      for(j = 0; j < N; j++)
	{
	  for(k=0; k<(K+1); k++)
	    {
	      //X_inverse[i][j] += X[i][k] * X_transpose[k][j];
	      //printf("temp_m[%d][%d] += X_inverse[[%d][%d] * X_transpose[%d][%d] >> %lf * %lf\n", i, j, i, k,  k, j, X_inverse[i][k], X_transpose[k][j]);
	      temp_m[i][j] += X_inverse[i][k] * X_transpose[k][j];
	      //printf("temp_m == %lf\n", temp_m[i][j]);
	    }
	  //printf("\n");
	  W[i] += temp_m[i][j] * Y[j];
	}
    }
  /*printf("\n");
  printf("X_transpose is:\n");
  //Print matrix X_transpose
  for (i=0; i<(K+1); i++)
    {
      for (j=0;j<K; j++)
	{
	  printf("%lf\t", X_transpose[i][j]);
	  if (j == (N-1))
	    {
	      printf("\n");
	    }
	}
    }*/

  /*printf("\n");
  printf("temp_m is:\n");
  //print X_inverse +
  for (i=0; i<(K+1); i++)
    {
      for (j=0;j<(N); j++)
	{
	  //printf("%lf\t", temp_matrix[i][j]);
	  printf("%lf\t", temp_m[i][j]);
	  if (j == (N-1))
	    {
	      printf("\n");
	    }
	}
    }*/

  /*printf("\n");
  printf("W is:\n");
  //Print matrix Y
  for (i = 0; i<K; i++)
    {
      printf("%lf\n", W[i]);
    }*/

  

  for(i=0; i<(K+1); i++)
    {
      free(temp_m[i]);
      //free(temp_matrix[i]);
    }
  //free(temp_matrix);
  free(temp_m);
}

void getPrice(double *price, double *W, double **attributes, int N, int K, int N2)
{
  int i,j;

  for(i=0;i<N2;i++)
    {
      //printf("\n");
      for(j=0;j<K;j++)
	{
	  if( j == 0)
	    {
	      //printf("price[%d] = W[%d]\n", i, j);
	      price[i] = W[j];
	    }
	  //printf("price[%d] += (attributes[%d][%d] * W[%d+1])\n", i,i, j,j);
	  price[i] += (attributes[i][j] * W[j+1]);
	}
    }

}

void print(double **X, double *Y, double **X_transpose,double **X_inverse, double *W, double **attributes,double *price, int N, int K, int N2)
{
  int i;//,j;

   //Print matrix X
  /*printf("\n");
  printf("X is \n");
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
  
  printf("\n");
  printf("Y is:\n");
  //Print matrix Y
  for (i = 0; i<N; i++)
    {
      printf("%lf\n", Y[i]);
    }

  printf("\n");
  printf("X_transpose is:\n");
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

   printf("\n");
   printf("X_inverse is:\n");
   //print X_inverse +
   for (i=0; i<(K+1); i++)
    {
      for (j=0;j<(K+1); j++)
	{
	  printf("%lf\t", X_inverse[i][j]);
	  if (j == (K))
	    {
	      printf("\n");
	    }
	}
    }
  printf("\n");
  printf("W is:\n");
  //Print matrix Y
  for (i = 0; i<(K+1); i++)
    {
      printf("%lf\n", W[i]);
    }
  printf("\n");

  
  printf("\n");
  printf("attributes is:\n");
  //Print matrix attributes
  for (i=0; i<N2; i++)
    {
      for (j=0;j<K; j++)
	{
	  printf("%lf\t", attributes[i][j]);
	  if (j == K-1)
	    {
	      printf("\n");
	    }
	}
    }

  
  printf("\n");
  printf("price is:\n");*/
  //Print matrix Y
  for (i = 0; i<N2; i++)
    {
      printf("%0.0lf\n", price[i]);
    }

  
}
