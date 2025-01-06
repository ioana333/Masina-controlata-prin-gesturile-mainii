#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Pinii motoarelor
const int enableRightMotor = 5;
const int rightMotorPin1 = 2;
const int rightMotorPin2 = 3;

const int enableLeftMotor = 6;
const int leftMotorPin1 = 4;
const int leftMotorPin2 = 7;

// Creează obiect RF24 (folosit doar pentru compatibilitate)
RF24 radio(9, 8);  // CE, CSN

void setup() {
  // Configurare pini pentru motoare
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  Serial.begin(9600);
  Serial.println("Testare motoare...");
  
  // Oprește motoarele inițial
  rotateMotor(0, 0);
}

void loop() {
  const int MAX_SPEED = 200;

  // Testare direcții:
  
  // 1. Mers înainte
  Serial.println("Mers înainte...");
  rotateMotor(MAX_SPEED, MAX_SPEED);
  delay(2000);

  // 2. Mers înapoi
  Serial.println("Mers înapoi...");
  rotateMotor(-MAX_SPEED, -MAX_SPEED);
  delay(2000);

  // 3. Rotire la stânga
  Serial.println("Rotire la stânga...");
  rotateMotor(MAX_SPEED, -MAX_SPEED);
  delay(2000);

  // 4. Rotire la dreapta
  Serial.println("Rotire la dreapta...");
  rotateMotor(-MAX_SPEED, MAX_SPEED);
  delay(2000);

  // 5. Stop
  Serial.println("Oprire motoare...");
  rotateMotor(0, 0);
  delay(2000);
}

// Funcție pentru controlul motoarelor
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
  // Controlează motorul din dreapta
  if (rightMotorSpeed < 0) 
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  } else if (rightMotorSpeed > 0) 
  {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  // Controlează motorul din stânga
  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } else if (leftMotorSpeed > 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  } else {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }

  // Setează viteza motorului
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}
