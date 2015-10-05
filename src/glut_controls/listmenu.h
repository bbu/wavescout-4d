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
|   MODULE:  List Menus Input Detection & Display                   |
|     FILE:  listmenu.h                                             |
|     TODO:  This module is yet incomplete                          |
\__________________________________________________________________/

*/

#ifndef __LISTMENU_H
#define __LISTMENU_H

#define LISTMENU_MAX_ELEMENTS 20

typedef struct listmenu_t listmenu_t;
struct listmenu_t
{
	// PUBLIC:
	inpbuffer_t *inp;
	int x, y, width, rowheight, rows, elt_count;
	char *elts[LISTMENU_MAX_ELEMENTS];
	void *font;
	void ( *idlefunc ) ( listmenu_t *menu );
	void ( *mouseup ) ( listmenu_t *menu );
	void ( *mousedown ) ( listmenu_t *menu );
	void ( *mouseover ) ( listmenu_t *menu );
	void ( *mouseout ) ( listmenu_t *menu );
	void ( *onfocus ) ( listmenu_t *menu );
	void ( *onblur ) ( listmenu_t *menu );
	void ( *onchange ) ( listmenu_t *menu, int newpos );


	color_t backgrcol, bordercol, fontcol, selbackgr, selfontcol, selbordercol;
	unsigned char borderwidth, margin;
	char is_transparent, has_border, is_visible;
	/*

	----------------- X
	| abc            | |
	|----------------| |
	| def            | |
	|----------------| |
	| ghi            | |
	|----------------| |
	| jkl            | |
	|----------------| |
	| mno            | |
	|----------------| |
	| pqr            | |
	|----------------| |
	| stu            | |
	----------------- X

	*/

	// PRIVATE:
	int selpos, offset;
};

#include "listmenu.c"

#endif
