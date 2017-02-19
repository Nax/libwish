/*
 * src/wish_frame.h
 *
 * This file is a source file from the libwish project.
 * You are free to distribute it as long as you respect the terms
 * and conditions of the MIT license.
 *
 * (c) Maxime Bacoux, 2016 - 2017
 */

#ifndef WISH_FRAME_H
#define WISH_FRAME_H

#include <wish.h>

struct wish_frame_s
{
    wish_unicode*   ch;
    wish_attr*      attr;
    wish_size       cursor;
};

typedef struct wish_frame_s wish_frame;

void wish_frame_init(wish_frame* frame, int w, int h);
void wish_frame_resize(wish_frame* frame, int w, int h);
void wish_frame_copy(wish_frame* dst, wish_frame* src, int w, int h);
void wish_frame_free(wish_frame* frame);

#endif
