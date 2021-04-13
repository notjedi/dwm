dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.


Requirements
------------
In order to build dwm you need the Xlib header files.


Patches
------------
* fibonacci
* scratchpad
* vanitygaps
* actualfullscreen
* hide-vacant-gaps
* statuscmd-signal patch for dwmblocks
* floating-center - custom patch center all floating windows
* shiftview - custom patch to only move only through active tags

Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the `/usr/local` namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    doas make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    ssh-agent dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
