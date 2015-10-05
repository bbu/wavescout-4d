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
|   MODULE:  Main                                                   |
|     FILE:  main.c                                                 |
\__________________________________________________________________/

*/

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int rot = 0;
int speckeys = 1;
char sbuf[100];

#include "phpstring/phpstring.h"
#include "postfix_eval/infix_tokenizer.h"
#include "camera/camera.h"
#include "vector2/vector2.h"
#include "glut_controls/common.h"

#define WINDOW_TITLE "WaveScout 4D v1.0"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_GAP 4
#define SIDEBAR_WIDTH 200
#define MENUBAR_HEIGHT 24
#define STATUSBAR_HEIGHT 20

#define PROJECTION_MOUSE_SENSITIVITY .01

#define RENDER_WIREFRAME     1
#define RENDER_SOLID_LINECOL 2
#define RENDER_SOLID_FACECOL 3
#define RENDER_SOLID_NOLINES 4

#define LINEWIDTH_THIN       1
#define LINEWIDTH_MEDIUM     2
#define LINEWIDTH_THICK      3

double extr4 ( double a, double b, double c, double d, char min );
void num_bound ( int *num, int from, int to );

void projection_reshape ( int w, int h );
void projection_display ( void );
void motion ( int x, int y );
void mainwin_keyb ( int key, int x, int y );
void mainwin_display ( void );
void mainwin_reshape ( int w, int h );
void sidebar_display ( void );
void sidebar_reshape ( int w, int h );
void sidebar_mouse ( int button, int state, int x, int y );
void sidebar_pmotion ( int x, int y );
void sidebar_keyb ( unsigned char key, int x, int y );
void menubar_display ( void );
void menubar_reshape ( int w, int h );
void menubar_mouse ( int button, int state, int x, int y );
void menubar_pmotion ( int x, int y );
void projection_reshape ( int w, int h );
void projection_display ( void );
void projection_handle_menu ( int ch );
void statusbar_display ( void );
void statusbar_reshape ( int w, int h );

double varlist[3];

int orthomode = 0,
    fullscreen = 0,
    pmotion = 0,
    showaxes = 0,
    showcursor = 1,
    showbounds = 0,
    stoptime = 0,
    axessize = 4,
    rendermode = RENDER_WIREFRAME,
    linewidth = LINEWIDTH_THIN,
    curr_page = 1,
    rot_position = 0,
    rot_rev = 1,
    display_maxmin = 0,
    revtime = 0;

int mainwin,
    sidebar,
    menubar,
    projection,
    statusbar;

double time_incr = 0.1;

double extr4 ( double a, double b, double c, double d, char min )
{
	double all[] = { b, c, d };
	double extr = a;
	int i;

	for ( i = 0; i < 3; i++ )
	{
		if ( min ? all[i] < extr : all[i] > extr )
			extr = all[i];
	}
	return extr;
}

void num_bound ( int *num, int from, int to )
{
	if ( *num < from )
		*num = from;

	if ( *num > to )
		*num = to;
}

tokendata_t col_r[100], col_g[100], col_b[100];
tokendata_t expr[100];

float step = 0.4f, size = 4.0f, sens = 0.025f;
float xfrom = -4, zfrom = -4, xto = 4, zto = 4;
float t = 0.0f;
float rotspeed = 0.015f, camspeed = 0.15;

void button_mouseover ( button_t *b )
{
	b->is_transparent = 0;
}

void button_mouseout ( button_t *b )
{
	b->is_transparent = 1;
}

void button_mouseup ( button_t *b )
{
	b->y = 3;
}

void button_mousedown ( button_t *b )
{
	b->y = 4;
}

void menu_1 ( button_t *b )
{
	button_mouseup ( b );
	curr_page = 1;
}

void menu_2 ( button_t *b )
{
	button_mouseup ( b );
	curr_page = 2;
}

void menu_3 ( button_t *b )
{
	button_mouseup ( b );
	curr_page = 3;
}

void menu_4 ( button_t *b )
{
	button_mouseup ( b );
	curr_page = 4;
}

void menu_5 ( button_t *b )
{
	button_mouseup ( b );
	curr_page = 5;
}

void menu_6 ( button_t *b )
{
	button_mouseup ( b );
	curr_page = 6;
}

void menu_7 ( button_t *b )
{
	exit ( 0 );
}

void menu_mover ( button_t *b )
{
	button_mouseover ( b );
}

void menu_down ( button_t *b )
{
	button_mousedown ( b );
}

void menu_mout ( button_t *b )
{
	button_mouseout ( b );
}

inpbuffer_t sidebar_ibuf, menubar_ibuf;

