#include "config.h"

void write_to_file(File &file, String File_name, double temperature, double pressure, float shuntvoltage, float busvoltage, float current_mA, float loadvoltage, float power_mW, int time)
{
    if (file)
    {
        file = SD.open(File_name, FILE_WRITE);

        file.print(temperature, 2);
        file.print("\t");
        file.print(pressure, 2);
        file.print("\t");
        file.print(shuntvoltage, 2);
        file.print("\t");
        file.print(busvoltage, 2);
        file.print("\t");
        file.print(current_mA, 2);
        file.print("\t");
        file.print(loadvoltage, 2);
        file.print("\t");
        file.print(power_mW, 2);
        file.print("\t");
        file.println(time);

        file.close();
    }
}

void radio_transmitter(Radio &radio, Frame &frame, double temperature, double pressure, float shuntvoltage, float busvoltage, float current_mA, float loadvoltage, float power_mW, int time)
{
    frame.print(temperature, 2);
    frame.print("\t");
    frame.print(pressure, 2);
    frame.print("\t");
    frame.print(shuntvoltage, 2);
    frame.print("\t");
    frame.print(busvoltage, 2);
    frame.print("\t");
    frame.print(current_mA, 2);
    frame.print("\t");
    frame.print(loadvoltage, 2);
    frame.print("\t");
    frame.print(power_mW, 2);
    frame.print("\t");
    frame.println(time);

    radio.transmit(frame);

    frame.clear();
}

void serial_print(double temperature, double pressure, float shuntvoltage, float busvoltage, float current_mA, float loadvoltage, float power_mW, int time)
{
    SerialUSB.print(temperature, 2);
    SerialUSB.print("\t");
    SerialUSB.print(pressure, 2);
    SerialUSB.print("\t");
    SerialUSB.print(shuntvoltage, 2);
    SerialUSB.print("\t");
    SerialUSB.print(busvoltage, 2);
    SerialUSB.print("\t");
    SerialUSB.print(current_mA, 2);
    SerialUSB.print("\t");
    SerialUSB.print(loadvoltage, 2);
    SerialUSB.print("\t");
    SerialUSB.print(power_mW, 2);
    SerialUSB.print("\t");
    SerialUSB.println(time);
}

float lm35_raw_to_temperature(int raw)
{
    float voltage = raw * 3.3 / (pow(2, 12));
    float temperature = 100.0 * voltage;
    return temperature;
}

void measure(Adafruit_INA219 &ina219, BMP280 &bmp, double &temperature, double &pressure, int raw, float &temperature_analog, int &lm_pin,
             float &shuntvoltage, float &busvoltage, float &current_mA, float &loadvoltage, float &power_mW)
{
    bmp.measureTemperatureAndPressure(temperature, pressure);
    raw = analogRead(lm_pin);
    temperature_analog = lm35_raw_to_temperature(raw);
    shuntvoltage = ina219.getShuntVoltage_mV();
    busvoltage = ina219.getBusVoltage_V();
    current_mA = ina219.getCurrent_mA();
    power_mW = ina219.getPower_mW();
    loadvoltage = busvoltage + (shuntvoltage / 1000);
}

int millis_to_secound()
{
    return static_cast<int>(millis() / 1000);
}