#ifndef LKC_EXPORT_H
#define LKC_EXPORT_H

#if defined(LIBLKC_STATIC)         // Using static.
#  define LIBLKC_SYMEXPORT
#elif defined(LIBLKC_STATIC_BUILD) // Building static.
#  define LIBLKC_SYMEXPORT
#elif defined(LIBLKC_SHARED)       // Using shared.
#  ifdef _WIN32
#    define LIBLKC_SYMEXPORT __declspec(dllimport)
#  else
#    define LIBLKC_SYMEXPORT
#  endif
#elif defined(LIBLKC_SHARED_BUILD) // Building shared.
#  ifdef _WIN32
#    define LIBLKC_SYMEXPORT //__declspec(dllexport) Note: using .def file.
#  else
#    define LIBLKC_SYMEXPORT
#  endif
#else
// If none of the above macros are defined, then we assume we are being used
// by some third-party build system that cannot/doesn't signal the library
// type. Note that this fallback works for both static and shared libraries
// provided the library only exports functions (in other words, no global
// exported data) and for the shared case the result will be sub-optimal
// compared to having dllimport. If, however, your library does export data,
// then you will probably want to replace the fallback with the (commented
// out) error since it won't work for the shared case.
//
#  define LIBLKC_SYMEXPORT         // Using static or shared.
//#  error define LIBLKC_STATIC or LIBLKC_SHARED preprocessor macro to signal liblkc library type being linked
#endif

#endif /* LKC_EXPORT_H */
