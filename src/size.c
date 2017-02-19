#include <sys/ioctl.h>
#include "wish_view.h"

int wish_resize(wish_term* term)
{
    struct winsize ws;

    ioctl(1, TIOCGWINSZ, &ws);
    if (term->size.x != ws.ws_col || term->size.y != ws.ws_row)
    {
        term->size.x = ws.ws_col;
        term->size.y = ws.ws_row;
        wish_frame_resize(&term->frame, term->size.x, term->size.y);
        wish_frame_resize(&term->frame_old, term->size.x, term->size.y);
        return 1;
    }
    return 0;
}

void wish_get_size(wish_term* term, wish_size* osize)
{
    *osize = term->size;
}

void wish_get_view_size(wish_view* view, wish_size* size)
{
    *size = view->size;
}
