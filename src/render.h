#ifndef RENDER_H
#define RENDER_H


void R_init(void);
void R_frame(void);
void R_resize(GLFWwindow* window, int width, int height);
void R_setScreen(int w, int h);

#endif