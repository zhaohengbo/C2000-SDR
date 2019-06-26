#include "DSP28x_Project.h"
#include "libs/safepipe/safepipe.h"
#include "libs/complex/complex.h"
#include "libs/fsk/fsk_table.h"
#include "libs/fsk/fsk_filter.h"
#include "libs/fsk/fsk_gen.h"
#include "libs/fsk/fsk_dc.h"
#include "libs/fsk/fsk_frame.h"
#include "libs/link/link_tx.h"
#include "libs/fsk/fsk_pack.h"

#include <string.h>

short_complex_t sx1255_tx_buffer[4][256];

safepipe_t fsk_mod_pipe;
Uint16 mod_state = 0;
Uint16 send_position = 0;
Uint16 send_raw_buff[38];

//int16 raw_send_i[256];
//int16 raw_send_q[256];

const void *fsk_mod_buf_p[4] = {sx1255_tx_buffer[0],sx1255_tx_buffer[1],sx1255_tx_buffer[2],sx1255_tx_buffer[3]};

void fsk_mod_init(void)
{
    memset(sx1255_tx_buffer,0,sizeof(sx1255_tx_buffer));
    safepipe_init(&fsk_mod_pipe,4,(void **)fsk_mod_buf_p);
}

#pragma CODE_SECTION(fsk_mod_loop,"ramfuncs");
void fsk_mod_loop(void)
{
    short_complex_t *write_buf;
    fsk_frame_t raw_frame;
    int16 i,txBit;
    if(safepipe_writeable(&fsk_mod_pipe))
    {
        write_buf = safepipe_get_current_write_buf(&fsk_mod_pipe);

        if(mod_state == 0)
        {
            if(link_tx_layer_send_cb(&raw_frame))
            {
                mod_state = 1;
                fsk_pack(send_raw_buff,&raw_frame);
            }
        }

        if(mod_state == 1)
        {
        	for(i=0;i<8;i++)
        	{
        		txBit = (send_raw_buff[send_position] >> (7 - i)) & 0x1;
        		if(txBit)
        		{
        			fsk_gen(write_buf + (32 * i),1,32);
        		}
        		else
        		{
        			fsk_gen(write_buf + (32 * i),-1,32);
        		}
        	}
        	send_position++;
        	if(send_position == 38)
        	{
        		send_position = 0;
        		mod_state = 0;
        	}
        }
        else
        {
        	fsk_gen(write_buf,0,256);
        }

        fsk_tx_filter(write_buf, filterTable, 256);
        fsk_dac_dc(write_buf, 256);

        //for(i=0;i<256;i++)
        //{
        //    raw_send_i[i] = write_buf[i].I;
        //    raw_send_q[i] = write_buf[i].Q;
        //}

        safepipe_write_update(&fsk_mod_pipe);
    }
}
