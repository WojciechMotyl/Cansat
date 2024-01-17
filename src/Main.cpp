#include "setup_functions.h"
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

const unsigned long time_cycle = 1000;
unsigned long last_cycle = 0;

int counter = 1; // to test radio

const String File_name = "test.txt";

void write_to_file(double temperature, double pressure, float shuntvoltage, float busvoltage, float current_mA, float loadvoltage, float power_mW);

void radio_transmitter_test(Radio &radio, Frame &frame, double temperature, double pressure, float shuntvoltage, float busvoltage, float current_mA, float loadvoltage, float power_mW);

void serial_print(double temperature, double pressure, float shuntvoltage, float busvoltage, float current_mA, float loadvoltage, float power_mW);

void setup()
{
    SerialUSB.begin(serial_baudrate);
    if (!start_bmp(bmp))
        while (1)
            ;

    radio.begin();
    if (!SD.begin(CanSatKit::Pins::SD::ChipSelect))
    {
        SerialUSB.println("SD card not found");
        while (1)
            ;
    }
    else
    {
        SerialUSB.println("SD card found");
    }

    if (!ina219.begin())
    {
        SerialUSB.println("Sensor not detected");
        while (1)
            ;
    }
    else
    {
        SerialUSB.println("SD card found");
    }
}
void loop()
{
    double T, P;

    float shuntvoltage = 0;
    float busvoltage = 0;
    float current_mA = 0;
    float loadvoltage = 0;
    float power_mW = 0;

    if (millis() - last_cycle >= time_cycle)
    {
        bmp.measureTemperatureAndPressure(T, P);
        shuntvoltage = ina219.getShuntVoltage_mV();
        busvoltage = ina219.getBusVoltage_V();
        current_mA = ina219.getCurrent_mA();
        power_mW = ina219.getPower_mW();
        loadvoltage = busvoltage + (shuntvoltage / 1000);

        write_to_file(T, P, shuntvoltage, busvoltage, current_mA, power_mW, loadvoltage);
        serial_print(T, P, shuntvoltage, busvoltage, current_mA, power_mW, loadvoltage);
        radio_transmitter_test(radio, frame, T, P, shuntvoltage, busvoltage, current_mA, power_mW, loadvoltage);
        last_cycle = millis();
    }
}

void write_to_file(double temperature, double pressure, float shuntvoltage, float busvoltage, float current_mA, float loadvoltage, float power_mW)
{
    File file = SD.open(File_name, FILE_WRITE);

    if (file)
    {
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
        file.println(power_mW, 2);

        file.close();
    }
    else
    {
        SerialUSB.println("File do not open");
    }
}

void radio_transmitter_test(Radio &radio, Frame &frame, double temperature, double pressure, float shuntvoltage, float busvoltage, float current_mA, float loadvoltage, float power_mW)
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
    frame.println(power_mW, 2);

    radio.transmit(frame);

    // for tests
    SerialUSB.println(frame);

    frame.clear();
}

void serial_print(double temperature, double pressure, float shuntvoltage, float busvoltage, float current_mA, float loadvoltage, float power_mW)
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
    SerialUSB.println(power_mW, 2);
}