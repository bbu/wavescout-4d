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
|   MODULE:  Postfix Expression Evaluation                          |
|     FILE:  postfix_eval.c                                         |
\__________________________________________________________________/

*/

double apply_operator ( token_t op, double x, double y )
{
	switch ( op )
	{
		case TOKEN_ADD:
		return ( x + y );

		case TOKEN_SUB:
		return ( x - y );

		case TOKEN_MUL:
		return ( x * y );

		case TOKEN_DIV:
		return ( y == 0 ? x / 0.00001 : x / y );

		case TOKEN_POW:
		return y == 2 ? x * x : pow ( x, y );
	}
}

double apply_unary_operator ( token_t op, double x )
{
	switch ( op )
	{
		case TOKEN_UNARY_PLUS:
		return ( +x );

		case TOKEN_UNARY_MINUS:
		return ( -x );
	}
}

int postfix_error ( const tokendata_t *expr )
{
	int nums = 0, i = -1;

	while ( expr[++i].tok )
	{
		if ( TOKEN_IS_OPERATOR ( expr[i].tok ) )
		{
			if ( nums < 2 )
				return POSTFIX_E_NO_BINARY_OPERAND;

			nums--;
		}
		else if ( TOKEN_IS_OPERAND ( expr[i].tok ) )
		{
			if ( nums > POSTFIX_NUMSTK_SIZE )
				return POSTFIX_E_NUMSTK_SIZE_EXCEED;

			nums++;
		}
		else if ( TOKEN_IS_UNARY ( expr[i].tok ) && nums < 1 )
			return POSTFIX_E_NO_UNARY_OPERAND;
		else if ( expr[i].tok == TOKEN_FUNC )
		{
			if ( nums < funcs[expr[i].index].argc )
				return POSTFIX_E_FEW_ARGS;

			nums -= funcs[expr[i].index].argc - 1;
		}
	}

	if ( nums != 1 )
		return POSTFIX_E_UNEXPECTED_END;

	return POSTFIX_E_OK;
}

static double numstk[POSTFIX_NUMSTK_SIZE];

double postfix_eval ( const tokendata_t *expr, const double *varlist )
{
	register int i = -1, top = -1;

	while ( expr[++i].tok )
	{
		if ( TOKEN_IS_OPERATOR ( expr[i].tok ) )
			numstk[--top] = apply_operator ( expr[i].tok, numstk[top], numstk[top + 1] );
		else if ( TOKEN_IS_OPERAND ( expr[i].tok ) )
			numstk[++top] = ( expr[i].tok == TOKEN_VAR ) ? varlist[expr[i].index] : expr[i].dval;
		else if ( TOKEN_IS_UNARY ( expr[i].tok ) )
			numstk[top] = apply_unary_operator ( expr[i].tok, numstk[top] );
		else if ( expr[i].tok == TOKEN_FUNC )
		{
			top -= funcs[expr[i].index].argc - 1;
			numstk[top] = ( funcs[expr[i].index].func ) ( numstk[top], numstk[top + 1], numstk[top + 2], numstk[top + 3] );
		}
	}
	return numstk[top];
}
