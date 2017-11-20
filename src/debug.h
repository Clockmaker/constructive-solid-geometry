#ifndef DEBUG_H
#define DEBUG_H
#define DBG(...)\
	printf("%s:%d> ",__FILE__,__LINE__);\
	printf(__VA_ARGS__);\
	printf("\n")



#endif
	