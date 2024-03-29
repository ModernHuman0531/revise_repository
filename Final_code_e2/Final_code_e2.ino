// state = 0: auto
// state = 1: manual
#include<string.h>
#include <SoftwareSerial.h>
#include <Wire.h>
int state = 0;
int Left_motor1=9,Left_motor2=8,Left_pwm=3,Right_motor1=10,Right_motor2=12,Right_pwm=11;
int IR_left=5,IR_mid=6,IR_right=7;
int Time1=300,Time2=100;
char moterstatus;
SoftwareSerial BT(4,13);
class Sensor
{
  public:
    Sensor(int IR_left,int IR_mid,int IR_right);
    int sensor_value();
  private:
    int _IR_left,_IR_mid,_IR_right;
}
Sensor::Sensor
{
  pinMode(IR_left,INPUT);
  pinMode(IR_mid,INPUT);
  pinMode(IR_right,INPUT);
  _IR_left=IR_left;
  _IR_mid=IR_mid;
  _IR_right=IR_right;
}
int Sensor::sensor_value()
{
  if(digitalRead(IR_mid)==LOW&&digitalRead(IR_right)==HIGH&&digitalRead(IR_left)==LOW)
  {
    Serial.println("Forward");
    return 1;
  }
  else if(IR_left_value==HIGH&&IR_right_value==HIGH&&IR_mid_value==HIGH)
  {
    Serial.println("TurnLeft_quickly");
    return 2;
  }
  else if(IR_right_value==LOW&&IR_mid_value==HIGH&&IR_left_value==LOW)
  {
    Serial.println("TurnRight_quickly");
    return 3;
  }
  else if(IR_mid_value==HIGH&&IR_right_value==HIGH&&IR_left_value==LOW)
  {
    Serial.println("Backward");
    return 4;
  }
  else if(IR_right_value==LOW&&IR_mid_value==LOW&&IR_left_value==HIGH)
  {
    Serial.println("Stop");
    return 5;
  }
  else if(IR_right_value==LOW&&IR_mid_value==LOW&&IR_left_value==LOW)
  {
    Serial.println("TurnRight_slowly");
    return 6;
  }
  else if(IR_left_value==HIGH&&IR_right_value==HIGH&&IR_mid_value==LOW)
  {
    Serial.println("TurnLeft_slowly");
    return 7;
  }
  else 
  {
    Serial.println("else");
    return 8;
    move(0);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Left_motor1,OUTPUT);
  pinMode(Left_motor2,OUTPUT);
  pinMode(Right_motor1,OUTPUT);
  pinMode(Right_motor2,OUTPUT);
  pinMode(Left_pwm,OUTPUT);
  pinMode(Right_pwm,OUTPUT);
  Serial.begin(9600);
  BT.begin(9600); // 設定和 HC-06 通訊的速度 (預設 9600) 
}
void loop() {
  if(state == 0) // auto
  {
    // auto code here
  switch(sensor_value)
  {
    case 1:
      move(2);
      move(0);
      break;
    case 2:
      move(3);
      move(0);
      break;
    case 3:
      move(4);
      move(0);
      break;
    case 4:
      move(6);
      move(0);
      move(5);
      move(0);
      break;
    move 5:
      move(0);
      state = 1;
      break;
    move 6:
      move(5);
      move(0);
      break;
    move 7:
      move(6);
      move(0);
      break;
    move 8:
      move(0);
      break;
  }
  else if(state == 1) // manual
  {
      // manual code here
    if (BT.available())
    {
      moterstatus=BT.read();
      Serial.println(moterstatus); 
    }
    switch (moterstatus)
    { 
      case 'F':
        Serial.println("Forward");
        move(2);
        break;
      case 'B':
        Serial.println("Backward");
        move(1);
        break;
      case 'L':
        Serial.println("TurnLeft");
        move(4);
        break;
      case 'R':
        Serial.println("TurnRight");
        move(3);
        break;
      case 'S':
        Serial.println("Stop");
        move(0);
        break;
      case '0':
        Serial.println("Stop");
        move(0);
        break;
    }
  }
}
void move(int dir)
{
  if(dir==1)
  {
    digitalWrite(Left_motor1,HIGH);
    digitalWrite(Left_motor2,LOW);
    digitalWrite(Right_motor1,LOW);
    digitalWrite(Right_motor2,HIGH);
    analogWrite(Left_pwm,150);
    analogWrite(Right_pwm,150);
    delay(Time2);
  }
  else if(dir==0)
  {
    digitalWrite(Left_motor1,LOW);
    digitalWrite(Left_motor2,LOW);
    digitalWrite(Right_motor1,LOW);
    digitalWrite(Right_motor2,LOW);
    analogWrite(Left_pwm,150);
    analogWrite(Right_pwm,150);
    delay(Time1);
  }
  else if(dir==2)
  {
    digitalWrite(Left_motor1,LOW);
    digitalWrite(Left_motor2,HIGH);
    digitalWrite(Right_motor1,HIGH);
    digitalWrite(Right_motor2,LOW);
    analogWrite(Left_pwm,150);
    analogWrite(Right_pwm,150);
    delay(Time2);
  }
  else if(dir==3)
  {
    digitalWrite(Left_motor1,HIGH);
    digitalWrite(Left_motor2,LOW);
    digitalWrite(Right_motor1,HIGH);
    digitalWrite(Right_motor2,LOW);
    analogWrite(Left_pwm,0);
    analogWrite(Right_pwm,200);
    delay(Time2);
  }
  else if(dir==4)
  {
    digitalWrite(Left_motor1,LOW);
    digitalWrite(Left_motor2,HIGH);
    digitalWrite(Right_motor1,LOW);
    digitalWrite(Right_motor2,HIGH);
    analogWrite(Left_pwm,200);
    analogWrite(Right_pwm,0);
    delay(Time2);
  }
  else if(dir==5)
  {
    digitalWrite(Left_motor1,LOW);
    digitalWrite(Left_motor2,HIGH);
    digitalWrite(Right_motor1,LOW);
    digitalWrite(Right_motor2,HIGH);
    analogWrite(Left_pwm,85);
    analogWrite(Right_pwm,0);
    delay(Time2);
  }
  else if(dir==6)
  {
    digitalWrite(Left_motor1,HIGH);
    digitalWrite(Left_motor2,LOW);
    digitalWrite(Right_motor1,HIGH);
    digitalWrite(Right_motor2,LOW);
    analogWrite(Left_pwm,0);
    analogWrite(Right_pwm,85);
    delay(Time2);
  }
}