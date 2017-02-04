#include <string.h>
#include "wish_buffer.h"

#define BUFFER_CAPACITY 4096

void wish_buffer_init(wish_buffer* buffer)
{
    buffer->data = malloc(BUFFER_CAPACITY);
    buffer->size = 0;
    buffer->capacity = BUFFER_CAPACITY;
}

void wish_buffer_reset(wish_buffer* buffer)
{
    buffer->size = 0;
}

void wish_buffer_free(wish_buffer* buffer)
{
    free(buffer->data);
}

void wish_buffer_append(wish_buffer* buffer, const char* str, size_t size)
{
    while (buffer->size + size > buffer->capacity)
    {
        buffer->capacity *= 2;
        buffer->data = realloc(buffer->data, buffer->capacity);
    }
    memcpy(buffer->data + buffer->size, str, size);
    buffer->size += size;
}

void wish_buffer_append_auto(wish_buffer* buffer, const char* str)
{
    wish_buffer_append(buffer, str, strlen(str));
}
