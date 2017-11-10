#include "render.h"

void R_Init(void){
	glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glClearColor( 0, 0, 0, 0 );

    glViewport(0, 0, 640, 640);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

}

void R_Frame(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}