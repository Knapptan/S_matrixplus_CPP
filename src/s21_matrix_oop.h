#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  S21Matrix() noexcept;                       // Default constructor
  S21Matrix(const int rows, const int cols);  // Constructor
  S21Matrix(const S21Matrix& other);          // Copy
  S21Matrix(S21Matrix&& other) noexcept;      // Moving
  ~S21Matrix();                               // Destructor

  // Access
  int GetRows() noexcept;
  int GetCols() noexcept;

  // Mutation
  void SetRows(const int value);
  void SetCols(const int value);

  // Printer
  void PrintMatrix();

  // Arithmetic methods
  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);

  // Algebraic methods
  S21Matrix Transpose() const noexcept;
  S21Matrix CalcMinor(int delete_rows, int delete_cols);
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // For tests method
  void FullMatrix() noexcept;

  // Operators overload
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  S21Matrix operator*(const S21Matrix& other) const;
  bool operator==(const S21Matrix& other) const noexcept;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const double& other);
  S21Matrix& operator*=(const S21Matrix& other);
  double& operator()(const int i, const int j);
};

#endif  // S21_MATRIX_OOP_H
