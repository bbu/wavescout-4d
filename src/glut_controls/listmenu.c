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
|     FILE:  listmenu.c                                             |
|     TODO:  This module is yet incomplete                          |
\__________________________________________________________________/

*/

void controls_draw_listmenu ( listmenu_t *menu )
{
	if ( menu->idlefunc != NULL ) ( * ( menu->idlefunc ) ) ( menu );

	if ( menu->is_visible )
	{
		controls_apply_color ( menu->backgrcol );
		draw_rect ( menu->x, menu->y, menu->width, menu->rowheight * menu->rows + menu->margin * 2, 1 );

		if ( menu->has_border )
		{
			controls_apply_color ( menu->bordercol );
			glLineWidth ( menu->borderwidth );
			draw_rect ( menu->x, menu->y, menu->width, menu->rowheight * menu->rows + menu->margin * 2, 0 );
			glLineWidth ( 1 );
		}
		int i = -1;

		controls_apply_color ( menu->fontcol );
		while ( ++i < menu->rows )
		{
			if ( i == menu->selpos )
			{
				color_t a;
				a.r = a.g = a.b = 210;
				controls_apply_color ( a );
				draw_rect ( menu->x + menu->margin, menu->y + menu->margin + i * menu->rowheight, menu->width - menu->margin * 2, menu->rowheight, 1 );
			}
			controls_apply_color ( i != menu->selpos ? menu->fontcol : menu->bordercol );
			outtext ( menu->x + menu->margin + 3, ( menu->y + menu->margin + i * menu->rowheight ) + ( menu->rowheight + fontheight ( menu->font ) ) / 2, menu->font, menu->elts[i] );
		}
	}

	if ( menu->inp->mouse.is_active && in_rect ( menu->inp->pmotion.x, menu->inp->pmotion.y, menu->x + menu->margin, menu->y + menu->margin, menu->width - menu->margin * 2, menu->rowheight * menu->rows ) )
	{
		int sel = floor ( ( 1. * ( menu->inp->pmotion.y - menu->y - menu->margin ) / ( menu->rowheight * menu->rows ) ) * menu->rows );

		if ( sel != menu->selpos )
		{
			menu->selpos = sel;
			if ( menu->onchange != NULL ) ( * ( menu->onchange ) ) ( menu, sel );
		}
	}
}
