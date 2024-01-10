#ifndef SETUP_FUNCTIONS_H
#define SETUP_FUNCTIONS_H

#include "config.h"

void start_serial(uint32_t baudrate);

bool start_bmp(BMP280 &bmp);

#endif