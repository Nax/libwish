#include <string.h>
#include "wish_view.h"

void wish_clear(wish_term* term)
{
    wish_frame* frame;

    frame = &term->frame;
    memset(frame->ch, ' ', term->size.x * term->size.y * sizeof(*frame->ch));
    memset(frame->attr, 0, term->size.x * term->size.y * sizeof(*frame->attr));
}

void wish_clear_view(wish_view* view)
{
    int offset;
    int len;
    int y;
    int yoff;
    int w;
    size_t index;
    wish_frame* frame;

    offset = view->origin.x;
    len = view->size.x;
    if (offset + len >= view->term->size.x)
        len -= (view->term->size.x - (offset + len));
    if (len <= 0)
        return;
    y = 0;
    frame = &view->term->frame;
    w = view->term->size.x;
    for (;;)
    {
        if (y >= view->size.y)
            return;
        yoff = y + view->origin.y;
        if (yoff >= view->term->size.y)
            return;
        index = w * yoff + offset;
        memset(frame->ch + index, ' ', len * sizeof(*frame->ch));
        memset(frame->attr + index, 0, len * sizeof(*frame->attr));
        y++;
    }
}
