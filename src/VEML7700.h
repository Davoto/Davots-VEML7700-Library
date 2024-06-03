#ifndef VEML7700_H
#define VEML7700_H

#include <Arduino.h>
#include "VEML7700_ENUM.h"

// Class VEML7700

class VEML7700 {
public:
  // Standard Functions  
  void SetGain(EnumGain NewGain);

  void SetIT(EnumIT NewIT);

  void SetPersistence(EnumPersistence NewPersistence);

  void SetInterrupt(EnumInterrupt NewInterrupt);

  void SetHighT(u16 NewHighT);

  void SetLowT(u16 NewLowT);

  void SetOn(EnumOn NewOn);

  void SetPSM(EnumPSM NewPSM);

  int GetALSLux();

  int GetWhiteLux();

  int GetThresholdState();

  void Begin();

  VEML7700() : Gain(ALS_GAIN_0_125X), IT(ALS_IT_100MS), Persistence(ALS_PERS_1), Interrupt(ALS_INT_ON), On(ALS_ON), PSM(ALS_PSM_OFF) {}

  VEML7700(const EnumGain& Gain) : Gain(Gain), IT(ALS_IT_100MS), Persistence(ALS_PERS_1), Interrupt(ALS_INT_ON), On(ALS_ON), PSM(ALS_PSM_OFF) {}

  VEML7700(const EnumGain& Gain, const EnumIT& IT, const EnumPersistence& Persistence, const EnumInterrupt& Interrupt, const EnumOn& On, const EnumPSM& PSM) : Gain(Gain), IT(IT), Persistence(Persistence), Interrupt(Interrupt), On(On), PSM(PSM) {} 
  
  void Send(EnumCommandMode CommandMode, u16 Command);

  u16 Receive(EnumCommandMode CommandMode);
private:
  u16 Gain, IT, Persistence, Interrupt, On, PSM, HighT, LowT;

  int ValueLuxCalculator(u16 val);

  void UpdateConfig0();
};

#endif /* VEML7700_H */