button_t menubar_buttons[] =
{
	{ &menubar_ibuf, 5, 3, 80, 20, "Function", GLUT_BITMAP_HELVETICA_12, NULL, menu_1, menu_down, menu_mover, menu_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 1, 1, 1, 1 },
	{ &menubar_ibuf, 85 + 5, 3, 80, 20, "Time", GLUT_BITMAP_HELVETICA_12, NULL, menu_2, menu_down, menu_mover, menu_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 1, 1, 1, 1 },
	{ &menubar_ibuf, 165 + 10, 3, 80, 20, "Camera", GLUT_BITMAP_HELVETICA_12, NULL, menu_3, menu_down, menu_mover, menu_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 1, 1, 1, 1 },
	{ &menubar_ibuf, 245 + 15, 3, 80, 20, "Surface", GLUT_BITMAP_HELVETICA_12, NULL, menu_4, menu_down, menu_mover, menu_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 1, 1, 1, 1 },
	{ &menubar_ibuf, 325 + 20, 3, 80, 20, "Coloring", GLUT_BITMAP_HELVETICA_12, NULL, menu_5, menu_down, menu_mover, menu_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 1, 1, 1, 1 },
	{ &menubar_ibuf, 405 + 25, 3, 80, 20, "Misc", GLUT_BITMAP_HELVETICA_12, NULL, menu_6, menu_down, menu_mover, menu_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 1, 1, 1, 1 },
	{ &menubar_ibuf, 490 + 25, 3, 80, 20, "Quit", GLUT_BITMAP_HELVETICA_12, NULL, menu_7, menu_down, menu_mover, menu_mout, { 128, 128, 132 }, { 0, 70, 45 }, { 255, 255, 255 }, 1, 1, 1, 1, 1 },
	{ NULL }
};

camera_t projection_cam = {
	{ 0.f, 5.f, 5.f },
	{ 0.f, 0.f, 0.f },
	{ 0.f, 1.f, 0.f }
};

void projection_handle_menu ( int ch )
{
	switch ( ch )
	{
		case 101:
		showaxes = !showaxes;
		strcpy ( sbuf, showaxes ? "*** Toggled Axes ON" : "*** Toggled Axes OFF" );
		break;

		case 102:
		axessize++;
		sprintf ( sbuf, "*** Axes size increased to %d units", axessize );
		break;

		case 103:
		if ( axessize <= 1 )
			strcpy ( sbuf, "*** Axes size set to the minimum" );
		else
		{
			axessize--;
			sprintf ( sbuf, "*** Axes size decreased to %d units", axessize );
		}
		break;

		case 201:
		showcursor = !showcursor;
		glutSetCursor ( showcursor ? GLUT_CURSOR_CROSSHAIR : GLUT_CURSOR_NONE );
		strcpy ( sbuf, showcursor ? "*** Cursor Toggled ON" : "*** Cursor Toggled OFF" );
		break;

		case 202:
		pmotion = !pmotion;
		glutPassiveMotionFunc ( pmotion ? motion : NULL );
		strcpy ( sbuf, pmotion ? "*** Toggled Passive Motion ON" : "*** Toggled Passive Motion OFF" );
		break;

		case 203:
		sens += 0.005;
		sprintf ( sbuf, "*** Sensitivity ratio increased to %f", sens );
		break;

		case 204:
		if ( sens - 0.005 <= 0.01 )
			strcpy ( sbuf, "*** Sensitivity ratio set to the minimum" );
		else
		{
			sens -= 0.005;
			sprintf ( sbuf, "*** Sensitivity ratio decreased to %f", sens );
		}
		break;

		case 301:
		// WIREFRAME
		rendermode = RENDER_WIREFRAME;
		break;

		case 302:
		// LINE
		rendermode = RENDER_SOLID_LINECOL;
		break;

		case 303:
		// FACE
		rendermode = RENDER_SOLID_FACECOL;
		break;

		case 304:
		// SOLID
		rendermode = RENDER_SOLID_NOLINES;
		break;

		case 305:
		linewidth = LINEWIDTH_THIN;
		break;

		case 306:
		linewidth = LINEWIDTH_MEDIUM;
		break;

		case 307:
		linewidth = LINEWIDTH_THICK;
		break;

		case 401:
		stoptime = !stoptime;
		strcpy ( sbuf, stoptime ? "*** Time STOPPED" : "*** Time RESUMED" );
		break;

		case 402:
		stoptime = 0;
		revtime = !revtime;
		strcpy ( sbuf, revtime ? "*** Time direction set to negative" : "*** Time direction set to positive" );
		break;

		case 403:
		time_incr += 0.01f;
		sprintf ( sbuf, "*** Time ratio increased to %f", time_incr );
		break;

		case 404:
		time_incr -= 0.01f;
		sprintf ( sbuf, "*** Time ratio decreased to %f", time_incr );
		break;

		case 501:
		cam_setview ( &projection_cam, CAMERA_TOP );
		strcpy ( sbuf, "Camera view set to TOP" );
		break;

		case 502:
		cam_setview ( &projection_cam, CAMERA_BOTTOM );
		strcpy ( sbuf, "Camera view set to BOTTOM" );
		break;

		case 503:
		cam_setview ( &projection_cam, CAMERA_FRONT );
		strcpy ( sbuf, "Camera view set to FRONT" );
		break;

		case 504:
		cam_setview ( &projection_cam, CAMERA_REAR );
		strcpy ( sbuf, "Camera view set to REAR" );
		break;

		case 505:
		cam_setview ( &projection_cam, CAMERA_LEFT );
		strcpy ( sbuf, "Camera view set to LEFT" );
		break;

		case 506:
		cam_setview ( &projection_cam, CAMERA_RIGHT );
		strcpy ( sbuf, "Camera view set to RIGHT" );
		break;

		case 507:
		cam_set ( &projection_cam, 0., 5., 5., 0., 0., 0., 0., 1., 0. );
		break;

		case 0:
		break;

		case 1:
		strcpy ( sbuf, "" );
		break;

		case 2:
		break;

		case 3:
		showbounds = !showbounds;
		strcpy ( sbuf, showbounds ? "*** Toggled Bounding Box ON" : "*** Toggled Bounding Box OFF" );
		break;

		case 4:
		//stoptime = !stoptime;
		//strcpy ( sbuf, stoptime ? "*** Time STOPPED" : "*** Time RESUMED" );
		break;

		case 5:
		orthomode = !orthomode;
		glutSetWindow ( projection );
		projection_reshape ( glutGet ( GLUT_WINDOW_WIDTH ), glutGet ( GLUT_WINDOW_HEIGHT ) );
        glutSetWindow ( statusbar );
		strcpy ( sbuf, orthomode ? "*** Switched to Ortho projection" : "*** Switched to Perspective projection" );
		glutSetWindow ( sidebar );
		break;

		case 6:
		fullscreen = !fullscreen;
		glutSetWindow ( mainwin );
		mainwin_reshape ( glutGet ( GLUT_WINDOW_WIDTH ), glutGet ( GLUT_WINDOW_HEIGHT ) );
		break;

		case 999:
		strcpy ( sbuf, "" );
		break;

		case 1000:
		exit ( 0 );
		break;
	}
}

