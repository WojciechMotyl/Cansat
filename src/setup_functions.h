#ifndef SETUP_FUNCTIONS_H
#define SETUP_FUNCTIONS_H

#include "config.h"

void start_serial(uint32_t baudrate);

bool start_bmp(BMP280 &bmp);

bool start_ina(Adafruit_INA219 &ina219);

bool start_radio(Radio &radio);

bool start_sd(File &file, String File_name);



#endif