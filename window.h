#if defined (__cplusplus)
# pragma once
#endif
#
#if !defined (_window_h_)
# define _window_h_ 1
#
# /* WINDEF (window.h API) - global functions */
# if !defined (WINDEF)
#  define WINDEF extern inline
# endif /* WINDEF */
#
# /* WININT (window.h internal API) - internal static functions */
# if !defined (WININT)
#  define WININT static inline
# endif /* WININT */
#
# /* Define platform macros */
# if defined (__linux__)
#  define WINDOW_PLATFORM "linux"
#  define WINDOW_PLATFORM_LINUX 1
#  /* define default backend if none is defined */
#  if !defined (WINDOW_BACKEND_X11) && !defined (WINDOW_BACKEND_WAYLAND)
#   define WINDOW_BACKEND_X11 1 /* by default window.h picks X11 for *nix platforms */
#  endif
#
# elif defined (__APPLE__) || defined (__MACH__)
#  define WINDOW_PLATFORM "apple"
#  define WINDOW_PLATFORM_APPLE 1
#
# elif defined (__CYGWIN__) || defined (_WIN32)
#  define WINDOW_PLATFORM "win32"
#  define WINDOW_PLATFORM_WIN32 1
#
# elif defined (__FreeBSD__) || defined (__NetBSD__) || defined (__bsdi__) || defined (__DragonFly__) || defined (__MidnightBSD__)
#  define WINDOW_PLATFORM "bsd"
#  define WINDOW_PLATFORM_BSD 1
#  /* define default backend if none is defined */
#  if !defined (WINDOW_BACKEND_X11) && !defined (WINDOW_BACKEND_WAYLAND)
#   define WINDOW_BACKEND_X11 1 /* by default window.h picks X11 for *nix platforms */
#  endif
#
# else
#  error /* No valid platform found */
# endif
#
# /* Preprocessor configuration */
#
# if !defined (WINDOW_EVENT_QUEUE_CAPACITY)
#  define WINDOW_EVENT_QUEUE_CAPACITY 1024
# endif /* WINDOW_EVENT_QUEUE_CAPACITY */
#
# include <stddef.h>
# include <stdint.h>

/* inputs */

enum {
    WINDOW_BUTTON_NONE = 0,
# define WINDOW_BUTTON_NONE WINDOW_BUTTON_NONE

    WINDOW_BUTTON_LEFT,
# define WINDOW_BUTTON_LEFT WINDOW_BUTTON_LEFT

    WINDOW_BUTTON_RIGHT,
# define WINDOW_BUTTON_RIGHT WINDOW_BUTTON_RIGHT

    WINDOW_BUTTON_MIDDLE,
# define WINDOW_BUTTON_MIDDLE WINDOW_BUTTON_MIDDLE

    /* ... */
};

enum {
    WINDOW_KEY_NONE = 0,
# define WINDOW_KEY_NONE WINDOW_KEY_NONE

    WINDOW_KEY_ESCAPE = 0x100,
# define WINDOW_KEY_ESCAPE WINDOW_KEY_ESCAPE

    WINDOW_KEY_F1 = 0x101,
# define WINDOW_KEY_F1 WINDOW_KEY_F1

    WINDOW_KEY_F2 = 0x102,
# define WINDOW_KEY_F2 WINDOW_KEY_F2

    WINDOW_KEY_F3 = 0x103,
# define WINDOW_KEY_F3 WINDOW_KEY_F3

    WINDOW_KEY_F4 = 0x104,
# define WINDOW_KEY_F4 WINDOW_KEY_F4

    WINDOW_KEY_F5 = 0x105,
# define WINDOW_KEY_F5 WINDOW_KEY_F5

    WINDOW_KEY_F6 = 0x106,
# define WINDOW_KEY_F6 WINDOW_KEY_F6

    WINDOW_KEY_F7 = 0x107,
# define WINDOW_KEY_F7 WINDOW_KEY_F7

    WINDOW_KEY_F8 = 0x108,
# define WINDOW_KEY_F8 WINDOW_KEY_F8

    WINDOW_KEY_F9 = 0x109,
# define WINDOW_KEY_F9 WINDOW_KEY_F9

    WINDOW_KEY_F10 = 0x10A,
# define WINDOW_KEY_F10 WINDOW_KEY_F10

    WINDOW_KEY_F11 = 0x10B,
# define WINDOW_KEY_F11 WINDOW_KEY_F11

    WINDOW_KEY_F12 = 0x10C,
# define WINDOW_KEY_F12 WINDOW_KEY_F12

    WINDOW_KEY_GRAVE = 0x60,
# define WINDOW_KEY_GRAVE WINDOW_KEY_GRAVE

    WINDOW_KEY_ONE = 0x31,
# define WINDOW_KEY_ONE WINDOW_KEY_ONE

    WINDOW_KEY_TWO = 0x32,
# define WINDOW_KEY_TWO WINDOW_KEY_TWO

    WINDOW_KEY_THREE = 0x33,
# define WINDOW_KEY_THREE WINDOW_KEY_THREE

    WINDOW_KEY_FOUR = 0x34,
# define WINDOW_KEY_FOUR WINDOW_KEY_FOUR

    WINDOW_KEY_FIVE = 0x35,
# define WINDOW_KEY_FIVE WINDOW_KEY_FIVE

    WINDOW_KEY_SIX = 0x36,
# define WINDOW_KEY_SIX WINDOW_KEY_SIX

    WINDOW_KEY_SEVEN = 0x37,
# define WINDOW_KEY_SEVEN WINDOW_KEY_SEVEN

    WINDOW_KEY_EIGHT = 0x38,
# define WINDOW_KEY_EIGHT WINDOW_KEY_EIGHT

    WINDOW_KEY_NINE = 0x39,
# define WINDOW_KEY_NINE WINDOW_KEY_NINE

    WINDOW_KEY_ZERO = 0x30,
# define WINDOW_KEY_ZERO WINDOW_KEY_ZERO

    WINDOW_KEY_DASH = 0x2D,
# define WINDOW_KEY_DASH WINDOW_KEY_DASH

    WINDOW_KEY_EQUAL = 0x3D,
# define WINDOW_KEY_EQUAL WINDOW_KEY_EQUAL

    WINDOW_KEY_BACKSPACE = 0x08,
# define WINDOW_KEY_BACKSPACE WINDOW_KEY_BACKSPACE

    WINDOW_KEY_TAB = 0x09,
# define WINDOW_KEY_TAB WINDOW_KEY_TAB

    WINDOW_KEY_Q = 0x51,
# define WINDOW_KEY_Q WINDOW_KEY_Q

    WINDOW_KEY_W = 0x57,
# define WINDOW_KEY_W WINDOW_KEY_W

    WINDOW_KEY_E = 0x45,
# define WINDOW_KEY_E WINDOW_KEY_E

    WINDOW_KEY_R = 0x52,
# define WINDOW_KEY_R WINDOW_KEY_R

    WINDOW_KEY_T = 0x54,
# define WINDOW_KEY_T WINDOW_KEY_T

    WINDOW_KEY_Y = 0x59,
# define WINDOW_KEY_Y WINDOW_KEY_Y

    WINDOW_KEY_U = 0x55,
# define WINDOW_KEY_U WINDOW_KEY_U

    WINDOW_KEY_I = 0x49,
# define WINDOW_KEY_I WINDOW_KEY_I

    WINDOW_KEY_O = 0x4F,
# define WINDOW_KEY_O WINDOW_KEY_O

    WINDOW_KEY_P = 0x50,
# define WINDOW_KEY_P WINDOW_KEY_P

    WINDOW_KEY_OBRACE = 0x5B,
# define WINDOW_KEY_OBRACE WINDOW_KEY_OBRACE

    WINDOW_KEY_CBRACE = 0x5D,
# define WINDOW_KEY_CBRACE WINDOW_KEY_CBRACE

    WINDOW_KEY_CAPSLOCK = 0,
# define WINDOW_KEY_CAPSLOCK WINDOW_KEY_CAPSLOCK

    WINDOW_KEY_A = 0x41,
# define WINDOW_KEY_A WINDOW_KEY_A

    WINDOW_KEY_S = 0x53,
# define WINDOW_KEY_S WINDOW_KEY_S

    WINDOW_KEY_D = 0x44,
# define WINDOW_KEY_D WINDOW_KEY_D

