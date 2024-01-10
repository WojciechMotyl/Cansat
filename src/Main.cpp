#include "setup_functions.h"

BMP280 bmp;

void setup()
{
    SerialUSB.begin(serial_baudrate);
    if (!start_bmp(bmp))
    {
        while (1)
        {
            SerialUSB.println("BMP initialization failed! Waiting...");
        }
    }
}

void loop()
{
    double T, P;
    bmp.measureTemperatureAndPressure(T, P);
    SerialUSB.print(T, 2);
    SerialUSB.print("\t");
    SerialUSB.println(P, 2);
}
