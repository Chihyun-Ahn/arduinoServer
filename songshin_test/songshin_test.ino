#include <SoftwareSerial.h>
SoftwareSerial mySerial(12,11);

void setup()
{
  Serial.begin(19200);
  Serial.println("Good Morning!");
  mySerial.begin(19200); 
  mySerial.println("Hello ??");
}

void loop() // 반복
{
  mySerial.println("Msg!!");
  Serial.println("Good morning");
  delay(150);
}
