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

// Creează obiect RF24
RF24 radio(9, 8);  // CE, CSN

// Adresa prin care modulele comunică
const byte address[6] = "00001";

struct PacketData {
  byte xAxisValue;
  byte yAxisValue;
} receivedData;

void setup() {
  // Configurare pini pentru motoare
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  rotateMotor(0, 0); // Oprește motoarele inițial

  // Configurare RF24
  Serial.begin(9600);
  while (!Serial);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  // Verifică dacă există date disponibile
  if (radio.available()) {
    // Citește datele primite
    radio.read(&receivedData, sizeof(PacketData));

    // Afișează datele primite
    Serial.print("xAxisValue: "); Serial.print(receivedData.xAxisValue);
    Serial.print(" | yAxisValue: "); Serial.println(receivedData.yAxisValue);

    // Controlează motoarele pe baza datelor primite
    controlMotors(receivedData.xAxisValue, receivedData.yAxisValue);
  }
}

void controlMotors(byte xAxis, byte yAxis) {
  const int MAX_MOTOR_SPEED = 200; // Viteza maximă a motorului

  // Motorul se mișcă înainte
  if (yAxis > 150) {
    rotateMotor(MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
  }
  // Motorul se mișcă înapoi
  else if (yAxis < 100) {
    rotateMotor(-MAX_MOTOR_SPEED, -MAX_MOTOR_SPEED);
  }
  // Rotire la stânga
  else if (xAxis < 100) {
    rotateMotor(MAX_MOTOR_SPEED, -MAX_MOTOR_SPEED);
  }
  // Rotire la dreapta
  else if (xAxis > 150) {
    rotateMotor(-MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
  }
  // Stop
  else {
    rotateMotor(0, 0);
  }
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
  // Controlează motorul din dreapta
  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);    
  } else if (rightMotorSpeed > 0) {
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
