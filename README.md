# HayaiHexen2
A Hexen 2 source port focused on speedrunning features.

Based on Hexen II: Hammer of Thyrion (uHexen2) source port at https://sourceforge.net/projects/uhexen2/ and http://uhexen2.sourceforge.net/.
Cloned from https://github.com/sezero/uhexen2 (version 1.5.10).
Original Hexen II source code has been released under the GNU GPLv2 license.

Many of the features added are copied over from JoeQuake: https://github.com/j0zzz/JoeQuake and http://joequake.runecentral.com. Some features originated in https://github.com/crashfort/NEAQUAKE.

Huge thanks to all of the above developers!


## Changes done:

* speedmeter (from JoeQuake / NEAQUAKE) ('show_speed', 'show_speed_interval' and 'show_speed_XYonly' cvars)
* 3rd person view yaw angle ('chase_angle' cvar)
* 'chase_checkwalls' cvar
* fps-independent physics when using 'cl_independentphysics 1' and 'cl_maxfps > 72' (from JoeQuake)
* changed 'sys_throttle' cvar to be 0 by default (to ensure that fps hits the 'cl_maxfps' limit)
* changed 'external_ents' cvar to be 0 by default (external level bug fixes are not wanted for speedruns)

## To do:

* 'rawinput' as default option for mouse input (implementation from JoeQuake / NEAQUAKE)
* 'cl_demospeed' and 'cl_demorewind' (implementation from JoeQuake)
* console command history autosaving to a file
* add a speedrun timer, which accurately measures time for both individual levels and full game runs (implement in HexenC gamecode?)
* revert gameplay to be authentic with the original CD version of Hexen 2: Portal of Praevus (i.e. revert bugfixes of the HoT source port which alter speedrun gameplay) (requires reverting changes both to the engine and the HexenC gamecode)
* various debug tools to aid in speedrun routing