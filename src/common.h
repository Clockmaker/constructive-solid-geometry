/* common.h */
#ifndef COMMON_H
#define COMMON_H
#if defined(__linux__)
# define DP_OS_STR		"linux"
#elif defined(WIN64)
# define DP_OS_STR		"win64"
	#include <windows.h>
#elif defined(MACOSX)
# define DP_OS_STR		"osx"
#endif

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <math.h>

#endif