#include "main.h"

void motion ( int x, int y )
{
	static int lastx = ( WINDOW_WIDTH - SIDEBAR_WIDTH - WINDOW_GAP * 3 ) / 2;
	static int lasty = ( WINDOW_HEIGHT - MENUBAR_HEIGHT - STATUSBAR_HEIGHT - WINDOW_GAP * 3 ) / 2;
	int ydiff = y - lasty, xdiff = x - lastx;
	num_bound ( &ydiff, -16, 16 );
	num_bound ( &xdiff, -16, 16 );
	cam_rotateview ( &projection_cam, ( xdiff * sens ) / 4, CAMERA_Y );
	projection_cam.view.y += ( ydiff * sens ) * ( cosh ( 2 * ( atan ( ( projection_cam.view.y - projection_cam.position.y ) / hypot ( projection_cam.view.x - projection_cam.position.x, projection_cam.view.z - projection_cam.position.z ) ) ) ) );
	lastx = x, lasty = y;
}

void mainwin_keyb ( int key, int x, int y )
{
	if ( speckeys )
	{
		switch ( key )
		{
			case GLUT_KEY_LEFT:
			cam_strafe ( &projection_cam, -camspeed );
			break;

			case GLUT_KEY_RIGHT:
			cam_strafe ( &projection_cam, camspeed );
			break;

			case GLUT_KEY_DOWN:
			cam_movebetweenaxis ( &projection_cam, -camspeed, CAMERA_X, CAMERA_Z );
			break;

			case GLUT_KEY_UP:
			cam_movebetweenaxis ( &projection_cam, camspeed, CAMERA_X, CAMERA_Z );
			break;

			case GLUT_KEY_PAGE_UP:
			if ( !orthomode )
				cam_move ( &projection_cam, camspeed * 2 );
			else
				strcpy ( sbuf, "Zooming doesn't work in Ortho projection." );
			break;

			case GLUT_KEY_PAGE_DOWN:
			if ( !orthomode )
				cam_move ( &projection_cam, -camspeed * 2 );
			else
				strcpy ( sbuf, "Zooming doesn't work in Ortho projection." );
			break;

			case GLUT_KEY_F3:
			cam_movealongaxis ( &projection_cam, camspeed, CAMERA_Y );
			break;

			case GLUT_KEY_F4:
			cam_movealongaxis ( &projection_cam, -camspeed, CAMERA_Y );
			break;

			case GLUT_KEY_F5:
			cam_movealongaxis ( &projection_cam, camspeed, CAMERA_X );
			break;

			case GLUT_KEY_F6:
			cam_movealongaxis ( &projection_cam, -camspeed, CAMERA_X );
			break;

			case GLUT_KEY_F7:
			cam_movealongaxis ( &projection_cam, camspeed, CAMERA_Z );
			break;

			case GLUT_KEY_F8:
			cam_movealongaxis ( &projection_cam, -camspeed, CAMERA_Z );
			break;

			case GLUT_KEY_F9:
			size += step;
			break;

			case GLUT_KEY_F10:
			size -= step;
			break;

			case GLUT_KEY_F1:
			step += 0.1f;
			sprintf ( sbuf, "*** Surface step increased to %f", step );
			break;

			case GLUT_KEY_F2:
			if ( step - 0.1 >= 0.1 )
			{
				step -= 0.1f;
				sprintf ( sbuf, "*** Surface step decreased to %f", step );
			}
			break;
		}
	}
	else
	{
		sidebar_ibuf.keyspec.key = key;
		sidebar_ibuf.keyspec.x = x;
		sidebar_ibuf.keyspec.y = y;
		sidebar_ibuf.keyspec.is_active = 1;
	}
}

