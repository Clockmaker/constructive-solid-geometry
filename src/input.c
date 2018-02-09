#include "define.h"
#include "common.h"
#include <GLFW/glfw3.h>
#include "matrix.h"
#include "input.h"
#include "ui.h"

struct mouse_s Mouse = {.x=0,.y=0};

void IN_onMouseMove(GLFWwindow* window, double xpos, double ypos){
    //D_LOG("%g, %g", xpos, ypos);
    Mouse.x = xpos;
    Mouse.y = ypos;
    
    //FIXME DRAG STATE PER BUTTON
    if(MOUSE_CLICK == Mouse.state){
        Mouse.state = MOUSE_DRAG;
    }
    if(MOUSE_DRAG == Mouse.state){
        Camera.rot[0] = Camera.last.rot[0] + (Mouse.x - Mouse.x0)*RAD;
        Camera.rot[1] = Camera.last.rot[1] + (Mouse.y - Mouse.y0)*RAD;
    }
}

void IN_onMouseClick(GLFWwindow* window, int button, int action, int mods){
    //D_LOG("mouse (%g,%g) click %i %s %i %i %i", Mouse.x, Mouse.y, button, 
    //button==0?"left":button==1?"right":button==2?"scroll":"other"
    //,action, mods, Mouse.state);

    if (1 == action){
        Mouse.state = MOUSE_CLICK;
        //TODO: check if glfwGetCursorPos(window, &xpos, &ypos) is needed
        Mouse.x0 = Mouse.x;
        Mouse.y0 = Mouse.y;
        Camera.last.rot[0] = Camera.rot[0];
        Camera.last.rot[1] = Camera.rot[1];
    } else {
        Mouse.state = MOUSE_RELEASE;
    }
    /*
    switch(action){
        case 1:
            Mouse.state = CLICK;
        break;
        default:
            Mouse.state = RELEASE;
        break;
    }
    */

}
extern float zoom;

void IN_onMouseScroll(GLFWwindow* window, double xoffset, double yoffset){
    Camera.zoom += yoffset * MOUSE_DELTA;
}

void IN_frame(void){

}
