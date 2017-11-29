/* input.h */
#ifndef INPUT_H
#define INPUT_H

void IN_onMouseMove(GLFWwindow* window, double xpos, double ypos);
void IN_onMouseClick(GLFWwindow* window, int button, int action, int mods);
void IN_onMouseScroll(GLFWwindow* window, double xoffset, double yoffset);

struct {
	double x;
	double y;
	double x0;
	double y0;
	enum {LEFT=0, RIGHT, SCROLL, BACK, FORWARD} button; 
	enum {RELEASE=0, CLICK, DRAG} state;
} Mouse;


#endif
