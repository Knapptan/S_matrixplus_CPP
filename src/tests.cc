#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(test, constructor_default_1) {
  S21Matrix m;
  EXPECT_EQ(m.GetRows(), 0);
  EXPECT_EQ(m.GetCols(), 0);
}

TEST(test, constructor_with_parameters_1) {
  S21Matrix m(1, 1);
  EXPECT_EQ(m.GetRows(), 1);
  EXPECT_EQ(m.GetCols(), 1);
}

TEST(test, constructor_with_parameters_2) {
  S21Matrix m(300, 400);
  EXPECT_EQ(m.GetRows(), 300);
  EXPECT_EQ(m.GetCols(), 400);
}

TEST(test, constructor_with_parameters_3) {
  EXPECT_THROW(S21Matrix m(-1, 4), std::logic_error);
}

TEST(test, constructor_with_parameters_4) {
  EXPECT_THROW(S21Matrix m(2, 0), std::logic_error);
}

TEST(test, constructor_with_parameters_5) {
  S21Matrix m(2, 2);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test, constructor_copy_1) {
  S21Matrix m1 = S21Matrix(2, 2);
  S21Matrix m2(m1);
  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 2);
}

TEST(test, constructor_move_1) {
  S21Matrix m1 = S21Matrix(100, 200);
  S21Matrix m2(std::move(m1));
  EXPECT_EQ(m2.GetRows(), 100);
  EXPECT_EQ(m2.GetCols(), 200);
  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m1.GetCols(), 0);
}

TEST(test, seters_1) {
  S21Matrix m = S21Matrix(11, 22);
  m.FullMatrix();
  EXPECT_NE(m.GetRows(), 15);
  m.SetRows(15);
  EXPECT_EQ(m.GetRows(), 15);
}

TEST(test, seters_2) {
  S21Matrix m = S21Matrix(11, 22);
  EXPECT_NE(m.GetRows(), 15);
  EXPECT_THROW(m.SetRows(0), std::logic_error);
}

TEST(test, seters_3) {
  S21Matrix m = S21Matrix(10, 10);
  m.FullMatrix();
  EXPECT_NE(m.GetCols(), 2);
  m.SetCols(2);
  EXPECT_EQ(m.GetCols(), 2);
  EXPECT_EQ(m(1, 1), 12);
}

TEST(test, seters_4) {
  S21Matrix m = S21Matrix(2, 2);
  m.FullMatrix();
  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 2);
  m.SetRows(3);
  m.SetCols(3);
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 3);
  S21Matrix expect = S21Matrix(3, 3);
  expect(0, 0) = 1;
  expect(0, 1) = 2;
  expect(0, 2) = 0;
  expect(1, 0) = 3;
  expect(1, 1) = 4;
  expect(1, 2) = 0;
  expect(2, 0) = 0;
  expect(2, 1) = 0;
  expect(2, 2) = 0;
  EXPECT_TRUE(expect == m);
}

TEST(test, eq_1) {
  S21Matrix m1 = S21Matrix(4, 5);
  S21Matrix m2 = S21Matrix(4, 5);
  EXPECT_TRUE(m1.EqMatrix(m2));
}

