#include <AFMotor.h>

#define SENSOR_PIN 2
#define RELAY_PIN 4

#define SPRINKLER_START_DELAY 1500  // 1.5 second
#define SPRINKLER_ON_TIME 1000      // 1 second

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

int val;
int Speeed = 255;
unsigned long previousTime = millis();

void setup() {
  Serial.begin(9600);  // Bluetooth baud rate
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  digitalWrite(RELAY_PIN, HIGH); // Keep sprinkler OFF initially
}

void loop() {
  // -------- FIRE DETECTION AND SPRINKLER ----------
  int sensorValue = digitalRead(SENSOR_PIN);

  if (sensorValue == LOW) { // Fire detected
    Serial.println("Fire detected!");

    if (millis() - previousTime > SPRINKLER_START_DELAY) {
      Serial.println("Sprinkler ON");
      digitalWrite(RELAY_PIN, LOW); // LOW = ON for relay
      delay(SPRINKLER_ON_TIME);
    }
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Turn OFF sprinkler
    previousTime = millis();
  }

  // -------- BLUETOOTH MOTOR CONTROL ----------
  if (Serial.available() > 0) {
    val = Serial.read();
    Serial.print("Received: ");
    Serial.println((char)val);
    Stop();

    switch (val) {
      case 'F': forward(); break;
      case 'B': back(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case 'I': topright(); break;
      case 'J': topleft(); break;
      case 'K': bottomright(); break;
      case 'M': bottomleft(); break;
      case 'T': Stop(); break;
    }
  }
}

// -------- MOTOR CONTROL FUNCTIONS --------------

void forward() {
  motor1.setSpeed(Speeed); motor1.run(FORWARD);
  motor2.setSpeed(Speeed); motor2.run(FORWARD);
  motor3.setSpeed(Speeed); motor3.run(FORWARD);
  motor4.setSpeed(Speeed); motor4.run(FORWARD);
}

void back() {
  motor1.setSpeed(Speeed); motor1.run(BACKWARD);
  motor2.setSpeed(Speeed); motor2.run(BACKWARD);
  motor3.setSpeed(Speeed); motor3.run(BACKWARD);
  motor4.setSpeed(Speeed); motor4.run(BACKWARD);
}

void left() {
  motor1.setSpeed(Speeed); motor1.run(BACKWARD);
  motor2.setSpeed(Speeed); motor2.run(BACKWARD);
  motor3.setSpeed(Speeed); motor3.run(FORWARD);
  motor4.setSpeed(Speeed); motor4.run(FORWARD);
}

void right() {
  motor1.setSpeed(Speeed); motor1.run(FORWARD);
  motor2.setSpeed(Speeed); motor2.run(FORWARD);
  motor3.setSpeed(Speeed); motor3.run(BACKWARD);
  motor4.setSpeed(Speeed); motor4.run(BACKWARD);
}

void topleft() {
  motor1.setSpeed(Speeed); motor1.run(FORWARD);
  motor2.setSpeed(Speeed); motor2.run(FORWARD);
  motor3.setSpeed(Speeed / 3.1); motor3.run(FORWARD);
  motor4.setSpeed(Speeed / 3.1); motor4.run(FORWARD);
}

void topright() {
  motor1.setSpeed(Speeed / 3.1); motor1.run(FORWARD);
  motor2.setSpeed(Speeed / 3.1); motor2.run(FORWARD);
  motor3.setSpeed(Speeed); motor3.run(FORWARD);
  motor4.setSpeed(Speeed); motor4.run(FORWARD);
}

void bottomleft() {
  motor1.setSpeed(Speeed); motor1.run(BACKWARD);
  motor2.setSpeed(Speeed); motor2.run(BACKWARD);
  motor3.setSpeed(Speeed / 3.1); motor3.run(BACKWARD);
  motor4.setSpeed(Speeed / 3.1); motor4.run(BACKWARD);
}

void bottomright() {
  motor1.setSpeed(Speeed / 3.1); motor1.run(BACKWARD);
  motor2.setSpeed(Speeed / 3.1); motor2.run(BACKWARD);
  motor3.setSpeed(Speeed); motor3.run(BACKWARD);
  motor4.setSpeed(Speeed); motor4.run(BACKWARD);
}

void Stop() {
  motor1.setSpeed(0); motor1.run(RELEASE);
  motor2.setSpeed(0); motor2.run(RELEASE);
  motor3.setSpeed(0); motor3.run(RELEASE);
  motor4.setSpeed(0); motor4.run(RELEASE);
}
