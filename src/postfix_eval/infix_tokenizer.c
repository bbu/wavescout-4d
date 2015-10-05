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
|     FILE:  infix_tokenizer.c                                      |
\__________________________________________________________________/

*/

infix_token_t infix_get_token ( const char *literal, int *index, double *dval )
{
	int i;

	for ( i = ITOKEN_RPAREN; i >= ITOKEN_FUNC; --i )
		if ( ( *index = infix_get_token_index ( literal, i, dval ) ) != -1 )
			return i;

	return 0;
}

int infix_get_token_index ( const char *literal, infix_token_t tok, double *dval )
{
	int i = -1;

	switch ( tok )
	{
		case ITOKEN_FUNC:
		{
			while ( infix_funcs[++i].literal != NULL )
				if ( INFIX_CASE_SENSITIVE ? !strcmp ( infix_funcs[i].literal, literal ) : !strcasecmp ( infix_funcs[i].literal, literal ) )
					return infix_funcs[i].index;
		}
		break;

		case ITOKEN_ARGSEP:
		{
			return ( INFIX_CASE_SENSITIVE ? strcmp ( INFIX_LITERAL_ARGSEP, literal ) : strcasecmp ( INFIX_LITERAL_ARGSEP, literal ) ) ? -1 : 1;
		}
		break;

		case ITOKEN_VAR:
		{
			while ( infix_vars[++i].literal != NULL )
				if ( INFIX_CASE_SENSITIVE ? !strcmp ( infix_vars[i].literal, literal ) : !strcasecmp ( infix_vars[i].literal, literal ) )
					return infix_vars[i].index;
		}
		break;

		case ITOKEN_CONST:
		{
			while ( infix_consts[++i].literal != NULL )
				if ( INFIX_CASE_SENSITIVE ? !strcmp ( infix_consts[i].literal, literal ) : !strcasecmp ( infix_consts[i].literal, literal ) )
				{
					*dval = infix_consts[i].value;
					return i;
				}
		}
		break;

		case ITOKEN_OP:
		{
			while ( infix_ops[++i].literal != NULL )
				if ( INFIX_CASE_SENSITIVE ? !strcmp ( infix_ops[i].literal, literal ) : !strcasecmp ( infix_ops[i].literal, literal ) )
					return i;
		}
		break;

		case ITOKEN_NUM:
		{
			int len = strlen ( literal ), count = 0;

			if ( len == 1 && literal[0] == INFIX_CHAR_PERIOD )
				return -1;

			while ( ++i < len )
			{
				if ( isdigit ( literal[i] ) )
					continue;
				else if ( literal[i] == INFIX_CHAR_PERIOD )
				{
					if ( ++count > 1 )
						return -1;
				}
				else
					return -1;
			}

			*dval = atof ( literal );
			return 1;
		}
		break;

		case ITOKEN_LPAREN:
		{
			return ( INFIX_CASE_SENSITIVE ? strcmp ( INFIX_LITERAL_LPAREN, literal ) : strcasecmp ( INFIX_LITERAL_LPAREN, literal ) ) ? -1 : 1;
		}
		break;

		case ITOKEN_RPAREN:
		{
			return ( INFIX_CASE_SENSITIVE ? strcmp ( INFIX_LITERAL_RPAREN, literal ) : strcasecmp ( INFIX_LITERAL_RPAREN, literal ) ) ? -1 : 1;
		}
		break;
	}
	return -1;
}

int infix_tokenize ( const char *expr, char **tokens )
{
	int alloc = sizeof ( char ) * ( strlen ( expr ) + 1 );
	char *buf1 = ( char * ) malloc ( alloc );
	char *buf2 = ( char * ) malloc ( alloc );
	char *tmp = ( char * ) malloc ( alloc );

	if ( buf1 == NULL || buf2 == NULL || tmp == NULL )
		return 0;

	trim ( tmp, expr );
	int diff, pos, scan = 0, len = strlen ( tmp );

	while ( scan < len )
	{
		ltrim ( buf2, substr ( buf1, tmp, scan, len ) );
		diff = strlen ( buf1 ) - strlen ( buf2 );
		!( pos = strcspn ( buf2, INFIX_TOK_CHARS ) ) && pos++;
		substr ( buf1, buf2, 0, pos );
		scan += diff + pos;

		if ( ( *tokens = ( char * ) malloc ( ( strlen ( buf1 ) + 1 ) * sizeof ( char ) ) ) == NULL )
			return 0;

		strcpy ( *tokens, buf1 );
		*tokens++;
	}
	free ( buf1 ); free ( buf2 ); free ( tmp );
	*tokens = NULL;
	return 1;
}

