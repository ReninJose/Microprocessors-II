const int ENABLE = 5; //enable on pin 5
const int DIRA = 3; //clock-wise spin on pin 3
const int DIRB = 4; //counterclock-wise spin on pin 4
const int buttonApin = 9; //button A
const int buttonBpin = 8; //button B

void setup() 
{
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);  
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  if (digitalRead(buttonApin) == LOW) //if button A is pressed, fan turn clock-wise
  {
    digitalWrite(ENABLE,HIGH); //turn enable ON
    digitalWrite(DIRA,HIGH); //make fan spin clock-wise
    digitalWrite(DIRB,LOW); //turn counterclock-wise OFF
    analogWrite(ENABLE,180); //turn enable OFF
  }
  if (digitalRead(buttonBpin) == LOW) //if buton B is pressed, fan turn counterclock-wise
  {
    digitalWrite(ENABLE,HIGH); //turn enable ON
    digitalWrite(DIRA,LOW); //turn clock-wise OFF
    digitalWrite(DIRB,HIGH); //make fan spin counterclock-wise
    analogWrite(ENABLE,180); //turn enable OFF
  }

}
