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
#  /* define default backend if none is defined... */
#  if !defined (WINDOW_BACKEND_X11) && !defined (WINDOW_BACKEND_WAYLAND)
#   define WINDOW_BACKEND_X11 1 /* by default window.h picks X11 for *nix platforms... */
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
#  /* define default backend if none is defined... */
#  if !defined (WINDOW_BACKEND_X11) && !defined (WINDOW_BACKEND_WAYLAND)
#   define WINDOW_BACKEND_X11 1 /* by default window.h picks X11 for *nix platforms... */
#  endif
#
# else
#  error /* No valid platform found... */
# endif
#
# include <stddef.h>
# include <stdint.h>

/* library functions */

enum {
    WINDOW_PROP_PLATFORM_NONE = 0,
# define WINDOW_PROP_PLATFORM_NONE WINDOW_PROP_PLATFORM_NONE

    /* X11 properties... */

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

    /* X11 properties... */

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


typedef struct s_event t_event;

struct s_event {
    uint32_t type;
    uint64_t timestamp;

    union {
        int8_t  c[64 / sizeof(int8_t)];
        int16_t s[64 / sizeof(int16_t)];
        int32_t i[64 / sizeof(int32_t)];
        int64_t l[64 / sizeof(int64_t)];
    } data;
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

    struct {
        t_event *arr;
        size_t   cnt;
        size_t   cap;
    } da_event;

    struct {
        t_window *arr;
        size_t    cap;
    } da_window;
};

static struct s_platform *WINDOW = 0; 

WINDEF int win_init(void) {
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

    /* set up event queue... */
    WINDOW->da_event.cnt = 0;
    WINDOW->da_event.cap = 16;
    WINDOW->da_event.arr = calloc(WINDOW->da_event.cap, sizeof(t_event));
    if (!WINDOW->da_event.arr) { return (0); }

    /* set up window array... */
    WINDOW->da_window.cap = 16;
    WINDOW->da_window.arr = calloc(WINDOW->da_window.cap, sizeof(t_window));
    if (!WINDOW->da_window.arr) { return (0); }

    /* success */
    return (1);
}


WINDEF int win_quit(void) {
    /* null-check... */
    if (!WINDOW) { return (0); }

    /* deallocate all the windows... */
    for (size_t i = 0; i < WINDOW->da_window.cap; i++) {
        if (!WINDOW->da_window.arr[i]) { continue; }

        win_windestroy(WINDOW->da_window.arr[i]);
    }

    free(WINDOW->da_window.arr);
    WINDOW->da_window.arr = 0;
    WINDOW->da_window.cap = 0;
   
    /* deallocate da_event... */
    free(WINDOW->da_event.arr);
    WINDOW->da_event.arr = 0;
    WINDOW->da_event.cnt = 0;
    WINDOW->da_event.cap = 0;

    /* terminate `xlib`... */
    XCloseDisplay(WINDOW->xlib.dpy), WINDOW->xlib.dpy = 0;

    /* deallocate `WINDOW` object... */
    free(WINDOW), WINDOW = 0;

    /* success */
    return (1);
}


WINDEF int win_getsize(size_t *w_ptr, size_t *h_ptr) {
    /* null-check... */
    if (!WINDOW) { return (0); }

    /* query attributes */
    XWindowAttributes attr;
    if (!XGetWindowAttributes(WINDOW->xlib.dpy, WINDOW->xlib.r_id, &attr)) { return (0); }
    
    /* assign values */
    if (w_ptr) { *w_ptr = attr.width; }
    if (h_ptr) { *h_ptr = attr.height; }

    /* success */
	return (1);
}


WINDEF void *win_getprop(const uint64_t prop) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    switch (prop) {
        case (WINDOW_PROP_PLATFORM_X11_DISPLAY):   { return (WINDOW->xlib.dpy); }
        case (WINDOW_PROP_PLATFORM_X11_ROOT_ID):   { return (&WINDOW->xlib.r_id); }
        case (WINDOW_PROP_PLATFORM_X11_SCREEN_ID): { return (&WINDOW->xlib.s_id); }

        default: { } break;
    }

    /* return nothing... */
    return (0);
}

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

    struct {
        /* position attributes... */
        size_t x, y;

        /* dimension attributes... */
        size_t w, h;
    } attr;
};

