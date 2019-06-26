#include "DSP28x_Project.h"
#include "libs/fsk/fsk_frame.h"
#include "libs/complex/complex.h"
#include "libs/fsk/fsk_table.h"
#include "libs/crc/crc32.h"

#include <string.h>

static inline void scramble_frame(Uint16 *frame, int16 frame_length,
                           const Uint16 *scrambling_sequence)
{
    int16 i;
    for (i = 0; i < frame_length; i++){
        //XOR byte with byte from scrambling sequence
        frame[i] ^= scrambling_sequence[i];
    }
}

#pragma CODE_SECTION(fsk_pack,"ramfuncs");
void fsk_pack(Uint16 *buf,fsk_frame_t *frame)
{
    Uint32 crc32_value;
	buf[0] = 0xA5;
	buf[37] = 0x5A;

	buf[1] = frame->addr;
	buf[2] = frame->type;

	memcpy(&buf[3],frame->data,30);
	scramble_frame(&buf[3],30,scrambleTable);
	crc32_value = crc32(&buf[3],30);

	buf[33] = (crc32_value >> 24) & 0xFF;
	buf[34] = (crc32_value >> 16) & 0xFF;
	buf[35] = (crc32_value >> 8) & 0xFF;
	buf[36] = (crc32_value) & 0xFF;
}
