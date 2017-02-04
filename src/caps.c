#include <stdlib.h>
#include <string.h>
#include "wish_caps.h"
#include "wish_term.h"

/*
 * This file was automatically generated.
 * DO NOT EDIT.
 */

void wish_init_caps(wish_caps* caps)
{
    char*  tmp;
    size_t size;
    tmp = tigetstr("smcup");
    if (tmp != (char*)0 && tmp != (char*)-1)
    {
        size = strlen(tmp);
        caps->smcup = malloc(size + 1);
        strcpy(caps->smcup, tmp);
    }
    else
        caps->smcup = NULL;
    tmp = tigetstr("rmcup");
    if (tmp != (char*)0 && tmp != (char*)-1)
    {
        size = strlen(tmp);
        caps->rmcup = malloc(size + 1);
        strcpy(caps->rmcup, tmp);
    }
    else
        caps->rmcup = NULL;
    tmp = tigetstr("clear");
    if (tmp != (char*)0 && tmp != (char*)-1)
    {
        size = strlen(tmp);
        caps->clear = malloc(size + 1);
        strcpy(caps->clear, tmp);
    }
    else
        caps->clear = NULL;
    tmp = tigetstr("setaf");
    if (tmp != (char*)0 && tmp != (char*)-1)
    {
        size = strlen(tmp);
        caps->setaf = malloc(size + 1);
        strcpy(caps->setaf, tmp);
    }
    else
        caps->setaf = NULL;
    tmp = tigetstr("setab");
    if (tmp != (char*)0 && tmp != (char*)-1)
    {
        size = strlen(tmp);
        caps->setab = malloc(size + 1);
        strcpy(caps->setab, tmp);
    }
    else
        caps->setab = NULL;
    tmp = tigetstr("cup");
    if (tmp != (char*)0 && tmp != (char*)-1)
    {
        size = strlen(tmp);
        caps->cup = malloc(size + 1);
        strcpy(caps->cup, tmp);
    }
    else
        caps->cup = NULL;
    tmp = tigetstr("bold");
    if (tmp != (char*)0 && tmp != (char*)-1)
    {
        size = strlen(tmp);
        caps->bold = malloc(size + 1);
        strcpy(caps->bold, tmp);
    }
    else
        caps->bold = NULL;
    tmp = tigetstr("smul");
    if (tmp != (char*)0 && tmp != (char*)-1)
    {
        size = strlen(tmp);
        caps->smul = malloc(size + 1);
        strcpy(caps->smul, tmp);
    }
    else
        caps->smul = NULL;
    tmp = tigetstr("rmul");
    if (tmp != (char*)0 && tmp != (char*)-1)
    {
        size = strlen(tmp);
        caps->rmul = malloc(size + 1);
        strcpy(caps->rmul, tmp);
    }
    else
        caps->rmul = NULL;
    tmp = tigetstr("smso");
    if (tmp != (char*)0 && tmp != (char*)-1)
    {
        size = strlen(tmp);
        caps->smso = malloc(size + 1);
        strcpy(caps->smso, tmp);
    }
    else
        caps->smso = NULL;
    tmp = tigetstr("rmso");
    if (tmp != (char*)0 && tmp != (char*)-1)
    {
        size = strlen(tmp);
        caps->rmso = malloc(size + 1);
        strcpy(caps->rmso, tmp);
    }
    else
        caps->rmso = NULL;
    tmp = tigetstr("sgr0");
    if (tmp != (char*)0 && tmp != (char*)-1)
    {
        size = strlen(tmp);
        caps->sgr0 = malloc(size + 1);
        strcpy(caps->sgr0, tmp);
    }
    else
        caps->sgr0 = NULL;
    tmp = tigetstr("civis");
    if (tmp != (char*)0 && tmp != (char*)-1)
    {
        size = strlen(tmp);
        caps->civis = malloc(size + 1);
        strcpy(caps->civis, tmp);
    }
    else
        caps->civis = NULL;
    tmp = tigetstr("cnorm");
    if (tmp != (char*)0 && tmp != (char*)-1)
    {
        size = strlen(tmp);
        caps->cnorm = malloc(size + 1);
        strcpy(caps->cnorm, tmp);
    }
    else
        caps->cnorm = NULL;
}

void wish_free_caps(wish_caps* caps)
{
    free(caps->smcup);
    free(caps->rmcup);
    free(caps->clear);
    free(caps->setaf);
    free(caps->setab);
    free(caps->cup);
    free(caps->bold);
    free(caps->smul);
    free(caps->rmul);
    free(caps->smso);
    free(caps->rmso);
    free(caps->sgr0);
    free(caps->civis);
    free(caps->cnorm);
}
