#include "DSP28x_Project.h"
#include "libs/safepipe/safepipe.h"
#include "libs/fsk/fsk_frame.h"

#include <string.h>

fsk_frame_t link_rx_buffer[4];

safepipe_t link_rx_pipe;

const void *link_rx_buf_p[4] = {&link_rx_buffer[0],&link_rx_buffer[1],&link_rx_buffer[2],&link_rx_buffer[3]};

void link_rx_layer_init(void)
{
    memset(link_rx_buffer,0,sizeof(link_rx_buffer));
    safepipe_init(&link_rx_pipe,4,(void **)link_rx_buf_p);
}

#pragma CODE_SECTION(link_rx_layer_recv_cb,"ramfuncs");
int16 link_rx_layer_recv_cb(fsk_frame_t * recv_frame)
{
    fsk_frame_t *new_frame;
    if(safepipe_writeable(&link_rx_pipe))
    {
        new_frame = safepipe_get_current_write_buf(&link_rx_pipe);

        memcpy(new_frame,recv_frame,sizeof(fsk_frame_t));

        safepipe_write_update(&link_rx_pipe);
        return 1;
    }
    return 0;
}

#pragma CODE_SECTION(link_rx_loop,"ramfuncs");
void link_rx_loop(void)
{
    fsk_frame_t *new_frame;
    if(safepipe_readable(&link_rx_pipe))
    {
        safepipe_read_update(&link_rx_pipe);
        new_frame = safepipe_get_current_read_buf(&link_rx_pipe);
    }
}
