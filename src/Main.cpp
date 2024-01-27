#include "setup_functions.h"
#include "main_functions.h"
#include <CanSatKit.h>

using namespace CanSatKit;

BMP280 bmp;
Adafruit_INA219 ina219;

Radio radio(Pins::Radio::ChipSelect,
            Pins::Radio::DIO0,
            433.0,
            Bandwidth_125000_Hz,
            SpreadingFactor_9,
            CodingRate_4_8);

Frame frame;

File file;

const unsigned long time_cycle = 1000;
unsigned long last_cycle = 0;

const String File_name = "test.txt";
int mode = 0; // 0-dev mode, 1-normal mode without Serial connection

int lm35_pin = A0;

void setup()
{
    analogReadResolution(12);
    SerialUSB.begin(serial_baudrate);
    if (!SerialUSB.available())
    {
        mode = 0;
        if (start_bmp(bmp) && start_ina(ina219) && start_radio(radio) && start_sd(file, File_name))
        {
            SerialUSB.println("Dev mode ready - configuration successful");
        }
        else
        {
            while (1)
            {
                SerialUSB.println("Dev mode - configuration failed");
            }
        }
    }
    else
    {
        mode = 1;
        if (start_bmp(bmp) && start_ina(ina219) && start_radio(radio) && start_sd(file, File_name))
        {
        }
        else
        {
            while (1)
                ;
        }
    }
}

void loop()
{
    double T = 0;
    double P = 0;
    int raw;
    float temperature;
    float shuntvoltage = 0;
    float busvoltage = 0;
    float current_mA = 0;
    float loadvoltage = 0;
    float power_mW = 0;

    int time = millis_to_secound();
    if (millis() - last_cycle >= time_cycle)
    {
        measure(ina219, bmp, T, P, raw, temperature, lm35_pin, shuntvoltage, busvoltage, current_mA, power_mW, loadvoltage);
        write_to_file(file, File_name, temperature, P, shuntvoltage, busvoltage, current_mA, power_mW, loadvoltage, time);
        radio_transmitter(radio, frame, temperature, P, shuntvoltage, busvoltage, current_mA, power_mW, loadvoltage, time);
        if (mode == 0)
        {
            serial_print(temperature, P, shuntvoltage, busvoltage, current_mA, power_mW, loadvoltage, time);
        }
        last_cycle = millis();
    }
}
