#define BUZZER 23
// LED status
int buzzer_status = HIGH;
int incomingByte = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize buzer as an output.
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);   // turn the buzzer off
  buzzer_status = HIGH;
}

void loop() {
  // read from the Serial port:
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
}
