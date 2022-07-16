dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.


Requirements
------------
In order to build dwm you need the Xlib header files.


Patches
------------
* [fibonacci](https://dwm.suckless.org/patches/fibonacci/)
* [scratchpad](https://dwm.suckless.org/patches/scratchpad/)
* [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/)
* [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/)
* [hide-vacant-tags](https://dwm.suckless.org/patches/hide_vacant_tags/)
* [statuscmd-signal](https://dwm.suckless.org/patches/statuscmd/) - patch for dwmblocks
* [floating-center](https://github.com/notjedi/dwm/blob/main/patches/dwm-floating-center.diff) - custom patch to center all floating windows
* [shiftview](https://github.com/notjedi/dwm/blob/fab6892ffd4a2fa168d485f0c85fb99d8aff467a/dwm.c#L1601) - custom patch to only move only through active tags

Installation
------------
Edit `config.mk` to match your local setup (dwm is installed into
the `/usr/local` namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    doas make clean install


Running dwm
-----------
Add the following line to your `.xinitrc` to start dwm using startx:

    ssh-agent dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g:

    DISPLAY=foo.bar:1 ssh-agent dwm

(This will start dwm on display :1 of the host foo.bar.)


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