TEST(test, eq_2) {
  S21Matrix m1 = S21Matrix(4, 5);
  S21Matrix m2 = S21Matrix(5, 4);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(test, eq_3) {
  S21Matrix m1 = S21Matrix(4, 5);
  S21Matrix m2 = S21Matrix(4, 5);
  m1.FullMatrix();
  m2.FullMatrix();
  EXPECT_TRUE(m1.EqMatrix(m2));
  EXPECT_EQ(m1(0, 2), 3);
}

TEST(test, eq_4) {
  S21Matrix m1 = S21Matrix(11, 22);
  S21Matrix m2 = S21Matrix(11, 22);
  m1.FullMatrix();
  m2.FullMatrix();
  m2(3, 6) = 11;
  EXPECT_FALSE(m1 == m2);
}

TEST(test, eq_5) {
  S21Matrix m1 = S21Matrix(11, 22);
  S21Matrix m2 = S21Matrix();
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(test, sum_1) {
  S21Matrix m1 = S21Matrix(4, 4);
  S21Matrix m2 = S21Matrix(4, 3);
  EXPECT_THROW(m1.SumMatrix(m2), std::logic_error);
}

TEST(test, sum_2) {
  S21Matrix m1 = S21Matrix(4, 4);
  S21Matrix m2 = S21Matrix();
  EXPECT_THROW(m1.SumMatrix(m2), std::logic_error);
}

TEST(test, sum_3) {
  S21Matrix m1 = S21Matrix(4, 4);
  S21Matrix m2 = S21Matrix(4, 4);
  m1.FullMatrix();
  m2.FullMatrix();
  S21Matrix result = m1 + m2;
  EXPECT_TRUE(result(2, 2) == m1(2, 2) * 2);
}

TEST(test, sum_4) {
  S21Matrix m1 = S21Matrix(4, 4);
  S21Matrix m2 = S21Matrix(4, 4);
  m1.FullMatrix();
  m2.FullMatrix();
  m1 += m2;
  EXPECT_TRUE(m1(2, 2) == m2(2, 2) * 2);
}

TEST(test, sub_1) {
  S21Matrix m1 = S21Matrix(4, 4);
  S21Matrix m2 = S21Matrix(4, 4);
  m1.FullMatrix();
  m2.FullMatrix();
  m1 -= m2;
  EXPECT_EQ(m1(1, 3), 0);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(test, sub_2) {
  S21Matrix m1 = S21Matrix(2, 2);
  S21Matrix m2 = S21Matrix(2, 2);
  S21Matrix expect = S21Matrix(2, 2);
  m1.FullMatrix();
  m2.FullMatrix();
  EXPECT_TRUE((m1 - m2).EqMatrix(expect));
}

TEST(test, mult_num_1) {
  S21Matrix m = S21Matrix(4, 4);
  S21Matrix expect = S21Matrix(4, 4);
  m.FullMatrix();
  m *= 2;
  EXPECT_EQ(m(0, 3), 8);
  m *= 0.5;
  expect.FullMatrix();
  EXPECT_TRUE(m.EqMatrix(expect));
}

TEST(test, mult_num_2) {
  S21Matrix m = S21Matrix(2, 3);
  S21Matrix expect = S21Matrix(2, 3);
  m.FullMatrix();
  expect.FullMatrix();
  expect += m;
  expect += m;
  S21Matrix result(2, 3);
  result = m * 3;
  m.FullMatrix();
  EXPECT_TRUE(result == expect);
}

TEST(test, mult_mtrx_1) {
  S21Matrix m1 = S21Matrix(3, 4);
  S21Matrix m2 = S21Matrix(4, 3);
  S21Matrix expect = S21Matrix(3, 3);
  m1.FullMatrix();
  m2.FullMatrix();
  m1 *= m2;
  expect(0, 0) = 70;
  expect(0, 1) = 80;
  expect(0, 2) = 90;
  expect(1, 0) = 158;
  expect(1, 1) = 184;
  expect(1, 2) = 210;
  expect(2, 0) = 246;
  expect(2, 1) = 288;
  expect(2, 2) = 330;
  EXPECT_TRUE(m1.EqMatrix(expect));
}

TEST(test, mult_mtrx_2) {
  S21Matrix m1 = S21Matrix(3, 4);
  S21Matrix m2 = S21Matrix(4, 3);
  S21Matrix expect = S21Matrix(3, 3);
  m1.FullMatrix();
  m2.FullMatrix();
  m1 *= -1;
  m1 *= m2;
  expect(0, 0) = -70;
  expect(0, 1) = -80;
  expect(0, 2) = -90;
  expect(1, 0) = -158;
  expect(1, 1) = -184;
  expect(1, 2) = -210;
  expect(2, 0) = -246;
  expect(2, 1) = -288;
  expect(2, 2) = -330;
  EXPECT_TRUE(m1.EqMatrix(expect));
}

TEST(test, mult_mtrx_3) {
  S21Matrix m1 = S21Matrix(4, 3);
  S21Matrix m2 = S21Matrix(4, 4);
  EXPECT_THROW(m1 *= m2, std::logic_error);
}

TEST(test, mult_mtrx_4) {
  S21Matrix m1 = S21Matrix();
  S21Matrix m2 = S21Matrix(4, 4);
  EXPECT_THROW(m1 *= m2, std::logic_error);
}

TEST(test, mult_mtrx_5) {
  S21Matrix m1 = S21Matrix(2, 3);
  S21Matrix m2 = S21Matrix();
  EXPECT_THROW(m1 *= m2, std::logic_error);
}

TEST(test, transpose_1) {
  S21Matrix m = S21Matrix(3, 4);
  m.FullMatrix();
  S21Matrix result = m.Transpose();
  S21Matrix expect(4, 3);
  expect(0, 0) = 1;
  expect(0, 1) = 5;
  expect(0, 2) = 9;
  expect(1, 0) = 2;
  expect(1, 1) = 6;
  expect(1, 2) = 10;
  expect(2, 0) = 3;
  expect(2, 1) = 7;
  expect(2, 2) = 11;
  expect(3, 0) = 4;
  expect(3, 1) = 8;
  expect(3, 2) = 12;
  EXPECT_EQ(result.GetRows(), 4);
  EXPECT_EQ(result.GetCols(), 3);
  EXPECT_TRUE(result == expect);
}

TEST(test, calc_minor_1) {
  S21Matrix m = S21Matrix(1, 1);
  m(0, 0) = 5;
  EXPECT_THROW(m.CalcMinor(0, 0), std::logic_error);
}

TEST(test, calc_minor_2) {
  S21Matrix m = S21Matrix(2, 2);
  m(0, 0) = 5;
  EXPECT_THROW(m.CalcMinor(2, 0), std::logic_error);
}

TEST(test, calc_minor_3) {
  S21Matrix m(2, 2);
  m(0, 0) = 5;
  S21Matrix result = m.CalcMinor(1, 1);
  EXPECT_EQ(result.GetRows(), 1);
  EXPECT_EQ(result.GetCols(), 1);
  EXPECT_EQ(result(0, 0), 5);
}

TEST(test, calc_complements_1) {
  S21Matrix m(1, 1);
  m(0, 0) = 5;
  S21Matrix result = m.CalcComplements();
  EXPECT_EQ(result(0, 0), 5);
}

TEST(test, calc_complements_2) {
  S21Matrix m = S21Matrix(2, 2);
  S21Matrix expect = S21Matrix(2, 2);
  m.FullMatrix();
  S21Matrix result = m.CalcComplements();
  expect(0, 0) = 4;
  expect(0, 1) = -3;
  expect(1, 0) = -2;
  expect(1, 1) = 1;
  EXPECT_TRUE(expect == result);
}

TEST(test, determinant_1) {
  S21Matrix m = S21Matrix(3, 3);
  m.FullMatrix();
  EXPECT_EQ(m.Determinant(), 0);
}

TEST(test, determinant_2) {
  S21Matrix m = S21Matrix(6, 6);
  m.FullMatrix();
  m(0, 0) = -0.99;
  m(0, 4) = -99;
  m(2, 2) = -76.12;
  m(4, 0) = 25.1;
  m(5, 1) = -1.11;
  EXPECT_FLOAT_EQ(m.Determinant(), -753039);
}

TEST(test, determinant_3) {
  S21Matrix m = S21Matrix(7, 7);
  m.FullMatrix();
  m(0, 0) = 5;
  m(0, 1) = -1.33;
  m(2, 4) = 0;
  m(3, 1) = 1;
  m(3, 6) = 2.122;
  m(5, 3) = -1;
  m(6, 3) = 1.1;
  m(6, 6) = 2;
  EXPECT_FLOAT_EQ(m.Determinant(), -1.9803168e+08);
}

TEST(test, determinant_4) {
  S21Matrix m = S21Matrix(10, 9);
  EXPECT_THROW(m.Determinant(), std::logic_error);
}

TEST(test, inverse_1) {
  S21Matrix m = S21Matrix(1, 1);
  m(0, 0) = -5.11;
  S21Matrix result = m.InverseMatrix();
  EXPECT_FLOAT_EQ(result(0, 0), -0.195694716);
}

TEST(test, inverse_2) {
  S21Matrix m = S21Matrix(2, 2);
  m.FullMatrix();
  S21Matrix result = m.InverseMatrix();
  result.PrintMatrix();
  S21Matrix expect = S21Matrix(2, 2);
  expect(0, 0) = -2;
  expect(0, 1) = 1;
  expect(1, 0) = 1.5;
  expect(1, 1) = -0.5;
  EXPECT_TRUE(expect == result);
}

TEST(test, inverse_3) {
  S21Matrix m = S21Matrix(5, 6);
  m.FullMatrix();
  EXPECT_THROW(m.InverseMatrix(), std::logic_error);
}

TEST(test, inverse_4) {
  S21Matrix m = S21Matrix();
  EXPECT_THROW(m.InverseMatrix(), std::logic_error);
}

TEST(test, inverse_5) {
  S21Matrix m = S21Matrix(2, 2);
  EXPECT_THROW(m.InverseMatrix(), std::logic_error);
}

TEST(test, operator_brackets_1) {
  S21Matrix m = S21Matrix(3, 3);
  EXPECT_THROW(m(-1, 1), std::out_of_range);
}

TEST(test, operator_brackets_2) {
  S21Matrix m = S21Matrix(3, 3);
  EXPECT_THROW(m(2, 3), std::out_of_range);
}

TEST(test, operator_brackets_3) {
  S21Matrix m = S21Matrix(3, 3);
  m(2, 2) = 5;
  EXPECT_FLOAT_EQ(m(2, 2), 5);
}

TEST(test, operator_eq_1) {
  S21Matrix m1 = S21Matrix(5, 4);
  m1.FullMatrix();
  S21Matrix m2 = S21Matrix();
  S21Matrix m3 = S21Matrix();
  m3 = m2 = m1;
  EXPECT_TRUE(m1 == m2);
  EXPECT_TRUE(m2 == m3);
}

TEST(test, operator_eq_2) {
  S21Matrix m1 = S21Matrix();
  S21Matrix m2 = S21Matrix();
  S21Matrix m3 = S21Matrix();
  m3 = m2 = m1;
  EXPECT_TRUE(m1 == m2);
  EXPECT_TRUE(m2 == m3);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}