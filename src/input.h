/* input.h */
#ifndef INPUT_H
#define INPUT_H

void IN_frame(void);
void IN_onMouseMove(GLFWwindow* window, double xpos, double ypos);
void IN_onMouseClick(GLFWwindow* window, int button, int action, int mods);
void IN_onMouseScroll(GLFWwindow* window, double xoffset, double yoffset);

struct mouse_s {
	double x, y;
	double x0, y0;
	//vec2 delta;
	enum {MOUSE_NONE=0, MOUSE_CLICK, MOUSE_WAS_CLICKED, MOUSE_DOUBLECLICK, MOUSE_DRAG, MOUSE_RELEASE} state;
	//enum {MB_NONE=0, MB_LEFT, MB_RIGHT, MB_SCROLL, MB_BACK, MB_FORWARD} button; 
};
extern struct mouse_s Mouse;



#endif
