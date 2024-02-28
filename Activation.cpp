#include "Activation.h"
#include <cmath>

/**
 * get a matrix and apply relu
 * @param mat
 * @return new matrix
 */
Matrix activation::relu (const Matrix &mat)
{
  Matrix new_mat(mat.get_rows(), mat.get_cols());
  for(int i=0; i<mat.get_rows(); i++)
  {
    for(int j=0; j<mat.get_cols(); j++)
    {
      if(mat(i,j) > 0)
      {
        new_mat(i,j) = mat(i,j);
      }
    }
  }
  return new_mat;
}

/**
 * get a matrix and apply softmax
 * @param mat
 * @return new matrix
 */
Matrix activation::softmax (const Matrix &mat)
{
  Matrix new_mat(mat.get_rows(), mat.get_cols());
  float exp_sum = 0;
  for(int i=0; i<mat.get_rows(); i++)
  {
    for (int j = 0; j < mat.get_cols (); j++)
    {
      exp_sum += float (exp (mat (i, j)));
    }
  }
  exp_sum = 1/exp_sum;
  for(int i=0; i<mat.get_rows(); i++)
  {
    for(int j=0; j<mat.get_cols(); j++)
    {
      new_mat(i,j) = exp_sum * float(exp(mat(i,j)));
    }
  }
  return new_mat;
}