// Includes the Servo library
#include <Servo.h>. 
// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;
const int threshold = 30; // 거리 임계값 설정 
// Variables for the duration and the distance
long duration;
int distance;
Servo myServo; // Creates a servo object for controlling the servo motor
Servo turretServo; //고무줄 발사용 모터 제어 
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  myServo.attach(12); // Defines on which pin is the servo motor attached
  turretServo.attach(13); //고무줄 발사용 모터 핀 할당 
}
void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for(int i=15;i<=165;i++){  
  myServo.write(i);
  delay(30);  
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  if(distance <= threshold) {//임계값 이하이면 작동  
    turretServoMove();
  }
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  // Repeats the previous lines from 165 to 15 degrees
  for(int i=165;i>15;i--){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
  if(distance <= threshold) { //임계값 이하이면 작동 
    turretServoMove();
  }
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}

void turretServoMove() { //고무줄 터렛 제어 함수
  int startAngle = turretServo.read();
  turretServo.write(50);
  delay(1000);
  turretServo.write(-50);
  /*
  for(int j=0; j<30; j++) {
    turretServo.write(startAngle + j);
    delay(100); 
  }
  */
}

/*
이 Arduino 코드는 서보 모터와 초음파 센서를 사용하여 주변 거리를 측정하는 프로그램입니다.

주요 내용은 다음과 같습니다:

trigPin과 echoPin 변수를 정의하여 초음파 센서의 Trig와 Echo 핀을 지정합니다.
Servo 라이브러리를 포함하고 myServo 객체를 만들어 서보 모터를 제어합니다.
setup() 함수에서 핀모드를 설정하고 서보 모터를 attached 핀에 연결합니다.
loop() 함수에서 for문을 사용하여 서보 모터 각도를 15도에서 165도까지 변경합니다.
calculateDistance() 함수를 호출하여 각 각도에 대한 거리를 측정합니다.
측정된 각도와 거리를 시리얼 모니터에 출력합니다.
각도를 165도에서 15도까지 반대 방향으로 다시 변경하며 위 과정을 반복합니다.
calculateDistance() 함수에서 초음파 센서의 값을 읽어 거리를 계산하여 리턴합니다.
즉, 서보모터가 회전하면서 초음파센서가 다양한 방향으로 거리를 측정하고 그 값을 시리얼로 출력하는 프로그램입니다.
*/