int infix_convert ( char **tokens, int *pos, tokendata_t *postfix )
{
	if ( tokens[0] == NULL )
		return 0;

	infix_token_t curr_tok, prev_tok;
	infix_opstk_elt_t opstk[INFIX_OPSTK_SIZE];
	int i = 0, end = 0, index, ptop = -1, otop = -1;
	double dval;

	prev_tok = infix_get_token ( tokens[0], &index, &dval );

	if ( !prev_tok )
		return INFIX_E_TOKEN_UNKNOWN;

	if ( prev_tok == ITOKEN_LPAREN )
		opstk[++otop].tok = ITOKEN_LPAREN;
	else if ( ITOKEN_IS_OPERAND ( prev_tok ) )
	{
		if ( prev_tok == ITOKEN_VAR )
			postfix[++ptop].tok = TOKEN_VAR, postfix[ptop].index = index;
		else
			postfix[++ptop].tok = TOKEN_CONST, postfix[ptop].dval = dval;

		end = 1;
	}
	else if ( prev_tok == ITOKEN_OP && ( infix_ops[index].tok == TOKEN_ADD || infix_ops[index].tok == TOKEN_SUB ) )
	{
		prev_tok = ITOKEN_UNARY_OP;
		opstk[++otop].tok = ITOKEN_UNARY_OP, opstk[otop].index = index;
	}
	else if ( prev_tok == ITOKEN_FUNC )
		opstk[++otop].tok = ITOKEN_FUNC, opstk[otop].index = index;
	else // if ( prev_tok == ITOKEN_OP || prev_tok == ITOKEN_RPAREN || prev_tok == ITOKEN_ARGSEP )
		return INFIX_E_UNEXPECTED_BEGINNING;

	while ( tokens[++i] != NULL )
	{
		curr_tok = infix_get_token ( tokens[i], &index, &dval );
		*pos = i;

		if ( !curr_tok )
			return INFIX_E_TOKEN_UNKNOWN;

		switch ( curr_tok )
		{
			case ITOKEN_LPAREN:
			{
				if ( ITOKEN_IS_OPERAND ( prev_tok ) || prev_tok == ITOKEN_RPAREN )
					return INFIX_E_BEFORE_LPAREN;

				if ( prev_tok != ITOKEN_FUNC )
					opstk[++otop].tok = ITOKEN_LPAREN;

				end = 0;
			}
			break;

			case ITOKEN_RPAREN:
			{
				if ( prev_tok == ITOKEN_FUNC || prev_tok == ITOKEN_LPAREN || prev_tok == ITOKEN_OP || prev_tok == ITOKEN_UNARY_OP || prev_tok == ITOKEN_ARGSEP )
					return INFIX_E_BEFORE_RPAREN;

				while ( otop != -1 && opstk[otop].tok == ITOKEN_OP )
					postfix[++ptop].tok = infix_ops[opstk[otop--].index].tok;

 				if ( otop == -1 )
					return INFIX_E_NO_LPAREN;

				switch ( opstk[otop].tok )
				{
					case ITOKEN_LPAREN:
					// do nothing :)
					break;

					case ITOKEN_FUNC:
					{
 						if ( funcs[opstk[otop].index].argc != 1 )
 							return INFIX_E_WRONG_ARGC;

						postfix[++ptop].tok = TOKEN_FUNC, postfix[ptop].index = opstk[otop].index;
					}
					break;

					case ITOKEN_ARGSEP:
					{
						if ( opstk[otop].index != funcs[opstk[otop - 1].index].argc )
							return INFIX_E_WRONG_ARGC;

						otop--;
						postfix[++ptop].tok = TOKEN_FUNC, postfix[ptop].index = opstk[otop].index;
					}
					break;

					// Would it happen anyway?
					case ITOKEN_UNARY_OP:
					break;
				}
				otop--;

				while ( otop != -1 && opstk[otop].tok == ITOKEN_UNARY_OP )
					postfix[++ptop].tok = opstk[otop--].index ? TOKEN_UNARY_MINUS : TOKEN_UNARY_PLUS;

				end = 1;
			}
			break;

			case ITOKEN_FUNC:
			{
				if ( ITOKEN_IS_OPERAND ( prev_tok ) || prev_tok == ITOKEN_RPAREN || prev_tok == ITOKEN_FUNC )
					return INFIX_E_BEFORE_FUNC;

				opstk[++otop].tok = ITOKEN_FUNC, opstk[otop].index = index;
				end = 0;
			}
			break;

			case ITOKEN_ARGSEP:
			{
				if ( prev_tok == ITOKEN_LPAREN || prev_tok == ITOKEN_FUNC || prev_tok == ITOKEN_OP || prev_tok == ITOKEN_UNARY_OP || prev_tok == ITOKEN_ARGSEP )
					return INFIX_E_BEFORE_ARGSEP;

				while ( otop != -1 && opstk[otop].tok == ITOKEN_OP )
					postfix[++ptop].tok = infix_ops[opstk[otop--].index].tok;

				if ( otop == -1 || opstk[otop].tok == ITOKEN_LPAREN )
					return INFIX_E_NO_FUNC_TO_ARGSEP;
 				else if ( opstk[otop].tok == ITOKEN_FUNC )
 					opstk[++otop].tok = ITOKEN_ARGSEP, opstk[otop].index = 2;
				else // if ( opstk[otop].tok == ITOKEN_ARGSEP )
					opstk[otop].index++;

				end = 0;
			}
			break;

			case ITOKEN_NUM:
			case ITOKEN_CONST:
			case ITOKEN_VAR:
			{
				if ( ITOKEN_IS_OPERAND ( prev_tok ) || prev_tok == ITOKEN_RPAREN || prev_tok == ITOKEN_FUNC )
					return INFIX_E_BEFORE_OPERAND;

				if ( curr_tok == ITOKEN_VAR )
					postfix[++ptop].tok = TOKEN_VAR, postfix[ptop].index = index;
				else
					postfix[++ptop].tok = TOKEN_CONST, postfix[ptop].dval = dval;

				while ( otop != -1 && opstk[otop].tok == ITOKEN_UNARY_OP )
					postfix[++ptop].tok = opstk[otop--].index ? TOKEN_UNARY_MINUS : TOKEN_UNARY_PLUS;

				end = 1;
			}
			break;

			case ITOKEN_OP:
			{
				if ( ( infix_ops[index].tok == TOKEN_ADD || infix_ops[index].tok == TOKEN_SUB ) && ( prev_tok == ITOKEN_LPAREN || prev_tok == ITOKEN_OP || prev_tok == ITOKEN_UNARY_OP || prev_tok == ITOKEN_ARGSEP ) )
					curr_tok = ITOKEN_UNARY_OP;
				else if ( prev_tok == ITOKEN_UNARY_OP || prev_tok == ITOKEN_FUNC || prev_tok == ITOKEN_LPAREN || prev_tok == ITOKEN_OP || prev_tok == ITOKEN_ARGSEP )
					return INFIX_E_BEFORE_OP;

				if ( curr_tok == ITOKEN_UNARY_OP )
					opstk[++otop].tok = ITOKEN_UNARY_OP, opstk[otop].index = index;
				else
				{
					if ( otop == -1 || opstk[otop].tok == ITOKEN_LPAREN || opstk[otop].tok == ITOKEN_FUNC || opstk[otop].tok == ITOKEN_ARGSEP )
						opstk[++otop].tok = ITOKEN_OP, opstk[otop].index = index;
					else
					{
						while ( otop != -1 && opstk[otop].tok == ITOKEN_OP && ( infix_ops[opstk[otop].index].precedence >= infix_ops[index].precedence ) )
							postfix[++ptop].tok = infix_ops[opstk[otop--].index].tok;

						opstk[++otop].tok = ITOKEN_OP, opstk[otop].index = index;
					}
				}
				end = 0;
			}
			break;
		}
		prev_tok = curr_tok;
	}

	if ( !end )
		return INFIX_E_UNEXPECTED_END;

	while ( otop != -1 )
	{
		if ( opstk[otop].tok != ITOKEN_LPAREN && opstk[otop].tok != ITOKEN_FUNC )
			postfix[++ptop].tok = infix_ops[opstk[otop--].index].tok;
		else
			return INFIX_E_NO_RPAREN;
	}

	postfix[++ptop].tok = 0;
	return 0;
}