    WINDOW_KEY_F = 0x46,
# define WINDOW_KEY_F WINDOW_KEY_F

    WINDOW_KEY_G = 0x47,
# define WINDOW_KEY_G WINDOW_KEY_G

    WINDOW_KEY_H = 0x48,
# define WINDOW_KEY_H WINDOW_KEY_H

    WINDOW_KEY_J = 0x4A,
# define WINDOW_KEY_J WINDOW_KEY_J

    WINDOW_KEY_K = 0x4B,
# define WINDOW_KEY_K WINDOW_KEY_K

    WINDOW_KEY_L = 0x4C,
# define WINDOW_KEY_L WINDOW_KEY_L

    WINDOW_KEY_SEMICOLON = 0x3B,
# define WINDOW_KEY_SEMICOLON WINDOW_KEY_SEMICOLON

    WINDOW_KEY_QUOTE = 0x27,
# define WINDOW_KEY_QUOTE WINDOW_KEY_QUOTE

    WINDOW_KEY_BACKSLASH = 0x5C,
# define WINDOW_KEY_BACKSLASH WINDOW_KEY_BACKSLASH

    WINDOW_KEY_ENTER = 0x0D,
# define WINDOW_KEY_ENTER WINDOW_KEY_ENTER

    WINDOW_KEY_LSHIFT = 0x120,
# define WINDOW_KEY_LSHIFT WINDOW_KEY_LSHIFT

    WINDOW_KEY_Z = 0x5A,
# define WINDOW_KEY_Z WINDOW_KEY_Z

    WINDOW_KEY_X = 0x58,
# define WINDOW_KEY_X WINDOW_KEY_X

    WINDOW_KEY_C = 0x43,
# define WINDOW_KEY_C WINDOW_KEY_C

    WINDOW_KEY_V = 0x56,
# define WINDOW_KEY_V WINDOW_KEY_V

    WINDOW_KEY_B = 0x42,
# define WINDOW_KEY_B WINDOW_KEY_B

    WINDOW_KEY_N = 0x4E,
# define WINDOW_KEY_N WINDOW_KEY_N

    WINDOW_KEY_M = 0x4D,
# define WINDOW_KEY_M WINDOW_KEY_M

    WINDOW_KEY_COMMA = 0x2C,
# define WINDOW_KEY_COMMA WINDOW_KEY_COMMA

    WINDOW_KEY_PERIOD = 0x2E,
# define WINDOW_KEY_PERIOD WINDOW_KEY_PERIOD

    WINDOW_KEY_SLASH = 0x2F,
# define WINDOW_KEY_SLASH WINDOW_KEY_SLASH

    WINDOW_KEY_RSHIFT = 0x121,
# define WINDOW_KEY_RSHIFT WINDOW_KEY_RSHIFT

    WINDOW_KEY_LCTRL = 0x122,
# define WINDOW_KEY_LCTRL WINDOW_KEY_LCTRL

    WINDOW_KEY_MOD = 0x123,
# define WINDOW_KEY_MOD WINDOW_KEY_MOD

    WINDOW_KEY_LALT = 0x124,
# define WINDOW_KEY_LALT WINDOW_KEY_LALT

    WINDOW_KEY_SPACE = 0x20,
# define WINDOW_KEY_SPACE WINDOW_KEY_SPACE

    WINDOW_KEY_RALT = 0x125,
# define WINDOW_KEY_RALT WINDOW_KEY_RALT

    WINDOW_KEY_RCTRL = 0x126,
# define WINDOW_KEY_RCTRL WINDOW_KEY_RCTRL

    WINDOW_KEY_PRINTSCREEN = 0x127,
# define WINDOW_KEY_PRINTSCREEN WINDOW_KEY_PRINTSCREEN

    WINDOW_KEY_SCROLLLOCK = 0x128,
# define WINDOW_KEY_SCROLLLOCK WINDOW_KEY_SCROLLLOCK

    WINDOW_KEY_PAUSE = 0x129,
# define WINDOW_KEY_PAUSE WINDOW_KEY_PAUSE

    WINDOW_KEY_INSERT = 0x144,
# define WINDOW_KEY_INSERT WINDOW_KEY_INSERT

    WINDOW_KEY_HOME = 0x145,
# define WINDOW_KEY_HOME WINDOW_KEY_HOME

    WINDOW_KEY_PAGEUP = 0x146,
# define WINDOW_KEY_PAGEUP WINDOW_KEY_PAGEUP

    WINDOW_KEY_DELETE = 0x147,
# define WINDOW_KEY_DELETE WINDOW_KEY_DELETE

    WINDOW_KEY_END = 0x148,
# define WINDOW_KEY_END WINDOW_KEY_END

    WINDOW_KEY_PAGEDOWN = 0x149,
# define WINDOW_KEY_PAGEDOWN WINDOW_KEY_PAGEDOWN

    WINDOW_KEY_UP = 0x140,
# define WINDOW_KEY_UP WINDOW_KEY_UP

    WINDOW_KEY_LEFT = 0x141,
# define WINDOW_KEY_LEFT WINDOW_KEY_LEFT

    WINDOW_KEY_DOWN = 0x142,
# define WINDOW_KEY_DOWN WINDOW_KEY_DOWN

    WINDOW_KEY_RIGHT = 0x143,
# define WINDOW_KEY_RIGHT WINDOW_KEY_RIGHT

    WINDOW_KEY_NUMLOCK = 0x12A,
# define WINDOW_KEY_NUMLOCK WINDOW_KEY_NUMLOCK

    WINDOW_KEY_NUMSLASH = 0x16A,
# define WINDOW_KEY_NUMSLASH WINDOW_KEY_NUMSLASH

    WINDOW_KEY_NUMSTAR = 0x16B,
# define WINDOW_KEY_NUMSTAR WINDOW_KEY_NUMSTAR

    WINDOW_KEY_NUMDASH = 0x16C,
# define WINDOW_KEY_NUMDASH WINDOW_KEY_NUMDASH

    WINDOW_KEY_NUM7 = 0x167,
# define WINDOW_KEY_NUM7 WINDOW_KEY_NUM7

    WINDOW_KEY_NUM8 = 0x168,
# define WINDOW_KEY_NUM8 WINDOW_KEY_NUM8

    WINDOW_KEY_NUM9 = 0x169,
# define WINDOW_KEY_NUM9 WINDOW_KEY_NUM9

    WINDOW_KEY_NUM4 = 0x164,
# define WINDOW_KEY_NUM4 WINDOW_KEY_NUM4

    WINDOW_KEY_NUM5 = 0x165,
# define WINDOW_KEY_NUM5 WINDOW_KEY_NUM5

    WINDOW_KEY_NUM6 = 0x166,
# define WINDOW_KEY_NUM6 WINDOW_KEY_NUM6

    WINDOW_KEY_NUM1 = 0x161,
# define WINDOW_KEY_NUM1 WINDOW_KEY_NUM1

    WINDOW_KEY_NUM2 = 0x162,
# define WINDOW_KEY_NUM2 WINDOW_KEY_NUM2

    WINDOW_KEY_NUM3 = 0x163,
# define WINDOW_KEY_NUM3 WINDOW_KEY_NUM3

    WINDOW_KEY_NUM0 = 0x160,
# define WINDOW_KEY_NUM0 WINDOW_KEY_NUM0

    WINDOW_KEY_NUMSEP = 0x16D,
# define WINDOW_KEY_NUMSEP WINDOW_KEY_NUMSEP

    WINDOW_KEY_NUMPLUS = 0x16E,
# define WINDOW_KEY_NUMPLUS WINDOW_KEY_NUMPLUS

    WINDOW_KEY_NUMENTER = 0x16F,
# define WINDOW_KEY_NUMENTER WINDOW_KEY_NUMENTER

    /* ... */
};

/* library functions */

enum {
    WINDOW_PROP_PLATFORM_NONE = 0,
# define WINDOW_PROP_PLATFORM_NONE WINDOW_PROP_PLATFORM_NONE

    /* X11 properties */

    WINDOW_PROP_PLATFORM_X11_DISPLAY,
# define WINDOW_PROP_PLATFORM_X11_DISPLAY WINDOW_PROP_PLATFORM_X11_DISPLAY

