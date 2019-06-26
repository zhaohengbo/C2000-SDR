#include "DSP28x_Project.h"
#include "drivers/spi.h"
#include "drivers/mcbsp.h"
#include "libs/safepipe/safepipe.h"
#include "libs/fsk/fsk_mod.h"

int16 sx1255_tx_overrun = 0;

void sx1255_tx_reset_state(void)
{
    Uint16 *new_buf;
    fsk_mod_init();
    new_buf = safepipe_get_current_read_buf(&fsk_mod_pipe);
    EALLOW;
    DmaRegs.CH2.SRC_ADDR_SHADOW = (Uint32)new_buf;
    DmaRegs.CH2.SRC_BEG_ADDR_SHADOW = (Uint32)new_buf;
    EDIS;
}

// INT7.2
interrupt void SX1255_TX_DMA_ISR(void)     // DMA Ch2 - McBSP-A Tx
{
    Uint16 *new_buf;

    if(safepipe_readable(&fsk_mod_pipe))
    {
        safepipe_read_update(&fsk_mod_pipe);
    }
    else
    {
    	sx1255_tx_overrun = 1;
    }

    new_buf = safepipe_get_current_read_buf(&fsk_mod_pipe);

    EALLOW;
    DmaRegs.CH2.SRC_ADDR_SHADOW = (Uint32)new_buf;
    DmaRegs.CH2.SRC_BEG_ADDR_SHADOW = (Uint32)new_buf;
    EDIS;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // To receive more interrupts from this PIE group, acknowledge this interrupt
}
