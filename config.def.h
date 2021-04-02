/* See LICENSE file for copyright and license details. */

#define TERMINAL "alacritty"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainMono Nerd Font:size=10" };
static const char dmenufont[]       = "JetBrainMono Nerd Font:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#BF616A";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      			instance    title       				tags mask     isfloating   monitor */
	{ "Gimp",     			NULL,       NULL,       				0,            1,           -1 },
	{ "Brave-browser", 		NULL, 		NULL,						1 << 2,		  0,		   -1 },
	{ "Chromium", 			NULL, 		NULL,						1 << 3,		  0,		   -1 },
	{ "discord",			NULL,		NULL,						1 << 4,		  0,		   -1 },
	{ "Spotify",			NULL,		NULL,						1 << 5,		  0,		   -1 },
	{ "jetbrains-studio",	NULL,		NULL,						1 << 1,		  0,		   -1 },
	{ NULL,					"win0",		NULL,						1 << 1,		  1,		   -1 },
	{ NULL, 				NULL,		"Task Manager - Brave", 	0,			  1,		   -1 },
	{ NULL,					NULL,		"Android Emulator",			1 << 1,		  1,		   -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[\\]",      dwindle },
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        					function        		argument */
	{ MODKEY,                       XK_b,      					togglebar,      		{0} },
	{ MODKEY,             			XK_e,	   					zoom,           		{0} },
	{ MODKEY,                       XK_f,      					togglefullscreen,		{0} },
	{ MODKEY,                       XK_h,      					setmfact,       		{.f = -0.05 } },
	{ MODKEY,                       XK_j,      					focusstack,     		{.i = +1 } },
	{ MODKEY,                       XK_k,      					focusstack,     		{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,      					spawn,     				SHCMD("killprocess") },
	{ MODKEY,                       XK_l,      					setmfact,       		{.f = +0.05 } },
	{ MODKEY, 						XK_p,						spawn,					SHCMD("playerctl play-pause") },
	{ MODKEY,                       XK_r,      					spawn,          		SHCMD("rofi -show drun -show-icons -lines 5 -width 30") },
	{ MODKEY,             			XK_q,      					killclient,     		{0} },
	{ MODKEY, 						XK_bracketleft,				spawn,					SHCMD("playerctl previous") },
	{ MODKEY, 						XK_bracketright,			spawn,					SHCMD("playerctl next") },
	{ MODKEY,             			XK_Return, 					spawn,          		SHCMD(TERMINAL) },
	{ MODKEY,             			XK_space,  					togglefloating, 		{0} },

	{ MODKEY|Mod1Mask,              XK_h,      					incrgaps,       		{.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_l,      					incrgaps,       		{.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      					togglegaps,     		{0} },
	{ MODKEY|Mod1Mask,              XK_y,      					incrohgaps,     		{.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_o,      					incrohgaps,     		{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      					incrovgaps,    			{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      					incrovgaps,    			{.i = -1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      					defaultgaps,   			{0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_h,      					incrogaps,     			{.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,      					incrogaps,      		{.i = -1 } },

	{ Mod1Mask,                     XK_Tab,    					shiftview,           	{.i = +1 } },
	{ Mod1Mask|ShiftMask,           XK_Tab,    					shiftview,           	{.i = -1 } },

	{ MODKEY,                       XK_w,      					setlayout,      		{.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      					setlayout,      		{.v = &layouts[1]} },
	{ MODKEY,                       XK_s,      					setlayout,      		{.v = &layouts[2]} },

	{ MODKEY|ShiftMask,             XK_q,      					quit,           		{0} },
	{ MODKEY|ShiftMask,           	XK_space,  					setlayout,      		{0} },

	{ 0, 							XF86XK_AudioMute,			spawn,					SHCMD("pamixer -t") },
	{ 0, 							XF86XK_AudioRaiseVolume,	spawn,					SHCMD("pamixer --allow-boost -i 5") },
	{ 0, 							XF86XK_AudioLowerVolume,	spawn,					SHCMD("pamixer --allow-boost -d 5") },
	{ 0, 							XF86XK_AudioNext,			spawn,					SHCMD("playerctl next") },
	{ 0, 							XF86XK_AudioPrev,			spawn,					SHCMD("playerctl previous") },
	{ 0, 							XF86XK_AudioPlay,			spawn,					SHCMD("playerctl play-pause") },
	{ 0, 							XF86XK_AudioPause,			spawn,					SHCMD("playerctl play-pause") },
	{ 0, 							XF86XK_AudioStop,			spawn,					SHCMD("playerctl stop") },
	

	TAGKEYS(                        XK_1,      	                						0)
	TAGKEYS(                        XK_2,      	                						1)
	TAGKEYS(                        XK_3,      	                						2)
	TAGKEYS(                        XK_4,      	                						3)
	TAGKEYS(                        XK_5,      	                						4)
	TAGKEYS(                        XK_6,      	                						5)
	TAGKEYS(                        XK_7,      	                						6)
	TAGKEYS(                        XK_8,      	                						7)
	TAGKEYS(                        XK_9,      	                						8)

	/* mod + a */
	/* mod + c */
	/* mod + d */
	/* mod + g */
	/* mod + p */
	/* mod + v */
	/* mod + x */
	/* mod + y - flameshot or maim */
	/* mod + , - mpc */
	/* mod + . - mpc */
	/* mod + braketleft - general audio prev */
	/* mod + braketright - general audio next */
	/* mod + shift + d */
	/* mod + shift + j */
	/* mod + shift + k */
	/* print key */
	/* shift + print key */

	/* TODO: mod + shift + x for slock? */
	/* TODO: use xcape to map right shift to ctrl + super? */
	/* TODO: cycle layouts patch */
	/* TODO: vanity gaps for dwindle layout */
	/* { MODKEY,                       XK_comma,  	focusmon,       		{.i = -1 } }, */
	/* { MODKEY,                       XK_period, 	focusmon,       		{.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_comma,  	tagmon,         		{.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_period, 	tagmon,         		{.i = +1 } }, */

	/* { MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      			{.i = +1 } }, */
	/* { MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      			{.i = -1 } }, */
	/* { MODKEY,                       XK_y,      incrihgaps,     			{.i = +1 } }, */
	/* { MODKEY,                       XK_o,      incrihgaps,     			{.i = -1 } }, */
	/* { MODKEY|ControlMask,           XK_y,      incrivgaps,     			{.i = +1 } }, */
	/* { MODKEY|ControlMask,           XK_o,      incrivgaps,     			{.i = -1 } }, */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
