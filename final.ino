const int trigPin = 12;
const int echoPin = 13;
const int leftMotorPin = 7;
const int rightMotorPin = 8;
const int irSensorPin = 2;
const int flameSensorPin = 4;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);
  pinMode(irSensorPin, INPUT);
  pinMode(flameSensorPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  long duration;
  float distance;
  int irValue = digitalRead(irSensorPin);
  int flameValue = digitalRead(flameSensorPin);

  // Measure ultrasonic distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Debug prints
  Serial.print("Ultrasonic Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("IR Sensor: ");
  Serial.println(irValue == LOW ? "Object detected" : "Clear");

  Serial.print("Flame Sensor: ");
  Serial.println(flameValue == LOW ? "Flame detected!" : "No flame");

  // Logic for turning when obstacle is detected by ultrasonic sensor
  if (distance < 10) {
    // If obstacle detected, turn
    digitalWrite(leftMotorPin, LOW);   // Stop left motor
    digitalWrite(rightMotorPin, HIGH); // Keep right motor running (turn right)
    Serial.println("Obstacle detected! Turning.");
  } else if (irValue == LOW || flameValue == LOW) {
    // Stop if IR or flame sensor detects obstacle
    digitalWrite(leftMotorPin, LOW);
    digitalWrite(rightMotorPin, LOW);
    Serial.println("Obstacle or Flame detected — Stopping.");
  } else {
    // Otherwise, move forward
    digitalWrite(leftMotorPin, HIGH);
    digitalWrite(rightMotorPin, HIGH);
    Serial.println("All clear. Moving forward.");
  }

  delay(200);
}
