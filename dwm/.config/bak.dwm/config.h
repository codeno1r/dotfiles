/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int gappx = 10;   /* gaps between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayonleft =
    0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 10; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 0; /* 0 means no systray */
static const int showbar = 1;     /* 0 means no bar */
static const int topbar = 1;      /* 0 means bottom bar */
static const int vertpad = 0;     /* vertical padding of bar */
static const int sidepad = 0;     /* horizontal padding of bar */
static const char *fonts[] = {"JetBrainsMono Nerd Font:style=Bold:size=14",
                              "Noto Color Emoji:size=12",
                              "NotoSans Nerd Font:size=12"};
static const char dmenufont[] = "JetBrainsMono Nerd Font:style=Bold:size=14";
static const char col_gray1[] = "#09090b";
static const char col_gray2[] = "#1e2939";
static const char col_gray3[] = "#52525c";
static const char col_gray4[] = "#99a1af";
static const char col_gray5[] = "#e4e4e7";
static const char col_cyan[] = "#0f172b";

// 🌿 Elegant & Relaxing DWM Color Scheme
// static const char dark_slate[] = "#2E3440";
static const char dark_slate[] = "#1B1E25";
static const char snow_white[] = "#D8DEE9";
static const char muted_border[] = "#4C566A";
static const char calm_cyan[] = "#88C0D0";
static const char subtle_blue[] = "#81A1C1";

static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {snow_white, dark_slate, muted_border},
    [SchemeSel] = {dark_slate, calm_cyan, subtle_blue},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"steam_app_381210", NULL, NULL, 1, 0, 0},
    {"Code", NULL, NULL, 1 << 1, 0, 0},
    {"Google-chrome", NULL, NULL, 1 << 2, 0, 0},
    {"Brave-browser", NULL, NULL, 1 << 2, 0, 0},
    {"Roam", NULL, NULL, 1 << 3, 0, 0},
    {"zoom", NULL, NULL, 1 << 5, 0, 0},
    {"WebWork Tracker", NULL, NULL, 1 << 8, 1, 0},
    {"mpv", NULL, NULL, 1 << 6, 0, 0},
    {"Virt-manager", NULL, NULL, 1 << 7, 0, 0},
    {"Virt-viewer", NULL, NULL, 1 << 7, 0, 0},
    {"steam", NULL, NULL, 1 << 7, 0, 0},

    {"firefox", NULL, NULL, 1 << 2, 0, 1},
    {"WhatSie", NULL, NULL, 1 << 3, 0, 1},
    {"ZapZap", NULL, NULL, 1 << 3, 0, 1},
    {"discord", NULL, NULL, 1 << 3, 0, 1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = {
//     "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb", col_gray1,
//     "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *dmenucmd[] = {"dmenu_run", "-c", NULL};
static const char *termcmd[] = {"st", NULL};
static const char *filemgrcmd[] = {"thunar", NULL};
// static const char *keepassxccmd[] = {"keepassxc", NULL};
// static const char *bluemanApplet[] = {"blueman-applet", NULL};
// static const char *nmApplet[] = {"nm-applet", NULL};
// static const char *noisetorch[] = {"noisetorch", "-i", NULL};

Autostarttag autostarttaglist[] = {
    {.cmd = NULL, .tags = 0},
};

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_space, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_e, spawn, {.v = filemgrcmd}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    //	{ MODKEY,                       XK_t,      setlayout,      {.v =
    //&layouts[0]} }, 	{ MODKEY,                       XK_f,      setlayout,
    //{.v = &layouts[1]} }, 	{ MODKEY,                       XK_m, setlayout,
    //{.v = &layouts[2]} }, 	{ MODKEY,                       XK_space,
    // setlayout, {0} }, 	{ MODKEY|ShiftMask,             XK_space,
    // togglefloating, {0} },
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY, XK_minus, setgaps, {.i = -1}},
    {MODKEY, XK_equal, setgaps, {.i = +1}},
    {MODKEY | ShiftMask, XK_equal, setgaps, {.i = 0}},
    {MODKEY, XK_F7, spawn, SHCMD("kill -49 $(pidof dwmblocks); nightlight.sh")},
    {MODKEY | ShiftMask, XK_n, spawn, SHCMD("nlchangestatus.sh")},
    {MODKEY | ShiftMask, XK_s, spawn, SHCMD("flameshotgui-dwm.sh")},
    {MODKEY | ShiftMask, XK_m, spawn, SHCMD("win10.sh")},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
    {MODKEY | ShiftMask, XK_F10, spawn,
     SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof "
           "dwmblocks)")},
    {MODKEY | ShiftMask, XK_F12, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof "
           "dwmblocks)")},
    {MODKEY | ShiftMask, XK_F11, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof "
           "dwmblocks)")},
    {0, XF86XK_MonBrightnessUp, spawn,
     SHCMD("brightnessctl s 10%+; kill -48 $(pidof dwmblocks)")},
    {0, XF86XK_MonBrightnessDown, spawn,
     SHCMD("brightnessctl s 10%-; kill -48 $(pidof dwmblocks)")},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button1, sigstatusbar, {.i = 1}},
    {ClkStatusText, 0, Button2, sigstatusbar, {.i = 2}},
    {ClkStatusText, 0, Button3, sigstatusbar, {.i = 3}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
