/* draw.h */
#ifndef DRAW_H
#define DRAW_H

struct va_s{
    GLuint vao, vbo, ebo;
    GLuint shader;
    mat4 matrix;
    GLint uniform_matrix;

};

void draw_init(void);

void draw_origin(void);

#endif