    WINDOW_PROP_PLATFORM_X11_ROOT_ID,
# define WINDOW_PROP_PLATFORM_X11_ROOT_ID WINDOW_PROP_PLATFORM_X11_ROOT_ID

    WINDOW_PROP_PLATFORM_X11_SCREEN_ID,
# define WINDOW_PROP_PLATFORM_X11_SCREEN_ID WINDOW_PROP_PLATFORM_X11_SCREEN_ID

    /* ... */
};

WINDEF int win_init(void);

WINDEF int win_quit(void);

WINDEF int win_getsize(size_t *, size_t *);

WINDEF void *win_getprop(const uint64_t);

/* windowing functions */

enum {
    WINDOW_PROP_WINDOW_NONE = 0,
# define WINDOW_PROP_WINDOW_NONE WINDOW_PROP_WINDOW_NONE

    /* X11 properties */

    WINDOW_PROP_WINDOW_X11_DISPLAY,
# define WINDOW_PROP_WINDOW_X11_DISPLAY WINDOW_PROP_WINDOW_X11_DISPLAY

    WINDOW_PROP_WINDOW_X11_ROOT_ID,
# define WINDOW_PROP_WINDOW_X11_ROOT_ID WINDOW_PROP_WINDOW_X11_ROOT_ID

    WINDOW_PROP_WINDOW_X11_SCREEN_ID,
# define WINDOW_PROP_WINDOW_X11_SCREEN_ID WINDOW_PROP_WINDOW_X11_SCREEN_ID

    WINDOW_PROP_WINDOW_X11_WINDOW_ID,
# define WINDOW_PROP_WINDOW_X11_WINDOW_ID WINDOW_PROP_WINDOW_X11_WINDOW_ID

    WINDOW_PROP_WINDOW_X11_VISUAL,
# define WINDOW_PROP_WINDOW_X11_VISUAL WINDOW_PROP_WINDOW_X11_VISUAL

    /* ... */
};

typedef struct s_window *t_window;

WINDEF int win_wincreate(t_window *, const size_t, const size_t, const char *, const uint64_t);

WINDEF int win_windestroy(t_window);

WINDEF int win_winmap(t_window);

WINDEF int win_winunmap(t_window);

WINDEF int win_wingetsize(t_window, size_t *, size_t *);

WINDEF int win_winsetsize(t_window, const size_t, const size_t);

WINDEF int win_winsetsizemin(t_window, const size_t, const size_t);

WINDEF int win_winsetsizemax(t_window, const size_t, const size_t);

WINDEF int win_wingetpos(t_window, size_t *, size_t *);

WINDEF int win_winsetpos(t_window, const size_t, const size_t);

WINDEF int win_winsetminim(t_window);

WINDEF int win_winsetmaxim(t_window);

WINDEF int win_winsetfullscr(t_window);

WINDEF int win_wingettitle(t_window, char **);

WINDEF int win_winsettitle(t_window, const char *);

WINDEF void *win_wingetprop(t_window, const uint64_t);

/* event functions */

enum {

    WINDOW_EVENT_NONE = 0,
# define WINDOW_EVENT_NONE WINDOW_EVENT_NONE

    WINDOW_EVENT_QUIT,
# define WINDOW_EVENT_QUIT WINDOW_EVENT_QUIT

    WINDOW_EVENT_MOUSE_MOTION,
# define WINDOW_EVENT_MOUSE_MOTION WINDOW_EVENT_MOUSE_MOTION

    WINDOW_EVENT_MOUSE_BUTTON,
# define WINDOW_EVENT_MOUSE_BUTTON WINDOW_EVENT_MOUSE_BUTTON

    WINDOW_EVENT_MOUSE_SCROLL,
# define WINDOW_EVENT_MOUSE_SCROLL WINDOW_EVENT_MOUSE_SCROLL

    WINDOW_EVENT_KEYBOARD_KEY,
# define WINDOW_EVENT_KEYBOARD_KEY WINDOW_EVENT_KEYBOARD_KEY

    WINDOW_EVENT_WINDOW_RESIZE,
# define WINDOW_EVENT_WINDOW_RESIZE WINDOW_EVENT_WINDOW_RESIZE

    WINDOW_EVENT_WINDOW_MOTION,
# define WINDOW_EVENT_WINDOW_MOTION WINDOW_EVENT_WINDOW_MOTION

    /* ... */

    WINDOW_EVENT_COUNT
# define WINDOW_EVENT_COUNT WINDOW_EVENT_COUNT

};


typedef struct s_eventCommon t_eventCommon;

struct s_eventCommon {
    uint32_t type;
    uint64_t timestamp;
};


typedef struct s_eventQuit t_eventQuit;

struct s_eventQuit {
    uint32_t type;
    uint64_t timestamp;
};


typedef struct s_eventMouseMotion t_eventMouseMotion;

struct s_eventMouseMotion {
    uint32_t type;
    uint64_t timestamp;

    int32_t x, xrel;
    int32_t y, yrel;
};


typedef struct s_eventMouseButton t_eventMouseButton;

struct s_eventMouseButton {
    uint32_t type;
    uint64_t timestamp;

    int8_t btn;
    int8_t state;
};


typedef struct s_eventMouseScroll t_eventMouseScroll;

struct s_eventMouseScroll {
    uint32_t type;
    uint64_t timestamp;

    int8_t scroll;
};


typedef struct s_eventKeyboardKey t_eventKeyboardKey;

struct s_eventKeyboardKey {
    uint32_t type;
    uint64_t timestamp;

    int32_t key;
    int8_t  state;
};


typedef struct s_eventWindow t_eventWindow;

struct s_eventWindow {
    uint32_t type;
    uint64_t timestamp;

    uint32_t x, y;
    uint32_t w, h;
};


typedef union u_event t_event;

union u_event {
    uint32_t type;

    /* common event */
    t_eventCommon common;

    /* mouse event */
    t_eventMouseMotion motion;
    t_eventMouseButton button;

    /* keyboard event */
    t_eventKeyboardKey key;

    /* window event */
    t_eventWindow window;
};

WINDEF int win_eventpoll(t_event *);

WINDEF int win_eventwait(t_event *);

WINDEF int win_eventpush(t_event *);

WINDEF int win_eventpop(t_event *);

WINDEF int win_eventflush(void);

/* timing functions */

WINDEF uint64_t win_timeget(void);

WINDEF int win_timewait(uint64_t);

# if defined WINDOW_IMPLEMENTATION
#
#  include <stdlib.h>
#
#  /* WINDOW_BACKEND_X11 - Unix X11 implementation layer */
#  if defined (WINDOW_BACKEND_X11)
#   include <unistd.h>
#   include <sys/time.h>
#
#   include <X11/X.h>
#   include <X11/Xlib.h>
#   include <X11/Xutil.h>
#   include <X11/Xatom.h>
#   include <X11/XKBlib.h>
#   include <X11/keysym.h>
#   include <X11/keysymdef.h>

struct s_keymap {
    uint32_t src;
    uint32_t dst;
};

