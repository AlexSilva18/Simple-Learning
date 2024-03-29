#ifndef LEARN_H
#define LEARN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getTrainingData(FILE *fp, double **X, double *Y,int N, int K);
void getTestData(FILE *fp, double **attributes, int N2, int K);
void transposeMatrix(double **X, double **X_transpose, int N, int K);
void invertMatrix(double **X, double **X_transpose, double **X_inverse, int N, int K);
void getWeight(double **X_inverse, double **X_transpose, double *Y, double *W, int N, int K);
void getPrice(double *price, double *W, double **attributes, int N, int K, int N2);
void print(double **X, double *Y, double **X_transpose, double **X_inverse, double *W, double **attributes, double *price, int N, int K, int N2);
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
