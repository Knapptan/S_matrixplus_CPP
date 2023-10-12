#include "s21_matrix_oop.h"

// Constructor
S21Matrix::S21Matrix() noexcept {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

// Default constructor
S21Matrix::S21Matrix(const int rows, const int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::logic_error("matrix incorrect");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

// Destructor
S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
    rows_ = 0;
    cols_ = 0;
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

// Copy
S21Matrix::S21Matrix(const S21Matrix &other) {
  if (&other == this) {
    throw std::logic_error("self-copying error");
  } else {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}

// Move
S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

// Access
int S21Matrix::GetRows() noexcept { return rows_; }

int S21Matrix::GetCols() noexcept { return cols_; }

// Mutation
void S21Matrix::SetRows(int value) {
  if (value <= 0) {
    throw std::logic_error("number of rows incorrect");
  }

  if (rows_ == value) {
    return;
  }

  double **tmp_matrix = new double *[value];
  for (int i = 0; i < value; i++) {
    tmp_matrix[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      if (i < rows_) {
        tmp_matrix[i][j] = matrix_[i][j];
      } else {
        tmp_matrix[i][j] = 0;
      }
    }
  }
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;

  rows_ = value;
  matrix_ = tmp_matrix;
}

void S21Matrix::SetCols(int value) {
  if (value <= 0) {
    throw std::logic_error("number of cols incorrect");
  }

  if (cols_ == value) {
    return;
  }

  double **tmp_matrix = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    tmp_matrix[i] = new double[value];
    for (int j = 0; j < value; j++) {
      if (j < cols_) {
        tmp_matrix[i][j] = matrix_[i][j];
      } else {
        tmp_matrix[i][j] = 0;
      }
    }
  }
  for (int i = 0; i < cols_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;

  matrix_ = tmp_matrix;
  cols_ = value;
}

// Print
void S21Matrix::PrintMatrix() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      printf("%.2f ", matrix_[i][j]);
    }
    printf("\n");
  }
}

// Arithmetic methods
bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
  bool eq_result = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    eq_result = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          eq_result = false;
        }
      }
    }
  }
  return eq_result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (matrix_ == nullptr || other.matrix_ == nullptr) {
    throw std::logic_error("matrix incorrect");
  }
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("matrix different size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("matrix different size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::logic_error("matrix different size");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

// Algebraic methods
S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcMinor(int delete_rows, int delete_cols) {
  if (delete_rows >= cols_ || delete_cols >= rows_) {
    throw std::logic_error("index incorrect");
  }
  if (cols_ < 2 || rows_ < 2 || cols_ != rows_) {
    throw std::logic_error("matrix incorrect size");
  }
  S21Matrix minor(cols_ - 1, rows_ - 1);
  for (int k = 0, i = 0; i < cols_ && k < minor.cols_; i++) {
    if (i == delete_rows) continue;
    for (int m = 0, j = 0; j < rows_ && m < minor.rows_; j++) {
      if (j == delete_cols) continue;
      minor.matrix_[k][m] = matrix_[i][j];
      m++;
    }
    k++;
  }
  return minor;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::logic_error("matrix incorrect size");
  }
  if (rows_ == 1) {
    return *this;
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor_matrix(rows_ - 1, cols_ - 1);
      double calc_complement = 0;
      minor_matrix = CalcMinor(i, j);
      calc_complement = minor_matrix.Determinant();
      result.matrix_[i][j] = calc_complement * pow(-1, i + j);
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (cols_ != rows_) {
    throw std::logic_error("matrix incorrect size");
  }
  if (cols_ == 1) {
    return matrix_[0][0];
  }
  if (cols_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  }
  double determinant = 0.0;
  char sign = 1;
  for (int i = 0; i < cols_; i++) {
    double tmp_determinant = 0;
    S21Matrix minor_matrix(rows_ - 1, cols_ - 1);
    minor_matrix = CalcMinor(0, i);
    tmp_determinant = matrix_[0][i] * minor_matrix.Determinant();
    determinant += sign * tmp_determinant;
    sign = sign * -1;
  }
  return determinant;
}

S21Matrix S21Matrix::InverseMatrix() {
  double determinant = Determinant();
  if (determinant == 0) {
    throw std::logic_error("invalid operation determinant == 0");
  }
  S21Matrix result = S21Matrix(rows_, cols_);
  if (rows_ == 1) {
    result(0, 0) = 1 / (*this)(0, 0);
    return result;
  }
  result = CalcComplements().Transpose();
  result.MulNumber(1 / determinant);

  return result;
}

// For tests method
void S21Matrix::FullMatrix() noexcept {
  int count = 1;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = count;
      count++;
    }
  }
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    S21Matrix tmp(other);
    this->~S21Matrix();
    rows_ = tmp.rows_;
    cols_ = tmp.cols_;
    matrix_ = tmp.matrix_;
    tmp.matrix_ = nullptr;
  }
  return *this;
}

// Operators overload
S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix result = *this;
  result += other;
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result = *this;
  result -= other;
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result = *this;
  result *= num;
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix result = *this;
  result *= other;
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) const noexcept {
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double &other) {
  MulNumber(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

double &S21Matrix::operator()(const int i, const int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("index incorrect");
  }
  return matrix_[i][j];
}
