#include <unistd.h>
#include "wish_term.h"
#include "wish_buffer.h"

static int wish_cmp_chattr(wish_unicode u1, wish_unicode u2, wish_attr a1, wish_attr a2)
{
    if (u1 != u2)
        return 0;
    if (a1.color != a2.color)
        return 0;
    if (a1.bcolor != a2.bcolor)
        return 0;
    if (a1.has_color != a2.has_color)
        return 0;
    if (a1.has_bcolor != a2.has_bcolor)
        return 0;
    if (a1.flags != a2.flags)
        return 0;
    return 1;
}

void wish_draw(wish_term* term)
{
    wish_unicode    u1, u2;
    wish_attr       a1, a2;
    wish_frame*     frame;
    wish_frame*     frame_old;
    wish_attr       attr = {0};
    int             in_draw;
    int             x;
    int             y;
    size_t          index;
    size_t          max;
    char            tmp[4];
    size_t          tmp_len;
    int             should_reset;

    in_draw = 0;
    wish_buffer_reset(&term->buffer);
    frame = &term->frame;
    frame_old = &term->frame_old;

    wish_buffer_append_auto(&term->buffer, term->caps.sgr0);
    max = term->size.x * term->size.y;

    for (index = 0; index < max; ++index)
    {
        u1 = frame->ch[index];
        u2 = frame_old->ch[index];
        a1 = frame->attr[index];
        a2 = frame_old->attr[index];

        if (wish_cmp_chattr(u1, u2, a1, a2))
        {
            /* Nothing changed, no need to redraw this */
            in_draw = 0;
        }
        else
        {
            /* We need to redraw this part */
            if (!in_draw)
            {
                /* Not a drawing continuation, we must move the cursor */
                in_draw = 1;
                x = index % term->size.x;
                y = index / term->size.x;
                wish_buffer_append_auto(&term->buffer, tparm(term->caps.cup, y, x));
            }

            should_reset = 0;
            /* Bold cannot be unset, so we must special case it */
            if ((attr.flags & WISH_BOLD) && !(a1.flags & WISH_BOLD))
                should_reset = 1;
            else if (attr.has_color && !(a1.has_color))
                should_reset = 1;
            else if (attr.has_bcolor && !(a1.has_bcolor))
                should_reset = 1;
            if (should_reset)
            {
                wish_buffer_append_auto(&term->buffer, term->caps.sgr0);
                attr.flags = 0;
                attr.has_color = 0;
                attr.has_bcolor = 0;
            }

            /* Now that we have reset the style if needed, we need to check for flags to change */
            /* Let's start with color */
            if (a1.has_color && (a1.color != attr.color))
            {
                wish_buffer_append_auto(&term->buffer, tparm(term->caps.setaf, a1.color));
                attr.color = a1.color;
                attr.has_color = 1;
            }
            if (a1.has_bcolor && (a1.bcolor != attr.bcolor))
            {
                wish_buffer_append_auto(&term->buffer, tparm(term->caps.setab, a1.bcolor));
                attr.bcolor = a1.bcolor;
                attr.has_bcolor = 1;
            }
            if ((a1.flags & WISH_BOLD) && !(attr.flags & WISH_BOLD))
            {
                wish_buffer_append_auto(&term->buffer, term->caps.bold);
                attr.flags |= WISH_BOLD;
            }
            if ((a1.flags & WISH_UNDERLINE) && !(attr.flags & WISH_UNDERLINE))
            {
                wish_buffer_append_auto(&term->buffer, term->caps.smul);
                attr.flags |= WISH_UNDERLINE;
            }
            else if (!(a1.flags & WISH_UNDERLINE) && (attr.flags & WISH_UNDERLINE))
            {
                wish_buffer_append_auto(&term->buffer, term->caps.rmul);
                attr.flags &= ~WISH_UNDERLINE;
            }
            if ((a1.flags & WISH_INVERSE) && !(attr.flags & WISH_INVERSE))
            {
                wish_buffer_append_auto(&term->buffer, term->caps.smso);
                attr.flags |= WISH_INVERSE;
            }
            else if (!(a1.flags & WISH_INVERSE) && (attr.flags & WISH_INVERSE))
            {
                wish_buffer_append_auto(&term->buffer, term->caps.rmso);
                attr.flags &= ~WISH_INVERSE;
            }

            /* Here comes the display */
            tmp_len = wish_utf8_encode(tmp, frame->ch[index]);
            wish_buffer_append(&term->buffer, tmp, tmp_len);
        }
    }

    /* Display cursor if needed */
    if (term->display_cursor && !term->display_cursor_old)
    {
        term->display_cursor_old = 1;
        wish_buffer_append_auto(&term->buffer, term->caps.cnorm);
    }
    else if (!term->display_cursor && term->display_cursor_old)
    {
        term->display_cursor_old = 0;
        wish_buffer_append_auto(&term->buffer, term->caps.civis);
    }

    /* Move cursor if needed */
    if (term->display_cursor)
        wish_buffer_append_auto(&term->buffer, tparm(term->caps.cup, term->cursor.y, term->cursor.x));

    write(1, term->buffer.data, term->buffer.size);
    wish_frame_copy(frame_old, frame, term->size.x, term->size.y);
}
