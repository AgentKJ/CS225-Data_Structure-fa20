#include "Image.h"
#include "cs225/HSLAPixel.h"
#include <cmath>

using cs225::PNG;
using cs225::HSLAPixel;

void Image::lighten() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel &pixel = this->getPixel(x, y);
      if (pixel.l <= 0.9) {
        pixel.l += 0.1;
      } else {
        pixel.l = 1;
      }
    }
  }
}

void Image::lighten(double amount) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel &pixel = this->getPixel(x, y);
      if (pixel.l + amount <= 1) {
        pixel.l += amount;
      } else {
        pixel.l = 1;
      }
    }
  }
}

void Image::darken() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel &pixel = this->getPixel(x, y);
      if (pixel.l >= 0.1) {
        pixel.l -= 0.1;
      } else {
        pixel.l = 0;
      }
    }
  }
}

void Image::darken(double amount) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel &pixel = this->getPixel(x, y);
      if (pixel.l - amount >= 0) {
        pixel.l -= amount;
      } else {
        pixel.l = 0;
      }
    }
  }
}

void Image::saturate() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel &pixel = this->getPixel(x, y);
      if (pixel.s <= 0.9) {
        pixel.s += 0.1;
      } else {
        pixel.s = 1;
      }
    }
  }
}

void Image::saturate(double amount) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel &pixel = this->getPixel(x, y);
      if (pixel.s + amount <= 1) {
        pixel.s += amount;
      } else {
        pixel.s = 1;
      }
    }
  }
}

void Image::desaturate() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel &pixel = this->getPixel(x, y);
      if (pixel.s >= 0.1) {
        pixel.s -= 0.1;
      } else {
        pixel.s = 0;
      }
    }
  }
}

void Image::desaturate(double amount) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel &pixel = this->getPixel(x, y);
      if (pixel.s - amount >= 0) {
        pixel.s -= amount;
      } else {
        pixel.s = 0;
      }
    }
  }
}

void Image::grayscale() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel &pixel = this->getPixel(x, y);
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees) {
  double toRotate = std::fmod(degrees, 360);
  for (unsigned int x = 0; x < this->width(); x++) {
    for (unsigned int y = 0; y < this->height(); y++) {
      HSLAPixel &pixel = this->getPixel(x, y);
      if (pixel.h + toRotate < 360) {
        pixel.h += toRotate;
      } else {
        pixel.h = std::fmod((pixel.h + toRotate), 360);
      }
      if (pixel.h < 0) {
        pixel.h += 360;
      }
    }
  }
}

void Image::illinify() {
  for (unsigned int x = 0; x < this->width(); x++) {
    for (unsigned int y = 0; y < this->height(); y++) {
      HSLAPixel &pixel = this->getPixel(x, y);
      if ((pixel.h >= 216 && pixel.h <= 293) || (pixel.h <= 216 && pixel.h >= 114)) {
        pixel.h = 216;
      } else {
        pixel.h = 11;
      }
    }
  }
}

void Image::scale(double factor) {
  unsigned int w = this->width() * factor;
  unsigned int h = this->height() * factor;
  Image *newImage = new Image(*this);
  this->resize(w, h);
  for (unsigned i = 0; i < h; i++) {
    for (unsigned j = 0; j < w; j++) {
      HSLAPixel &pixel = this->getPixel(j, i);
      HSLAPixel &newPixel = newImage->getPixel(j / factor, i / factor);
      pixel = newPixel;
    }
  }
  delete newImage;
}

void Image::scale(unsigned w, unsigned h) {
  Image *newImage = new Image(*this);
  this->resize(w, h);
  double x_ratio = w / width();
  double y_ratio = h / height();
  for (unsigned i = 0; i < h; i++) {
    for (unsigned j = 0; j < w; j++) {
      HSLAPixel &pixel = this->getPixel(j, i);
      HSLAPixel &newPixel = newImage->getPixel(j / x_ratio, i / y_ratio);
      pixel = newPixel;
    }
  }
  delete newImage;
}