WINDEF int win_wincreate(t_window *win, const size_t w, const size_t h, const char *t, const uint64_t f) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* allocate `result` window... */
    t_window result = malloc(sizeof(struct s_window));
    if (!result) { return (0); }
    
    /* NOTE:
     *  Temporarily disabled parameter
     * */
    (void) f;
    
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
   
    /* configure windows attributes... */
    result->attr.w = w;
    result->attr.h = h;

    /* append window to da_window... */
    size_t i;
    for (i = 0; i < WINDOW->da_window.cap; i++) {
        /* set the first `null` window object to the current window... */
        if (WINDOW->da_window.arr[i] == 0) {
            WINDOW->da_window.arr[i]  = result;
            break;
        }
    }

    /* da_window is exhausted, we must resize it.
     * After that we must append the window to newly - resized da_window.
     * */
    if (i == WINDOW->da_window.cap) {
        WINDOW->da_window.cap *= 1.5;
        WINDOW->da_window.arr  = realloc(WINDOW->da_window.arr, WINDOW->da_window.cap * sizeof(t_window));
        if (!WINDOW->da_window.arr) { return (0); }

        for ( ; i< WINDOW->da_window.cap; i++) {
            /* set the first `null` window object to the current window... */
            if (WINDOW->da_window.arr[i] == 0) {
                WINDOW->da_window.arr[i]  = result;
                break;
            }
        }
    }

    /* set the `result` object as `win` return object... */
    *win = result;
    
    /* success */
    return (1);
}


WINDEF int win_windestroy(t_window win) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* erase window from da_window... */
    for (size_t i = 0; i < WINDOW->da_window.cap; i++) {
        if (win == WINDOW->da_window.arr[i]) {
            WINDOW->da_window.arr[i] = 0;
            break;
        }
    }

    /* destroy window's components... */
    XDestroyWindow(win->xlib.dpy, win->xlib.w_id);
    
    /* deallocate window object... */
    free(win);

    /* success */
    return (1);
}


WINDEF int win_winmap(t_window win) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    XMapWindow(win->xlib.dpy, win->xlib.w_id);

    /* success */
    return (1);
}


WINDEF int win_winunmap(t_window win) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    XUnmapWindow(win->xlib.dpy, win->xlib.w_id);

    /* success */
    return (1);
}


WINDEF int win_wingetsize(t_window win, size_t *w_ptr, size_t *h_ptr) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* query attributes */
    XWindowAttributes attr;
    if (!XGetWindowAttributes(win->xlib.dpy, win->xlib.w_id, &attr)) { return (0); }
    
    /* assign values */
    if (w_ptr) { *w_ptr = attr.width; }
    if (h_ptr) { *h_ptr = attr.height; }

    /* success */
	return (1);
}


WINDEF int win_winsetsize(t_window win, const size_t w, const size_t h) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* resize */
    if (!XResizeWindow(win->xlib.dpy, win->xlib.w_id, w, h)) { return (0); }

    /* success */
	return (1);
}


WINDEF int win_winsetsizemin(t_window win, const size_t w, const size_t h) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* get WM normal hints */
    XSizeHints hints;
    int64_t supp;
    XGetWMNormalHints(win->xlib.dpy, win->xlib.w_id, &hints, &supp);

    /* set new WM normal hints with position changed */
    hints.flags = PMinSize;
    hints.min_width  = w;
    hints.min_height = h;
    XSetWMNormalHints(win->xlib.dpy, win->xlib.w_id, &hints);

    /* success */
	return (1);
}


WINDEF int win_winsetsizemax(t_window win, const size_t w, const size_t h) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* get WM normal hints */
    XSizeHints hints;
    int64_t supp;
    XGetWMNormalHints(win->xlib.dpy, win->xlib.w_id, &hints, &supp);

    /* set new WM normal hints with position changed */
    hints.flags = PMaxSize;
    hints.max_width  = w;
    hints.max_height = h;
    XSetWMNormalHints(win->xlib.dpy, win->xlib.w_id, &hints);

    /* success */
	return (1);
}


WINDEF int win_wingetpos(t_window win, size_t *x_ptr, size_t *y_ptr) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* query attributes */
    XWindowAttributes attr;
    if (!XGetWindowAttributes(win->xlib.dpy, win->xlib.w_id, &attr)) { return (0); }
    
    /* assign values */
    if (x_ptr) { *x_ptr = attr.x; }
    if (y_ptr) { *y_ptr = attr.y; }

    /* success */
	return (1);
}


