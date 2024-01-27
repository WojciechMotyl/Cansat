#include "setup_functions.h"

bool start_bmp(BMP280 &bmp)
{
    if (!bmp.begin())
    {
        return false;
    }
    else
    {
        bmp.setOversampling(16);
        return true;
    }
}

bool start_ina(Adafruit_INA219 &ina219)
{
    if (!ina219.begin())
    {
        return false;
    }
    else
    {
        ina219.setCalibration_16V_400mA();
        return true;
    }
}

bool start_radio(Radio &radio)
{
    if (!radio.begin())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool start_sd(File &file, String File_name)
{
    if (!SD.begin(CanSatKit::Pins::SD::ChipSelect))
    {
        return false;
    }
    else
    {
        return true;
    }
}