static const struct s_keymap g_keymap[] = {
    
    { XK_Escape, WINDOW_KEY_ESCAPE },
    
    { XK_F1, WINDOW_KEY_F1 },
    
    { XK_F2, WINDOW_KEY_F2 },
    
    { XK_F3, WINDOW_KEY_F3 },
    
    { XK_F4, WINDOW_KEY_F4 },
    
    { XK_F5, WINDOW_KEY_F5 },
    
    { XK_F6, WINDOW_KEY_F6 },
    
    { XK_F7, WINDOW_KEY_F7 },
    
    { XK_F8, WINDOW_KEY_F8 },
    
    { XK_F9, WINDOW_KEY_F9 },
    
    { XK_F10, WINDOW_KEY_F10 },
    
    { XK_F11, WINDOW_KEY_F11 },
    
    { XK_F12, WINDOW_KEY_F12 },
    
    { XK_grave, WINDOW_KEY_GRAVE }, 
    { XK_asciitilde, WINDOW_KEY_GRAVE },
    
    { XK_1, WINDOW_KEY_ONE },       
    { XK_exclam, WINDOW_KEY_ONE },
    
    { XK_2, WINDOW_KEY_TWO },       
    { XK_at, WINDOW_KEY_TWO },
    
    { XK_3, WINDOW_KEY_THREE },     
    { XK_numbersign, WINDOW_KEY_THREE },
    
    { XK_4, WINDOW_KEY_FOUR },      
    { XK_dollar, WINDOW_KEY_FOUR },
    
    { XK_5, WINDOW_KEY_FIVE },      
    { XK_percent, WINDOW_KEY_FIVE },
    
    { XK_6, WINDOW_KEY_SIX },       
    { XK_asciicircum, WINDOW_KEY_SIX },
    
    { XK_7, WINDOW_KEY_SEVEN },     
    { XK_ampersand, WINDOW_KEY_SEVEN },
    
    { XK_8, WINDOW_KEY_EIGHT },     
    { XK_asterisk, WINDOW_KEY_EIGHT },
    
    { XK_9, WINDOW_KEY_NINE },      
    { XK_parenleft, WINDOW_KEY_NINE },
    
    { XK_0, WINDOW_KEY_ZERO },      
    { XK_parenright, WINDOW_KEY_ZERO },
    
    { XK_minus, WINDOW_KEY_DASH },  
    { XK_underscore, WINDOW_KEY_DASH },
    
    { XK_equal, WINDOW_KEY_EQUAL },
    { XK_plus, WINDOW_KEY_EQUAL },
    
    { XK_BackSpace, WINDOW_KEY_BACKSPACE },
    
    { XK_Tab, WINDOW_KEY_TAB },
    
    { XK_Q, WINDOW_KEY_Q },
    { XK_q, WINDOW_KEY_Q },
    
    { XK_W, WINDOW_KEY_W },
    { XK_w, WINDOW_KEY_W },
    
    { XK_E, WINDOW_KEY_E },
    { XK_e, WINDOW_KEY_E },
    
    { XK_R, WINDOW_KEY_R },
    { XK_r, WINDOW_KEY_R },
    
    { XK_T, WINDOW_KEY_T },
    { XK_t, WINDOW_KEY_T },
    
    { XK_Y, WINDOW_KEY_Y },
    { XK_y, WINDOW_KEY_Y },
    
    { XK_U, WINDOW_KEY_U },
    { XK_u, WINDOW_KEY_U },
    
    { XK_I, WINDOW_KEY_I },
    { XK_i, WINDOW_KEY_I },
    
    { XK_O, WINDOW_KEY_O },
    { XK_o, WINDOW_KEY_O },
    
    { XK_P, WINDOW_KEY_P },
    { XK_p, WINDOW_KEY_P },
    
    { XK_bracketleft, WINDOW_KEY_OBRACE },
    { XK_braceleft, WINDOW_KEY_OBRACE },
    
    { XK_bracketright, WINDOW_KEY_CBRACE },
    { XK_braceright, WINDOW_KEY_CBRACE },

    { XK_Caps_Lock, WINDOW_KEY_CAPSLOCK },

    { XK_A, WINDOW_KEY_A },
    { XK_a, WINDOW_KEY_A },

    { XK_S, WINDOW_KEY_S },
    { XK_s, WINDOW_KEY_S },

    { XK_D, WINDOW_KEY_D },
    { XK_d, WINDOW_KEY_D },

    { XK_F, WINDOW_KEY_F },
    { XK_f, WINDOW_KEY_F },

    { XK_G, WINDOW_KEY_G },
    { XK_g, WINDOW_KEY_G },

    { XK_H, WINDOW_KEY_H },
    { XK_h, WINDOW_KEY_H },

    { XK_J, WINDOW_KEY_J },
    { XK_j, WINDOW_KEY_J },

    { XK_K, WINDOW_KEY_K },
    { XK_k, WINDOW_KEY_K },

    { XK_L, WINDOW_KEY_L },
    { XK_l, WINDOW_KEY_L },

    { XK_semicolon, WINDOW_KEY_SEMICOLON },
    { XK_colon, WINDOW_KEY_SEMICOLON },

    { XK_apostrophe, WINDOW_KEY_QUOTE },
    { XK_quotedbl, WINDOW_KEY_QUOTE },

    { XK_backslash, WINDOW_KEY_BACKSLASH },
    { XK_bar, WINDOW_KEY_BACKSLASH },

    { XK_Return, WINDOW_KEY_ENTER },

    { XK_Shift_L, WINDOW_KEY_LSHIFT },
    
    { XK_Z, WINDOW_KEY_Z },
    { XK_z, WINDOW_KEY_Z },
    
    { XK_X, WINDOW_KEY_X },
    { XK_x, WINDOW_KEY_X },
    
    { XK_C, WINDOW_KEY_C },
    { XK_c, WINDOW_KEY_C },
    
    { XK_V, WINDOW_KEY_V },
    { XK_v, WINDOW_KEY_V },
    
    { XK_B, WINDOW_KEY_B },
    { XK_b, WINDOW_KEY_B },
    
    { XK_N, WINDOW_KEY_N },
    { XK_n, WINDOW_KEY_N },
    
    { XK_M, WINDOW_KEY_M },
    { XK_m, WINDOW_KEY_M },
    
    { XK_comma, WINDOW_KEY_COMMA },
    { XK_less, WINDOW_KEY_COMMA },
    
    { XK_period, WINDOW_KEY_PERIOD },
    { XK_greater, WINDOW_KEY_PERIOD },
    
    { XK_slash, WINDOW_KEY_SLASH },
    { XK_question, WINDOW_KEY_SLASH },
    
    { XK_Shift_R, WINDOW_KEY_RSHIFT },
    
    { XK_Control_L, WINDOW_KEY_LCTRL },
    
    { XK_Super_L, WINDOW_KEY_MOD },
    
    { XK_Alt_L, WINDOW_KEY_LALT },
    
    { XK_space, WINDOW_KEY_SPACE },
    
    { XK_Alt_R, WINDOW_KEY_RALT },
    
    { XK_Control_R, WINDOW_KEY_RCTRL },

    { XK_Print, WINDOW_KEY_PRINTSCREEN },
    
    { XK_Scroll_Lock, WINDOW_KEY_SCROLLLOCK },
    
    { XK_Pause, WINDOW_KEY_PAUSE },

    { XK_Insert, WINDOW_KEY_INSERT },
    
    { XK_Home, WINDOW_KEY_HOME },
    
    { XK_Prior, WINDOW_KEY_PAGEUP },

    { XK_Delete, WINDOW_KEY_DELETE },
    
    { XK_End, WINDOW_KEY_END },
    
    { XK_Next, WINDOW_KEY_PAGEDOWN },

    { XK_Up, WINDOW_KEY_UP },
    
    { XK_Left, WINDOW_KEY_LEFT },
    
    { XK_Down, WINDOW_KEY_DOWN },
    
    { XK_Right, WINDOW_KEY_RIGHT },

    { XK_Num_Lock, WINDOW_KEY_NUMLOCK },
    
    { XK_KP_Divide, WINDOW_KEY_NUMSLASH },
    
    { XK_KP_Multiply, WINDOW_KEY_NUMSTAR },
    
    { XK_KP_Subtract, WINDOW_KEY_NUMDASH },
    
    { XK_KP_Home, WINDOW_KEY_NUM7 },
    { XK_KP_7, WINDOW_KEY_NUM7 },
    
    { XK_KP_Up, WINDOW_KEY_NUM8 },
    { XK_KP_8, WINDOW_KEY_NUM8 },
    
    { XK_KP_Prior, WINDOW_KEY_NUM9 },
    { XK_KP_9, WINDOW_KEY_NUM9 },
    
    { XK_KP_Left, WINDOW_KEY_NUM4 },
    { XK_KP_4, WINDOW_KEY_NUM4 },
    
    { XK_KP_Begin, WINDOW_KEY_NUM5 },
    { XK_KP_5, WINDOW_KEY_NUM5 },
    
    { XK_KP_Right, WINDOW_KEY_NUM6 },
    { XK_KP_6, WINDOW_KEY_NUM6 },
    
    { XK_KP_End, WINDOW_KEY_NUM1 },
    { XK_KP_1, WINDOW_KEY_NUM1 },
    
    { XK_KP_Down, WINDOW_KEY_NUM2 },
    { XK_KP_2, WINDOW_KEY_NUM2 },
    
    { XK_KP_Next, WINDOW_KEY_NUM3 },
    { XK_KP_3, WINDOW_KEY_NUM3 },
    
    { XK_KP_Insert, WINDOW_KEY_NUM0 },
    { XK_KP_0, WINDOW_KEY_NUM0 },
    
    { XK_KP_Delete, WINDOW_KEY_NUMSEP },
    
    { XK_KP_Add, WINDOW_KEY_NUMPLUS },
    
    { XK_KP_Enter, WINDOW_KEY_NUMENTER },

    /* ... */

    { 0, WINDOW_KEY_NONE }
};

