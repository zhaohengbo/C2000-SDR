#include "DSP28x_Project.h"
#include "libs/safepipe/safepipe.h"
#include "libs/complex/complex.h"
#include "libs/fsk/fsk_table.h"
#include "libs/fsk/fsk_dc.h"
#include "libs/fsk/fsk_filter.h"
#include "libs/fsk/fsk_norm.h"
#include "libs/fsk/fsk_corr.h"
#include "libs/fsk/fsk_ang.h"
#include "libs/fsk/fsk_decode.h"
#include "libs/fsk/fsk_frame.h"
#include "libs/fsk/fsk_unpack.h"
#include "libs/link/link_rx.h"

#include <string.h>

short_complex_t sx1255_rx_buffer[4][256];

safepipe_t fsk_demod_pipe;

const void *fsk_demod_buf_p[4] = {sx1255_rx_buffer[0],sx1255_rx_buffer[1],sx1255_rx_buffer[2],sx1255_rx_buffer[3]};

Uint16 demod_buf_position = 0;
Uint16 demod_state = 0;
int16 demod_raw_buf[512];
Uint16 decode_raw_buff[38];
//int16 sx1255_raw_i[256];
//int16 sx1255_raw_q[256];
//int16 filter_raw_i[256];
//int16 filter_raw_q[256];
//int16 norm_raw_i[256];
//int16 norm_raw_q[256];

static inline void shift_buf(int16 * buf, Uint16 shift_position)
{
	Uint16 i;
	Uint16 shift_len = demod_buf_position - shift_position;
	for(i=0;i<shift_len;i++)
	{
		buf[i] = buf[i + shift_position];
	}
	demod_buf_position -= shift_position;
}

void fsk_demod_init(void)
{
    memset(sx1255_rx_buffer,0,sizeof(sx1255_rx_buffer));
    safepipe_init(&fsk_demod_pipe,4,(void **)fsk_demod_buf_p);
}

#pragma CODE_SECTION(fsk_demod_loop,"ramfuncs");
void fsk_demod_loop(void)
{
    short_complex_t *read_buf;
    Uint16 corr_position;
    int16 corr_result;
    Uint16 decode_position;
    int16 decode_result;
    fsk_frame_t raw_frame;
    //Uint16 i;

    if(safepipe_readable(&fsk_demod_pipe))
    {
        safepipe_read_update(&fsk_demod_pipe);

        read_buf = safepipe_get_current_read_buf(&fsk_demod_pipe);

        //do demod
        //for(i=0;i<256;i++)
        {
        	//sx1255_raw_i[i] = read_buf[i].I;
        	//sx1255_raw_q[i] = read_buf[i].Q;
        }
        //fsk_iq_dc(read_buf, 256, 0);
        //DC remove can be seem as a high_pass filter
        //It is not necessary,unless you need caculate tx dc offset
        fsk_rx_filter(read_buf, filterTable, 256);
        //for(i=0;i<256;i++)
        {
            //filter_raw_i[i] = read_buf[i].I;
            //filter_raw_q[i] = read_buf[i].Q;
        }
        //fsk_norm(read_buf, 256, 0);
        //for(i=0;i<256;i++)
        {
        //    norm_raw_i[i] = read_buf[i].I;
        //    norm_raw_q[i] = read_buf[i].Q;
        }
        fsk_angle(read_buf,&demod_raw_buf[demod_buf_position],256);
        demod_buf_position += 256;

        if(demod_state == 1)
        {
        	decode_result = fsk_decode(demod_raw_buf,decode_raw_buff, demod_buf_position, 0, &decode_position);
        	shift_buf(demod_raw_buf, decode_position);
        	if(decode_result == 1)
        	{
        		if(fsk_unpack(decode_raw_buff,&raw_frame))
        		{
        		    link_rx_layer_recv_cb(&raw_frame);
        		}
        		demod_state = 0;
        	}
        }
        else
        {
        	corr_result = fsk_corr(demod_raw_buf, demod_buf_position, &corr_position);
        	shift_buf(demod_raw_buf, corr_position);
        	if(corr_result == 1)
        	{
        		decode_result = fsk_decode(demod_raw_buf,decode_raw_buff, demod_buf_position, 1, &decode_position);
        		shift_buf(demod_raw_buf, decode_position);
        		if(decode_result == 0)
        		{
        			demod_state = 1;
        		}
        	}
        }
    }
}
