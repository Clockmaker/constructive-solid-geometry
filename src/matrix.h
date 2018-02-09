/* 
Do NOT use.

FIXME: needs a better name 

TODO:
sort by alphabetic order

*/
#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"

typedef float mat3[9];
typedef float mat4[16];
/*
typedef double dvec2[2];
typedef double dvec3[3];
typedef double dmat3[9];
typedef double dmat4[16];
*/
#define RAD 0.0174532925199432957692f
#define radians(deg) deg * RAD
#define DEG 57.295779513082320876798f
#define degrees(rad) rad * DEG
//#define isnan(x)

#define MAT4_LOG(m) D_LOG(\
        "\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f",\
        m[ 0],m[ 1],m[ 2],m[ 3],\
        m[ 4],m[ 5],m[ 6],m[ 7],\
        m[ 8],m[ 9],m[10],m[11],\
        m[12],m[13],m[14],m[15])

#define mat4_copy(mat,toCopy) memcpy((mat), (toCopy), sizeof(mat4))

#define mat4_newTranslate(V) \
    (mat4) {\
    1.0f, 0.0f, 0.0f, 0.0f,\
    0.0f, 1.0f, 0.0f, 0.0f,\
    0.0f, 0.0f, 1.0f, 0.0f,\
    V[0], V[1], V[2], 1.0f }
#define mat4_newTranslate3f(Tx,Ty,Tz) \
    (mat4) {\
    1.0f, 0.0f, 0.0f, 0.0f,\
    0.0f, 1.0f, 0.0f, 0.0f,\
    0.0f, 0.0f, 1.0f, 0.0f,\
    (Tx), (Ty), (Tz), 1.0f }
#define mat4_newScale(Sx, Sy, Sz) \
    (mat4) {\
    (Sx), 0.0f, 0.0f, 0.0f,\
    0.0f, (Sy), 0.0f, 0.0f,\
    0.0f, 0.0f, (Sz), 0.0f,\
    0.0f, 0.0f, 0.0f, 1.0f }
#define mat4_newScale1f(S) \
    (mat4) {\
     (S), 0.0f, 0.0f, 0.0f,\
    0.0f,  (S), 0.0f, 0.0f,\
    0.0f, 0.0f,  (S), 0.0f,\
    0.0f, 0.0f, 0.0f, 1.0f }

//TODO: missing arbirtrary rotation (vector+angle)
static void mat4_identity(mat4 out);
static void mat4_transpose(mat4 out);
static void mat4_rotate(mat4 out, double angle, vec3 axis);
static void mat4_multiply(mat4 out, const mat4 one, const mat4 two);
static void mat4_mul(mat4 out, const mat4 in);
static void mat4_scale(mat4 out, const vec3 s);
static void mat4_scale1f(mat4 out, const float s);
static void mat4_translate(mat4 out, const vec3 t);
static void mat4_translate3f(mat4 out, const float x, const float y, const float z);
static void mat4_rotateX(mat4 out, const double angle);
static void mat4_rotateY(mat4 out, const double angle);
static void mat4_rotateZ(mat4 out, const double angle);
static void mat4_rotateXY(mat4 out, const double a, const double b);

#define mat4_newOrtho(left, right, bottom, top, zNear, zFar) \
    (mat4) {\
    2.0f/((right)-(left)), 0.0f, 0.0f, 0.0f,\
    0.0f, 2.0f/((bottom)-(top)), 0.0f, 0.0f,\
    0.0f, 0.0f, 2.0f/((zFar)-(zNear)), 0.0f,\
    ((left)+(right))/((left)-(right)), ((bottom)+(top))/((top)-(bottom)), ((zNear)+(zFar))/((zNear)-(zFar)), 1.0f }

static void mat4_lookAt(mat4 out, const vec3 eye, const vec3 center, vec3 up);
static void mat4_perspective(mat4 out, const double fovy, const double aspect, const double zNear, const double zFar);

