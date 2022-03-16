#include <SoftwareSerial.h>

#define x_axis 1
#define y_axis 0 

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(x_axis));
  Serial.println("\n");
  Serial.println(analogRead(y_axis));
  delay(200);
}
