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
|     FILE:  inpbuffer.c                                            |
\__________________________________________________________________/

*/

#include "inpbuffer.h"

void inp_reset ( inpbuffer_t *inp )
{
	inp->mouse.is_active =
	inp->motion.is_active =
	inp->pmotion.is_active =
	inp->keyspec.is_active =
	inp->keyb.is_active = 0;
}

int inp_is_active ( inpbuffer_t *inp )
{
	return ( inp->mouse.is_active || inp->motion.is_active || inp->pmotion.is_active || inp->keyspec.is_active || inp->keyb.is_active );
}
