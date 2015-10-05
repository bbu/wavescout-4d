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
|   MODULE:  Camera Manipulation Functions                          |
|     FILE:  camera.c                                               |
\__________________________________________________________________/

*/

void cam_set ( camera_t *cam, VECTOR3_ELT px, VECTOR3_ELT py, VECTOR3_ELT pz, VECTOR3_ELT vx, VECTOR3_ELT vy, VECTOR3_ELT vz, VECTOR3_ELT ux, VECTOR3_ELT uy, VECTOR3_ELT uz )
{
	cam->position = vector3 ( px, py, pz );
	cam->view = vector3 ( vx, vy, vz );
	cam->up = vector3 ( ux, uy, uz );
}

void cam_rotateview ( camera_t *cam, VECTOR3_ELT theta, short axis )
{
	vector3_t view = vector3_sub ( cam->view, cam->position );
	VECTOR3_ELT radius, angle;

	switch ( axis )
	{
		case CAMERA_X:
			radius = hypot ( view.y, view.z ), angle = atan2 ( view.z, view.y ) + theta;
			view.y = radius * cos ( angle );
			view.z = radius * sin ( angle );
			break;

		case CAMERA_Y:
			radius = hypot ( view.x, view.z ), angle = atan2 ( view.z, view.x ) + theta;
			view.x = radius * cos ( angle );
			view.z = radius * sin ( angle );
			break;

		case CAMERA_Z:
			radius = hypot ( view.y, view.x ), angle = atan2 ( view.x, view.y ) + theta;
			view.y = radius * cos ( angle );
			view.x = radius * sin ( angle );
			break;
    }
	cam->view = vector3_add ( cam->position, view );
}

void cam_rotatev ( camera_t *cam, VECTOR3_ELT theta, VECTOR3_ELT x, VECTOR3_ELT y, VECTOR3_ELT z )
{
	vector3_t view = vector3_sub ( cam->view, cam->position ), rotated;

	VECTOR3_ELT _cos = ( VECTOR3_ELT ) cos ( theta );
	VECTOR3_ELT _sin = ( VECTOR3_ELT ) sin ( theta );

	rotated.x = ( _cos + ( 1 - _cos ) * x * x ) * view.x + ( ( 1 - _cos ) * x * y - z * _sin ) * view.y + ( ( 1 - _cos ) * x * z + y * _sin ) * view.z;
	rotated.y = ( ( 1 - _cos ) * x * y + z * _sin ) * view.x + ( _cos + ( 1 - _cos ) * y * y ) * view.y + ( ( 1 - _cos ) * y * z - x * _sin ) * view.z;
	rotated.z = ( ( 1 - _cos ) * x * z - y * _sin ) * view.x + ( ( 1 - _cos ) * y * z + x * _sin ) * view.y + ( _cos + ( 1 - _cos ) * z * z ) * view.z;

	cam->view = vector3_add ( cam->position, rotated );
}

void cam_rotatearoundpoint ( camera_t *cam, vector3_t center, VECTOR3_ELT theta, VECTOR3_ELT x, VECTOR3_ELT y, VECTOR3_ELT z )
{
	vector3_t pos = vector3_sub ( cam->position, center ), rotated;

	VECTOR3_ELT _cos = ( VECTOR3_ELT ) cos ( theta );
	VECTOR3_ELT _sin = ( VECTOR3_ELT ) sin ( theta );

	rotated.x = ( _cos + ( 1 - _cos ) * x * x ) * pos.x + ( ( 1 - _cos ) * x * y - z * _sin ) * pos.y + ( ( 1 - _cos ) * x * z + y * _sin ) * pos.z;
	rotated.y = ( ( 1 - _cos ) * x * y + z * _sin ) * pos.x + ( _cos + ( 1 - _cos ) * y * y ) * pos.y + ( ( 1 - _cos ) * y * z - x * _sin ) * pos.z;
	rotated.z = ( ( 1 - _cos ) * x * z - y * _sin ) * pos.x + ( ( 1 - _cos ) * y * z + x * _sin ) * pos.y + ( _cos + ( 1 - _cos ) * z * z ) * pos.z;

	cam->position = vector3_add ( center, rotated );
}

void cam_move ( camera_t *cam, VECTOR3_ELT speed )
{
	vector3_t move = vector3_mul ( vector3_normalize ( vector3_sub ( cam->view, cam->position ) ), speed );

	cam->position = vector3_add ( cam->position, move );
	cam->view = vector3_add ( cam->view, move );
}

void cam_movebetweenaxis ( camera_t *cam, VECTOR3_ELT speed, short axis1, short axis2 )
{
	vector3_t move = vector3_sub ( cam->view, cam->position );

	if ( ( axis1 == CAMERA_Y && axis2 == CAMERA_Z ) || ( axis1 == CAMERA_Z && axis2 == CAMERA_Y ) )
		move.x = 0;
	else if ( ( axis1 == CAMERA_X && axis2 == CAMERA_Z ) || ( axis1 == CAMERA_Z && axis2 == CAMERA_X ) )
		move.y = 0;
	else if ( ( axis1 == CAMERA_X && axis2 == CAMERA_Y ) || ( axis1 == CAMERA_Y && axis2 == CAMERA_X ) )
		move.z = 0;

	move = vector3_mul ( vector3_normalize ( move ), speed );
	cam->position = vector3_add ( cam->position, move );
	cam->view = vector3_add ( cam->view, move );
}

void cam_strafe ( camera_t *cam, VECTOR3_ELT speed )
{
	vector3_t strafe = vector3_mul ( vector3_normalize ( vector3_cross ( vector3_sub ( cam->view, cam->position ), cam->up ) ), speed );

	cam->position = vector3_add ( cam->position, strafe );
	cam->view = vector3_add ( cam->view, strafe );
}

void cam_movealongaxis ( camera_t *cam, VECTOR3_ELT speed, short axis )
{
	switch ( axis )
	{
		case CAMERA_X:
			cam->position.x += speed;
			cam->view.x += speed;
			break;

		case CAMERA_Y:
			cam->position.y += speed;
			cam->view.y += speed;
			break;

		case CAMERA_Z:
			cam->position.z += speed;
			cam->view.z += speed;
			break;
	}
}

void cam_setview ( camera_t *cam, short view )
{
	VECTOR3_ELT dist = vector3_distance ( cam->position, cam->view );
	cam->view = vector3 ( 0, 0, 0 );

	switch ( view )
	{
		case CAMERA_TOP:
			cam->position = vector3 ( 0, dist, -0.0001 );
			break;

		case CAMERA_BOTTOM:
			cam->position = vector3 ( 0.0001, -dist, 0 );
			break;

		case CAMERA_FRONT:
			cam->position = vector3 ( 0, 0, -dist );
			break;

		case CAMERA_REAR:
			cam->position = vector3 ( 0, 0, dist );
			break;

		case CAMERA_LEFT:
			cam->position = vector3 ( -dist, 0, 0 );
			break;

		case CAMERA_RIGHT:
			cam->position = vector3 ( dist, 0, 0 );
			break;
	}
}

void cam_update ( const camera_t *cam )
{
	glLoadIdentity ( );
	gluLookAt (
		cam->position.x, 	cam->position.y, 	cam->position.z,
		cam->view.x, 		cam->view.y,		cam->view.z,
		cam->up.x, 			cam->up.y, 			cam->up.z
	);
}
