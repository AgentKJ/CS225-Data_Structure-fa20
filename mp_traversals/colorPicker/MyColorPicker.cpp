#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(double increment)
  : increment_(increment), l_(0) { }
  
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(22.5, 1, l_);
  l_ += increment_;
  if (l_ >= 1) {
    l_ -= 1;
  }
  return pixel;
}
