#include <stdio.h>
#include <stdbool.h>

#define RGFW_WEBGPU
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <webgpu/webgpu.h>

//--------------------------------------------------
// defines
//--------------------------------------------------
#define SHADER_SOURCE(...) #__VA_ARGS__

//--------------------------------------------------
// structs
//--------------------------------------------------

// global state
typedef struct state_t {
    struct {
        WGPUSwapChain swapchain;
        WGPURenderPipeline pipeline;
    } wgpu;

    // resources
    struct {
        WGPUBuffer vbuffer, ibuffer, ubuffer;
        WGPUBindGroup bindgroup;
    } res;

    // vars
    struct {
        float rot;
    } var;
} state_t;

// state
static state_t state;

//--------------------------------------------------
// callbacks and functions
//--------------------------------------------------

// callbacks
static void draw();

// helper functions
static WGPUSwapChain    create_swapchain();
static WGPUShaderModule create_shader(const char* code, const char* label);
static WGPUBuffer       create_buffer(const void* data, size_t size, WGPUBufferUsage usage);

//--------------------------------------------------
// vertex and fragment shaders
//--------------------------------------------------

// triangle shader
static const char* wgsl_triangle = SHADER_SOURCE(
    // attribute/uniform decls

    struct VertexIn {
        @location(0) aPos : vec2<f32>,
        @location(1) aCol : vec3<f32>,
    };
    struct VertexOut {
        @location(0) vCol : vec3<f32>,
        @builtin(position) Position : vec4<f32>,
    };
    struct Rotation {
        @location(0) degs : f32,
    };
    @group(0) @binding(0) var<uniform> uRot : Rotation;

    // vertex shader

    @vertex
    fn vs_main(input : VertexIn) -> VertexOut {
        var rads : f32 = radians(uRot.degs);
        var cosA : f32 = cos(rads);
        var sinA : f32 = sin(rads);
        var rot : mat3x3<f32> = mat3x3<f32>(
            vec3<f32>( cosA, sinA, 0.0),
            vec3<f32>(-sinA, cosA, 0.0),
            vec3<f32>( 0.0,  0.0,  1.0));
        var output : VertexOut;
        output.Position = vec4<f32>(rot * vec3<f32>(input.aPos, 1.0), 1.0);
        output.vCol = input.aCol;
        return output;
    }

    // fragment shader

    @fragment
    fn fs_main(@location(0) vCol : vec3<f32>) -> @location(0) vec4<f32> {
        return vec4<f32>(vCol, 1.0);
    }
);


//--------------------------------------------------
//
// main
//
//--------------------------------------------------

RGFW_window* win;

