#include <Arduino.h>
#include "VEML7700.h"

VEML7700 Ronnie;

void setup() {
  // put your setup code here, to run once:
  Ronnie.Begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  Serial.print("ALS Lux: ");
  Serial.println(Ronnie.GetALSLux());
  Serial.print("White Lux: ");
  Serial.println(Ronnie.GetWhiteLux());
}