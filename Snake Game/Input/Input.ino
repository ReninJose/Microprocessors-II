#include <SoftwareSerial.h>

#define x_axis 1
#define y_axis 0 
#define BUZZER 23

// LED status
int buzzer_status = HIGH;
int incomingByte = 0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize buzer as an output.
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);   // turn the buzzer off
  buzzer_status = HIGH;
}

void loop() {

  if(analogRead(x_axis) == 0){
    Serial.write("left\n");
  }
  else if(analogRead(x_axis) == 1023){
    Serial.write("right\n");
  }
  else if(analogRead(y_axis) == 0){
    Serial.write("up\n");
  }
  else if(analogRead(y_axis) == 1023){
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
