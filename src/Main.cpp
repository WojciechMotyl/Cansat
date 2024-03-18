#include "setup_functions.h"
#include "main_functions.h"
#include <CanSatKit.h>

using namespace CanSatKit;

BMP280 bmp;
INA3221 ina(INA3221_ADDR40_GND);

Radio radio(Pins::Radio::ChipSelect,
            Pins::Radio::DIO0,
            433.0,
            Bandwidth_125000_Hz,
            SpreadingFactor_10,
            CodingRate_4_8);

Frame frame;

File file;

const unsigned long time_cycle = 1000;
unsigned long last_cycle = 0;

const String File_name = "test.txt";
int mode = 0; // 0-dev mode, 1-normal mode without Serial connection

void setup()
{
    start_ina(ina);
    SerialUSB.begin(serial_baudrate);
    if (!SerialUSB.available())
    {
        mode = 0;
        if (start_bmp(bmp) && start_radio(radio))
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
        if (start_bmp(bmp) && start_radio(radio))
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
    float current_generator = 0;
    float current_battery = 0;
    float voltage_generator = 0;
    float voltage_battery = 0;
    float power_generator = 0;
    float power_battery = 0;
    float generator_work = 0;
    generator_work = current_generator * current_generator * 1000;
    int time = millis_to_secound();
    if (millis() - last_cycle >= time_cycle)
    {
        measure(ina, bmp, T, P, voltage_battery, voltage_generator, current_battery, current_generator);
        write_to_file(file, File_name, T, P, voltage_battery, voltage_generator, current_battery, current_generator, time);
        radio_transmitter(radio, frame, T, P, voltage_battery, voltage_generator, current_battery, current_generator, time);
        if (mode == 0)
        {
            serial_print(T, P, voltage_battery, voltage_generator, current_battery, current_generator, time);
        }
        last_cycle = millis();
    }
}
