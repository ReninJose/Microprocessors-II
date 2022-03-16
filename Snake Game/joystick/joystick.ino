#include <SoftwareSerial.h>

#define x_axis 1
#define y_axis 0 

void setup() {
  Serial.begin(9600);
}

void loop() {

  if(analogRead(x_axis) == 0){
    Serial.write("left");
  }
  else if(analogRead(x_axis) == 1023){
    Serial.write("right");
  }
  else if(analogRead(y_axis) == 0){
    Serial.write("up");
  }
  else if(analogRead(y_axis) == 1023){
    Serial.write("down");
  }

  delay(200);
}
