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
|   MODULE:  Textbox Input Detection & Display                      |
|     FILE:  textbox.h                                              |
\__________________________________________________________________/

*/

#ifndef __GLUT_CONTROLS_TEXTBOX
#define __GLUT_CONTROLS_TEXTBOX

#define TEXTBOX_TEXT_MAXLEN 100

typedef struct textbox_t textbox_t;
struct textbox_t
{
	// PUBLIC:
	inpbuffer_t *inp;
	int x, y, width, height;
	char text[TEXTBOX_TEXT_MAXLEN];
	void *font;
	void ( *idlefunc ) ( textbox_t *txt );
	void ( *mouseup ) ( textbox_t *txt );
	void ( *mousedown ) ( textbox_t *txt );
	void ( *mouseover ) ( textbox_t *txt );
	void ( *mouseout ) ( textbox_t *txt );
	void ( *onfocus ) ( textbox_t *txt );
	void ( *onblur ) ( textbox_t *txt );
	color_t backgrcol, bordercol, fontcol;
	unsigned char borderwidth, margin, maxlen;
	char is_transparent, has_border, is_visible;

	// PRIVATE:
	char is_mouseover, is_focused, is_clicked;
	int cursorpos, offset;
	char buf[TEXTBOX_TEXT_MAXLEN];
};

#include "textbox.c"

#endif
