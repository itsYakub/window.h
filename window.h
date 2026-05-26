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

WINDEF int win_map(t_window);

WINDEF int win_unmap(t_window);

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
#  include <stdlib.h>
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
        Display *dpy;   /* display pointer */
        XID      r_id;  /* root window's ID */
        XID      s_id;  /* screen's ID */
    } xlib;

    struct {
        Atom wm_protocols;
        Atom wm_delete_window;
    } xatom;

    struct {
        int depth;
        int class;
    } config;
};

static struct s_platform *WINDOW = 0; 

WININT int __win_init_x11(void);

WININT int __win_quit_x11(void);


WINDEF int win_init(void) { return (__win_init_x11()); }

WINDEF int win_quit(void) { return (__win_quit_x11()); }

/* windowing functions */

struct s_window {
    struct {
        Display *dpy;   /* display pointer */
        XID      r_id;  /* root window's ID */
        XID      s_id;  /* screen's ID */
        XID      w_id;  /* this window's ID */
    } xlib;
    
    struct {
        Atom wm_protocols;
        Atom wm_delete_window;
    } xatom;

    struct {
        XVisualInfo visual;
    } xutil;
};

WININT int __win_create_x11(t_window *, const size_t, const size_t, const char *, const uint64_t);

WININT int __win_destroy_x11(t_window);

WININT int __win_map_x11(t_window);

WININT int __win_unmap_x11(t_window);

WINDEF int win_create(t_window *win, const size_t w, const size_t h, const char *t, const uint64_t f) { return (__win_create_x11(win, w, h, t, f)); }

WINDEF int win_destroy(t_window win) { return (__win_destroy_x11(win)); }

WINDEF int win_map(t_window win) { return (__win_map_x11(win)); }

WINDEF int win_unmap(t_window win) { return (__win_unmap_x11(win)); }

/* event functions */

WININT int __win_pollEvents_x11(t_window, t_event *);

WINDEF int win_pollEvents(t_window win, t_event *event) { return (__win_pollEvents_x11(win, event)); }


/* platform functions */

WININT int __win_init_x11(void) {
    /* manage global platform object... */
    if (WINDOW) { return (1); } /* check if `WINDOW` is not null. If so, return... */

    WINDOW = malloc(sizeof(struct s_platform));
    if (!WINDOW) {
        return (0);
    }

    /* connect to x11 server... */
    Display *dpy = XOpenDisplay(0);
    if (!dpy) { return (0); }

    /* get the root window... */
    XID r_id = XDefaultRootWindow(dpy);
    if (!r_id) { return (0); }

    /* get screen number... */
    XID s_id = XDefaultScreen(dpy);

    /* assign data to `xlib` platform section... */
    WINDOW->xlib.dpy  = dpy;
    WINDOW->xlib.r_id = r_id;
    WINDOW->xlib.s_id = s_id;
   
    /* retrieve atoms from x11 session... */
    Atom wm_protocols = XInternAtom(dpy, "WM_PROTOCOLS", False);
    if (!wm_protocols) { return (0); }
    
    Atom wm_delete_window = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
    if (!wm_delete_window) { return (0); }
    
    /* assign data to `xatom` platform section... */
    WINDOW->xatom.wm_protocols     = wm_protocols;
    WINDOW->xatom.wm_delete_window = wm_delete_window;

    /* set default config values... */
    WINDOW->config.depth = 24;
    WINDOW->config.class = TrueColor;

    /* success */
    return (1);
}

WININT int __win_quit_x11(void) {
    /* terminate `xlib`... */
    XCloseDisplay(WINDOW->xlib.dpy), WINDOW->xlib.dpy = 0;
    
    /* deallocate `WINDOW` object... */
    free(WINDOW), WINDOW = 0;

    /* success */
    return (1);
}

/* windowing functions */

WININT int __win_create_x11(t_window *win, const size_t w, const size_t h, const char *t, const uint64_t f) {
    /* null-check... */
    if (!win) { return (0); }

    /* allocate `result` window... */
    t_window result = malloc(sizeof(struct s_window));
    if (!result) { return (0); }
    
    /* assign references to X11 objects... */
    if (!WINDOW->xlib.dpy) { return (0); }
    result->xlib.dpy  = WINDOW->xlib.dpy;
    
    if (!WINDOW->xlib.r_id) { return (0); }
    result->xlib.r_id = WINDOW->xlib.r_id;
    result->xlib.s_id = WINDOW->xlib.s_id;

    /* assign references to X11 atoms... */
    result->xatom.wm_protocols = WINDOW->xatom.wm_protocols;
    result->xatom.wm_delete_window = WINDOW->xatom.wm_delete_window;

    /* get visual info... */
    if (!XMatchVisualInfo(result->xlib.dpy,
                          result->xlib.s_id,
                          WINDOW->config.depth,
                          WINDOW->config.class,
                          &result->xutil.visual)
    ) {
        return (0);
    }

    /* colormap... */
    XID colormap = XCreateColormap(result->xlib.dpy, result->xlib.r_id, result->xutil.visual.visual, AllocNone);
    if (!colormap) {
        return (0);
    }

    /* window attributes... */
    XSetWindowAttributes attr = {
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

    /* create window... */
    XID w_id = XCreateWindow(result->xlib.dpy, result->xlib.r_id, 0, 0, w, h, 0, result->xutil.visual.depth, InputOutput, result->xutil.visual.visual, CWColormap | CWBorderPixel | CWBackPixel | CWEventMask, &attr);
    if (!w_id) { return (0); }

    result->xlib.w_id = w_id;
    XSelectInput(result->xlib.dpy, result->xlib.w_id, attr.event_mask);
    XStoreName(result->xlib.dpy, result->xlib.w_id, t);

    XSetWMProtocols(result->xlib.dpy, result->xlib.w_id, &result->xatom.wm_protocols, 1);
    XSetWMProtocols(result->xlib.dpy, result->xlib.w_id, &result->xatom.wm_delete_window, 1);

    /* success */
    *win = result;
    return (1);
}

WININT int __win_destroy_x11(t_window win) {
    /* null-check... */
    if (!win) { return (0); }

    /* destroy window's components... */
    XDestroyWindow(win->xlib.dpy, win->xlib.w_id);
    
    /* deallocate window object... */
    free(win);

    /* success */
    return (1);
}

WININT int __win_map_x11(t_window win) {
    /* null-check... */
    if (!win)            { return (0); }
    if (!win->xlib.w_id) { return (0); }

    XMapWindow(win->xlib.dpy, win->xlib.w_id);

    /* success */
    return (1);
}

WININT int __win_unmap_x11(t_window win) {
    /* null-check... */
    if (!win)            { return (0); }
    if (!win->xlib.w_id) { return (0); }

    XUnmapWindow(win->xlib.dpy, win->xlib.w_id);

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
