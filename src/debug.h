#ifndef __debug_h__
#define __debug_h__
#endif

#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifdef NODEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG: %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif
