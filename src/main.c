#include "def.h"
#include "common.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render.h"

int main(void) {
    GLFWwindow* window;
    if (!glfwInit()) return -1;

    //glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    
    window = glfwCreateWindow(640, 640, "CSG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;

    D_LOG("%s (%s)", glGetString(GL_RENDERER), glGetString(GL_VENDOR));
    D_LOG("OpenGL %s", glGetString(GL_VERSION));
    D_LOG("GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

    R_Init();

    while (!glfwWindowShouldClose(window)) {
       
        R_Frame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
