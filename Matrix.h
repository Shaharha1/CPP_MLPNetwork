// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows, cols;
} matrix_dims;

class Matrix{
 private:
    matrix_dims dims;
    float* matrix;
 public:
  //Constructors
  Matrix(int rows, int cols);
  Matrix();
  Matrix(const Matrix& matrix);
  ~Matrix();
  //Functions
  int get_rows() const;
  int get_cols() const;
  Matrix& transpose();
  Matrix& vectorize();
  void plain_print() const;
  Matrix dot(const Matrix& rhs);
  float norm() const;
  int argmax() const;
  float sum() const;
  //Operators
  Matrix operator+(const Matrix& rhs) const;
  Matrix& operator=(const Matrix& rhs);
  Matrix operator*(const Matrix& rhs) const;
  Matrix operator*(float c) const;
  friend Matrix operator*(float c, Matrix& rhs);
  float& operator()(int i,int j) const;
  float& operator[](int i) const;
  Matrix& operator+=(const Matrix& rhs);
  friend std::ostream& operator<<(std::ostream& s, const Matrix& rhs);
  friend std::istream& operator>>(std::istream& s, const Matrix& rhs);
};

#endif //MATRIX_H