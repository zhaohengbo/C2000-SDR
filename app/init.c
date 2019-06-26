#include "DSP28x_Project.h"
#include "drivers/sx1255.h"

void Gpio_init(void)
{
    EALLOW;
// GPIO (GENERAL PURPOSE I/O) CONFIG
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// QUICK NOTES on GPIO CONFIG USAGE:
//----------------------------------
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 1, 2 or 3 (i.e. Non GPIO func), then leave
//  rest of lines commented
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 0 (i.e. GPIO func), then:
//    1) uncomment GpioCtrlRegs.GP?DIR.bit.GPIO? = ? and choose pin to be IN or OUT direc.
//    2) If IN, can leave next two lines commented
//    3) If OUT, uncomment line with ..GPACLEAR.. to force pin LOW or
//               uncomment line with ..GPASET.. to force pin HIGH
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//  GPIO-08 - PIN FUNCTION = --Spare--
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;     // 0=GPIO,  1=EPWM5A,  2=CANTX-B,  3=ADCSOC-A
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;      // 1=OUTput,  0=INput
//  GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;    // uncomment if --> Set Low initially
//  GpioDataRegs.GPASET.bit.GPIO8 = 1;      // uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-16 - PIN FUNCTION = --Spare--
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // 0=GPIO,  1=SPISIMO-A,  2=CANTX-B,  3=TZ5
//  GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;     // 1=OUTput,  0=INput
//  GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;   // uncomment if --> Set Low initially
//  GpioDataRegs.GPASET.bit.GPIO16 = 1;     // uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-17 - PIN FUNCTION = --Spare--
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // 0=GPIO,  1=SPISOMI-A,  2=CANRX-B,  3=TZ6
//  GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;     // 1=OUTput,  0=INput
//  GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;   // uncomment if --> Set Low initially
//  GpioDataRegs.GPASET.bit.GPIO17 = 1;     // uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-18 - PIN FUNCTION = --Spare--
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // 0=GPIO,  1=SPICLK-A,  2=SCITX-B,  3=CANRX-A
//  GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;     // 1=OUTput,  0=INput
//  GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;   // uncomment if --> Set Low initially
//  GpioDataRegs.GPASET.bit.GPIO18 = 1;     // uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-19 - PIN FUNCTION = --Spare--
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // 0=GPIO,  1=SPISTE-A,  2=SCIRX-B,  3=CANTX-A
//  GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;     // 1=OUTput,  0=INput
//  GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;   // uncomment if --> Set Low initially
//  GpioDataRegs.GPASET.bit.GPIO19 = 1;     // uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-20 - PIN FUNCTION = --Spare--
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 2; // 0=GPIO,  1=EQEPA-1,  2=MDX-A,  3=CANTX-B
//  GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;     // 1=OUTput,  0=INput
//  GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;   // uncomment if --> Set Low initially
//  GpioDataRegs.GPASET.bit.GPIO20 = 1;     // uncomment if --> Set High initially
    GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 3;   // Asynch only
//--------------------------------------------------------------------------------------
//  GPIO-21 - PIN FUNCTION = --Spare--
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 2; // 0=GPIO,  1=EQEPB-1,  2=MDR-A,  3=CANRX-B
//  GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;     // 1=OUTput,  0=INput
//  GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;   // uncomment if --> Set Low initially
//  GpioDataRegs.GPASET.bit.GPIO21 = 1;     // uncomment if --> Set High initially
    GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 3;   // Asynch only
//--------------------------------------------------------------------------------------
//  GPIO-22 - PIN FUNCTION = --Spare--
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 2; // 0=GPIO,  1=EQEPS-1,  2=MCLKX-A,  3=SCITX-B
//  GpioCtrlRegs.GPADIR.bit.GPIO22 = 0;     // 1=OUTput,  0=INput
//  GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;   // uncomment if --> Set Low initially
//  GpioDataRegs.GPASET.bit.GPIO22 = 1;     // uncomment if --> Set High initially
    GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 3;   // Asynch only
//--------------------------------------------------------------------------------------
//  GPIO-23 - PIN FUNCTION = --Spare--
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 2; // 0=GPIO,  1=EQEPI-1,  2=MFSX-A,  3=SCIRX-B
//  GpioCtrlRegs.GPADIR.bit.GPIO23 = 0;     // 1=OUTput,  0=INput
//  GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;   // uncomment if --> Set Low initially
//  GpioDataRegs.GPASET.bit.GPIO23 = 1;     // uncomment if --> Set High initially
    GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;   // Asynch only
//--------------------------------------------------------------------------------------
//  GPIO-28 - PIN FUNCTION = SCIRX-A
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1; // 0=GPIO,  1=SCIRX-A,  2=Resv,  3=Resv
//  GpioCtrlRegs.GPADIR.bit.GPIO28 = 0;     // 1=OUTput,  0=INput
//  GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;   // uncomment if --> Set Low initially
//  GpioDataRegs.GPASET.bit.GPIO28 = 1;     // uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-29 - PIN FUNCTION = SCITX-A
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1; // 0=GPIO,  1=SCITXD-A,  2=XA19,  3=Resv
//  GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;     // 1=OUTput,  0=INput
//  GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;   // uncomment if --> Set Low initially
//  GpioDataRegs.GPASET.bit.GPIO29 = 1;     // uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-30 - PIN FUNCTION = --Spare--
    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1; // 0=GPIO,  1=CANRX-A,  2=XA18,  3=Resv
//  GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;     // 1=OUTput,  0=INput
//  GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;   // uncomment if --> Set Low initially
//  GpioDataRegs.GPASET.bit.GPIO30 = 1;     // uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-31 - PIN FUNCTION = LED2 (for Release 1 and up F2833x controlCARDs)
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1; // 0=GPIO,  1=CANTX-A,  2=XA17,  3=Resv
//  GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;     // 1=OUTput,  0=INput
//  GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;   // uncomment if --> Set Low initially
//  GpioDataRegs.GPASET.bit.GPIO31 = 1;     // uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-58 - PIN FUNCTION = --Spare--
    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 1; // 0=GPIO,  1=MCLKR-A,  2=XD21,  3=Resv
//  GpioCtrlRegs.GPBDIR.bit.GPIO58 = 0;     // 1=OUTput,  0=INput
//  GpioDataRegs.GPBCLEAR.bit.GPIO58 = 1;   // uncomment if --> Set Low initially
//  GpioDataRegs.GPBSET.bit.GPIO58 = 1;     // uncomment if --> Set High initially
    GpioCtrlRegs.GPBQSEL2.bit.GPIO58 = 3;   // Asynch only
//--------------------------------------------------------------------------------------
//  GPIO-59 - PIN FUNCTION = --Spare--
    GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 1;  // 0=GPIO,  1=MFSR-A,  2=XD20,  3=Resv
//  GpioCtrlRegs.GPBDIR.bit.GPIO59 = 0;     // 1=OUTput,  0=INput
//  GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1;   // uncomment if --> Set Low initially
//  GpioDataRegs.GPBSET.bit.GPIO59 = 1;     // uncomment if --> Set High initially
    GpioCtrlRegs.GPBQSEL2.bit.GPIO59 = 3;   // Asynch only
//--------------------------------------------------------------------------------------

    EDIS;
}

void DeviceInit(void)
{
    InitSysCtrl();

    DINT;
    // Global Disable all Interrupts
    IER = 0x0000;   // Disable CPU interrupts
    IFR = 0x0000;   // Clear all CPU interrupt flags

    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

    InitPieCtrl();

    InitPieVectTable();

    Gpio_init();

    sx1255_init();

    EINT;
    ERTM;
}
