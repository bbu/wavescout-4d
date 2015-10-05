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
|     FILE:  vector3.h                                              |
\__________________________________________________________________/

*/

#ifndef __VECTOR3_H
#define __VECTOR3_H

#include <math.h>
#define VECTOR3_ELT float

typedef struct vector3_t vector3_t;
struct vector3_t
{
	VECTOR3_ELT x, y, z;
};

vector3_t vector3 ( VECTOR3_ELT x, VECTOR3_ELT y, VECTOR3_ELT z );
vector3_t vector3_add ( vector3_t v1, vector3_t v2 );
vector3_t vector3_sub ( vector3_t v1, vector3_t v2 );
vector3_t vector3_mul ( vector3_t v, VECTOR3_ELT scalar );
vector3_t vector3_div ( vector3_t v, VECTOR3_ELT scalar );
vector3_t vector3_abs ( vector3_t v );
vector3_t vector3_sgn ( vector3_t v );
vector3_t vector3_cross ( vector3_t v1, vector3_t v2 );
vector3_t vector3_ratio ( vector3_t v );
vector3_t vector3_normalize ( vector3_t v );
vector3_t vector3_normal ( vector3_t v1, vector3_t v2, vector3_t v3 );
VECTOR3_ELT vector3_scalar_product ( vector3_t v1, vector3_t v2 );
VECTOR3_ELT vector3_distance ( vector3_t v1, vector3_t v2 );
VECTOR3_ELT vector3_magnitude ( vector3_t v );
VECTOR3_ELT vector3_max_element ( vector3_t v );
VECTOR3_ELT vector3_min_element ( vector3_t v );
int vector3_equals ( vector3_t v1, vector3_t v2 );
//int vector3_scalable ( vector3_t v1, vector3_t v2 );

#include "vector3.c"

#endif
