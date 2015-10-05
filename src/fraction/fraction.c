// this is a temporary file, not yet included in the project
// this file provides handy functions for dealing with fractions

#include "fraction.h"

int gcd ( int m, int n )
{
	int t, r;

	if ( m < n )
		t = m, m = n, n = t;

	r = m % n;
	return r ? gcd ( n, r ) : n;
}

frac fraction ( int num, int div )
{
	frac ret;
	ret.num = num, ret.div = div;
	return ret;
}

frac frac_reduce ( frac a )
{
	if ( a.num && a.div )
	{
		int div = gcd ( a.num, a.div );
		return fraction ( a.num / div, a.div / div );
	}
	a.div = a.div ? 1 : a.div;
	return a;
}

frac frac_mul ( frac a, frac b )
{
	return fraction ( a.num * b.num, a.div * b.div );
}

frac frac_div ( frac a, frac b )
{
	return fraction ( a.num * b.div, a.div * b.num );
}

frac frac_add ( frac a, frac b )
{
	return fraction ( a.num * b.div + b.num * a.div, a.div * b.div );
}

frac frac_sub ( frac a, frac b )
{
	return fraction ( a.num * b.div - b.num * a.div, a.div * b.div );
}

int main ( int argc, char **argv )
{
	frac a = frac_reduce ( fraction ( 320, 400 ) );
	printf ( "%d / %d\n", a.num, a.div );
	getch ( );
	return 0;
}
