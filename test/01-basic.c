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

    t_window win;
    win_wincreate(&win, 800, 600, "Hello, window.h", WINDOW_FLAG_FULLSCREEN);
    win_winmap(win);

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
                    if (event.key.key == WINDOW_KEY_SPACE) {
                        win_winsetflag(win, WINDOW_FLAG_FULLSCREEN);
                    }
                } break;
            }
        }
    }

    /* quit */
    win_quit();
    return (0);
}
