/*
 * src/init.c
 *
 * This file is a source file from the libwish project.
 * You are free to distribute it as long as you respect the terms
 * and conditions of the MIT license.
 *
 * (c) Maxime Bacoux, 2016 - 2017
 */

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "wish_term.h"

wish_term* wish_init(void)
{
    struct winsize ws;
    wish_term* term;
    int ret;
    int erret;

    ret = setupterm(NULL, 1, &erret);
    if (ret == ERR)
        return NULL;

    term = calloc(1, sizeof(*term));

    /* Load caps */
    wish_init_caps(&term->caps);

    /* Init buffer */
    wish_buffer_init(&term->buffer);

    /* Get the terminal attributes, and store a backup as well */
    tcgetattr(1, &term->term_attr);
    tcgetattr(1, &term->term_attr_backup);

    /* Set the term in raw mode */
    term->term_attr.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    term->term_attr.c_oflag &= ~OPOST;
    term->term_attr.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    term->term_attr.c_cflag &= ~(CSIZE | PARENB);
    term->term_attr.c_cflag |= CS8;
    term->term_attr.c_cc[VMIN] = 1;
    term->term_attr.c_cc[VTIME] = 0;

    /* Use the new attributes */
    tcsetattr(1, TCSADRAIN, &term->term_attr);

    /* Clear the terminfo database */
    del_curterm(cur_term);

    /* Apply some defaults */
    write(1, term->caps.smcup, strlen(term->caps.smcup));
    write(1, term->caps.clear, strlen(term->caps.clear));

    /* Get the term size */
    ioctl(1, TIOCGWINSZ, &ws);
    term->size.x = ws.ws_col;
    term->size.y = ws.ws_row;

    /* Allocate frames */
    wish_frame_init(&term->frames[0], term->size.x, term->size.y);
    wish_frame_init(&term->frames[1], term->size.x, term->size.y);

    term->active_frame = 0;
    term->cursor.x = 0;
    term->cursor.y = 0;
    term->display_cursor = 1;
    term->display_cursor_old = 1;

    return term;
}

void wish_quit(wish_term* term)
{
    if (term)
    {
        /* Free the frames */
        wish_frame_free(&term->frames[0]);
        wish_frame_free(&term->frames[1]);

        /* Reset the old term */
        tcsetattr(1, TCSAFLUSH, &term->term_attr_backup);

        /* Reset cursor */
        write(1, term->caps.cnorm, strlen(term->caps.cnorm));

        /* Exit CA mode */
        write(1, term->caps.rmcup, strlen(term->caps.rmcup));

        /* Free buffer */
        wish_buffer_free(&term->buffer);

        /* Free caps */
        wish_free_caps(&term->caps);
    }
    free(term);
}
