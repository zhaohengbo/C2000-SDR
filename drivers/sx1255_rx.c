#include "DSP28x_Project.h"
#include "drivers/spi.h"
#include "drivers/mcbsp.h"
#include "libs/safepipe/safepipe.h"
#include "libs/fsk/fsk_demod.h"

int16 sx1255_rx_overrun = 0;

void sx1255_rx_reset_state(void)
{
    Uint16 *new_buf;
    fsk_demod_init();
    new_buf = safepipe_get_current_write_buf(&fsk_demod_pipe);
    EALLOW;
    DmaRegs.CH1.DST_ADDR_SHADOW = (Uint32)new_buf;
    DmaRegs.CH1.DST_BEG_ADDR_SHADOW = (Uint32)new_buf;
    EDIS;
}

interrupt void SX1255_RX_DMA_ISR(void)     // DMA Ch1 - McBSP-A Rx
{
    Uint16 *new_buf;
    if(safepipe_writeable(&fsk_demod_pipe))
    {
        safepipe_write_update(&fsk_demod_pipe);
    }
    else
    {
    	sx1255_rx_overrun = 1;
    }

    new_buf = safepipe_get_current_write_buf(&fsk_demod_pipe);
    EALLOW;
    DmaRegs.CH1.DST_ADDR_SHADOW = (Uint32)new_buf;
    DmaRegs.CH1.DST_BEG_ADDR_SHADOW = (Uint32)new_buf;
    EDIS;
// To receive more interrupts from this PIE group, acknowledge this interrupt
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    EDIS;
}
