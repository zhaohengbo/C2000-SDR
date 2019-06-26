#include "DSP28x_Project.h"

static inline int32 epl_sum(int16 *buf)
{
    Uint16 i;
    int32 sum = 0;
    for(i=0;i<16;i++)
    {
        sum += buf[i];
    }
    return sum;
}

#pragma CODE_SECTION(fsk_est,"ramfuncs");
int16 fsk_est(int16 *buf,int16 bit_earl,int16 bit_curr,int16 bit_late)
{
    int16 *buf_earl = buf - 16 - 32;
    int16 *buf_late = buf - 16;
    int32 delta,abs_delta;
    //A Part of Delay Lock Loop
    if((bit_earl == 0) && (bit_curr == 1) && (bit_late == 0))
    {
        delta = epl_sum(buf_earl) - epl_sum(buf_late);
        abs_delta = (delta < 0) ? (0 - delta) : (delta);
        if(abs_delta < 4000)
        {
            return 0;
        }
        else if(delta >= 4000)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    else if((bit_earl == 1) && (bit_curr == 0) && (bit_late == 1))
    {
        delta = epl_sum(buf_earl) - epl_sum(buf_late);
        abs_delta = (delta < 0) ? (0 - delta) : (delta);
        if(abs_delta < 4000)
        {
            return 0;
        }
        else if(delta >= 4000)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
}
