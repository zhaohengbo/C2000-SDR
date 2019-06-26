#ifndef LIBS_FSK_FSK_DECODE_H_
#define LIBS_FSK_FSK_DECODE_H_

#ifdef __cplusplus
extern "C" {
#endif

int16 fsk_decode(int16 *buf_in, Uint16 *buf_out, Uint16 bufSize, int16 first, Uint16 *position);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* LIBS_FSK_FSK_DECODE_H_ */
