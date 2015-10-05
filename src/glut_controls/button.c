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
|     FILE:  button.c                                               |
\__________________________________________________________________/

*/

void controls_draw_button ( button_t *btn )
{
	if ( btn->is_visible )
	{
		if ( !btn->is_transparent )
		{
			controls_apply_color ( btn->backgrcol );
			draw_rect ( btn->x, btn->y, btn->width, btn->height, 1 );
		}
		if ( btn->has_border )
		{
			controls_apply_color ( btn->bordercol );
			glLineWidth ( btn->borderwidth );
			draw_rect ( btn->x, btn->y, btn->width, btn->height, 0 );
			glLineWidth ( 1 );
		}
		if ( btn->has_label )
		{
			controls_apply_color ( btn->fontcol );
			outtext ( btn->x + ( btn->width - glutBitmapLength ( btn->font, btn->label ) ) / 2, btn->y + ( btn->height + fontheight ( btn->font ) ) / 2, btn->font, btn->label );
		}
	}
	if ( btn->idlefunc != NULL )
		( * ( btn->idlefunc ) ) ( btn );

	int inside = in_rect ( btn->inp->pmotion.x, btn->inp->pmotion.y, btn->x, btn->y, btn->width, btn->height );

	if ( btn->mouseover != NULL && !btn->is_mouseover && inside )
	{
		btn->is_mouseover = 1;
		( * ( btn->mouseover ) ) ( btn );
	}

	if ( btn->mouseout != NULL && btn->is_mouseover && !inside )
	{
		btn->is_mouseover = 0;
		( * ( btn->mouseout ) ) ( btn );
	}

	if ( btn->mouseup != NULL && btn->inp->mouse.is_active && btn->inp->mouse.state == GLUT_UP && btn->is_clicked )
	{
		btn->is_clicked = 0;
		( * ( btn->mouseup ) ) ( btn );
	}

	if ( btn->mousedown != NULL && btn->inp->mouse.is_active && btn->inp->mouse.state == GLUT_DOWN && inside )
	{
		btn->is_clicked = 1;
		( * ( btn->mousedown ) ) ( btn );
	}
}
