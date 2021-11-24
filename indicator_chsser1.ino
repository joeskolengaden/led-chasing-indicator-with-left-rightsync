
#include <Wire.h>  // I2C lib

#define SLAVE_ADDR 9  // I2C address of slave

const int ldelay = 20 ; //delay between each led (smaller value = faster design)
const int l = A0;     // the number of the left signal input pin
const int p = A1;     // the number of the parl signal input pin
const int lrelay = A2;
const int prelay = A3;

// variables will change:
int lState = 0;         // variable for reading the pushbutton status
int pState = 0;         // variable for reading the pushbutton status

void setup() {
  //Serial.begin(9600);
  Wire.begin();   // start I2C connection as master & communication

  // initialize the LED pin as an output:
  for (int led = 0; led < 14; led++) {
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
  }

  // initialize the pushbutton pin as an input:
  pinMode(l, INPUT);
  pinMode(p, INPUT);

  pinMode(lrelay, OUTPUT);
  pinMode(prelay, OUTPUT);

  digitalWrite(lrelay, 0);
  digitalWrite(prelay , 0);
}

void loop() {

  // read the state of the pushbutton value:
  lState = digitalRead(l);
  pState = digitalRead(p);
  //Serial.print(" i ");
  //Serial.print(l);
  //Serial.print(" p ");
  //Serial.println(p);

  //check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (lState == LOW) {
    // turn LED on:
    digitalWrite(lrelay, HIGH);
    //Serial.println(" indicator ");
    runningLED(50);
    digitalWrite(lrelay, LOW);
  }
  else if (pState == LOW)
  {
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(1);
    Wire.endTransmission();
    // Serial.println(" park ");
    digitalWrite(prelay, HIGH);
    runningLED(200);
    digitalWrite(prelay, LOW);
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.endTransmission();
  }


}


int runningLED(int x)
{

  for (int i = 1; i < 15; i++)
  {
    digitalWrite(i, HIGH);
    delay(x);
    digitalWrite(i - 1, LOW);
  }
}
