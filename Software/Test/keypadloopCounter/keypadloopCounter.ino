#include <Keypad.h>


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'},
  {'0','1','2','3'}
};
byte rowPins[ROWS] = {38, 39, 40, 12}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {42, 41, 6, 34}; //connect to the column pinouts of the keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount = 0;
unsigned long keytimer_t = 0;

void setup(){
	Serial.begin(9600);
	
	// Try playing with different debounceTime settings to see how it affects
	// the number of times per second your loop will run. The library prevents
	// setting it to anything below 1 millisecond.
	kpd.setDebounceTime(10);	// setDebounceTime(mS)
}

void loop(){
	char key = kpd.getKey();
	
	// Report the number of times through the loop in 1 second. This will give
	// you a relative idea of just how much the debounceTime has changed the
	// speed of your code. If you set a high debounceTime your loopCount will
	// look good but your keypresses will start to feel sluggish.
	if ((millis() - keytimer_t) > 1000) {
		Serial.print("Your loop code ran ");
		Serial.print(loopCount);
		Serial.println(" times over the last second");
		loopCount = 0;
		keytimer_t = millis();
	}
	loopCount++;
	if(key)
		Serial.println(key);
}
