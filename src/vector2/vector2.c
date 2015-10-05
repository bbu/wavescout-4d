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
|   MODULE:  Handy functions for 2d vectors                         |
|     FILE:  vector2.c                                              |
\__________________________________________________________________/

*/

vector2_t vector2 ( VECTOR2_ELT x, VECTOR2_ELT y )
{
	vector2_t ret = { x, y };
	return ret;
}

vector2_t vector2_add ( vector2_t v1, vector2_t v2 )
{
	return vector2 ( v1.x + v2.x, v1.y + v2.y );
}

vector2_t vector2_sub ( vector2_t v1, vector2_t v2 )
{
	return vector2 ( v1.x - v2.x, v1.y - v2.y );
}

vector2_t vector2_mul ( vector2_t v, VECTOR2_ELT scalar )
{
	return vector2 ( v.x * scalar, v.y * scalar );
}

vector2_t vector2_div ( vector2_t v, VECTOR2_ELT scalar )
{
	return vector2 ( v.x / scalar, v.y / scalar );
}

vector2_t vector2_abs ( vector2_t v )
{
	return vector2 ( fabs ( v.x ), fabs ( v.y ) );
}

vector2_t vector2_ratio ( vector2_t v )
{
	if ( !v.x && !v.y )
		return v;

	VECTOR2_ELT max = fabs ( vector2_max_element ( v ) ), min = fabs ( vector2_min_element ( v ) );
	return vector2_div ( v, max > min ? max : min );
}

vector2_t vector2_normalize ( vector2_t v )
{
	return vector2_div ( v, vector2_magnitude ( v ) );
}

VECTOR2_ELT vector2_scalar_product ( vector2_t v1, vector2_t v2 )
{
	return ( v1.x * v2.x + v1.y * v2.y );
}

VECTOR2_ELT vector2_distance ( vector2_t v1, vector2_t v2 )
{
	return vector2_magnitude ( vector2_sub ( v2, v1 ) );
}

VECTOR2_ELT vector2_magnitude ( vector2_t v )
{
	return hypot ( v.x, v.y );
}

VECTOR2_ELT vector2_max_element ( vector2_t v )
{
	return ( v.x > v.y ) ? v.x : v.y;
}

VECTOR2_ELT vector2_min_element ( vector2_t v )
{
	return ( v.x < v.y ) ? v.x : v.y;
}

int vector2_equals ( vector2_t v1, vector2_t v2 )
{
	return ( v1.x == v2.x && v1.y == v2.y );
}

/*int vector2_scalable ( vector2_t v1, vector2_t v2 )
{
	return vector2_equals ( vector2_abs ( vector2_ratio ( v1 ) ), vector2_abs ( vector2_ratio ( v2 ) ) );
}*/
