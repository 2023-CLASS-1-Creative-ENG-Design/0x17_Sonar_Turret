//발사용 코드
//시리얼 모니터에 s를 누루면 발사 d를 누루면 재장전용
#include <Stepper.h>

const int STEPS = 2037;

Stepper myStepper(STEPS,4,6,5,7);

void setup(){
  Serial.begin(9600);
  myStepper.setSpeed(12);
}

void loop() {
  if (Serial.available()) {
    char c= Serial.read();
    if (c == 's'){
      delay(1000);
      myStepper.step(2500);
    }
    else if(c == 'd'){
      myStepper.step(-2500);
    }
  }
}