WINDEF int win_winsetpos(t_window win, const size_t x, const size_t y) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* get WM normal hints */
    XSizeHints hints;
    int64_t supp;
    XGetWMNormalHints(win->xlib.dpy, win->xlib.w_id, &hints, &supp);

    /* set new WM normal hints with position changed */
    hints.flags = PPosition;
    hints.x = x;
    hints.y = y;
    XSetWMNormalHints(win->xlib.dpy, win->xlib.w_id, &hints);

    /* success */
	return (1);
}


WINDEF int win_winsetminim(t_window win) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_winsetmaxim(t_window win) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_winsetfullscr(t_window win) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_wingettitle(t_window win, char **t_ptr) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }
    if (!t_ptr)  { return (0); }

    /* fetch the title */
    if (XFetchName(win->xlib.dpy, win->xlib.w_id, t_ptr)) {
        return (0);
    }

    /* success */
	return (1);

}


WINDEF int win_winsettitle(t_window win, const char *t) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }
    if (!t)      { return (0); }

    /* store the title */
    XStoreName(win->xlib.dpy, win->xlib.w_id, t);

    /* success */
	return (1);

}


WINDEF void *win_wingetprop(t_window win, const uint64_t prop) {
    /* null-check... */
    if (!WINDOW)  { return (0); }
    if (!win)     { return (0); }
    switch (prop) {
        case (WINDOW_PROP_WINDOW_X11_DISPLAY):   { return (win->xlib.dpy); }
        case (WINDOW_PROP_WINDOW_X11_ROOT_ID):   { return (&win->xlib.r_id); }
        case (WINDOW_PROP_WINDOW_X11_SCREEN_ID): { return (&win->xlib.s_id); }
        case (WINDOW_PROP_WINDOW_X11_WINDOW_ID): { return (&win->xlib.w_id); }
        case (WINDOW_PROP_WINDOW_X11_VISUAL):    { return (win->xutil.visual.visual); }

        default: { } break;
    }

    /* return nothing... */
    return (0);
}

/* event functions */

WININT int __win_eventpoll_x11(void);

WINDEF int win_eventpoll(t_event *event) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }

    /* poll events from platform queue... */
    if (win_eventpop(event)) { return (1); }

    /* handle platform events... */
    __win_eventpoll_x11();

    /* no events in the queue...
     * ...it usually means we can break from a loop that iterates until there's no event in the queue left...
     * ...so returning `false` seems reasonable
     * Also, it's wise to return `WINDOW_EVENT_NONE` event type
     * */
    *event = (t_event) {
        .type = WINDOW_EVENT_NONE
    };

    return (0);
}
    
