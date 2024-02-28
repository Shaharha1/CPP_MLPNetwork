#include "Matrix.h"
#include <iostream>
#include <cmath>
#include <fstream>

#define LEN_ERROR "length error"
#define RANGE_ERROR "out of range"
#define RANTIME_ERROR "runtime error"


using std::cout;
using  std::pow;
using std::sqrt;

Matrix::Matrix ()
{
  matrix = new float[1];
  matrix[0] = 0;
  dims.cols = 1;
  dims.rows = 1;
}
Matrix::Matrix (int rows, int cols)
{
  if(rows < 0 || cols < 0)
  {
    throw std::length_error(LEN_ERROR);
  }
  dims.rows = rows;
  dims.cols = cols;
  matrix = new float [rows * cols];
  for(int i =0; i< rows; i++)
  {
    for(int j=0; j<cols; j++)
    {
      matrix[i*cols + j] = 0;
    }
  }
}
Matrix::Matrix(const Matrix& matrix_copy)
{
  dims = matrix_copy.dims;
  matrix = new float[dims.rows * dims.cols];
  for (int i=0; i<dims.rows; i++)
  {
    for(int j=0; j<dims.cols; j++)
    {
      matrix[i*dims.cols + j] = matrix_copy.matrix[i*dims.cols + j];
    }
  }
}
Matrix::~Matrix()
{
  delete[] matrix;
}

int Matrix::get_rows() const
{
  return dims.rows;
}

int Matrix::get_cols() const
{
  return dims.cols;
}

Matrix& Matrix::transpose ()
{
  float *temp;
  temp = new float[dims.rows * dims.cols];
  float temp_dims = dims.rows;
  dims.rows = dims.cols;
  dims.cols = temp_dims;
  for(int i=0; i<dims.cols; i++)
  {
    for(int j=0; j<dims.rows; j++)
    {
      temp[i*dims.rows + j] = matrix[j*dims.cols + i];
    }
  }
  delete[] matrix;
  matrix = temp;
  return (*this);
}

Matrix& Matrix::vectorize ()
{
  float* vector = new float [dims.rows*dims.cols];
  for(int i=0; i<dims.rows;i++)
  {
    for(int j=0; j<dims.cols;j++)
    {
      float temp = matrix[i*dims.cols + j];
      vector[i*dims.cols +j] = temp;
    }
  }
  dims.rows = dims.rows * dims.cols;
  dims.cols = 1;
  return (*this);
}

void Matrix::plain_print () const
{
  for(int i=0 ; i<dims.rows; i++)
  {
    for(int j=0; j<dims.cols; j++)
    {
      cout << matrix[i*dims.cols + j] << " ";
    }
    cout << std::endl;
  }
}

Matrix Matrix::dot(const Matrix& rhs)
{
  if(dims.rows != rhs.dims.rows || dims.cols != rhs.dims.cols)
  {
    throw std::length_error(LEN_ERROR);
  }
  Matrix new_mat(dims.rows, dims.cols);
  for(int i=0; i<dims.rows; i++)
  {
    for(int j=0; j<dims.cols; j++)
    {
      new_mat.matrix[i*dims.cols + j] = matrix[i*dims.cols + j] *
                                        rhs.matrix[i*dims.cols + j];
    }
  }
  return new_mat;
}

float Matrix::norm() const
{
  float sum = 0;
  for(int i=0; i<dims.rows; i++)
  {
    for(int j=0; j<dims.cols; j++)
    {
      sum += float(pow(matrix[i*dims.cols + j], 2));
    }
  }
  return float(sqrt(sum));
}

int Matrix::argmax() const
{
  int index = 0;
  float max = matrix[0];
  for(int i=0; i<dims.rows; i++)
  {
    for(int j=0; j<dims.cols; j++)
    {
      if(matrix[i*dims.cols + j] > max)
      {
        max = matrix[i*dims.cols + j];
        index = (i*dims.cols) + j;
      }
    }
  }
  return index;
}

float Matrix::sum() const
{
  float sum =0;
  for(int i=0; i<dims.rows; i++)
  {
    for(int j=0; j<dims.cols; j++)
    {
      sum += matrix[i*dims.cols + j];
    }
  }
  return sum;
}

Matrix Matrix::operator+(const Matrix& rhs) const
{
  if(dims.rows != rhs.dims.rows || dims.cols != rhs.dims.cols)
  {
    throw std::length_error(LEN_ERROR);
  }
  Matrix new_mat(dims.rows, dims.cols);
  for(int i=0; i<dims.rows; i++)
  {
    for(int j=0; j<dims.cols; j++)
    {
      new_mat.matrix[i*dims.cols + j] = (matrix[i*dims.cols + j]) +
                                        (rhs.matrix[i*dims.cols + j]);
    }
  }
  return new_mat;
}

