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
|     FILE:  phpstring.c                                            |
\__________________________________________________________________/

*/

char *ltrim ( char *dst, const char *src )
{
	int pos = -1, len = strlen ( src ), i;

	while ( IS_WHITESPACE ( src[++pos] ) );

	int end = len - pos;

	for ( i = 0; i < end; i++ )
		dst[i] = src[i + pos];

	dst[i] = '\0';
	return dst;
}

char *rtrim ( char *dst, const char *src )
{
	int pos = strlen ( src ), len = pos, i;

	while ( IS_WHITESPACE ( src[--pos] ) );

	for ( i = 0; i <= pos; i++ )
		dst[i] = src[i];

	dst[i] = '\0';
	return dst;
}

char *trim ( char *dst, const char *src )
{
	return rtrim ( ltrim ( dst, src ), dst );
}

char *tight ( char *dst, const char *src )
{
	int pos = -1, len = strlen ( src ), i;
	strcpy ( dst, src );

	while ( ++pos < len )
	{
		if ( dst[pos] == ' ' && dst[pos + 1] == ' ' )
		{
			for ( i = pos; i < len; i++ )
				dst[i] = dst[i + 1];

			pos--;
			len--;
		}
	}
	return trim ( dst, dst );
}

char *substr ( char *dst, const char *src, int pos, int len )
{
	int len_src = strlen ( src ), i, j;

	if ( !len_src )
	{
		strcpy ( dst, "" );
		return dst;
	}

	if ( pos < 0 )
		pos = 0;

	if ( pos > len_src )
		pos = len_src;

	int pos_end = pos + len;

	if ( pos_end < 0 )
		pos_end = 0;

	if ( pos_end > len_src )
		pos_end = len_src;

	if ( pos > pos_end )
	{
		int temp;
		temp = pos;
		pos = pos_end;
		pos_end = temp;
	}

	for ( i = pos, j = 0; i < pos_end; i++, j++ )
		dst[j] = src[i];

	dst[j] = '\0';
	return dst;
}

char *substr_replace ( char *dst, const char *src, const char *rpl, int pos, int len )
{
	int len_src = strlen ( src ), len_rpl = strlen ( rpl ), i, j, k;

	if ( !len_src && !len_rpl )
	{
		strcpy ( dst, "" );
		return dst;
	}

	if ( pos < 0 )
		pos = 0;

	if ( pos > len_src )
		pos = len_src;

	if ( len < 0 )
	{
		len = -len;
		if ( pos - len > 0 )
			pos -= len;
		else
		{
			len = pos;
			pos = 0;
		}
	}

	int pos_end = pos + len;

	if ( pos_end > len_src )
		pos_end = len_src;

	len = pos_end - pos;

	int len_new = len_src + ( len_rpl - len );

	for ( i = 0, j = 0; i < len_new; i++, j++ )
	{
		if ( i == pos )
		{
			for ( k = 0; k < len_rpl; k++ )
				dst[i + k] = rpl[k];

			i += len_rpl;

			for ( ; i < len_new; i++, j++ )
				dst[i] = src[j + len];

			break;
		}
		else
			dst[i] = src[j];
	}
	dst[len_new] = '\0';
	return dst;
}

char *str_replace ( char *dst, const char *src, const char *ndl, const char *rpl )
{
	int len_src = strlen ( src ), len_ndl = strlen ( ndl ), len_rpl = strlen ( rpl ), i, j, k;

	if ( !len_ndl || ( len_ndl > len_src ) )
	{
		strcpy ( dst, src );
		return dst;
	}

	for ( i = 0, j = 0; j < len_src; i++, j++ )
	{
		for ( k = 0; k < len_ndl; k++ )
		{
			if ( src[j + k] == ndl[k] )
			{
				if ( k == len_ndl - 1 )
				{
					for ( k = 0; k < len_rpl; k++ )
						dst[i + k] = rpl[k];

					i += len_rpl - 1;
					j += len_ndl - 1;

					break;
				}
			}
			else
			{
				dst[i] = src[j];
				break;
			}
		}
	}
	dst[i] = '\0';
	return dst;
}

char *str_repeat ( char *dst, const char *src, int mul )
{
	if ( mul > 1 )
	{
		int len = strlen ( src ), i = -1, j;

		while ( ++i < mul )
		{
			for ( j = 0; j < len; j++ )
				dst[i * len + j] = src[j];
		}
		dst[i * len] = '\0';
	}
	else if ( mul == 1 )
		strcpy ( dst, src );
	else
		strcpy ( dst, "" );

	return dst;
}