int main(int argc, const char* argv[]) {
	win = RGFW_createWindow("RGFW webGPU", RGFW_RECT(0, 0, 200, 200), 0);
    //-----------------
    // init
    //-----------------
	if (state.wgpu.swapchain) {
		wgpuSwapChainRelease(state.wgpu.swapchain);
		state.wgpu.swapchain = NULL;
	}

	state.wgpu.swapchain = create_swapchain();

    //-----------------
    // setup pipeline
    //-----------------

    // compile shaders
    WGPUShaderModule shader_triangle = create_shader(wgsl_triangle, NULL);

    // describe buffer layouts
    WGPUVertexAttribute vertex_attributes[2] = {
        // position: x, y
        [0] = {
            .format = WGPUVertexFormat_Float32x2,
            .offset = 0,
            .shaderLocation = 0,
        },
        // color: r, g, b
        [1] = {
            .format = WGPUVertexFormat_Float32x3,
            .offset = 2 * sizeof(float),
            .shaderLocation = 1,
        }
    };
    WGPUVertexBufferLayout vertex_buffer_layout = {
        .arrayStride = 5 * sizeof(float),
        .attributeCount = 2,
        .attributes = vertex_attributes,
    };

    // describe pipeline layout
    WGPUBindGroupLayout bindgroup_layout = wgpuDeviceCreateBindGroupLayout(win->src.device, &(WGPUBindGroupLayoutDescriptor){
        .entryCount = 1,
        // bind group layout entry
        .entries = &(WGPUBindGroupLayoutEntry){
            .binding = 0,
            .visibility = WGPUShaderStage_Vertex,
            // buffer binding layout
            .buffer = {
                .type = WGPUBufferBindingType_Uniform,
            }
        },
    });
    WGPUPipelineLayout pipeline_layout = wgpuDeviceCreatePipelineLayout(win->src.device, &(WGPUPipelineLayoutDescriptor){
        .bindGroupLayoutCount = 1,
        .bindGroupLayouts = &bindgroup_layout,
    });

    // create pipeline
    state.wgpu.pipeline = wgpuDeviceCreateRenderPipeline(win->src.device, &(WGPURenderPipelineDescriptor){
        // pipeline layout
        .layout = pipeline_layout,
        // vertex state
        .vertex = {
            .module = shader_triangle,
            .entryPoint = "vs_main",
            .bufferCount = 1,
            .buffers = &vertex_buffer_layout,
        },
        // primitive state
        .primitive = {
            .frontFace = WGPUFrontFace_CCW,
            .cullMode = WGPUCullMode_None,
            .topology = WGPUPrimitiveTopology_TriangleList,
            .stripIndexFormat = WGPUIndexFormat_Undefined,
        },
        // fragment state
        .fragment = &(WGPUFragmentState){
            .module = shader_triangle,
            .entryPoint = "fs_main",
            .targetCount = 1,
            // color target state
            .targets = &(WGPUColorTargetState){
                .format = WGPUTextureFormat_BGRA8Unorm,
                .writeMask = WGPUColorWriteMask_All,
                // blend state
                .blend = &(WGPUBlendState){
                    .color = {
                        .operation = WGPUBlendOperation_Add,
                        .srcFactor = WGPUBlendFactor_One,
                        .dstFactor = WGPUBlendFactor_One,
                    },
                    .alpha = {
                        .operation = WGPUBlendOperation_Add,
                        .srcFactor = WGPUBlendFactor_One,
                        .dstFactor = WGPUBlendFactor_One,
                    },
                },
            },
        },
        // multi-sampling state
        .multisample = {
            .count = 1,
            .mask = 0xFFFFFFFF,
            .alphaToCoverageEnabled = false,
        },
        // depth-stencil state
        .depthStencil = NULL,

    });

    wgpuBindGroupLayoutRelease(bindgroup_layout);
    wgpuPipelineLayoutRelease(pipeline_layout);
    wgpuShaderModuleRelease(shader_triangle);

    //-----------------
    // setup
    //-----------------

    // create the vertex buffer (x, y, r, g, b) and index buffer
    float const vertex_data[] = {
        // x, y          // r, g, b
       -0.5f, -0.5f,     1.0f, 0.0f, 0.0f, // bottom-left
        0.5f, -0.5f,     0.0f, 1.0f, 0.0f, // bottom-right
        0.5f,  0.5f,     0.0f, 0.0f, 1.0f, // top-right
       -0.5f,  0.5f,     1.0f, 1.0f, 0.0f, // top-left
    };
    uint16_t index_data[] = {
        0, 1, 2,
        0, 2, 3,
    };
    state.res.vbuffer = create_buffer(vertex_data, sizeof(vertex_data), WGPUBufferUsage_Vertex);
    state.res.ibuffer = create_buffer(index_data, sizeof(index_data), WGPUBufferUsage_Index);

    // create the uniform bind group
    state.res.ubuffer = create_buffer(&state.var.rot, sizeof(state.var.rot), WGPUBufferUsage_Uniform);
    state.res.bindgroup = wgpuDeviceCreateBindGroup(win->src.device, &(WGPUBindGroupDescriptor){
        .layout = wgpuRenderPipelineGetBindGroupLayout(state.wgpu.pipeline, 0),
        .entryCount = 1,
        // bind group entry
        .entries = &(WGPUBindGroupEntry){
            .binding = 0,
            .offset = 0,
            .buffer = state.res.ubuffer,
            .size = sizeof(state.var.rot),
        },
    });

    //-----------------
    // main loop
    //-----------------

	while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        RGFW_event event;
        while (RGFW_window_checkEvent(win, &event)) {
			if (event.type == RGFW_windowResized) {
				if (state.wgpu.swapchain) {
					wgpuSwapChainRelease(state.wgpu.swapchain);
					state.wgpu.swapchain = NULL;
				}

				state.wgpu.swapchain = create_swapchain();
			}
		}
		draw();
	}

    //-----------------
    // quit
    //-----------------

    wgpuRenderPipelineRelease(state.wgpu.pipeline);
    wgpuSwapChainRelease(state.wgpu.swapchain);
    wgpuQueueRelease(win->src.queue);
    wgpuDeviceRelease(win->src.device);
    wgpuInstanceRelease(win->src.wgpuCtx);

	RGFW_window_close(win);

    return 0;
}

