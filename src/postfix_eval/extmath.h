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
|   MODULE:  Extra math functions for the expression evaluator      |
|     FILE:  extmath.h                                              |
\__________________________________________________________________/

*/

#ifndef __EXTMATH_H
#define __EXTMATH_H

#include <math.h>

double sgn ( double x );
double deg ( double x );
double rad ( double x );

double cot ( double x );
double sec ( double x );
double csc ( double x );

double acot ( double x );
double asec ( double x );
double acsc ( double x );

double coth ( double x );
double sech ( double x );
double csch ( double x );

double asinh ( double x );
double acosh ( double x );
double atanh ( double x );
double acoth ( double x );
double asech ( double x );
double acsch ( double x );

double sqr ( double x );
double logbe ( double b, double e );

#include "extmath.c"

#endif
