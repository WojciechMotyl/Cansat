#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#define GENERATOR 1
#define BATTERY 2

void write_to_file(File &file, String File_name, double temperature, double pressure, float &voltage_battery,
                   float &voltage_generator, float &current_generator, float &current_battery, int time, float generator_work);

void radio_transmitter(Radio &radio, Frame &frame, double temperature,
                       double pressure, float &voltage_battery, float &voltage_generator, float &current_generator, float &current_battery, int time, float generator_work);

void serial_print(double temperature, double pressure, float &voltage_battery,
                  float &voltage_generator, float &current_generator, float &current_battery, int time, float generator_work);

void measure(INA3221 &ina, BMP280 &bmp, double &temperature, double &pressure, float &voltage_battery,
             float &voltage_generator, float &current_generator, float &current_battery);

int millis_to_secound();

#endif