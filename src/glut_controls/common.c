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
|     FILE:  common.c                                               |
\__________________________________________________________________/

*/

int in_rect ( int px, int py, int x, int y, int width, int height )
{
	return ( px >= x && px <= x + width ) && ( py >= y && py <= y + height );
}

int in_circle ( int px, int py, int cx, int cy, int radius )
{
	return ( hypot ( px - cx, py - cy ) <= radius );
}

void draw_rect ( int x, int y, int width, int height, int filled )
{
	glBegin ( filled ? GL_QUADS : GL_LINE_LOOP );
		glVertex2i ( x, y );
		glVertex2i ( x + width, y );
		glVertex2i ( x + width, y + height );
		glVertex2i ( x, y + height );
	glEnd ( );
}

void draw_circle ( int cx, int cy, int radius, int sectors )
{
	float theta, step = 2 * M_PI / ( sectors <= 3 ? 3 : sectors );

	glBegin ( GL_LINE_LOOP );

	for ( theta = 0; theta < 2 * M_PI; theta += step )
		glVertex2i ( cx + radius * cos ( theta ), cy + radius * sin ( theta ) );

	glEnd ( );
}

void outtext ( int x, int y, void *font, const char *str )
{
	int len = strlen ( str ), i;
	glRasterPos2f ( x, y );

	for ( i = 0; i < len; i++ )
		glutBitmapCharacter ( font, str[i] );
}

int fontheight ( const void *font )
{
	if ( font == GLUT_BITMAP_HELVETICA_10 )
		return 8;

	if ( font == GLUT_BITMAP_HELVETICA_12 )
		return 9;

	if ( font == GLUT_BITMAP_HELVETICA_18 )
		return 14;

	if ( font == GLUT_BITMAP_8_BY_13 )
		return 9;

	if ( font == GLUT_BITMAP_9_BY_15 )
		return 10;

	if ( font == GLUT_BITMAP_TIMES_ROMAN_10 )
		return 7;

	if ( font == GLUT_BITMAP_TIMES_ROMAN_24 )
		return 17;
}

void controls_apply_color ( color_t col )
{
	glColor3ub ( col.r, col.g, col.b );
}
