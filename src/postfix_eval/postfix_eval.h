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
|     FILE:  postfix_eval.h                                         |
\__________________________________________________________________/

*/

#ifndef __POSTFIX_EVAL_H
#define __POSTFIX_EVAL_H

#include "extmath.h"

// postfix evaluation errors that may occur
#define POSTFIX_E_OK                  0x00  // No errors, everythin is OK
#define POSTFIX_E_NO_BINARY_OPERAND   0x01  // Not enough operands to apply binary operator on
#define POSTFIX_E_NO_UNARY_OPERAND    0x02  // No operand to apply unary operator on
#define POSTFIX_E_UNEXPECTED_END      0x03  // Unstacked operands, more operators needed in expression
#define POSTFIX_E_FEW_ARGS            0x04  // Too few arguments to a function
#define POSTFIX_E_NUMSTK_SIZE_EXCEED  0x05  // Numeric stack capacity exceeded

#define POSTFIX_NUMSTK_SIZE 40

typedef struct
{
	double ( *func ) ( );
	unsigned char argc;
} func_t;

// Available callback functions. Max number of args is 4.
static func_t funcs[] = {
	{ fabs,  1 }, { ceil,  1 }, { floor, 1 }, { sgn,   1 }, { deg,   1 }, { rad,   1 },
	{ sin,   1 }, { cos,   1 }, { tan,   1 }, { cot,   1 }, { sec,   1 }, { csc,   1 },
	{ asin,  1 }, { acos,  1 }, { atan,  1 }, { acot,  1 }, { asec,  1 }, { acsc,  1 },
	{ sinh,  1 }, { cosh,  1 }, { tanh,  1 }, { coth,  1 }, { sech,  1 }, { csch,  1 },
	{ asinh, 1 }, { acosh, 1 }, { atanh, 1 }, { acoth, 1 }, { asech, 1 }, { acsch, 1 },
	{ sqrt,  1 }, { sqr,   1 }, { exp,   1 }, { log,   1 }, { log10, 1 }, { logbe, 2 },
	{ pow,   2 }, { hypot, 2 }, { atan2, 2 },
	{ NULL }
};

typedef enum
{
	TOKEN_ADD = 1,
	TOKEN_SUB,
	TOKEN_MUL,
	TOKEN_DIV,
	TOKEN_POW,
	TOKEN_CONST,
	TOKEN_VAR,
	TOKEN_UNARY_MINUS,
	TOKEN_UNARY_PLUS,
	TOKEN_FUNC,
} token_t;

#define TOKEN_IS_OPERAND(t)    ( ( t ) == TOKEN_VAR || ( t ) == TOKEN_CONST )
#define TOKEN_IS_OPERATOR(t)   ( ( t ) == TOKEN_ADD || ( t ) == TOKEN_SUB || ( t ) == TOKEN_MUL || ( t ) == TOKEN_DIV || ( t ) == TOKEN_POW )
#define TOKEN_IS_UNARY(t)      ( ( t ) == TOKEN_UNARY_PLUS || ( t ) == TOKEN_UNARY_MINUS )

typedef struct
{
	token_t tok;
	unsigned char index;
	double dval;
} tokendata_t;

// PRIVATE USE:
double apply_operator ( token_t op, double x, double y );
double apply_unary_operator ( token_t op, double x );

// PUBLIC USE:
int postfix_error ( const tokendata_t *expr );
double postfix_eval ( const tokendata_t *expr, const double *varlist );

#include "postfix_eval.c"

#endif
