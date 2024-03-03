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

void start_ina(INA3221 &ina)
{
    ina.begin(&Wire);
    ina.reset();
    ina.setShuntRes(10, 10, 10);
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