// ========= MAINWIN =============
void mainwin_display ( void )
{
	glClear ( GL_COLOR_BUFFER_BIT );
	glutSwapBuffers ( );
}

void mainwin_reshape ( int w, int h )
{
	glClearColor ( 0.37f, 0.46f, 0.54f, 1.0f );
	glViewport ( 0, 0, w, h );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ( );
	gluOrtho2D ( 0, w, h, 0 );

	if ( fullscreen )
	{
		glutSetWindow ( sidebar ); glutHideWindow ( );
		glutSetWindow ( statusbar ); glutHideWindow ( );
		glutSetWindow ( menubar ); glutHideWindow ( );
		glutSetWindow ( projection );
		glutPositionWindow ( 0, 0 );
		glutReshapeWindow ( w, h );
	}
	else
	{
		glMatrixMode ( GL_MODELVIEW );
		glutSetWindow ( sidebar ); glutShowWindow ( );
		glutReshapeWindow ( SIDEBAR_WIDTH, h - WINDOW_GAP * 2 - MENUBAR_HEIGHT );
		glutSetWindow ( statusbar ); glutShowWindow ( );
		glutPositionWindow ( SIDEBAR_WIDTH + WINDOW_GAP * 2, h - WINDOW_GAP - STATUSBAR_HEIGHT );
		glutReshapeWindow ( w - WINDOW_GAP * 3 - SIDEBAR_WIDTH, STATUSBAR_HEIGHT );
		glutSetWindow ( projection );
		glutReshapeWindow ( w - WINDOW_GAP * 3 - SIDEBAR_WIDTH, h - WINDOW_GAP * 3 - STATUSBAR_HEIGHT - MENUBAR_HEIGHT );
		glutPositionWindow ( SIDEBAR_WIDTH + WINDOW_GAP * 2, MENUBAR_HEIGHT + WINDOW_GAP );
		glutSetWindow ( menubar ); glutShowWindow ( );
		glutReshapeWindow ( w, MENUBAR_HEIGHT );
	}
}

// ========= SIDEBAR =============
void sidebar_display ( void )
{
	glClear ( GL_COLOR_BUFFER_BIT );

	int h = glutGet ( GLUT_WINDOW_HEIGHT );

	glLineWidth ( 2 );
	glBegin ( GL_LINES );
		glColor3f ( 0.0f, 0.0f, 0.0f );

		glVertex2i ( 0, 0 );
		glVertex2i ( SIDEBAR_WIDTH, 0 );

		glVertex2i ( SIDEBAR_WIDTH, 0 );
		glVertex2i ( SIDEBAR_WIDTH, h );

		glVertex2i ( SIDEBAR_WIDTH, h );
		glVertex2i ( 0, h );

		glVertex2i ( 0, h );
		glVertex2i ( 0, 0 );
	glEnd ( );
	glLineWidth ( 1 );

	handle_page ( curr_page );
	inp_reset ( &sidebar_ibuf );

	glutPostRedisplay ( );
	glutSwapBuffers ( );
}

void sidebar_reshape ( int w, int h )
{
	glClearColor ( 0.65f, 0.65f, 0.68f, 1.0f );
	glViewport ( 0, 0, w, h );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ( );
	gluOrtho2D ( 0, w, h, 0 );
	glMatrixMode ( GL_MODELVIEW );
}

