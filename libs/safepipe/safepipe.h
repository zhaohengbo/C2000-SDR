#ifndef LIBS_SAFEPIPE_SAFEPIPE_H_
#define LIBS_SAFEPIPE_SAFEPIPE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef  struct
{
  Uint16 read_count;
  Uint16 write_count;
  Uint16 size;
  void **buf_p;
}safepipe_t;

void safepipe_init(safepipe_t *pipe_p,int size,void **buf_p);

/*
    Although we call this safepipe, it is not safe at all!!!
    Callers must obey the rules, otherwise bad things will happen!!!
    For readers, safepipe_readable----->safepipe_read_update----->safepipe_get_current_read_buf
    For writers, safepipe_writeable----->safepipe_get_current_write_buf----->safepipe_write_update
    For writers(int), safepipe_writeable----->safepipe_write_update----->safepipe_get_current_write_buf
*/

Uint16 safepipe_writeable(safepipe_t *pipe_p);
void safepipe_write_update(safepipe_t *pipe_p);
void *safepipe_get_current_write_buf(safepipe_t *pipe_p);

Uint16 safepipe_readable(safepipe_t *pipe_p);
void safepipe_read_update(safepipe_t *pipe_p);
void *safepipe_get_current_read_buf(safepipe_t *pipe_p);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* LIBS_SAFEPIPE_SAFEPIPE_H_ */
