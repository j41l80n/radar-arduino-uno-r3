#include <Servo.h>
#include <hcsr04.h>
#include <SPI.h>

#define SERVO 6 // Porta Digital 6 PWM
#define PINO_TRIG 4
#define PINO_ECHO 5

Servo microServo;
HCSR04 ultrasonic(PINO_TRIG, PINO_ECHO, 20, 4000);

long duration;
int distance;

void setup() {
  pinMode(PINO_TRIG, OUTPUT); // Sets the trigPin as an Output
  pinMode(PINO_ECHO, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  microServo.attach(6);
  microServo.write(0);
}
void loop() {
  for (int i = 1; i <= 180; i++) {
    microServo.write(i);
    delay(15);
    distance = calculateDistance(); // Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
    Serial.print(i); // Sends the current degree into the Serial Port
    Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    Serial.print(distance); // Sends the distance value into the Serial Port
    Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  // Repeats the previous lines from 165 to 15 degrees
  for (int i = 180; i >= 1; i--) {
    microServo.write(i);
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
  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(PINO_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIG, LOW);
  duration = pulseIn(PINO_ECHO, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;
  return distance;
}
