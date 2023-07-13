#include <Adafruit_NeoPixel.h>  //inclusion of Adafruit's NeoPixel (RBG addressable LED) library

#define PIN            13 // Which pin on the Arduino is connected to the NeoPixels?
#define NUMPIXELS      16 // How many NeoPixels are attached to the Arduino? 11 total, but they are address from 0,1,2,...10.


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int keyBrightness = 40;       // Brightness control variable. Used to divide the RBG vales set for the RGB LEDs. full range is 0-255. 255 is super bright
                       // In fact 255 is obnoxiously bright, so this use this variable to reduce the value. It also reduces the current draw on the USB
uint16_t keyHue = 4335; 

#define LDO_power     17 //ldo power swith pin



void setup() {
  pinMode(LDO_power, OUTPUT);
  delay(100);
  digitalWrite(LDO_power, HIGH);
  delay(1000);
  
  
  // put your setup code here, to run once:
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(keyBrightness);

  
  pixels.fill(pixels.gamma32(pixels.ColorHSV(keyHue)), 0, pixels.numPixels());
  pixels.show();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(1000); // Pause before next pass through loop
  }
}
