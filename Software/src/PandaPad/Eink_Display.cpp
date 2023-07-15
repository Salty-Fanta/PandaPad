//#include "Eink_Display.h"

#include <arduino.h>
#include <GxEPD2_BW.h>
#include <pgmspace.h>
#include <cstdint>

#include "Display/ScreenSelection/GxEPD2_display_selection_new_style.h"

#include "Display/Icons/Panda_Logo.h"

#include <Fonts/FreeMonoBold9pt7b.h> //optional font, will be replaced

const char HelloWorld[] = "Hello World!";

void helloWorld(int rotation)
{
  display.setRotation(rotation);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
  }
  while (display.nextPage());
}

void DrawBitmap()
{
  display.setRotation(3);
  //bool m = display.mirror(true);
  display.firstPage();
  do
  {
  display.fillScreen(GxEPD_WHITE);
  //display.drawInvertedBitmap(0, 0, Bitmap128x296_1, 128, 296, GxEPD_BLACK);
  
  
  display.drawInvertedBitmap(72, 0, Panda_Logo, Panda_Logo_Width, Panda_Logo_Height, GxEPD_BLACK);
  }
  while (display.nextPage());
  delay(1000); //arduino
  //display.mirror(m);
}

void DisplayInit(){
  //display.init(115200); // default 10ms reset pulse, e.g. for bare panels with DESPI-C02
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
}

void DisplayHibernate(){
  display.hibernate();
}
