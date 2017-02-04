#include "wish_view.h"

void wish_cursor_show(wish_term* term, int visible)
{
    if (visible)
        term->display_cursor = 1;
    else
        term->display_cursor = 0;
}

void wish_cursor_move(wish_view* view, int x, int y)
{
    if (view->wrap && x > view->size.x)
    {
        y += x / view->size.x;
        x %= view->size.x;
    }
    x += view->origin.x;
    y += view->origin.y;
    view->term->cursor.x = x;
    view->term->cursor.y = y;
}
