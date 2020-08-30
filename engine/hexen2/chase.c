/*
 * chase.c -- chase camera code
 * $Id: chase.c,v 1.9 2007-04-03 06:19:19 sezero Exp $
 * 
 * tallustelija: added chase_angle and chase_checkwalls
 *
 * Copyright (C) 1996-1997  Id Software, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "quakedef.h"

static	cvar_t	chase_back = {"chase_back", "100", CVAR_NONE};
static	cvar_t	chase_up = {"chase_up", "16", CVAR_NONE};
static	cvar_t	chase_right = {"chase_right", "0", CVAR_NONE};
cvar_t		chase_active = {"chase_active", "0", CVAR_NONE};
/*
	tallustelija:
*/
cvar_t		chase_angle = { "chase_angle", "0", CVAR_NONE };
cvar_t		chase_checkwalls = { "chase_checkwalls", "1", CVAR_NONE };

static	vec3_t	chase_dest;


void Chase_Init (void)
{
	Cvar_RegisterVariable (&chase_back);
	Cvar_RegisterVariable (&chase_up);
	Cvar_RegisterVariable (&chase_right);
	Cvar_RegisterVariable (&chase_active);
	/*
		tallustelija:
	*/
	Cvar_RegisterVariable(&chase_angle);
	Cvar_RegisterVariable(&chase_checkwalls);
}

void Chase_Reset (void)
{
	// for respawning and teleporting
//	start position 12 units behind head
}

static void TraceLine (vec3_t start, vec3_t end, vec3_t impact)
{
	trace_t	trace;

	memset (&trace, 0, sizeof(trace));
	SV_RecursiveHullCheck (cl.worldmodel->hulls, 0, 0, 1, start, end, &trace);
	VectorCopy (trace.endpos, impact);
}

void Chase_Update (void)
{
	float	dist;
	vec3_t	forward, up, right;
	vec3_t	dest, stop;

// if can't see player, reset
	AngleVectors (cl.viewangles, forward, right, up);

// calc exact destination
	chase_dest[0] = r_refdef.vieworg[0] -
			forward[0] * chase_back.value -
			right[0] * chase_right.value;
	chase_dest[1] = r_refdef.vieworg[1] -
			forward[1] * chase_back.value -
			right[1] * chase_right.value;
#if 0
	chase_dest[2] = r_refdef.vieworg[2] -
			forward[2] * chase_back.value -
			right[] * chase_right.value;
	chase_dest[2] += chase_up.value;
#endif
	chase_dest[2] = r_refdef.vieworg[2] + chase_up.value;

// find the spot the player is looking at
	VectorMA (r_refdef.vieworg, 4096, forward, dest);
	TraceLine (r_refdef.vieworg, dest, stop);

// calculate pitch to look at the same spot from camera
	VectorSubtract (stop, r_refdef.vieworg, stop);
	dist = DotProduct (stop, forward);
	if (dist < 1)
		dist = 1;
	r_refdef.viewangles[PITCH] = -atan(stop[2] / dist) / M_PI * 180;

/*
	tallustelija:
	chase_angle cvar determines the angle to rotate the chaseview in yaw direction
	FIXTHIS: ugly unoptimized code
*/
	if (chase_angle.value != 0)
	{
		vec3_t	chasevieworientation;
		vec3_t	rotateinrelationtothis = { 0, 1, 0 };
		vec3_t tempvector1;
		vec3_t tempvector2;
		vec3_t rotatedorientation;
		float angletorotate;
		angletorotate = chase_angle.value;
		angletorotate = angletorotate * (M_PI * 2 / 360);

		chasevieworientation[0] = chase_dest[0] - r_refdef.vieworg[0];
		chasevieworientation[1] = chase_dest[1] - r_refdef.vieworg[1];
		chasevieworientation[2] = 0;
		CrossProduct(chasevieworientation, rotateinrelationtothis, tempvector1);
		VectorNormalize(tempvector1);
		CrossProduct(tempvector1, chasevieworientation, tempvector2);
		chasevieworientation[0] = cos(angletorotate) * chasevieworientation[0];
		chasevieworientation[1] = cos(angletorotate) * chasevieworientation[1];
		chasevieworientation[2] = cos(angletorotate) * chasevieworientation[2];
		tempvector2[0] = sin(angletorotate) * tempvector2[0];
		tempvector2[1] = sin(angletorotate) * tempvector2[1];
		tempvector2[2] = sin(angletorotate) * tempvector2[2];
		if (r_refdef.viewangles[YAW] < 90 || r_refdef.viewangles[YAW] > 270)
		{
			VectorSubtract(chasevieworientation, tempvector2, rotatedorientation);
		}
		else
		{
			VectorAdd(chasevieworientation, tempvector2, rotatedorientation);
		}

		r_refdef.viewangles[YAW] = r_refdef.viewangles[YAW] + chase_angle.value;

		chase_dest[0] = r_refdef.vieworg[0] + rotatedorientation[0];
		chase_dest[1] = r_refdef.vieworg[1] + rotatedorientation[1];
	}

// check for walls between player and camera (from quakeforge)
	/*
		tallustelija:
		check for chase_checkwalls cvar first
	*/
	if (chase_checkwalls.value != 0)
	{
		TraceLine(r_refdef.vieworg, chase_dest, stop);
		if (VectorLength(stop) != 0)
		{
			chase_dest[0] = stop[0] + forward[0] * 8;
			chase_dest[1] = stop[1] + forward[1] * 8;
			chase_dest[2] = stop[2] + forward[2] * 8;
		}
	}

// move towards destination
	VectorCopy (chase_dest, r_refdef.vieworg);
}

