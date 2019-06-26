#include "DSP28x_Project.h"
#include "libs/fsk/fsk_frame.h"
#include "libs/complex/complex.h"
#include "libs/fsk/fsk_table.h"
#include "libs/crc/crc32.h"

#include <string.h>

static inline void unscramble_frame(Uint16 *frame, int16 frame_length,
                             const Uint16 *scrambling_sequence)
{
    int16 i;
    for (i = 0; i < frame_length; i++){
        //XOR byte with byte from scrambling sequence
        frame[i] ^= scrambling_sequence[i];
    }
}

#pragma CODE_SECTION(fsk_unpack,"ramfuncs");
int16 fsk_unpack(Uint16 *buf,fsk_frame_t *frame)
{
    Uint32 crc32_value,crc32_received;
	if((buf[0] == 0xA5) && (buf[37] == 0x5A))
	{
	    crc32_received = (Uint32)buf[33] << 24;
	    crc32_received |= (Uint32)buf[34] << 16;
	    crc32_received |= (Uint32)buf[35] << 8;
	    crc32_received |= (Uint32)buf[36];

	    crc32_value = crc32(&buf[3],30);
	    if(crc32_value != crc32_received)
	    {
	        return 0;
	    }

		frame->addr = buf[1];
		frame->type = buf[2];
		unscramble_frame(&buf[3],30,scrambleTable);
		memcpy(frame->data,&buf[3],30);
		return 1;
	}
	else
	{
		return 0;
	}
}
