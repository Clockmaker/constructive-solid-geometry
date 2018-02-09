#include "define.h"
#include "common.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define MATRIX_H_SOURCE
#include "matrix.h"
#include "render.h"
#include "ui.h"


void R_init(void){
    glClearColor( 0.16, 0.16, 0.16, 1.0 );
    R_setScreen(640,640);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

void R_setScreen(int w, int h){
    //FIXME: quick hack (GLFW window minimized state = 0,0)
    if(h < 100 || w < 100) return;
    UI.width = w;
    UI.height = h;
    UI.aspect = w>h
              ? w/h
              : h/w;
    mat4_copy(Camera.projection, mat4_newOrtho(-UI.width/2, UI.width/2, UI.height/2, -UI.height/2, -500.f, 500.f) );
    //MAT4_LOG(Camera.projection);
    glViewport(0, 0, w, h);
}


void R_frame(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void R_resize(GLFWwindow* window, int width, int height){
    R_setScreen(width, height);
}