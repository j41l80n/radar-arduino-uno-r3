#include <SPI.h>
//#include <Servo.h>
#include <VarSpeedServo.h>
#include <hcsr04.h>

#define SERVO 12
#define PINO_TRIG 4
#define PINO_ECHO 5

VarSpeedServo microServo;
HCSR04 ultrasonic(PINO_TRIG, PINO_ECHO, 20, 4000);

long duration;
int distance;
int pos = 0;

void setup() {
  pinMode(PINO_TRIG, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
  Serial.begin(9600);
  microServo.attach(SERVO);
  microServo.write(0);
}
void loop() {
  for (int i = 0; i <= 179; i++) {
    Serial.print("pos: ");
    Serial.println(i);
    
    microServo.write(i);
    delay(10);
    
   // distance = calculateDistance(); // Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
//    Serial.print(pos); // Sends the current degree into the Serial Port
//    Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
//    Serial.print(distance); // Sends the distance value into the Serial Port
//    Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  
  // Repeats the previous lines from 165 to 15 degrees
//  for (int i = 18; i >= 0; i--) {
//    microServo.write(pos);
//    delay(10);
//    
//    //distance = calculateDistance();
////    Serial.print(pos);
////    Serial.print(",");
////    Serial.print(distance);
////    Serial.print(".");
//  }
}

int calculateDistance() {
  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(PINO_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIG, LOW);
  
  duration = pulseIn(PINO_ECHO, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;
  return distance;
}
