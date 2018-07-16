#include <Servo.h>
#include <hcsr04.h>
#include <SPI.h>

#define SERVO 6 // Porta Digital 6 PWM
#define PINO_TRG 4
#define PINO_ECHO 5

Servo myServo; // Variável Servo
HCSR04 ultrasonic(PINO_TRG, PINO_ECHO, 20, 4000);

long duration;
int distance;

void setup() {
  pinMode(PINO_TRG, OUTPUT); // Sets the trigPin as an Output
  pinMode(PINO_ECHO, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  myServo.attach(6); // Defines on which pin is the servo motor attached
  myServo.write(0);
}
void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for (int i = 1; i <= 180; i++) {
    myServo.write(i);
    delay(15);
    distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
    //
    Serial.print(i); // Sends the current degree into the Serial Port
    Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    Serial.print(distance); // Sends the distance value into the Serial Port
    Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  // Repeats the previous lines from 165 to 15 degrees
  for (int i = 180; i >= 1; i--) {
    myServo.write(i);
    delay(15);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance() {
  digitalWrite(PINO_TRG, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(PINO_TRG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRG, LOW);
  duration = pulseIn(PINO_ECHO, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;
  return distance;
}