#endif
/*****************************************************************************/
#ifdef MATRIX_H_SOURCE

static void mat4_identity(mat4 out) { //mat4 implicitly decays to a pointer...
    //{[0]=1.0f,[5]=1.0f,[10]=1.0f,[15]=1.0f};
    static mat4 I = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    memcpy(out, I, sizeof(mat4));
}
static void mat4_transpose(mat4 out){
    memcpy(out, (mat4) {\
        out[0], out[4], out[ 8], out[12],\
        out[1], out[5], out[ 9], out[13],\
        out[2], out[6], out[10], out[14],\
        out[3], out[7], out[11], out[15]
    }, sizeof(mat4));
}

static void mat4_mul(mat4 out, const mat4 in){
    mat4 tmp;
    mat4_multiply(tmp, out, in);
    mat4_copy(out, tmp);
}

static void mat4_scale(mat4 out, const vec3 s) {
    out[ 0] *= s[0];    out[ 1] *= s[0];    out[ 2] *= s[0];    out[ 3] *= s[0];
    out[ 4] *= s[1];    out[ 5] *= s[1];    out[ 6] *= s[1];    out[ 7] *= s[1];
    out[ 8] *= s[2];    out[ 9] *= s[2];    out[10] *= s[2];    out[11] *= s[2];
}
static void mat4_scale1f(mat4 out, const float s) {
    out[ 0] *= s;    out[ 1] *= s;    out[ 2] *= s;    out[ 3] *= s;
    out[ 4] *= s;    out[ 5] *= s;    out[ 6] *= s;    out[ 7] *= s;
    out[ 8] *= s;    out[ 9] *= s;    out[10] *= s;    out[11] *= s;
}

static void mat4_translate(mat4 out, const vec3 t){
    out[ 0] += out[ 3]*t[0];    out[ 1] += out[ 3]*t[1];    out[ 2] += out[ 3]*t[2];
    out[ 4] += out[ 7]*t[0];    out[ 5] += out[ 7]*t[1];    out[ 6] += out[ 7]*t[2];
    out[ 8] += out[11]*t[0];    out[ 9] += out[11]*t[1];    out[10] += out[11]*t[2];
    out[12] += out[15]*t[0];    out[13] += out[15]*t[1];    out[14] += out[15]*t[2];

}

