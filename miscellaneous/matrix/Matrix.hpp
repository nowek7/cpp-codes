#pragma once

#include <algorithm>
#include <initializer_list>
#include <stdexcept>

class Matrix
  {
  public:
    Matrix() = delete;
    Matrix(const Matrix &aOther);

    Matrix(std::initializer_list<std::initializer_list<double>> aRows);
    Matrix(const unsigned int &aRowsNum, const unsigned int &aColumnsNum, double **aRows);

    Matrix operator=(const Matrix &aOther);

    ~Matrix();

    Matrix operator+(const Matrix &aOther);
    Matrix& operator+=(const Matrix &aOther);

    Matrix operator-(const Matrix &aOther);
    Matrix& operator-=(const Matrix &aOther);

    Matrix operator*(const Matrix &aOther);
    Matrix &operator*=(const Matrix &aOther);

    Matrix operator*(double aScalar);
    Matrix& operator*=(double aScalar);

    Matrix operator/(double aScalar);
    Matrix& operator/=(double aScalar);

    bool operator==(Matrix &aOther);
    bool operator!=(Matrix &aOther);

    unsigned int getRowsNum() const;
    unsigned int getColumnsNum() const;

    double **getRows() const;
    double *getRow(unsigned int aRowIdx) const;
    double getAt(unsigned int aRowIdx, unsigned int aColIdx) const;

  private:
    unsigned int theRowsNum;
    unsigned int theColumnsNum;

    double **theRows = nullptr;
  };

Matrix::Matrix(const Matrix &aOther)
  :
  theRowsNum(aOther.getRowsNum()),
  theColumnsNum(aOther.getColumnsNum())
  {
  theRows = new double *[theRowsNum];
  for (unsigned int i = 0; i < theRowsNum; i++)
    {
    theRows[i] = new double[theColumnsNum];
    auto row = aOther.getRow(i);
    std::copy(row, row + theColumnsNum, theRows[i]);
    }
  }

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> aRows)
  {
  const unsigned int rowsNum = static_cast<unsigned int>(aRows.size());
  const unsigned int columnsNum = static_cast<unsigned int>((*(aRows.begin())).size());
  for (unsigned int i = 1; i < rowsNum; i++)
    {
    if ((*(aRows.begin() + i)).size() != columnsNum)
      throw std::logic_error("Size of columns is not the same!");
    }

  theRowsNum = rowsNum;
  theColumnsNum = columnsNum;

  theRows = new double *[theRowsNum];
  for (unsigned int i = 0; i < rowsNum; i++)
    {
    auto row = *(aRows.begin() + i);
    theRows[i] = new double[theColumnsNum];
    std::copy(row.begin(), row.end(), theRows[i]);
    }
  }

Matrix::Matrix(const unsigned int &aRowsNum, const unsigned int &aColumnsNum, double **aRows)
  :
  theRowsNum(aRowsNum),
  theColumnsNum(aColumnsNum)
  {
  theRows = new double *[theRowsNum];
  for (unsigned int i = 0; i < theRowsNum; i++)
    {
    theRows[i] = new double[theColumnsNum];
    std::copy(aRows[i], aRows[i] + theColumnsNum, theRows[i]);
    }
  }

Matrix Matrix::operator=(const Matrix &aOther)
  {
  unsigned int rowsNum = aOther.getRowsNum();
  unsigned int columnsNum = aOther.getColumnsNum();

  double **rows = new double *[rowsNum];
  for (unsigned int i = 0; i < rowsNum; i++)
    {
    rows[i] = new double[columnsNum];
    std::copy(rows[i], rows[i] + theColumnsNum, aOther.getRow(i));
    }

  return Matrix(rowsNum, columnsNum, rows);
  }

Matrix::~Matrix()
  {
  for (unsigned int i = 0; i < theRowsNum; i++)
    delete[] theRows[i];
  delete theRows;
  }

inline Matrix Matrix::operator+(const Matrix &aOther)
  {
  if ((theRowsNum != aOther.getRowsNum()) && (theColumnsNum != aOther.getColumnsNum()))
    throw std::logic_error("Matrices have different size!");

  double **rows = new double *[theRowsNum];
  for (unsigned int i = 0; i < theRowsNum; i++)
    {
    rows[i] = new double[theColumnsNum];
    auto otherRow = aOther.getRow(i);
    for (unsigned int j = 0; j < theColumnsNum; j++)
      rows[i][j] = theRows[i][j] + otherRow[j];
    }

  return Matrix(theRowsNum, theColumnsNum, rows);
  }

Matrix &Matrix::operator+=(const Matrix &aOther)
  {
  if ((theRowsNum != aOther.getRowsNum()) && (theColumnsNum != aOther.getColumnsNum()))
    throw std::logic_error("Matrices have different size!");

  for (unsigned int i = 0; i < theRowsNum; i++)
    {
    auto otherRow = aOther.getRow(i);
    for (unsigned int j = 0; j < theColumnsNum; j++)
      theRows[i][j] += otherRow[j];
    }

  return *this;
  }

Matrix Matrix::operator-(const Matrix &aOther)
  {
  if ((theRowsNum != aOther.getRowsNum()) && (theColumnsNum != aOther.getColumnsNum()))
    throw std::logic_error("Matrices have different size!");

  double **rows = new double *[theRowsNum];
  for (unsigned int i = 0; i < theRowsNum; i++)
    {
    rows[i] = new double[theColumnsNum];
    auto otherRow = aOther.getRow(i);
    for (unsigned int j = 0; j < theColumnsNum; j++)
      rows[i][j] = theRows[i][j] - otherRow[j];
    }

  return Matrix(theRowsNum, theColumnsNum, rows);
  }

