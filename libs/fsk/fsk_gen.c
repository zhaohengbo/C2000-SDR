#include "DSP28x_Project.h"
#include "libs/complex/complex.h"
#include "libs/fsk/fsk_table.h"

#include <string.h>
#include <stdlib.h>

#define N_POINT             16

#define MARKFREQ            1
#define SPACEFREQ          -1

int32 GAIN_SPACE = 1;  // SPACE Gain
int32 GAIN_MARK = 1;   // MARK Gain

Uint16 phasePosition = 0;

#pragma CODE_SECTION(fsk_gen,"ramfuncs");
void fsk_gen(short_complex_t *buf,int16 txBit, Uint16 bufSize)
{
    int32 dacGain;
    int16 phaseStep;
    int16 x;
    switch (txBit)
    {
        case SPACEFREQ:
            dacGain = GAIN_SPACE;
            phaseStep = 1;
            break;
        case MARKFREQ:
            dacGain = GAIN_MARK;
            phaseStep = -1;
            break;
        default:
            dacGain = 0;
            phaseStep = 0;
            break;
    }

    for(x=0;x<bufSize;x++)
    {
        buf[x].I = dacGain * sampleTable[phasePosition].I;
        buf[x].Q = dacGain * sampleTable[phasePosition].Q;

        // Calculate next step
        phasePosition += phaseStep;
        phasePosition &= (N_POINT - 1);
    }
}
