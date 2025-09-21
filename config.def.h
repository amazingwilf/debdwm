/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;
static const unsigned int snap      = 32;

static const unsigned int gappih	= 10;       /* horiz inner gap between windows */
static const unsigned int gappiv	= 10;       /* vert inner gap between windows */
static const unsigned int gappoh	= 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov	= 10;       /* vert outer gap between windows and screen edge */
static int smartgaps				= 0;        /* 1 means no outer gap when there is only one window */

static const int showbar            = 1;
static const int topbar             = 1;

#define ICONSIZE (bh - 8)
#define ICONSPACING 10

static const char *fonts[]			= { "Inter:size=11",
										"NotoSans Nerd Font:size=12",
										"IosevkaTerm Nerd Font:style=Bold:size=10" };

#include "termcolors.h"

static char normfgcolor[]			= "#bbbbbb";
static char normbgcolor[]			= "#222222";
static char normbordercolor[]		= "#444444";

static char selfgcolor[]			= "#eeeeee";
static char selbgcolor[]			= "#005577";
static char selbordercolor[]		= "#005577";

static char tagemptyfgcolor[]		= "#005577";
static char tagemptybgcolor[]		= "#222222";

static char tagoccfgcolor[]			= "#bbbbbb";
static char tagoccbgcolor[]			= "#222222";

static char tagselfgcolor[]			= "#eeeeee";
static char tagselbgcolor[]			= "#005577";

static char titlenormfgcolor[]		= "#bbbbbb";
static char titlenormbgcolor[]		= "#222222";

static char titleselfgcolor[]		= "#eeeeee";
static char titleselbgcolor[]		= "#005577";

static char ltsymfgcolor[]			= "#eeeeee";
static char ltsymbgcolor[]			= "#005577";

static char *colors[][3]		= {
	[SchemeNorm]		= { normfgcolor,		normbgcolor,		normbordercolor },
	[SchemeSel]			= { selfgcolor,			selbgcolor,			selbordercolor },
	[SchemeTagEmpty]	= { tagemptyfgcolor,	tagemptybgcolor,	NULL },
	[SchemeTagOcc]		= { tagoccfgcolor,		tagoccbgcolor,		NULL },
	[SchemeTagSel]		= { tagselfgcolor,		tagselbgcolor,		NULL },
	[SchemeTitleNorm]	= { titlenormfgcolor,	titlenormbgcolor,	NULL },
	[SchemeTitleSel]	= { titleselfgcolor,	titleselbgcolor,	NULL },
	[SchemeLtSym]		= { ltsymfgcolor,		ltsymbgcolor,		NULL },
};

