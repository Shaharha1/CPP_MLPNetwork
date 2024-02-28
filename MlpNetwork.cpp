#include "MlpNetwork.h"

enum {SIZE = 4,SIZE_1 =1, SIZE_2 = 2, SIZE_3 = 3};

MlpNetwork::MlpNetwork(Matrix weights[],Matrix biases[]) :
    _layer1 (weights[0], biases[0], activation::relu),
    _layer2 (weights[SIZE_1],biases[SIZE_1], activation::relu),
    _layer3 (weights[SIZE_2],biases[SIZE_2], activation::relu),
    _layer4 (weights[SIZE_3],biases[SIZE_3], activation::softmax)
{
}

/**
 * Apply the Mlp on the img
 * @param img
 * @return digit object that contain the number
 */
digit MlpNetwork::operator() (const Matrix &img)
{
  enum {ROWS = 28};
  if(img.get_rows() != ROWS || img.get_cols() != ROWS)
  {
    throw std::length_error("length error");
  }
  Matrix vec(img);
  vec.vectorize();
  vec = _layer1(vec);
  vec = _layer2(vec);
  vec = _layer3(vec);
  vec = _layer4(vec);
  digit final;
  final.value = vec.argmax();
  final.probability = vec[vec.argmax()];
  return final;
}