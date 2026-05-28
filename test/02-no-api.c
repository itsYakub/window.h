#include <stdio.h>
#
#include <X11/Xlib.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* initialize window.h */
    win_init();
   
    /* create window */
    t_window window = 0;
    win_create(&window, 800, 600, "02 - no API", 0);
    if (!window) {
        return (1);
    }
    win_map(window);

    /* query properties */
    Display *dpy = win_getwinprop(window, WINDOW_PROP_WINDOW_X11_DISPLAY);
    XID w_id = *(XID *) win_getwinprop(window, WINDOW_PROP_WINDOW_X11_WINDOW_ID);
    Visual *visual = win_getwinprop(window, WINDOW_PROP_WINDOW_X11_VISUAL);

    /* get monitor size */
    size_t width  = 0,
           height = 0;
    win_getsize(&width, &height);

    /* create buffer */
    uint32_t *buffer = malloc(width * height * sizeof(uint32_t));
    if (!buffer) {
        return (1);
    }

    /* create bitmap */
    XImage *bitmap = XCreateImage(dpy, visual, 24, ZPixmap, 0, (char *) buffer, width, height, 32, width * sizeof(uint32_t));
    if (!bitmap) {
        return (1);
    }

    /* create graphics context */
    GC gc = XCreateGC(dpy, w_id, 0, 0);

    int exit = 0;
    while (!exit) {
        /* get window size */
        size_t width  = 0,
               height = 0;
        win_getwinsize(window, &width, &height);

        /* set the background color */
        for (size_t i = 0; i < width * height; i++) {
            buffer[i] = 0xff191919; /* equivalent of: (1.0f, 0.1, 0.1, 0.1) */
        }

        /* display */
        XPutImage(dpy, w_id, gc, bitmap, 0, 0, 0, 0, width, height);

        /* poll events */
        t_event event = { 0 };
        while (win_eventpoll(&event)) {
            switch (event.type) {
                case (WINDOW_EVENT_QUIT): {
                    printf("WINDOW_EVENT_QUIT\n");
                    exit = 1;
                } break;
            }
        }
    }

    /* quit */
    XFreeGC(dpy, gc), gc = 0;
    XDestroyImage(bitmap), bitmap = 0;
    win_destroy(window), window = 0;
    win_quit();
    return (0);
}
