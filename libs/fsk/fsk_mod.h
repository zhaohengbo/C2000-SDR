#ifndef LIBS_FSK_FSK_MOD_H_
#define LIBS_FSK_FSK_MOD_H_

#ifdef __cplusplus
extern "C" {
#endif

extern safepipe_t fsk_mod_pipe;
void fsk_mod_init(void);
void fsk_mod_loop(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* LIBS_FSK_FSK_MOD_H_ */
