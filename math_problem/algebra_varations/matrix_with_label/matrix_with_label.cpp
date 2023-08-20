#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>

class Matrix
{
public:
  Matrix();
  Matrix(int n, int m);
  Matrix(std::initializer_list<std::initializer_list<double>> values);
  Matrix(const Matrix& matrix);
  Matrix(Matrix&& matrix);
  virtual ~Matrix();

  Matrix operator-();
  double operator()(const int rowIdx, const int colIdx);
  Matrix& operator=(const Matrix& matrix);
  Matrix& operator=(Matrix&& matrix);

  void setN(int n)
  {
    N = n;
  }

  int getN() const
  {
    return N;
  }

  void setM(int m)
  {
    M = m;
  }

  int getM() const
  {
    return M;
  }

  double* getData() const
  {
    return data;
  }

  void setData(double* values)
  {
    if (!data)
    {
      data = new double[N * M];
    }

    for (int i = 0; i < N * M; ++i)
    {
      data[i] = values[i];
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

private:
  int N = 0;
  int M = 0;
  double* data = nullptr;
};

Matrix::Matrix()
{
  std::cout << "constructor " << N << "x" << M << " of matrix \n";
}

Matrix::Matrix(int n, int m): N(n), M(m)
{
  std::cout << "constructor " << N << "x" << M << " of matrix \n";
  data = new double[N * M]{0};
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> values)
{
  N = values.size();

  {
    auto row = values.begin();
    M = row->size();
    for (auto it = row + 1; it < values.end(); ++it)
    {
      if (it->size() > row->size())
      {
        M = it->size();
      }
    }
  }

  data = new double[N * M]{0};
  std::cout << "constructor " << N << "x" << M << " of matrix from initializer_list \n";

  for (int i = 0; i < N; ++i)
  {
    auto row = values.begin() + i;
    int j = 0;
    for (auto it = row->begin(); it != row->end(); ++it, ++j)
    {
      data[i * M + j] = *it;
    }
  }
}

Matrix::Matrix(const Matrix& matrix): N(matrix.N), M(matrix.M)
{
  std::cout << "copy constructor \n";
  data = new double[matrix.N * matrix.M];
  for (int i = 0; i < N * M; ++i)
  {
    data[i] = matrix.data[i];
  }
}

Matrix::Matrix(Matrix&& matrix)
{
  std::cout << "move constructor \n";
  N = std::move(matrix.N);
  M = std::move(matrix.M);

  data = new double[N * M];
  for (int i = 0; i < N * M; ++i)
  {
    data[i] = std::move(matrix.data[i]);
  }

  matrix.data = nullptr;
}

Matrix::~Matrix()
{
  delete[] data;
}

Matrix Matrix::operator-()
{
  Matrix matrix(N, M);
  matrix.data = new double[N * M];
  for (int i = 0; i < N * M; ++i)
  {
    data[i] = -data[i];
  }

  return matrix;
}

Matrix& Matrix::operator=(Matrix&& matrix)
{
  if (this != &matrix)
  {
    std::cout << "move assignment operator \n";

    N = std::move(matrix.N);
    M = std::move(matrix.M);
    data = new double[N * M];
    for (int i = 0; i < N * M; ++i)
    {
      data[i] = std::move(matrix.data[i]);
    }

    matrix.data = nullptr;
  }

  return *this;
}

Matrix& Matrix::operator=(const Matrix& matrix)
{
  std::cout << "copy assignment operator \n";

  N = matrix.N;
  M = matrix.M;
  data = new double[N * M];
  for (int i = 0; i < N * M; ++i)
  {
    data[i] = matrix.data[i];
  }

  return *this;
}

double Matrix::operator()(const int rowIdx, const int colIdx)
{
  return data[(rowIdx - 1) * M + (colIdx - 1)];
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
  const int& rowSize = matrix.N;
  const int& colSize = matrix.M;
  for (int i = 0; i < rowSize; ++i)
  {
    os << "{ ";
    const int rowIdx = i * rowSize;
    for (int j = 0; j < colSize - 1; ++j)
    {
      os << matrix.data[rowIdx + j] << ", ";
    }
    os << matrix.data[rowIdx + colSize - 1];
    os << " }\n";
  }

  return os;
}

class MatrixWithLabel: Matrix
{
  std::string label;

public:
  MatrixWithLabel() = default;
  MatrixWithLabel(int numRows, int numCols, std::string label = "A"): Matrix(numRows, numCols), label(label)
  {
  }

  MatrixWithLabel(std::initializer_list<std::initializer_list<double>> values, std::string label = "A"):
    Matrix(values), label(label)
  {
  }

  MatrixWithLabel(const MatrixWithLabel& matrixWithLabel): Matrix(matrixWithLabel), label(matrixWithLabel.getLabel())
  {
  }

  MatrixWithLabel(MatrixWithLabel&& matrixWithLabel):
    Matrix(std::move(matrixWithLabel)), label(std::move(matrixWithLabel.getLabel()))
  {
  }

  MatrixWithLabel& operator=(const MatrixWithLabel& matrixWithLabel)
  {
    std::cout << "copy assignment operator \n";
    label = matrixWithLabel.getLabel();
    setN(matrixWithLabel.getN());
    setM(matrixWithLabel.getM());

    return *this;
  }

  void setLabel(const std::string label)
  {
    this->label = label;
  }

  std::string getLabel() const
  {
    return label;
  }
};

int main()
{
  std::cout << "Inheritance \n";
  MatrixWithLabel l0(3, 4, "B");
  MatrixWithLabel l1({{1, 2}, {4, 5}});
  l1.setLabel("A");

  MatrixWithLabel l2 = l1;
  MatrixWithLabel l3 = std::move(l1);
  std::cout << l2.getLabel() << " " << l3.getLabel() << std::endl;

  MatrixWithLabel l4 = l2;
  l2 = l1;
}