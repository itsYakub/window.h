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
#  error
# endif
#
# include <stddef.h>
# include <stdint.h>

/* ... */

# if defined WINDOW_IMPLEMENTATION
#
#  /* Auto - Configuration preprocessor statements... */
#  if !defined (WINDOW_PLATFORM_X11) !defined (WINDOW_PLATFORM_WAYLAND) !defined (WINDOW_PLATFORM_WIN32)
#
#   /* default window library for *nix should be X11... */
#   if WINDOW_PLATFORM == "linux" || WINDOW_PLATFORM == "bsd"
#    define WINDOW_PLATFORM_X11 1
#
#   /* default window library for win32 should be... win32... */
#   elif WINDOW_PLATFORM == "win32"
#    define WINDOW_PLATFORM_WIN32 1
#
#   /* undefined windowing library... */
#   else
#    error
#   endif
#
#  endif
#
#  /* WINDOW_PLATFORM_X11 - Unix X11 implementation layer */
#  if defined (WINDOW_PLATFORM_X11)
#   include <X11/X.h>
#   include <X11/Xlib.h>
#   include <X11/Xutil.h>
#   include <X11/Xatom.h>

/* ... */

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
