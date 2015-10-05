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
|     FILE:  extmath.c                                              |
\__________________________________________________________________/

*/

double sgn ( double x )
{
	return ( x >= 0. ? 1. : -1. );
}

double deg ( double x )
{
	return ( x * 180. / M_PI );
}

double rad ( double x )
{
	return ( x * M_PI / 180. );
}

// ===========================================

double cot ( double x )
{
	return ( 1. / tan ( x ) );
}

double sec ( double x )
{
	return ( 1. / cos ( x ) );
}

double csc ( double x )
{
	return ( 1. / sin ( x ) );
}

// ===========================================

double acot ( double x )
{
	return ( atan ( 1. / x ) );
}

double asec ( double x )
{
	return ( acos ( 1. / x ) );
}

double acsc ( double x )
{
	return ( asin ( 1. / x ) );
}

// ===========================================

double coth ( double x )
{
	return ( 1. / tanh ( x ) );
}

double sech ( double x )
{
	return ( 1. / cosh ( x ) );
}

double csch ( double x )
{
	return ( 1. / sinh ( x ) );
}

// ===========================================

double asinh ( double x )
{
	return log ( x + sqrt ( x * x + 1. ) );
}

double acosh ( double x )
{
	return log ( x + sqrt ( x * x - 1. ) );
}

double atanh ( double x )
{
	return log ( ( x + 1. ) / ( x - 1. ) ) / 2.;
}

double acoth ( double x )
{
	return atanh ( 1. / x );
}

double asech ( double x )
{
	return acosh ( 1. / x );
}

double acsch ( double x )
{
	return asinh ( 1. / x );
}

// ===========================================

double sqr ( double x )
{
	return ( x * x );
}

double logbe ( double b, double e )
{
	return ( log ( e ) / log ( b ) );
}
