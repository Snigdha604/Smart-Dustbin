#include <Servo.h>

// Define pins for ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Define distance threshold (in cm)
const int distanceThreshold = 15;

// Define servo motor
Servo dustbinLid;
const int servoPin = 6;

// Time variables
long duration;
int distance;

void setup() {
  // Set pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo to pin
  dustbinLid.attach(servoPin);

  // Initially close the lid
  dustbinLid.write(0); // 0 degrees = closed position

  // Start serial communication (for debugging)
  Serial.begin(9600);
}

void loop() {
  // Send a 10us HIGH pulse to trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time
  duration = pulseIn(echoPin, HIGH);

  // Convert time to distance (cm)
  distance = duration * 0.034 / 2;

  // Print distance (for debugging)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If object is within threshold distance, open lid
  if (distance > 0 && distance < distanceThreshold) {
    dustbinLid.write(90); // Open lid
    delay(3000);          // Keep lid open for 3 seconds
    dustbinLid.write(0);  // Close lid
  }

  delay(500); // Small delay before next measurement
}
