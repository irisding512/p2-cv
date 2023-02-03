// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(test_image_init) {
  Image *img = new Image; // create an Image in dynamic memory

  Image_init(img, 7, 9);

  ASSERT_EQUAL(Image_width(img), 7);
  ASSERT_EQUAL(Image_height(img), 9);

  delete img;
}

TEST(test_image_set_and_get_pixel) {
Image *img = new Image; // create an Image in dynamic memory
Image_init(img, 7, 9);

 const Pixel red = {255, 0, 0};
 const Pixel green = {0, 255, 0};
 const Pixel blue = {0, 0, 255};

  Image_set_pixel(img, 0, 0, red);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).r, red.r);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).g, red.g);
  ASSERT_EQUAL(Image_get_pixel(img, 0, 0).b, red.b);

  Image_set_pixel(img, 1, 1, green);
  ASSERT_EQUAL(Image_get_pixel(img, 1, 1).r, green.r);
  ASSERT_EQUAL(Image_get_pixel(img, 1, 1).g, green.g);
  ASSERT_EQUAL(Image_get_pixel(img, 1, 1).b, green.b);

  Image_set_pixel(img, 2, 2, blue);
  ASSERT_EQUAL(Image_get_pixel(img, 2, 2).r, blue.r);
  ASSERT_EQUAL(Image_get_pixel(img, 2, 2).g, blue.g);
  ASSERT_EQUAL(Image_get_pixel(img, 2, 2).b, blue.b);

  delete img;
}

TEST(test_image_fill) {
  Image *img = new Image;

  Pixel pix {1, 1, 1};
  Image_init(img, 5, 5);
  Image_fill(img, pix);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      ASSERT_EQUAL(Image_get_pixel(img, i, j).r, pix.r);
      ASSERT_EQUAL(Image_get_pixel(img, i, j).g, pix.g);
      ASSERT_EQUAL(Image_get_pixel(img, i, j).b, pix.b);
    }
  }

  delete img;
}

TEST(test_image_from_and_to_stream) {
  Image *img = new Image;

  // A very poorly behaved input PPM.
  string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);

  // Should be well behaved when you print it though!
  string output_correct = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
  std::ostringstream ss_output;
  Image_print(img, ss_output);
  string actual = ss_output.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, output_correct);

  delete img;
}

TEST(test_image_basic) {
  Pixel red = {255, 0, 0};
  Pixel green = {0, 255, 0};
  Image *img = new Image;
  Image_init(img, 3, 4);

  ASSERT_EQUAL(Image_width(img), 3);
  ASSERT_EQUAL(Image_height(img), 4);

  Image_fill(img, red);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 2), red));

  Image_set_pixel(img, 0, 0, green);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), green));

  delete img;
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