static void mat4_translate3f(mat4 out, const float x, const float y, const float z){
    out[ 0] += out[ 3]*x;   out[ 1] += out[ 3]*y;   out[ 2] += out[ 3]*z;
    out[ 4] += out[ 7]*x;   out[ 5] += out[ 7]*y;   out[ 6] += out[ 7]*z;
    out[ 8] += out[11]*x;   out[ 9] += out[11]*y;   out[10] += out[11]*z;
    out[12] += out[15]*x;   out[13] += out[15]*y;   out[14] += out[15]*z;
}
//FIXME: hardcode this too
static void mat4_rotateX(mat4 out, const double angle){
    float cosx = cos(angle);
    float sinx = sin(angle);
    mat4_mul(out, (mat4) {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cosx,-sinx, 0.0f,
        0.0f, sinx, cosx, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

static void mat4_rotateY(mat4 out, const double angle){
    float cosy = cos(angle);
    float siny = sin(angle);
    mat4_mul(out, (mat4) {
        cosy, 0.0f, siny, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
       -siny, 0.0f, cosy, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

static void mat4_rotateZ(mat4 out, const double angle){
    float cosz = cos(angle);
    float sinz = sin(angle);
    mat4_mul(out, (mat4) {
        cosz, sinz, 0.0f, 0.0f,
       -sinz, cosz, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

static void mat4_rotateXY(mat4 out, const double b, const double a){
    float cx = cos(a), sx = sin(a),
          cy = cos(b), sy = sin(b);
    mat4_mul(out, (mat4) {
           cy,  0.0f,    sy, 0.0f,
        sx*sy,    cx,-sx*cy, 0.0f,
       -sy*cx,    sx, cy*cx, 0.0f,
         0.0f,  0.0f,  0.0f, 1.0f
    });
}

static void mat4_multiply(mat4 out, const mat4 one, const mat4 two){
    //TODO: SIMD?
    out[ 0] = one[ 0]*two[ 0] + one[ 1]*two[ 4] + one[ 2]*two[ 8] + one[ 3]*two[12];//
    out[ 1] = one[ 0]*two[ 1] + one[ 1]*two[ 5] + one[ 2]*two[ 9] + one[ 3]*two[13];
    out[ 2] = one[ 0]*two[ 2] + one[ 1]*two[ 6] + one[ 2]*two[10] + one[ 3]*two[14];
    out[ 3] = one[ 0]*two[ 3] + one[ 1]*two[ 7] + one[ 2]*two[11] + one[ 3]*two[15];
    out[ 4] = one[ 4]*two[ 0] + one[ 5]*two[ 4] + one[ 6]*two[ 8] + one[ 7]*two[12];//
    out[ 5] = one[ 4]*two[ 1] + one[ 5]*two[ 5] + one[ 6]*two[ 9] + one[ 7]*two[13];
    out[ 6] = one[ 4]*two[ 2] + one[ 5]*two[ 6] + one[ 6]*two[10] + one[ 7]*two[14];
    out[ 7] = one[ 4]*two[ 3] + one[ 5]*two[ 7] + one[ 6]*two[11] + one[ 7]*two[15];
    out[ 8] = one[ 8]*two[ 0] + one[ 9]*two[ 4] + one[10]*two[ 8] + one[11]*two[12];//
    out[ 9] = one[ 8]*two[ 1] + one[ 9]*two[ 5] + one[10]*two[ 9] + one[11]*two[13];
    out[10] = one[ 8]*two[ 2] + one[ 9]*two[ 6] + one[10]*two[10] + one[11]*two[14];
    out[11] = one[ 8]*two[ 3] + one[ 9]*two[ 7] + one[10]*two[11] + one[11]*two[15];
    out[12] = one[12]*two[ 0] + one[13]*two[ 4] + one[14]*two[ 8] + one[15]*two[12];//
    out[13] = one[12]*two[ 1] + one[13]*two[ 5] + one[14]*two[ 9] + one[15]*two[13];
    out[14] = one[12]*two[ 2] + one[13]*two[ 6] + one[14]*two[10] + one[15]*two[14];
    out[15] = one[12]*two[ 3] + one[13]*two[ 7] + one[14]*two[11] + one[15]*two[15];
}

static void mat4_lookAt(mat4 out, const vec3 eye, const vec3 center, vec3 up){
    vec3 forward = vec3_newSub(center, eye);
    vec3_normalize(forward);
    vec3 right = vec3_newCross(up, forward);
    vec3_normalize(right);
    vec3_crossTo(up, forward, right);
    
    memcpy(out, (mat4) {\
      right[0], up[0], forward[0], 0.0f,\
      right[1], up[1], forward[1], 0.0f,\
      right[2], up[2], forward[2], 0.0f,\
      -vec3_dot(right,eye), -vec3_dot(up,eye), -vec3_dot(forward,eye), 1.0f \
    }, sizeof(mat4));
}
static void mat4_perspective(mat4 out, const double fovy, const double aspect, const double zNear, const double zFar){
    const double f = 1 / tan(fovy/2);
    const double z = zNear - zFar;

    memcpy(out, (mat4) {                      \
      f/aspect, 0.0f, 0.0f, 0.0f,             \
          0.0f,   f, 0.0f, 0.0f,              \
          0.0f, 0.0f,-(zFar+zNear)/z,   1.0f, \
          0.0f, 0.0f, (2*zFar*zNear)/z, 0.0f  \
    }, sizeof(mat4));

}


#endif