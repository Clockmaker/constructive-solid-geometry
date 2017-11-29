/* FIXME: needs a better name */
#ifndef MATRIX_H
#define MATRIX_H

#define MAT4_LOG(m) D_LOG(\
        "\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f",\
        m[ 0],m[ 1],m[ 2],m[ 3],\
        m[ 4],m[ 5],m[ 6],m[ 7],\
        m[ 8],m[ 9],m[10],m[11],\
        m[12],m[13],m[14],m[15])

#define RAD 0.0174532925199432957692f
#define radians(deg) deg * RAD
#define DEG 57.295779513082320876798f
#define degrees(rad) rad * DEG
//#define isnan(x)


typedef GLfloat mat3[9];
typedef GLfloat mat4[16];
/*
typedef double dvec2[2];
typedef double dvec3[3];
typedef double dmat3[9];
typedef double dmat4[16];
*/

#define mat4_copy(mat, value) memcpy(mat, value, sizeof(mat4))


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
      Tx,   Ty,   Tz, 1.0f }
#define mat4_newScale(Sx, Sy, Sz) \
    (mat4) {\
      Sx, 0.0f, 0.0f, 0.0f,\
    0.0f,   Sy, 0.0f, 0.0f,\
    0.0f, 0.0f,   Sz, 0.0f,\
    0.0f, 0.0f, 0.0f, 1.0f }

//TODO: Missing
//void mat4_rotate(mat4 out, double angle, vec3 axis);


void mat4_multiplyTo(mat4 out, const mat4 one, const mat4 two);
//

void mat4_identity(mat4 out);
void mat4_identity(mat4 out) { //mat4 implicitly decays to a pointer...
    //{[0]=1.0f,[5]=1.0f,[10]=1.0f,[15]=1.0f};
    static mat4 I = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    memcpy(out, I, sizeof(mat4));
}

void mat4_multiply(mat4 out, const mat4 in);
void mat4_multiply(mat4 out, const mat4 in){
    mat4 tmp;
    mat4_multiplyTo(tmp, out, in);
    mat4_copy(out, tmp);
}


void mat4_scale(mat4 out, const vec3 s);
void mat4_scale(mat4 out, const vec3 s) {
    out[ 0] *= s[0];    out[ 1] *= s[0];    out[ 2] *= s[0];    out[ 3] *= s[0];
    out[ 4] *= s[1];    out[ 5] *= s[1];    out[ 6] *= s[1];    out[ 7] *= s[1];
    out[ 8] *= s[2];    out[ 9] *= s[2];    out[10] *= s[2];    out[11] *= s[2];
}

void mat4_translate(mat4 out, const vec3 t);
void mat4_translate(mat4 out, const vec3 t){
    out[ 0] += out[ 3]*t[0];    out[ 1] += out[ 3]*t[1];    out[ 2] += out[ 3]*t[2];
    out[ 4] += out[ 7]*t[0];    out[ 5] += out[ 7]*t[1];    out[ 6] += out[ 7]*t[2];
    out[ 8] += out[11]*t[0];    out[ 9] += out[11]*t[1];    out[10] += out[11]*t[2];
    out[12] += out[15]*t[0];    out[13] += out[15]*t[1];    out[14] += out[15]*t[2];

}

void mat4_translate3f(mat4 out, const float x, const float y, const float z);
void mat4_translate3f(mat4 out, const float x, const float y, const float z){
    out[ 0] += out[ 3]*x;   out[ 1] += out[ 3]*y;   out[ 2] += out[ 3]*z;
    out[ 4] += out[ 7]*x;   out[ 5] += out[ 7]*y;   out[ 6] += out[ 7]*z;
    out[ 8] += out[11]*x;   out[ 9] += out[11]*y;   out[10] += out[11]*z;
    out[12] += out[15]*x;   out[13] += out[15]*y;   out[14] += out[15]*z;
}
//FIXME: hardcode this too
void mat4_rotateX(mat4 out, const double angle);
void mat4_rotateX(mat4 out, const double angle){
    float cosx = cos(angle);
    float sinx = sin(angle);
    mat4_multiply(out, (mat4) {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cosx, sinx, 0.0f,
        0.0f,-sinx, cosx, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

void mat4_rotateY(mat4 out, const double angle);
void mat4_rotateY(mat4 out, const double angle){
    float cosy = cos(angle);
    float siny = sin(angle);
    mat4_multiply(out, (mat4) {
        cosy, 0.0f,-siny, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        siny, 0.0f, cosy, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

void mat4_rotateZ(mat4 out, const double angle);
void mat4_rotateZ(mat4 out, const double angle){
    float cosz = cos(angle);
    float sinz = sin(angle);
    mat4_multiply(out, (mat4) {
        cosz, sinz, 0.0f, 0.0f,
       -sinz, cosz, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

void mat4_multiplyTo(mat4 out, const mat4 one, const mat4 two){
    //FIXME: SIMD
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

#endif
