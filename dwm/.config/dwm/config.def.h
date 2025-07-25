/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx = 4;
static const unsigned int snap = 5;   /* snap pixel */
static const unsigned int gappih = 5; /* horiz inner gap between windows */
static const unsigned int gappiv = 5; /* vert inner gap between windows */
static const unsigned int gappoh = 5; /* horiz outer gap */
static const unsigned int gappov = 5; /* vert outer gap */
static int smartgaps = 0;
/* 1 means no outer gap when there is only one window */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1;  /* 0 means bottom bar */
static const int vertpad = 0; /* vertical padding of bar */
static const int sidepad = 0; /* horizontal padding of bar */
static const char *fonts[] = {"JetBrainsMono Nerd Font:style=Bold:size=14"};
static const char dmenufont[] = "JetBrainsMono Nerd Font:style=Bold:size=14";

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
    {"firefox", NULL, NULL, 1 << 1, 0, 0},
    {"Google-chrome", NULL, NULL, 1 << 2, 0, 0},
    {"Brave-browser", NULL, NULL, 1 << 2, 0, 0},
    {"Roam", NULL, NULL, 1 << 3, 0, 0},
    {"discord", NULL, NULL, 1 << 4, 0, 0},
    {"ZapZap", NULL, NULL, 1 << 5, 0, 0},
    {"mpv", NULL, NULL, 1 << 6, 0, 0},
    {"zoom", NULL, NULL, 1 << 7, 0, 0},
    {"Virt-manager", NULL, NULL, 1 << 7, 0, 0},
    {"Virt-viewer", NULL, NULL, 1 << 7, 0, 0},
    {"WebWork Tracker", NULL, NULL, 1 << 8, 1, 0},

};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT                                                           \
  1 /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"[M]", monocle},
    {"[@]", spiral},
    {"[\\]", dwindle},
    {"H[]", deck},
    {"TTT", bstack},
    {"===", bstackhoriz},
    {"HHH", grid},
    {"###", nrowgrid},
    {"---", horizgrid},
    {":::", gaplessgrid},
    {"|M|", centeredmaster},
    {">M>", centeredfloatingmaster},
    {"><>", NULL}, /* no layout function means floating behavior */
    {NULL, NULL},
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

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-c", NULL};
static const char *termcmd[] = {"alacritty", NULL};
static const char *filemgrcmd[] = {"thunar", NULL};

static const Key keys[] = {
    /* modifier                     key        function        argument */

    /********************
    **General Shortcuts**
    ********************/

    // Tags
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},

    // Terminal
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},

    // Menu
    {MODKEY, XK_space, spawn, {.v = dmenucmd}},

    // Switch App Position
    {MODKEY, XK_Return, zoom, {0}},

    // View last App
    {MODKEY, XK_Tab, view, {0}},

    // Close App
    {MODKEY | ShiftMask, XK_c, killclient, {0}},

    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_e, spawn, {.v = filemgrcmd}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_h, setcfact, {.f = +0.25}},
    {MODKEY | ShiftMask, XK_l, setcfact, {.f = -0.25}},
    {MODKEY | ShiftMask, XK_o, setcfact, {.f = 0.00}},
    {MODKEY | Mod4Mask, XK_u, incrgaps, {.i = +1}},
    {MODKEY | Mod4Mask | ShiftMask, XK_u, incrgaps, {.i = -1}},
    {MODKEY | Mod4Mask, XK_i, incrigaps, {.i = +1}},
    {MODKEY | Mod4Mask | ShiftMask, XK_i, incrigaps, {.i = -1}},
    {MODKEY | Mod4Mask, XK_o, incrogaps, {.i = +1}},
    {MODKEY | Mod4Mask | ShiftMask, XK_o, incrogaps, {.i = -1}},
    {MODKEY | Mod4Mask, XK_6, incrihgaps, {.i = +1}},
    {MODKEY | Mod4Mask | ShiftMask, XK_6, incrihgaps, {.i = -1}},
    {MODKEY | Mod4Mask, XK_7, incrivgaps, {.i = +1}},
    {MODKEY | Mod4Mask | ShiftMask, XK_7, incrivgaps, {.i = -1}},
    {MODKEY | Mod4Mask, XK_8, incrohgaps, {.i = +1}},
    {MODKEY | Mod4Mask | ShiftMask, XK_8, incrohgaps, {.i = -1}},
    {MODKEY | Mod4Mask, XK_9, incrovgaps, {.i = +1}},
    {MODKEY | Mod4Mask | ShiftMask, XK_9, incrovgaps, {.i = -1}},
    {MODKEY | Mod4Mask, XK_0, togglegaps, {0}},
    {MODKEY | Mod4Mask | ShiftMask, XK_0, defaultgaps, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},

    // {MODKEY, XK_i, incnmaster, {.i = +1}},
    // {MODKEY, XK_d, incnmaster, {.i = -1}},
    // {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    // {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    // {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    // {MODKEY, XK_space, setlayout, {0}},
    // {MODKEY, XK_0, view, {.ui = ~0}},
    // {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},

    // {MODKEY, XK_minus, setgaps, {.i = -1}},
    // {MODKEY, XK_equal, setgaps, {.i = +1}},
    // {MODKEY | ShiftMask, XK_equal, setgaps, {.i = 0}},

    // Custom Shortcuts
    {MODKEY | ShiftMask, XK_s, spawn,
     SHCMD("flameshotgui.sh")}, // If you're using DWM
    {MODKEY | ShiftMask, XK_b, spawn, SHCMD("WebWorkTracker.sh")},
    {MODKEY | ShiftMask, XK_n, spawn, SHCMD("nlchangestatus.sh")},
    {MODKEY | ShiftMask, XK_m, spawn, SHCMD("win10.sh")},

    // // Lenovo Laptop Custom Shortcut
    // {MODKEY, XK_F7, spawn, SHCMD("kill -49 $(pidof dwmblocks);
    // nightlight.sh")}, {0, XF86XK_AudioMute, spawn,
    //  SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof "
    //        "dwmblocks)")},
    // {0, XF86XK_AudioRaiseVolume, spawn,
    //  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof "
    //        "dwmblocks)")},
    // {0, XF86XK_AudioLowerVolume, spawn,
    //  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof "
    //        "dwmblocks)")},
    // {0, XF86XK_MonBrightnessUp, spawn,
    //  SHCMD("brightnessctl s 10%+; kill -48 $(pidof dwmblocks)")},
    // {0, XF86XK_MonBrightnessDown, spawn,
    //  SHCMD("brightnessctl s 10%-; kill -48 $(pidof dwmblocks)")},

    // PC Custom Shortcut
    {MODKEY, XK_F10, spawn,
     SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof "
           "dwmblocks)")},
    {MODKEY, XK_F12, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof "
           "dwmblocks)")},
    {MODKEY, XK_F11, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof "
           "dwmblocks)")},

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function
       argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
