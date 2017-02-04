/*
 * src/wish_buffer.h
 *
 * This file is a source file from the libwish project.
 * You are free to distribute it as long as you respect the terms
 * and conditions of the MIT license.
 *
 * (c) Maxime Bacoux, 2016 - 2017
 */

#ifndef WISH_BUFFER_H
#define WISH_BUFFER_H

#include <stdlib.h>

struct wish_buffer_s
{
    char*   data;
    size_t  size;
    size_t  capacity;
};

typedef struct wish_buffer_s wish_buffer;

void wish_buffer_init(wish_buffer* buffer);
void wish_buffer_reset(wish_buffer* buffer);
void wish_buffer_free(wish_buffer* buffer);
void wish_buffer_append(wish_buffer* buffer, const char* str, size_t size);
void wish_buffer_append_auto(wish_buffer* buffer, const char* str);

#endif
