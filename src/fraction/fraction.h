// this is a temporary file, not yet included in the project
// this file provides handy functions for dealing with fractions

#ifndef __FRACTION_H
#define __FRACTION_H

int gcd ( int m, int n );

struct fraction
{
	int num, div;
};

typedef struct fraction frac;

frac fraction ( int num, int div );
frac frac_reduce ( frac a );
frac frac_mul ( frac a, frac b );
frac frac_div ( frac a, frac b );
frac frac_add ( frac a, frac b );
frac frac_sub ( frac a, frac b );

//#include "fraction.c"

#endif
