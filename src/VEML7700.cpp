#include "VEML7700.h"
#include <Arduino.h>
#include <Wire.h>

// Public
// Standard Functions
void VEML7700::SetGain(EnumGain NewGain){
  Gain = NewGain;
  UpdateConfig0();
}

void VEML7700::SetIT(EnumIT NewIT){
  IT = NewIT;
  UpdateConfig0();
}

void VEML7700::SetPersistence(EnumPersistence NewPersistence){
  Persistence = NewPersistence;
  UpdateConfig0();
}

void VEML7700::SetInterrupt(EnumInterrupt NewInterrupt){
  Interrupt = NewInterrupt;
  UpdateConfig0();
}

void VEML7700::SetOn(EnumOn NewOn){
  On = NewOn;
  UpdateConfig0();
}

void VEML7700::SetHighT(u16 NewHighT){
  HighT = NewHighT;
  Send(COMMAND_MODE_1, NewHighT);
}

void VEML7700::SetLowT(u16 NewLowT){
  LowT = NewLowT;
  Send(COMMAND_MODE_2, NewLowT);
}

void VEML7700::SetPSM(EnumPSM NewPSM){
  PSM = NewPSM;
  Send(COMMAND_MODE_3, NewPSM);
}

int VEML7700::GetALSLux(){
  u16 val = Receive(COMMAND_MODE_4);
  return ValueLuxCalculator(val);
}

int VEML7700::GetWhiteLux(){
  u16 val = Receive(COMMAND_MODE_5);
  return ValueLuxCalculator(val); 
}

int VEML7700::GetThresholdState(){
  u16 val = Receive(COMMAND_MODE_6);
  if((val & 0x4000) == 0x4000) return 2;
  if((val & 0x8000) == 0x8000) return 1;
  return 0;
}

void VEML7700::Begin(){
  Wire.setClock(400000);
  Wire.begin(VEML7700_ADRESS);
  UpdateConfig0();
  Send(COMMAND_MODE_3, PSM);
}

void VEML7700::Send(EnumCommandMode CommandMode, u16 Command){
  Wire.beginTransmission(VEML7700_ADRESS);
  Wire.write(CommandMode);
  Wire.write(u8(Command));
  Wire.write(u8(Command >> 8));
  Wire.endTransmission();
}

u16 VEML7700::Receive(EnumCommandMode CommandMode){
  // send registry
  Wire.beginTransmission(VEML7700_ADRESS);
  Wire.write(CommandMode);
  Wire.endTransmission(false);

  // request bytes
  Wire.requestFrom(VEML7700_ADRESS, 2);
  u8 b1 = Wire.read();
  u8 b2 = Wire.read();
  u16 val = (b2 << 8) | b1;

  return val;
}

// Private

int VEML7700::ValueLuxCalculator(u16 val){
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

  int out = val * factorGain * factorIT;
  return out;
}

void VEML7700::UpdateConfig0(){
  u16 command = Gain | IT | Persistence | Interrupt | On;
  Send(COMMAND_MODE_0, command);
}
