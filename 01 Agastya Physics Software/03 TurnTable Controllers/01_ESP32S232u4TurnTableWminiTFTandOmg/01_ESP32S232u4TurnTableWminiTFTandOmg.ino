#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h> // Hardware-specific library
#include "Adafruit_miniTFTWing.h"
#include <Fonts/FreeMonoBoldOblique12pt7b.h>


Adafruit_miniTFTWing ss;
#define TFT_RST    -1    // we use the seesaw for resetting to save a pin



// Anything else!
/**
   Overriding the original code so "everything" will be defaulted these -- since we GnG are using only 32u4 and/or esp32s2, we should be good.
*/
//#if defined (__AVR_ATmega32U4__) || defined(ARDUINO_SAMD_FEATHER_M0) || defined (__AVR_ATmega328P__) || defined(ARDUINO_SAMD_ZERO) || defined(__SAMD51__) || defined(__SAM3X8E__)
#define TFT_CS   5
#define TFT_DC   6
//#endif

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);



//IRSensor PINS

#define LEDPIN 13
// Pin 13: Arduino has an LED connected on pin 13
// Pin 11: Teensy 2.0 has the LED on pin 11
// Pin  6: Teensy++ 2.0 has the LED on pin 6
// Pin 13: Teensy 3.0 has the LED on pin 13

#define SENSORPIN 10
//IR COMPLETE





//HBRIDGE PINS
int motorSpeed = 0;
int m1 = 12;
int m2 = 9;
int pwm = 11;
//int d=0;

void setup()   {

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(pwm, OUTPUT);

  IRSetup();

  Serial.begin(9600);

  if (!ss.begin()) {
    Serial.println("seesaw couldn't be found!");
    while (1);
  }

  Serial.print("seesaw started!\tVersion: ");
  Serial.println(ss.getVersion(), HEX);

  ss.tftReset();   // reset the display
  ss.setBacklight(TFTWING_BACKLIGHT_ON);  // turn off the backlight
  tft.setFont(&FreeMonoBoldOblique12pt7b);
  tft.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display
  Serial.println("TFT initialized");

  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

}
// move to a different tab called motormovements or whatever.
void CCW() {
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
}


void CW() {
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
}

void fSTOP() {
  digitalWrite(m2, LOW);
  digitalWrite(m1, LOW);
}

void loop() {

  controlSpeedDirection();
  IRProcessCrossing();
  printOmegaPeriodically();
}
