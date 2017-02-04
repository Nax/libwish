/*
 * src/attr.c
 *
 * This file is a source file from the libwish project.
 * You are free to distribute it as long as you respect the terms
 * and conditions of the MIT license.
 *
 * (c) Maxime Bacoux, 2016 - 2017
 */

#include <stdlib.h>
#include <string.h>
#include <wish.h>

void wish_attr_init(wish_attr* attr)
{
    memset(attr, 0, sizeof(*attr));
}

void wish_color(wish_attr* attr, int color)
{
    if (color >= 0)
    {
        attr->color = (uint8_t)color;
        attr->has_color = 1;
    }
    else
    {
        attr->has_color = 0;
    }
}

void wish_bcolor(wish_attr* attr, int bcolor)
{
    if (bcolor >= 0)
    {
        attr->bcolor = (uint8_t)bcolor;
        attr->has_bcolor = 1;
    }
    else
    {
        attr->has_bcolor = 0;
    }
}

void wish_attr_enable(wish_attr* attr, uint16_t flags)
{
    attr->flags |= flags;
}

void wish_attr_disable(wish_attr* attr, uint16_t flags)
{
    attr->flags &= ~flags;
}

void wish_attr_set(wish_attr* attr, uint16_t flags)
{
    attr->flags = flags;
}
