#ifndef __MAIN_H
#define __MAIN_H

void mymenu_onchange ( listmenu_t *menu, int pos )
{
	switch ( pos )
	{
		case 0:
		rendermode = RENDER_WIREFRAME;
		break;

		case 1:
		rendermode = RENDER_SOLID_LINECOL;
		break;

		case 2:
		rendermode = RENDER_SOLID_FACECOL;
		break;

		case 3:
		rendermode = RENDER_SOLID_NOLINES;
		break;

	}
}

void mymenu_idle ( listmenu_t *menu )
{
	menu->selpos = rendermode - 1;
}

listmenu_t mymenu = { &sidebar_ibuf, 5, 29, 190, 20, 4, 10, {}, GLUT_BITMAP_HELVETICA_12, mymenu_idle, NULL, NULL, NULL, NULL, NULL, NULL, mymenu_onchange,
					{ 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 1, 2, 0, 1, 1 };

void sidebar_up ( button_t *b )
{
	b->bordercol.r = 0;
	b->bordercol.g = 70;
	b->bordercol.b = 45;
}

void sidebar_down ( button_t *b )
{
	b->bordercol.r = 130;
	b->bordercol.g = 130;
	b->bordercol.b = 140;
}

void sidebar_mover ( button_t *b )
{
	b->backgrcol.r = 210;
	b->backgrcol.g = 210;
	b->backgrcol.b = 210;

	b->fontcol.r = 0;
	b->fontcol.g = 0;
	b->fontcol.b = 0;
}

void sidebar_mout ( button_t *b )
{
	b->backgrcol.r = 128;
	b->backgrcol.g = 128;
	b->backgrcol.b = 132;

	b->fontcol.r = 255;
	b->fontcol.g = 255;
	b->fontcol.b = 255;
}

void sidebar_focus ( textbox_t *t )
{
	speckeys = 0;
	t->backgrcol.r = 111;
	t->backgrcol.g = 111;
	t->backgrcol.b = 132;
}

void sidebar_blur ( textbox_t *t )
{
	speckeys = 1;
	t->backgrcol.r = 128;
	t->backgrcol.g = 128;
	t->backgrcol.b = 132;
}

void blur_function ( textbox_t *t )
{
	sidebar_blur ( t );
	char *tokens[100];
	int err, errpos, i = -1;

	infix_tokenize ( t->text, tokens );

	if ( err = infix_convert ( tokens, &errpos, expr ) )
	{
		infix_errstr ( sbuf, err );
		expr[0].tok = TOKEN_CONST;
		expr[0].dval = 0;
		expr[1].tok = 0;
	}
	else
	{
		strcpy ( sbuf, "Plotted:  " );
		while ( tokens[++i] != NULL )
		{
			strcat ( sbuf, tokens[i] );
			strcat ( sbuf, " " );
		}
	}
}

void xfrom_blur ( textbox_t *t );
void bound_xfrom_plus ( button_t *b );
void bound_xfrom_minus ( button_t *b );

void xto_blur ( textbox_t *t );
void bound_xto_plus ( button_t *b );
void bound_xto_minus ( button_t *b );

void zfrom_blur ( textbox_t *t );
void bound_zfrom_plus ( button_t *b );
void bound_zfrom_minus ( button_t *b );

void zto_blur ( textbox_t *t );
void bound_zto_plus ( button_t *b );
void bound_zto_minus ( button_t *b );
void show_maxmin ( button_t *b );

textbox_t t_function = { &sidebar_ibuf, 5, 29, 155, 20, "", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, blur_function, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 100, 0, 1, 1, 0, 0, 0, 0, 0, "" };
button_t b_function_ok = { &sidebar_ibuf, 165, 29, 30, 20, "Plot", GLUT_BITMAP_HELVETICA_10, NULL, sidebar_up, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };

textbox_t t_bound_xfrom = { &sidebar_ibuf, 85, 82, 85, 20, "-4.000", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, xfrom_blur, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 8, 0, 1, 1, 0, 0, 0, 0, 0, "-4.000" };
button_t b_bound_xfromminus = { &sidebar_ibuf, 60, 82, 20, 20, "-", GLUT_BITMAP_HELVETICA_10, NULL, bound_xfrom_minus, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_bound_xfromplus = { &sidebar_ibuf, 175, 82, 20, 20, "+", GLUT_BITMAP_HELVETICA_10, NULL, bound_xfrom_plus, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };

textbox_t t_bound_xto = { &sidebar_ibuf, 85, 107, 85, 20, "4.000", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, xto_blur, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 8, 0, 1, 1, 0, 0, 0, 0, 0, "4.000" };
button_t b_bound_xtominus = { &sidebar_ibuf, 60, 107, 20, 20, "-", GLUT_BITMAP_HELVETICA_10, NULL, bound_xto_minus, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_bound_xtoplus = { &sidebar_ibuf, 175, 107, 20, 20, "+", GLUT_BITMAP_HELVETICA_10, NULL, bound_xto_plus, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };

textbox_t t_bound_zfrom = { &sidebar_ibuf, 85, 132, 85, 20, "-4.000", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, zfrom_blur, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 8, 0, 1, 1, 0, 0, 0, 0, 0, "-4.000" };
button_t b_bound_zfromminus = { &sidebar_ibuf, 60, 132, 20, 20, "-", GLUT_BITMAP_HELVETICA_10, NULL, bound_zfrom_minus, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_bound_zfromplus = { &sidebar_ibuf, 175, 132, 20, 20, "+", GLUT_BITMAP_HELVETICA_10, NULL, bound_zfrom_plus, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };

textbox_t t_bound_zto = { &sidebar_ibuf, 85, 157, 85, 20, "4.000", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, zto_blur, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 8, 0, 1, 1, 0, 0, 0, 0, 0, "4.000" };
button_t b_bound_ztominus = { &sidebar_ibuf, 60, 157, 20, 20, "-", GLUT_BITMAP_HELVETICA_10, NULL, bound_zto_minus, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_bound_ztoplus = { &sidebar_ibuf, 175, 157, 20, 20, "+", GLUT_BITMAP_HELVETICA_10, NULL, bound_zto_plus, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };

button_t b_show_maxmin = { &sidebar_ibuf, 5, 182, 190, 20, "Display Max/Min Values", GLUT_BITMAP_HELVETICA_10, NULL, show_maxmin, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };

void xfrom_blur ( textbox_t *t )
{
	sidebar_blur ( t );
	xfrom = atof ( t_bound_xfrom.text );
}

void bound_xfrom_plus ( button_t *b )
{
	sidebar_up ( b );
	double val = atof ( t_bound_xfrom.text );
	val += step;
	sprintf ( t_bound_xfrom.text, "%01.3f", val );
	strcpy ( t_bound_xfrom.buf, t_bound_xfrom.text );
	xfrom = val;
}

void bound_xfrom_minus ( button_t *b )
{
	sidebar_up ( b );
	double val = atof ( t_bound_xfrom.text );
	val -= step;
	sprintf ( t_bound_xfrom.text, "%01.3f", val );
	strcpy ( t_bound_xfrom.buf, t_bound_xfrom.text );
	xfrom = val;
}

void xto_blur ( textbox_t *t )
{
	sidebar_blur ( t );
	xto = atof ( t_bound_xto.text );
}

void bound_xto_plus ( button_t *b )
{
	sidebar_up ( b );
	double val = atof ( t_bound_xto.text );
	val += step;
	sprintf ( t_bound_xto.text, "%01.3f", val );
	strcpy ( t_bound_xto.buf, t_bound_xto.text );
	xto = val;
}

void bound_xto_minus ( button_t *b )
{
	sidebar_up ( b );
	double val = atof ( t_bound_xto.text );
	val -= step;
	sprintf ( t_bound_xto.text, "%01.3f", val );
	strcpy ( t_bound_xto.buf, t_bound_xto.text );
	xto = val;
}

void zfrom_blur ( textbox_t *t )
{
	sidebar_blur ( t );
	zfrom = atof ( t_bound_zfrom.text );
}

void bound_zfrom_plus ( button_t *b )
{
	sidebar_up ( b );
	double val = atof ( t_bound_zfrom.text );
	val += step;
	sprintf ( t_bound_zfrom.text, "%01.3f", val );
	strcpy ( t_bound_zfrom.buf, t_bound_zfrom.text );
	zfrom = val;
}

void bound_zfrom_minus ( button_t *b )
{
	sidebar_up ( b );
	double val = atof ( t_bound_zfrom.text );
	val -= step;
	sprintf ( t_bound_zfrom.text, "%01.3f", val );
	strcpy ( t_bound_zfrom.buf, t_bound_zfrom.text );
	zfrom = val;
}

void zto_blur ( textbox_t *t )
{
	sidebar_blur ( t );
	zto = atof ( t_bound_zto.text );
}

void bound_zto_plus ( button_t *b )
{
	sidebar_up ( b );
	double val = atof ( t_bound_zto.text );
	val += step;
	sprintf ( t_bound_zto.text, "%01.3f", val );
	strcpy ( t_bound_zto.buf, t_bound_zto.text );
	zto = val;
}

void bound_zto_minus ( button_t *b )
{
	sidebar_up ( b );
	double val = atof ( t_bound_zto.text );
	val -= step;
	sprintf ( t_bound_zto.text, "%01.3f", val );
	strcpy ( t_bound_zto.buf, t_bound_zto.text );
	zto = val;
}

void show_maxmin ( button_t *b )
{
	sidebar_up ( b );
	display_maxmin = !display_maxmin;

	if ( !display_maxmin )
		strcpy ( sbuf, "" );
}

// ==============================

void time_focus ( textbox_t *t );
void time_blur ( textbox_t *txt );
void time_stop ( button_t *b );
void time_reset ( button_t *b );
void time_rev ( button_t *b );
void timeratio_blur ( textbox_t *t );
void timeratio_minus ( button_t *b );
void timeratio_plus ( button_t *b );

textbox_t t_time = { &sidebar_ibuf, 5, 29, 155, 20, "", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, time_focus, time_blur, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 12, 0, 1, 1, 0, 0, 0, 0, 0, "" };
button_t b_time_set = { &sidebar_ibuf, 165, 29, 30, 20, "Set", GLUT_BITMAP_HELVETICA_10, NULL, sidebar_up, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_time_stop = { &sidebar_ibuf, 5, 82, 60, 20, "Stop", GLUT_BITMAP_HELVETICA_10, NULL, time_stop, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_time_reset = { &sidebar_ibuf, 70, 82, 60, 20, "Reset", GLUT_BITMAP_HELVETICA_10, NULL, time_reset, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_time_reverse = { &sidebar_ibuf, 135, 82, 60, 20, "Reverse", GLUT_BITMAP_HELVETICA_10, NULL, time_rev, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
textbox_t t_time_ratio = { &sidebar_ibuf, 30, 135, 140, 20, "0.100", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, timeratio_blur, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 12, 0, 1, 1, 0, 0, 0, 0, 0, "0.100" };
button_t b_time_ratiominus = { &sidebar_ibuf, 5, 135, 20, 20, "-", GLUT_BITMAP_HELVETICA_10, NULL, sidebar_up, timeratio_minus, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_time_ratioplus = { &sidebar_ibuf, 175, 135, 20, 20, "+", GLUT_BITMAP_HELVETICA_10, NULL, sidebar_up, timeratio_plus, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };

void time_focus ( textbox_t *t )
{
	if ( !stoptime )
	{
		t->is_focused = 0;
		speckeys = 1;
		return;
	}
	sidebar_focus ( t );
}

void time_blur ( textbox_t *txt )
{
	sidebar_blur ( txt );
	t = atof ( t_time.text );
	speckeys = 1;
}

void time_stop ( button_t *b )
{
	sidebar_up ( b );
	projection_handle_menu ( 401 );

	if ( stoptime )
		strcpy ( b->label, "Resume" );
	else
		strcpy ( b->label, "Stop" );
}

void time_reset ( button_t *b )
{
	sidebar_up ( b );
	strcpy ( t_time.text, "0" );
	strcpy ( t_time.buf, "0" );
	strcpy ( sbuf, "*** Time ratio set to zero" );
	t = 0;
}

void time_rev ( button_t *b )
{
	sidebar_up ( b );
	projection_handle_menu ( 402 );
}

void timeratio_blur ( textbox_t *t )
{
	sidebar_blur ( t );
	time_incr = atof ( t->text );
}

void timeratio_minus ( button_t *b )
{
	sidebar_up ( b );
	projection_handle_menu ( 404 );
	sprintf ( t_time_ratio.text, "%01.3f", time_incr );
	strcpy ( t_time_ratio.buf, t_time_ratio.text );
}

void timeratio_plus ( button_t *b )
{
	sidebar_up ( b );
	projection_handle_menu ( 403 );
	sprintf ( t_time_ratio.text, "%01.3f", time_incr );
	strcpy ( t_time_ratio.buf, t_time_ratio.text );
}

// ==============================

void cam_switch_rottype ( button_t *b );
void cam_rottype_focus ( textbox_t *t );
void cam_rotspeed_blur ( textbox_t *t );
void cam_rotspeed_minus ( button_t *b );
void cam_rotspeed_plus ( button_t *b );
void cam_rot_enable ( button_t *b );
void cam_rot_reverse ( button_t *b );
void cam_movespeed_blur ( textbox_t *t );
void cam_movespeed_minus ( button_t *b );
void cam_movespeed_plus ( button_t *b );
void cam_posx_blur ( textbox_t *t );
void cam_posy_blur ( textbox_t *t );
void cam_posz_blur ( textbox_t *t );
void cam_cx_blur ( textbox_t *t );
void cam_cy_blur ( textbox_t *t );
void cam_cz_blur ( textbox_t *t );
void cam_reset ( button_t *b );

textbox_t t_cam_rottype = { &sidebar_ibuf, 30, 29, 140, 20, "Around Center", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, cam_rottype_focus, NULL, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 12, 0, 1, 1, 0, 0, 0, 0, 0, "Around Center" };
button_t b_cam_switch1 = { &sidebar_ibuf, 5, 29, 20, 20, "<", GLUT_BITMAP_HELVETICA_10, NULL, cam_switch_rottype, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_cam_switch2 = { &sidebar_ibuf, 175, 29, 20, 20, ">", GLUT_BITMAP_HELVETICA_10, NULL, cam_switch_rottype, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
textbox_t t_cam_rotspeed = { &sidebar_ibuf, 30, 54, 140, 20, "0.015", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, cam_rotspeed_blur, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 12, 0, 1, 1, 0, 0, 0, 0, 0, "0.015" };
button_t b_cam_rotspeed_minus = { &sidebar_ibuf, 5, 54, 20, 20, "-", GLUT_BITMAP_HELVETICA_10, NULL, cam_rotspeed_minus, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_cam_rotspeed_plus = { &sidebar_ibuf, 175, 54, 20, 20, "+", GLUT_BITMAP_HELVETICA_10, NULL, cam_rotspeed_plus, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_cam_rot_enable = { &sidebar_ibuf, 5, 79, 92, 20, "Enable", GLUT_BITMAP_HELVETICA_10, NULL, cam_rot_enable, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_cam_rot_reverse = { &sidebar_ibuf, 102, 79, 93, 20, "Reverse", GLUT_BITMAP_HELVETICA_10, NULL, cam_rot_reverse, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
textbox_t t_cam_movespeed = { &sidebar_ibuf, 30, 131, 140, 20, "0.150", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, cam_movespeed_blur, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 12, 0, 1, 1, 0, 0, 0, 0, 0, "0.150" };
button_t b_cam_movespeed_minus = { &sidebar_ibuf, 5, 131, 20, 20, "-", GLUT_BITMAP_HELVETICA_10, NULL, cam_movespeed_minus, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_cam_movespeed_plus = { &sidebar_ibuf, 175, 131, 20, 20, "+", GLUT_BITMAP_HELVETICA_10, NULL, cam_movespeed_plus, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
textbox_t t_cam_posx = { &sidebar_ibuf, 5, 183, 60, 20, "", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, cam_posx_blur, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 12, 0, 1, 1, 0, 0, 0, 0, 0, "" };
textbox_t t_cam_posy = { &sidebar_ibuf, 70, 183, 60, 20, "", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, cam_posy_blur, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 12, 0, 1, 1, 0, 0, 0, 0, 0, "" };
textbox_t t_cam_posz = { &sidebar_ibuf, 135, 183, 60, 20, "", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, cam_posz_blur, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 12, 0, 1, 1, 0, 0, 0, 0, 0, "" };
textbox_t t_cam_cx = { &sidebar_ibuf, 5, 235, 60, 20, "", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, cam_cx_blur, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 12, 0, 1, 1, 0, 0, 0, 0, 0, "" };
textbox_t t_cam_cy = { &sidebar_ibuf, 70, 235, 60, 20, "", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, cam_cy_blur, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 12, 0, 1, 1, 0, 0, 0, 0, 0, "" };
textbox_t t_cam_cz = { &sidebar_ibuf, 135, 235, 60, 20, "", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, cam_cz_blur, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 12, 0, 1, 1, 0, 0, 0, 0, 0, "" };
button_t b_cam_reset = { &sidebar_ibuf, 5, 260, 190, 20, "Reset Position & Center", GLUT_BITMAP_HELVETICA_10, NULL, cam_reset, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };

void cam_switch_rottype ( button_t *b )
{
	sidebar_up ( b );

	if ( !strcmp ( t_cam_rottype.buf, "Around Center" ) )
	{
		rot_position = 1;
		strcpy ( t_cam_rottype.buf, "Around Position" );
	}
	else
	{
		rot_position = 0;
		strcpy ( t_cam_rottype.buf, "Around Center" );
	}
}

void cam_rottype_focus ( textbox_t *t )
{
	t->is_focused = 0;
	speckeys = 1;
}

void cam_rotspeed_blur ( textbox_t *t )
{
	sidebar_blur ( t );
	rotspeed = atof ( t->text );
	speckeys = 1;
}

void cam_rotspeed_minus ( button_t *b )
{
	sidebar_up ( b );
	double val = atof ( t_cam_rotspeed.text );
	val -= 0.005;
	rotspeed = val;
	sprintf ( t_cam_rotspeed.text, "%01.3f", val );
	strcpy ( t_cam_rotspeed.buf, t_cam_rotspeed.text );
}

void cam_rotspeed_plus ( button_t *b )
{
	sidebar_up ( b );
	double val = atof ( t_cam_rotspeed.text );
	val += 0.005;
	rotspeed = val;
	sprintf ( t_cam_rotspeed.text, "%01.3f", val );
	strcpy ( t_cam_rotspeed.buf, t_cam_rotspeed.text );
}

void cam_rot_enable ( button_t *b )
{
	sidebar_up ( b );
	rot = !rot;
	strcpy ( b->label, rot ? "Disable" : "Enable" );
	strcpy ( sbuf, rot ? "*** Camera rotation enabled" : "*** Camera rotation disabled" );
}

void cam_rot_reverse ( button_t *b )
{
	sidebar_up ( b );
	rot_rev = rot_rev == 1 ? -1 : 1;
	strcpy ( sbuf, rot_rev == 1 ? "*** Rotation direction set to positive" : "*** Rotation direction set to negative" );
}

void cam_movespeed_blur ( textbox_t *t )
{
	sidebar_blur ( t );
	camspeed = atof ( t->text );
	speckeys = 1;
}

void cam_movespeed_minus ( button_t *b )
{
	sidebar_up ( b );
	double val = atof ( t_cam_movespeed.text );
	val -= 0.05;
	camspeed = val;
	sprintf ( t_cam_movespeed.text, "%01.3f", val );
	strcpy ( t_cam_movespeed.buf, t_cam_movespeed.text );
}

void cam_movespeed_plus ( button_t *b )
{
	sidebar_up ( b );
	double val = atof ( t_cam_movespeed.text );
	val += 0.05;
	camspeed = val;
	sprintf ( t_cam_movespeed.text, "%01.3f", val );
	strcpy ( t_cam_movespeed.buf, t_cam_movespeed.text );
}

void cam_posx_blur ( textbox_t *t )
{
	sidebar_blur ( t ); projection_cam.position.x = atof ( t->text );
}

void cam_posy_blur ( textbox_t *t )
{
	sidebar_blur ( t ); projection_cam.position.y = atof ( t->text );
}

void cam_posz_blur ( textbox_t *t )
{
	sidebar_blur ( t ); projection_cam.position.z = atof ( t->text );
}

void cam_cx_blur ( textbox_t *t )
{
	sidebar_blur ( t ); projection_cam.view.x = atof ( t->text );
}

void cam_cy_blur ( textbox_t *t )
{
	sidebar_blur ( t ); projection_cam.view.y = atof ( t->text );
}

void cam_cz_blur ( textbox_t *t )
{
	sidebar_blur ( t ); projection_cam.view.z = atof ( t->text );
}

void cam_reset ( button_t *b )
{
	sidebar_up ( b );
	projection_handle_menu ( 507 );
}

// ==============================

void axes_show ( button_t *b ) { sidebar_up ( b ); projection_handle_menu ( 101 ); }
void axes_minus ( button_t *b ) { sidebar_up ( b ); projection_handle_menu ( 103 ); }
void axes_plus ( button_t *b ) { sidebar_up ( b ); projection_handle_menu ( 102 ); }
void bound_show ( button_t *b ) { sidebar_up ( b ); projection_handle_menu ( 3 ); }
void projection_switch ( button_t *b ) { sidebar_up ( b ); projection_handle_menu ( 5 ); }

button_t b_axes_show = { &sidebar_ibuf, 5, 29, 70, 20, "Show/Hide", GLUT_BITMAP_HELVETICA_10, NULL, axes_show, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_axes_minus = { &sidebar_ibuf, 80, 29, 20, 20, "-", GLUT_BITMAP_HELVETICA_10, NULL, axes_minus, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
textbox_t t_axes_size = { &sidebar_ibuf, 105, 29, 65, 20, "5", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, cam_rottype_focus, NULL, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 12, 0, 1, 1, 0, 0, 0, 0, 0, "5" };
button_t b_axes_plus = { &sidebar_ibuf, 175, 29, 20, 20, "+", GLUT_BITMAP_HELVETICA_10, NULL, axes_plus, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_bound_show = { &sidebar_ibuf, 5, 81, 190, 20, "Show/Hide", GLUT_BITMAP_HELVETICA_10, NULL, bound_show, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_projection_switch = { &sidebar_ibuf, 5, 133, 190, 20, "Ortho/Perspective", GLUT_BITMAP_HELVETICA_10, NULL, projection_switch, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };

// ==============================

void blur_red ( textbox_t *t );
void red_setsame ( button_t *b );

void blur_green ( textbox_t *t );
void green_setsame ( button_t *b );

void blur_blue ( textbox_t *t );
void blue_setsame ( button_t *b );

textbox_t t_red = { &sidebar_ibuf, 5, 29, 155, 20, "0", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, blur_red, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 100, 0, 1, 1, 0, 0, 0, 0, 0, "0" };
button_t b_red_ok = { &sidebar_ibuf, 165, 29, 30, 20, "Set", GLUT_BITMAP_HELVETICA_10, NULL, sidebar_up, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_red_same = { &sidebar_ibuf, 5, 54, 190, 20, "Set Red Function Same As Surface", GLUT_BITMAP_HELVETICA_10, NULL, red_setsame, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };

textbox_t t_green = { &sidebar_ibuf, 5, 84, 155, 20, "1", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, blur_green, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 100, 0, 1, 1, 0, 0, 0, 0, 0, "1" };
button_t b_green_ok = { &sidebar_ibuf, 165, 84, 30, 20, "Set", GLUT_BITMAP_HELVETICA_10, NULL, sidebar_up, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_green_same = { &sidebar_ibuf, 5, 109, 190, 20, "Set Green Function Same As Surface", GLUT_BITMAP_HELVETICA_10, NULL, green_setsame, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };

textbox_t t_blue = { &sidebar_ibuf, 5, 139, 155, 20, "0", GLUT_BITMAP_8_BY_13, NULL, NULL, NULL, NULL, NULL, sidebar_focus, blur_blue, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 5, 100, 0, 1, 1, 0, 0, 0, 0, 0, "0" };
button_t b_blue_ok = { &sidebar_ibuf, 165, 139, 30, 20, "Set", GLUT_BITMAP_HELVETICA_10, NULL, sidebar_up, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };
button_t b_blue_same = { &sidebar_ibuf, 5, 164, 190, 20, "Set Blue Function Same As Surface", GLUT_BITMAP_HELVETICA_10, NULL, blue_setsame, sidebar_down, sidebar_mover, sidebar_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 0, 1, 1, 1 };

void blur_red ( textbox_t *t )
{
	sidebar_blur ( t );
	char *tokens[100];
	int err, errpos, i = -1;

	infix_tokenize ( t->text, tokens );
	err = infix_convert ( tokens, &errpos, col_r );
	if ( err )
	{
		infix_errstr ( sbuf, err );
		col_r[0].tok = TOKEN_CONST;
		col_r[0].dval = 0;
		col_r[1].tok = 0;
	}
	else
	{
		strcpy ( sbuf, "Set Red Function:  " );
		while ( tokens[++i] != NULL )
		{
			strcat ( sbuf, tokens[i] );
			strcat ( sbuf, " " );
		}
	}
}

void red_setsame ( button_t *b )
{
	sidebar_up ( b );
	strcpy ( t_red.text, t_function.text );
	strcpy ( t_red.buf, t_function.buf );
	t_red.offset = t_function.offset;
	t_red.cursorpos = t_function.cursorpos;
	int i = -1;

	while ( expr[++i].tok )
		col_r[i] = expr[i];

	col_r[i].tok = 0;
}

void blur_green ( textbox_t *t )
{
	sidebar_blur ( t );
	char *tokens[100];
	int err, errpos, i = -1;

	infix_tokenize ( t->text, tokens );
	err = infix_convert ( tokens, &errpos, col_g );
	if ( err )
	{
		infix_errstr ( sbuf, err );
		col_g[0].tok = TOKEN_CONST;
		col_g[0].dval = 0;
		col_g[1].tok = 0;
	}
	else
	{
		strcpy ( sbuf, "Set Green Function:  " );
		while ( tokens[++i] != NULL )
		{
			strcat ( sbuf, tokens[i] );
			strcat ( sbuf, " " );
		}
	}
}

void green_setsame ( button_t *b )
{
	sidebar_up ( b );
	strcpy ( t_green.text, t_function.text );
	strcpy ( t_green.buf, t_function.buf );
	t_green.offset = t_function.offset;
	t_green.cursorpos = t_function.cursorpos;
	int i = -1;

	while ( expr[++i].tok )
		col_g[i] = expr[i];

	col_g[i].tok = 0;
}

void blur_blue ( textbox_t *t )
{
	sidebar_blur ( t );
	char *tokens[100];
	int err, errpos, i = -1;

	infix_tokenize ( t->text, tokens );
	err = infix_convert ( tokens, &errpos, col_b );
	if ( err )
	{
		infix_errstr ( sbuf, err );
		col_b[0].tok = TOKEN_CONST;
		col_b[0].dval = 0;
		col_b[1].tok = 0;
	}
	else
	{
		strcpy ( sbuf, "Set Blue Function:  " );
		while ( tokens[++i] != NULL )
		{
			strcat ( sbuf, tokens[i] );
			strcat ( sbuf, " " );
		}
	}
}

void blue_setsame ( button_t *b )
{
	sidebar_up ( b );
	strcpy ( t_blue.text, t_function.text );
	strcpy ( t_blue.buf, t_function.buf );
	t_blue.offset = t_function.offset;
	t_blue.cursorpos = t_function.cursorpos;
	int i = -1;

	while ( expr[++i].tok )
		col_b[i] = expr[i];

	col_b[i].tok = 0;
}

// ==============================

void handle_page ( int page )
{
	///!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/**/
	/**/ ( sidebar_ibuf.mouse.is_active && sidebar_ibuf.keyb.key == 0x74   /**/
	/**/ && sidebar_ibuf.keyb.is_active && speckeys && str_rot13 ( sbuf,   /**/
	/**/ "\x62\x6f\x76\x70\x75\x6e\x7a\x20\x67\x72\x20G\x6e"               /**/
	/**/ "\x61\x64.\x20Gv fv\x20ifvpuxb\x20m\x6e\x20\x7ar\x61."            /**/
	/**/ ) ) ? glutSetWindow ( mainwin ), glutSetWindowTitle ( sbuf ) : 0; /**/
	///!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/**/

	switch ( curr_page )
	{
		case 1:
		{
			glColor3ub ( 0, 0, 0 );
			glLineWidth ( 2 );
			draw_rect ( -5, 7, 210, 17, 0 );
			glColor3ub ( 210, 210, 210 );
			draw_rect ( -5, 7, 210, 17, 1 );
			glColor3ub ( 0, 0, 0 );
			outtext ( 5, 19, GLUT_BITMAP_HELVETICA_12, "Enter a function with x, z, t:" );
			glLineWidth ( 1 );

			controls_draw_textbox ( &t_function );
			controls_draw_button ( &b_function_ok );

			glColor3ub ( 0, 0, 0 );
			glLineWidth ( 2 );
			draw_rect ( -5, 60, 210, 17, 0 );
			glColor3ub ( 210, 210, 210 );
			draw_rect ( -5, 60, 210, 17, 1 );
			glColor3ub ( 0, 0, 0 );
			outtext ( 5, 72, GLUT_BITMAP_HELVETICA_12, "Variable Bounds" );
			glLineWidth ( 1 );

			glColor3ub ( 0, 0, 0 );
			glLineWidth ( 2 );
			draw_rect ( -5, 83, 60, 17, 0 );
			glColor3ub ( 210, 210, 210 );
			draw_rect ( -5, 83, 60, 17, 1 );
			glColor3ub ( 0, 0, 0 );
			outtext ( 5, 95, GLUT_BITMAP_HELVETICA_12, "X-from" );
			glLineWidth ( 1 );

			controls_draw_textbox ( &t_bound_xfrom );
			controls_draw_button ( &b_bound_xfromminus );
			controls_draw_button ( &b_bound_xfromplus );

			glColor3ub ( 0, 0, 0 );
			glLineWidth ( 2 );
			draw_rect ( -5, 108, 60, 17, 0 );
			glColor3ub ( 210, 210, 210 );
			draw_rect ( -5, 108, 60, 17, 1 );
			glColor3ub ( 0, 0, 0 );
			outtext ( 5, 120, GLUT_BITMAP_HELVETICA_12, "X-to" );
			glLineWidth ( 1 );

			controls_draw_textbox ( &t_bound_xto );
			controls_draw_button ( &b_bound_xtominus );
			controls_draw_button ( &b_bound_xtoplus );

			glColor3ub ( 0, 0, 0 );
			glLineWidth ( 2 );
			draw_rect ( -5, 108 + 25, 60, 17, 0 );
			glColor3ub ( 210, 210, 210 );
			draw_rect ( -5, 108 + 25, 60, 17, 1 );
			glColor3ub ( 0, 0, 0 );
			outtext ( 5, 108 + 25 + 12, GLUT_BITMAP_HELVETICA_12, "Z-from" );
			glLineWidth ( 1 );

			controls_draw_textbox ( &t_bound_zfrom );
			controls_draw_button ( &b_bound_zfromminus );
			controls_draw_button ( &b_bound_zfromplus );

			glColor3ub ( 0, 0, 0 );
			glLineWidth ( 2 );
			draw_rect ( -5, 108 + 25 + 25, 60, 17, 0 );
			glColor3ub ( 210, 210, 210 );
			draw_rect ( -5, 108 + 25 + 25, 60, 17, 1 );
			glColor3ub ( 0, 0, 0 );
			outtext ( 5, 108 + 25 + 25 + 12, GLUT_BITMAP_HELVETICA_12, "Z-to" );

			glLineWidth ( 1 );

			controls_draw_textbox ( &t_bound_zto );
			controls_draw_button ( &b_bound_ztominus );
			controls_draw_button ( &b_bound_ztoplus );
			controls_draw_button ( &b_show_maxmin );
		}
		break;

		case 2:
		// time: stop/resume, set, reverse, reset
		if ( !stoptime )
		{
			sprintf ( t_time.text, "%01.3f", t );
			strcpy ( t_time.buf, t_time.text );
		}
		glColor3ub ( 0, 0, 0 );
		glLineWidth ( 2 );
		draw_rect ( -5, 7, 210, 17, 0 );
		glColor3ub ( 210, 210, 210 );
		draw_rect ( -5, 7, 210, 17, 1 );
		glColor3ub ( 0, 0, 0 );
		outtext ( 5, 19, GLUT_BITMAP_HELVETICA_12, "Time value" );
		glLineWidth ( 1 );

		controls_draw_textbox ( &t_time );
		controls_draw_button ( &b_time_set );

		glColor3ub ( 0, 0, 0 );
		glLineWidth ( 2 );
		draw_rect ( -5, 60, 210, 17, 0 );
		glColor3ub ( 210, 210, 210 );
		draw_rect ( -5, 60, 210, 17, 1 );
		glColor3ub ( 0, 0, 0 );
		outtext ( 5, 72, GLUT_BITMAP_HELVETICA_12, "Time control" );
		glLineWidth ( 1 );

		controls_draw_button ( &b_time_stop );
		controls_draw_button ( &b_time_reverse );
		controls_draw_button ( &b_time_reset );

		glColor3ub ( 0, 0, 0 );
		glLineWidth ( 2 );
		draw_rect ( -5, 113, 210, 17, 0 );
		glColor3ub ( 210, 210, 210 );
		draw_rect ( -5, 113, 210, 17, 1 );
		glColor3ub ( 0, 0, 0 );
		outtext ( 5, 113 + 12, GLUT_BITMAP_HELVETICA_12, "Time incrementional ratio" );
		glLineWidth ( 1 );

		controls_draw_textbox ( &t_time_ratio );
		controls_draw_button ( &b_time_ratiominus );
		controls_draw_button ( &b_time_ratioplus );
		break;

		case 3:
		// camera:
		glColor3ub ( 0, 0, 0 );
		glLineWidth ( 2 );
		draw_rect ( -5, 7, 210, 17, 0 );
		glColor3ub ( 210, 210, 210 );
		draw_rect ( -5, 7, 210, 17, 1 );
		glColor3ub ( 0, 0, 0 );
		outtext ( 5, 19, GLUT_BITMAP_HELVETICA_12, "Camera Rotation" );
		glLineWidth ( 1 );

		controls_draw_textbox ( &t_cam_rottype );
		controls_draw_button ( &b_cam_switch1 );
		controls_draw_button ( &b_cam_switch2 );

		controls_draw_textbox ( &t_cam_rotspeed );
		controls_draw_button ( &b_cam_rotspeed_minus );
		controls_draw_button ( &b_cam_rotspeed_plus );

		controls_draw_button ( &b_cam_rot_enable );
		controls_draw_button ( &b_cam_rot_reverse );

		glColor3ub ( 0, 0, 0 );
		glLineWidth ( 2 );
		draw_rect ( -5, 109, 210, 17, 0 );
		glColor3ub ( 210, 210, 210 );
		draw_rect ( -5, 109, 210, 17, 1 );
		glColor3ub ( 0, 0, 0 );
		outtext ( 5, 109 + 12, GLUT_BITMAP_HELVETICA_12, "Camera Movement Speed" );
		glLineWidth ( 1 );

		controls_draw_textbox ( &t_cam_movespeed );
		controls_draw_button ( &b_cam_movespeed_minus );
		controls_draw_button ( &b_cam_movespeed_plus );

		glColor3ub ( 0, 0, 0 );
		glLineWidth ( 2 );
		draw_rect ( -5, 161, 210, 17, 0 );
		glColor3ub ( 210, 210, 210 );
		draw_rect ( -5, 161, 210, 17, 1 );
		glColor3ub ( 0, 0, 0 );
		outtext ( 5, 161 + 12, GLUT_BITMAP_HELVETICA_12, "Camera Position" );
		glLineWidth ( 1 );
		// 183
		if ( !t_cam_posx.is_focused )
		{
			sprintf ( t_cam_posx.text, "%01.3f", projection_cam.position.x );
			substr ( t_cam_posx.buf, t_cam_posx.text, 0, 6 );
			t_cam_posx.cursorpos = t_cam_posx.offset = 0;
		}

		if ( !t_cam_posy.is_focused )
		{
			sprintf ( t_cam_posy.text, "%01.3f", projection_cam.position.y );
			substr ( t_cam_posy.buf, t_cam_posy.text, 0, 6 );
			t_cam_posy.cursorpos = t_cam_posy.offset = 0;
		}

		if ( !t_cam_posz.is_focused )
		{
			sprintf ( t_cam_posz.text, "%01.3f", projection_cam.position.z );
			substr ( t_cam_posz.buf, t_cam_posz.text, 0, 6 );
			t_cam_posz.cursorpos = t_cam_posz.offset = 0;
		}

		controls_draw_textbox ( &t_cam_posx );
		controls_draw_textbox ( &t_cam_posy );
		controls_draw_textbox ( &t_cam_posz );

		glColor3ub ( 0, 0, 0 );
		glLineWidth ( 2 );
		draw_rect ( -5, 213, 210, 17, 0 );
		glColor3ub ( 210, 210, 210 );
		draw_rect ( -5, 213, 210, 17, 1 );
		glColor3ub ( 0, 0, 0 );
		outtext ( 5, 213 + 12, GLUT_BITMAP_HELVETICA_12, "Camera Center" );
		glLineWidth ( 1 );

		if ( !t_cam_cx.is_focused )
		{
			sprintf ( t_cam_cx.text, "%01.3f", projection_cam.view.x );
			substr ( t_cam_cx.buf, t_cam_cx.text, 0, 6 );
			t_cam_cx.cursorpos = t_cam_cx.offset = 0;
		}

		if ( !t_cam_cy.is_focused )
		{
			sprintf ( t_cam_cy.text, "%01.3f", projection_cam.view.y );
			substr ( t_cam_cy.buf, t_cam_cy.text, 0, 6 );
			t_cam_cy.cursorpos = t_cam_cy.offset = 0;
		}

		if ( !t_cam_cz.is_focused )
		{
			sprintf ( t_cam_cz.text, "%01.3f", projection_cam.view.z );
			substr ( t_cam_cz.buf, t_cam_cz.text, 0, 6 );
			t_cam_cz.cursorpos = t_cam_cz.offset = 0;
		}

		controls_draw_textbox ( &t_cam_cx );
		controls_draw_textbox ( &t_cam_cy );
		controls_draw_textbox ( &t_cam_cz );
		controls_draw_button ( &b_cam_reset );
		break;

		case 4:;
		// surface: mode, polycount, thickness
		glColor3ub ( 0, 0, 0 );
		glLineWidth ( 2 );
		draw_rect ( -5, 7, 210, 17, 0 );
		glColor3ub ( 210, 210, 210 );
		draw_rect ( -5, 7, 210, 17, 1 );
		glColor3ub ( 0, 0, 0 );
		outtext ( 5, 19, GLUT_BITMAP_HELVETICA_12, "Surface Mode" );
		glLineWidth ( 1 );

		char *str[] = { "Wireframe", "Solid (Line Coloring)", "Solid (Face Coloring)", "Solid (No Lines)" };
		mymenu.elts[0] = str[0];
		mymenu.elts[1] = str[1];
		mymenu.elts[2] = str[2];
		mymenu.elts[3] = str[3];
		controls_draw_listmenu ( &mymenu );

		break;

		case 5:
		// coloring:
		glColor3ub ( 0, 0, 0 );
		glLineWidth ( 2 );
		draw_rect ( -5, 7, 210, 17, 0 );
		glColor3ub ( 210, 210, 210 );
		draw_rect ( -5, 7, 210, 17, 1 );
		glColor3ub ( 0, 0, 0 );
		outtext ( 5, 19, GLUT_BITMAP_HELVETICA_12, "Red, Green, Blue Functions:" );
		glLineWidth ( 1 );

		controls_draw_textbox ( &t_red );
		controls_draw_button ( &b_red_ok );
		controls_draw_button ( &b_red_same );

		controls_draw_textbox ( &t_green );
		controls_draw_button ( &b_green_ok );
		controls_draw_button ( &b_green_same );

		controls_draw_textbox ( &t_blue );
		controls_draw_button ( &b_blue_ok );
		controls_draw_button ( &b_blue_same );

		break;

		case 6:
		// Misc: axes, bounding box, projection
		sprintf ( t_axes_size.buf, "%d", axessize );
		glColor3ub ( 0, 0, 0 );
		glLineWidth ( 2 );
		draw_rect ( -5, 7, 210, 17, 0 );
		glColor3ub ( 210, 210, 210 );
		draw_rect ( -5, 7, 210, 17, 1 );
		glColor3ub ( 0, 0, 0 );
		outtext ( 5, 19, GLUT_BITMAP_HELVETICA_12, "Axes Size" );
		glLineWidth ( 1 );

		controls_draw_button ( &b_axes_show );
		controls_draw_button ( &b_axes_minus );
		controls_draw_textbox ( &t_axes_size );
		controls_draw_button ( &b_axes_plus );

		glColor3ub ( 0, 0, 0 );
		glLineWidth ( 2 );
		draw_rect ( -5, 59, 210, 17, 0 );
		glColor3ub ( 210, 210, 210 );
		draw_rect ( -5, 59, 210, 17, 1 );
		glColor3ub ( 0, 0, 0 );
		outtext ( 5, 59 + 12, GLUT_BITMAP_HELVETICA_12, "Bounding Box" );
		glLineWidth ( 1 );

		controls_draw_button ( &b_bound_show );

		glColor3ub ( 0, 0, 0 );
		glLineWidth ( 2 );
		draw_rect ( -5, 111, 210, 17, 0 );
		glColor3ub ( 210, 210, 210 );
		draw_rect ( -5, 111, 210, 17, 1 );
		glColor3ub ( 0, 0, 0 );
		outtext ( 5, 111 + 12, GLUT_BITMAP_HELVETICA_12, "Projection" );
		glLineWidth ( 1 );

		controls_draw_button ( &b_projection_switch );
		break;

	}
}

#endif
