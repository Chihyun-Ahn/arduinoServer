#include <SoftwareSerial.h>
SoftwareSerial HC12(2,3); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);        // Serial port to computer
  HC12.begin(9600);         // Serial port to HC12
}

void loop()
{
  while(HC12.available()) {
    String receivedMsg = HC12.readStringUntil('\n');
    Serial.println(receivedMsg);
//    Serial.print((char)HC12.read());
//    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//    delay(200);                       // wait for a second
//    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
    HC12.println("Received!!");
  }
  delay(100);
}
