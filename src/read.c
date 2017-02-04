#include <unistd.h>
#include "wish_term.h"

wish_unicode wish_getchar(wish_term* term)
{
    char            buf[4];
    unsigned char   leader;
    size_t          uni_len;
    size_t          len;
    wish_unicode    cp;

    len = read(0, buf, 1);
    if (len == 0)
        return WISH_CP_NONE;
    leader = (unsigned char)(buf[0]);
    if (leader < 0x80)
        return (wish_unicode)leader;
    else if (leader < 0xe0)
        uni_len = 2;
    else if (leader < 0xf0)
        uni_len = 3;
    else
        uni_len = 4;
    while (len < uni_len)
        len += read(0, buf + len, uni_len - len);
    wish_utf8_decode(&cp, buf);
    return cp;
}

void wish_read_block(wish_term* term, int block)
{
    if (block)
        term->term_attr.c_cc[VMIN] = 1;
    else
        term->term_attr.c_cc[VMIN] = 0;
    tcsetattr(1, TCSAFLUSH, &term->term_attr);
}

void wish_read_delay(wish_term* term, int delay)
{
    term->term_attr.c_cc[VTIME] = delay;
    tcsetattr(1, TCSAFLUSH, &term->term_attr);
}
