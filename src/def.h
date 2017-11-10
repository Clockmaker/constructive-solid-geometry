/* def.h */
#ifndef DEF_H
#define DEF_H

#define MAX_FILEPATH 64
#define SCREEN_HEIGHT 
#define SCREEN_WIDTH

#if defined(__linux__)
# define DP_OS_STR		"linux"
#elif defined(WIN64)
# define DP_OS_STR		"win64"
	#include <windows.h>
#elif defined(MACOSX)
# define DP_OS_STR		"osx"
#endif

//#define M_PI 3.1415926535897932384626
#define ARRAY_LENGTH(x)  (sizeof(x) / sizeof(x[0]))
#define FLOAT_IS_TRUE_FOR_INT(x) ((x) & 0x7FFFFFFF) // also match "negative zero" floats of value 0x80000000

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef enum{false=0,true} bool;

#endif