struct s_platform {
    /* singly-linked list of windows 
     * (glfw3 style of window handling)
     * */
    struct s_window *win_ll;

    struct {
        Display *dpy;
        Window   root;
        XID      screen;
    } xlib;

    struct {
        Atom wm_protocols;
        Atom wm_delete_window;
    } xatom;

    struct {
        int depth;
        int class;
    } config;

    struct {
        t_event *arr;
        t_event *arr_s;
        t_event *arr_e;
        size_t   cap;
        size_t   cnt;
    } da_event;
};

struct s_window {
    struct s_window *next;

    struct {
        Display *dpy;
        Window   parent;
        Window   child;
        XID      screen;
    } xlib;
    
    struct {
        Atom wm_protocols;
        Atom wm_delete_window;
    } xatom;

    struct {
        XVisualInfo visual;
    } xutil;

    struct {
        /* position attributes */
        size_t x, y;

        /* dimension attributes */
        size_t w, h;
    } attr;
};

/* platform functions */

static struct s_platform *WINDOW = 0; 

WINDEF int win_init(void) {
    /* manage global platform object */
    if (WINDOW) { return (1); } /* check if `WINDOW` is not null. If so, return */

    /* alloc global platfom object */
    WINDOW = malloc(sizeof(struct s_platform));
    if (!WINDOW) { goto __win_init_failure; }

    /* connect to x11 server */
    Display *dpy = XOpenDisplay(0);
    if (!dpy) { goto __win_init_failure; }

    /* get the root window */
    XID root = XDefaultRootWindow(dpy);
    if (!root) { goto __win_init_failure; }

    /* get screen number */
    XID screen = XDefaultScreen(dpy);

    /* assign data to `xlib` platform section */
    WINDOW->xlib.dpy  = dpy;
    WINDOW->xlib.root = root;
    WINDOW->xlib.screen = screen;
   
    /* retrieve atoms from x11 session */
    Atom wm_protocols = XInternAtom(dpy, "WM_PROTOCOLS", False);
    if (!wm_protocols) { goto __win_init_failure; }
    
    Atom wm_delete_window = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
    if (!wm_delete_window) { goto __win_init_failure; }
    
    /* assign data to `xatom` platform section */
    WINDOW->xatom.wm_protocols     = wm_protocols;
    WINDOW->xatom.wm_delete_window = wm_delete_window;

    /* set default config values */
    WINDOW->config.depth = 24;
    WINDOW->config.class = TrueColor;

    /* initialize da_event */
    WINDOW->da_event.arr = 0;
    WINDOW->da_event.arr_s = 0;
    WINDOW->da_event.arr_e = 0;
    WINDOW->da_event.cap = 0;
    WINDOW->da_event.cnt = 0;

    /* set keyboard input repeating */
    Bool supported;
    XkbSetDetectableAutoRepeat(dpy, True, &supported);
    if (!supported) {
        goto __win_init_failure;
    }

    /* success */
    win_eventflush();
    return (1);

__win_init_failure:

    /* release xlib resources */
    if (WINDOW->xlib.dpy) { XCloseDisplay(WINDOW->xlib.dpy), WINDOW->xlib.dpy = 0; }

    /* release WINDOW */
    if (WINDOW) { free(WINDOW), WINDOW = 0; }

    /* success */
    return (0);
}


WINDEF int win_quit(void) {
    /* null-check */
    if (!WINDOW) { return (0); }

    /* deallocate all the windows */
    t_window curr = WINDOW->win_ll,
             next = 0;
    while (curr) {
        next = curr->next;
        win_windestroy(curr);
        curr = next;
    }
   
    /* deallocate event */
    if (WINDOW->da_event.arr) {
        free(WINDOW->da_event.arr);
        WINDOW->da_event.arr   = 0;
        WINDOW->da_event.arr_s = 0;
        WINDOW->da_event.arr_e = 0;
        WINDOW->da_event.cnt = 0;
        WINDOW->da_event.cap = 0;
    }

    /* terminate `xlib` */
    XCloseDisplay(WINDOW->xlib.dpy), WINDOW->xlib.dpy = 0;

    /* deallocate `WINDOW` object */
    free(WINDOW), WINDOW = 0;

    /* success */
    return (1);
}


WINDEF int win_getsize(size_t *w_ptr, size_t *h_ptr) {
    /* null-check */
    if (!WINDOW) { return (0); }

    /* query attributes */
    XWindowAttributes attr;
    if (!XGetWindowAttributes(WINDOW->xlib.dpy, WINDOW->xlib.root, &attr)) { return (0); }
    
    /* assign values */
    if (w_ptr) { *w_ptr = attr.width; }
    if (h_ptr) { *h_ptr = attr.height; }

    /* success */
	return (1);
}


WINDEF void *win_getprop(const uint64_t prop) {
    /* null-check */
    if (!WINDOW) { return (0); }
    switch (prop) {
        case (WINDOW_PROP_PLATFORM_X11_DISPLAY):   { return (WINDOW->xlib.dpy); }
        case (WINDOW_PROP_PLATFORM_X11_ROOT_ID):   { return (&WINDOW->xlib.root); }
        case (WINDOW_PROP_PLATFORM_X11_SCREEN_ID): { return (&WINDOW->xlib.screen); }

        default: { } break;
    }

    /* return nothing */
    return (0);
}

/* windowing functions */

WINDEF int win_wincreate(t_window *win, const size_t w, const size_t h, const char *t, const uint64_t f) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* allocate `result` window */
    t_window result = malloc(sizeof(struct s_window));
    if (!result) { goto __win_wincreate_failure; }
    
    /* NOTE:
     *  Temporarily disabled parameter
     * */
    (void) f;
    
    /* assign references to X11 objects */
    if (!WINDOW->xlib.dpy) { goto __win_wincreate_failure; }
    result->xlib.dpy  = WINDOW->xlib.dpy;
    
    if (!WINDOW->xlib.root) { goto __win_wincreate_failure; }
    result->xlib.parent = WINDOW->xlib.root;
    result->xlib.screen = WINDOW->xlib.screen;

    /* assign references to X11 atoms */
    result->xatom.wm_protocols = WINDOW->xatom.wm_protocols;
    result->xatom.wm_delete_window = WINDOW->xatom.wm_delete_window;

    /* get visual info */
    if (!XMatchVisualInfo(result->xlib.dpy,
                          result->xlib.screen,
                          WINDOW->config.depth,
                          WINDOW->config.class,
                          &result->xutil.visual)
    ) {
        goto __win_wincreate_failure;
    }

    /* colormap */
    XID colormap = XCreateColormap(result->xlib.dpy, result->xlib.parent, result->xutil.visual.visual, AllocNone);
    if (!colormap) {
        goto __win_wincreate_failure;
    }

    /* window attributes */
    XSetWindowAttributes attr0 = {
        .background_pixmap     = 0,
        .background_pixel      = 0,
        .border_pixmap         = CopyFromParent,
        .border_pixel          = 0,
        .bit_gravity           = ForgetGravity,
        .win_gravity           = NorthWestGravity,
        .backing_store         = NotUseful,
        .backing_planes        = 1,
        .backing_pixel         = 0,
        .save_under            = False,
        .event_mask            = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | ExposureMask | StructureNotifyMask | ClientMessage,
        .do_not_propagate_mask = 0,
        .override_redirect     = False,
        .colormap              = colormap,
        .cursor                = None
    };

    /* create window */
    XID child = XCreateWindow(result->xlib.dpy, result->xlib.parent, 0, 0, w, h, 0, result->xutil.visual.depth, InputOutput, result->xutil.visual.visual, CWColormap | CWBorderPixel | CWBackPixel | CWEventMask, &attr0);
    if (!child) { goto __win_wincreate_failure; }

    result->xlib.child = child;
    XSelectInput(result->xlib.dpy, result->xlib.child, attr0.event_mask);
    XSetWMProtocols(result->xlib.dpy, result->xlib.child, &result->xatom.wm_protocols, 1);
    XSetWMProtocols(result->xlib.dpy, result->xlib.child, &result->xatom.wm_delete_window, 1);
   
    win_winsettitle(result, t);
    win_wingetpos(result, &result->attr.x, &result->attr.y);
    win_wingetsize(result, &result->attr.w, &result->attr.h);

    /* append the window to platform's window linked list */
    result->next   = WINDOW->win_ll;
    WINDOW->win_ll = result; 
    /* and return the result */
    *win = result;

    /* success */
    win_eventflush();
    return (1);

