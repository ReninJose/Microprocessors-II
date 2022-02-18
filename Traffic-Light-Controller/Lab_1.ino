// Renin Kingsly Jose
// Lab 1: Traffic Light Controller

#define RED 22
#define YELLOW 24
#define GREEN 26
#define SWITCH 23
#define BUZZER 25

// Const boolean variable to check if button is pressed
// LOW/false = Button Pressed
const bool pressed = false;
bool check = true;           // To check if button is pressed
bool invert = HIGH;         // To invert LED's state

void setup() {
  // Setup LEDs
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  // Setup Switch
  pinMode(SWITCH, INPUT_PULLUP);
  // Setup Active Buzzer
  pinMode(BUZZER, OUTPUT);

  // Turn on RED
  digitalWrite(RED, invert);
  
  // Setup Initial State 1 (RED 1 sec on and 1 sec off)
  while (check != pressed) {
    if (invert == HIGH) {
      digitalWrite(RED, invert);
      invert = LOW;
    }
    else if (invert == LOW) {
      digitalWrite(RED, invert);
      invert = HIGH;
    }
    // 1-sec delay
    delay(1000);
    check = digitalRead(SWITCH);
  }
}

// IMPLEMENT BUZZER FOR ALL STATE (Remove this comment once its done)
void loop() {
  
  // State 1 (RED on for 20 seconds)
  digitalWrite(RED, HIGH);
  delay(20000);
  digitalWrite(RED, LOW);

  // State 2 (GREEN for 20 seconds)
  digitalWrite(GREEN, HIGH);
  delay(20000);
  digitalWrite(GREEN, LOW);

  // State 3 (Yellow stays on for 3 sec)
  digitalWrite(YELLOW, HIGH);
  delay(3000);
  digitalWrite(YELLOW, LOW);    // Remove this line once state 4 is implemented

  // State 4 (Yellow blinks every 200ms)
  for(int i = 0; i < 9; i = i + 1) {    //loops for 3 seconds
    digitalWrite(YELLOW, HIGH);         // turn the LED on (HIGH is the voltage level)
    delay(200);                         // wait for 200ms
    digitalWrite(YELLOW, LOW);          // turn the LED off by making the voltage LOW
    delay(200);                         // wait for 200ms
  }
}
