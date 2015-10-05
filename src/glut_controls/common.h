/*
____________________________________________________________________
|__ GNU General Public License _____________________________________|
|                                                                   |
|  THIS SOFTWARE AND DOCUMENTATION IS PROVIDED "AS IS" IN THE HOPE  |
|  THAT IT WILL BE USEFUL, BUT WITHOUT ANY WARRANTIES, INCLUDING,   |
|  WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY    |
|  AND FITNESS FOR A PARTICULAR PURPOSE.                            |
|                                                                   |
|  This software may be used, copied, redistributed, and/or         |
|  modified under the terms of version 2 (or later) of the          |
|  GNU General Public License as published by the Free Software     |
|  Foundation. The license will probably be available at            |
|  http://www.gnu.org/copyleft/gpl.html.                            |
\__________________________________________________________________/

____________________________________________________________________
|__ Additional Notes _______________________________________________|
|                                                                   |
|  PROJECT:  WaveScout 4D                                           |
|   AUTHOR:  Blagovest Buyukliev "hitman" <hitman@bootbox.net>      |
|   MODULE:  Common Interface Routines                              |
|     FILE:  common.h                                               |
\__________________________________________________________________/

*/

#ifndef __GLUT_CONTROLS_COMMON
#define __GLUT_CONTROLS_COMMON

#include "inpbuffer.h"

typedef struct
{
	unsigned char r, g, b;
} color_t;

int in_rect ( int px, int py, int x, int y, int width, int height );
int in_circle ( int px, int py, int cx, int cy, int radius );
void draw_rect ( int x, int y, int width, int height, int filled );
void outtext ( int x, int y, void *font, const char *str );
int fontheight ( const void *font );
void controls_apply_color ( color_t col );

#include "common.c"
#include "button.h"
#include "textbox.h"
#include "listmenu.h"

#endif