char *str_shuffle ( char *dst, const char *src )
{
	int len = strlen ( src ), i;
	strcpy ( dst, src );

	if ( len > 1 )
	{
		char tmp = src[0];

		for ( i = 1; i < len; i++ )
		{
			if ( src[i] == tmp )
				tmp = src[i];
			else
			{
				int pos;

				srand ( time ( NULL ) - rand ( ) );
				do
				{
					for ( i = 0; i < len; i += ( pos % 2 ) ? 2 : 1 )
					{
						pos = rand ( ) % len;
						if ( pos != i )
						{
							tmp = dst[i];
							dst[i] = dst[pos];
							dst[pos] = tmp;
						}
					}
				} while ( !strcmp ( dst, src ) );

				return dst;
			}
		}
	}
	return dst;
}

char *str_rot13 ( char *dst, const char *src )
{
	int len = strlen ( src ), i;

	for ( i = 0; i < len; i++ )
	{
		if ( ( src[i] >= 'a' && src[i] <= 'm' ) || ( src[i] >= 'A' && src[i] <= 'M' ) )
			dst[i] = src[i] + 13;
		else if ( ( src[i] >= 'n' && src[i] <= 'z' ) || ( src[i] >= 'N' && src[i] <= 'Z' ) )
			dst[i] = src[i] - 13;
		else
			dst[i] = src[i];
	}
	dst[len] = '\0';
	return dst;
}

char *str_pad ( char *dst, const char *src, const char *pad, int len, int mode )
{
	int len_src = strlen ( src ), len_pad = strlen ( pad ), i, j;

	if ( len <= len_src || !len_pad )
	{
		strcpy ( dst, src );
		return dst;
	}

	int diff = len - len_src;

	switch ( mode )
	{
		case STR_PAD_LEFT:
		case STR_PAD_RIGHT:
		default:
		{
			for ( i = 0; i < len; i++ )
			{
				if ( i < ( ( mode == STR_PAD_LEFT ) ? diff : len_src ) )
					dst[i] = ( mode == STR_PAD_LEFT ) ? pad[i % len_pad] : src[i];
				else
				{
					for ( j = 0; i < len; i++, j++ )
						dst[i] = ( mode == STR_PAD_LEFT ) ? src[j] : pad[j % len_pad];

					dst[len] = '\0';
					return dst;
				}
			}
		}
		break;

		case STR_PAD_BOTH:
		{
			int tmp = diff / 2, pos_beg = tmp, pos_end = ( diff % 2 ) ? pos_beg + len_src : len - pos_beg;

			for ( i = 0; i < pos_beg; i++ )
				dst[i] = pad[i % len_pad];

			for ( j = 0; i < pos_end; i++, j++ )
				dst[i] = src[j];

			for ( j = 0; i < len; i++, j++ )
				dst[i] = pad[j % len_pad];

			dst[len] = '\0';
			return dst;
		}
		break;
	}
}

char *htmlspecialchars ( char *dst, const char *src, int mode )
{
	int len_src = strlen ( src ), len_ent, i, j, k;

	for ( i = 0, j = 0; j < len_src; i++, j++ )
	{
		if ( IS_HTML_ENTITY ( src[j], mode ) )
		{
			len_ent = strlen ( HTML_TRANS ( src[j] ) );

			for ( k = 0; k < len_ent; k++ )
				dst[i + k] = HTML_TRANS ( src[j] ) [k];

			i += len_ent - 1;
		}
		else
			dst[i] = src[j];
	}
	dst[i] = '\0';
	return dst;
}

int substr_count ( const char *hay, const char *ndl )
{
	int len_hay = strlen ( hay ), len_ndl = strlen ( ndl ), cnt = 0, i, j;

	if ( ( !len_hay || !len_ndl ) || ( len_hay < len_ndl ) )
		return 0;

	for ( i = 0; i < len_hay - len_ndl + 1; i++ )
	{
		for ( j = 0; j < len_ndl; j++ )
		{
			if ( hay[i + j] == ndl[j] )
			{
				if ( j == len_ndl - 1 )
				{
					cnt++;
					i += j;
 				}
			}
			else
				break;
		}
	}
	return cnt;
}

int strpos ( const char *hay, const char *ndl )
{
	int len_hay = strlen ( hay ), len_ndl = strlen ( ndl ), i, j;

	if ( ( !len_hay || !len_ndl ) || ( len_hay < len_ndl ) )
		return -1;

	for ( i = 0; i < len_hay - len_ndl + 1; i++ )
	{
		for ( j = 0; j < len_ndl; j++ )
		{
			if ( hay[i + j] == ndl[j] )
			{
				if ( j == len_ndl - 1 )
					return i;
			}
			else
				break;
		}
	}
	return -1;
}

int strrpos ( const char *hay, const char *ndl )
{
	int len_hay = strlen ( hay ), len_ndl = strlen ( ndl ), i, j;

	if ( ( !len_hay || !len_ndl ) || ( len_hay < len_ndl ) )
		return -1;

	for ( i = len_hay - len_ndl; i >= 0; i-- )
	{
		for ( j = 0; j < len_ndl; j++ )
		{
			if ( hay[i + j] == ndl[j] )
			{
				if ( j == len_ndl - 1 )
					return i;
			}
			else
				break;
		}
	}
	return -1;
}
