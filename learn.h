#ifndef LEARN_H
#define LEARN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getTrainingData(char *file, double **X, double *Y,int N, int K);
void getTestData(char *file);

void getTrainingData(char *file, double **X, double *Y, int N, int K)
{
  FILE *fp = fopen(file, "r");
  int i,j;
  
  
  if (fp == NULL)
    {
      printf("0\n");
    }
  
  for (i=0; i<N; i++)
    {
      for (j=0;j < K ; j++)
	{
	  //X[i] = 1;
	  fscanf(fp,"%lf,", &X[i][j]);
	  fscanf(fp,"%lf",&Y[i]);
	}
      break;
    }

  
  for (i=0; i<N; i++)
    {
      for (j=0;j<(K-1); j++)
	{
	  printf("%lf\t", (&X)[i][j]);
	  if (j== K-1)
	    {
	      printf("\n");
	    }
	  
	}
    }
  
  
}



/*Predict the price of the house for each entry in the test data file*/

/*GET TRAINING DATA FILE

  1st line has int K = # of attributes
  2nd line has int N = # of training exampels in the training data set
  Nth lines has the N training examples.(list of comma seperated double precision floating point values.)
  - the first K double precision values represent the values for the attributes of the house
  - the last double precision value in the line represents the price of the house1

  to do:
       - read 1st line to know the number of attributes to be stored in the Nth lines as attributes (columns)
       - read 2nd line to know how many training examples to be stored as K (rows)
       - last line will be stored as the price in a new matrix (N x 1)
       - The matrix size is going to be equal to N x K+1 (where K + 1 is equal to 1 and the values of K)
       
*/

/*GET TESTING DATA FILES
  
  1st line has integer M = # of test data points in the file
  K is the same as getTrainingData
  

*/

// read the training data
// read the test data
// store them in matrices
// transpose getTrainingData, multiply it by the regular matrix, inverse it, * by transpose, * getTestData
// W = (X^T * X)^-1 * X^T * Y


#endif
