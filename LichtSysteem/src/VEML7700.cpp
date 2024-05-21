#include "VEML7700.h"
#include <Arduino.h>
#include <Wire.h>

u16 command_mode0(u16 Gain, u16 IT, u16 Persistence, u16 Interrupt, u16 On) {
    u16 output = Gain | IT | Persistence | Interrupt | On;
    return output;
}