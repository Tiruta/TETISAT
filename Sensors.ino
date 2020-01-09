void checkmag(){
  int16_t x, y, z, t;
  compass.readRaw(&x, &y, &z, &t);
  data.magX2=x;
  data.magY2=y;
  data.magZ2=z;
}

void checkBNO(){
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  data.eulerX = euler.x();
  data.eulerY = euler.y();
  data.eulerZ = euler.z();

  imu::Vector<3> magnetic = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

  data.magX1 = magnetic.x();
  data.magY1 = magnetic.y();
  data.magZ1 = magnetic.z();

  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

  data.gyroX = gyro.x();
  data.gyroY = gyro.y();
  data.gyroZ = gyro.z();
}

void checkGyro(){
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

  data.gyroX = gyro.x();
  data.gyroY = gyro.y();
  data.gyroZ = gyro.z();
}
