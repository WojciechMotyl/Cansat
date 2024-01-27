#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

void write_to_file(File &file, String File_name, double temperature, double pressure, float shuntvoltage,
                   float busvoltage, float current_mA, float loadvoltage, float power_mW, int time);

void radio_transmitter(Radio &radio, Frame &frame, double temperature,
                       double pressure, float shuntvoltage, float busvoltage,
                       float current_mA, float loadvoltage, float power_mW, int time);

void serial_print(double temperature, double pressure, float shuntvoltage,
                  float busvoltage, float current_mA, float loadvoltage, float power_mW, int time);

float lm35_raw_to_temperature(int raw);

void measure(Adafruit_INA219 &ina219, BMP280 &bmp, double &temperature, double &pressure, int raw, float &temperature_analog, int &lm_pin,
             float &shuntvoltage, float &busvoltage, float &current_mA, float &loadvoltage, float &power_mW);

int millis_to_secound();

#endif