static const char *const autostart[] = {
	"/usr/libexec/xfce-polkit", NULL,
	"nitrogen", "--restore", NULL,
	"dunst", NULL,
	"picom", "-b", NULL,
	"dwmblocks", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[]		= { "1", "2", "3", "4", "5", "6", "7", "8" };
static const int viewontag		= 1;
static const int viewonrulestag	= 1;

static const unsigned int ulinepad		= 5;
static const unsigned int ulinestroke	= 2;
static const unsigned int ulinevoffset	= 0;
static const int ulineall 				= 0;

static const Rule rules[]	= {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	{ .class = "Nwg-look", .isfloating = 1 },
	{ .class = "firefox", .tags = 1 << 1 },
	{ .class = "thunar", .tags = 1 << 2 },
};

/* layout(s) */
static const float mfact		= 0.50;
static const int nmaster		= 1; 
static const int resizehints	= 0;
static const int lockfullscreen	= 1;
static const int refreshrate	= 120; 

#define FORCE_VSPLIT 1
#include "vanitygaps.c"

static const Layout layouts[]	= {
	{ "[]=",	tile }, 
	{ "><>",	NULL },
	{ "[M]",	monocle },
	{ "[@]",	spiral },
	{ "[\\]",	dwindle },
	{ "D[]",	deck },
	{ "TTT",	bstack },
	{ "===",	bstackhoriz },
	{ "HHH",	grid },
	{ "###",	nrowgrid },
	{ "---",	horizgrid },
	{ ":::",	gaplessgrid },
	{ "|M|",	centeredmaster },
	{ ">M>",	centeredfloatingmaster },
	{ NULL,		NULL },
};

/* key definitions */
#define Super Mod4Mask
#define Shift ShiftMask
#define Ctrl ControlMask
#define Alt Mod1Mask

#define TAGKEYS(KEY,TAG) \
	{ Super,				KEY,	view,			{.ui = 1 << TAG} }, \
	{ Super|Ctrl,			KEY,	toggleview,		{.ui = 1 << TAG} }, \
	{ Super|Shift,			KEY,	tag,			{.ui = 1 << TAG} }, \
	{ Super|Ctrl|Shift,		KEY,	toggletag,		{.ui = 1 << TAG} },

#define STATUSBAR "dwmblocks"

/* commands */
static const char *termcmd[]		= { "ghostty", NULL };
static const char *roficmd[]		= { "rofi", "-show", "drun", NULL };
static const char *firefoxcmd[]		= { "firefox", NULL };
static const char *thunarcmd[]		= { "thunar", NULL };

static const Key keys[] = {
	/* modifier	key	function	argument */			
	{ Super,			XK_Return,		spawn,				{.v = termcmd } },
	{ Super,			XK_space,		spawn,				{.v = roficmd } },
	{ Super,			XK_w,			spawn,				{.v = firefoxcmd } },
	{ Super,			XK_e,			spawn,				{.v = thunarcmd } },
	{ Super,			XK_j,			focusstack,			{.i = +1 } },
	{ Super,			XK_k,			focusstack,			{.i = -1 } },
	{ Super,			XK_i,			incnmaster,			{.i = +1 } },
	{ Super,			XK_d,			incnmaster,			{.i = -1 } },
	{ Super,			XK_h,			setmfact,			{.f = -0.05} },
	{ Super,			XK_l,			setmfact,			{.f = +0.05} },
	{ Super|Shift,		XK_h,			setcfact,			{.f = +0.25} },
	{ Super|Shift,		XK_l,			setcfact,			{.f = -0.25} },
	{ Super|Shift,		XK_o,			setcfact,			{.f =  0.00} },
	{ Super,			XK_q,			killclient,			{0} },
	{ Super|Shift,		XK_q,			quit,				{0} },
	{ Super|Shift,		XK_r,			quit,				{1} },
	{ Super,			XK_t,			setlayout,			{.v = &layouts[0]} },
	{ Super,			XK_f,			setlayout,			{.v = &layouts[1]} },
	{ Super,			XK_m,			setlayout,			{.v = &layouts[2]} },
	{ Super|Shift,		XK_b,			togglebar,			{0} },
	{ Super|Shift,		XK_f,			togglefullscr,		{0} },
	{ Super|Shift,		XK_g,			togglegaps,			{0} },
	{ Super|Shift,		XK_space,		togglefloating, 	{0} },
	{ Super|Shift,		XK_x,			xrdb,				{.v = NULL } },
	{ Super,			XK_0,			view,				{.ui = ~0 } },
	{ Super|Shift,		XK_0,			tag,				{.ui = ~0 } },
	{ Super,			XK_Right,		viewnext,			{0} },
	{ Super,			XK_Left,		viewprev,			{0} },
	{ Super|Shift,		XK_Right,		tagtonext,			{0} },
	{ Super|Shift,		XK_Left,		tagtoprev,			{0} },
	TAGKEYS(			XK_1,								0)
	TAGKEYS(			XK_2,								1)
	TAGKEYS(			XK_3,								2)
	TAGKEYS(			XK_4,								3)
	TAGKEYS(			XK_5,								4)
	TAGKEYS(			XK_6,								5)
	TAGKEYS(			XK_7,								6)
	TAGKEYS(			XK_8,								7)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	{ ClkLtSymbol,		0,		Button1,	setlayout,			{0} },
	{ ClkLtSymbol,		0,		Button3,	setlayout,			{.v = &layouts[2]} },
	{ ClkWinTitle,		0,		Button2,	zoom,				{0} },
	{ ClkStatusText,	0,		Button1,	sigstatusbar,		{.i = 1} },
	{ ClkStatusText,	0,		Button2,	sigstatusbar,		{.i = 2} },
	{ ClkStatusText,	0,		Button3,	sigstatusbar,		{.i = 3} },
	{ ClkStatusText,	0,		Button4,	sigstatusbar,		{.i = 4} },
	{ ClkStatusText,	0,		Button5,	sigstatusbar,		{.i = 5} },
	{ ClkClientWin,		Super,	Button1,	movemouse,			{0} },
	{ ClkClientWin,		Super,	Button2,	togglefloating, 	{0} },
	{ ClkClientWin,		Super,	Button3,	resizemouse,		{0} },
	{ ClkTagBar,		0,		Button1,	view,				{0} },
	{ ClkTagBar,		0,		Button3,	toggleview,			{0} },
	{ ClkTagBar,		Super,	Button1,	tag,				{0} },
	{ ClkTagBar,		Super,	Button3,	toggletag,			{0} },
};

