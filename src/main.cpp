#include <Arduino.h>
#include "VEML7700.h"

// This file is an a selftest to see measurements from a VEML7700 sensor.



// Setup of VEML7700 Lightsensor you can change the settings based on lighting situation.
VEML7700 LightSensor(EnumGain::ALS_GAIN_0_125X, EnumIT::ALS_IT_100MS, EnumPersistence::ALS_PERS_1, EnumInterrupt::ALS_INT_ON, EnumOn::ALS_ON, EnumPSM::ALS_PSM_OFF);

void setup() {

  LightSensor.Begin();
  Serial.begin(9600);

  Serial.println("/// Welcome to the selftest for Tijs Knecht's VEML7700 Library \\\\\\ \n\nFirst some info:");
  Serial.print("Device ID in decimal: ");
  Serial.println(LightSensor.GetDeviceID());
  Serial.print("Slave Adress in decimal: ");
  Serial.println(LightSensor.GetSlaveAddress());

  Serial.println("\nNow measurements in a loop updating every 2 seconds:");

  LightSensor.AutoSetGainAndIT(MODE_ALS);
}

void loop() {
  if(LightSensor.GetHighThresExc()) Serial.println("!!! High threshold exceeded. !!!");
  if(LightSensor.GetLowThresExc()) Serial.println("!!! Low threshold exceeded. !!!");

  Serial.print("ALS Lux: ");
  Serial.println(LightSensor.GetALSLux());
  Serial.print("White Lux: ");
  Serial.println(LightSensor.GetWhiteLux());

  delay(2000);
}