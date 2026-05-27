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

WINDEF int win_pollEvents(t_event *);

WINDEF int win_waitEvents(t_event *);

WINDEF int win_pushEvents(t_event *);

WINDEF int win_popEvents(t_event *);

WINDEF int win_flush(void);

/* timing functions */

WINDEF uint64_t win_getTime(void);

WINDEF int win_waitTime(uint64_t);

# if defined WINDOW_IMPLEMENTATION
#
#  include <stdlib.h>
#
#  /* WINDOW_PLATFORM_X11 - Unix X11 implementation layer */
#  if defined (WINDOW_PLATFORM_X11)
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

WININT int __win_pollEvents_x11(t_event *);

WININT int __win_waitEvents_x11(t_event *);

WININT int __win_pushEvents_x11(t_event *);

WININT int __win_popEvents_x11(t_event *);

WININT int __win_flush_x11(void);


WINDEF int win_pollEvents(t_event *event) { return (__win_pollEvents_x11(event)); }


WINDEF int win_waitEvents(t_event *event) { return (__win_waitEvents_x11(event)); }


WINDEF int win_pushEvents(t_event *event) { return (__win_pushEvents_x11(event)); }


WINDEF int win_popEvents(t_event *event) { return (__win_popEvents_x11(event)); }


WINDEF int win_flush(void) { return (__win_flush_x11()); }

/* timing functions */

WINDEF uint64_t win_getTime(void) {
    struct timeval t;
    if (gettimeofday(&t, 0) == -1) {
        return (0);
    }

    return (t.tv_sec * 1000 + t.tv_usec / 1000);
}


WINDEF int win_waitTime(uint64_t ms) {
    uint64_t t = win_getTime();
    if (t == 0) { return (0); }

    while ((win_getTime() - t) < ms);
    return (1);
}


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

    /* set up event queue... */
    WINDOW->da_event.cnt = 0;
    WINDOW->da_event.cap = 16;
    WINDOW->da_event.arr = calloc(WINDOW->da_event.cap, sizeof(t_event));
    if (!WINDOW->da_event.arr) { return (0); }

    /* success */
    return (1);
}


WININT int __win_quit_x11(void) {
    /* terminate `xlib`... */
    XCloseDisplay(WINDOW->xlib.dpy), WINDOW->xlib.dpy = 0;
   
    /* deallocate da_event... */
    free(WINDOW->da_event.arr);
    WINDOW->da_event.arr = 0;
    WINDOW->da_event.cnt = 0;
    WINDOW->da_event.cap = 0;

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

    /* set the `result` object as `win` return object... */
    *win = result;
    
    /* success */
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

WININT int __win_eventLoop_x11(void);

WININT int __win_pollEvents_x11(t_event *event) {
    /* null-check... */
    if (!event) { return (0); }

    /* poll events from platform queue... */
    if (win_popEvents(event)) { return (1); }

    /* handle platform events... */
    __win_eventLoop_x11();

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

WININT int __win_eventLoop_x11(void) {
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
                            .quit = (t_eventQuit) {
                                .type = WINDOW_EVENT_QUIT,
                                .timestamp = win_getTime() 
                            }
                        };

                        win_pushEvents(&event);
                    }
                }
            } break;
        }
    }

    /* success */
    return (1);
}


WININT int __win_waitEvents_x11(t_event *event) {
    /* null-check... */
    if (!event) { return (0); }

    /* success */
    return (1);
}


WININT int __win_isCoalescable_x11(t_eventType);

WININT int __win_pushEvents_x11(t_event *event) {
    /* null-check... */
    if (!event) { return (0); }

    /* bounds-check... */
    if (WINDOW->da_event.cnt >= WINDOW->da_event.cap) {
        WINDOW->da_event.cap *= 1.5;
        WINDOW->da_event.arr = realloc(WINDOW->da_event.arr, WINDOW->da_event.cap * sizeof(t_event));
        if (!WINDOW->da_event.arr) { return (0); }
    }

    /* tail-coalescing... */
    if (WINDOW->da_event.cnt > 0) {
        t_event *tail = &WINDOW->da_event.arr[WINDOW->da_event.cnt - 1];
        if (tail->type == event->type && __win_isCoalescable_x11(event->type)) {
            *tail = *event;
            return (1);
        }
    }

    /* copy-assignment event object to event queue... */
    WINDOW->da_event.arr[WINDOW->da_event.cnt++] = *event;

    /* success */
    return (1);
}

WININT int __win_isCoalescable_x11(t_eventType type) {
    const uint64_t coalescable = 
        (1U << WINDOW_EVENT_NONE);

    return ((coalescable >> type) & 1);
}


WININT int __win_popEvents_x11(t_event *event) {
    /* null-check... */
    if (!event) { return (0); }

    /* bounds-check... */
    if (WINDOW->da_event.cnt == 0) { return (0); }

    /* copy to `event` pointer... */
    *event = WINDOW->da_event.arr[0];

    /* move all the event objects one place to the front... */
    size_t i = 0;
    while (i < WINDOW->da_event.cnt - 1) {
        WINDOW->da_event.arr[i] = WINDOW->da_event.arr[++i];
    }

    /* set last queue element to `zero`... */
    WINDOW->da_event.arr[i] = (t_event) { 0 };

    /* ...and decrement the size of the queue... */
    WINDOW->da_event.cnt--;

    /* success */
    return (1);
}


WININT int __win_flush_x11(void) {
    if (!XFlush(WINDOW->xlib.dpy)) { return (0); }

    /* success */
    return (1);
}

#  endif /* WINDOW_PLATFORM_X11 */
#
#  /* WINDOW_PLATFORM_WAYLAND - Unix Wayland implementation layer */
#  if defined (WINDOW_PLATFORM_WAYLAND)
#   include <unistd.h>
#   include <sys/time.h>
#
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
