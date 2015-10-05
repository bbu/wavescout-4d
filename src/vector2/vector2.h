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
|     FILE:  vector2.h                                              |
\__________________________________________________________________/

*/

#ifndef __VECTOR2_H
#define __VECTOR2_H

#include <math.h>
#define VECTOR2_ELT float

typedef struct vector2_t vector2_t;
struct vector2_t
{
	VECTOR2_ELT x, y;
};

vector2_t vector2 ( VECTOR2_ELT x, VECTOR2_ELT y );
vector2_t vector2_add ( vector2_t v1, vector2_t v2 );
vector2_t vector2_sub ( vector2_t v1, vector2_t v2 );
vector2_t vector2_mul ( vector2_t v, VECTOR2_ELT scalar );
vector2_t vector2_div ( vector2_t v, VECTOR2_ELT scalar );
vector2_t vector2_abs ( vector2_t v );
vector2_t vector2_ratio ( vector2_t v );
vector2_t vector2_normalize ( vector2_t v );
VECTOR2_ELT vector2_scalar_product ( vector2_t v1, vector2_t v2 );
VECTOR2_ELT vector2_distance ( vector2_t v1, vector2_t v2 );
VECTOR2_ELT vector2_magnitude ( vector2_t v );
VECTOR2_ELT vector2_max_element ( vector2_t v );
VECTOR2_ELT vector2_min_element ( vector2_t v );
int vector2_equals ( vector2_t v1, vector2_t v2 );
//int vector2_scalable ( vector2_t v1, vector2_t v2 );

#include "vector2.c"

#endif
