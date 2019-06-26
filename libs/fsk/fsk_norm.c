#include "DSP28x_Project.h"
#include "libs/complex/complex.h"

int32 power2_sum = 0;
int32 power2 = 0;

#pragma CODE_SECTION(fsk_norm,"ramfuncs");
void fsk_norm(short_complex_t *buf, Uint16 bufSize, int16 hold)
{
    Uint16 i;
    int32 power;
    Uint16 power_filter = 0;
    if(!hold)
    {
        power2_sum = 0;
        power2 = 0;

        for(i=0;i<bufSize;i++)
        {
            power = (int32)buf[i].I * (int32)buf[i].I + (int32)buf[i].Q * (int32)buf[i].Q;
            if(power < 6000)
            {
                //Blank noise power
                buf[i].I = buf[i].Q = 0;
            }
            else if(power > 30000000)
            {
                //Blank impulse power
                buf[i].I = buf[i].Q = 0;
            }
            else
            {
                power2_sum += power;
                power_filter++;
            }
            power2 = power2_sum / power_filter;
        }
    }
}
