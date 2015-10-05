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
|   MODULE:  A String Library similar to the PHP's string funcs     |
| COMMENTS:  Refer to the PHP manual for each function's use        |
|     FILE:  phpstring.h                                            |
\__________________________________________________________________/

*/

#ifndef __PHPSTRING_H
#define __PHPSTRING_H

#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STR_PAD_LEFT 	1
#define STR_PAD_RIGHT 	2
#define STR_PAD_BOTH 	3
#define ENT_COMPAT 		4
#define ENT_QUOTES 		5
#define ENT_NOQUOTES 	6

char *ltrim ( char *dst, const char *src );
char *rtrim ( char *dst, const char *src );
char *trim ( char *dst, const char *src );
char *tight ( char *dst, const char *src );
char *substr ( char *dst, const char *src, int pos, int len );
char *substr_replace ( char *dst, const char *src, const char *rpl, int pos, int len );
char *str_replace ( char *dst, const char *src, const char *ndl, const char *rpl );
char *str_repeat ( char *dst, const char *src, int mul );
char *str_shuffle ( char *dst, const char *src );
char *str_rot13 ( char *dst, const char *src );
char *str_pad ( char *dst, const char *src, const char *pad, int len, int mode );
char *htmlspecialchars ( char *dst, const char *src, int mode );
int substr_count ( const char *hay, const char *ndl );
int strpos ( const char *hay, const char *ndl );
int strrpos ( const char *hay, const char *ndl );

int IS_WHITESPACE ( char chr )
{
	return ( chr == ' '  ) ||
	       ( chr == '\n' ) ||
	       ( chr == '\t' ) ||
	       ( chr == '\r' ) ||
	       ( chr == '\0' ) ||
	       ( chr == '\x0B' );
}

int IS_HTML_ENTITY ( char chr, int mode )
{
	return ( chr == '&' ) ||
	       ( chr == '"' && mode != ENT_NOQUOTES ) ||
	       ( chr == '\'' && mode == ENT_QUOTES ) ||
	       ( chr == '<' ) ||
	       ( chr == '>' );
}

char *HTML_TRANS ( char chr )
{
	switch ( chr )
	{
		case '&':	return "&amp;";
		case '"':	return "&quot;";
		case '\'':	return "&#039;";
		case '<':	return "&lt;";
		case '>':	return "&gt;";
	}
	return "";
}

#include "phpstring.c"

#endif