WININT int __win_eventpoll_x11(void) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    
    XEvent xevent = { 0 };
    while (XPending(WINDOW->xlib.dpy)) {
        XNextEvent(WINDOW->xlib.dpy, &xevent);

        switch (xevent.type) {
            case (ClientMessage): {
                if (xevent.xclient.message_type == WINDOW->xatom.wm_protocols) {
                    const Atom data = xevent.xclient.data.l[0];

                    if (data == WINDOW->xatom.wm_delete_window) {
                        t_event event = (t_event) {
                            .type = WINDOW_EVENT_QUIT,
                            .timestamp = win_timeget()
                        };

                        win_eventpush(&event);
                    }
                }
            } break;

            case (MotionNotify): {
                t_event event = (t_event) {
                    .type = WINDOW_EVENT_MOUSE_MOTION,
                    .timestamp = win_timeget(),
                    .data = {
                        .l = {
                            [0] = xevent.xmotion.x,
                            [1] = xevent.xmotion.x_root,
                            [2] = xevent.xmotion.y,
                            [3] = xevent.xmotion.y_root,
                        }
                    }
                };

                win_eventpush(&event);
            } break;

            case (ButtonPress):
            case (ButtonRelease): {
                uint8_t btn = 0;
                switch (xevent.xbutton.button) {
                    case (1): { btn = 1; } break; /* left */
                    case (2): { btn = 3; } break; /* middle */
                    case (3): { btn = 2; } break; /* right */
                    case (4): { btn = 4; } break; /* scroll up */
                    case (5): { btn = 5; } break; /* scroll down */
                }

                /* invalid button... */
                if (btn == 0) { break; }

                /* mouse button presses / releases... */
                else if (btn >= 1 && btn <= 3) {
                    uint8_t state = (xevent.type == ButtonPress) ? 1 : 0;

                    t_event event = (t_event) {
                        .type = WINDOW_EVENT_MOUSE_BUTTON,
                        .timestamp = win_timeget(),
                        .data = {
                            .c = {
                                [0] = btn,
                                [1] = state
                            }
                        }
                    };
                    
                    win_eventpush(&event);
                }

                /* scroll up / down... */
                else {
                    if (xevent.type == ButtonRelease) { break; }

                    t_event event = (t_event) {
                        .type = WINDOW_EVENT_MOUSE_SCROLL,
                        .timestamp = win_timeget(),
                        .data = {
                            .c = {
                                [0] = (btn == 4) ? 1 : -1
                            }
                        }
                    };

                    win_eventpush(&event);
                }
            } break;

            case (ConfigureNotify): {
                /* get the window reference... */
                t_window win = 0;
                for (size_t i = 0; i < WINDOW->da_window.cap; i++) {
                    if (WINDOW->da_window.arr[i]) {
                        if (WINDOW->da_window.arr[i]->xlib.w_id == xevent.xconfigure.window) {
                            win = WINDOW->da_window.arr[i];
                            break;
                        }
                    }
                }

                /* handle motion event... */
                if (win->attr.x != (size_t) xevent.xconfigure.x ||
                    win->attr.y != (size_t) xevent.xconfigure.y
                ) {
                    win->attr.x = xevent.xconfigure.x;
                    win->attr.y = xevent.xconfigure.y;

                    t_event event = (t_event) {
                        .type = WINDOW_EVENT_WINDOW_MOTION,
                        .timestamp = win_timeget(),
                        .data = {
                            .l = {
                                [0] = xevent.xconfigure.x,
                                [1] = xevent.xconfigure.y,
                            }
                        }
                    };
                    
                    win_eventpush(&event);
                }

                /* handle resize event... */
                if (win->attr.w != (size_t) xevent.xconfigure.width ||
                    win->attr.h != (size_t) xevent.xconfigure.height
                ) {
                    win->attr.w = xevent.xconfigure.width;
                    win->attr.h = xevent.xconfigure.height;

                    t_event event = (t_event) {
                        .type = WINDOW_EVENT_WINDOW_RESIZE,
                        .timestamp = win_timeget(),
                        .data = {
                            .l = {
                                [0] = xevent.xconfigure.width,
                                [1] = xevent.xconfigure.height,
                            }
                        }
                    };
                    
                    win_eventpush(&event);
                }

            } break;
        }
    }

    /* success */
    return (1);
}


WINDEF int win_eventwait(t_event *event) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }

    /* success */
    return (1);
}


WINDEF int win_eventpush(t_event *event) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }

    /* bounds-check... */
    if (WINDOW->da_event.cnt >= WINDOW->da_event.cap) {
        WINDOW->da_event.cap *= 1.5;
        WINDOW->da_event.arr = realloc(WINDOW->da_event.arr, WINDOW->da_event.cap * sizeof(t_event));
        if (!WINDOW->da_event.arr) { return (0); }
    }

    /* tail-coalescing... */
    if (WINDOW->da_event.cnt > 0) {
        t_event *tail = &WINDOW->da_event.arr[WINDOW->da_event.cnt - 1];
        if (tail->type == event->type) {
            if (tail->type == WINDOW_EVENT_MOUSE_MOTION  ||
                tail->type == WINDOW_EVENT_WINDOW_MOTION ||
                tail->type == WINDOW_EVENT_WINDOW_RESIZE
            ) {
                *tail = *event;
                return (1);
            }
        }
    }

    /* copy-assignment event object to event queue... */
    WINDOW->da_event.arr[WINDOW->da_event.cnt++] = *event;

    /* success */
    return (1);
}


WINDEF int win_eventpop(t_event *event) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }

    /* bounds-check... */
    if (WINDOW->da_event.cnt == 0) { return (0); }

    /* copy to `event` pointer... */
    *event = WINDOW->da_event.arr[0];

    /* move all the event objects one place to the front... */
    size_t i = 0;
    for ( ; i < WINDOW->da_event.cnt - 1; i++) {
        WINDOW->da_event.arr[i] = WINDOW->da_event.arr[i + 1];
    }

    /* set last queue element to `zero`... */
    WINDOW->da_event.arr[i] = (t_event) { 0 };

    /* ...and decrement the size of the queue... */
    WINDOW->da_event.cnt--;

    /* success */
    return (1);
}


WINDEF int win_eventflush(void) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    
    /* flush... */
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

/* platform functions */

struct s_platform {

    /* ... */

    struct {
        t_event *arr;
        size_t   cnt;
        size_t   cap;
    } da_event;

    struct {
        t_window *arr;
        size_t    cap;
    } da_window;
};

