#include "DSP28x_Project.h"
#include "libs/fsk/fsk_est.h"

Uint16 decode_bits = 0;
Uint16 decode_bytes = 0;

#pragma CODE_SECTION(fsk_decode,"ramfuncs");
int16 fsk_decode(int16 *buf_in, Uint16 *buf_out, Uint16 bufSize, int16 first, Uint16 *position)
{
	int16 i,j;
	int32 decode_sum;
	int16 bit_d2 = -1,bit_d1 = -1,bit_d0 = -1;
	int16 est_corr;
	if(first)
	{
		decode_bits = 0;
		decode_bytes = 0;
	}
	if(bufSize <= 32)
	{
		*position = 0;
		return 0;
	}
	bufSize -= 32;
	for(i=0;i<bufSize;i=i+32)
	{
		decode_sum = 0;
		for(j=0;j<16;j++)
		{
			decode_sum += buf_in[i + j];
		}
		buf_out[decode_bytes] = (buf_out[decode_bytes] << 1) & 0xFF;
		if(decode_sum < 0)
		{
			buf_out[decode_bytes] |=  0x1;
			bit_d2 = bit_d1;
			bit_d1 = bit_d0;
			bit_d0 = 1;
		}
		else
		{
		    bit_d2 = bit_d1;
		    bit_d1 = bit_d0;
		    bit_d0 = 0;
		}
		decode_bits++;
		if(decode_bits == 8)
		{
			decode_bits = 0;
			decode_bytes++;
		}
		est_corr = fsk_est(&buf_in[i],bit_d2,bit_d1,bit_d0);
		i += est_corr;
	}

	if(i != 0)
	{
		*position = i;
	}
	else
	{
		*position = 0;
	}

	if(decode_bytes == 38)
	{
		decode_bits = 0;
		decode_bytes = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}
