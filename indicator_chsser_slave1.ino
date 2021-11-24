#include <Wire.h>  // I2C lib

#define SLAVE_ADDR 9  // I2C address of slave

int rd;  // variable to recive data

const int ldelay = 20 ; //delay between each led (smaller value = faster design)
const int l = A0;     // the number of the left signal input pin
const int lrelay = A2;
const int prelay = A3;

int lState = 0;         // variable for reading the pushbutton status

void setup() {
  Wire.begin(SLAVE_ADDR);   // start I2C connection as slave & communication
  Wire.onReceive(receiveEvent);
  // initialize the LED pin as an output:
  for (int led = 0; led < 14; led++) {
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
  }
  // initialize the pushbutton pin as an input:
  pinMode(l, INPUT);


  pinMode(lrelay, OUTPUT);
  pinMode(prelay, OUTPUT);

  digitalWrite(lrelay, 0);
  digitalWrite(prelay , 0);

}

void loop() {
  // put your main code here, to run repeatedly:

  lState = digitalRead(l);

  if (lState == LOW) {
    // turn LED on:
    digitalWrite(lrelay, HIGH);
    runningLED(50);
    digitalWrite(lrelay, LOW);
  }
  else if (rd == 1)
  {
    digitalWrite(prelay, HIGH);
    runningLED(200);
    digitalWrite(prelay, LOW);
    rd = 0;
  }
}

void receiveEvent()
{
  rd = Wire.read();

}

int runningLED(int x)
{

  for (int i = 1; i < 15; i++)
  {
    digitalWrite(i, HIGH);
    delay(x);
    digitalWrite(i - 1, LOW);
  }
  //rd=0;
}
