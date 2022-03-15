//
// Created by rwork on 15.03.2022.
//

#ifndef ROASTENGINE_MTLRENDERER_H
#define ROASTENGINE_MTLRENDERER_H
// cc glfw-metal-example.m -lGLFW -framework AppKit -framework Metal -framework QuartzCore
//
#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>



class mtlRenderer {
public:
    static void quit(GLFWwindow *window, int key, int scancode, int action, int mods);
    int run();
};


#endif //ROASTENGINE_MTLRENDERER_H