static struct s_platform *WINDOW = 0; 

WINDEF int win_init(void) {
    /* manage global platform object... */
    if (WINDOW) { return (1); } /* check if `WINDOW` is not null. If so, return... */

    WINDOW = malloc(sizeof(struct s_platform));
    if (!WINDOW) {
        return (0);
    }

    /* ... */

    /* set up event queue... */
    WINDOW->da_event.cnt = 0;
    WINDOW->da_event.cap = 16;
    WINDOW->da_event.arr = calloc(WINDOW->da_event.cap, sizeof(t_event));
    if (!WINDOW->da_event.arr) { return (0); }

    /* set up window array... */
    WINDOW->da_window.cap = 16;
    WINDOW->da_window.arr = calloc(WINDOW->da_window.cap, sizeof(t_window));
    if (!WINDOW->da_window.arr) { return (0); }

    /* success */
    return (1);
}


WINDEF int win_quit(void) {
    /* null-check... */
    if (!WINDOW) { return (0); }

    /* deallocate all the windows... */
    for (size_t i = 0; i < WINDOW->da_window.cap; i++) {
        if (!WINDOW->da_window.arr[i]) { continue; }

        win_windestroy(WINDOW->da_window.arr[i]);
    }

    free(WINDOW->da_window.arr);
    WINDOW->da_window.arr = 0;
    WINDOW->da_window.cap = 0;
   
    /* deallocate da_event... */
    free(WINDOW->da_event.arr);
    WINDOW->da_event.arr = 0;
    WINDOW->da_event.cnt = 0;
    WINDOW->da_event.cap = 0;

    /* ... */

    /* deallocate `WINDOW` object... */
    free(WINDOW), WINDOW = 0;

    /* success */
    return (1);
}


WINDEF int win_getsize(size_t *w_ptr, size_t *h_ptr) {
    /* null-check... */
    if (!WINDOW) { return (0); }

    /* ... */
    
    /* assign values */
    if (w_ptr) { *w_ptr = /* ... */; }
    if (h_ptr) { *h_ptr = /* ... */; }

    /* success */
	return (1);
}


WINDEF void *win_getprop(const uint64_t prop) {
    /* null-check... */
    if (!WINDOW) { return (0); }

    switch (prop) {
        case (WINDOW_PROP_PLATFORM_X11_DISPLAY):   { return (WINDOW->xlib.dpy); }
        case (WINDOW_PROP_PLATFORM_X11_ROOT_ID):   { return (&WINDOW->xlib.r_id); }
        case (WINDOW_PROP_PLATFORM_X11_SCREEN_ID): { return (&WINDOW->xlib.s_id); }

        default: { } break;
    }

    /* return nothing... */
    return (0);
}

/* windowing functions */

struct s_window {

    /* ... */

    struct {
        /* position attributes... */
        size_t x, y;

        /* dimension attributes... */
        size_t w, h;
    } attr;
};

WINDEF int win_wincreate(t_window *win, const size_t w, const size_t h, const char *t, const uint64_t f) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* allocate `result` window... */
    t_window result = malloc(sizeof(struct s_window));
    if (!result) { return (0); }

    /* ... */

    /* configure windows attributes... */
    result->attr.w = w;
    result->attr.h = h;

    /* append window to da_window... */
    size_t i;
    for (i = 0; i < WINDOW->da_window.cap; i++) {
        /* set the first `null` window object to the current window... */
        if (WINDOW->da_window.arr[i] == 0) {
            WINDOW->da_window.arr[i]  = result;
            break;
        }
    }

    /* da_window is exhausted, we must resize it.
     * After that we must append the window to newly - resized da_window.
     * */
    if (i == WINDOW->da_window.cap) {
        WINDOW->da_window.cap *= 1.5;
        WINDOW->da_window.arr  = realloc(WINDOW->da_window.arr, WINDOW->da_window.cap * sizeof(t_window));
        if (!WINDOW->da_window.arr) { return (0); }

        for ( ; i< WINDOW->da_window.cap; i++) {
            /* set the first `null` window object to the current window... */
            if (WINDOW->da_window.arr[i] == 0) {
                WINDOW->da_window.arr[i]  = result;
                break;
            }
        }
    }

    /* set the `result` object as `win` return object... */
    *win = result;
    
    /* success */
    return (1);
}


