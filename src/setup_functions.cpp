#include "setup_functions.h"


void start_serial(uint32_t baudrate)
{
    SerialUSB.begin(baudrate);
    if (!SerialUSB)
        while (1)
            ;
}

bool start_bmp(BMP280& bmp)
{
    if (!bmp.begin())
    {
            SerialUSB.println("BMP init failed!");
            return false;
    }
    else
    {
        SerialUSB.println("BMP init success!");
        bmp.setOversampling(16);
        return true;
    }
}