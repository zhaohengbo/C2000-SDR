#include "DSP28x_Project.h"

int16 spia_xmit(int16 spiTxData)
{
    SpiaRegs.SPITXBUF = spiTxData;
    while (SpiaRegs.SPISTS.bit.INT_FLAG != 1) {}    // Wait until character has been transferred
    return SpiaRegs.SPIRXBUF;              // Clears INT_FLAG
}

void spia_init(void)
{
    SpiaRegs.SPICCR.bit.SPISWRESET = 0;     // Hold SPI in reset
    SpiaRegs.SPIFFTX.bit.SPIRST = 0;        // Hold both FIFOs in reset
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 0;   // Hold RX FIFO in reset

    SpiaRegs.SPICCR.bit.SPICHAR = 15;       // 16 bit char
    SpiaRegs.SPICCR.bit.CLKPOLARITY = 1;    // Output on falling edge
    SpiaRegs.SPICCR.bit.SPILBK = 0;         // No Loopback
    SpiaRegs.SPIBRR = 99;                   // Baud rate select

    SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;   // Master mode
    SpiaRegs.SPICTL.bit.CLK_PHASE = 0;      // No Delay
    SpiaRegs.SPICTL.bit.OVERRUNINTENA = 0;  // Disable
    SpiaRegs.SPICTL.bit.TALK = 1;           // Enable TX
    SpiaRegs.SPICTL.bit.SPIINTENA = 1;      // Enable Interrupt Request
    SpiaRegs.SPIPRI.bit.FREE = 0;           // Set so brkpts don't disturb xmission

    SpiaRegs.SPIFFRX.bit.RXFFIL = 1;        // Set flag after 3 bytes rcv'd
    SpiaRegs.SPIFFRX.bit.RXFFINTCLR = 1;    // Clear any spurious Int Flag
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 1;   // Release RX FIFO from reset
    SpiaRegs.SPIFFTX.bit.SPIRST = 1;        // Release both FIFOs from reset
    SpiaRegs.SPIFFTX.bit.SPIFFENA = 0;      // Disable FIFOs feature
    SpiaRegs.SPICCR.bit.SPISWRESET = 1;     // Release SPI from reset
}
