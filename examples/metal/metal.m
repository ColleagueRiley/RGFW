
// Simple RGFW+Metal example
//
//
// made using a modifed version of the GLFW+metal example
// https://github.com/glfw/glfw/blob/metal-guide/examples/metal.m
//
// Copyright (c) Camilla Berglund <elmindreda@elmindreda.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

/* RGFW will have to be linked/compiled outside of this file
	because this file uses objective-c and RGFW uses work arounds
*/
#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#import "RGFW.h"

#include <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>
#import <simd/simd.h>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

//#include <iostream>

int main(void)
{
	id<MTLDevice> device = MTLCreateSystemDefaultDevice();
	if (!device) {
        printf("failed to create metal device");
		exit(EXIT_FAILURE);
    }

    RGFW_window* window = RGFW_createWindow("RGFW Metal example", 0, 0, 640, 480, RGFW_windowCenter);
    RGFW_window_setExitKey(window, RGFW_escape);

    CAMetalLayer* layer = [CAMetalLayer layer];
    layer.device = device;
    layer.pixelFormat = MTLPixelFormatBGRA8Unorm;

    NSView* view = (NSView*)RGFW_window_getView_OSX(window);
    [view setLayer: layer];
    // [view setWantsLayer: YES]; (I think RGFW already sets this)

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
    assert(rps);

    while (!RGFW_window_shouldClose(window)) {
        RGFW_event event;
		while (RGFW_window_checkEvent(window, &event) != RGFW_FALSE) {
			if (event.type == RGFW_quit)
				break;
		}

        float ratio;

		i32 w, h;
        RGFW_window_getSize(window, &w, &h);
        ratio = w / (float) h;

        layer.drawableSize = CGSizeMake(w, h);
        id<CAMetalDrawable> drawable = [layer nextDrawable];
        assert(drawable);

        id<MTLCommandBuffer> cb = [cq commandBuffer];

        MTLRenderPassDescriptor* rpd = [MTLRenderPassDescriptor new];
        MTLRenderPassColorAttachmentDescriptor* cd = rpd.colorAttachments[0];
        cd.texture = drawable.texture;
        cd.loadAction = MTLLoadActionClear;
        cd.clearColor = MTLClearColorMake(1.0, 1.0, 1.0, 1.0);
        cd.storeAction = MTLStoreActionStore;
        id<MTLRenderCommandEncoder> rce = [cb renderCommandEncoderWithDescriptor:rpd];

        [rce setRenderPipelineState:rps];
        [rce setVertexBytes:(vector_float4[]){
            { 0, 0, 0, 1 },
            { -1, 1, 0, 1 },
            { 1, 1, 0, 1 },
        } length:3 * sizeof(vector_float4) atIndex:0];
        [rce drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:3];

        [rce endEncoding];
        [cb presentDrawable:drawable];
        [cb commit];
    }


    RGFW_window_close(window);
}



