#ifndef LIBS_FSK_FSK_DEMOD_H_
#define LIBS_FSK_FSK_DEMOD_H_

#ifdef __cplusplus
extern "C" {
#endif

extern safepipe_t fsk_demod_pipe;
void fsk_demod_init(void);
void fsk_demod_loop(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* LIBS_FSK_FSK_DEMOD_H_ */
