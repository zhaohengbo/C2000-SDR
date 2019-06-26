#include "DSP28x_Project.h"
#include "libs/safepipe/safepipe.h"

/*
    Although we call this safepipe, it is not safe at all!!!
    Callers must obey the rules, otherwise bad things will happen!!!
    For readers, safepipe_readable----->safepipe_read_update----->safepipe_get_current_read_buf
    For writers, safepipe_writeable----->safepipe_get_current_write_buf----->safepipe_write_update
    For writers(int), safepipe_writeable----->safepipe_write_update----->safepipe_get_current_write_buf
*/

void safepipe_init(safepipe_t *pipe_p,int size,void **buf_p)
{
    //check the size, at least 4 as one for write guard, one for read guard, two for use
    if(size < 4)
    {
        return;
    }
    pipe_p->size = size;
    pipe_p->read_count = 0;
    pipe_p->write_count = 1;
    pipe_p->buf_p = buf_p;
}

Uint16 safepipe_writeable(safepipe_t *pipe_p)
{
    Uint16 new_write_count;
    new_write_count = (pipe_p->write_count + 1) % pipe_p->size;

    if(new_write_count != pipe_p->read_count)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void safepipe_write_update(safepipe_t *pipe_p)
{
    Uint16 new_write_count;
    new_write_count = (pipe_p->write_count + 1) % pipe_p->size;
    pipe_p->write_count = new_write_count;
}

void *safepipe_get_current_write_buf(safepipe_t *pipe_p)
{
    return pipe_p->buf_p[pipe_p->write_count];
}

Uint16 safepipe_readable(safepipe_t *pipe_p)
{
    Uint16 new_read_count;
    new_read_count = (pipe_p->read_count + 1) % pipe_p->size;

    if(new_read_count != pipe_p->write_count)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void safepipe_read_update(safepipe_t *pipe_p)
{
    Uint16 new_read_count;
    new_read_count = (pipe_p->read_count + 1) % pipe_p->size;
    pipe_p->read_count = new_read_count;
}

void *safepipe_get_current_read_buf(safepipe_t *pipe_p)
{
    return pipe_p->buf_p[pipe_p->read_count];
}
