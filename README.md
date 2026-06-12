<div align="center">

# window.h - minimalistic windowing library 

</div>

`window.h` is a single-header minimalistic windowing solution for GNU/Linux, unix-like and win32 systems.

```c
#include <stdio.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* initialize window.h */
    win_init();

    /* create window */
    t_window win;
    win_wincreate(&win, 800, 600, "Hello, window.h", 0);
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
            }
        }
    }

    /* quit */
    win_quit();
    return (0);
}
```

It provides a simple interface for creating and manipulating windows on the screen and serves as a great
learning resource for discovering how large windowing libraries, such as `SDL`, `GLFW`, `RGFW`, `SFML` etc.
deals with windowing.

## Contributions

### 1. Contributing new backend.

*TODO: add this section*

## Resources

Resources used in this project:
- [The X Window system](https://tronche.com/gui/x/)
- [The Xlib Manual](https://tronche.com/gui/x/xlib/)
- [Create an OpenGL context using Xlib and EGL](https://gist.github.com/pedrominicz/2d81559c5fb66d23d6bb627570956605)

## Licence

This project is licenced under [LGPL-3 Licence](./LICENCE).
