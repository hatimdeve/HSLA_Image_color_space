/*
 * File: main.cpp
 * --------------
 * Sample QT project
 */

//#include <iostream>
#include "console.h"
#include "testing/SimpleTest.h"
#include "image.h"
#include "grayscale.h"
#include "illini.h"
#include "gwindow.h"
#include "catch.h"
#include "spotlight.h"
using namespace std;


/*
 * This sample main brings up testing menu.
 */
int main() {

    if (runSimpleTests(SELECTED_TESTS)) {
      return 0;
    }
    cout << "All done, exiting" << endl;

    return 0;

}

Image createRainbowImage() {
  Image png;
  png.resize(360, 100);

  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x, y);
      pixel.h = x;
      pixel.s = y / 100.0;
      pixel.l = y / 100.0;
    }
  }
  return png;
}




PROVIDED_TEST("Image : lighten1")
{
    //Creating an RainBowImage
    Image img = createRainbowImage();

    // Augmenting the light
    Image result = createRainbowImage();
    result.lighten();

    EXPECT_EQUAL(img.getPixel(10, 10).l + 0.1 ,  result.getPixel(10, 10).l );

}

PROVIDED_TEST("Image lighten() does not lighten a pixel above 1.0")
{
  Image img = createRainbowImage();

  Image result = createRainbowImage();
  result.lighten();

  EXPECT_EQUAL( 1.0 , result.getPixel(10, 95).l );
}

PROVIDED_TEST("Image darken(0.2) darkens pixels by 0.2") {
  Image img = createRainbowImage();

  Image result = createRainbowImage();
  result.lighten(-0.2);

 EXPECT_EQUAL( img.getPixel(50, 50).l - 0.2 , result.getPixel(50, 50).l );
}

PROVIDED_TEST("Image darken(0.2) does not darken a pixel below 0.0") {
  Image img = createRainbowImage();

  Image result = createRainbowImage();
  result.lighten(-0.2);

  EXPECT_EQUAL( 0 , result.getPixel(5, 5).l );
}

PROVIDED_TEST("Image saturate() saturates a pixels by 0.1") {
  Image img = createRainbowImage();

  Image result = createRainbowImage();
  result.saturate(0.1);

  EXPECT_EQUAL(img.getPixel(10, 10).s + 0.1 , result.getPixel(10, 10).s );
}

PROVIDED_TEST("Image rotateColor(double) rotates the color") {
  Image img = createRainbowImage();

  Image result = createRainbowImage();
  result.rotateColor(90);

  EXPECT_EQUAL( img.getPixel(90, 90).h + 90 , result.getPixel(90, 90).h );
}
PROVIDED_TEST("Image rotateColor(double) keeps the hue in the range [0, 360]" ) {
  Image img = createRainbowImage();

  Image result = createRainbowImage();
  result.rotateColor(90);
  EXPECT_EQUAL( result.getPixel(340, 90).h ,  70 );

  result.rotateColor(-180);
  EXPECT_EQUAL( result.getPixel(10, 90).h , 280 );
}


PROVIDED_TEST("Grayscale Image " ) {

    Grayscale Img("res/haikyuu.png");

    EXPECT_EQUAL(Img.getPixel(25, 23).s,  0.0);
}





PROVIDED_TEST("illini") {

    Illini result("res/ranbow.png");

    for (unsigned x = 0; x < result.width(); x++) {
        for (unsigned y = 0; y < result.height(); y++) {
          EXPECT(result.getPixel(x, y).h == 11 || result.getPixel(x, y).h == 216);
        }
      }
    }



PROVIDED_TEST("Pixels closest to blue become blue") {

   Illini result("res/ranbow.png");

  EXPECT_EQUAL( result.getPixel(200, 4).h , 216 );
  EXPECT_EQUAL( result.getPixel(210, 12).h , 216 );
  EXPECT_EQUAL( result.getPixel(220, 23).h , 216 );
  EXPECT_EQUAL( result.getPixel(230, 44).h , 216 );
}

PROVIDED_TEST("Pixels closest to orange become orange") {

  Illini result("res/ranbow.png");
  EXPECT_EQUAL( result.getPixel(10, 4).h , 11 );
  EXPECT_EQUAL( result.getPixel(30, 12).h , 11 );
  EXPECT_EQUAL( result.getPixel(40, 23).h , 11 );
  EXPECT_EQUAL( result.getPixel(40, 44).h , 11 );
}

PROVIDED_TEST("Hue wrap-arounds are correct (remember: h=359 is closer to orange than blue)") {

  Illini result("res/ranbow.png");
  EXPECT_EQUAL( result.getPixel(330, 4).h , 11 );
  EXPECT_EQUAL( result.getPixel(340, 12).h , 11 );
  EXPECT_EQUAL( result.getPixel(350, 23).h , 11 );
}


PROVIDED_TEST("Spotlight does not modify the center pixel") {
  Spotlight result("res/ranbow.png",100, 50);
  Image png("res/ranbow.png");
  EXPECT_EQUAL( png.getPixel(100, 50).l , result.getPixel(100, 50).l );
}


PROVIDED_TEST("Spotlight creates an 80% dark pixel >160 pixels away") {
    Spotlight result("res/ranbow.png",100, 50);
    Image png("res/ranbow.png");
    EXPECT(fabs(png.getPixel(320,50).l *0.2 - result.getPixel(320,50).l) <= 1E-6);
}

PROVIDED_TEST("Spotlight is correct at 20 pixels away from center") {

    Spotlight result("res/ranbow.png",100, 50);
    Image png("res/ranbow.png");
    EXPECT_EQUAL( png.getPixel(100, 50 + 20).l * 0.9 , result.getPixel(100, 50 + 20).l );
}

PROVIDED_TEST("Spotlight is correct at 5 pixels away from center") {

    Spotlight result("res/ranbow.png",100, 50);
    Image png("res/ranbow.png");
    EXPECT_EQUAL( png.getPixel(100 + 3, 50 + 4).l * 0.975 , result.getPixel(100 + 3, 50 + 4).l );
}





