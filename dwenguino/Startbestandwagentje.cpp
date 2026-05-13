#include <LiquidCrystal.h>
#include <Wire.h>
#include <Dwenguino.h>
#include <DwenguinoMotor.h> // the motor library

DCMotor dcMotor1(MOTOR_1_0, MOTOR_1_1);
DCMotor dcMotor2(MOTOR_2_0, MOTOR_2_1);

void setup() {
  // put your setup code here, to run once:
initDwenguino();
}

void loop() {
  // put your main code here, to run repeatedly:
    dcMotor1.setSpeed(250);
    dcMotor2.setSpeed(250);
    delay(500);
    digitalWrite(13,1); //LED13 - zie tabel eerste tutorial dwenguino
    digitalWrite(LED7,1); //LED7 
    dcMotor1.setSpeed(-250);
    dcMotor2.setSpeed(250);
    delay(500);
}

