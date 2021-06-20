#include <Servo.h>

// defines constants
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define powerPin 4 //attach ping D4 Arduino to pin VCC of HC-SR04
#define servoPin 5 //signal wire for servo
#define keyPin 6 //key on charge discharge module
#define range 8 // cm
#define downAngle 180 //degrees
#define upAngle 0 //degrees

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

Servo servo;

unsigned long lastTimeDown; 
bool isUp = true;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(powerPin, OUTPUT);
  pinMode(keyPin, OUTPUT);
  digitalWrite(powerPin, HIGH); 
  digitalWrite(keyPin, LOW); // if this doesn't work, try triggering it
  servo.attach(servoPin);

  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  /*
  digitalWrite(keyPin, HIGH);
  delayMicroseconds(2);
  digitalWrie(keyPin, LOW);
  delayMicroseconds(10);
  digitalWrite(keyPin, HIGH)
  */
  //sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");
  Serial.print(" Status: " + String(isUp));
  

  if (distance < range) {
    lastTimeDown = millis();
    Serial.print(", Writing: ");
    servo.write(downAngle);
    Serial.println(downAngle);
    isUp = false;
  }
  if (millis() - lastTimeDown > 1000) {

    Serial.print(", Writing: ");
    servo.write(upAngle);
    Serial.println(upAngle);
    isUp = true;
  }
}