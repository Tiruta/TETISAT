//I2C BNO055 & HMC5883 Library
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <QMC5883L.h>
#include <utility/imumaths.h>

//NRF24L01 Liibrary
#include <SPI.h>
#include "NRFLite.h"

//PID Computing Library
#include <PID_v1.h>
int Zrate = 0;
int target = 0;
float Kp = 1;
int error, correction;
int arah = 0;


//Magnetorquer Drivers
#define PWMA 4
#define PWMB 5
#define PWMC 6

#define IN1A 3
#define IN2A 2
#define IN1B 8
#define IN2B 7
#define IN1C 15
#define IN2C 9

#define CSA 16
#define CSB 17
#define CSC 20

#define DIAGA A10
#define DIAGB A11
#define DIAGC A14

//Reaction Wheel Drivers
#define RWA 23
#define RWB 22
#define RWC 21

//ESC Control Declaration
#include <PWMServo.h>
PWMServo RWa, RWb, RWc, mtqA, mtqB, mtqC;

//BNO055 and Related variables Declaration
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

//GY-271 HMC5883L Compass Declaration
QMC5883L compass;

//NRF24L01 Declaration
const static uint8_t RADIO_ID = 1;             // Our radio's id.
const static uint8_t DESTINATION_RADIO_ID = 0; // Id of the radio we will transmit to.
const static uint8_t PIN_RADIO_CE = 14;
const static uint8_t PIN_RADIO_CSN = 10;

struct RadioPacket{ // Any packet up to 32 bytes can be sent.
    uint8_t FromRadioId, retries;
    int8_t mtqA, mtqB, mtqC, RW, obj;  //actuator status and MCu's next objective
    int16_t eulerX, eulerY, eulerZ;          //absolute value, post fusion
    int16_t magX1, magY1, magZ1;       //BNO055 Raw Mag Values
    int16_t magX2, magY2, magZ2;       //HMC5883 Raw Values
    int16_t gyroX, gyroY, gyroZ;       //BNO055 Raw Gyro Values
};

NRFLite _radio;
RadioPacket data;

void setup() {
  Serial.begin(115200);

  //radio start & config
  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
   {
       Serial.println("Cannot communicate with radio");
       int LED = 13;
       pinMode(LED, OUTPUT);
       while (1){
        digitalWrite(LED, HIGH);
        delay(100);
        digitalWrite(LED, LOW);
        delay(100); // Wait here forever if nRF connection failed.
       }
   }
   data.FromRadioId = RADIO_ID;
  
  //IMU & Mag Start
  Wire.begin();
  bno.begin();
  compass.init();
  compass.setSamplingRate(100);

  //Setting prerequisite pins
  setinputs();
  setoutputs();

  //attaching PWM controls
  RWa.attach(RWA); //Reaction Wheel PWM pin
  RWb.attach(RWB); //Reaction Wheel PWM pin
  RWc.attach(RWC); //Reaction Wheel PWM pin
  mtqA.attach(PWMA); //Magnetorquer A
  mtqB.attach(PWMB); //Magnetorquer B
  mtqC.attach(PWMC); //Magnetorquer C

  RWc.write(90);

  uint8_t system, gyro, accel, mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
  while (gyro < 2){
  bno.getCalibration(&system, &gyro, &accel, &mag);
  }
  
  pinMode(13, OUTPUT);
  for(int j=0; j<6; j++){
    RWc.write(90);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  checkGyro();
  Zrate = data.gyroZ / 2;
  error = Zrate - target;
  correction = Kp * error;
  Serial.println(Zrate);

  if (correction < 0){
    arah = 0;
  }
  else if (correction > 0){
    arah = 1;
  }
  
  driveRW(3, arah, abs(correction));

}
