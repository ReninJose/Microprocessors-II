//EECE 4520: Lab 2: 3/20-23/22: 
//The code implimented for the python game; By Alex Skinner, Renin Kingsly Jose, and Johnny Nhem
// Specifically using the Gyroscope module; (GY 521 module) reading the analog pins read, then 
//writing the result tothe python code for its own functions.


//This was directly inspired from the examples provided by Prof.Liang-Min Wang. Including 
//The pdf. 'Lession_16_GY-521_Module.pdf': Modified heavily by Alex.Skinner
//For signifigant infortmation on how the analog pins 
//from the GY-521 module were read.

/*Notes During development: 

   *Inspired from the code currently produced by Renin Kingsly Jose and Jhonny Nhem: However since
   this relies on such different inputs, I'll have this be a completely different file (So far)
   
   *A clear difference from the example code is the nessesary variables and operations in order to
   obtain the changes in pitch and roll.(I won't use the yaw, since it shouldn't need to 'rotate')
   I'm adding the absolutely nessesary operations now in order to save space.

   *Currently adding the last code in order to have it write based on the read values: Here
    I had to edit the Alpha/ Omiga values to both operate for the X/Y rotations!

*/
#include <SoftwareSerial.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#define BUZZER 23

// LED status, and the status for the resulting buzzer
int buzzer_status = HIGH;
int incomingByte = 0;

//Then, apply the pre-setup values for the module


MPU6050 Gyro_Read(0x68);
//statement MPU6050 control and state variable
bool Ready = false; //set true if DMP init was successful
uint8_t IntStatus; //This variable is used to save the state when MPU6050 stop

uint8_t Status; //Return to equipment status, 0 for success, others for error
uint16_t PacketSize; // expected DMP packet size (default is 42 bytes)
uint16_t FifoCount; // count of all bytes currently in FIFO

uint8_t FifoBuffer[64]; // FIFO storage buffer
//state direction and movement of variables:
Quaternion Quat; //quaternion variable W,X,Y,Z
VectorFloat Grav_Status; //gravity vector X，Y, Z
float Orientation[3]; // [yaw, pitch, roll] yaw/pitch/roll container and gravity

volatile bool GyroInterrupt = false; // indicates whether MPU interrupt pin has

void dmpDataReady()
{
 GyroInterrupt = true;
}


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); //Open the serial port and set the baud rate to 115200, upload
  Wire.begin();
  Gyro_Read.initialize();
  
  delay(2); //delay 2ms, then begin the dmpInitialize and begin the rest
  Status = Gyro_Read.dmpInitialize(); //Return to DMP status, 0 for success
  
  //If its reading data, begin processing now, and have the loop() begin reading said data
  if (Status == 0){

    Serial.println("Enabling DMP...");    //Enabling the Arduino interrupt detection
    Gyro_Read.setDMPEnabled(true);
    
    Serial.println("Enabling interrupt detection (Arduino external interrupt 0)...");
    attachInterrupt(0, dmpDataReady, RISING);
    IntStatus = Gyro_Read.getIntStatus();
    
    Serial.println("DMP ready! Waiting for first interrupt..."); 
    Ready = true;
    // get expected DMP packet size for later comparison
    PacketSize = Gyro_Read.dmpGetFIFOPacketSize();
  }
   
  // initialize buzer as an output. / Going back to the original buzzer code
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);   // turn the buzzer off
  buzzer_status = HIGH;
  
}

void loop() {
  
  
  //First, The system needs to review any changes,and fully develop the gyroscope code
  
  float X_Ori, Y_Ori; //state two floating-point variables, alpha and omiga
  //if MPU6050 DMP status to error, the program stop working

 if (!Ready)
   //return;

 if (!GyroInterrupt && FifoCount < PacketSize) // wait for MPU interrupt or extra packet(s) available
   return;
   
 GyroInterrupt = false;  // reset interrupt flag and get INT_STATUS byte
 
 IntStatus = Gyro_Read.getIntStatus(); // get current FIFO count
 FifoCount = Gyro_Read.getFIFOCount();

 // check for overflow (this should never happen unless our code is too inefficient)
 if ((IntStatus & 0x10) || FifoCount == 1024){

   Gyro_Read.resetFIFO();  // reset so we can continue cleanly
   Serial.println("FIFO overflow!");
   // otherwise, check for DMP data ready interrupt (this should happen frequently)
   
 }
 else if (IntStatus & 0x02) { // wait for correct available data length, should be a VERY short wait
  

 while (FifoCount < PacketSize) 
   FifoCount = Gyro_Read.getFIFOCount();

  Gyro_Read.getFIFOBytes(FifoBuffer, PacketSize); // read a packet from FIFO
  FifoCount -= PacketSize;
  Gyro_Read.dmpGetQuaternion(&Quat, FifoBuffer);
  Gyro_Read.dmpGetGravity(&Grav_Status, &Quat);
  Gyro_Read.dmpGetYawPitchRoll(Orientation, &Quat, &Grav_Status); //take three axis angle from the
  
  //Then, apply the desired values; and then print it to the python program.
  //Originally, I was going to have simply the x-rotation and y-rotation, however its very unprecise

  Y_Ori = -Orientation[2] * 180/M_PI;
  X_Ori = -Orientation[1] * 180/M_PI;
  
  Serial.print(" 'Y' Orientation: ");
  Serial.print(Y_Ori);
  Serial.print("\n \n");
  Serial.print(" 'X' Orientation: ");
  Serial.print(X_Ori);
  Serial.print("\n \n");
  
  
  if(X_Ori >= 20){
    Serial.write("right\n");
  }
  else if(X_Ori <= -20){
    Serial.write("left\n");
  }
  else if(Y_Ori >= 20){
    Serial.write("up\n");
  }
  else if(Y_Ori <= -20){
    Serial.write("down\n");
  }

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    
    if(incomingByte == '1') {
      buzzer_status = (buzzer_status == HIGH)? LOW : HIGH;
      digitalWrite(BUZZER, HIGH);
      delay(200);
      digitalWrite(BUZZER, LOW);
      delay(200);
    }
  }
  

  delay(100);
 }
}
