/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 1;  /* border pixel of windows */
/* colors */ 
static const float rootcolor[]             = COLOR(0x121212ff);
static const float bordercolor[]           = COLOR(0x1a1a1aff);
static const float focuscolor[]            = COLOR(0x3fc3aaff);
static const float urgentcolor[]           = COLOR(0xb66358ff);
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1f, 0.1f, 0.1f, 1.0f}; /* You can also use glsl colors */
/* change the cursor theme and size */
static const char *cursor_theme            = "Quintom_Snow";
static const char cursor_size[]            = "24"; /* Make sure it's a valid integer, otherwise things will break */
/* keyboard layout change notification for status bar */
static const char  kblayout_file[] = "/tmp/dwl-keymap";
static const char *kblayout_cmd[]  = {"pkill", "-RTMIN+3", "someblocks", NULL};

/* tagging - TAGCOUNT must be no greater than 31 */
#define TAGCOUNT (9)

/* logging */
static int log_level = WLR_ERROR;

/* Autostart */
static const char *const autostart[] = {
	"sh", "-c", "scripts/autostart.sh", NULL,
	"sh", "-c", "scripts/start_eww.sh", NULL,
	NULL  /* terminate */
};


/* NOTE: ALWAYS keep a rule declared even if you don't use rules (e.g leave at least one example) */
static const Rule rules[] = {
	/* app_id             title       tags mask  switchtotag   isfloating   monitor */
	/* examples: */
	{ "firefox",  NULL,       1 << 1,     1,	0,           -1 }, 
	{ "dolphin",  NULL,       1 << 4,     0,	0,           -1 }, 
	{ "org.telegram.desktop._353c6751dd3837b1ed6ebfcdc83f2de9",  NULL,       1 << 2,    1,     0,           -1 }, 

};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
/* (x=-1 y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than ( -1) cause problems with Xwayland clients
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899
*/
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't be used */
static const MonitorRule monrules[] = {
	/* name       mfact  nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, -1, -1 },
	*/
	/* defaults */
	{ NULL,       0.5f,  1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,  -1, -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	.layout = "us", 
	.variant = "altgr-intl",
	.options = NULL,	
};

static const int repeat_rate = 30;
static const int repeat_delay = 300;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for SUPER, use WLR_MODIFIER_LOGO */
#define SUPER WLR_MODIFIER_LOGO
#define SHIFT WLR_MODIFIER_SHIFT
#define CTRL WLR_MODIFIER_CTRL
#define TAGKEYS(KEY,SKEY,TAG) \
	{ SUPER,                     KEY,            view,            {.ui = 1 << TAG} }, \
	{ SUPER|CTRL,    KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ SUPER|SHIFT,   SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ SUPER|CTRL|SHIFT, SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[] = { "alacritty", NULL };
static const char *webcmd[] = { "firefox", NULL };
static const char *telegramcmd[] = { "Telegram", NULL };
static const char *pulsecmd[] = { "pavucontrol", NULL };
static const char *menucmd[] = { "scripts/wl-script","runbmenu", NULL };
static const char *printcmd[] = { "scripts/wl-script","print_screenshot", NULL };
static const char *packagescmd[] = { "alacritty","-e","vifm","/build/ports","/build/ports", NULL };
static const char *cavacmd[] = { "alacritty","-e","cava", NULL };
static const char *btmcmd[] = { "alacritty","-e","btm", NULL };
static const char *brootcmd[] = { "alacritty","-e","broot", NULL };
static const char *dolphincmd[] = { "dolphin", NULL };
static const char *volumeup[] = { "scripts/wl-script","volume_up", NULL };
static const char *volumedown[] = { "scripts/wl-script","volume_down", NULL };
static const char *volumemute[] = { "scripts/wl-script","volume_mute", NULL };
static const char *rofi[] = { ".config/rofi/launchers/type-2/launcher.sh", NULL };
static const char *poweroff[] = { "scripts/wl-script","power_off", NULL };
static const char *reboot[] = { "scripts/wl-script","power_reboot", NULL };


static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                   key                 function        argument */
	{ SUPER,                     XKB_KEY_r,          spawn,          {.v = menucmd} },
	{ SUPER,		      XKB_KEY_Return,     spawn,          {.v = termcmd} },
	{ SUPER|SHIFT,  XKB_KEY_Y,	  spawn,          {.v = webcmd} },
	{ SUPER|SHIFT,  XKB_KEY_T,	  spawn,          {.v = telegramcmd} },
	{ 0,			      XKB_KEY_Print,      spawn,          {.v = printcmd} },
	{ SUPER|SHIFT,  XKB_KEY_P,		 spawn,          {.v = packagescmd} },
	{ SUPER|SHIFT,  XKB_KEY_C,		 spawn,          {.v = cavacmd} },
	{ SUPER|SHIFT,  XKB_KEY_B,		 spawn,          {.v = brootcmd} },
	{ SUPER|SHIFT,  XKB_KEY_F,		 spawn,          {.v = dolphincmd} },
	{ SUPER|SHIFT,  XKB_KEY_V,		 spawn,          {.v = pulsecmd} },
	{ SUPER|CTRL,   XKB_KEY_t,		 spawn,          {.v = btmcmd} },
	{ 0,			      XKB_KEY_XF86AudioRaiseVolume,	spawn,         {.v = volumeup} },
	{ 0,			      XKB_KEY_XF86AudioLowerVolume,	spawn,         {.v = volumedown} },
	{ 0,			      XKB_KEY_XF86AudioMute,		spawn,          {.v = volumemute} },
	{ SUPER|CTRL,   XKB_KEY_s,		 spawn,          {.v = poweroff} },
	{ SUPER|CTRL,   XKB_KEY_r,		 spawn,          {.v = reboot} },
	{ SUPER|SHIFT,  XKB_KEY_M,		 spawn,          {.v = rofi} },
	{ SUPER,                     XKB_KEY_b,          togglebar,      {0} },
	{ SUPER,                     XKB_KEY_j,          focusstack,     {.i = +1} },
	{ SUPER,                     XKB_KEY_k,          focusstack,     {.i = -1} },
	{ SUPER|SHIFT,  XKB_KEY_J,	  movestack,	  {.i = -1 } },
	{ SUPER|SHIFT,  XKB_KEY_K,	  movestack,	  {.i = +1 } },
	{ SUPER,                     XKB_KEY_i,          incnmaster,     {.i = +1} },
	{ SUPER,                     XKB_KEY_d,          incnmaster,     {.i = -1} },
	{ SUPER,                     XKB_KEY_h,          setmfact,       {.f = -0.05f} },
	{ SUPER,                     XKB_KEY_l,          setmfact,       {.f = +0.05f} },
	{ SUPER|SHIFT,  XKB_KEY_Return,     zoom,           {0} },
	{ SUPER,                     XKB_KEY_Tab,        view,           {0} },
	{ SUPER|SHIFT,  XKB_KEY_N,          killclient,     {0} },
	{ SUPER,                     XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ SUPER,                     XKB_KEY_f,          setlayout,      {.v = &layouts[1]} },
	{ SUPER,                     XKB_KEY_m,          setlayout,      {.v = &layouts[2]} },
	{ SUPER,                     XKB_KEY_space,      setlayout,      {0} },
	{ SUPER|SHIFT,  XKB_KEY_space,      togglefloating, {0} },
	{ SUPER,                     XKB_KEY_e,          togglefullscreen, {0} },
	{ SUPER,                     XKB_KEY_0,          view,           {.ui = ~0} },
	{ SUPER|SHIFT,  XKB_KEY_parenright, tag,            {.ui = ~0} },
	{ SUPER,                     XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ SUPER,                     XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ SUPER|SHIFT,  XKB_KEY_less,       tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ SUPER|SHIFT,  XKB_KEY_greater,    tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	{ SUPER,		      XKB_KEY_Left,	  focusdir,       {.i = 0} },
	{ SUPER,                     XKB_KEY_Right,      focusdir,       {.i = 1} },
	{ SUPER,                     XKB_KEY_Up,         focusdir,       {.i = 2} },
	{ SUPER,		      XKB_KEY_Down,       focusdir,       {.i = 3} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),
	{ SUPER|SHIFT,  XKB_KEY_Q,          quit,           {0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ CTRL|WLR_MODIFIER_LOGO,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ SUPER, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ SUPER, BTN_MIDDLE, togglefloating, {0} },
	{ SUPER, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
