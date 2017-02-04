#ifndef WISH_CAPS_H
#define WISH_CAPS_H

/*
 * This file was automatically generated.
 * DO NOT EDIT.
 */

struct wish_caps_s
{
    char* smcup;
    char* rmcup;
    char* clear;
    char* setaf;
    char* setab;
    char* cup;
    char* bold;
    char* smul;
    char* rmul;
    char* smso;
    char* rmso;
    char* sgr0;
    char* civis;
    char* cnorm;
};
typedef struct wish_caps_s wish_caps;

void wish_init_caps(wish_caps* caps);
void wish_free_caps(wish_caps* caps);

#endif
