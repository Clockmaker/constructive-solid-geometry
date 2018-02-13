#include "define.h"
#include "common.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define MATRIX_H_SOURCE
#include "matrix.h"
#include "shader.h"

#include "input.h"
#include "ui.h"
#include "draw.h"

#define STB_IMAGE_IMPLEMENTATION
//#define STBI_ONLY_TGA
#include "stb_image.h"

struct camera_s Camera = {.zoom=1.0f};

struct mdl {
    GLuint vao, vbo, ebo, tbo;
    
    //GLenum mode;//glDrawArrays
    //GLenum usage;//glBufferData

    GLuint shader, texture;
    GLint attribute;
    float size;

    mat4 matrix;

    GLsizei count;
    GLushort element[36];
    GLint normal[108];
    GLfloat texture_uv[72];
    GLfloat vertex[108];
} navCube = { 
.count = 36,
.size = 32.0f,
.texture_uv = {
 0.250f,0.000f, 0.375f,0.000f, 0.375f,0.125f,  0.375f,0.125f, 0.250f,0.125f, 0.250f,0.000f,//Back
 0.375f,0.000f, 0.500f,0.000f, 0.500f,0.125f,  0.500f,0.125f, 0.375f,0.125f, 0.375f,0.000f,//Left
 0.000f,0.000f, 0.125f,0.000f, 0.125f,0.125f,  0.125f,0.125f, 0.000f,0.125f, 0.000f,0.000f,//Front
 0.125f,0.000f, 0.250f,0.000f, 0.250f,0.125f,  0.250f,0.125f, 0.125f,0.125f, 0.125f,0.000f,//Right
 0.625f,0.125f, 0.500f,0.125f, 0.500f,0.000f,  0.500f,0.000f, 0.625f,0.000f, 0.625f,0.125f,//Top 
 0.750f,0.125f, 0.625f,0.125f, 0.625f,0.000f,  0.625f,0.000f, 0.750f,0.000f, 0.750f,0.125f,//Bottom
    },
.vertex =   {
 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f,-1.0f, 1.0f,  -1.0f,-1.0f, 1.0f,  1.0f,-1.0f, 1.0f,  1.0f, 1.0f, 1.0f,
 1.0f, 1.0f,-1.0f,  1.0f, 1.0f, 1.0f,  1.0f,-1.0f, 1.0f,   1.0f,-1.0f, 1.0f,  1.0f,-1.0f,-1.0f,  1.0f, 1.0f,-1.0f,
-1.0f, 1.0f,-1.0f,  1.0f, 1.0f,-1.0f,  1.0f,-1.0f,-1.0f,   1.0f,-1.0f,-1.0f, -1.0f,-1.0f,-1.0f, -1.0f, 1.0f,-1.0f,
-1.0f, 1.0f, 1.0f, -1.0f, 1.0f,-1.0f, -1.0f,-1.0f,-1.0f,  -1.0f,-1.0f,-1.0f, -1.0f,-1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
 1.0f, 1.0f,-1.0f, -1.0f, 1.0f,-1.0f, -1.0f, 1.0f, 1.0f,  -1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,-1.0f,
 1.0f,-1.0f, 1.0f, -1.0f,-1.0f, 1.0f, -1.0f,-1.0f,-1.0f,  -1.0f,-1.0f,-1.0f,  1.0f,-1.0f,-1.0f,  1.0f,-1.0f, 1.0f
    }
};

void UI_init(void){


    navCube.shader = Shader_loadFromFile("./shader/nav.vert", "./shader/nav.frag");
    glBindFragDataLocation(navCube.shader, 0, "color");
    
    glGenVertexArrays(1, &navCube.vao);
    glBindVertexArray(navCube.vao);

    glGenBuffers(1, &navCube.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, navCube.vbo);
    glBufferData(GL_ARRAY_BUFFER, 108*sizeof(GLfloat), navCube.vertex, GL_STATIC_DRAW);

    glGenBuffers(1, &navCube.tbo);
    glBindBuffer(GL_ARRAY_BUFFER, navCube.tbo);
    glBufferData(GL_ARRAY_BUFFER, 72 * sizeof(GLfloat), navCube.texture_uv, GL_STATIC_DRAW);
    
    /*
    glGenBuffers(1, &navCube.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, navCube.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, navCube.count * sizeof(GLushort),//sizeof(navCube->element)
                 navCube.element, GL_STATIC_DRAW);
    */

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &navCube.texture);
    glBindTexture(GL_TEXTURE_2D, navCube.texture);

    int w,h,n;
    GLubyte *data = stbi_load("./data/theme_default.png", &w, &h, &n, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    //FIXME: check if image is loaded correctly
    
    //glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

    glBindVertexArray(navCube.vao);
    glUseProgram(navCube.shader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, navCube.texture);
    glUniform1i(glGetUniformLocation(navCube.shader, "texs"), 0);


    GLint Attrib = 0;//glGetAttribLocation(navCube->shader, "position");// as defined in the shader
    glEnableVertexAttribArray(Attrib);
    glBindBuffer(GL_ARRAY_BUFFER, navCube.vbo);
    glVertexAttribPointer(Attrib, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    Attrib = 1;//glGetAttribLocation(navCube.shader,"vert_uv"));
    glEnableVertexAttribArray(Attrib);
    glBindBuffer(GL_ARRAY_BUFFER, navCube.tbo);
    glVertexAttribPointer(Attrib, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    draw_init();

}


void UI_frame(void) {
    /*mat4_lookAt(Camera.view,(vec3){
        Camera.zoom * sin(Camera.rot[0]) * cos(Camera.rot[1]),
        Camera.zoom * sin(Camera.rot[0]) * sin(Camera.rot[1]),
        Camera.zoom * cos(Camera.rot[0])
    },(vec3){0.f,0.f,0.f},(vec3){0.f,1.f,0.f});*/
    mat4_identity(Camera.view);
    mat4_rotateXY(Camera.view, Camera.rot[0],Camera.rot[1]);

    mat4_multiply(Camera.matrix,  Camera.view, Camera.projection);
    
    //mat4_copy(navCube.matrix, mat4_newScale1f(navCube.size));
    mat4_multiply(navCube.matrix, Camera.view, Camera.projection);
    mat4_scale1f(navCube.matrix, navCube.size);
    mat4_mul(navCube.matrix, mat4_newTranslate3f(1.0f-4*navCube.size/UI.width,1.0f-4*navCube.size/UI.height,0.f));

    

    glBindVertexArray(navCube.vao);
    //glBindBuffer(GL_ARRAY_BUFFER, navCube.vbo);
    glUseProgram(navCube.shader);
    glUniformMatrix4fv(0, 1, GL_FALSE, navCube.matrix); //glGetUniformLocation(navCube.shader, "model")
    glDrawArrays(GL_TRIANGLES, 0, navCube.count); //glDrawElements(GL_TRIANGLES, navCube.count, GL_UNSIGNED_SHORT, NULL);
    

    draw_origin();
}

void UI_refresh(int width, int height) {
//unused

}