void sidebar_mouse ( int button, int state, int x, int y )
{
	sidebar_ibuf.mouse.button = button;
	sidebar_ibuf.mouse.state = state;
	sidebar_ibuf.mouse.x = x;
	sidebar_ibuf.mouse.y = y;
	sidebar_ibuf.mouse.is_active = 1;
}

void sidebar_pmotion ( int x, int y )
{
	sidebar_ibuf.pmotion.x = x;
	sidebar_ibuf.pmotion.y = y;
	sidebar_ibuf.pmotion.is_active = 1;
}

void sidebar_keyb ( unsigned char key, int x, int y )
{
	sidebar_ibuf.keyb.key = key;
	sidebar_ibuf.keyb.x = x;
	sidebar_ibuf.keyb.y = y;
	sidebar_ibuf.keyb.is_active = 1;
}

// ========= MENUBAR =============
void menubar_display ( void )
{
	int w = glutGet ( GLUT_WINDOW_WIDTH ), offset;
	glClear ( GL_COLOR_BUFFER_BIT );
	glColor3f ( 0.0f, 0.0f, 0.0f );

	int i = -1;

	while ( menubar_buttons[++i].inp != NULL )
		controls_draw_button ( &menubar_buttons[i] );

	inp_reset ( &menubar_ibuf );
	glutPostRedisplay ( );
	glutSwapBuffers ( );
}

void menubar_reshape ( int w, int h )
{
	glClearColor ( 0.37f, 0.46f, 0.54f, 1.0f );
	glViewport ( 0, 0, w, h );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ( );
	gluOrtho2D ( 0, w, h, 0 );
	glMatrixMode ( GL_MODELVIEW );
}

void menubar_mouse ( int button, int state, int x, int y )
{
	menubar_ibuf.mouse.button = button;
	menubar_ibuf.mouse.state = state;
	menubar_ibuf.mouse.x = x;
	menubar_ibuf.mouse.y = y;
	menubar_ibuf.mouse.is_active = 1;
}

void menubar_pmotion ( int x, int y )
{
	menubar_ibuf.pmotion.x = x;
	menubar_ibuf.pmotion.y = y;
	menubar_ibuf.pmotion.is_active = 0;
}

// ========= PROJECTION =============
void projection_reshape ( int w, int h )
{
	glViewport ( 0, 0, w, h );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ( );
	orthomode ? glOrtho ( -w / ( ( w + h ) / 2. ) * 5., w / ( ( w + h ) / 2. ) * 5., -h / ( ( w + h ) / 2. ) * 5., h / ( ( w + h ) / 2. ) * 5., -100.0f, 100.0f ) : gluPerspective ( 45.0f, ( float ) w / ( float ) h, 0.01f, 100.0f );
	glMatrixMode ( GL_MODELVIEW );
	glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable ( GL_DEPTH_TEST );
}

