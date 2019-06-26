#include "DSP28x_Project.h"
#include "libs/fsk/fsk_corr.h"

#define PREAMBLE_CODE 0xA5

static inline int16 get_preamble_bit(Uint16 bit)
{
    return ((PREAMBLE_CODE >> bit) & 0x1);
}

#pragma CODE_SECTION(fsk_corr,"ramfuncs");
int16 fsk_corr(int16 *buf, Uint16 bufSize, Uint16 *position)
{
    Uint16 window_end,i,j,k;
    int32 corr_sum,corr_temp;
    int16 corr_found_position = -1;

    if(bufSize <= 256)
    {
    	*position = 0;
        return 0;
    }
    else
    {
        window_end = bufSize - 256;
        for(i=0;(i<window_end) && (corr_found_position < 0);i=i+16)
        {
            corr_sum = 0;
            for(j=0;j<8;j++)
            {
                corr_temp = 0;
                for(k=0;k<16;k++)
                {
                    corr_temp += buf[i + (j*32) + k];
                }
                if(get_preamble_bit(j))
                {
                    if(corr_temp > -24000)
                    {
                        break;
                    }
                    else
                    {
                        corr_sum -= corr_temp;
                    }
                }
                else
                {
                    if(corr_temp < 24000)
                    {
                        break;
                    }
                    else
                    {
                        corr_sum += corr_temp;
                    }
                }
                if(j==7)
                {
                    if(corr_found_position < 0)
                    {
                    	corr_found_position = i;
                    }
                }
            }
        }

        if(corr_found_position > 0)
        {
        	*position = corr_found_position;
            return 1;
        }
        else
        {
        	*position = i;
            return 0;
        }
    }
}
