// importing libraries
#include <PPMReader.h>
PPMReader ppm(INTERRUPT_PIN, PPM_CHANNELS);

// functions declaration
int calculateSpd(int ch_reading);
void moveForward(int channelReading);
void moveBackward(int channelReading);
void moveLeft(int channelReading);
void moveRight(int channelReading);
void forwardBelt(int channelReading);
void backwardBelt(int channelReading);
void stopBelt();

// put your setup code here, to run once:
void setup() {
  Serial.begin(115200);
  
  pinMode(belt_L_PWM, OUTPUT);
  pinMode(belt_R_PWM, OUTPUT);
  pinMode(belt_EN, OUTPUT);

  pinMode(rightWheel_L_PWM, OUTPUT);
  pinMode(rightWheel_R_PWM, OUTPUT);
  pinMode(rightWheel_EN, OUTPUT);

  pinMode(leftWheel_L_PWM, OUTPUT);
  pinMode(leftWheel_R_PWM, OUTPUT);
  pinMode(leftWheel_EN, OUTPUT);
}


// put your main code here, to run repeatedly:
void loop() {
  //ppm.latestValidChannelValue(channle no, midpt) returns value between [1000,200]
  //midpt acts as the default value when the joystick is not toched at all(?)
  
  int ch2 = ppm.latestValidChannelValue(CHANNEL_2, 1500);
  int ch1 = ppm.latestValidChannelValue(CHANNEL_1, 1500);
  int ch3 = ppm.latestValidChannelValue(CHANNEL_3, 1500);  
  
  //Serial.println("Channel 2 is " + String(ch2) );
  //Serial.println("Channel 1 is " + String(ch1) );
  //Serial.println("Channel 3 is " + String(ch3) );
  //delay(200);
  
  // move the wheels forward when channel 2 is greater than 1492
  if (ch2 > 1501){
    moveForward(ch2);
    }
  // move the wheels backward when channel 2 is lower than 1492
  else if (ch2 < 1480){
    moveBackward(ch2);
    }

  // move the wheels right when channel 1 is greater than 1492
  if (ch1 > 1500){
    moveRight(ch1);
    }
  // move the wheels left when channel 1 is lower than 1492
  else if (ch1 < 1480){
    moveLeft(ch1);
    }

  // move the belt forward when channel 3 is maxed
   if (ch3 > 1501){
    forwardBelt(ch3);
   }
   // move the belt backward when channel 3 is minimum
   else if (ch3 < 1480){
    backwardBelt(ch3);
   }
   // else stop the belt
   else{
    stopBelt();
   }
}

int calculateSpd(int channelReading){
  long spd = channelReading - 1492;
  spd = spd * 255 / 500;
  return spd;
}

void moveForward(int channelReading){
  // change channel values to values between [-255,255] midpoint 0
  long spd = calculateSpd(channelReading);
  digitalWrite(rightWheel_L_PWM, 1);
  digitalWrite(rightWheel_R_PWM, 0);
  analogWrite(rightWheel_EN, abs(spd));
  digitalWrite(leftWheel_L_PWM, 0);
  digitalWrite(leftWheel_R_PWM, 1);
  analogWrite(leftWheel_EN, abs(spd));
}

void moveBackward(int channelReading){
  // change channel values to values between [-255,255] midpoint 0
  long spd = calculateSpd(channelReading);
  digitalWrite(rightWheel_L_PWM, 0);
  digitalWrite(rightWheel_R_PWM, 1);
  analogWrite(rightWheel_EN, abs(spd));
  digitalWrite(leftWheel_L_PWM, 1);
  digitalWrite(leftWheel_R_PWM, 0);
  analogWrite(leftWheel_EN, abs(spd));
}

void moveLeft(int channelReading){
  // change channel values to values between [-255,255] midpoint 0
  long spd = calculateSpd(channelReading);
  digitalWrite(rightWheel_L_PWM, 0);
  digitalWrite(rightWheel_R_PWM, 1);
  analogWrite(rightWheel_EN, abs(spd));
  digitalWrite(leftWheel_L_PWM, 0);
  digitalWrite(leftWheel_R_PWM, 0);
  analogWrite(leftWheel_EN, 0);
}

void moveRight(int channelReading){
  // change channel values to values between [-255,255] midpoint 0
  long spd = calculateSpd(channelReading);
  digitalWrite(rightWheel_L_PWM, 0);
  digitalWrite(rightWheel_R_PWM, 0);
  analogWrite(rightWheel_EN, 0);
  digitalWrite(leftWheel_L_PWM, 1);
  digitalWrite(leftWheel_R_PWM, 0);
  analogWrite(leftWheel_EN, abs(spd));
}

void forwardBelt(int channelReading){
  // change channel values to values between [-255,255] midpoint 0
  long spd = calculateSpd(channelReading);
  digitalWrite(belt_L_PWM, 1);
  digitalWrite(belt_R_PWM, 0);
  analogWrite(belt_EN, abs(spd));
}

void backwardBelt(int channelReading){
  // change channel values to values between [-255,255] midpoint 0
  long spd = calculateSpd(channelReading);
  digitalWrite(belt_L_PWM, 0);
  digitalWrite(belt_R_PWM, 1);
  analogWrite(belt_EN, abs(spd));
}

void stopBelt(){
  digitalWrite(belt_L_PWM, 0);
  digitalWrite(belt_R_PWM, 0);
  analogWrite(belt_EN, 0);
}
