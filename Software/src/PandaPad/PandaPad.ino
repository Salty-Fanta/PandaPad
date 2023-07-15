/*

PandaPad

-----------------------------
| 0 | 1 |                   |
---------   E-ink screen    -
| 2 | 3 |                   |
-----------------------------
|           | 4 | 5 | 6 | 7 |
-           -----------------
| Touchpad  | 8 | 9 | A | B |
-           -----------------
|           | C | D | E | F |
-----------------------------

*/

/********************************************************/
//DISPLAY INITS


#include <GxEPD2_BW.h>
#include <pgmspace.h>

//#include "Display/ScreenSelection/GxEPD2_display_selection_new_style.h" //BUG: if done here Eink_Display functions can't acces display class
#include "Eink_Display.h"

/********************************************************/
//LED INITS

#include <Adafruit_NeoPixel.h>  //inclusion of Adafruit's NeoPixel (RBG addressable LED) library

#define PIN            13 // Which pin on the Arduino is connected to the NeoPixels?
#define NUMPIXELS      16 // How many NeoPixels are attached to the Arduino? 11 total, but they are address from 0,1,2,...10.


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int keyBrightness = 40;       // Brightness control variable. Used to divide the RBG vales set for the RGB LEDs. full range is 0-255. 255 is super bright
                       // In fact 255 is obnoxiously bright, so this use this variable to reduce the value. It also reduces the current draw on the USB
uint16_t keyHue = 4335; 

#define LDO_power     17 //ldo power swith pin


/********************************************************/
//USB INPUT INIT
 
#include "USB.h"
#include "USBHIDKeyboard.h"
#include "USBHIDMouse.h"
USBHIDMouse Mouse;
USBHIDKeyboard Keyboard;

#include <CirquePinnacle.h>
#include <Keypad.h>

#define SS_PIN 2
#define DR_PIN 7

PinnacleTouchI2C trackpad(DR_PIN);
RelativeReport data;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char Keys[ROWS][COLS] = {
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'},
  {'0','1','2','3'}
};


byte rowPins[ROWS] = {38, 39, 40, 12}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {42, 41, 6, 34}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS); 




void setup() {
  Serial.begin(115200);
  
  Keyboard.begin();
  USB.begin();

  if (!trackpad.begin()) {
    Serial.println(F("Cirque Pinnacle not responding!"));
  }
  Serial.println(F("CirquePinnacle/examples/relative_mode"));
  trackpad.setDataMode(PINNACLE_RELATIVE);
  trackpad.relativeModeConfig(); // uses default config
  Serial.println(F("Touch the trackpad to see the data."));

  Mouse.begin();


  DisplayInit();
  DrawBitmap();
  DisplayHibernate();


  pinMode(LDO_power, OUTPUT);
  delay(100);
  digitalWrite(LDO_power, HIGH);
  delay(1000);
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(keyBrightness);

  
  pixels.fill(pixels.gamma32(pixels.ColorHSV(keyHue)), 0, pixels.numPixels());
  pixels.show();
  delay(1000);
}

void loop() {

  char customKey = customKeypad.getKey();

  if (customKey){
    Keyboard.write(customKey);
  }

  if (trackpad.available()) {
    trackpad.read(&data);
    
    Mouse.move(-1*(data.y), -1*(data.x));
    if (data.buttons & 1){
      Mouse.click(MOUSE_LEFT);
    }
  }
  
}
