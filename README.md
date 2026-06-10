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

`window.h` comes with ready-to-use samples to work with the library, including:
- No-API solution (bare-bones window creation and event handling), showcasing the most minimal use of the library.
- Software-Renderer solution for X11.
- EGL Context creation.

## Contributions

`window.h` is Free and Open Source software under [LGPL-3 Licence](./LICENCE).
Thus it allows contributors to create, share and modify the content for the library itself.

### 1. Contributing changes.

To contribute your new changes, fixes and demands for the library, follow the general steps of contributing to OSS.
Remember to:
- not modify information about the **original author**, the **version** or the **licence of the software**.
- add yourself to the list of **Contributors** at the top of the library's file.
- open the pull request with your changes at [https://github.com/joleksia/window.h/pulls](https://github.com/joleksia/window.h/pulls).

### 2. Contributing new backend.

To contribute the new backend for the library, follow the general steps of contributing to OSS.
Contributing backend though requires you to also follow the general design of the API, especially it's implementation,
to keep the code clean and tidy as much as possible.

The general template of the API implementation is provided at the bottom of the `window.h` file.
It provides the common definitions of what the library should do PLUS `/* ... */` marks reserved for the platform-specific code.

Then, as follows, follow the steps from previous step. 
 
## Resources

Resources used in this project:
- [The X Window system](https://tronche.com/gui/x/)
- [The Xlib Manual](https://tronche.com/gui/x/xlib/)
- [Create an OpenGL context using Xlib and EGL](https://gist.github.com/pedrominicz/2d81559c5fb66d23d6bb627570956605)

## Licence

This project is licenced under [LGPL-3 Licence](./LICENCE).
