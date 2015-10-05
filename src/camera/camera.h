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
|     FILE:  camera.h                                               |
\__________________________________________________________________/

*/

#ifndef __CAMERA_H
#define __CAMERA_H

#include "../vector3/vector3.h"

#define CAMERA_X        0x01
#define CAMERA_Y        0x02
#define CAMERA_Z        0x03
#define CAMERA_TOP      0x04
#define CAMERA_BOTTOM   0x05
#define CAMERA_FRONT    0x06
#define CAMERA_REAR     0x07
#define CAMERA_LEFT     0x08
#define CAMERA_RIGHT    0x09

typedef struct
{
	vector3_t position, view, up;
} camera_t;

void cam_set ( camera_t *cam, VECTOR3_ELT px, VECTOR3_ELT py, VECTOR3_ELT pz, VECTOR3_ELT vx, VECTOR3_ELT vy, VECTOR3_ELT vz, VECTOR3_ELT ux, VECTOR3_ELT uy, VECTOR3_ELT uz );
void cam_rotateview ( camera_t *cam, VECTOR3_ELT theta, short axis );
void cam_rotatearoundpoint ( camera_t *cam, vector3_t center, VECTOR3_ELT theta, VECTOR3_ELT x, VECTOR3_ELT y, VECTOR3_ELT z );
void cam_move ( camera_t *cam, VECTOR3_ELT speed );
void cam_movebetweenaxis ( camera_t *cam, VECTOR3_ELT speed, short axis1, short axis2 );
void cam_strafe ( camera_t *cam, VECTOR3_ELT speed );
//void cam_strafebetweenaxis ( camera_t *cam, VECTOR3_ELT speed, short axis1, short axis2 );
void cam_movealongaxis ( camera_t *cam, VECTOR3_ELT speed, short axis );
void cam_setview ( camera_t *cam, short view );
void cam_update ( const camera_t *cam );

#include "camera.c"

/*
	radius = hypot ( view.y, view.z ), angle = sgn ( view.z ) * acos ( view.y / radius ) + theta;
	z > 0 && x > 0 then angle { 0, 90 }
	z > 0 && x < 0 then angle { 90, 180 }
	z < 0 && x < 0 then angle { 180, 270 }
	z < 0 && x > 0 then angle { 270, 360 }
*/

#endif