void projection_display ( void )
{
	if ( !stoptime )
		t += revtime ? -time_incr : time_incr;

	varlist[0] = xfrom, varlist[1] = zfrom, varlist[2] = t;

	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if ( rot )
	{
		rot_position ? cam_rotatev ( &projection_cam, sgn ( rot_rev ) * rotspeed, 0, 1, 0 ) :
		cam_rotatearoundpoint ( &projection_cam, projection_cam.view, sgn ( rot_rev ) * rotspeed, 0, 1, 0 );
	}

	cam_update ( &projection_cam );
	register float x, z, y1, y2, y3, y4;
	vector3_t c1, c2, c3, c4;
	float maxval = postfix_eval ( expr, varlist ), minval = maxval, temp;
	int xsteps = 0, zsteps;

	glLineWidth ( linewidth );

	for ( x = xfrom; x <= xto; x += step )
	{
		xsteps++;
		zsteps = 0;

		varlist[0] = x, varlist[1] = zfrom;
		y1 = postfix_eval ( expr, varlist );
		c1 = vector3_mul ( vector3_add ( vector3_ratio ( vector3 ( postfix_eval ( col_r, varlist ), postfix_eval ( col_g, varlist ), postfix_eval ( col_b, varlist ) ) ), vector3 ( 1, 1, 1 ) ), .5 );

		varlist[0] = x + step, varlist[1] = zfrom;
		y2 = postfix_eval ( expr, varlist );
		c2 = vector3_mul ( vector3_add ( vector3_ratio ( vector3 ( postfix_eval ( col_r, varlist ), postfix_eval ( col_g, varlist ), postfix_eval ( col_b, varlist ) ) ), vector3 ( 1, 1, 1 ) ), .5 );

		for ( z = zfrom; z <= zto; z += step )
		{
			zsteps++;

			varlist[0] = x, varlist[1] = z + step;
			y3 = postfix_eval ( expr, varlist );
			c3 = vector3_mul ( vector3_add ( vector3_ratio ( vector3 ( postfix_eval ( col_r, varlist ), postfix_eval ( col_g, varlist ), postfix_eval ( col_b, varlist ) ) ), vector3 ( 1, 1, 1 ) ), .5 );

			varlist[0] = x + step, varlist[1] = z + step;
			y4 = postfix_eval ( expr, varlist );
			c4 = vector3_mul ( vector3_add ( vector3_ratio ( vector3 ( postfix_eval ( col_r, varlist ), postfix_eval ( col_g, varlist ), postfix_eval ( col_b, varlist ) ) ), vector3 ( 1, 1, 1 ) ), .5 );

			char linecol = ( rendermode == RENDER_SOLID_LINECOL || rendermode == RENDER_WIREFRAME );

			if ( rendermode != RENDER_SOLID_NOLINES )
			{
				glBegin ( GL_LINES );

				!linecol ? glColor3f ( 0.35, 0.45, 0.55 ) : 0;

				linecol ? glColor3f ( c1.x, c1.y, c1.z ) : 0;
				glVertex3f ( x, y1, z );
				linecol ? glColor3f ( c3.x, c3.y, c3.z ) : 0;
				glVertex3f ( x, y3, z + step );

				glVertex3f ( x, y3, z + step );
				linecol ? glColor3f ( c4.x, c4.y, c4.z ) : 0;
				glVertex3f ( x + step, y4, z + step );

				glVertex3f ( x + step, y4, z + step );
				linecol ? glColor3f ( c2.x, c2.y, c2.z ) : 0;
				glVertex3f ( x + step, y2, z );

				glVertex3f ( x + step, y2, z );
				linecol ? glColor3f ( c1.x, c1.y, c1.z ) : 0;
				glVertex3f ( x, y1, z );

				glEnd ( );
			}

			if ( rendermode != RENDER_WIREFRAME )
			{
				glBegin ( GL_QUADS );

				linecol ? glColor3f ( 0.35, 0.45, 0.55 ) : 0;

				!linecol ? glColor3f ( c1.x, c1.y, c1.z ) : 0;
				glVertex3f ( x, y1, z );
				!linecol ? glColor3f ( c3.x, c3.y, c3.z ) : 0;
				glVertex3f ( x, y3, z + step );
				!linecol ? glColor3f ( c4.x, c4.y, c4.z ) : 0;
				glVertex3f ( x + step, y4, z + step );
				!linecol ? glColor3f ( c2.x, c2.y, c2.z ) : 0;
				glVertex3f ( x + step, y2, z );

				glEnd ( );
			}

			if ( display_maxmin || showbounds )
			{
				if ( ( temp = extr4 ( y1, y2, y3, y4, 0 ) ) > maxval )
					maxval = temp;

				if ( ( temp = extr4 ( y1, y2, y3, y4, 1 ) ) < minval )
					minval = temp;

			}
			y1 = y3, y2 = y4, c1 = c3, c2 = c4;
		}
	}

	if ( showaxes )
	{
		glLineWidth ( LINEWIDTH_THICK );
		glBegin ( GL_LINES );
			glColor3f ( 1.0f, 0.0f, 0.0f );
			glVertex3f ( 0.0f, 0.0f, 0.0f ); glVertex3f ( axessize * step, 0.0f, 0.0f );

			glColor3f ( 0.0f, 1.0f, 0.0f );
			glVertex3f ( 0.0f, 0.0f, 0.0f ); glVertex3f ( 0.0f, axessize * step, 0.0f );

			glColor3f ( 0.0f, 0.0f, 1.0f );
			glVertex3f ( 0.0f, 0.0f, 0.0f ); glVertex3f ( 0.0f, 0.0f, axessize * step );
		glEnd ( );
	}

	if ( showbounds )
    {
		glLineWidth ( LINEWIDTH_MEDIUM );
  		glBegin ( GL_LINES );
			glColor3f ( 1.0f, 1.0f, 1.0f );

			float xend = xfrom + xsteps * step, zend = zfrom + zsteps * step;

			glVertex3f ( xfrom, minval, zfrom ); glVertex3f ( xend, minval, zfrom );
			glVertex3f ( xfrom, minval, zend ); glVertex3f ( xend, minval, zend );
			glVertex3f ( xfrom, minval, zfrom ); glVertex3f ( xfrom, minval, zend );
			glVertex3f ( xend, minval, zfrom ); glVertex3f ( xend, minval, zend );

			glVertex3f ( xfrom, minval, zend ); glVertex3f ( xfrom, maxval, zend );
			glVertex3f ( xfrom, minval, zfrom ); glVertex3f ( xfrom, maxval, zfrom );
			glVertex3f ( xend, minval, zend ); glVertex3f ( xend, maxval, zend );
			glVertex3f ( xend, minval, zfrom ); glVertex3f ( xend, maxval, zfrom );

			glVertex3f ( xfrom, maxval, zfrom ); glVertex3f ( xend, maxval, zfrom );
			glVertex3f ( xfrom, maxval, zend ); glVertex3f ( xend, maxval, zend );
			glVertex3f ( xfrom, maxval, zfrom ); glVertex3f ( xfrom, maxval, zend );
			glVertex3f ( xend, maxval, zfrom ); glVertex3f ( xend, maxval, zend );

		glEnd ( );
	}

	if ( display_maxmin )
		sprintf ( sbuf, "Min Value: %f; Max Value: %f", minval, maxval );

	glutSwapBuffers ( );
	glutPostRedisplay ( );
}

