#include <SoftwareSerial.h>
#include <avr/sleep.h> 
#include <SimpleTimer.h>

SimpleTimer timer;
const int wakeUpPin = 2; // pin of interrupt 0
const int LED = 8;
const int numMsg = 1; // For the safety, send multiple messages, everytime.  
boolean armed = true;
SoftwareSerial mySerial(4,5);
String ID = "1001";
String code = "01";
String msg = "xxxx";
String rcvMsg = "xxxx";
int timerID = 0;

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
  timerID = timer.setInterval(1000, sendMsg);
  
  Serial.begin(9600);  
  mySerial.begin(9600); 
  
//  mySerial.println(msg);
  Serial.println(msg);
  
  delay(100);
}

void loop() // 반복
{
  Serial.println("start loop.");
  armed = true;
  delay(100);
  Serial.println("Now sleeping.."); 
  delay(200);
  sleepNow(); 
}  

void wakeUpNow(){
  if(armed){
    Serial.println("Waked up. Send Feed full msg.");
    delay(200);
    code = "02";
    msg = String(ID + code);
    sendMsg();
//    timer.run();

//    Serial.print("Msg sent: ");
//    Serial.print(msg);
//    Serial.print('\n');
//    Serial.print("Timer started. waiting for response.\n");
    while(1){
      Serial.println("**");
      if(mySerial.available()>0){
        Serial.println("RECEIVED!!!!");
        rcvMsg = mySerial.readStringUntil('\n');
        if(rcvMsg.substring(0,4).equals(ID)){
          timer.deleteTimer(timerID);
          Serial.println("My msg is received successfully. Now sleep again..");
          break;
        }
      }
//      delay(100);  
    }
    armed = false;
  }
  return;
}

void sleepNow(){
  Serial.println("Entered sleep now()");
  delay(100);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
  sleep_enable(); 
  attachInterrupt(0,wakeUpNow, LOW); 
  sleep_mode(); 
  sleep_disable(); 
  detachInterrupt(0);   
  return;
}

void sendMsg(){
  for (int i=0;i<numMsg;i++){
    mySerial.println(msg);
  }
  return;
}
