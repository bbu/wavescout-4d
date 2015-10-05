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
|   MODULE:  Input Buffer                                           |
|     FILE:  inpbuffer.h                                            |
\__________________________________________________________________/

*/

#ifndef __INPBUFFER_H
#define __INPBUFFER_H

typedef struct
{
	int x, y, state, button;
	int is_active;
} mouse_t;

typedef struct
{
	int x, y;
	int is_active;
} motion_t;

typedef struct
{
	int key, x, y;
	int is_active;
} keyspec_t;

typedef struct
{
	unsigned char key;
	int x, y;
	int is_active;
} keyb_t;

typedef struct
{
	mouse_t mouse;
	motion_t motion, pmotion;
	keyspec_t keyspec;
	keyb_t keyb;
} inpbuffer_t;

void inp_reset ( inpbuffer_t *inp );
int inp_is_active ( inpbuffer_t *inp );

#include "inpbuffer.c"

#endif
