#include "def.h"
#include "common.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render.h"
#include "shader.h"

GLuint shader_nav=0;

void R_Init(void){
    glClearColor( 0.16, 0.16, 0.16, 1.0 );
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);
    //glEnable(GL_CULL_FACE);
    glViewport(0, 0, 640, 640);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    shader_nav = Shader_load( "./shader/nav.vert", "./shader/nav.frag" );
    glBindFragDataLocation(shader_nav, 0, "FragColor");
    glUseProgram(shader_nav);
    //D_LOG("shader %i\n", shader_nav);

}

void R_Frame(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

