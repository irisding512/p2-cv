// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

TEST(test_matrix_width) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  Matrix_init(mat, width, height);
  ASSERT_EQUAL(Matrix_width(mat), width);

  delete mat;
}

TEST(test_matrix_height) {
   Matrix *mat = new Matrix; // create a Matrix in dynamic memory

   const int width = 3;
   const int height = 5;
   Matrix_init(mat, width, height);
   ASSERT_EQUAL(Matrix_height(mat), height);

   delete mat;
}

TEST(test_matrix_fill_border) {
   Matrix *mat = new Matrix; // create a Matrix in dynamic memory

   const int width = 3;
   const int height = 5;
   const int value = 69;
   const int value2 = 0;
   Matrix_init(mat, width, height);
   Matrix_fill_border(mat, 69);
   Matrix_fill(mat, value2);

  //testing first row
  int r = 0;
  for (int c = 0; c < width; ++c) {
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
  }

  //testing last row
  r = height - 1;
  for (int c = 0; c < width; ++c) {
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
  }

  //testing first column
  int c = 0;
  for (int r = 0; r < height; ++r) {
    ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
  }
  //testing last column
  c = width - 1;
  for (int r = 0; r < height; ++r) {
    ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
  }

   delete mat;
}

TEST (test_matrix_max) {
   Matrix *mat = new Matrix; // create a Matrix in dynamic memory
   const int width = 3;
   const int height = 5;
   const int value = 69;
   const int value2 = 1000;
   Matrix_init(mat, width, height);
   Matrix_fill(mat, value);

   ASSERT_EQUAL(Matrix_max(mat), value);

   *Matrix_at(mat, 0, 0) = value2;
   ASSERT_EQUAL(Matrix_max(mat), value2); 

   delete mat;  
}

TEST(test_column_of_min_value_in_row) {
   Matrix *mat = new Matrix; // create a Matrix in dynamic memory
   const int width = 3;
   const int height = 5;
   const int value = 10;
   const int value2 = 1;
   Matrix_init(mat, width, height);
   Matrix_fill(mat, value);

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 1), 0);

  *Matrix_at(mat, 0, 2) = value2;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 5), 2);

  delete mat;
}

TEST(test_min_value_in_row) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
   const int width = 3;
   const int height = 5;
   const int value = 10;
   const int value2 = 1;
   Matrix_init(mat, width, height);
   Matrix_fill(mat, value);

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 1), value);

  *Matrix_at(mat, 0, 2) = value2;
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 5), value2);

  delete mat;
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
