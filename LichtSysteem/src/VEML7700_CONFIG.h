#ifndef VEML7700_CONFIG_H
#define VEML7700_CONFIG_H

// Standard adress of VEML7700
enum EnumAdress{
  VEML7700_ADRESS = 0x10
};

// Different command modes:
enum EnumCommandMode{
  COMMAND_MODE_0 = 0x00,
  COMMAND_MODE_1 = 0x01,
  COMMAND_MODE_2 = 0x02,
  COMMAND_MODE_3 = 0x03,
  COMMAND_MODE_4 = 0x04,
  COMMAND_MODE_5 = 0x05,
  COMMAND_MODE_6 = 0x06,
  COMMAND_MODE_7 = 0x07
};

// Different options for command_mode_0
// Different Gain options
enum EnumGain{
  ALS_GAIN_0_125X = 0x1000,
  ALS_GAIN_0_25X = 0x1800,
  ALS_GAIN_1X = 0x0000,
  ALS_GAIN_2X = 0x0800
};

// Different integration time settings
enum EnumIT{
  ALS_IT_25MS = 0x0300,
  ALS_IT_50MS = 0x0200,
  ALS_IT_100MS = 0x0000,
  ALS_IT_200MS = 0x0080,
  ALS_IT_400MS = 0x0100,
  ALS_IT_800MS = 0x0180
};

// Different persistence protection numbers
enum EnumPersistence{
  ALS_PERS_1 = 0x0000,
  ALS_PERS_2 = 0x0010,
  ALS_PERS_4 = 0x0020,
  ALS_PERS_8 = 0x0030
};

// Interrupt on/off
enum EnumInterrupt{
  ALS_INT_OFF = 0x0000,
  ALS_INT_ON = 0x0002
};

// Power on/off
enum EnumOn{
  ALS_ON = 0x0000,
  ALS_OFF = 0x0001
};

enum EnumPowerSave{
  ALS_PSM_OFF = 0x0000,
  ALS_PSM_1 = 0x0001,
  ALS_PSM_2 = 0x0003,
  ALS_PSM_3 = 0x0005,
  ALS_PSM_4 = 0x0007
};

#endif /* VEML7700_CONFIG_H */