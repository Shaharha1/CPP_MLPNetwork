#include "Dense.h"

Dense::Dense(Matrix& weights, Matrix& bias, activation_func ActivFunc)
{
  _ActivationFunction = ActivFunc;
  _weights = weights;
  _bias = bias;
}

Matrix Dense::get_weights () const
{
  Matrix return_weights(_weights.get_rows(), _weights.get_cols());
  return_weights = _weights;
  return return_weights;
}

Matrix Dense::get_bias () const
{
  Matrix return_bias(_bias.get_rows(),_bias.get_cols());
  return_bias = _bias;
  return return_bias;
}

activation_func Dense::get_activation () const
{
  activation_func return_func;
  return_func = _ActivationFunction;
  return return_func;
}

/**
 * applay the layer of the Mlp
 * @param vector
 * @return new vector
 */
Matrix Dense::operator() (const Matrix& vector)
{
  Matrix new_vec(vector.get_rows(),vector.get_cols());
  new_vec = vector;
  new_vec = _weights * new_vec;
  new_vec = new_vec + _bias;
  new_vec = _ActivationFunction(new_vec);
  return new_vec;
}