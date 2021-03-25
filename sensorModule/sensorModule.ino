#include <SimpleTimer.h>
#include <SoftwareSerial.h>
#include <avr/sleep.h> 

const int wakeUpPin = 2; // pin of interrupt 0
const int LED = 8;
boolean armed = true;

SoftwareSerial mySerial(12,11);

String ID = "0001";
String code = "01";
String msg = "xxxx";

//int cnt = 0;
/*
  Communication protocol
  01: powered on
  02: Sensor touched (Feed is full)
  03: alive
 */

void setup()
{
  String msg = String(ID + code);
  pinMode(wakeUpPin, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  
  Serial.begin(19200);
    
  mySerial.begin(19200); 
  mySerial.println(msg);
  Serial.println(msg);
  
  delay(100);
}

void loop() // 반복
{
  armed = true;
  delay(100);
  Serial.println("Now sleeping.."); 
  delay(200);
  sleepNow(); 

//  cnt++;
//  char strCnt[4];
//  sprintf(strCnt, "%d", cnt);
//  mySerial.println(strCnt);
//  Serial.println("sent msg.");

//  delay(150);
}  

void wakeUpNow(){
  if(armed){
    Serial.println("Waked up. Send Feed full msg. (1001+02)");
    code = "02";
    msg = String(ID + code);
    mySerial.println(msg);
    Serial.print("Msg sent: ");
    Serial.print(msg);
    Serial.print('\n');
    armed = false;
  }
  return;
}

void sleepNow(){
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
  sleep_enable(); 
  attachInterrupt(0,wakeUpNow, LOW); 
  sleep_mode(); 
  sleep_disable(); 
  detachInterrupt(0);   
  return;
}
