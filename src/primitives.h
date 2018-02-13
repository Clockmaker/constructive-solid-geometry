/* primitives.h */
#ifndef PRIMITIVES_H
#define PRIMITIVES_H

typedef struct plane_s {
	struct sketch_s *path[10];
	vec3 normal;
	vec3 origin;
	//vec4 coeff;
} plane;

typedef struct sketch_s {
	struct plane_s *link[10];
	vec2 points[];
} sketch;

#endif