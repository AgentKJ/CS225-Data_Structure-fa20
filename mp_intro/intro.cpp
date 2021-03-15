#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

#include <string>

/**
 * Creates a new output image.
 
 * @param w width of the image
 * @param h height of the image
 
 * @return a pointer to the newly-created image
 */
PNG* setupOutput(unsigned w, unsigned h) {
  PNG* image = new PNG(w, h);
  return image;
}

void rotate(std::string inputFile, std::string outputFile) {
  // Load in.png
  PNG* original = new PNG();
  original->readFromFile(inputFile);
  unsigned width = original->width();
  unsigned height = original->height();
  
  // Create out.png
  PNG* output = setupOutput(width, height);
  
  for (unsigned y = 0; y < height; y++) {
    for (unsigned x = 0; x < width; x++) {
      HSLAPixel &curr = original->getPixel(x, y);
      HSLAPixel &currOutPixel = output->getPixel(width - x - 1, height - y - 1);
      currOutPixel = curr;
    }
  }
  
  // Save the output file
  output->writeToFile(outputFile);
  
  // Clean up memory
  delete original;
}

cs225::PNG myArt(unsigned int width=800, unsigned int height=800) {
  cs225::PNG png(width, height);
  
  // Go over the whole image, and if a pixel differs from that to its upper
  // left, color it my favorite color in the output
  for (unsigned y = 0; y < height; y++) {
    for (unsigned x = 0; x < width; x++) {
      // If the pixel is an edge pixel,
      // color the output pixel with my favorite color
      cs225::HSLAPixel &currOutPixel = png.getPixel(x, y);
      
      if (x % 3 == 0) {
        currOutPixel.h = 0;
        currOutPixel.s = 1;
        currOutPixel.l = 0.5;
        currOutPixel.a = 0.5;
      } else if (x % 3 == 1) {
        currOutPixel.h = 120;
        currOutPixel.s = 1;
        currOutPixel.l = 0.5;
        currOutPixel.a = 0.5;
      } else {
        currOutPixel.h = 240;
        currOutPixel.s = 1;
        currOutPixel.l = 0.5;
        currOutPixel.a = 0.5;
      }
    }
  }

  return png;
}
