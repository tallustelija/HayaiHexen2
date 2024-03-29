/*
 * host.h -- public host structures and functions
 * $Id$
 *
 * tallustelija: Changes for cl_independentphysics (from JoeQuake)
 *
 * Copyright (C) 1996-1997  Id Software, Inc.
 * Copyright (C) 1997-1998  Raven Software Corp.
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

#ifndef HX2_HOST_H
#define HX2_HOST_H

// quakeparms structure specifies the base of the directory tree, the
// command line parms passed to the program, and the amount of memory
// available for the program to use

typedef struct quakeparms_s
{
	const char *basedir;
	const char *userdir;	// user's directory on UNIX platforms.
				// if user directories are enabled, basedir
				// and userdir will point to different
				// memory locations, otherwise to the same.
	int	argc;
	char	**argv;
	void	*membase;
	int	memsize;
	int	errstate;
} quakeparms_t;


extern	quakeparms_t	*host_parms;

extern	qboolean	isDedicated;

extern	cvar_t		sys_ticrate;
extern	cvar_t		sys_throttle;
extern	cvar_t		sys_nostdout;
extern	cvar_t		developer;

/*
	tallustelija:
	cl_independentphysics
*/
extern	cvar_t		cl_maxfps;

extern	cvar_t		pausable;

extern	qboolean	host_initialized;	// true if into command execution
extern	double		host_frametime;
extern	byte		*host_basepal;
extern	byte		*host_colormap;
extern	int		host_framecount;	// incremented every frame, never reset
extern	double		realtime;		// not bounded in any way, changed at
						// start of every frame, never reset

/*
	tallustelija:
	cl_independentphysics
*/
extern	double	physframetime;

void Host_Init (void);
void Host_InitCommands (void);
void Host_Shutdown(void);
void Host_Callback_Notify (cvar_t *var);	/* callback function for CVAR_NOTIFY */
/* Host_Error and Host_EndGame doesn't return either due to Sys_Error() or longjmp() */
FUNC_NORETURN void Host_Error (const char *error, ...) FUNC_PRINTF(1,2);
FUNC_NORETURN void Host_EndGame (const char *message, ...) FUNC_PRINTF(1,2);
#ifdef __WATCOMC__
#pragma aux Host_Error aborts;
#pragma aux Host_EndGame aborts;
#endif
void Host_Frame (float time);
void Host_Quit_f (void);
void Host_ClientCommands (const char *fmt, ...) FUNC_PRINTF(1,2);
void Host_ShutdownServer (qboolean crash);

void Host_ClearMemory (void);

void Host_RemoveGIPFiles (const char *path);
void Host_DeleteSave (const char *savepath);
int Host_CopyFiles(const char *source, const char *pat, const char *dest);
int SaveGamestate (qboolean ClientsOnly);

/*
	tallustelija:
	cl_independentphysics
*/
void Host_ServerFrame(double time);


extern	int		current_skill;	// skill level for currently loaded level (in case
					//  the user changes the cvar while the level is
					//  running, this reflects the level actually in use)

extern	int		sv_kingofhill;		// mission pack king of the hill.

extern	unsigned int	info_mask, info_mask2;	// mission pack objectives

#endif	/* HX2_HOST_H */