Matrix& Matrix::operator-=(const Matrix &aOther)
  {
  if ((theRowsNum != aOther.getRowsNum()) && (theColumnsNum != aOther.getColumnsNum()))
    throw std::logic_error("Matrices have different size!");

  for (unsigned int i = 0; i < theRowsNum; i++)
    {
    auto row = aOther.getRow(i);
    for (unsigned int j = 0; j < theColumnsNum; j++)
      theRows[i][j] -= row[j];
    }

  return *this;
  }

Matrix Matrix::operator*(const Matrix &aOther)
  {
  unsigned int otherRowsNum = aOther.getRowsNum();
  unsigned int otherColumnsNum = aOther.getColumnsNum();
  if (theColumnsNum != otherRowsNum)
    throw std::logic_error("Cannot multiply by matrix");

  double **rows = new double *[theRowsNum];
  for (unsigned int i = 0; i < theRowsNum; i++)
    {
    rows[i] = new double[otherColumnsNum];
    for (unsigned int j = 0; j < otherColumnsNum; j++)
      {
      double sum = 0;
      for (unsigned int k = 0; k < otherRowsNum; k++)
        sum += theRows[i][k] * aOther.getAt(k, j);

      rows[i][j] = sum;
      }
    }

  return Matrix(theRowsNum, otherColumnsNum, rows);
  }

Matrix &Matrix::operator*=(const Matrix &aOther)
  {
  unsigned int otherRowsNum = aOther.getRowsNum();
  unsigned int otherColumnsNum = aOther.getColumnsNum();
  if (theColumnsNum != otherRowsNum)
    throw std::logic_error("Cannot multiply by matrix");

  double **rows = new double *[theRowsNum];
  for (unsigned int i = 0; i < theRowsNum; i++)
    {
    rows[i] = new double[otherColumnsNum];
    for (unsigned int j = 0; j < otherColumnsNum; j++)
      {
      double sum = 0;
      for (unsigned int k = 0; k < otherRowsNum; k++)
        sum += theRows[i][k] * aOther.getAt(k, j);

      rows[i][j] = sum;
      }
    }

  theColumnsNum = otherColumnsNum;
  for (unsigned int i = 0; i < theRowsNum; i++)
    {
    delete[] theRows[i];
    theRows[i] = std::move(rows[i]);
    }

  return *this;
  }

Matrix Matrix::operator*(double aScalar)
  {
  double **rows = new double *[theRowsNum];
  for (unsigned int i = 0; i < theRowsNum; i++)
    {
    rows[i] = new double[theColumnsNum];
    for (unsigned int j = 0; j < theColumnsNum; j++)
      rows[i][j] = theRows[i][j] * aScalar;
    }

  return Matrix(theRowsNum, theColumnsNum, rows);
  }

Matrix& Matrix::operator*=(double aScalar)
  {
  for (unsigned int i = 0; i < theRowsNum; i++)
    {
    for (unsigned int j = 0; j < theColumnsNum; j++)
      theRows[i][j] *= aScalar;
    }

  return *this;
  }

Matrix Matrix::operator/(double aScalar)
  {
  if (aScalar == 0)
    throw std::logic_error("Cannot divide by zero!");

  double **rows = new double *[theRowsNum];
  for (unsigned int i = 0; i < theRowsNum; i++)
    {
    rows[i] = new double[theColumnsNum];
    for (unsigned int j = 0; j < theColumnsNum; j++)
      rows[i][j] = theRows[i][j] / aScalar;
    }

  return Matrix(theRowsNum, theColumnsNum, rows);
  }

Matrix &Matrix::operator/=(double aScalar)
  {
  if (aScalar == 0)
    throw std::logic_error("Cannot divide by zero!");

  for (unsigned int i = 0; i < theRowsNum; i++)
    {
    for (unsigned int j = 0; j < theColumnsNum; j++)
      theRows[i][j] /= aScalar;
    }

  return *this;
  }

inline bool Matrix::operator==(Matrix &aOther)
  {
  if ((theRowsNum != aOther.getRowsNum()) && (theColumnsNum != aOther.getColumnsNum()))
    return false;

  for (unsigned int i = 0; i < theRowsNum; i++)
    {
    auto row = aOther.getRow(i);
    auto res = std::equal(row, row + theColumnsNum, theRows[i], theRows[i] + theColumnsNum);
    if (!res)
      return res;
    }

  return true;
  }

inline bool Matrix::operator!=(Matrix &aOther)
  {
  return !(*this == aOther);
  }

inline unsigned int Matrix::getRowsNum() const
  {
  return theRowsNum;
  }

inline unsigned int Matrix::getColumnsNum() const
  {
  return theColumnsNum;
  }

inline double **Matrix::getRows() const
  {
  return theRows;
  }

double *Matrix::getRow(unsigned int aRowIdx) const
  {
  if (!theRows)
    throw std::logic_error("The matrix is empty!");

  if (aRowIdx > theRowsNum)
    throw std::out_of_range("Out of range rows!");

  return theRows[aRowIdx];
  }

double Matrix::getAt(unsigned int aRowIdx, unsigned int aColIdx) const
  {
  if (!theRows)
    throw std::logic_error("The matrix is empty!");

  if (aRowIdx > theRowsNum)
    throw std::out_of_range("Out of range rows!");

  if (aColIdx > theColumnsNum)
    throw std::out_of_range("Out of range columns!");

  return theRows[aRowIdx][aColIdx];
  }
