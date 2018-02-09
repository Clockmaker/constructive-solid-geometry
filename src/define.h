/* def.h */
#ifndef DEF_H
#define DEF_H

#define MAX_FILEPATH 64
#define DEFAULT_WINDOW_HEIGHT 640
#define DEFAULT_WINDOW_WIDTH 640

#define MOUSE_DELTA 0.1f


//#define M_PI 3.1415926535897932384626 //math.h
#define PI 3.141592653589793238462643383279502884L // long double pi

#define ARRAY_LENGTH(x) ( sizeof(x) / sizeof(x[0]) )

#ifdef DEBUG
	#define D_LOG(...)\
		printf("%s:%d> ",__FILE__,__LINE__);\
		printf(__VA_ARGS__);\
		printf("\n")
	#define D_CHECK(condition, error_message)\
		do{if(condition){ \
		printf("%s:%d> %s\n", __FILE__,__LINE__,error_message);\
		}while(0)
#else
	#define D_LOG(...) 
	#define D_CHECK(...)

#endif

//typedef enum{false=0,true} bool;
#define uint unsigned int
#define ushort unsigned short

#endif
