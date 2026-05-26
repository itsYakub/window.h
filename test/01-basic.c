#include <stdio.h>
#
#define WINDOW_PLATFORM_X11
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* initialize window.h */
    if (!win_init()) {
        fprintf(stderr, "win_init() failed\n");
        return (1);
    }

    /* create window */
    t_window window = 0;
    if (!win_create(&window, 800, 600, "Hello, window.h", 0)) {
        fprintf(stderr, "win_create() failed\n");

        win_quit();
        return (1);
    }

    /* map window onto the screen */
    if (!win_map(window)) {
        fprintf(stderr, "win_create() failed\n");

        win_quit();
        return (1);
    }

    int exit = 0;
    while (!exit) {
        /* poll events */
        t_event event = { 0 };
        while (win_pollEvents(&event)) {
            switch (event.type) {
                case (WINDOW_EVENT_QUIT): {
                    exit = 1;
                } break;
            }
        }
    }

    /* quit */
    win_destroy(window), window = 0;
    win_quit();
    return (0);
}
