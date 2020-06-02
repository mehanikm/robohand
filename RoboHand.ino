#include <I2Cdev.h>
#include <MPU6050.h>
#include <Servo.h>
#include <ServoEasing.h>

//  Define pins for servos
#define BROT_SERVO  10  //  base_rotation servo
#define BLIFT_SERVO 9   //  base_lift servo
#define MLIFT_SERVO 6   //  middle_lift servo
#define GRIP_SERVO  5   //  grip servo

//EASE_LINEAR       //
//EASE_QUADRATIC    //
//EASE_CUBIC        //
//EASE_QUARTIC      //
//EASE_SINE         //  Movement smoothness types (+ _IN + _OUT)
//EASE_CIRCULAR     //
//EASE_BACK         //
//EASE_ELASTIC      //
//EASE_BOUNCE       //
//EASE_USER         //

ServoEasing base_rotation, base_lift, middle_lift, grip;  //  Create 4 servos for each joint
MPU6050 accelerometer;   // Create accelerometer and gyroscope sensor


float acceleration_x, acceleration_y, acceleration_z;   //  Variables to store x,y,z accelerations from sensor
float brot_deg, blift_deg, mlift_deg; //  Variables to define position of servos
bool is_grip;  //  Variable to activate grip
bool connection;  //  Is accelerometer connected?

float max_from_acc = 16000;   // Maximum value we can get from accelerometer to constrain to it


void setup() {
  Serial.begin(9600);   //  Start serial monitor and plotter to examine necessary information
  Serial.println("Starting sketch............");

  accelerometer.initialize();   //  Start accelerometer

  base_rotation.attach(BROT_SERVO); //  Start servos
  base_lift.attach(BLIFT_SERVO);    //  Start servos
  middle_lift.attach(MLIFT_SERVO);  //  Start servos
  grip.attach(GRIP_SERVO);          //  Start servos

  base_rotation.write(0);                       ////
  base_rotation.setEasingType(EASE_LINEAR);     //
  base_lift.write(0);                           //  Setup initial position and apply smoothing to servos' movement
  base_lift.setEasingType(EASE_LINEAR);         //
  middle_lift.write(0);                         //
  middle_lift.setEasingType(EASE_LINEAR);       ////

  Serial.println("Testing connection............");
  do {
    connection = accelerometer.testConnection();  //  Test connection with accelerometer
    Serial.println("Conncetion failed");
  } while (!connection);
  Serial.println("Conncetion successful");

}



void loop() {
  acceleration_x = accelerometer.getAccelerationX();  //Read X from accelerometer
  acceleration_y = accelerometer.getAccelerationY();  //Read Y from accelerometer
  mlift_deg = analogRead(0);                          //Read value from petentiometer

  Serial.println("X: " + String(acceleration_x) + "\tY: " + String(acceleration_y));


  brot_deg = constrain(acceleration_y, -max_from_acc, max_from_acc);    //  Constrain values from accelerometer and convert them to degrees
  brot_deg = map(brot_deg, -max_from_acc, max_from_acc, 0, 180);        ////  -Base rotation

  blift_deg = constrain(acceleration_x, -max_from_acc, max_from_acc);
  blift_deg = map(blift_deg, -max_from_acc, max_from_acc, 0, 180);      ////  -Base lift

  mlift_deg = map(mlift_deg, 0, 1023, 0, 180);                          ////  -Middle lift


  Serial.println("X: " + String(blift_deg) + "\tY: " + String(brot_deg));

  base_rotation.startEaseTo(brot_deg, 270);       ////
  base_lift.startEaseTo(180 - blift_deg, 270);    //  Write degrees to servos
  middle_lift.startEaseTo(mlift_deg, 270);        ////


  Serial.println(accelerometer.testConnection());
  delay(20);
}
