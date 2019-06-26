#ifndef LIBS_FSK_FSK_DC_H_
#define LIBS_FSK_FSK_DC_H_

#ifdef __cplusplus
extern "C" {
#endif

void fsk_iq_dc(short_complex_t *buf, Uint16 bufSize, int16 hold);
void fsk_ang_dc(int16 *buf, Uint16 bufSize, int16 hold);
void fsk_dac_dc(short_complex_t *buf, Uint16 bufSize);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* LIBS_FSK_FSK_DC_H_ */
