#include <SPI.h>
#include <Servo.h>
#include <hcsr04.h>

#define SERVO 6
#define PINO_TRIG 4
#define PINO_ECHO 5

Servo microServo;
HCSR04 ultrasonic(PINO_TRIG, PINO_ECHO, 20, 4000);

long duration;
int distance;
int pos = 0;

void setup() {
  pinMode(PINO_TRIG, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
  Serial.begin(9600);
  microServo.attach(6);
  microServo.write(0);
}
void loop() {
  for (pos = microServo.read(); pos <= 180; pos += 1) {
    Serial.print("pos: ");
    Serial.println(pos);
    
    microServo.write(pos);
    delay(10);
    
   // distance = calculateDistance(); // Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
//    Serial.print(pos); // Sends the current degree into the Serial Port
//    Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
//    Serial.print(distance); // Sends the distance value into the Serial Port
//    Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  
  // Repeats the previous lines from 165 to 15 degrees
//  for (pos = microServo.read(); pos >= 0; pos -= 1) {
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
