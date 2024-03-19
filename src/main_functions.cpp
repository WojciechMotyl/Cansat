#include "config.h"

void write_to_file(File &file, String File_name, double temperature, double pressure, float &voltage_battery,
                   float &voltage_generator, float &current_generator, float &current_battery, int time, float generator_work)
{
    if (file)
    {
        file = SD.open(File_name, FILE_WRITE);

        file.print(temperature, 2);
        file.print("\t");
        file.print(pressure, 2);
        file.print("\t");
        file.print(voltage_battery, 2);
        file.print("\t");
        file.print(current_battery, 2);
        file.print("\t");
        file.print(voltage_generator, 2);
        file.print("\t");
        file.print(current_generator, 2);
        file.print("\t");
        file.print(generator_work, 2);
        file.print("\t");
        file.println(time);

        file.close();
    }
}

void radio_transmitter(Radio &radio, Frame &frame, double temperature,
                       double pressure, float &voltage_battery, float &voltage_generator, float &current_generator, float &current_battery, int time, float generator_work)
{
    frame.print(temperature, 2);
    frame.print("\t");
    frame.print(pressure, 2);
    frame.print("\t");
    frame.print(voltage_battery, 2);
    frame.print("\t");
    frame.print(current_battery, 2);
    frame.print("\t");
    frame.print(voltage_generator, 2);
    frame.print("\t");
    frame.print(current_generator, 2);
    frame.print("\t");
    frame.print(generator_work, 2);
    frame.print("\t");
    frame.println(time);

    radio.transmit(frame);

    frame.clear();
}

void serial_print(double temperature, double pressure, float &voltage_battery,
                  float &voltage_generator, float &current_generator, float &current_battery, int time, float generator_work)
{
    SerialUSB.print(temperature, 2);
    SerialUSB.print("\t");
    SerialUSB.print(pressure, 2);
    SerialUSB.print("\t");
    SerialUSB.print(voltage_battery, 2);
    SerialUSB.print("\t");
    SerialUSB.print(current_battery, 2);
    SerialUSB.print("\t");
    SerialUSB.print(voltage_generator, 2);
    SerialUSB.print("\t");
    SerialUSB.print(current_generator, 2);
    SerialUSB.print("\t");
    SerialUSB.print(generator_work, 2);
    SerialUSB.print("\t");
    SerialUSB.println(time);
}

void measure(INA3221 &ina, BMP280 &bmp, double &temperature, double &pressure, float &voltage_battery,
             float &voltage_generator, float &current_generator, float &current_battery)
{
    bmp.measureTemperatureAndPressure(temperature, pressure);
    current_generator = ina.getCurrent(INA3221_CH2) * 1000;
    voltage_generator = ina.getVoltage(INA3221_CH2);
    current_battery = ina.getCurrent(INA3221_CH1);
    voltage_battery = ina.getVoltage(INA3221_CH1);
}

int millis_to_secound()
{
    return static_cast<int>(millis() / 1000);
}