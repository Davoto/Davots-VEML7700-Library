#ifndef VEML7700_H
#define VEML7700_H

#include <Arduino.h>

// Standard adress of VEML7700
#define VEML7700_ADRESS 0x10


// Different options for command mode #0
#define COMMAND_MODE_0 0x00
// Different Gain options
#define ALS_GAIN_0_125X 0x1000
#define ALS_GAIN_0_25X 0x1800
#define ALS_GAIN_1X 0x0000
#define ALS_GAIN_2X 0x0800

// Different integration time settings
#define ALS_IT_25MS 0x0300
#define ALS_IT_50MS 0x0200
#define ALS_IT_100MS 0x0000
#define ALS_IT_200MS 0x0080
#define ALS_IT_400MS 0x0100
#define ALS_IT_800MS 0x0180

// Different persistence protection numbers
#define ALS_PERS_1 0x0000
#define ALS_PERS_2 0x0010
#define ALS_PERS_4 0x0020
#define ALS_PERS_8 0x0030

// Interrupt on/off
#define ALS_INT_OFF 0x0000
#define ALS_INT_ON 0x0002

// Power on/off
#define ALS_ON 0x0000
#define ALS_OFF 0x0001


u16 command_mode0(u16 Gain, u16 IT, u16 Persistence, u16 Interrupt, u16 On);

#endif /* VEML7700_H */