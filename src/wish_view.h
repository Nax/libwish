/*
 * src/wish_view.h
 *
 * This file is a source file from the libwish project.
 * You are free to distribute it as long as you respect the terms
 * and conditions of the MIT license.
 *
 * (c) Maxime Bacoux, 2016 - 2017
 */

#ifndef WISH_VIEW_H
#define WISH_VIEW_H

#include "wish_term.h"

struct wish_view_s
{
    wish_term*  term;
    wish_size   origin;
    wish_size   size;
    wish_size   pen;
    int         wrap:1;
};

#endif
