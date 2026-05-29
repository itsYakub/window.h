#include <stdio.h>
#
#include <GL/gl.h>
#include <EGL/egl.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

/* egl context struct */
static struct {
    EGLDisplay dpy;
    EGLSurface surface;
    EGLConfig  cfg;
    EGLContext ctx;
} egl = { 0 };

/* egl config attributes */
static const EGLint cfg_attr[] = {
    EGL_SURFACE_TYPE,     EGL_WINDOW_BIT,
    EGL_RED_SIZE,         8,
    EGL_GREEN_SIZE,       8,
    EGL_BLUE_SIZE,        8,
    EGL_RENDERABLE_TYPE,  EGL_OPENGL_BIT,
    EGL_NONE
};

/* egl context attributes */
static const EGLint ctx_attr[] = {
    EGL_CONTEXT_MAJOR_VERSION, 4,
    EGL_CONTEXT_MINOR_VERSION, 6,
    EGL_NONE
};

int main(void) {
    /* initialize window.h */
    win_init();
   
    /* create window */
    t_window window = 0;
    win_wincreate(&window, 800, 600, "03 - egl", 0);
    win_winmap(window);
    
    /* query EGL display */
    Display *dpy = win_wingetprop(window, WINDOW_PROP_WINDOW_X11_DISPLAY);
    egl.dpy = eglGetDisplay((EGLDisplay) dpy);
    if (egl.dpy == EGL_NO_DISPLAY) {
        return (1);
    }

    /* initialzie EGL */
    if (!eglInitialize(egl.dpy, 0, 0)) { return (1); }
    if (!eglBindAPI(EGL_OPENGL_API))   { return (1); }

    /* query EGL config */
    EGLint cfg_cnt = 0;
    if (!eglChooseConfig(egl.dpy, cfg_attr, &egl.cfg, 1, &cfg_cnt)) { return (1); }
    if (cfg_cnt != 1) {
        return (1);
    }

    /* create EGL surface */
    XID w_id = *(XID *) win_wingetprop(window,WINDOW_PROP_WINDOW_X11_WINDOW_ID);
    egl.surface = eglCreateWindowSurface(egl.dpy, egl.cfg, w_id, 0);
    if (egl.surface == EGL_NO_SURFACE) {
        return (1);
    }

    /* create EGL context */
    egl.ctx = eglCreateContext(egl.dpy, egl.cfg, EGL_NO_CONTEXT, ctx_attr);
    if (egl.ctx == EGL_NO_CONTEXT) {
        return (1);
    }

    /* make context current */
    if (!eglMakeCurrent(egl.dpy, egl.surface, egl.surface, egl.ctx)) {
        return (1);
    }

    printf("GL_VERSION: %s\n", glGetString(GL_VERSION));

    int exit = 0;
    while (!exit) {
        /* render */
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        eglSwapBuffers(egl.dpy, egl.surface);

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
    eglMakeCurrent(egl.dpy, 0, 0, 0);
    eglDestroyContext(egl.dpy, egl.ctx);
    eglDestroySurface(egl.dpy, egl.surface);
    eglTerminate(egl.dpy);

    win_windestroy(window), window = 0;
    win_quit();
    return (0);
}
