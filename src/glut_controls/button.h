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
|   MODULE:  Button Input Detection & Display                       |
|     FILE:  button.h                                               |
\__________________________________________________________________/

*/

#ifndef __GLUT_CONTROLS_BUTTON
#define __GLUT_CONTROLS_BUTTON

#define BTN_LABEL_MAXLEN 50

typedef struct button_t button_t;
struct button_t
{
	// PUBLIC:
	const inpbuffer_t *inp;
	int x, y, width, height;
	char label[BTN_LABEL_MAXLEN];
	void *font;
	void ( *idlefunc ) ( button_t *btn );
	void ( *mouseup ) ( button_t *btn );
	void ( *mousedown ) ( button_t *btn );
	void ( *mouseover ) ( button_t *btn );
	void ( *mouseout ) ( button_t *btn );
	color_t backgrcol, bordercol, fontcol;
	unsigned char borderwidth;
	char is_transparent, has_border, has_label, is_visible;

	// PRIVATE:
	char is_mouseover, is_clicked;
};

#include "button.c"

#endif
