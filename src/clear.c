#include <string.h>
#include "wish_view.h"

void wish_clear(wish_term* term)
{
    wish_frame* frame;
    wish_attr attr;

    wish_attr_init(&attr);
    frame = &term->frame;
    for (size_t i = 0; i < term->size.x * term->size.y; ++i)
    {
        frame->ch[i] = ' ';
        frame->attr[i] = attr;
    }
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
