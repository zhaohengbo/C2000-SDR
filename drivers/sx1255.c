#include "DSP28x_Project.h"
#include "drivers/spi.h"
#include "drivers/mcbsp.h"

#define SX1255_VERSION			0x11

#define SX1255_REG_MODE			0x0
#define SX1255_REG_FRFH_RX		0x1
#define SX1255_REG_FRFM_RX		0x2
#define SX1255_REG_FRFL_RX		0x3
#define SX1255_REG_FRFH_TX		0x4
#define SX1255_REG_FRFM_TX		0x5
#define SX1255_REG_FRFL_TX		0x6
#define SX1255_REG_VERSION		0x7
#define SX1255_REG_TXFE1		0x8
#define SX1255_REG_TXFE2		0x9
#define SX1255_REG_TXFE3		0xA
#define SX1255_REG_TXFE4		0xB
#define SX1255_REG_RXFE1		0xC
#define SX1255_REG_RXFE2		0xD
#define SX1255_REG_RXFE3		0xE
#define SX1255_REG_IO_MAP		0xF
#define SX1255_REG_CK_SEL		0x10
#define SX1255_REG_STAT			0x11
#define SX1255_REG_IISM			0x12
#define SX1255_REG_DIG_BRIDGE	0x13
#define SX1255_REG_XOSC         0x28//This speciall reg was found in libloragw

Uint16 sx1255_spi_read(Uint16 reg_name)
{
    int16 spi_value = 0;
    reg_name &= 0x7F;
    spi_value = reg_name << 8;
    spi_value |= 0xFF;
    return (spia_xmit(spi_value) & 0xFF);
}

void sx1255_spi_write(Uint16 reg_name,Uint16 value)
{
    Uint16 spi_value = 0;
    reg_name &= 0x7F;
    value &= 0xFF;
    spi_value = reg_name << 8;
    spi_value |= (value | 0x8000);
    spia_xmit(spi_value);
}

void sx1255_reset(void)
{
	//reset SX1255
	GpioDataRegs.GPASET.bit.GPIO8 = 1;
	DELAY_US(1000);
	GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;
	DELAY_US(50000);
}

void sx1255_init(void)
{
    Uint16 sx1255_hw_ver;

    spia_init();
    dma_init();
    mcbspa_init();

    sx1255_reset();

    sx1255_hw_ver = sx1255_spi_read(SX1255_REG_VERSION);

    if(sx1255_hw_ver == SX1255_VERSION)
    {
        sx1255_spi_write(SX1255_REG_XOSC,((0x00 << 4) | (0x0D)));

        sx1255_spi_write(SX1255_REG_CK_SEL,0b0010);

    	sx1255_spi_write(SX1255_REG_TXFE1,((0x02 << 4) | (0x0E)));
    	sx1255_spi_write(SX1255_REG_TXFE2,((0x04 << 3) | (0x04)));
    	sx1255_spi_write(SX1255_REG_TXFE3,0x1F);
    	sx1255_spi_write(SX1255_REG_TXFE4,0x0);


    	sx1255_spi_write(SX1255_REG_RXFE1,((0x03 << 5) | (0x0F << 1) | (0x00)));
    	sx1255_spi_write(SX1255_REG_RXFE2,((0x01 << 5) | (0x05 << 2) | (0x01)));
    	sx1255_spi_write(SX1255_REG_RXFE3,0x0);

    	//set up i2s mode
    	sx1255_spi_write(SX1255_REG_IISM,((0x00 << 7) | (0x00 << 6) | (0x02 << 4) | (0x03)));
    	sx1255_spi_write(SX1255_REG_DIG_BRIDGE,((0x00 << 7) | (0x00 << 6) | (0x05 << 3) | (0x01 << 2)));

    	if((sx1255_spi_read(SX1255_REG_DIG_BRIDGE) & 0x2) == 0)
    	{
    	    do{
    	        //sx1255_spi_write(SX1255_REG_MODE,0xF);//enable RX/TX,PA
    	        sx1255_spi_write(SX1255_REG_MODE,0xD);//enable TX,PA
    	        //sx1255_spi_write(SX1255_REG_MODE,0x3);//enable RX
    	        DELAY_US(50000);
    	    } while((sx1255_spi_read(SX1255_REG_STAT) & 0x03) == 0);
    	}
    }
}
