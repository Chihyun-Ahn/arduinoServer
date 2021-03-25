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
  if(mySerial.available()>0){
    Serial.write(mySerial.read());
  }
  if(Serial.available()>0){
    mySerial.write(Serial.read());
  }
}
