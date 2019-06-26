#include "DSP28x_Project.h"
#include "libs/complex/complex.h"

Uint16 rx_ins1 = 0;
Uint16 rx_ins2 = 64;

short_complex_t rx_filter_buf[128];

#pragma CODE_SECTION(fsk_rx_filter,"ramfuncs");
void fsk_rx_filter(short_complex_t *buf, const int16* filter_table, Uint16 count)
{
    Uint16 i,j,k;
	int32 result_i,result_q;

    for (i = 0; i < count; i ++) 
	{
        result_i = 0;
        result_q = 0;
		
		rx_filter_buf[rx_ins1].I = rx_filter_buf[rx_ins2].I = buf[i].I;
		rx_filter_buf[rx_ins1].Q = rx_filter_buf[rx_ins2].Q = buf[i].Q;

        for (j = 0, k = rx_ins2; j < 64; j++, k--) 
		{
            result_i += (int32)filter_table[j] * (int32)rx_filter_buf[k].I;
            result_q += (int32)filter_table[j] * (int32)rx_filter_buf[k].Q;
        }

        buf[i].I = result_i >> 16;
        buf[i].Q = result_q >> 16;

        rx_ins2++;
        if (rx_ins2 == 128) {
            rx_ins1 = 0;
            rx_ins2 = 64;
        } else {
            rx_ins1++;
        }
    }
}

Uint16 tx_ins1 = 0;
Uint16 tx_ins2 = 64;

short_complex_t tx_filter_buf[128];

#pragma CODE_SECTION(fsk_tx_filter,"ramfuncs");
void fsk_tx_filter(short_complex_t *buf, const int16* filter_table, Uint16 count)
{
    Uint16 i,j,k;
	int32 result_i,result_q;

    for (i = 0; i < count; i ++) 
	{
        result_i = 0;
        result_q = 0;
		
		tx_filter_buf[tx_ins1].I = tx_filter_buf[tx_ins2].I = buf[i].I;
		tx_filter_buf[tx_ins1].Q = tx_filter_buf[tx_ins2].Q = buf[i].Q;

        for (j = 0, k = tx_ins2; j < 64; j++, k--) 
		{
            result_i += (int32)filter_table[j] * (int32)tx_filter_buf[k].I;
            result_q += (int32)filter_table[j] * (int32)tx_filter_buf[k].Q;
        }

        buf[i].I = result_i >> 16;
        buf[i].Q = result_q >> 16;

        tx_ins2++;
        if (tx_ins2 == 128) {
            tx_ins1 = 0;
            tx_ins2 = 64;
        } else {
            tx_ins1++;
        }
    }
}