__win_wincreate_failure:

    /* release xlib resources */
    if (child) { XDestroyWindow(WINDOW->xlib.dpy, child), child = 0; }

    /* release result */
    if (result) { free(result), result = 0; }

    /* ensure we "return" null */
    *win = 0;

    /* failure */
    return (0);
}


WINDEF int win_windestroy(t_window win) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* unlink the node from platform's window linked list */
    t_window *curr = &WINDOW->win_ll;
    if (win == (*curr)) {
        WINDOW->win_ll = (*curr)->next;
    }
    else {
        /* go until the next node is out `win` */
        while ((*curr) && (*curr)->next != win) {
            (*curr) = (*curr)->next;
        }
        
        /* check if we found anything */
        if (!(*curr)) {
            return (0);
        }
        
        (*curr) = win->next;
    }

    /* destroy window's components */
    XDestroyWindow(win->xlib.dpy, win->xlib.child);
    
    /* deallocate window object */
    free(win);

    /* success */
    win_eventflush();
    return (1);
}


WINDEF int win_winmap(t_window win) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    XMapWindow(win->xlib.dpy, win->xlib.child);

    /* success */
    return (1);
}


WINDEF int win_winunmap(t_window win) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    XUnmapWindow(win->xlib.dpy, win->xlib.child);

    /* success */
    win_eventflush();
    return (1);
}


WINDEF int win_wingetsize(t_window win, size_t *w_ptr, size_t *h_ptr) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* query attributes */
    XWindowAttributes attr;
    if (!XGetWindowAttributes(win->xlib.dpy, win->xlib.child, &attr)) { return (0); }
    
    /* assign values */
    if (w_ptr) { *w_ptr = attr.width; }
    if (h_ptr) { *h_ptr = attr.height; }

    /* success */
    win_eventflush();
	return (1);
}


WINDEF int win_winsetsize(t_window win, const size_t w, const size_t h) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* resize */
    if (!XResizeWindow(win->xlib.dpy, win->xlib.child, w, h)) { return (0); }

    /* success */
    win_eventflush();
	return (1);
}


WINDEF int win_winsetsizemin(t_window win, const size_t w, const size_t h) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* get WM normal hints */
    XSizeHints hints;
    int64_t supp;
    XGetWMNormalHints(win->xlib.dpy, win->xlib.child, &hints, &supp);

    /* set new WM normal hints with position changed */
    hints.flags = PMinSize;
    hints.min_width  = w;
    hints.min_height = h;
    XSetWMNormalHints(win->xlib.dpy, win->xlib.child, &hints);

    /* success */
    win_eventflush();
	return (1);
}


WINDEF int win_winsetsizemax(t_window win, const size_t w, const size_t h) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* get WM normal hints */
    XSizeHints hints;
    int64_t supp;
    XGetWMNormalHints(win->xlib.dpy, win->xlib.child, &hints, &supp);

    /* set new WM normal hints with position changed */
    hints.flags = PMaxSize;
    hints.max_width  = w;
    hints.max_height = h;
    XSetWMNormalHints(win->xlib.dpy, win->xlib.child, &hints);

    /* success */
    win_eventflush();
	return (1);
}


WINDEF int win_wingetpos(t_window win, size_t *x_ptr, size_t *y_ptr) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* query attributes */
    XWindowAttributes attr;
    if (!XGetWindowAttributes(win->xlib.dpy, win->xlib.child, &attr)) { return (0); }
    
    /* assign values */
    if (x_ptr) { *x_ptr = attr.x; }
    if (y_ptr) { *y_ptr = attr.y; }

    /* success */
    win_eventflush();
	return (1);
}


WINDEF int win_winsetpos(t_window win, const size_t x, const size_t y) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* get WM normal hints */
    XSizeHints hints;
    int64_t supp;
    XGetWMNormalHints(win->xlib.dpy, win->xlib.child, &hints, &supp);

    /* set new WM normal hints with position changed */
    hints.flags = PPosition;
    hints.x = x;
    hints.y = y;
    XSetWMNormalHints(win->xlib.dpy, win->xlib.child, &hints);

    /* success */
    win_eventflush();
	return (1);
}


WINDEF int win_winsetminim(t_window win) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
    win_eventflush();
	return (1);
}


WINDEF int win_winsetmaxim(t_window win) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
    win_eventflush();
	return (1);
}


WINDEF int win_winsetfullscr(t_window win) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
    win_eventflush();
	return (1);
}


WINDEF int win_wingettitle(t_window win, char **t_ptr) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }
    if (!t_ptr)  { return (0); }

    /* fetch the title */
    if (XFetchName(win->xlib.dpy, win->xlib.child, t_ptr)) {
        return (0);
    }

    /* success */
    win_eventflush();
	return (1);

}


WINDEF int win_winsettitle(t_window win, const char *t) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }
    if (!t)      { return (0); }

    /* store the title */
    XStoreName(win->xlib.dpy, win->xlib.child, t);

    /* success */
    win_eventflush();
	return (1);

}


WINDEF void *win_wingetprop(t_window win, const uint64_t prop) {
    /* null-check */
    if (!WINDOW)  { return (0); }
    if (!win)     { return (0); }
    switch (prop) {
        case (WINDOW_PROP_WINDOW_X11_DISPLAY):   { return (win->xlib.dpy); }
        case (WINDOW_PROP_WINDOW_X11_ROOT_ID):   { return (&win->xlib.parent); }
        case (WINDOW_PROP_WINDOW_X11_SCREEN_ID): { return (&win->xlib.screen); }
        case (WINDOW_PROP_WINDOW_X11_WINDOW_ID): { return (&win->xlib.child); }
        case (WINDOW_PROP_WINDOW_X11_VISUAL):    { return (win->xutil.visual.visual); }

        default: { } break;
    }

    /* return nothing */
    return (0);
}

/* event functions */

WININT int __win_eventpoll_x11(void);

WINDEF int win_eventpoll(t_event *event) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }

    /* poll events from platform queue */
    if (win_eventpop(event)) { return (1); }

    /* handle platform events */
    __win_eventpoll_x11();

    /* queue filled, return WINDOW_EVENT_NONE */
    *event = (t_event) { 0 };
    return (0);
}
    
