#include "DSP28x_Project.h"
#include "drivers/sx1255_tx.h"
#include "drivers/sx1255_rx.h"

void mcbspa_init(void)
{
	Uint16 i;
    EALLOW;
    McbspaRegs.SPCR2.all=0x0000;		// Reset FS generator, sample rate generator & transmitter
	McbspaRegs.SPCR1.all=0x0000;		// Reset Receiver, Right justify word

    McbspaRegs.SPCR1.bit.RJUST = 2;		// left-justify word in DRR and zero-fill LSBs

 	McbspaRegs.MFFINT.all=0x0;			// Disable all interrupts

    McbspaRegs.SPCR1.bit.RINTM = 0;		// Configure McBSP interrupts
	McbspaRegs.SPCR2.bit.XINTM = 0;

    McbspaRegs.RCR2.all=0x0;			// Single-phase frame, 1 word/frame, No companding	(Receive)
    McbspaRegs.RCR1.all=0x0;

    McbspaRegs.XCR2.all=0x0;			// Single-phase frame, 1 word/frame, No companding	(Transmit)
    McbspaRegs.XCR1.all=0x0;

    McbspaRegs.RCR2.bit.RWDLEN2 = 2;	// 32-BIT OPERATION
    McbspaRegs.RCR1.bit.RWDLEN1 = 2;
    McbspaRegs.XCR2.bit.XWDLEN2 = 2;
    McbspaRegs.XCR1.bit.XWDLEN1 = 2;

    McbspaRegs.RCR2.bit.RPHASE = 1;		// Dual-phase frame
	McbspaRegs.RCR2.bit.RFRLEN2 = 0;	// Recv frame length = 1 word in phase2
	McbspaRegs.RCR1.bit.RFRLEN1 = 0;	// Recv frame length = 1 word in phase1

	McbspaRegs.XCR2.bit.XPHASE = 1;		// Dual-phase frame
	McbspaRegs.XCR2.bit.XFRLEN2 = 0;	// Xmit frame length = 1 word in phase2
	McbspaRegs.XCR1.bit.XFRLEN1 = 0;	// Xmit frame length = 1 word in phase1

	McbspaRegs.RCR2.bit.RDATDLY = 1;	// n = n-bit data delay (max 2) CRITICAL PARAMETER !!!
	McbspaRegs.XCR2.bit.XDATDLY = 1;    // If LRP (AIC23) = 0, X/RDATDLY=0, if LRP=1, X/RDATDLY=1

    McbspaRegs.SRGR2.bit.FPER = 0x0002;	// Does not matter
    McbspaRegs.SRGR1.all=0x0001;		// Frame Width = 1 CLKG period, CLKGDV must be 1 as slave!!
                                        // SRG clocked by LSPCLK - SRG clock MUST be at least 2x external data shift clk

    McbspaRegs.PCR.all=0x0000;			// Frame sync generated externally, CLKX/CLKR driven
    McbspaRegs.PCR.bit.FSXM = 0;		// FSX is always an i/p signal
	McbspaRegs.PCR.bit.FSRM = 0;		// FSR is always an i/p signal
	McbspaRegs.PCR.bit.SCLKME = 0;

	McbspaRegs.PCR.bit.FSRP = 1;		// 1-FSRP is active low (L-channel first)
	McbspaRegs.PCR.bit.FSXP = 1 ;       // 1-FSXP is active low (L-channel first)
    McbspaRegs.PCR.bit.CLKRP  = 0;		// 1-Rcvd data sampled on rising edge of CLKR
	McbspaRegs.PCR.bit.CLKXP  = 1;      // 0- Tx data sampled on falling edge of CLKX
	McbspaRegs.SRGR2.bit.CLKSM = 1;		// LSPCLK is clock source for SRG

	McbspaRegs.PCR.bit.CLKXM = 0;		// 0-MCLKXA is an i/p driven by an external clock
    McbspaRegs.PCR.bit.CLKRM = 0;		// MCLKRA is an i/p signal

    McbspaRegs.SPCR2.all |=0x00C0;     	// Frame sync & sample rate generators pulled out of reset

    for (i = 0;i < 100;i++)	{}			//delay in McBsp init. must be at least 2 SRG cycles

	McbspaRegs.SPCR2.bit.XRST=1;       	// Enable Transmitter
    McbspaRegs.SPCR1.bit.RRST=1;		// Enable Receiver

    EDIS;

	for (i = 0;i < 100;i++)	{}			//delay in McBsp init. must be at least 2 SRG cycles
}