char *infix_errstr ( char *buf, int err )
{
	switch ( err )
	{
		case INFIX_E_BEFORE_LPAREN:
		return strcpy ( buf, "Error in expression: incompatible token before \"(\"" );

		case INFIX_E_BEFORE_RPAREN:
		return strcpy ( buf, "Error in expression: incompatible token before \")\"" );

		case INFIX_E_BEFORE_FUNC:
		return strcpy ( buf, "Error in expression: incompatible token before function" );

		case INFIX_E_BEFORE_ARGSEP:
		return strcpy ( buf, "Error in expression: incompatible token before argument separator" );

		case INFIX_E_BEFORE_OPERAND:
		return strcpy ( buf, "Error in expression: incompatible token before operand" );

		case INFIX_E_BEFORE_OP:
		return strcpy ( buf, "Error in expression: incompatible token before operator" );

		case INFIX_E_TOKEN_UNKNOWN:
		return strcpy ( buf, "Error in expression: couldn't recognize token" );

		case INFIX_E_UNEXPECTED_BEGINNING:
		return strcpy ( buf, "Error in expression: unexpected beginning" );

		case INFIX_E_UNEXPECTED_END:
		return strcpy ( buf, "Error in expression: unexpected end" );

		case INFIX_E_NO_LPAREN:
		return strcpy ( buf, "Error in expression: no matching \"(\"" );

		case INFIX_E_NO_RPAREN:
		return strcpy ( buf, "Error in expression: no matching \")\"" );

		case INFIX_E_WRONG_ARGC:
		return strcpy ( buf, "Error in expression: wrong argument count to function" );

		case INFIX_E_NO_FUNC_TO_ARGSEP:
		return strcpy ( buf, "Error in expression: no corresponding function to argument separator" );
	}
}
