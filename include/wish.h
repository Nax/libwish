/*
 * include/wish.h
 *
 * This file is a source file from the libwish project.
 * You are free to distribute it as long as you respect the terms
 * and conditions of the MIT license.
 *
 * (c) Maxime Bacoux, 2016 - 2017
 */

#ifndef WISH_H
#define WISH_H

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * C++ needs extern "C"
 */
#if defined(__cplusplus)
# define WISH_DECL_START    extern "C" {
# define WISH_DECL_END      }
#else
# define WISH_DECL_START
# define WISH_DECL_END
#endif

#define WISH_VERSION_MAJOR  0
#define WISH_VERSION_MINOR  1
#define WISH_VERSION_PATCH  2

#define WISH_VERSION_HELPER(x,y,z)  ((x) * 10000 + (y) * 100 + (z))
#define WISH_VERSION                WISH_VERSION_HELPER(WISH_VERSION_MAJOR, WISH_VERSION_MINOR, WISH_VERSION_PATCH)

/*
 * Typedefs
 */

/**
 * An unicode codepoint.
 */
typedef uint32_t    wish_unicode;

#define WISH_CP_NONE    (0xffffffff)

struct wish_size_s
{
    int     x;
    int     y;
};

struct wish_term_s;
struct wish_view_s;

typedef struct wish_size_s  wish_size;
typedef struct wish_view_s  wish_view;
typedef struct wish_term_s  wish_term;

#define WISH_BOLD       (1 << 0)
#define WISH_UNDERLINE  (1 << 1)
#define WISH_INVERSE    (1 << 2)

struct wish_attr_s
{
    uint8_t     color;
    uint8_t     bcolor;
    uint16_t    has_color:1;
    uint16_t    has_bcolor:1;
    uint16_t    flags:14;
};

typedef struct wish_attr_s wish_attr;

WISH_DECL_START

/*
 * attr
 */
void    wish_attr_init(wish_attr* attr);
void    wish_color(wish_attr* attr, int color);
void    wish_bcolor(wish_attr* attr, int bcolor);
void    wish_attr_enable(wish_attr* attr, uint16_t flags);
void    wish_attr_disable(wish_attr* attr, uint16_t flags);
void    wish_attr_set(wish_attr* attr, uint16_t flags);

/*
 * clear
 */
void    wish_clear(wish_term* term);
void    wish_clear_view(wish_view* view);

/*
 * cursor
 */

void    wish_cursor_show(wish_term* term, int visible);
void    wish_cursor_move(wish_view* view, int x, int y);

/*
 * draw
 */
void    wish_draw(wish_term* term);

/*
 * init
 */
wish_term*  wish_init(void);
void        wish_quit(wish_term* term);

/*
 * print
 */
void    wish_move(wish_view* view, int x, int y);
void    wish_putchar(wish_view* view, wish_unicode ch, wish_attr attr);
void    wish_mvputchar(wish_view* view, int x, int y, wish_unicode ch, wish_attr attr);
size_t  wish_puts(wish_view* view, const char* str, wish_attr attr);
size_t  wish_mvputs(wish_view* view, int x, int y, const char* str, wish_attr attr);
size_t  wish_printf(wish_view* view, const char* format, wish_attr attr, ...);
size_t  wish_mvprintf(wish_view* view, int x, int y, const char* format, wish_attr attr, ...);
size_t  wish_vprintf(wish_view* view, const char* format, wish_attr attr, va_list arg);
size_t  wish_mvvprintf(wish_view* view, int x, int y, const char* format, wish_attr attr, va_list arg);

/*
 * read
 */
wish_unicode    wish_getchar(wish_term* term);
void            wish_read_block(wish_term* term, int block);
void            wish_read_delay(wish_term* term, int delay);

/*
 * size
 */
int     wish_resize(wish_term* term);
void    wish_get_size(wish_term* term, wish_size* osize);

/*
 * unicode
 */
size_t  wish_utf8_encode(char* dst, wish_unicode cp);
size_t  wish_utf8_decode(wish_unicode* cp, const char* src);
size_t  wish_utf8_strlen(const char* src);

/*
 * view
 */
wish_view*  wish_view_create(wish_term* term);
void        wish_view_resize(wish_view* view, int x, int y, int w, int h);
void        wish_view_fullscreen(wish_view* view);
void        wish_view_wrap(wish_view* view, int wrap);
void        wish_view_free(wish_view* view);

WISH_DECL_END

#endif
