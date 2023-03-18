/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 32;       /* snap pixel */
static const int center		    = 1;	/* center windows that have CenterThisWindow on */
static const float centerratio	    = 0.7;	/* center windows ratio */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 10;        /* 2 is the default spacing around the bar's font */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:pixelsize=19:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:pixelsize=17:antialias=true:autohint=true" ;

#include "themes/catppuccin.h"

#define NUMCOLORS	20
static const char *colors[NUMCOLORS][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]       = { gray1,   black, gray2 },
	[SchemeSel]        = { black,   gray5,   blue  },
	[SchemeYellow]	   = { surface,   yellow, red   },
	[SchemeYellowFg]   = { yellow,   surface, red   },
	[SchemeRed]	   = { surface,   red,    red   },
	[SchemeRedFg]	   = { red,   surface,    red   },
	[SchemeGreen]	   = { surface,	green,  red   },
	[SchemeGreenFg]	   = { green,	surface,  red   },
	[SchemePink]	   = { surface,	pink,   red   },
	[SchemePinkFg]	   = { pink,	surface,   red   },
	[SchemeGray]	   = { black,	gray5,  red   },
	[SchemeGrayFg]	   = { gray5,	black,  red   },
	[SchemeOrange]	   = { surface,	orange,  red   },
	[SchemeOrangeFg]   = { orange,	surface,  red   },
	[SchemeBlueFg]     = { blue,	black,  red  },
	[SchemeBlue]       = { black,	blue,  red  },
	[SchemeMauve]      = { surface,	mauve,  red  },
	[SchemeMauveFg]    = { mauve, surface,  red  },
};

/* tagging */
static const char *tags[] =          { "", "", "", "", "", "", "", "", "", "", "", "" };
static const char *nonactivetags[] = { "", "", "", "", "", "", "", "", "", "", "", "" };

static const char *tagsel[][2] = {
	{ blue, black},
	{ red, black},
	{ yellow, black},
	{ orange, black},
	{ text, black},
	{ mauve, black},
	{ pink, black},
	{ green, black},
	{ white, black},
	{ teal, black},
	{ maroon, black},
	{ flamingo, black},
};


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	/* class		     instance    title    tags mask     isfloating   CenterThisWindow?     monitor */
	{ "st",				NULL,		NULL,		0,        0,           1,	-1 },
	{ "firefox",			NULL,		NULL,       1 << 1,       0,           0,	-1 },
	{ "TelegramDesktop",  "telegram-desktop",       NULL,       1 << 2,       0,           0,	-1 },
	{ "vlc",			"vlc",		NULL,       1 << 6,       0,           0,	-1 },
	{ "qBittorrent",	"qbittorrent",		NULL,       1 << 11,      0,           0,	-1 },
	{ NULL,				NULL,	      "cmus",       1 << 10,      0,           0,	-1 },
	{ NULL,			"virt-manager",	"Virtual Machine Manager",       1 << 8,       0,           1,	-1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " ",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "󰍹 ",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-c", "-l", "12", NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	{ MODKEY,	                XK_c,	   togglecenter,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_F1,                      9)
	TAGKEYS(                        XK_F2,                      10)
	TAGKEYS(                        XK_F3,                      11)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

