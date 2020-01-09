void drivecoil(int coilnumber, int dir, int pwr){

  int pwmspeed;

  pwmspeed = map(pwr, 0, 100, 0, 120); //0-100 is mapped to 0-120 to limit coil voltage, max is 255 but might burn the cable
  
  switch (coilnumber){
    case 1:
        if(dir == 0){
          digitalWrite(IN1A, 1);
          digitalWrite(IN2A, 0);
        }
        else if(dir == 1){
          digitalWrite(IN1A, 0);
          digitalWrite(IN2A, 1);
        }
      break;
    case 2:
        if(dir == 0){
          digitalWrite(IN1B, 1);
          digitalWrite(IN2B, 0);
        }
        else if(dir == 1){
          digitalWrite(IN1B, 0);
          digitalWrite(IN2B, 1);
        }
      break;
    case 3:
        if(dir == 0){
          digitalWrite(IN1C, 1);
          digitalWrite(IN2C, 0);
        }
        else if(dir == 1){
          digitalWrite(IN1C, 0);
          digitalWrite(IN2C, 1);
        }
      break;
  }

  switch (coilnumber){
    case 1:
      mtqA.write(pwmspeed);
      break;
    case 2:
      mtqB.write(pwmspeed);
      break;
    case 3:
      mtqC.write(pwmspeed);
      break;
  }
}


void driveRW(int RWnumber, int dir, int pwr){

  if(pwr > 100){
    pwr = 100;
  }

  if(dir == 0){
    pwr = map(pwr, 0, 100, 90, 180);
  }
  else if(dir == 1){
    pwr = map(pwr, 0, 100, 90, 0);
  }

  switch (RWnumber){
    case 1:
      RWa.write(pwr);
      break;
    case 2:
      RWb.write(pwr);
      break;
    case 3:
      RWc.write(pwr);
      break;
  }

}
