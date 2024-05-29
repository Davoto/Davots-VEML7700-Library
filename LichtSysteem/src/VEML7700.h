#ifndef VEML7700_H
#define VEML7700_H

#include <Arduino.h>
#include "VEML7700_CONFIG.h"

// Class VEML7700

class VEML7700 {
public:
  // Standard Functions  
  void SetGain(EnumGain NewGain);

  void SetIT(EnumIT NewIT);

  void SetPersistence(EnumPersistence NewPersistence);

  void SetInterrupt(EnumInterrupt NewInterrupt);

  void SetOn(EnumOn NewOn);

  void SetPSM(EnumPowerSave NewPSM);

  int GetALSLux();

  int GetWhiteLux();

  void Begin();

  VEML7700() : Gain(ALS_GAIN_0_125X), IT(ALS_IT_100MS), Persistence(ALS_PERS_1), Interrupt(ALS_INT_ON), On(ALS_ON) {}

  VEML7700(const EnumGain& Gain) : Gain(Gain), IT(ALS_IT_100MS), Persistence(ALS_PERS_1), Interrupt(ALS_INT_ON), On(ALS_ON) {}

  VEML7700(const u16& Gain, const u16& IT, const u16& Persistence, const u16& Interrupt, const u16& On) : Gain(Gain), IT(IT), Persistence(Persistence), Interrupt(Interrupt), On(On) {} 
  
  void Send(EnumCommandMode CommandMode, u16 Command);

  u16 Receive(EnumCommandMode CommandMode);
private:
  u16 Gain, IT, Persistence, Interrupt, On;

  // Translates the settings for config_0
  u16 TranslatorConfig0();

  int ValueLuxCalculator(u16 val);

  void UpdateConfig0();
};

#endif /* VEML7700_H */