#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "GulgEngine/GulgEngine.hpp"

bool initOpenGL(GLFWwindow **window) {

    glfwInit();

        // Open a window and create its OpenGL context
    *window = glfwCreateWindow(1200, 800, "Gulg engine", NULL, NULL);

    if(*window == nullptr){

        std::cout << "ERROR: Can't create a window, glfw error." << std::endl;
        const char* errorMessage;
        int code = glfwGetError(&errorMessage);
        std::cout << "GLFW error " << code << ": " << errorMessage << std::endl;
        return false;
    }

    glfwMakeContextCurrent(*window);

    // Initialize GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cout << "Can't initialize GLEW." << std::endl;
        glfwTerminate();
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

int main() {


    // OpenGL init
    GLFWwindow* window;

    if(!initOpenGL(&window)) {

        glfwTerminate();
        return -1;
    }



    // Gulg init
    Gg::GulgEngine engine;


    // Main loop

    bool haveToStop{false};
   
    while (!haveToStop) {

        // Input
        glfwPollEvents();
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { haveToStop = true; }


        // Update
       


        // Draw

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.15f, 0.75f, 0.95f, 1.0f);


        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
