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
|   MODULE:  Handy functions for 3d vectors                         |
|     FILE:  vector3.c                                              |
\__________________________________________________________________/

*/

vector3_t vector3 ( VECTOR3_ELT x, VECTOR3_ELT y, VECTOR3_ELT z )
{
	vector3_t ret = { x, y, z };
	return ret;
}

vector3_t vector3_add ( vector3_t v1, vector3_t v2 )
{
	return vector3 ( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z );
}

vector3_t vector3_sub ( vector3_t v1, vector3_t v2 )
{
	return vector3 ( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
}

vector3_t vector3_mul ( vector3_t v, VECTOR3_ELT scalar )
{
	return vector3 ( v.x * scalar, v.y * scalar, v.z * scalar );
}

vector3_t vector3_div ( vector3_t v, VECTOR3_ELT scalar )
{
	return vector3 ( v.x / scalar, v.y / scalar, v.z / scalar );
}

vector3_t vector3_abs ( vector3_t v )
{
	return vector3 ( fabs ( v.x ), fabs ( v.y ), fabs ( v.z ) );
}

vector3_t vector3_sgn ( vector3_t v )
{
	return vector3 ( v.x >= 0 ? 1 : -1, v.y >= 0 ? 1 : -1, v.z >= 0 ? 1 : -1 );
}

vector3_t vector3_cross ( vector3_t v1, vector3_t v2 )
{
	return vector3 ( v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x );
}

vector3_t vector3_ratio ( vector3_t v )
{
	if ( !v.x && !v.y && !v.z )
		return v;

	return vector3_div ( v, vector3_max_element ( vector3_abs ( v ) ) );
}

vector3_t vector3_normalize ( vector3_t v )
{
	return vector3_div ( v, vector3_magnitude ( v ) );
}

vector3_t vector3_normal ( vector3_t v1, vector3_t v2, vector3_t v3 )
{
	return vector3_normalize ( vector3_cross ( vector3_sub ( v3, v1 ), vector3_sub ( v2, v1 ) ) );
}

VECTOR3_ELT vector3_scalar_product ( vector3_t v1, vector3_t v2 )
{
	return ( v1.x * v2.x + v1.y * v2.y + v1.z * v2.z );
}

VECTOR3_ELT vector3_distance ( vector3_t v1, vector3_t v2 )
{
	return vector3_magnitude ( vector3_sub ( v2, v1 ) );
}

VECTOR3_ELT vector3_magnitude ( vector3_t v )
{
	return sqrt ( v.x * v.x + v.y * v.y + v.z * v.z );
}

VECTOR3_ELT vector3_max_element ( vector3_t v )
{
	VECTOR3_ELT max = v.x;

	if ( v.y > max )
		max = v.y;
	if ( v.z > max )
		max = v.z;

	return max;
}

VECTOR3_ELT vector3_min_element ( vector3_t v )
{
	VECTOR3_ELT min = v.x;

	if ( v.y < min )
		min = v.y;
	if ( v.z < min )
		min = v.z;

	return min;
}

int vector3_equals ( vector3_t v1, vector3_t v2 )
{
	return ( v1.x == v2.x && v1.y == v2.y && v1.z == v2.z );
}

/*int vector3_scalable ( vector3_t v1, vector3_t v2 )
{
	return vector3_equals ( vector3_sgn ( v1 ), vector3_sgn ( v2 ) ) && vector3_equals ( vector3_abs ( vector3_ratio ( v1 ) ), vector3_abs ( vector3_ratio ( v2 ) ) );
}*/
