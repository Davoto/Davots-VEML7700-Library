#include <Arduino.h>
#include <Wire.h>
#include "VEML7700.h"

u8 Veml = VEML7700_ADRESS;
u8 command_mode = 0;
u16 command = command_mode0(ALS_GAIN_2X, ALS_IT_800MS, ALS_PERS_1, ALS_INT_ON, ALS_ON);

int send(){
  Wire.beginTransmission(Veml);
  if(Wire.write(command_mode) != 1) return 2;
  if(Wire.write(u8(0)) != 1) return 3;
  if(Wire.write(u8(command >> 8)) != 1) return 4;
  if(Wire.endTransmission()) return 5;
  return 0;
}

int receive(){
  Wire.beginTransmission(Veml);
  if(Wire.write(u8(0x04)) != 1) return 2;
  return 0;
}

void setup() {
  // put your setup code here, to run once:
  Wire.setClock(400000);
  Wire.begin(Veml);
  Serial.begin(9600);

  Serial.println(send());

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);

  u8 command_mode5 = 0x04;

  Wire.beginTransmission(Veml);
  Wire.write(command_mode5);
  Wire.endTransmission(false);

  u8 bitje = 2;

  Wire.requestFrom(Veml, bitje);
  if(Wire.available()) {
    u8 b1 = Wire.read();
    u8 b2 = Wire.read();
    u16 val = (b1 << 8) | b2;
    Serial.print("Getal: ");
    Serial.println(val);
  }
}