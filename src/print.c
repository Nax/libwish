#include "wish_view.h"

void wish_apply_wrap(wish_view* view)
{
    if (view->wrap && view->pen.x >= view->size.x && view->size.x > 0)
    {
        view->pen.y += view->pen.x / view->size.x;
        view->pen.x %= view->size.x;
    }
}

void wish_move(wish_view* view, int x, int y)
{
    if (x < 0)
        view->pen.x = 0;
    else
        view->pen.x = x;
    if (y < 0)
        view->pen.y = 0;
    else
        view->pen.y = y;
    wish_apply_wrap(view);
}

void wish_putchar(wish_view* view, wish_unicode ch, wish_attr attr)
{
    wish_frame* frame;
    int x;
    int y;
    size_t index;

    x = view->pen.x;
    y = view->pen.y;

    if (ch == '\n')
    {
        view->pen.x = 0;
        view->pen.y++;
    }
    else
    {
        if (x < view->size.x && y < view->size.y)
        {
            x += view->origin.x;
            y += view->origin.y;
            if (x < view->term->size.x && y < view->term->size.y)
            {
                index = y * view->term->size.x + x;
                frame = &view->term->frames[view->term->active_frame];
                frame->ch[index] = ch;
                frame->attr[index] = attr;
            }
        }
        view->pen.x++;
        wish_apply_wrap(view);
    }
}

void wish_mvputchar(wish_view* view, int x, int y, wish_unicode ch, wish_attr attr)
{
    wish_move(view, x, y);
    wish_putchar(view, ch, attr);
}

size_t wish_puts(wish_view* view, const char* str, wish_attr attr)
{
    size_t i;
    size_t len;
    size_t ret;
    wish_unicode cp;

    len = 0;
    i = 0;
    for (;;)
    {
        ret = wish_utf8_decode(&cp, str + i);
        if (cp == 0)
            break;
        i += ret;
        wish_putchar(view, cp, attr);
        len++;
    }
    return len;
}

size_t wish_mvputs(wish_view* view, int x, int y, const char* str, wish_attr attr)
{
    wish_move(view, x, y);
    return wish_puts(view, str, attr);
}

size_t wish_printf(wish_view* view, const char* format, wish_attr attr, ...)
{
    va_list ap;
    size_t size;

    va_start(ap, attr);
    size = wish_vprintf(view, format, attr, ap);
    va_end(ap);
    return size;
}

size_t wish_mvprintf(wish_view* view, int x, int y, const char* format, wish_attr attr, ...)
{
    va_list ap;
    size_t size;

    va_start(ap, attr);
    size = wish_mvvprintf(view, x, y, format, attr, ap);
    va_end(ap);
    return size;
}

size_t wish_vprintf(wish_view* view, const char* format, wish_attr attr, va_list arg)
{
    size_t size;
    char buffer[4096];

    buffer[4095] = 0;
    size = vsnprintf(buffer, 4096, format, arg);
    wish_puts(view, buffer, attr);
    return size;
}

size_t wish_mvvprintf(wish_view* view, int x, int y, const char* format, wish_attr attr, va_list arg)
{
    wish_move(view, x, y);
    return wish_vprintf(view, format, attr, arg);
}
