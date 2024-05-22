#include "VEML7700.h"
#include <Arduino.h>
#include <Wire.h>

u16 options_command_mode_0(u16 Gain, u16 IT, u16 Persistence, u16 Interrupt, u16 On) {
    u16 output = Gain | IT | Persistence | Interrupt | On;
    return output;
}

int debug_send(u8 command_mode, u16 command){  
  Wire.beginTransmission(VEML7700_ADRESS);
  if(Wire.write(command_mode) != 1) return 1;
  if(Wire.write(u8(command)) != 1) return 2;
  if(Wire.write(u8(command >> 8)) != 1) return 3;
  if(Wire.endTransmission()) return 4;
  return 0;
  
}

int debug_receive(u8 command_mode, String text){
  // send registry
  Wire.beginTransmission(VEML7700_ADRESS);
  Wire.write(command_mode);
  Wire.endTransmission(false);

  // request bytes
  Wire.requestFrom(VEML7700_ADRESS, 2);
  u8 b1 = Wire.read();
  u8 b2 = Wire.read();
  u16 val = (b2 << 8) | b1;
  Serial.print(text);
  Serial.println(val);
  return 0;
}

int debug_interrupt_status(){
  // send registry for interrupt
  Wire.beginTransmission(VEML7700_ADRESS);
  Wire.write(COMMAND_MODE_6);
  Wire.endTransmission(false);

  // request bytes + return interrupt status
  Wire.requestFrom(VEML7700_ADRESS, 2);
  u8 b1 = Wire.read();
  u8 b2 = Wire.read();
  u16 val = (b2 << 8) | b1;
  Serial.print("Interrupt status: ");
  if(val >> 14 == 1){ 
    Serial.println("High treshold exceeded");
    return 1;
  }else if(val >> 15 == 1){
    Serial.println("Low treshold exceeded");
    return 2;
  }  
  Serial.println("Everything is fine.");
  return 0;
}

int value_lux_translator(u16 Gain, u16 IT, u16 result_raw){
  float factorGain = 1;
  float factorIT = 0.0576;

  if(Gain == ALS_GAIN_0_125X){factorGain = 8;}else
  if(Gain == ALS_GAIN_0_25X){factorGain = 4;}else
  if(Gain == ALS_GAIN_1X){factorGain = 1;}else
  if(Gain == ALS_GAIN_2X){factorGain = 0.5;}

  if(IT == ALS_IT_25MS){factorIT = 0.2304;}else
  if(IT == ALS_IT_50MS){factorIT = 0.1152;}else
  if(IT == ALS_IT_100MS){factorIT = 0.0576;}else
  if(IT == ALS_IT_200MS){factorIT = 0.0288;}else
  if(IT == ALS_IT_400MS){factorIT = 0.0144;}else
  if(IT == ALS_IT_800MS){factorIT = 0.0072;}

  int val = result_raw * factorGain * factorIT;
  // int lux = val * (1.0023f + val * (8.1488e-5f + val * (-9.3924e-9f + val * 6.0135e-13f)));

  return val;
}

void standard_setup(u16 Gain, u16 IT, u16 Persistence, u16 Interrupt, u16 On){
  u16 command = options_command_mode_0(Gain, IT, Persistence, Interrupt, On);
  Wire.beginTransmission(VEML7700_ADRESS);
  Wire.write(u8(COMMAND_MODE_0));
  Wire.write(u8(command));
  Wire.write(u8(command >> 8));
  Wire.endTransmission();
}

int get_lux(u16 Gain, u16 IT){
  // send registry
  Wire.beginTransmission(VEML7700_ADRESS);
  Wire.write(COMMAND_MODE_4);
  Wire.endTransmission(false);

  // request bytes
  Wire.requestFrom(VEML7700_ADRESS, 2);
  u8 b1 = Wire.read();
  u8 b2 = Wire.read();
  u16 val = (b2 << 8) | b1;
  
  return value_lux_translator(Gain, IT, val);
}
