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
   Matrix_fill(mat, value2);
   Matrix_fill_border(mat, value);

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

  //testing items that shouldn't have been filled
  ASSERT_EQUAL(*Matrix_at(mat, 1, 1), value2);
  
    for (int r = 1; r < height - 1; r++) {
      for (int c = 1; c < width - 1; c++) {
        ASSERT_EQUAL(*Matrix_at(mat, r, c), value2);
      }
    }

  delete mat;
}

TEST (test_matrix_max) {
   Matrix *mat = new Matrix; // create a Matrix in dynamic memory
   const int width = 3;
   const int height = 5;
   const int value = 69;
   const int value2 = 1000;
   const int value3 = 10000;
   Matrix_init(mat, width, height);
   Matrix_fill(mat, value);

   ASSERT_EQUAL(Matrix_max(mat), value);

   *Matrix_at(mat, 0, 0) = value2;
   ASSERT_EQUAL(Matrix_max(mat), value2); 

   *Matrix_at(mat, 1, 1) = value3;
   ASSERT_EQUAL(Matrix_max(mat), value3); 

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

  for (int i = 0; i < height; i++) {
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 
                  i, 0, width - 1), 0);
  }

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 1), 0);

  *Matrix_at(mat, 1, 2) = value2;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 1, 3), 2);

  delete mat;
}

TEST(test_min_value_in_row) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
   const int width = 3;
   const int height = 5;
   const int value = 10;
   const int value2 = 1;
   const int value3 = 0;
   Matrix_init(mat, width, height);
   Matrix_fill(mat, value);

  for (int i = 0; i < mat->height; i++) {
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, i, 0, 
                          mat->width - 1), value);
  }

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 1), value);

  *Matrix_at(mat, 0, 2) = value2;
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 3), value2);

  *Matrix_at(mat, 0, 1) = value3;
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 3, 0, 2), value);

  delete mat;
}

TEST(test_matrix_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  *Matrix_at(mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST(test_matrix_row) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
   const int width = 3;
   const int height = 5;
   int value = 10;
   Matrix_init(mat, width, height);
   Matrix_fill(mat, value);

   int *ptr = Matrix_at(mat, 0, 0);  //&mat->data[0], changed / respect M 
   ASSERT_EQUAL(Matrix_row(mat, ptr), 0);

   int *ptr2 = Matrix_at(mat, 4, 2);
   ASSERT_EQUAL(Matrix_row(mat, ptr2), height - 1);

   int *ptr3 = Matrix_at(mat, 2, 1);
   ASSERT_EQUAL(Matrix_row(mat, ptr3), 2);

   delete mat;
}

TEST(test_matrix_column) {
   Matrix *mat = new Matrix; // create a Matrix in dynamic memory
   const int width = 3;
   const int height = 5;
   int value = 10;
   Matrix_init(mat, width, height);
   Matrix_fill(mat, value);

   int *ptr = Matrix_at(mat, 0, 0); //&mat->data[0], changed / respect M 
   ASSERT_EQUAL(Matrix_column(mat, ptr), 0);

   int *ptr2 = Matrix_at(mat, 4, 2);
   ASSERT_EQUAL(Matrix_column(mat, ptr2), 2);

   int *ptr3 = Matrix_at(mat, 4, 2);
   ASSERT_EQUAL(Matrix_column(mat, ptr3), width - 1);

   delete mat;
}

TEST(test_matrix_basic) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 5);

  ASSERT_EQUAL(Matrix_width(mat), 5);
  ASSERT_EQUAL(Matrix_height(mat), 5);

  Matrix_fill(mat, 0);

  int *ptr = Matrix_at(mat, 2, 3);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 3);
  ASSERT_EQUAL(*ptr, 0);
  *ptr = 42;

  const int *cptr = Matrix_at(mat, 2, 3);
  ASSERT_EQUAL(*cptr, 42);

  Matrix_fill_border(mat, 2);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 2);

  delete mat;
}

TEST(test_matrix_at) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
   const int width = 3;
   const int height = 5;
   const int value = 10;
   const int value2 = 100;
   Matrix_init(mat, width, height);
   Matrix_fill(mat, value);
   
   ASSERT_EQUAL(*Matrix_at(mat, 2, 2), 10);

   *Matrix_at(mat, 1, 2) = value2;
   ASSERT_EQUAL(*Matrix_at(mat, 1, 2), 100);

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
