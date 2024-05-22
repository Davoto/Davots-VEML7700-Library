#include <Arduino.h>
#include <Wire.h>
#include "VEML7700.h"

void setup() {
  // put your setup code here, to run once:
  Wire.setClock(400000);
  Wire.begin(VEML7700_ADRESS);
  Serial.begin(9600);
  standard_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  Serial.print("Lux: ");
  Serial.println(get_lux());
}