// ========= STATUSBAR =============
void statusbar_display ( void )
{
	glClear ( GL_COLOR_BUFFER_BIT );
	outtext ( 4, 13, GLUT_BITMAP_HELVETICA_12, sbuf );
	glutPostRedisplay ( );
	glutSwapBuffers ( );
}

void statusbar_reshape ( int w, int h )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
	glViewport ( 0, 0, w, h );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ( );
	gluOrtho2D ( 0, w, h, 0 );
	glMatrixMode ( GL_MODELVIEW );
}

void menus_create ( void )
{
		int sub_axes = glutCreateMenu ( projection_handle_menu );
		glutAddMenuEntry ( "&Show/Hide", 101 );
		glutAddMenuEntry ( "&Increase Length", 102 );
		glutAddMenuEntry ( "&Decrease Length", 103 );

		int sub_mouse = glutCreateMenu ( projection_handle_menu );
		glutAddMenuEntry ( "&Show/Hide Cursor", 201 );
		glutAddMenuEntry ( "&Toggle Passive Motion On/Off", 202 );
		glutAddMenuEntry ( "&Increase Sensitivity", 203 );
		glutAddMenuEntry ( "&Decrease Sensitivity", 204 );

			int sub_surface_linewidth = glutCreateMenu ( projection_handle_menu );
			glutAddMenuEntry ( "&Thin", 305 );
			glutAddMenuEntry ( "&Medium", 306 );
			glutAddMenuEntry ( "Thic&k", 307 );

   		int sub_surface = glutCreateMenu ( projection_handle_menu );
		glutAddMenuEntry ( "&Wireframe", 301 );
		glutAddMenuEntry ( "Solid (&Line coloring)", 302 );
		glutAddMenuEntry ( "Solid (&Face coloring)", 303 );
		glutAddMenuEntry ( "&Solid (No Lines)", 304 );
		glutAddSubMenu ( "Line &Thickness", sub_surface_linewidth );

		int sub_time = glutCreateMenu ( projection_handle_menu );
		glutAddMenuEntry ( "&Stop/Resume", 401 );
		glutAddMenuEntry ( "&Reverse", 402 );
		glutAddMenuEntry ( "&Increase Ratio", 403 );
		glutAddMenuEntry ( "&Decrease Ratio", 404 );

			int sub_camera_views = glutCreateMenu ( projection_handle_menu );
			glutAddMenuEntry ( "&Top", 501 );
			glutAddMenuEntry ( "&Bottom", 502 );
			glutAddMenuEntry ( "&Front", 503 );
			glutAddMenuEntry ( "R&ear", 504 );
			glutAddMenuEntry ( "&Left", 505 );
			glutAddMenuEntry ( "&Right", 506 );

			/*int sub_camera_movement = glutCreateMenu ( projection_handle_menu );
			glutAddMenuEntry ( "----- GENERAL MOVEMENT -----", 100 );
			glutAddMenuEntry ( "Move Forward (UP Arrow)", 100 );
			glutAddMenuEntry ( "Move Backward (DOWN Arrow)", 100 );
			glutAddMenuEntry ( "Strafe Left (LEFT Arrow)", 100 );
			glutAddMenuEntry ( "Strafe Right (Right Arrow)", 100 );
			glutAddMenuEntry ( "Zoom In (PageUp)", 100 );
			glutAddMenuEntry ( "Zoom Out (PageDown)", 100 );
			glutAddMenuEntry ( "", 100 );
			glutAddMenuEntry ( "----- MOVEMENT ALONG AXIS -----", 100 );
			glutAddMenuEntry ( "Move Forward Along X (F3)", 100 );
			glutAddMenuEntry ( "Move Backward Along X (F4)", 100 );
			glutAddMenuEntry ( "Elevate Up Around Y (F5)", 100 );
			glutAddMenuEntry ( "Elevate Down Around Y (F6)", 100 );
			glutAddMenuEntry ( "Move Forward Along Z (F7)", 100 );
			glutAddMenuEntry ( "Move Backward Along Z (F8)", 100 );*/

		int sub_camera = glutCreateMenu ( projection_handle_menu );
		glutAddSubMenu ( "Set &View", sub_camera_views );
		glutAddMenuEntry ( "&Reset", 507 );

	int main_menu = glutCreateMenu ( projection_handle_menu );
	glutAddSubMenu ( "&Axes", sub_axes );
	glutAddSubMenu ( "&Mouse", sub_mouse );
	glutAddSubMenu ( "&Camera", sub_camera );
	glutAddSubMenu ( "&Time", sub_time );
	glutAddSubMenu ( "&Surface Mode", sub_surface );
	glutAddMenuEntry ( "_____________________________", 100 );
	glutAddMenuEntry ( "Switch Ortho/&Perspective projection", 5 );
	glutAddMenuEntry ( "Toggle &Bounding Box On/Off", 3 );
	glutAddMenuEntry ( "&Enlarge/Restore projection window", 6 );
	glutAddMenuEntry ( "_____________________________", 100 );
	glutAddMenuEntry ( "C&lear Statusbar", 999 );
	glutAddMenuEntry ( "&Quit", 1000 );
	glutAttachMenu ( GLUT_RIGHT_BUTTON );
}

