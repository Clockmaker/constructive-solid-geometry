/* vector.h */
#ifndef VECTOR_H
#define VECTOR_H

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];
/*
typedef double dvec2[2];
typedef double dvec3[3];
*/
#define vec3_newCopy(v) (vec3) {(v)[0], (v)[1], (v)[2]}
#define vec3_copy(a,b) memcpy((a),(b), sizeof(vec3))
#define vec3_length(v) sqrt((v)[0]*(v)[0] + (v)[1]*(v)[1] + (v)[2]*(v)[2])
#define vec3_newCross(a,b) \
       { (a)[1]*(b)[2]-(a)[2]*(b)[1],\
         (a)[2]*(b)[0]-(a)[0]*(b)[2],\
         (a)[0]*(b)[1]-(a)[1]*(b)[0] }

#define vec3_dot(a,b) ((a)[0]*(b)[0] + (a)[1]*(b)[1] + (a)[2]*(b)[2])
//inline float vec3_dot(const vec3 a, const vec3 b){return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];}

#define vec3_newAdd(a,b) {(a)[0]+(b)[0], (a)[1]+(b)[1], (a)[2]+(b)[2]}
//#define vec3_add(a,b) (vec3){(a)[0]+(b)[0], (a)[1]+(b)[1], (a)[2]+(b)[2]}
#define vec3_newSub(a,b) {(a)[0]-(b)[0], (a)[1]-(b)[1], (a)[2]-(b)[2]}
//#define vec3_sub(a,b) (vec3){(a)[0]-(b)[0], (a)[1]-(b)[1], (a)[2]-(b)[2]}
#define vec3_newNeg(a) {-(a)[0],-(a)[1],-(a)[2]}
#define vec3_neg(a) (vec3){-(a)[0],-(a)[1],-(a)[2]}

static void vec3_normalized(vec3 out, const vec3 vector);
static void vec3_normalize(vec3 vector);
static inline void vec3_crossTo(vec3 out, const vec3 a, const vec3 b);
static void vec3_add(vec3 out, const vec3 a, const vec3 b);
static void vec3_sub(vec3 out, const vec3 a, const vec3 b);

#endif
/*****************************************************************************/
#ifdef MATRIX_H_SOURCE

static void vec3_normalized(vec3 out, const vec3 vector){
    vec3_copy(out, vector);
    vec3_normalize(out);
}

static void vec3_normalize(vec3 vector){
    float norm = vec3_length(vector);
    vector[0] /= norm;
    vector[1] /= norm;
    vector[2] /= norm;
}

static inline void vec3_crossTo(vec3 out, const vec3 a, const vec3 b){
    out[0] =  a[1]*b[2] - a[2]*b[1];
    out[1] =  a[2]*b[0] - a[0]*b[2];
    out[2] =  a[0]*b[1] - a[1]*b[0];
}

static void vec3_add(vec3 out, const vec3 a, const vec3 b){
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}

static void vec3_sub(vec3 out, const vec3 a, const vec3 b){
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}

#endif