Matrix& Matrix::operator=(const Matrix& rhs)
{
  if(this != &rhs)
  {
    float* new_mat = new float[rhs.dims.rows * rhs.dims.cols];
    dims = rhs.dims;
    for(int i=0; i<dims.rows;i++)
    {
      for(int j=0; j<dims.cols; j++)
      {
        new_mat[i*dims.cols + j] = rhs.matrix[i*dims.cols + j];
      }
    }
    delete[] matrix;
    matrix = new_mat;
  }
  return (*this);
}

Matrix Matrix::operator* (const Matrix &rhs) const
{
  if(dims.cols != rhs.dims.rows)
  {
    throw std::length_error(LEN_ERROR);
  }
  Matrix new_mat(dims.rows, rhs.dims.cols);
  for(int i=0; i<dims.rows; i++)
  {
    for(int j=0; j<rhs.dims.cols; j++)
    {
      float sum_index = 0;
      for(int k=0; k<dims.cols; k++)
      {
        sum_index += matrix[i*dims.cols + k] * rhs.matrix[k*rhs.dims.cols +j];
      }
      new_mat.matrix[i*new_mat.dims.cols + j] = sum_index;
    }
  }
  return new_mat;
}

Matrix Matrix::operator* (float c) const
{
  Matrix new_mat(dims.rows,dims.cols);
  for(int i=0; i<dims.rows; i++)
  {
    for(int j=0; j<dims.cols; j++)
    {
      new_mat.matrix[i*dims.cols + j] = c * matrix[i*dims.cols + j];
    }
  }
  return new_mat;
}

Matrix operator*(float c, Matrix& rhs)
{
  Matrix new_mat(rhs.dims.rows,rhs.dims.cols);
  for(int i=0; i<rhs.dims.rows; i++)
  {
    for(int j=0; j<rhs.dims.cols; j++)
    {
      new_mat.matrix[i*rhs.dims.cols + j] = c* rhs.matrix[i*rhs.dims.cols + j];
    }
  }
  return new_mat;
}

float& Matrix::operator()(int i,int j) const
{
  if(i < 0 || i >= dims.rows || j < 0 || j >= dims.cols)
  {
    throw std::out_of_range(RANGE_ERROR);
  }
  return matrix[i*dims.cols + j];
}

float& Matrix::operator[](int i) const
{
  if(i < 0 || i > (dims.rows * dims.cols))
  {
    throw std::out_of_range(RANGE_ERROR);
  }

  int row = i / dims.cols;
  int col = i % dims.cols;
  return matrix[row*dims.cols + col];
}

Matrix& Matrix::operator+=(const Matrix& rhs)
{
  if(dims.rows != rhs.dims.rows || dims.cols != rhs.dims.cols)
  {
    throw std::length_error(LEN_ERROR);
  }
  for(int i=0; i<dims.rows; i++)
  {
    for(int j=0; j<dims.cols; j++)
    {
      matrix[i*dims.cols + j] += rhs.matrix[i*dims.cols + j];
    }
  }
  return (*this);
}

std::ostream& operator<<(std::ostream& s, const Matrix& rhs)
{
  enum {TEN = 10, ONE = 1};
  float bias = ONE / TEN;
  for(int i=0; i<rhs.dims.rows; i++)
  {
    for(int j=0; j<rhs.dims.cols; j++)
    {
      if(rhs[i*rhs.dims.rows + j] > bias)
      {
        s << "**";
      }
      else{
        s << "  ";
      }
    }
    s << std::endl;
  }
  return s;
}

std::istream& operator>>(std::istream& s, const Matrix& rhs)
{
  long int matrix_size_bytes =
      rhs.get_cols () * rhs.get_rows () * sizeof (float);
  s.seekg (0, std::ios_base::end);
  long int file_size_bytes = s.tellg ();
  if (file_size_bytes != matrix_size_bytes)
  {
    throw std::runtime_error (RANTIME_ERROR);
  }
  s.seekg (0, std::ios_base::beg);
  float *buf = new float[matrix_size_bytes];
  if (!s.read ((char *) buf, matrix_size_bytes))
  {
    throw std::runtime_error (RANTIME_ERROR);
  }
  int mat_size = rhs.get_rows() * rhs.get_cols();
  for (int i = 0; i < mat_size; i++)
  {
    rhs.matrix[i] = buf[i];
  }
  delete[] buf;
  return s;
}