// draw callback
void draw() {
    // update rotation
    state.var.rot += 0.1f;
    state.var.rot = state.var.rot >= 360.f ? 0.0f : state.var.rot;
    wgpuQueueWriteBuffer(win->src.queue, state.res.ubuffer, 0, &state.var.rot, sizeof(state.var.rot));

    // create texture view
    WGPUTextureView back_buffer = wgpuSwapChainGetCurrentTextureView(state.wgpu.swapchain);

    // create command encoder
    WGPUCommandEncoder cmd_encoder = wgpuDeviceCreateCommandEncoder(win->src.device, NULL);

    // begin render pass
    WGPURenderPassEncoder render_pass = wgpuCommandEncoderBeginRenderPass(cmd_encoder, &(WGPURenderPassDescriptor){
        // color attachments
        .colorAttachmentCount = 1,
        .colorAttachments = &(WGPURenderPassColorAttachment){
            .view = back_buffer,
            .loadOp = WGPULoadOp_Clear,
            .storeOp = WGPUStoreOp_Store,
            .clearValue = (WGPUColor){ 0.2f, 0.2f, 0.3f, 1.0f },
            .depthSlice = WGPU_DEPTH_SLICE_UNDEFINED
        },
    });

    // draw quad (comment these five lines to simply clear the screen)
    wgpuRenderPassEncoderSetPipeline(render_pass, state.wgpu.pipeline);
    wgpuRenderPassEncoderSetBindGroup(render_pass, 0, state.res.bindgroup, 0, 0);
    wgpuRenderPassEncoderSetVertexBuffer(render_pass, 0, state.res.vbuffer, 0, WGPU_WHOLE_SIZE);
    wgpuRenderPassEncoderSetIndexBuffer(render_pass, state.res.ibuffer, WGPUIndexFormat_Uint16, 0, WGPU_WHOLE_SIZE);
    wgpuRenderPassEncoderDrawIndexed(render_pass, 6, 1, 0, 0, 0);

    // end render pass
    wgpuRenderPassEncoderEnd(render_pass);

    // create command buffer
    WGPUCommandBuffer cmd_buffer = wgpuCommandEncoderFinish(cmd_encoder, NULL); // after 'end render pass'

    // submit commands
    wgpuQueueSubmit(win->src.queue, 1, &cmd_buffer);

    // release all
    wgpuRenderPassEncoderRelease(render_pass);
    wgpuCommandEncoderRelease(cmd_encoder);
    wgpuCommandBufferRelease(cmd_buffer);
    wgpuTextureViewRelease(back_buffer);
}

// helper functions
WGPUSwapChain create_swapchain() {
    WGPUSurface surface = wgpuInstanceCreateSurface(win->src.wgpuCtx, &(WGPUSurfaceDescriptor){
        .nextInChain = (WGPUChainedStruct*)(&(WGPUSurfaceDescriptorFromCanvasHTMLSelector){
            .chain.sType = WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector,
            .selector = "canvas",
        })
    });

    return wgpuDeviceCreateSwapChain(win->src.device, surface, &(WGPUSwapChainDescriptor){
        .usage = WGPUTextureUsage_RenderAttachment,
        .format = WGPUTextureFormat_BGRA8Unorm,
        .width = win->r.w,
        .height = win->r.h,
        .presentMode = WGPUPresentMode_Fifo,
    });
}

WGPUShaderModule create_shader(const char* code, const char* label) {
    WGPUShaderModuleWGSLDescriptor wgsl = {
        .chain.sType = WGPUSType_ShaderModuleWGSLDescriptor,
        .code = code,
    };

    return wgpuDeviceCreateShaderModule(win->src.device, &(WGPUShaderModuleDescriptor){
        .nextInChain = (WGPUChainedStruct*)(&wgsl),
        .label = label,
    });
}

WGPUBuffer create_buffer(const void* data, size_t size, WGPUBufferUsage usage) {
    WGPUBuffer buffer = wgpuDeviceCreateBuffer(win->src.device, &(WGPUBufferDescriptor){
        .usage = WGPUBufferUsage_CopyDst | usage,
        .size = size,
    });
    wgpuQueueWriteBuffer(win->src.queue, buffer, 0, data, size);
    return buffer;
}
