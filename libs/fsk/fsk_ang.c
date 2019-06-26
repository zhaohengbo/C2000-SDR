#include "DSP28x_Project.h"
#include "libs/complex/complex.h"
#include "libs/fsk/fsk_table.h"

#pragma CODE_SECTION(angle_unwrap,"ramfuncs");
static int16 angle_unwrap(int16 angle_prev, int16 angle)
{
    int32 diff = (int32)angle - (int32)angle_prev;
    if (diff > 18000){
        return diff - 36000;
    }else if (diff < -18000){
        return diff + 36000;
    }
	return diff;
}

#pragma CODE_SECTION(fsk_angle,"ramfuncs");
void fsk_angle(short_complex_t *buf_in, int16 *buf_out, Uint16 bufSize)
{
    int i,new_a;
    static int16 old_a = 0;
    for(i=0;i<256;i++)
    {
        new_a = atan2_table_16(buf_in[i].Q,buf_in[i].I);
        buf_out[i] = angle_unwrap(old_a,new_a);
        if(buf_out[i] > 5000)
        {
        	buf_out[i] = 5000;
        }
        else if(buf_out[i] < -5000)
        {
        	buf_out[i] = -5000;
        }
		old_a = new_a;
    }
}

