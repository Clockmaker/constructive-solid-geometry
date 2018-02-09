#include "define.h"
#include "common.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "matrix.h"
#include "shader.h"
#include "draw.h"
#include "ui.h"


struct va_s line;

void draw_init(void){
    line.shader = Shader_loadFromFile("./shader/line.vert", "./shader/line.frag");
    glBindFragDataLocation(line.shader, 0, "color");
    
    glGenVertexArrays(1, &line.vao);
    glBindVertexArray(line.vao);

    GLfloat v[] ={
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        100.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        0.0f, 100.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 100.0f,  0.0f, 1.0f, 0.0f,
    };
    glGenBuffers(1, &line.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, line.vbo);
    glBufferData(GL_ARRAY_BUFFER, 36*sizeof(GLfloat), v, GL_STATIC_DRAW);

    glBindVertexArray(line.vao);
    //glBindBuffer(GL_ARRAY_BUFFER, line.vbo);
    glUseProgram(line.shader);

    GLint Attrib = glGetAttribLocation(line.shader, "position");
    glEnableVertexAttribArray(Attrib);
    glVertexAttribPointer(Attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), NULL);

    Attrib = glGetAttribLocation(line.shader, "colorBuf");
    glEnableVertexAttribArray(Attrib);
    glVertexAttribPointer(Attrib, 3, GL_FLOAT, GL_FALSE,  6*sizeof(GLfloat),  (void*)(3*sizeof(GLfloat)) );
    line.uniform_matrix = glGetUniformLocation(line.shader, "camera");
}

void draw_origin(void){

    glBindVertexArray(line.vao);

    //glBindBuffer(GL_ARRAY_BUFFER, line.vbo);
    glUseProgram(line.shader);
    glUniformMatrix4fv(line.uniform_matrix, 1, GL_FALSE, Camera.matrix);
    glDrawArrays(GL_LINES, 0, 6);

}