int main ( int argc, char **argv )
{
	expr[0].tok = TOKEN_CONST, expr[0].dval = 0;
	expr[1].tok = 0;

	col_r[0].tok = TOKEN_CONST, col_r[0].dval = 0;
	col_r[1].tok = 0;

	col_g[0].tok = TOKEN_CONST, col_g[0].dval = 1;
	col_g[1].tok = 0;

	col_b[0].tok = TOKEN_CONST, col_b[0].dval = 0;
	col_b[1].tok = 0;

	strcpy ( sbuf, "WaveScout 4D v1.0        Right-click on the projection for the menu." );
	glutInit ( &argc, argv );
	glutInitWindowSize ( WINDOW_WIDTH, WINDOW_HEIGHT );
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB );

	mainwin = glutCreateWindow ( WINDOW_TITLE );
	glutDisplayFunc ( mainwin_display );
	glutReshapeFunc ( mainwin_reshape );
	glutSpecialFunc ( mainwin_keyb );
	glutKeyboardFunc ( sidebar_keyb );

	menubar = glutCreateSubWindow ( mainwin,
		0,
		0,
		WINDOW_WIDTH,
		MENUBAR_HEIGHT
	);
	glutDisplayFunc ( menubar_display );
	glutReshapeFunc ( menubar_reshape );
	glutMouseFunc ( menubar_mouse );
	glutPassiveMotionFunc ( menubar_pmotion );

	sidebar = glutCreateSubWindow ( mainwin,
		WINDOW_GAP,
		MENUBAR_HEIGHT + WINDOW_GAP,
		SIDEBAR_WIDTH,
		WINDOW_HEIGHT - WINDOW_GAP * 2 - MENUBAR_HEIGHT
	);
	glutDisplayFunc ( sidebar_display );
	glutReshapeFunc ( sidebar_reshape );
	glutMouseFunc ( sidebar_mouse );
	//glutKeyboardFunc ( sidebar_keyb );
	glutPassiveMotionFunc ( sidebar_pmotion );

	statusbar = glutCreateSubWindow ( mainwin,
		SIDEBAR_WIDTH + WINDOW_GAP * 2,
		WINDOW_HEIGHT - WINDOW_GAP - STATUSBAR_HEIGHT,
		WINDOW_WIDTH - WINDOW_GAP * 3 - SIDEBAR_WIDTH,
		STATUSBAR_HEIGHT
	);
	glutDisplayFunc ( statusbar_display );
	glutReshapeFunc ( statusbar_reshape );

	projection = glutCreateSubWindow ( mainwin,
		SIDEBAR_WIDTH + WINDOW_GAP * 2,
		MENUBAR_HEIGHT + WINDOW_GAP,
		WINDOW_WIDTH - WINDOW_GAP * 3 - SIDEBAR_WIDTH,
		WINDOW_HEIGHT - WINDOW_GAP * 3 - STATUSBAR_HEIGHT - MENUBAR_HEIGHT
	);
	glutDisplayFunc ( projection_display );
	glutReshapeFunc ( projection_reshape );
	glutMotionFunc ( motion );
	glutCreateMenu ( projection_handle_menu );
	glutSetCursor ( GLUT_CURSOR_CROSSHAIR );
	menus_create ( );
	glutMainLoop ( );
	return 0;
}
