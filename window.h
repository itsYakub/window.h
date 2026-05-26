#if defined (__cplusplus)
# pragma once
#endif
#
#if !defined (_window_h_)
# define _window_h_ 1
#
# /* WINDEF (window.h API) - global functions... */
# if !defined (WINDEF)
#  define WINDEF extern inline
# endif /* WINDEF */
#
# /* WININT (window.h internal API) - internal static functions... */
# if !defined (WININT)
#  define WININT static inline
# endif /* WININT */
#
# /* Define platform macros... */
# if defined (__linux__)
#  define WINDOW_PLATFORM "linux"
#  define WINDOW_PLATFORM_LINUX 1
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
#
# else
#  error /* No valid platform found... */
# endif
#
# include <stddef.h>
# include <stdint.h>

/* library functions */

WINDEF int win_init(void);

WINDEF int win_quit(void);

/* windowing functions */

typedef struct s_window *t_window;

WINDEF int win_create(t_window *, const size_t, const size_t, const char *, const uint64_t);

WINDEF int win_destroy(t_window);

/* event functions */

typedef enum e_eventType t_eventType;

enum e_eventType {

    WINDOW_EVENT_NONE = 0,
# define WINDOW_EVENT_NONE WINDOW_EVENT_NONE

    WINDOW_EVENT_QUIT = 1,
# define WINDOW_EVENT_QUIT WINDOW_EVENT_QUIT

    /* ... */

    WINDOW_EVENT_COUNT
# define WINDOW_EVENT_COUNT WINDOW_EVENT_COUNT

};


typedef struct s_eventQuit t_eventQuit;

struct s_eventQuit {
    t_eventType type;
    size_t timestamp;
};


typedef union u_event t_event;

union u_event {
    t_eventType type;

    t_eventQuit quit;
};

WINDEF int win_pollEvents(t_window, t_event *);

# if defined WINDOW_IMPLEMENTATION
#
#  /* WINDOW_PLATFORM_X11 - Unix X11 implementation layer */
#  if defined (WINDOW_PLATFORM_X11)
#   include <X11/X.h>
#   include <X11/Xlib.h>
#   include <X11/Xutil.h>
#   include <X11/Xatom.h>

/* platform functions */

struct s_platform {
    struct {
        Display *dpy;
        Window   root;
    } xlib;

    struct {
        Atom wm_protocols;
        Atom wm_delete_window;
    } xatom;
};

static struct s_platform g_platform = { 0 };

WININT int __win_init_x11(void);

WININT int __win_quit_x11(void);


WINDEF int win_init(void) { return (__win_init_x11()); }

WINDEF int win_quit(void) { return (__win_quit_x11()); }

/* windowing functions */

struct s_window { };

WININT int __win_create_x11(t_window *, const size_t, const size_t, const char *, const uint64_t);

WININT int __win_destroy_x11(t_window);

WINDEF int win_create(t_window *win, const size_t w, const size_t h, const char *t, const uint64_t f) { return (__win_create_x11(win, w, h, t, f)); }

WINDEF int win_destroy(t_window win) { return (__win_destroy_x11(win)); }

/* event functions */

WININT int __win_pollEvents_x11(t_window, t_event *);

WINDEF int win_pollEvents(t_window win, t_event *event) { return (__win_pollEvents_x11(win, event)); }


/* platform functions */

WININT int __win_init_x11(void) {
    /* connect to x11 server... */
    Display *dpy = XOpenDisplay(0);
    if (!dpy) { return (0); }

    /* get the root window... */
    Window root = XDefaultRootWindow(dpy);
    if (!root) { return (0); }

    /* assign data to `xlib` platform section... */
    g_platform.xlib.dpy  = dpy;
    g_platform.xlib.root = root;
   
    /* retrieve atoms from x11 session... */
    Atom wm_protocols = XInternAtom(dpy, "WM_PROTOCOLS", False);
    if (!wm_protocols) { return (0); }
    
    Atom wm_delete_window = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
    if (!wm_delete_window) { return (0); }
    
    /* assign data to `xatom` platform section... */
    g_platform.xatom.wm_protocols     = wm_protocols;
    g_platform.xatom.wm_delete_window = wm_delete_window;

    /* success */
    return (1);
}

WININT int __win_quit_x11(void) {
    /* terminate `xlib`... */
    XCloseDisplay(g_platform.xlib.dpy), g_platform.xlib.dpy = 0;
    
    /* success */
    return (1);
}

/* windowing functions */

WININT int __win_create_x11(t_window *win, const size_t w, const size_t h, const char *t, const uint64_t f) {
    /* success */
    return (1);
}

WININT int __win_destroy_x11(t_window win) {
    /* success */
    return (1);
}

/* event functions */

WININT int __win_pollEvents_x11(t_window win, t_event *event) {
    /* success */
    return (1);
}

#  endif /* WINDOW_PLATFORM_X11 */
#
#  /* WINDOW_PLATFORM_WAYLAND - Unix Wayland implementation layer */
#  if defined (WINDOW_PLATFORM_WAYLAND)
#   include <wayland-util.h>
#   include <wayland-version.h>
#   include <wayland-client.h>
#   include <wayland-client-core.h>
#   include <wayland-client-protocol.h>

/* ... */

#  endif /* WINDOW_PLATFORM_WAYLAND */
#
#  /* WINDOW_PLATFORM_WIN32 - Windows Win32 implementation layer */
#  if defined (WINDOW_PLATFORM_WIN32)
#   include <windows.h>

/* ... */

#  endif /* WINDOW_PLATFORM_WIN32 */
# endif /* WINDOW_IMPLEMENTATION */
#endif /* _window_h_ */
