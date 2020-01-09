void setinputs(){
pinMode(PWMA, OUTPUT);
pinMode(PWMB, OUTPUT);
pinMode(PWMC, OUTPUT);

pinMode(IN1A, OUTPUT);
pinMode(IN2A, OUTPUT);
pinMode(IN1B, OUTPUT);
pinMode(IN2B, OUTPUT);
pinMode(IN1C, OUTPUT);
pinMode(IN2C, OUTPUT);
}

void setoutputs(void){
pinMode(CSA, INPUT);
pinMode(CSB, INPUT);
pinMode(CSC, INPUT);

pinMode(DIAGA, INPUT);
pinMode(DIAGB, INPUT);
pinMode(DIAGC, INPUT);
}

void serialout(){
  Serial.print(data.eulerX);
  Serial.print(" ");
  Serial.print(data.eulerY);
  Serial.print(" ");
  Serial.print(data.eulerZ);
  Serial.print(" ");

  Serial.print(data.gyroX);
  Serial.print(" ");
  Serial.print(data.gyroY);
  Serial.print(" ");
  Serial.print(data.gyroZ);
  Serial.print(" ");

  Serial.print(data.magX1);
  Serial.print(" ");
  Serial.print(data.magY1);
  Serial.print(" ");
  Serial.print(data.magZ1);
  Serial.print(" ");
  
  Serial.print(data.magX2);
  Serial.print(" ");
  Serial.print(data.magY2);
  Serial.print(" ");
  Serial.print(data.magZ2);
  Serial.println(" ");
}
