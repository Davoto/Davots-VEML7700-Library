#ifndef VEML7700_H
#define VEML7700_H

#include <Arduino.h>

// Standard adress of VEML7700
#define VEML7700_ADRESS 0x10

// Different command modes:
#define COMMAND_MODE_0 0x00
#define COMMAND_MODE_1 0x01
#define COMMAND_MODE_2 0x02
#define COMMAND_MODE_3 0x03
#define COMMAND_MODE_4 0x04
#define COMMAND_MODE_5 0x05
#define COMMAND_MODE_6 0x06
#define COMMAND_MODE_7 0x07

// Different options for command_mode 0
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

// function to combine settings of command mode 0
u16 options_command_mode_0(u16 Gain, u16 IT, u16 Persistence, u16 Interrupt, u16 On);

// function to set settings customly.
int debug_send(u8 command_mode, u16 command);

// function to recieve raw data decimally with a custom piece of text in front.
int debug_receive(u8 command_mode, String text);

// function to recieve status of interruptions.
int debug_interrupt_status();

int value_lux_translator(u16 Gain, u16 IT, u16 val);

// function standard settings
void standard_setup(u16 Gain = ALS_GAIN_0_25X, u16 IT = ALS_IT_100MS, u16 Persistence = ALS_PERS_1, u16 Interrupt = ALS_INT_ON, u16 On = ALS_ON);

int get_lux(u16 Gain = ALS_GAIN_0_25X, u16 IT = ALS_IT_100MS);
#endif /* VEML7700_H */