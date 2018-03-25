#ifndef __KEYBOARD__
#define __KEYBOARD__

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

static struct termios keyboard_setting, keyboard_new_setting;
static int keyboard_character = -1;

void keyboard_init();

int keyboard_hit();
int keyboard_readch();

void keyboard_close();
#endif
