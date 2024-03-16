#ifndef SETUP_FUNCTIONS_H
#define SETUP_FUNCTIONS_H

#include "config.h"

void start_serial(uint32_t baudrate);

bool start_bmp(BMP280 &bmp);

void start_ina(INA3221 &ina);

bool start_radio(Radio &radio);

bool start_sd(File &file, String File_name);

#endif