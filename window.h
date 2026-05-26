#if defined (__cplusplus)
# pragma once
#endif
#
#if !defined (_window_h_)
# define _window_h_ 1
#
# /* WINAPI (window.h API) - global functions */
# if !defined (WINAPI)
#  define WINAPI extern inline
# endif /* WINAPI */
#
# /* WININT (window.h internal API) - internal static functions */
# if !defined (WININT)
#  define WININT static inline
# endif /* WININT */
#
# include <stddef.h>
# include <stdint.h>

/* ... */

# if defined WINDOW_IMPLEMENTATION

/* ... */

# endif /* WINDOW_IMPLEMENTATION */
#endif /* _window_h_ */
