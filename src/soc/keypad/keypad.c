/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include "soc/keypad.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <termios.h>

static struct keypad_iomem *io = NULL;
static struct termios attr;

void keypad_init(void)
{
    struct termios newattr;

    io = (struct keypad_iomem *)KEYPAD_IOMEM_BASE;
    tcgetattr(STDIN_FILENO, &attr);
    newattr = attr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
}

void keypad_exit(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &attr);
    io = NULL;
}

void keypad_loop(void)
{
    struct termios oldattr, newattr;
    int inp;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    while (1) {
        inp = getc(stdin);
        printf("%d\n", inp);
    }
}