WINDEF int win_windestroy(t_window win) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* erase window from da_window... */
    for (size_t i = 0; i < WINDOW->da_window.cap; i++) {
        if (win == WINDOW->da_window.arr[i]) {
            WINDOW->da_window.arr[i] = 0;
            break;
        }
    }

    /* destroy window's components... */
    XDestroyWindow(win->xlib.dpy, win->xlib.w_id);
    
    /* deallocate window object... */
    free(win);

    /* success */
    return (1);
}


WINDEF int win_winmap(t_window win) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */


    XMapWindow(win->xlib.dpy, win->xlib.w_id);

    /* success */
    return (1);
}


WINDEF int win_winunmap(t_window win) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */


    XUnmapWindow(win->xlib.dpy, win->xlib.w_id);

    /* success */
    return (1);
}


WINDEF int win_wingetsize(t_window win, size_t *w_ptr, size_t *h_ptr) {
    /* null-check... */
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
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_winsetsizemin(t_window win, const size_t w, const size_t h) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_winsetsizemax(t_window win, const size_t w, const size_t h) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */
    
    /* success */
	return (1);
}


WINDEF int win_wingetpos(t_window win, size_t *x_ptr, size_t *y_ptr) {
    /* null-check... */
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
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_winsetminim(t_window win) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_winsetmaxim(t_window win) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_winsetfullscr(t_window win) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* success */
	return (1);
}


WINDEF int win_wingettitle(t_window win, char **t_ptr) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }
    if (!t_ptr)  { return (0); }

    /* ... */

    /* success */
	return (1);

}


WINDEF int win_winsettitle(t_window win, const char *t) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }
    if (!t)      { return (0); }

    /* ... */

    /* success */
	return (1);

}


WINDEF void *win_wingetprop(t_window win, const uint64_t prop) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!win)    { return (0); }

    /* ... */

    /* return nothing... */
    return (0);
}

/* event functions */

WINDEF int win_eventpoll(t_event *event) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }

    /* poll events from platform queue... */
    if (win_eventpop(event)) { return (1); }

    /* ... */


    /* handle platform events... */
    __win_eventpoll_x11();

    /* no events in the queue...
     * ...it usually means we can break from a loop that iterates until there's no event in the queue left...
     * ...so returning `false` seems reasonable
     * Also, it's wise to return `WINDOW_EVENT_NONE` event type
     * */
    *event = (t_event) {
        .type = WINDOW_EVENT_NONE
    };

    return (0);
}


WINDEF int win_eventwait(t_event *event) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }

    /* ... */


    /* success */
    return (1);
}


WINDEF int win_eventpush(t_event *event) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }

    /* bounds-check... */
    if (WINDOW->da_event.cnt >= WINDOW->da_event.cap) {
        WINDOW->da_event.cap *= 1.5;
        WINDOW->da_event.arr = realloc(WINDOW->da_event.arr, WINDOW->da_event.cap * sizeof(t_event));
        if (!WINDOW->da_event.arr) { return (0); }
    }

    /* tail-coalescing... */
    if (WINDOW->da_event.cnt > 0) {
        t_event *tail = &WINDOW->da_event.arr[WINDOW->da_event.cnt - 1];
        if (tail->type == event->type && __win_coalescable_x11(event->type)) {
            if (tail->type == WINDOW_EVENT_MOUSE_MOTION  ||
                tail->type == WINDOW_EVENT_WINDOW_MOTION ||
                tail->type == WINDOW_EVENT_WINDOW_RESIZE
            ) {
                *tail = *event;
                return (1);
            }
        }
    }

    /* copy-assignment event object to event queue... */
    WINDOW->da_event.arr[WINDOW->da_event.cnt++] = *event;

    /* success */
    return (1);
}


WINDEF int win_eventpop(t_event *event) {
    /* null-check... */
    if (!WINDOW) { return (0); }
    if (!event)  { return (0); }

    /* bounds-check... */
    if (WINDOW->da_event.cnt == 0) { return (0); }

    /* copy to `event` pointer... */
    *event = WINDOW->da_event.arr[0];

    /* move all the event objects one place to the front... */
    size_t i = 0;
    for ( ; i < WINDOW->da_event.cnt - 1; i++) {
        WINDOW->da_event.arr[i] = WINDOW->da_event.arr[i + 1];
    }

    /* set last queue element to `zero`... */
    WINDOW->da_event.arr[i] = (t_event) { 0 };

    /* ...and decrement the size of the queue... */
    WINDOW->da_event.cnt--;

    /* success */
    return (1);
}


WINDEF int win_eventflush(void) {
    /* null-check... */
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
