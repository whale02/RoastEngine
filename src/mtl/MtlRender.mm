#import <stdexcept>
#include "MtlRender.h"
#import "../common/RDDebug.h"


bool MtlRender::initWindow(const char *wTitle, int width, int height) {


    // Initialize System

    glfwSetErrorCallback(RDDebug::glfwErrorCallback);

    if (glfwInit() == GLFW_FALSE) {
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    pGlfwWindow= glfwCreateWindow(width, height, wTitle, NULL, NULL);

    device = MTLCreateSystemDefaultDevice();
    commandQueue = [device newCommandQueue];

    // Init Render options

    nswindow = glfwGetCocoaWindow(pGlfwWindow);
    layer = [CAMetalLayer layer];
    layer.device = device;
    layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    nswindow.contentView.layer = layer;
    nswindow.contentView.wantsLayer = YES;

    MTLCompileOptions* compileOptions = [MTLCompileOptions new];
    compileOptions.languageVersion = MTLLanguageVersion1_1;
    NSError* compileError;
    id<MTLLibrary> lib = [device newLibraryWithSource:
                    @"#include <metal_stdlib>\n"
                    "using namespace metal;\n"
                    "vertex float4 v_simple(\n"
                    "    constant float4* in  [[buffer(0)]],\n"
                    "    uint             vid [[vertex_id]])\n"
                    "{\n"
                    "    return in[vid];\n"
                    "}\n"
                    "fragment float4 f_simple(\n"
                    "    float4 in [[stage_in]])\n"
                    "{\n"
                    "    return float4(1, 0, 0, 1);\n"
                    "}\n"
                                              options:compileOptions error:&compileError];
    if (!lib)
    {
        NSLog(@"can't create library: %@", compileError);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    id<MTLFunction> vs = [lib newFunctionWithName:@"v_simple"];
    assert(vs);
    id<MTLFunction> fs = [lib newFunctionWithName:@"f_simple"];
    assert(fs);
    id<MTLCommandQueue> cq = [device newCommandQueue];
    assert(cq);
    MTLRenderPipelineDescriptor* rpd = [MTLRenderPipelineDescriptor new];
    rpd.vertexFunction = vs;
    rpd.fragmentFunction = fs;
    rpd.colorAttachments[0].pixelFormat = layer.pixelFormat;
    id<MTLRenderPipelineState> rps = [device newRenderPipelineStateWithDescriptor:rpd error:NULL];

    renderPassDescriptor = [MTLRenderPassDescriptor new];

    return true;
}

GLFWwindow *MtlRender::GetGlfwWindow() {
    return pGlfwWindow;
}
