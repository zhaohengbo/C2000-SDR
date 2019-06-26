#ifndef LIBS_FSK_FSK_FRAME_H_
#define LIBS_FSK_FSK_FRAME_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef  struct
{
	int16 type;
	int16 addr;
	int16 data[30];
}fsk_frame_t;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* LIBS_FSK_FSK_FRAME_H_ */
