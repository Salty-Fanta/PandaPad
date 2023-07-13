/*

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

#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;

#include <Keypad.h>

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
  // put your setup code here, to run once:
  Keyboard.begin();
  USB.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  char customKey = customKeypad.getKey();

  if (customKey){
    Keyboard.write(customKey);
  }
  
}
