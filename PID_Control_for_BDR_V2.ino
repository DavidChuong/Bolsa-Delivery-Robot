#include <PID_v1.h>

#define LEFT_INPUT 0 //left encoder 
#define RIGHT_INPUT 0 //right encoder 
#define LEFT_OUTPUT_A 6 //left motor A
#define LEFT_OUTPUT_B 8 //left motor B
#define RIGHT_OUTPUT_A 5 //right motor A
#define RIGHT_OUTPUT_B 10 //right motor B

double LeftInput, RightInput, LeftOutput, RightOutput;
double Kp = 0, Ki = 0, Kd = 0;

void setup() {
   LeftInput = analogRead(LEFT_INPUT); //read left encoder
   RightInput = analogRead(RIGHT_INPUT); //read right encoder
}

void loop() {
  //if left is greater than right, we reduce it to the speed of the right
  while (LeftInput > RightInput) {
    PID myPID(&LeftInput, &LeftOutput, &RightInput, Kp, Ki, Kd, DIRECT);
    myPID.SetMode(AUTOMATIC); //intialize PID
    myPID.Compute();
    analogWrite(LEFT_OUTPUT_A, LeftOutput);
    analogWrite(LEFT_OUTPUT_B, LeftOutput);
  }

  //if right is greater than left, we reduce it to the speed of the left
  while (LeftInput < RightInput) {
    PID myPID(&RightInput, &RightOutput, &LeftInput, Kp, Ki, Kd, DIRECT);
    myPID.SetMode(AUTOMATIC); //intialize PID
    myPID.Compute();
    analogWrite(RIGHT_OUTPUT_A, RightOutput);
    analogWrite(RIGHT_OUTPUT_B, RightOutput);
  }
}