WININT int __win_eventpoll_x11(void) {
    /* null-check */
    if (!WINDOW) { return (0); }
    
    XEvent xevent = { 0 };
    while (XPending(WINDOW->xlib.dpy)) {
        XNextEvent(WINDOW->xlib.dpy, &xevent);
        
        switch (xevent.type) {
            case (ClientMessage): {
                if (xevent.xclient.message_type == WINDOW->xatom.wm_protocols) {
                    const Atom data = xevent.xclient.data.l[0];

                    if (data == WINDOW->xatom.wm_delete_window) {
                        t_eventQuit event = (t_eventQuit) {
                            .type = WINDOW_EVENT_QUIT,
                            .timestamp = win_timeget()
                        };
                        win_eventpush((t_event *) &event);
                    }
                }
            } break;

            case (MotionNotify): {
                t_eventMouseMotion event = (t_eventMouseMotion) {
                    .type = WINDOW_EVENT_MOUSE_MOTION,
                    .timestamp = win_timeget(),
                    .x = xevent.xmotion.x, .xrel = xevent.xmotion.x_root,
                    .y = xevent.xmotion.y, .yrel = xevent.xmotion.y_root,
                };
                win_eventpush((t_event *) &event);
            } break;

            case (ButtonPress):
            case (ButtonRelease): {
                uint8_t btn = 0;
                switch (xevent.xbutton.button) {
                    /* key press / relese */
                    case (1): { btn = WINDOW_BUTTON_LEFT;   } break; /* left */
                    case (2): { btn = WINDOW_BUTTON_MIDDLE; } break; /* middle */
                    case (3): { btn = WINDOW_BUTTON_RIGHT;  } break; /* right */

                    /* scroll up / down */
                    case (4): { btn = 4; } break; /* scroll up */
                    case (5): { btn = 5; } break; /* scroll down */
                }

                /* invalid button */
                if (btn == 0) { break; }

                /* mouse button presses / releases */
                else if (btn >= 1 && btn <= 3) {
                    uint8_t state = (xevent.type == ButtonPress) ? 1 : 0;

                    t_eventMouseButton event = (t_eventMouseButton) {
                        .type = WINDOW_EVENT_MOUSE_BUTTON,
                        .timestamp = win_timeget(),
                        .btn = btn,
                        .state = state
                    };
                    win_eventpush((t_event *) &event);
                }

                /* scroll up / down */
                else if (btn >= 4 && btn <= 5) {
                    if (xevent.type == ButtonRelease) { break; }

                    t_eventMouseScroll event = (t_eventMouseScroll) {
                        .type = WINDOW_EVENT_MOUSE_SCROLL,
                        .timestamp = win_timeget(),
                        .scroll = (btn == 4) ? 1 : -1
                    };
                    win_eventpush((t_event *) &event);
                }
            } break;

            case (KeyPress):
            case (KeyRelease): {
                uint8_t  state   = (xevent.type == KeyPress) ? 1 : 0;
                uint64_t keycode = xevent.xkey.keycode;
                uint64_t keysym  = XkbKeycodeToKeysym(WINDOW->xlib.dpy, keycode, 0, state);

                uint32_t key = 0;
                for (size_t i = 0; g_keymap[i].src; i++) {
                    if (keysym == g_keymap[i].src) {
                        key = g_keymap[i].dst;
                        break;
                    }
                }

                /* invalid button */
                if (key == 0) { break; }

                t_eventKeyboardKey event = (t_eventKeyboardKey) {
                    .type = WINDOW_EVENT_KEYBOARD_KEY,
                    .timestamp = win_timeget(),
                    .key = key,
                    .state = state
                };
                win_eventpush((t_event *) &event);
            } break;

            case (ConfigureNotify): {
                /* get the window reference */
                t_window win;
                for (win = WINDOW->win_ll; win; win = win->next) {
                    if (win->xlib.child == xevent.xconfigure.window) {
                        break;
                    }
                }

                if (!win) { return (0); }

                uint32_t type = 0;

                /* handle motion event */
                if (win->attr.x != (size_t) xevent.xconfigure.x ||
                    win->attr.y != (size_t) xevent.xconfigure.y
                ) {
                    type = WINDOW_EVENT_WINDOW_MOTION;
                    win->attr.x = xevent.xconfigure.x;
                    win->attr.y = xevent.xconfigure.y;
                }

                /* handle resize event */
                else if (win->attr.w != (size_t) xevent.xconfigure.width ||
                         win->attr.h != (size_t) xevent.xconfigure.height
                ) {
                    type = WINDOW_EVENT_WINDOW_RESIZE;
                    win->attr.w = xevent.xconfigure.width;
                    win->attr.h = xevent.xconfigure.height;
                }

                t_eventWindow event = (t_eventWindow) {
                    .type = type,
                    .timestamp = win_timeget(),
                    .x = xevent.xconfigure.x,     .y = xevent.xconfigure.y,
                    .w = xevent.xconfigure.width, .h = xevent.xconfigure.height,
                };
                win_eventpush((t_event *) &event);
            } break;
        }
    }

    /* success */
    return (1);
}


WINDEF int win_eventwait(t_event *event) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }

    /* success */
    return (1);
}


WINDEF int win_eventpush(t_event *event) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }
    
    /* alloc new `arr` if needed */
    if (!WINDOW->da_event.arr) {
        t_event *arr = malloc(WINDOW_EVENT_QUEUE_CAPACITY * sizeof(t_event));
        if (!arr) { return (0); }

        WINDOW->da_event.arr = WINDOW->da_event.arr_s = WINDOW->da_event.arr_e = arr;
        WINDOW->da_event.cap = WINDOW_EVENT_QUEUE_CAPACITY;
        WINDOW->da_event.cnt = 0;
    }

    /* bound check */
    if (WINDOW->da_event.cnt >= WINDOW->da_event.cap) {
        /* consider resizing
         * for now returning
         * */
        return (0);
    }

    /* assign the object to the last `arr` element */
    *WINDOW->da_event.arr_e = *event;
    /* move the last element by one */
    WINDOW->da_event.arr_e++;
    /* boundary check
     * if exceeds the `arr`, return back to start
     * */
    size_t arr_e_idx = WINDOW->da_event.arr_e - WINDOW->da_event.arr;
    if (arr_e_idx >= WINDOW->da_event.cap) {
        WINDOW->da_event.arr_e = WINDOW->da_event.arr;
    }

    /* increment the count */
    WINDOW->da_event.cnt++;

    /* success */
    return (1);
}


WINDEF int win_eventpop(t_event *event) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }

    /* check if event queue exists */
    if (!WINDOW->da_event.arr) { return (0); }

    /* check if there's anything in the queue */
    if (WINDOW->da_event.cnt == 0) { return (0); }

    /* assign the first element to the reference */
    *event = *WINDOW->da_event.arr_s;
    /* zero-down the first element (safety matter) */
    *WINDOW->da_event.arr_s = (t_event) { 0 };
    /* move the first element by one */
    WINDOW->da_event.arr_s++;
    /* boundary check
     * if exceeds the `arr`, return back to start
     * */
    size_t arr_s_idx = WINDOW->da_event.arr_s - WINDOW->da_event.arr;
    if (arr_s_idx >= WINDOW->da_event.cap) {
        WINDOW->da_event.arr_s = WINDOW->da_event.arr;
    }

    /* decrement the count */
    WINDOW->da_event.cnt--;

    /* success */
    return (1);
}


WINDEF int win_eventflush(void) {
    /* null-check */
    if (!WINDOW) { return (0); }
    
    /* flush */
    if (!XFlush(WINDOW->xlib.dpy)) { return (0); }

    /* success */
    return (1);
}

/* timing functions */

WINDEF uint64_t win_timeget(void) {
    struct timeval t;
    if (gettimeofday(&t, 0) == -1) {
        return (0);
    }

    return (t.tv_sec * 1000 + t.tv_usec / 1000);
}


WINDEF int win_timewait(uint64_t ms) {
    uint64_t t = win_timeget();
    if (t == 0) { return (0); }

    while ((win_timeget() - t) < ms);
    return (1);
}

#  endif /* WINDOW_BACKEND_X11 */
#
#  /* WINDOW_BACKEND_WAYLAND - Unix Wayland implementation layer */
#  if defined (WINDOW_BACKEND_WAYLAND)
#   include <unistd.h>
#   include <sys/time.h>
#
#   include <wayland-util.h>
#   include <wayland-version.h>
#   include <wayland-client.h>
#   include <wayland-client-core.h>
#   include <wayland-client-protocol.h>

/* ... */

#  endif /* WINDOW_BACKEND_WAYLAND */
#
#  /* WINDOW_PLATFORM_WIN32 - Windows Win32 implementation layer */
#  if defined (WINDOW_PLATFORM_WIN32)
#   include <windows.h>

/* ... */

#  endif /* WINDOW_PLATFORM_WIN32 */
#
#  /* window.h API definitions template */
#  if (0)

struct s_keymap {
    uint32_t src;
    uint32_t dst;
};

static const struct s_keymap g_keymap[] = {
    
    /* ... */

    { 0, WINDOW_KEY_NONE }
};

struct s_platform {
    /* singly-linked list of windows 
     * (glfw3 style of window handling)
     * */
    struct s_window *win_ll;

    /* ... */

    struct {
        t_event *arr;
        t_event *arr_s;
        t_event *arr_e;
        size_t   cap;
        size_t   cnt;
    } da_event;
};

struct s_window {
    struct s_window *next;

    /* ... */

    struct {
        /* position attributes */
        size_t x, y;

        /* dimension attributes */
        size_t w, h;
    } attr;
};

/* platform functions */

static struct s_platform *WINDOW = 0; 

