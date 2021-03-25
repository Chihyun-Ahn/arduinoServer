#include <avr/sleep.h> 

const int wakePin=2; 
const int led=8; 
int wakeCount = 0;
int loopCount = 0;
boolean armed = true;

void wakeUpNow(){ 
  if(armed){
    wakeCount++;
    Serial.println("Waked up.");
    Serial.println(wakeCount);
    armed = false;
  }
  return;
} 

void setup(){ 
  Serial.begin(115200);
  pinMode(wakePin, INPUT_PULLUP); 
  pinMode(led, OUTPUT); 
//  attachInterrupt(0, wakeUpNow, LOW); 
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

void loop() {
  armed = true;
  loopCount++;
  Serial.print("LoopCount:");
  Serial.print(loopCount);
  Serial.print("\n");
  Serial.println("Blink Start..."); 
  for(int i=0; i<5; i++){
    digitalWrite(led, HIGH); 
    delay(1000); 
    digitalWrite(led, LOW);
    delay(1000);
    Serial.println(i);
  } 
  Serial.println("Good Night.."); 
  delay(1);
  sleepNow(); 
} 
