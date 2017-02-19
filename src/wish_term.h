/*
 * src/wish_term.h
 *
 * This file is a source file from the libwish project.
 * You are free to distribute it as long as you respect the terms
 * and conditions of the MIT license.
 *
 * (c) Maxime Bacoux, 2016 - 2017
 */

#ifndef WISH_TERM_H
#define WISH_TERM_H

#include <term.h>
#include <curses.h>
#include <wish.h>
#include "wish_caps.h"
#include "wish_buffer.h"
#include "wish_frame.h"

struct wish_term_s
{
    wish_caps       caps;
    wish_buffer     buffer;
    wish_frame      frame;
    wish_frame      frame_old;
    struct termios  term_attr;
    struct termios  term_attr_backup;
    wish_size       size;
    wish_size       cursor;
    int             display_cursor:1;
    int             display_cursor_old:1;
};

#endif
