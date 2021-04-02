#include <SimpleTimer.h>

SimpleTimer timer; 



void setup() {               
    Serial.begin(9600);
    timer.setInterval(1000, repeatMe);        // 이와같이 타이머를 설정할 수 있다. 파라미터는 '시간(밀리초)', 'function이름' 2개다
}

void loop() {
//    timer.run();                    // loop 부분에 이와같이 run()을 실행해줘야한다.
    test();
    Serial.println("hahaha.");
    delay(random(100,500));
}

void repeatMe() {   
    Serial.print("Uptime (s): ");
    Serial.println(millis() / 1000);
}

void test(){
  timer.run();
  return;  
}
