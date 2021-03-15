#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  alma.readFromFile("alma.png");
  Image i;
  i.readFromFile("i.png");

  StickerSheet sheet(alma, 100);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 80, 200);
  sheet.addSticker(i, 140, 200);
  sheet.addSticker(i, 200, 200);
  sheet.translate(0, 0, 0);
  sheet.render().writeToFile("myImage.png");
  return 0;
}
