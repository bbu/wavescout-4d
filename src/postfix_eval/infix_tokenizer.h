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
|   MODULE:  Infix Expression Tokenizer & Convertor                 |
|     FILE:  infix_tokenizer.h                                      |
\__________________________________________________________________/

*/

#ifndef __INFIX_TOKENIZER_H
#define __INFIX_TOKENIZER_H

#include "../phpstring/phpstring.h"
#include "postfix_eval.h"

#define ITOKEN_IS_OPERAND(t) ( ( t ) == ITOKEN_VAR || ( t ) == ITOKEN_CONST || ( t ) == ITOKEN_NUM )

#define INFIX_E_BEFORE_LPAREN         0x01
#define INFIX_E_BEFORE_RPAREN         0x02
#define INFIX_E_BEFORE_FUNC           0x03
#define INFIX_E_BEFORE_ARGSEP         0x04
#define INFIX_E_BEFORE_OPERAND        0x05
#define INFIX_E_BEFORE_OP             0x06
#define INFIX_E_TOKEN_UNKNOWN         0x07
#define INFIX_E_UNEXPECTED_BEGINNING  0x08
#define INFIX_E_UNEXPECTED_END        0x09
#define INFIX_E_NO_LPAREN             0x0a
#define INFIX_E_NO_RPAREN             0x0b
#define INFIX_E_WRONG_ARGC            0x0c
#define INFIX_E_NO_FUNC_TO_ARGSEP     0x0d

#define INFIX_OPSTK_SIZE 40
#define INFIX_CASE_SENSITIVE 0

typedef enum
{
	ITOKEN_FUNC = 1,
	ITOKEN_ARGSEP,
	ITOKEN_VAR,
	ITOKEN_CONST,
	ITOKEN_OP,
	ITOKEN_UNARY_OP,
	ITOKEN_NUM,
	ITOKEN_LPAREN,
	ITOKEN_RPAREN,
} infix_token_t;

typedef struct
{
	infix_token_t tok;
	unsigned char index;
} infix_opstk_elt_t;

typedef struct
{
	char *literal;
	unsigned char index;
} infix_var_t;

static infix_var_t infix_vars[] = {
	{ "x",     0 }, { "z",     1 }, { "t",     2 },
	{ NULL }
};

static infix_var_t infix_funcs[] = {
	{ "abs",    0 }, { "ceil",   1 }, { "floor",  2 }, { "sgn",    3 }, { "deg",    4 }, { "rad",    5 },
	{ "sin",    6 }, { "cos",    7 }, { "tan",    8 }, { "cot",    9 }, { "sec",   10 }, { "csc",   11 },
	{ "asin",  12 }, { "acos",  13 }, { "atan",  14 }, { "acot",  15 }, { "asec",  16 }, { "acsc",  17 },
	{ "sinh",  18 }, { "cosh",  19 }, { "tanh",  20 }, { "coth",  21 }, { "sech",  22 }, { "csch",  23 },
	{ "asinh", 24 }, { "acosh", 25 }, { "atanh", 26 }, { "acoth", 27 }, { "asech", 28 }, { "acsch", 29 },
	{ "sqrt",  30 }, { "sqr",   31 }, { "exp",   32 }, { "ln",    33 }, { "lg",    34 }, { "log",   35 },
	{ "pow",   36 }, { "hypot", 37 }, { "atan2", 38 },
	{ NULL }
};

typedef struct
{
	char *literal;
	double value;
} infix_const_t;

static infix_const_t infix_consts[] = {
	{ "pi", M_PI }, { "e",   M_E },
	{ NULL }
};

typedef struct
{
	char *literal;
	unsigned char precedence;
	token_t tok;
} infix_op_t;

static infix_op_t infix_ops[] = {
	{ "+", 1, TOKEN_ADD }, { "-", 1, TOKEN_SUB },
	{ "*", 2, TOKEN_MUL }, { "/", 2, TOKEN_DIV },
	{ "^", 3, TOKEN_POW },
	{ NULL }
};

#define INFIX_LITERAL_LPAREN  "("
#define INFIX_LITERAL_RPAREN  ")"
#define INFIX_LITERAL_ARGSEP  ","
#define INFIX_TOK_CHARS       "+-*/^(), "
#define INFIX_CHAR_PERIOD     '.'

// PRIVATE USE:
infix_token_t infix_get_token ( const char *literal, int *index, double *dval );
int infix_get_token_index ( const char *literal, infix_token_t tok, double *dval );

// PUBLIC USE:
int infix_tokenize ( const char *expr, char **tokens );
int infix_convert ( char **tokens, int *pos, tokendata_t *postfix );
char *infix_errstr ( char *buf, int err );

#include "infix_tokenizer.c"

#endif
