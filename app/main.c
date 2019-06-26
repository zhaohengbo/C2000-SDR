#include "DSP28x_Project.h"
#include "app/init.h"
#include "libs/safepipe/safepipe.h"
#include "libs/fsk/fsk_mod.h"
#include "libs/fsk/fsk_demod.h"
#include "libs/fsk/fsk_frame.h"
#include "libs/link/link_rx.h"
#include "libs/link/link_tx.h"

void main(void)
{
    DeviceInit();
    link_rx_layer_init();
    link_tx_layer_init();
    while(1)
    {
        link_rx_loop();
        link_tx_loop();
        fsk_demod_loop();
        fsk_mod_loop();
    }
}
