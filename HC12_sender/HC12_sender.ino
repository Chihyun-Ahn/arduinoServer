#include <SoftwareSerial.h>

String ID = "0001";
String code = "01";
//int
String msg = "xxxx";
/*
  Communication protocol
  01: powered on
  02: Sensor touched (Feed is full)
  03: alive
 */

SoftwareSerial HC12(4,5); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);               // Serial port to HC12
  String msg = String(ID + code);
  HC12.println(msg);
  Serial.println(msg);
  delay(100);
}

void loop()
{
  code = "03";
  msg = String(ID+code);
  HC12.println(msg);
  Serial.print("Msg sent: ");
  Serial.print(msg);
  Serial.print('\n');
  Serial.println("Waiting ACK.");
  if(HC12.available()){
    Serial.println(HC12.readStringUntil('\n'));
    
  }
  delay(800);
}
