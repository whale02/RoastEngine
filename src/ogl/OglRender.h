#include "OpenGL/gl.h"

#ifndef ROASTENGINE_OGLRENDERER_H
#define ROASTENGINE_OGLRENDERER_H


class OglRender {

public:
    void setupAdapter();

    void initWindow(const char *wName, int wWidth, int wHeight);

    GLFWwindow *GetGlfwWindow();

    GLFWwindow *glfwWindow;

    void setupAdapter(const char *wName, int wWidth, int wHeight);
};

#endif //ROASTENGINE_OGLRENDERER_H