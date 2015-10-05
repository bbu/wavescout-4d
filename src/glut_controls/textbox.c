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
|     FILE:  textbox.c                                              |
\__________________________________________________________________/

*/

void controls_draw_textbox ( textbox_t *txt )
{
	char tbuf[100];
	char buf[2] = { '\0', '\0' };

	if ( txt->is_focused )
	{
		speckeys = 0;
		if ( txt->inp->keyb.is_active )
		{
			if ( txt->inp->keyb.key == 0x08 && txt->cursorpos > 0 ) // backspace
			{
				substr_replace ( tbuf, txt->text, "", txt->cursorpos, -1 );
				strcpy ( txt->text, tbuf );
				txt->cursorpos--;

				if ( txt->offset > 0 )
				{
					txt->offset--;
					substr ( tbuf, txt->text, txt->offset, ( txt->width - txt->margin ) / glutBitmapLength ( txt->font, "a" ) );
					strcpy ( txt->buf, tbuf );
				}
				else
					substr ( txt->buf, tbuf, 0, ( txt->width - txt->margin ) / glutBitmapLength ( txt->font, "a" ) );
			}
			else if ( txt->inp->keyb.key == 0x0D ) // enter
			{
				txt->is_focused = 0;

				if ( txt->onblur != NULL )
					( * ( txt->onblur ) ) ( txt );
			}
			else if ( ( isgraph ( txt->inp->keyb.key ) || isspace ( txt->inp->keyb.key ) ) && ( strlen ( txt->text ) < txt->maxlen ) )
			{
				buf[0] = txt->inp->keyb.key;
				substr_replace ( tbuf, txt->text, buf, txt->cursorpos, 0 );
				strcpy ( txt->text, tbuf );

				if ( glutBitmapLength ( txt->font, txt->text ) > ( txt->width - txt->margin ) )
				{
					if ( txt->cursorpos )
						txt->offset++;

					substr ( tbuf, txt->text, txt->offset, ( txt->width - txt->margin ) / glutBitmapLength ( txt->font, "a" ) );
					strcpy ( txt->buf, tbuf );
				}
				else
					strcpy ( txt->buf, txt->text );

				txt->cursorpos++;
			}
		}
		else if ( txt->inp->keyspec.is_active )
		{
			if ( txt->inp->keyspec.key == GLUT_KEY_LEFT )
			{
				if ( txt->cursorpos > 0 )
					txt->cursorpos--;

				if ( txt->cursorpos - txt->offset == 0 )
				{
					if ( txt->offset )
						txt->offset--;

					substr ( tbuf, txt->text, txt->offset, ( txt->width - txt->margin ) / glutBitmapLength ( txt->font, "a" ) );
					strcpy ( txt->buf, tbuf );
				}
			}
			else if ( txt->inp->keyspec.key == GLUT_KEY_RIGHT )
			{
				if ( txt->cursorpos < strlen ( txt->text ) )
					txt->cursorpos++;

				if ( strlen ( txt->buf ) < strlen ( txt->text ) && txt->cursorpos - txt->offset == ( txt->width - txt->margin ) / glutBitmapLength ( txt->font, "a" ) )
				{
					if ( txt->cursorpos < strlen ( txt->text ) )
						txt->offset++;

					substr ( tbuf, txt->text, txt->offset, strlen ( txt->buf ) );
					strcpy ( txt->buf, tbuf );
				}
			}
		}
	}

	if ( txt->is_visible )
	{
		if ( !txt->is_transparent )
		{
			controls_apply_color ( txt->backgrcol );
			draw_rect ( txt->x, txt->y, txt->width, txt->height, 1 );
		}
		if ( txt->has_border )
		{
			controls_apply_color ( txt->bordercol );
			glLineWidth ( txt->borderwidth );
			draw_rect ( txt->x, txt->y, txt->width, txt->height, 0 );
			glLineWidth ( 1 );
		}

		if ( txt->is_focused )
		{
			int textx, texty;

			substr ( tbuf, txt->text, 0, txt->cursorpos - txt->offset );
			textx = txt->x + txt->margin + glutBitmapLength ( txt->font, tbuf );
			texty = txt->y + ( txt->height - fontheight ( txt->font ) ) / 2;
			controls_apply_color ( txt->fontcol );
			glBegin ( GL_LINES );
			glVertex2i ( textx, texty - 1 );
			glVertex2i ( textx, texty + fontheight ( txt->font ) + 3 );
			glEnd ( );
		}
		controls_apply_color ( txt->fontcol );
		outtext ( txt->x + txt->margin, txt->y + ( txt->height + fontheight ( txt->font ) ) / 2, txt->font, txt->buf );
	}

	if ( txt->idlefunc != NULL )
		( * ( txt->idlefunc ) ) ( txt );

	int inside = in_rect ( txt->inp->pmotion.x, txt->inp->pmotion.y, txt->x, txt->y, txt->width, txt->height );

	if ( txt->mouseover != NULL && !txt->is_mouseover && inside )
	{
		txt->is_mouseover = 1;
		( * ( txt->mouseover ) ) ( txt );
	}

	if ( txt->mouseout != NULL && txt->is_mouseover && !inside )
	{
		txt->is_mouseover = 0;
		( * ( txt->mouseout ) ) ( txt );
	}

	if ( txt->mouseup != NULL && txt->inp->mouse.is_active && txt->inp->mouse.state == GLUT_UP && txt->is_clicked )
	{
		txt->is_clicked = 0;
		( * ( txt->mouseup ) ) ( txt );
	}

	if ( txt->mousedown != NULL && txt->inp->mouse.is_active && txt->inp->mouse.state == GLUT_DOWN && inside )
	{
		txt->is_clicked = 1;
		( * ( txt->mousedown ) ) ( txt );
	}

	if ( !txt->is_focused && txt->inp->mouse.is_active && inside )
	{
		txt->is_focused = 1;
		speckeys = 0;

		if ( txt->onfocus != NULL )
			( * ( txt->onfocus ) ) ( txt );
	}

	if ( txt->is_focused && txt->inp->mouse.is_active && !inside )
	{
		txt->is_focused = 0;
		speckeys = 1;

		if ( txt->onblur != NULL )
			( * ( txt->onblur ) ) ( txt );
	}
}
