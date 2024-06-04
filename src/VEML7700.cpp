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
  AutoDelay();
  u16 val = Receive(COMMAND_MODE_4);
  return ValueLuxCalculator(val);
}

int VEML7700::GetWhiteLux(){
  AutoDelay();
  u16 val = Receive(COMMAND_MODE_5);
  return ValueLuxCalculator(val); 
}

int VEML7700::GetAutoALSLux(){
  AutoSetGainAndIT(MODE_ALS);
  return GetALSLux();
}

int VEML7700::GetAutoWhiteLux(){
  AutoSetGainAndIT(MODE_WHITE);
  return GetWhiteLux();
}

bool VEML7700::GetHighThresExc(){
  if((Receive(COMMAND_MODE_6) & 0x4000) == 0x4000) return true;
  return false;
}

bool VEML7700::GetLowThresExc(){
  if((Receive(COMMAND_MODE_6) & 0x8000) == 0x8000) return true;
  return false;
}

u8 VEML7700::GetSlaveAddress(){
  return Receive(COMMAND_MODE_7) >> 8;
}

u8 VEML7700::GetDeviceID(){
  return Receive(COMMAND_MODE_7);
}

void VEML7700::AutoSetGainAndIT(EnumWhiteALS WhiteOrALS){
  const EnumGain GainList[] = {ALS_GAIN_0_125X, ALS_GAIN_0_25X, ALS_GAIN_1X, ALS_GAIN_2X};
  const EnumIT ITList[] = {ALS_IT_25MS, ALS_IT_50MS, ALS_IT_100MS, ALS_IT_200MS, ALS_IT_400MS, ALS_IT_800MS};

  u8 GainIndex = 0;
  u8 ITIndex = 2;

  SetGain(GainList[GainIndex]);
  SetIT(ITList[ITIndex]);

  u16 ALS = Receive(EnumCommandMode(WhiteOrALS));

  if(ALS <= 100) {
    while ((ALS <= 100) && !((GainIndex == 3) && (ITIndex == 5))) {
      if(GainIndex < 3) {
        GainIndex++;
        SetGain(GainList[GainIndex]);
      } else if(ITIndex < 5){
        ITIndex++;
        SetIT(ITList[ITIndex]);
      }
      AutoDelay();
      ALS = Receive(EnumCommandMode(WhiteOrALS));
    } 
  }else {
    while ((ALS > 10000) && (ITIndex > 0)){
      ITIndex--;
      SetIT(ITList[ITIndex]);
      AutoDelay();
      ALS = Receive(EnumCommandMode(WhiteOrALS));
    }
  }
}

void VEML7700::Begin(){
  Wire.setClock(400000);
  Wire.begin(VEML7700_ADRESS);
  UpdateConfig0();
  Send(COMMAND_MODE_3, PSM);
}

// Private

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

int VEML7700::ValueLuxCalculator(u16 val){
  float factorGain, factorIT;

  switch(Gain) {
    case ALS_GAIN_0_125X:
      factorGain = 8;
      break;
    case ALS_GAIN_0_25X:
      factorGain = 4;
      break;
    case ALS_GAIN_1X:
      factorGain = 1;
      break;
    case ALS_GAIN_2X:
      factorGain = 0.5;
      break;
    default:
      factorGain = 1;
      break;
  }

  switch (IT) {
    case ALS_IT_25MS:
      factorIT = 0.2304;
      break;
    case ALS_IT_50MS:
      factorIT = 0.1152;
      break;
    case ALS_IT_100MS:
      factorIT = 0.0576;
      break;
    case ALS_IT_200MS:
      factorIT = 0.0288;
      break;
    case ALS_IT_400MS:
      factorIT = 0.0144;
      break;
    case ALS_IT_800MS:
      factorIT = 0.0072;
      break;
    default:
      factorIT = 0.0576;
      break;
  }

  int out = val * factorGain * factorIT;
  if(IT == ALS_IT_25MS or IT == ALS_IT_50MS) out = (((6.0135e-13 * out - 9.3924e-9) * out + 8.1488e-5) * out + 1.0023) * out;
  return out;
}

void VEML7700::UpdateConfig0(){
  u16 command = Gain | IT | Persistence | Interrupt | On;
  Send(COMMAND_MODE_0, command);
}

void VEML7700::AutoDelay(){
  switch (IT) {
      case ALS_IT_25MS:
      delay(25);
      break;
    case ALS_IT_50MS:
      delay(50);
      break;
    case ALS_IT_100MS:
      delay(100);
      break;
    case ALS_IT_200MS:
      delay(200);
      break;
    case ALS_IT_400MS:
      delay(400);
      break;
    case ALS_IT_800MS:
      delay(800);
      break;
    default:
      delay(100);
      break;  
  }
}