void dma_init(void)
{
	EALLOW;
	DmaRegs.DMACTRL.bit.HARDRESET = 1;
	asm("     NOP");

	DmaRegs.PRIORITYCTRL1.bit.CH1PRIORITY = 0;
	/* DMA Channel 1 - McBSP-A Receive */
	DmaRegs.CH1.BURST_SIZE.all = 0;	// 2 16-bit words/burst (1 32-bit word per RRDY) - memory address bumped up by 1 internally
	DmaRegs.CH1.SRC_BURST_STEP = 0;	// DRR2 must be read first & then DRR1. Increment by 1. Hence a value of +1. (This is a 2's C #)
	DmaRegs.CH1.DST_BURST_STEP = 0;	// Copy DRR2 data to address N+1 and DRR1 data to N. Hence -1 (32-bit read= read addr N+1 as MSB, then N as LSB)
	DmaRegs.CH1.TRANSFER_SIZE = 511;	// Interrupt every 1024 (n+1) bursts. McBSP handles 16-bit data only (DRR2 and DRR1 are 16-bit registers)

	DmaRegs.CH1.SRC_TRANSFER_STEP = 0; // Decrement source address by 1 (from DRR1 back to DRR2) after processing a burst of data
	DmaRegs.CH1.DST_TRANSFER_STEP = 1; // After copying L-C data, move down to R-C data in a given buffer

	DmaRegs.CH1.SRC_ADDR_SHADOW = (Uint32) &McbspaRegs.DRR1.all;  // First read from DRR2
	DmaRegs.CH1.SRC_BEG_ADDR_SHADOW = (Uint32) &McbspaRegs.DRR1.all;

	DmaRegs.CH1.DST_WRAP_SIZE = 0xFFFF;	  // After LEFT(1) and then RIGHT(2), go back to LEFT buffer
	DmaRegs.CH1.SRC_WRAP_SIZE = 0xFFFF; // Arbitary large value. We'll never hit this.....

	DmaRegs.CH1.CONTROL.bit.PERINTCLR = 1;		// Clears peripheral interrupt, sync and sycn error flags
	DmaRegs.CH1.CONTROL.bit.SYNCCLR = 1;
	DmaRegs.CH1.CONTROL.bit.ERRCLR = 1;

	DmaRegs.CH1.MODE.bit.CHINTE = 1;			// Channel Interrupt Enable
	DmaRegs.CH1.MODE.bit.CHINTMODE = 1;			// Generates Interrupt at beginning of transfer
	DmaRegs.CH1.MODE.bit.PERINTE = 1;			// Peripheral Interrupt Enable
	DmaRegs.CH1.MODE.bit.PERINTSEL = 15;		// McBSP MREVTA
	DmaRegs.CH1.MODE.bit.CONTINUOUS = 1;		// Continuous mode

	/* DMA Channel 2 - McBSP-A Transmit */
	DmaRegs.CH2.BURST_SIZE.all = 0;	// 2 16-bit words/burst (1 32-bit word per XRDY) - value bumped up by 1 internally
	DmaRegs.CH2.SRC_BURST_STEP = 0;	// Copy data at address N+1 to DXR2 first then data at N to DXR1. Hence -1
	DmaRegs.CH2.DST_BURST_STEP = 0;	// DXR2 must be written to first & then DXR1. Increment by 1. Hence a value of +1. (This is a 2's C #)
	DmaRegs.CH2.TRANSFER_SIZE = 511;	// Interrupt every 1024 (n+1) 16-bit words. McBSP still handles 16-bit data only in registers

	DmaRegs.CH2.SRC_TRANSFER_STEP = 1; // After copying L-C data, move down to R-C data in a given buffer
	DmaRegs.CH2.DST_TRANSFER_STEP = 0;   // Decrement dest. address by 1 (DXR1 back to DXR2) after processing a burst of data

	DmaRegs.CH2.DST_ADDR_SHADOW = (Uint32) &McbspaRegs.DXR1.all;  // First write to DXR2
	DmaRegs.CH2.DST_BEG_ADDR_SHADOW = (Uint32) &McbspaRegs.DXR1.all;

	DmaRegs.CH2.SRC_WRAP_SIZE = 0xFFFF;	     // After LEFT(1) and then RIGHT(2), go back to LEFT buffer
	DmaRegs.CH2.DST_WRAP_SIZE = 0xFFFF;  	 // Arbitary large value. We'll never hit this.....

	DmaRegs.CH2.CONTROL.bit.PERINTCLR = 1;		// Clears peripheral interrupt, sync and sync error flags
	DmaRegs.CH2.CONTROL.bit.SYNCCLR = 1;
	DmaRegs.CH2.CONTROL.bit.ERRCLR = 1;

	DmaRegs.CH2.MODE.bit.CHINTE = 1;			// Channel Interrupt Enable
	DmaRegs.CH2.MODE.bit.CHINTMODE = 1;			// Generates Interrupt at beginning of transfer
	DmaRegs.CH2.MODE.bit.PERINTE = 1;			// Peripheral Interrupt Enable
	DmaRegs.CH2.MODE.bit.PERINTSEL = 14;		// McBSP MXEVTA
	DmaRegs.CH2.MODE.bit.CONTINUOUS = 1;		// Continuous mode
	EDIS;

	sx1255_tx_reset_state();
	sx1255_rx_reset_state();

	EALLOW;
	PieVectTable.DINTCH1 = &SX1255_RX_DMA_ISR;
	PieVectTable.DINTCH2 = &SX1255_TX_DMA_ISR;

	PieCtrlRegs.PIEIER7.bit.INTx1 = 1;	// Enable INTx.1 of INT7 (DMA CH1)
	PieCtrlRegs.PIEIER7.bit.INTx2 = 1;  // Enable INTx.2 of INT7 (DMA CH2)

	DmaRegs.CH1.CONTROL.bit.RUN = 1; // Start rx on Channel 1
	DmaRegs.CH2.CONTROL.bit.RUN = 1; // Start rx on Channel 1
	EDIS;

	IER |= 0x0040;					    // Enable  INT7
}
