
/****** These are WIFI Parameters */
const char* ssid = "kvlan2017";
const char* password = "covada6164";
const char* mqtt_server = "192.168.1.126";
/****** ***** ***** ***** ***** ***** */


// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#include "01_wifi_support.h"
/*
*works with hardwired ESP32S2QTPy with Accelerometer I2C connections. NOT the QT I2c end of the board. 
*
 */


float accx, accy, accz;
float total;
String nodeReds;
char Buf[200];
int rows;
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
/*
  #if defined(ARDUINO_ARCH_SAMD)
  // for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
  #define Serial SerialUSB
  #endif
*/
void setup(void) {

  Serial.begin(9600);
  accSetup();

  delay(2000);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");
  delay(2000);
  setup_wifi();
  //  setupTFT ();
  delay(500);
  client.setServer(mqtt_server, 1883);

}

void loop() {

  //  lis.read();      // get X Y and Z data at once

  if (!client.connected()) {
    reconnect();
  }
  client.loop();



  sensors_event_t event;
  lis.getEvent(&event);

  // if (rows % 4 == 0) {
  //   TFTPrintHeader();
  //   rows = 0;
  // }

  // rows++;

  accx = - event.acceleration.x;
  accy = - event.acceleration.y;
  accz = - event.acceleration.z;

  /*  accx =  event.acceleration.x;
    accy =  event.acceleration.y;
    accz =  event.acceleration.z;
  */
  //serial print
  serialPrint();
  //nodered print
  nodeReds = (String)accx + ";" + (String)accy + ";" + (String)accz + ";";
  nodeReds.toCharArray(Buf, 200);
  client.publish("c_acc", Buf);


  //TFT print
 // TFTPrintString(" " + (String)accx + " " + (String) accy + " " + (String) accz);
 // setNextLine();
  delay (500);


}
