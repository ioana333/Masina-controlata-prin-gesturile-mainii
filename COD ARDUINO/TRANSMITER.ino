#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 mpu;
bool dmpReady = false;
uint8_t devStatus;
uint16_t packetSize;
uint8_t fifoBuffer[64];
Quaternion q;
VectorFloat gravity;
float ypr[3];

// const uint64_t pipeOut = 0xF9E8F0F0E1LL;

RF24 radio(9, 8);

const byte address[6] = "00001";

struct PacketData 
{
  byte xAxisValue;
  byte yAxisValue;
} data;

void setupRadioTransmitter()
{
  // radio.begin();
  // radio.setDataRate(RF24_250KBPS);
  // radio.openWritingPipe(pipeOut);
  // radio.stopListening();
  
  radio.begin();//set the address
  radio.openWritingPipe(address);//Set module as transmitter
  radio.stopListening(); 

  data.xAxisValue = 127;
  data.yAxisValue = 127;
}

void setupMPU()
{
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
      Wire.setClock(400000);
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
  
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  devStatus = mpu.dmpInitialize();
  if (devStatus == 0) 
  {
      mpu.CalibrateAccel(6);
      mpu.CalibrateGyro(6);
      mpu.setDMPEnabled(true);

      Serial.println(F("DMP ready!"));
      dmpReady = true;
      packetSize = mpu.dmpGetFIFOPacketSize();
  } 
  else 
  {
      Serial.print(F("DMP Initialization failed (code "));
      Serial.print(devStatus);
      Serial.println(F(")"));
  }
}

void setup()
{
  Serial.begin(115200); // Inițializează comunicația Serial Monitor
  setupRadioTransmitter();
  setupMPU();
}

void loop() 
{
  if (!dmpReady) return;

  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) 
  {  
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    int xAxisValue = constrain(ypr[2] * 180/M_PI, -90, 90);
    int yAxisValue = constrain(ypr[1] * 180/M_PI, -90, 90);
    data.xAxisValue = map(xAxisValue, -90, 90, 0, 254); 
    data.yAxisValue = map(yAxisValue, -90, 90, 254, 0);

    radio.write(&data, sizeof(PacketData));

    // Afișează valorile pe Serial Monitor
    Serial.print("Yaw: "); Serial.print(ypr[0] * 180/M_PI);
    Serial.print(" | Pitch: "); Serial.print(ypr[1] * 180/M_PI);
    Serial.print(" | Roll: "); Serial.println(ypr[2] * 180/M_PI);

    Serial.print("xAxisValue: "); Serial.print(data.xAxisValue);
    Serial.print(" | yAxisValue: "); Serial.println(data.yAxisValue);
  }
}
