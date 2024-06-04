#ifndef VEML7700_H
#define VEML7700_H

#include <Arduino.h>
#include "VEML7700_ENUM.h"

/// @file

/// @brief 
/// VEML7700 Class
/// @details 
/// This class includes all functions and variables used for the VEML7700 16bit high accuracy light sensor using a I²C Interface.

class VEML7700 {
public:

  /// @brief SetGain Function
  /// @details Like the title says it sets a new Gain setting and updates the appropriate registry.
  /// @param NewGain Requires a new Gain that falls under EnumGain.  
  void SetGain(EnumGain NewGain);

  /// @brief SetIT Function
  /// @details Like the title says it sets a new IT (Integration Time) setting and updates the appropriate registry.
  /// @param NewIT Requires a new IT that falls under EnumIT.  
  void SetIT(EnumIT NewIT);

  /// @brief SetPersistence Function
  /// @details Like the title says it sets a new Persistence setting and updates the appropriate registry.
  /// @param NewPersistence Requires a new Persistence that falls under EnumPersistence.  
  void SetPersistence(EnumPersistence NewPersistence);

  /// @brief SetInterrupt Function
  /// @details Like the title says it sets a new Interrupt setting and updates the appropriate registry.
  /// @param NewInterrupt Requires a new Interrupt that falls under EnumInterrupt.  
  void SetInterrupt(EnumInterrupt NewInterrupt);

  /// @brief SetHighT(hreshold) Function
  /// @details Like the title says it sets a new High Threshold setting and updates the appropriate registry.
  /// @param NewHighT Requires a new High Treshold thats a unsigned 16 bit integer.  
  void SetHighT(u16 NewHighT);

  /// @brief SetLowT(hreshold) Function
  /// @details Like the title says it sets a new Low Threshold setting and updates the appropriate registry.
  /// @param NewLowT Requires a new High Threshold thats a unsigned 16 bit integer.
  void SetLowT(u16 NewLowT);

  /// @brief On/off Function
  /// @details Like the title says it sets the sensor on/off setting and updates the appropriate registry.
  /// @param NewOn Requires on/off that falls under EnumOn.  
  void SetOn(EnumOn NewOn);

  /// @brief Powersave Mode Function
  /// @details Like the title says it sets a new Powersave Mode setting and updates the appropriate registry.
  /// @param NewPSM Requires a new Powersave Mode setting that falls under EnumPSM.  
  void SetPSM(EnumPSM NewPSM);

  /// @brief Get ALS(Ambient Light Sensor) Lux value Function.
  /// @details This function gets the ALS value of the appropriate registry and converts it based on a known list of values appropriate to the Gain and IT settings.
  /// @return A integer of the lux value measured by the sensor.
  int GetALSLux();

  /// @brief Get White light Lux value Function.
  /// @details This function gets the White Light value of the appropriate registry and converts it based on a known list of values appropriate to the Gain and IT settings.
  /// @return A integer of the lux value measured by the sensor.
  int GetWhiteLux();

  /// @brief Get Automated ALS(Ambient Light Sensor) Lux value Function.
  /// @details This function like GetALSLux() returns the light value measured by the sensor, only before it gives that it changes Gain and IT settings for a more accurate reading.
  /// @return A integer of the light value measured by the sensor.
  int GetAutoALSLux();

  /// @brief Get Automated White Light Lux value Function.
  /// @details This function like GetWhiteLux() returns the light value measured by the sensor, only before it gives that it changes Gain and IT settings for a more accurate reading.
  /// @return A integer of the light value measured by the sensor.
  int GetAutoWhiteLux();

  /// @brief Get High Threshold Exceeded Function.
  /// @details Gives a true value when the High Threshold is exceeded according to the appropriate registry of the sensor.
  /// @return A boolean value based on the exceding of the High Threshold.
  bool GetHighThresExc();

  /// @brief Get Low Threshold Exceeded Function.
  /// @details Gives a true value when the Low Threshold is exceeded according to the appropriate registry of the sensor.
  /// @return A boolean value based on the exceding of the Low Threshold.
  bool GetLowThresExc();

  /// @brief Get Slave Address Function.
  /// @details Gives a integer of the of the Slave Address of the sensor.
  /// @return Integer of the Slave Address.
  u8 GetSlaveAddress();

  /// @brief Get Device ID Function.
  /// @details Gives a integer of the of the Device ID of the sensor.
  /// @return Integer of the Device ID.
  u8 GetDeviceID();

  /// @brief Auto Set Gain And IT Function.
  /// @details Tests different Gain and IT settings for the most accurate reading of the selected registry White Light or ALS(Ambient Light Sensor).
  /// @param WhiteOrALS Option between White Light or ALS based automation.
  void AutoSetGainAndIT(EnumWhiteALS WhiteOrALS);

  /// @brief Starts the connection of the sensor using I²C.
  void Begin();

  /// @brief Sets up VEML7700 with standard settings.
  VEML7700() : Gain(ALS_GAIN_0_125X), IT(ALS_IT_100MS), Persistence(ALS_PERS_1), Interrupt(ALS_INT_ON), On(ALS_ON), PSM(ALS_PSM_OFF) {}

  /// @brief Sets up VEML7700 With standard settings except Gain.
  /// @param Gain Requires Gain setting according to EnumGain.
  VEML7700(const EnumGain& Gain) : Gain(Gain), IT(ALS_IT_100MS), Persistence(ALS_PERS_1), Interrupt(ALS_INT_ON), On(ALS_ON), PSM(ALS_PSM_OFF) {}

  /// @brief Sets up VEML7700 Manually requiring all settings.
  /// @param Gain Requires Gain setting according to EnumGain.
  /// @param IT Requires IT setting according to EnumIT.
  /// @param Persistence Requires Persistence setting according to EnumPersistence.
  /// @param Interrupt Requires Interrupt setting according to EnumInterrupt.
  /// @param On Requires On setting according to EnumOn.
  /// @param PSM Requires PSM setting according to EnumPSM.
  VEML7700(const EnumGain& Gain, const EnumIT& IT, const EnumPersistence& Persistence, const EnumInterrupt& Interrupt, const EnumOn& On, const EnumPSM& PSM) : Gain(Gain), IT(IT), Persistence(Persistence), Interrupt(Interrupt), On(On), PSM(PSM) {} 

private:
  u16 Gain, IT, Persistence, Interrupt, On, PSM, HighT, LowT;

  void Send(EnumCommandMode CommandMode, u16 Command);

  u16 Receive(EnumCommandMode CommandMode);
  
  int ValueLuxCalculator(u16 val);

  void UpdateConfig0();

  void AutoDelay();
};

#endif /* VEML7700_H */