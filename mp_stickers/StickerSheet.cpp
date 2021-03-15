#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
  base_ = new Image(picture);
  size_ = max;
  x_ = new unsigned[max];
  y_ = new unsigned[max];
  ptrArray_ = new Image*[size_];
  amount = 0;
}

StickerSheet::~StickerSheet() {
  for (unsigned i = 0; i < amount; i++) {
    delete ptrArray_[i];
  }
  delete[] ptrArray_;
  delete base_;
  delete[] x_;
  delete[] y_;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
  ptrArray_ = NULL;
  base_ = NULL;
  x_ = NULL;
  y_ = NULL;
  delete[] ptrArray_;
  delete base_;
  delete[] x_;
  delete[] y_;

  _copy(other);
}

void StickerSheet::_copy(StickerSheet const & other) {
  size_ = other.size_;
	base_ = new Image(*other.base_);
	amount = other.amount;
  x_ = new unsigned[size_];
  for (unsigned i = 0; i < amount; i++) {
    x_[i] = other.x_[i];
  }
  y_ = new unsigned[size_];
  for (unsigned i = 0; i < amount; i++) {
    y_[i] = other.y_[i];
  }
	ptrArray_ = new Image*[size_];
	for (unsigned i = 0; i < amount; i++) {
		ptrArray_[i] = new Image();
		*ptrArray_[i] = *(other.ptrArray_[i]);
	}
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
  if (this != &other) {
    delete[] ptrArray_;
    delete[] x_;
    delete[] y_;
    delete base_;
    _copy(other);
  }
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
  Image **newPtrArray_ = new Image*[amount];
  unsigned *newx_ = new unsigned[amount];
  unsigned *newy_ = new unsigned[amount];
  for (unsigned i = 0; i < amount; i++) {
    newPtrArray_[i] = ptrArray_[i];
    newx_[i] = x_[i];
    newy_[i] = y_[i];
  }
  delete[] x_;
  delete[] y_;
  delete[] ptrArray_;

  if (max >= amount) {
    ptrArray_ = new Image*[max];
    x_ = new unsigned[max];
    y_ = new unsigned[max];
    for (unsigned i = 0; i < amount; i++) {
      ptrArray_[i] = newPtrArray_[i];
      x_[i] = newx_[i];
      y_[i] = newy_[i];
    }
    size_ = max;
    delete[] newx_;
    delete[] newy_;
    delete[] newPtrArray_;
  } else {
    for (unsigned i = max; i < amount; i++) {
      delete newPtrArray_[i];
      newPtrArray_[i] = NULL;
    }
    amount = max;
    size_ = max;
    ptrArray_ = new Image*[max];
    x_ = new unsigned[max];
    y_ = new unsigned[max];
    for (unsigned i = 0; i < max; i++) {
      ptrArray_[i] = newPtrArray_[i];
      x_[i] = newx_[i];
      y_[i] = newy_[i];
    }
    delete[] newx_;
    delete[] newy_;
    delete[] newPtrArray_;
  }
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
  if (amount < size_) {
    ptrArray_[amount] = new Image(sticker);
    x_[amount] = x;
    y_[amount] = y;
    amount++;
    return amount;
  } else {
    return -1;
  }
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (index < 0 || index > amount - 1) {
    return false;
  } else {
    x_[index] = x;
    y_[index] = y;
    return true;
  }
}

void StickerSheet::removeSticker(unsigned index) {
  if (index >= 0 && index <= size_ - 1) {
    delete ptrArray_[index];
    for (unsigned i = index; i < size_ - 1; i++) {
      x_[i] = x_[i + 1];
		  y_[i] = y_[i + 1];
      ptrArray_[i] = ptrArray_[i + 1];
    }
    x_[size_ - 1] = 0; 
    y_[size_ - 1] = 0;
    ptrArray_[size_ - 1] = NULL;
    amount--;
  }
}

Image* StickerSheet::getSticker(unsigned index) {
  if (index < 0 || index >= amount) {
    return NULL;
  } else {
    return ptrArray_[index];
  }
}

Image StickerSheet::render() const {
  Image result(*base_);
  for (unsigned i = 0; i < amount; i++){
    if (ptrArray_[i]->width() + x_[i] > result.width()) {
      result.resize(ptrArray_[i]->width() + x_[i], result.height());
    }
    if (ptrArray_[i]->height() + y_[i] > result.height()) {
      result.resize(result.width(), ptrArray_[i]->height() + y_[i]);
    }
    for (unsigned x1 = 0; x1 < ptrArray_[i]->width(); x1++) {
      for (unsigned y1 = 0; y1 < ptrArray_[i]->height(); y1++) {
        HSLAPixel &pixel = result.getPixel(x_[i] + x1, y_[i] + y1);
        if (ptrArray_[i]->getPixel(x1, y1).a != 0) {
          pixel = ptrArray_[i]->getPixel(x1, y1);
        }
      }
    }
  }
  return result;
}