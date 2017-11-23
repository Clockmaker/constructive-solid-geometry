/* def.h */
#ifndef DEF_H
#define DEF_H

#define MAX_FILEPATH 64
#define SCREEN_HEIGHT 
#define SCREEN_WIDTH

//#define M_PI 3.1415926535897932384626 //math.h
// long double pi
#define PI 3.141592653589793238462643383279502884L

#define ARRAY_LENGTH(x) ( sizeof(x) / sizeof(x[0]) )

#ifndef DEBUG_H
	#define D_LOG(...) 
	//null statement to avoid breaking something
//{};;0
#endif
//typedef enum{false=0,true} bool;

#endif