WINDEF int win_init(void) {
    /* manage global platform object */
    if (WINDOW) { return (1); } /* check if `WINDOW` is not null. If so, return */

    WINDOW = malloc(sizeof(struct s_platform));
    if (!WINDOW) {
        return (0);
    }

    /* ... */

    /* set up event queue */
    WINDOW->da_event.cnt = 0;
    WINDOW->da_event.cap = 16;
    WINDOW->da_event.arr = calloc(WINDOW->da_event.cap, sizeof(t_event));
    if (!WINDOW->da_event.arr) { return (0); }

    /* set up window array */
    WINDOW->da_window.cap = 16;
    WINDOW->da_window.arr = calloc(WINDOW->da_window.cap, sizeof(t_window));
    if (!WINDOW->da_window.arr) { return (0); }

    /* success */
    win_eventflush();
    return (1);
}


WINDEF int win_quit(void) {
    /* null-check */
    if (!WINDOW) { return (0); }

    /* deallocate all the windows */
    t_window curr = WINDOW->win_ll,
             next = 0;
    while (curr) {
        next = curr->next;
        win_windestroy(curr);
        curr = next;
    }
   
    /* deallocate event */
    if (WINDOW->da_event.arr) {
        free(WINDOW->da_event.arr);
        WINDOW->da_event.arr   = 0;
        WINDOW->da_event.arr_s = 0;
        WINDOW->da_event.arr_e = 0;
        WINDOW->da_event.cnt = 0;
        WINDOW->da_event.cap = 0;
    }

    /* ... */

    /* deallocate `WINDOW` object */
    free(WINDOW), WINDOW = 0;

    /* success */
    return (1);
}


WINDEF int win_getsize(size_t *w_ptr, size_t *h_ptr) {
    /* null-check */
    if (!WINDOW) { return (0); }

    /* ... */
    
    /* assign values */
    if (w_ptr) { *w_ptr = /* ... */; }
    if (h_ptr) { *h_ptr = /* ... */; }

    /* success */
	return (1);
}


WINDEF void *win_getprop(const uint64_t prop) {
    /* null-check */
    if (!WINDOW) { return (0); }

    switch (prop) {
        case (WINDOW_PROP_PLATFORM_X11_DISPLAY):   { return (WINDOW->xlib.dpy); }
        case (WINDOW_PROP_PLATFORM_X11_ROOT_ID):   { return (&WINDOW->xlib.r_id); }
        case (WINDOW_PROP_PLATFORM_X11_SCREEN_ID): { return (&WINDOW->xlib.s_id); }

        default: { } break;
    }

    /* return nothing */
    return (0);
}

/* windowing functions */

WINDEF int win_wincreate(t_window *win, const size_t w, const size_t h, const char *t, const uint64_t f) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* allocate `result` window */
    t_window result = malloc(sizeof(struct s_window));
    if (!result) { return (0); }

    /* ... */

    win_winsettitle(result, t);
    win_wingetpos(result, &result->attr.x, &result->attr.y);
    win_wingetsize(result, &result->attr.w, &result->attr.h);

    /* append the window to platform's window linked list */
    result->next   = WINDOW->win_ll;
    WINDOW->win_ll = result; 
    /* and return the result */
    *win = result;

    /* success */
    win_eventflush();
    return (1);
}


WINDEF int win_windestroy(t_window win) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* unlink the node from platform's window linked list */
    t_window *curr = &WINDOW->win_ll;
    if (win == (*curr)) {
        WINDOW->win_ll = (*curr)->next;
    }
    else {
        /* go until the next node is out `win` */
        while ((*curr) && (*curr)->next != win) {
            (*curr) = (*curr)->next;
        }
        
        /* check if we found anything */
        if (!(*curr)) {
            return (0);
        }
        
        (*curr) = win->next;
    }

    /* ... */
    
    /* deallocate window object */
    free(win);

    /* success */
    win_eventflush();
    return (1);
}


WINDEF int win_winmap(t_window win) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
    return (1);
}


WINDEF int win_winunmap(t_window win) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
    return (1);
}


WINDEF int win_wingetsize(t_window win, size_t *w_ptr, size_t *h_ptr) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */
    
    /* assign values */
    if (w_ptr) { *w_ptr = /* ... */; }
    if (h_ptr) { *h_ptr = /* ... */; }

    /* success */
	return (1);
}


WINDEF int win_winsetsize(t_window win, const size_t w, const size_t h) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_winsetsizemin(t_window win, const size_t w, const size_t h) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_winsetsizemax(t_window win, const size_t w, const size_t h) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */
    
    /* success */
	return (1);
}


WINDEF int win_wingetpos(t_window win, size_t *x_ptr, size_t *y_ptr) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */
    
    /* assign values */
    if (x_ptr) { *x_ptr = /* ... */; }
    if (y_ptr) { *y_ptr = /* ... */; }

    /* success */
	return (1);
}


WINDEF int win_winsetpos(t_window win, const size_t x, const size_t y) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_winsetminim(t_window win) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_winsetmaxim(t_window win) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_winsetfullscr(t_window win) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_wingettitle(t_window win, char **t_ptr) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }
    if (!t_ptr)  { return (0); }

    /* ... */

    /* success */
	return (1);

}


WINDEF int win_winsettitle(t_window win, const char *t) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }
    if (!t)      { return (0); }

    /* ... */

    /* success */
	return (1);

}


WINDEF void *win_wingetprop(t_window win, const uint64_t prop) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* return nothing */
    return (0);
}

/* event functions */

WINDEF int win_eventpoll(t_event *event) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }

    /* poll events from platform queue */
    if (win_eventpop(event)) { return (1); }

    /* handle platform events */
    __win_eventpoll_x11();

    /* queue filled, return WINDOW_EVENT_NONE */
    *event = (t_event) { 0 };
    return (0);
}


WINDEF int win_eventwait(t_event *event) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }

    /* ... */


    /* success */
    return (1);
}


WINDEF int win_eventpush(t_event *event) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }

    /* alloc new `arr` if needed */
    if (!WINDOW->da_event.arr) {
        t_event *arr = malloc(WINDOW_EVENT_QUEUE_CAPACITY * sizeof(t_event));
        if (!arr) { return (0); }

        WINDOW->da_event.arr = WINDOW->da_event.arr_s = WINDOW->da_event.arr_e = arr;
        WINDOW->da_event.cap = WINDOW_EVENT_QUEUE_CAPACITY;
        WINDOW->da_event.cnt = 0;
    }

    /* bound check */
    if (WINDOW->da_event.cnt >= WINDOW->da_event.cap) {
        /* consider resizing
         * for now returning
         * */
        return (0);
    }

    /* assign the object to the last `arr` element */
    *WINDOW->da_event.arr_e = *event;
    /* move the last element by one */
    WINDOW->da_event.arr_e++;
    /* boundary check
     * if exceeds the `arr`, return back to start
     * */
    size_t arr_e_idx = WINDOW->da_event.arr_e - WINDOW->da_event.arr;
    if (arr_e_idx >= WINDOW->da_event.cap) {
        WINDOW->da_event.arr_e = WINDOW->da_event.arr;
    }

    /* increment the count */
    WINDOW->da_event.cnt++;

    /* success */
    return (1);
}


WINDEF int win_eventpop(t_event *event) {
    /* null-check */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }
    
    /* check if event queue exists */
    if (!WINDOW->da_event.arr) { return (0); }

    /* check if there's anything in the queue */
    if (WINDOW->da_event.cnt == 0) { return (0); }

    /* assign the first element to the reference */
    *event = *WINDOW->da_event.arr_s;
    /* zero-down the first element (safety matter) */
    *WINDOW->da_event.arr_s = (t_event) { 0 };
    /* move the first element by one */
    WINDOW->da_event.arr_s++;
    /* boundary check
     * if exceeds the `arr`, return back to start
     * */
    size_t arr_s_idx = WINDOW->da_event.arr_s - WINDOW->da_event.arr;
    if (arr_s_idx >= WINDOW->da_event.cap) {
        WINDOW->da_event.arr_s = WINDOW->da_event.arr;
    }

    /* decrement the count */
    WINDOW->da_event.cnt--;

    /* success */
    return (1);
}


WINDEF int win_eventflush(void) {
    /* null-check */
    if (!WINDOW) { return (0); }

    /* ... */

    /* success */
    return (1);
}

/* timing functions */

WINDEF uint64_t win_timeget(void) {

    /* ... */

}


WINDEF int win_timewait(uint64_t ms) {

    /* ... */

}

#  endif /* */
# endif /* WINDOW_IMPLEMENTATION */
#endif /* _window_h_ */
