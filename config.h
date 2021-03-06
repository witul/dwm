/* See LICENSE file for copyright and license details. */

#include<X11/XF86keysym.h>
#define NUMCOLORS         4
static const char colors[NUMCOLORS][ColLast][8] = {
  // border   foreground background
  { "#000033", "#dddddd", "#000033" },  // normal
  { "#000088", "#ffffff", "#000088" },  // selected
  { "#ff0000", "#000000", "#ffff00" },  // urgent/warning  (black on yellow)
  { "#ff0000", "#ffffff", "#ff0000" },  // error (white on red)
  // add more here
};
//static const char font[]            = "Sans 9";
static const char font[]            = "-*-terminus-*-*-*-*-*-*-*-*-*-*-*-*";
//static const char font[]            = "-*-terminus-medium-r-normal-*-8-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
/* False means using the scroll wheel on a window will not change focus */

//static const Bool focusonwheelscroll = True;




/* tagging */
static const char *tags[] = { "q", "w", "e", "r", "t", "y", "u", "i", "o" };
//static const char *tags[] = { "web", "term", "dev", "chat", "video", "misc" };
static const Rule rules[] = {
    /* class      instance    title       tags mask     isfloating   monitor */
     { "Firefox",  NULL,       NULL,       1 << 0,       False,       -1 },
    { "Skype",  NULL,       NULL,       1<<7,       False,       -1 },
    { NULL,  NULL,       "mutt",       1<<6,       False,       -1 },
    { NULL,  NULL,       "vifm",       1<<2,       False,       -1 },
};


/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "bstackhoriz.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "TTT",      bstack },
    { "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod1Mask
#define MODKEYWIN Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *passmenucmd[] = { "/home/witul/bin/passmenu", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt", NULL };

static const char *ss[]={"/home/witul/scripts/screenshot",NULL};
static const char *volu[] = { "amixer", "set", "Master", "5%+", NULL };
static const char *vold[] = { "amixer", "set", "Master", "5%-", NULL };
static const char *mute[] = { "amixer", "set", "Master", "toggle", NULL };
static const char *playpause[] = { "ncmpcpp", "toggle", NULL };
static const char *vifm[] = { "urxvt", "-e","vifm",NULL };
static const char *mutt[] = { "urxvt", "-e","mutt",NULL };


static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = passmenucmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    //  { MODKEY|CtrlMask,                       XK_b,      togglebar,      {0} },
    { MODKEY,                      XK_l,      focusstack,     {.i = +1 } },
    { MODKEY,                      XK_h,      focusstack,     {.i = -1 } },
    //zmiana ukladu - alt+shift+=
    { MODKEY|ShiftMask,                       0x3d,      incnmaster,     {.i = +1 } },
    //zmiana ukladu - alt+shift+-
    { MODKEY|ShiftMask,                       0x2d,      incnmaster,     {.i = -1 } },
    //zmiana rozmiaru - alt+[]
    { MODKEY,                       0x5b,      setmfact,       {.f = -0.05} },
    { MODKEY,                       0x5d,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEYWIN|ShiftMask,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEYWIN,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEYWIN,                       XK_m,      setlayout,      {.v = &layouts[2]} },

    { MODKEYWIN,                       XK_b,      setlayout,      {.v = &layouts[3]} },
    { MODKEYWIN|ShiftMask,             XK_b,      setlayout,      {.v = &layouts[4]} },

    { MODKEYWIN,                       XK_space,  setlayout,      {0} },
    { MODKEYWIN|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    //  { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    //  { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { 0,                            XK_Print,    spawn,          {.v = ss} },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    { 0, 0x1008ff13,spawn, {.v = volu } },
    { 0, 0x1008ff11,spawn, {.v = vold } },
    { 0, 0x1008ff12,spawn, {.v = mute } },
    { 0, 0x1008ff14,spawn, {.v = playpause} },

    TAGKEYS(                        XK_q,                      0)
    TAGKEYS(                        XK_w,                      1)
    TAGKEYS(                        XK_e,                      2)
    TAGKEYS(                        XK_r,                      3)
    TAGKEYS(                        XK_t,                      4)
    TAGKEYS(                        XK_y,                      5)
    TAGKEYS(                        XK_u,                      6)
    TAGKEYS(                        XK_i,                      7)
    TAGKEYS(                        XK_o,                      8)
    { MODKEY|ShiftMask,0xff08,      quit,           {0} },
    { MODKEY|ShiftMask, XK_d, spawn, {.v = vifm } },
    { MODKEY|ShiftMask, XK_m, spawn, {.v = mutt } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

