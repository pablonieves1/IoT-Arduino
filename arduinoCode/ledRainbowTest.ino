/*
First test code for ESP8266
*/

#include <Arduino.h>

#define WHITE 5
#define GREEN 4
#define YELLOW 0
#define RED 2

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  pinMode(WHITE, OUTPUT); 
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(WHITE, HIGH);
  Serial.println("white is off");
  delay(100);
  digitalWrite(WHITE, LOW);
  digitalWrite(GREEN, HIGH);
  Serial.println("green on white off");
  delay(100);
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, HIGH);
  Serial.println("yellow on green off");
  delay(100);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, HIGH);
  Serial.println("red on yellow off");
  delay(100);
  digitalWrite(RED, LOW);
  delay(1000);
}
