#include <PID_v1.h>

#define LEFT_INPUT 0 //left encoder
#define RIGHT_INPUT 0 //right encoder
#define LEFT_OUTPUT 0 //left motor
#define RIGHT_OUTPUT 0 //right motor

double Setpoint = 0; //condition where the vehicle moves straight
double leftInput, leftOutput, rightInput, rightOutput; //declare input and output
float leftKp = 0.1, leftKi = 0.1, leftKd = 0, rightKp = 0.1, rightKi = 0.1, rightKd = 0; //tuning variables 
PID leftPID(&leftInput, &leftOutput, &Setpoint, leftKp, leftKi, leftKd, DIRECT); //use PID on left motor
PID rightPID(&rightInput, &rightOutput, &Setpoint, rightKp, rightKi, rightKd, DIRECT); //use PID on right motor

void setup() {
  leftInput = analogRead(LEFT_INPUT); //read left encoder
  rightInput = analogRead(RIGHT_INPUT); //read right encoder
  leftPID.SetMode(AUTOMATIC); //left PID on
  rightPID.SetMode(AUTOMATIC); //right PID on
}

void loop() {
  leftInput = analogRead(LEFT_INPUT); //read left encoder repeatedly
  rightInput = analogRead(RIGHT_INPUT); //read right encoder repeatedly
  leftPID.Compute(); //calculate adjustment on left motor
  rightPID.Compute(); //calculate adjustment on right motor
  analogWrite(LEFT_OUTPUT, leftOutput);
  analogWrite(RIGHT_OUTPUT, rightOutput);
}
