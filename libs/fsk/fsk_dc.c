#include "DSP28x_Project.h"
#include "libs/complex/complex.h"

int32 dc_sum_i = 0,dc_sum_q = 0;
int16 dc_i = 0,dc_q = 0;

#pragma CODE_SECTION(fsk_iq_dc,"ramfuncs");
void fsk_iq_dc(short_complex_t *buf, Uint16 bufSize, int16 hold)
{
    Uint16 i;
    if(!hold)
    {
        dc_sum_i = dc_sum_q = 0;
        for(i=0;i<bufSize;i++)
        {
            dc_sum_i += (int32)buf[i].I;
            dc_sum_q += (int32)buf[i].Q;
        }
        dc_i = dc_sum_i/bufSize;
        dc_q = dc_sum_q/bufSize;
    }

	for(i=0;i<bufSize;i++)
	{
		buf[i].I -= dc_i;
		buf[i].Q -= dc_q;
	}
}

int32 dc_sum_ang = 0;
int16 dc_ang = 0;

#pragma CODE_SECTION(fsk_iq_dc,"ramfuncs");
void fsk_ang_dc(int16 *buf, Uint16 bufSize, int16 hold)
{
    Uint16 i;
    if(!hold)
    {
    	dc_sum_ang = 0;
        for(i=0;i<bufSize;i++)
        {
        	dc_sum_ang += buf[i];
        }
        dc_ang = dc_sum_ang/bufSize;
    }

	for(i=0;i<bufSize;i++)
	{
		buf[i] -= dc_ang;
	}
}

int16 DAC_CODE_OFFSET_I = 900;//test_value, diff from chip
int16 DAC_CODE_OFFSET_Q = 300;//test_value, diff from chip

#pragma CODE_SECTION(fsk_dac_dc,"ramfuncs");
void fsk_dac_dc(short_complex_t *buf, Uint16 bufSize)
{
	Uint16 i;
	for(i=0;i<bufSize;i++)
	{
		buf[i].I += DAC_CODE_OFFSET_I;
		buf[i].Q += DAC_CODE_OFFSET_Q;
	}
}
