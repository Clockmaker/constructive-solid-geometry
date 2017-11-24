/* def.h */
#ifndef DEF_H
#define DEF_H

#define MAX_FILEPATH 64
#define SCREEN_HEIGHT 
#define SCREEN_WIDTH

//#define M_PI 3.1415926535897932384626 //math.h
#define PI 3.141592653589793238462643383279502884L // long double pi

#define ARRAY_LENGTH(x) ( sizeof(x) / sizeof(x[0]) )

#ifdef DEBUG
#define D_LOG(...)\
	printf("%s:%d> ",__FILE__,__LINE__);\
	printf(__VA_ARGS__);\
	printf("\n")

#else
	#define D_LOG(...) 
	//null statement to avoid breaking something
	//{};;0

#endif

//typedef enum{false=0,true} bool;
#define uint unsigned int

#endif
