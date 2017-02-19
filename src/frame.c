#include <string.h>
#include <stdlib.h>
#include "wish_frame.h"

void wish_frame_init(wish_frame* frame, int w, int h)
{
    frame->ch = NULL;
    frame->attr = NULL;
    frame->cursor.x = 0;
    frame->cursor.y = 0;
    wish_frame_resize(frame, w, h);
}

void wish_frame_resize(wish_frame* frame, int w, int h)
{
    size_t count;
    size_t count_ch;
    size_t count_attr;

    count = w * h;
    count_ch = count * sizeof(*frame->ch);
    count_attr = count * sizeof(*frame->attr);
    frame->ch = realloc(frame->ch, count_ch);
    frame->attr = realloc(frame->attr, count_attr);
    memset(frame->ch, ' ', count_ch);
    memset(frame->attr, 0, count_attr);
}

void wish_frame_copy(wish_frame* dst, wish_frame* src, int w, int h)
{
    size_t count;

    count = w * h;
    memcpy(dst->ch, src->ch, count * sizeof(*dst->ch));
    memcpy(dst->attr, src->attr, count * sizeof(*dst->attr));
}

void wish_frame_free(wish_frame* frame)
{
    free(frame->ch);
    free(frame->attr);
}
