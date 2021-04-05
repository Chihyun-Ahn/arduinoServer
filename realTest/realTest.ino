#include <SimpleTimer.h>

#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define IDlen 4
#define maxID 5

SoftwareSerial mySerial(2,3);
LiquidCrystal_I2C lcd(0x27, 16, 2);
int upButtonPin = 7;
int selectButtonPin = 6;
int downButtonPin = 5;
int sensors[maxID] = {1001,9999,9999,9999,9999};
int receivedID = 0;
int currentPos = 0;
//String ack = "0000";

//void printSensor(int intID);
void menu();
void showAllSensors();
int removeID(int senNumInt);

void setup()
{
  Serial.begin(9600);
  Serial.println("Serial began.");

  mySerial.begin(9600);
  mySerial.println("mySerial began.");
  
  lcd.begin();
  pinMode(upButtonPin,  INPUT_PULLUP);
  pinMode(selectButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
}

void loop()
{
  lcd.setCursor(1,1);
  lcd.clear();
  lcd.print("Ready");
  if(digitalRead(upButtonPin)==LOW){
    lcd.clear();
    lcd.print("Up btn pressed!");
  }
  if(digitalRead(downButtonPin)==LOW){
    lcd.clear();
    lcd.print("Down btn pressed!");
  }
  if(digitalRead(selectButtonPin)==LOW){
    lcd.clear();
    lcd.print("Registered sensors:");
    delay(1000);
    lcd.clear();
    showAllSensors();
    menu();
  }
  if(mySerial.available()>0){
    
    String rcvMsg = mySerial.readStringUntil('\n');
    Serial.println(rcvMsg);
    receivedID = rcvMsg.substring(0,4).toInt();
    Serial.println(receivedID);
    delay(800);
    
    for (int i=0;i<maxID;i++){
      Serial.print(sensors[i]);
      Serial.print(receivedID);
      if(sensors[i] == receivedID){
        String temp = String(receivedID);
        String ack = String(temp + "01"); // 01: success 02: reject (ID does not exist)
        Serial.print("Ack sent: ");
        Serial.print(ack);
        for(int i=0;i<200;i++){
          mySerial.println(ack); 
          delay(100);
        } 
      }
    }
    
//    mySerial.write(rcvMsg);
  }
//  delay(200);
}

void menu(){
  lcd.print("UP: add sensor");
  lcd.setCursor(0,1);
  lcd.print("DOWN: del sensor");
  lcd.setCursor(0,0);
  
  while(1){  
    if(digitalRead(upButtonPin)==LOW){
      lcd.clear();
      lcd.print("Add sensor:");
      delay(1500);
      lcd.clear();
      int senNumInt = 1000;
      char senNum[IDlen];
      sprintf(senNum, "%d", senNumInt);
      
      while(1){   
        lcd.print(senNum);
        if(digitalRead(upButtonPin)==LOW){
          senNumInt++;
          sprintf(senNum, "%d", senNumInt);
          lcd.clear();
          lcd.print(senNum);
        }
        if(digitalRead(downButtonPin)==LOW){
          senNumInt--;
          sprintf(senNum, "%d", senNumInt);
          lcd.clear();
          lcd.print(senNum);
        }
        if(digitalRead(selectButtonPin)==LOW){
          lcd.clear();
          lcd.print(senNum);
          lcd.setCursor(0,1);
          lcd.print("Menu: OK, Down: Cancel");
          //센서 입력값을 받아서, 리스트에 넣어 놓기
          sensors[currentPos] = senNumInt;
          lcd.clear();
          showAllSensors();       
          delay(1500);
          break; // 값 입력 후 저장한 것 보여주고... 나가기.
        }
        delay(200);
        lcd.clear();
      }
      delay(200);
      break;
    } // up button 누름 메뉴 끝

    if(digitalRead(downButtonPin)==LOW){
      lcd.clear();
      lcd.print("Remove sensor:");
      delay(1500);
      lcd.clear();
      int senNumInt = 1000;
      char senNum[IDlen];
      sprintf(senNum, "%d", senNumInt);

      while(1){   
        lcd.print(senNum);
        if(digitalRead(upButtonPin)==LOW){
          senNumInt++;
          sprintf(senNum, "%d", senNumInt);
          lcd.clear();
          lcd.print(senNum);
        }
        if(digitalRead(downButtonPin)==LOW){
          senNumInt--;
          sprintf(senNum, "%d", senNumInt);
          lcd.clear();
          lcd.print(senNum);
        }
        if(digitalRead(selectButtonPin)==LOW){
          lcd.clear();
          lcd.print(senNum);
          lcd.setCursor(0,1);
          lcd.print("Delete sensor");
          delay(600);
          lcd.clear();
          
          //센서 입력값을 받아서, 리스트에서 찾은 후 삭제
          int result = removeID(senNumInt);
          if(result==1){
            lcd.print("Deleted.");
            showAllSensors();       
          }else{
            lcd.print("No such ID!!");
          };
          delay(1500);
          break; // 값 입력 후 저장한 것 보여주고... 나가기.
        }
        delay(200);
        lcd.clear();
      }
      delay(200);
      break;
    } // down button 누름 메뉴 끝
    
    
    
    delay(200);
  }
  return;
}

void showAllSensors(){
  char imsi[IDlen];
  for(int i=0;i<maxID;i++){
    Serial.println(sensors[i]);
    sprintf(imsi, "%d", sensors[i]);
    lcd.print(imsi);
    delay(800);
    lcd.clear();
  }
  return;
}

int removeID(int senNumInt){
  int isFound = 0;
  for(int i=0;i<maxID;i++){
    if(sensors[i] == senNumInt){
      sensors[i] = 9999;
      isFound = 1;
    }
  }
  return isFound;
}
