#include <I2Cdev.h>
#include <MPU6050.h>
#include <Servo.h>

//  Define pins for servos
#define BROT_SERVO 5  //  base_rotation servo
#define BLIFT_SERVO 6 //  base_lift servo
#define MLIFT_SERVO 9 //  middle_lift servo
#define GRIP_SERVO 10 //  grip servo

Servo base_rotation, base_lift, middle_lift, grip;  //  Create 4 servos for each joint
MPU6050 accelerometer;   // Create accelerometer and gyroscope sensor


float acceleration_x, acceleration_y, acceleration_z;   //  Variables to store x,y,z accelerations from sensor
float brot_deg, blift_deg, mlift_def; //  Variables to define position of servos
bool is_grip;  //  Variable to activate grip


void setup() {
  Serial.begin(9600);   //  Start serial monitor and plotter to examine necessary information
  accelerometer.initialize();   //  Start accelerometer

  base_rotation.attach(BROT_SERVO);
  base_lift.attach(BLIFT_SERVO);
  middle_lift.attach(MLIFT_SERVO);  //  Start servos
  grip.attach(GRIP_SERVO);

  Serial.println(accelerometer.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");   //  Test connection with accelerometer

}

void loop() {
  // put your main code here, to run repeatedly:

}
