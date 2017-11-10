#include <GLFW/glfw3.h>
#include "def.h"
#include "render.h"

int main(void) {
    printf("asf asd f");
    GLFWwindow* window;
    if (!glfwInit()) return -1;

    window = glfwCreateWindow(640, 640, "CSG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    R_Init();

    while (!glfwWindowShouldClose(window)) {
       
        R_Frame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
