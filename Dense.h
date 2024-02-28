#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense{
 private:
  Matrix _weights;
  Matrix _bias;
  activation_func _ActivationFunction;
 public:
  Dense(Matrix& weights, Matrix& bias, activation_func ActivFunc);
  Matrix get_weights() const;
  Matrix get_bias() const;
  activation_func get_activation() const;
  Matrix operator()(const Matrix& vector);
};

#endif //DENSE_H
