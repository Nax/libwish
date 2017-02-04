#include "wish_view.h"

void wish_apply_wrap(wish_view* view);

wish_view* wish_view_create(wish_term* term)
{
    wish_view* view;

    view = calloc(1, sizeof(*view));
    view->term = term;
    return view;
}

void wish_view_resize(wish_view* view, int x, int y, int w, int h)
{
    if (x < 0)
        view->origin.x = 0;
    else
        view->origin.x = x;
    if (y < 0)
        view->origin.y = 0;
    else
        view->origin.y = y;
    if (w < 0)
        view->size.x = 0;
    else
        view->size.x = w;
    if (h < 0)
        view->size.y = 0;
    else
        view->size.y = h;
    view->pen.x = 0;
    view->pen.y = 0;
}

void wish_view_fullscreen(wish_view* view)
{
    wish_term* t;

    t = view->term;
    wish_view_resize(view, 0, 0, t->size.x, t->size.y);
}

void wish_view_wrap(wish_view* view, int wrap)
{
    if (wrap)
        view->wrap = 1;
    else
        view->wrap = 0;
    wish_apply_wrap(view);
}

void wish_view_free(wish_view* view)
{
    free(view);
}
