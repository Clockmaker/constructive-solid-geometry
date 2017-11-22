#ifndef DEBUG_H
#define DEBUG_H
#define D_LOG(...)\
	printf("%s:%d> ",__FILE__,__LINE__);\
	printf(__VA_ARGS__);\
	printf("\n")



#endif
	