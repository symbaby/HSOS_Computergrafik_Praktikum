#ifdef WIN32

#include <GL/glew.h>
#include <glfw/glfw3.h>

#else
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <glfw/glfw3.h>
#endif

#include <stdio.h>
#include "../include/Application.h"
#include "FreeImage.h"

void PrintOpenGLVersion();


int main() {
    FreeImage_Initialise();
    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

#ifdef __APPLE__
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    const int WindowWidth = 800;
    const int WindowHeight = 600;

    GLFWwindow *window = glfwCreateWindow(WindowWidth, WindowHeight, "Computergrafik - Hochschule Osnabrück", NULL,
                                          NULL);
    if (!window) {
        fprintf(stderr, "ERROR: can not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

#if WIN32
    glewExperimental = GL_TRUE;
    glewInit();
#endif

    PrintOpenGLVersion();

    {
        Application App(window);
        App.start();

        /*INITIALISIEREN VON CURRENTTIME UND LASTTIME*/
        float currentTime = 1;
        float lastTime = glfwGetTime();

        while (!glfwWindowShouldClose(window)) {
            // once per frame
            glfwPollEvents();

            /*BERECHNEN NEU CURRENT*/
            /*BERECHNEN FRAMETIME AUS DIFFERENZ currentTime UND lastTime AUS LETZTEM LOOP*/
            /*LAST TIME FUE NAECHSTE RUNDE SETTEN*/
            currentTime = glfwGetTime();
            float frameTime = currentTime - lastTime;
            lastTime = currentTime;

            /*APPLICATION update() AUFRUF*/
            App.update(frameTime);


            App.draw();
            glfwSwapBuffers(window);
        }
        App.end();
    }

    glfwTerminate();
    return 0;
}


void PrintOpenGLVersion() {
    // get version info
    const GLubyte *renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte *version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
}
