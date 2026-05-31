#include <stdio.h>
#
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
    if (!win_wincreate(&window, 800, 600, "01 - basic", 0)) {
        fprintf(stderr, "win_wincreate() failed\n");

        win_quit();
        return (1);
    }

    /* map window onto the screen */
    if (!win_winmap(window)) {
        fprintf(stderr, "win_wincreate() failed\n");

        win_quit();
        return (1);
    }

    int exit = 0;
    while (!exit) {
        /* poll events */
        t_event event = { 0 };
        while (win_eventpoll(&event)) {
            switch (event.type) {
                case (WINDOW_EVENT_QUIT): {
                    printf("WINDOW_EVENT_QUIT\n");
                    exit = 1;
                } break;

                case (WINDOW_EVENT_KEYBOARD_KEY): {
                    printf("WINDOW_EVENT_KEYBOARD_KEY:\n- key: %d\n- state: %d\n", event.key.key, event.key.state);
                } break;
            }
        }
    }

    /* quit */
    win_windestroy(window), window = 0;
    win_quit();
    return (0);
}
