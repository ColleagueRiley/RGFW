#include <stdio.h>
#include <stdlib.h>

#define RGFW_ALLOC_DROPFILES
#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
#define RGFW_VULKAN
#include <RGFW.h>

/**
 * ```bash
 * glslangValidator -V triangle.vert -o vert.glsl.h --vn vert_code
 * ```
 */

#include <stdint.h>
#include <vulkan/vulkan.h>

const uint32_t vert_code[] = {
	0x07230203,0x00010000,0x0008000b,0x00000036,0x00000000,0x00020011,0x00000001,0x0006000b,
	0x00000001,0x4c534c47,0x6474732e,0x3035342e,0x00000000,0x0003000e,0x00000000,0x00000001,
	0x0008000f,0x00000000,0x00000004,0x6e69616d,0x00000000,0x00000022,0x00000026,0x00000031,
	0x00030003,0x00000002,0x000001c2,0x00090004,0x415f4c47,0x735f4252,0x72617065,0x5f657461,
	0x64616873,0x6f5f7265,0x63656a62,0x00007374,0x00040005,0x00000004,0x6e69616d,0x00000000,
	0x00050005,0x0000000c,0x69736f70,0x6e6f6974,0x00000073,0x00040005,0x00000017,0x6f6c6f63,
	0x00007372,0x00060005,0x00000020,0x505f6c67,0x65567265,0x78657472,0x00000000,0x00060006,
	0x00000020,0x00000000,0x505f6c67,0x7469736f,0x006e6f69,0x00070006,0x00000020,0x00000001,
	0x505f6c67,0x746e696f,0x657a6953,0x00000000,0x00070006,0x00000020,0x00000002,0x435f6c67,
	0x4470696c,0x61747369,0x0065636e,0x00070006,0x00000020,0x00000003,0x435f6c67,0x446c6c75,
	0x61747369,0x0065636e,0x00030005,0x00000022,0x00000000,0x00060005,0x00000026,0x565f6c67,
	0x65747265,0x646e4978,0x00007865,0x00050005,0x00000031,0x67617266,0x6f6c6f43,0x00000072,
	0x00050048,0x00000020,0x00000000,0x0000000b,0x00000000,0x00050048,0x00000020,0x00000001,
	0x0000000b,0x00000001,0x00050048,0x00000020,0x00000002,0x0000000b,0x00000003,0x00050048,
	0x00000020,0x00000003,0x0000000b,0x00000004,0x00030047,0x00000020,0x00000002,0x00040047,
	0x00000026,0x0000000b,0x0000002a,0x00040047,0x00000031,0x0000001e,0x00000000,0x00020013,
	0x00000002,0x00030021,0x00000003,0x00000002,0x00030016,0x00000006,0x00000020,0x00040017,
	0x00000007,0x00000006,0x00000002,0x00040015,0x00000008,0x00000020,0x00000000,0x0004002b,
	0x00000008,0x00000009,0x00000003,0x0004001c,0x0000000a,0x00000007,0x00000009,0x00040020,
	0x0000000b,0x00000006,0x0000000a,0x0004003b,0x0000000b,0x0000000c,0x00000006,0x0004002b,
	0x00000006,0x0000000d,0x00000000,0x0004002b,0x00000006,0x0000000e,0xbf000000,0x0005002c,
	0x00000007,0x0000000f,0x0000000d,0x0000000e,0x0004002b,0x00000006,0x00000010,0x3f000000,
	0x0005002c,0x00000007,0x00000011,0x00000010,0x00000010,0x0005002c,0x00000007,0x00000012,
	0x0000000e,0x00000010,0x0006002c,0x0000000a,0x00000013,0x0000000f,0x00000011,0x00000012,
	0x00040017,0x00000014,0x00000006,0x00000003,0x0004001c,0x00000015,0x00000014,0x00000009,
	0x00040020,0x00000016,0x00000006,0x00000015,0x0004003b,0x00000016,0x00000017,0x00000006,
	0x0004002b,0x00000006,0x00000018,0x3f800000,0x0006002c,0x00000014,0x00000019,0x00000018,
	0x0000000d,0x0000000d,0x0006002c,0x00000014,0x0000001a,0x0000000d,0x00000018,0x0000000d,
	0x0006002c,0x00000014,0x0000001b,0x0000000d,0x0000000d,0x00000018,0x0006002c,0x00000015,
	0x0000001c,0x00000019,0x0000001a,0x0000001b,0x00040017,0x0000001d,0x00000006,0x00000004,
	0x0004002b,0x00000008,0x0000001e,0x00000001,0x0004001c,0x0000001f,0x00000006,0x0000001e,
	0x0006001e,0x00000020,0x0000001d,0x00000006,0x0000001f,0x0000001f,0x00040020,0x00000021,
	0x00000003,0x00000020,0x0004003b,0x00000021,0x00000022,0x00000003,0x00040015,0x00000023,
	0x00000020,0x00000001,0x0004002b,0x00000023,0x00000024,0x00000000,0x00040020,0x00000025,
	0x00000001,0x00000023,0x0004003b,0x00000025,0x00000026,0x00000001,0x00040020,0x00000028,
	0x00000006,0x00000007,0x00040020,0x0000002e,0x00000003,0x0000001d,0x00040020,0x00000030,
	0x00000003,0x00000014,0x0004003b,0x00000030,0x00000031,0x00000003,0x00040020,0x00000033,
	0x00000006,0x00000014,0x00050036,0x00000002,0x00000004,0x00000000,0x00000003,0x000200f8,
	0x00000005,0x0003003e,0x0000000c,0x00000013,0x0003003e,0x00000017,0x0000001c,0x0004003d,
	0x00000023,0x00000027,0x00000026,0x00050041,0x00000028,0x00000029,0x0000000c,0x00000027,
	0x0004003d,0x00000007,0x0000002a,0x00000029,0x00050051,0x00000006,0x0000002b,0x0000002a,
	0x00000000,0x00050051,0x00000006,0x0000002c,0x0000002a,0x00000001,0x00070050,0x0000001d,
	0x0000002d,0x0000002b,0x0000002c,0x0000000d,0x00000018,0x00050041,0x0000002e,0x0000002f,
	0x00000022,0x00000024,0x0003003e,0x0000002f,0x0000002d,0x0004003d,0x00000023,0x00000032,
	0x00000026,0x00050041,0x00000033,0x00000034,0x00000017,0x00000032,0x0004003d,0x00000014,
	0x00000035,0x00000034,0x0003003e,0x00000031,0x00000035,0x000100fd,0x00010038
};

/**
 * ```bash
 * glslangValidator -V triangle.frag -o frag.glsl.h --vn frag_code
 * ```
 */
const uint32_t frag_code[] = {
    0x07230203,0x00010000,0x0008000b,0x00000013,0x00000000,0x00020011,0x00000001,0x0006000b,
    0x00000001,0x4c534c47,0x6474732e,0x3035342e,0x00000000,0x0003000e,0x00000000,0x00000001,
    0x0007000f,0x00000004,0x00000004,0x6e69616d,0x00000000,0x00000009,0x0000000c,0x00030010,
    0x00000004,0x00000007,0x00030003,0x00000002,0x000001c2,0x00090004,0x415f4c47,0x735f4252,
    0x72617065,0x5f657461,0x64616873,0x6f5f7265,0x63656a62,0x00007374,0x00040005,0x00000004,
    0x6e69616d,0x00000000,0x00050005,0x00000009,0x4374756f,0x726f6c6f,0x00000000,0x00050005,
    0x0000000c,0x67617266,0x6f6c6f43,0x00000072,0x00040047,0x00000009,0x0000001e,0x00000000,
    0x00040047,0x0000000c,0x0000001e,0x00000000,0x00020013,0x00000002,0x00030021,0x00000003,
    0x00000002,0x00030016,0x00000006,0x00000020,0x00040017,0x00000007,0x00000006,0x00000004,
    0x00040020,0x00000008,0x00000003,0x00000007,0x0004003b,0x00000008,0x00000009,0x00000003,
    0x00040017,0x0000000a,0x00000006,0x00000003,0x00040020,0x0000000b,0x00000001,0x0000000a,
    0x0004003b,0x0000000b,0x0000000c,0x00000001,0x0004002b,0x00000006,0x0000000e,0x3f800000,
    0x00050036,0x00000002,0x00000004,0x00000000,0x00000003,0x000200f8,0x00000005,0x0004003d,
    0x0000000a,0x0000000d,0x0000000c,0x00050051,0x00000006,0x0000000f,0x0000000d,0x00000000,
    0x00050051,0x00000006,0x00000010,0x0000000d,0x00000001,0x00050051,0x00000006,0x00000011,
    0x0000000d,0x00000002,0x00070050,0x00000007,0x00000012,0x0000000f,0x00000010,0x00000011,
    0x0000000e,0x0003003e,0x00000009,0x00000012,0x000100fd,0x00010038
};

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int draw_frame(RGFW_window* win) {
    vkWaitForFences(RGFW_vulkan_info.device, 1, &RGFW_vulkan_info.in_flight_fences[RGFW_vulkan_info.current_frame], VK_TRUE, UINT64_MAX);

    uint32_t image_index = 0;
    VkResult result = vkAcquireNextImageKHR(RGFW_vulkan_info.device, win->swapchain, UINT64_MAX, RGFW_vulkan_info.available_semaphores[RGFW_vulkan_info.current_frame], VK_NULL_HANDLE, &image_index);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        return RGFW_recreate_swapchain(win);
    } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        printf("failed to acquire swapchain image. Error %i\n", result);
        return -1;
    }

    if (RGFW_vulkan_info.image_in_flight[image_index] != VK_NULL_HANDLE) {
        vkWaitForFences(RGFW_vulkan_info.device, 1, &RGFW_vulkan_info.image_in_flight[image_index], VK_TRUE, UINT64_MAX);
    }
    RGFW_vulkan_info.image_in_flight[image_index] = RGFW_vulkan_info.in_flight_fences[RGFW_vulkan_info.current_frame];

    VkSubmitInfo submitInfo = {0};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore wait_semaphores[] = { RGFW_vulkan_info.available_semaphores[RGFW_vulkan_info.current_frame] };
    VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = wait_semaphores;
    submitInfo.pWaitDstStageMask = wait_stages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &RGFW_vulkan_info.command_buffers[image_index];

    VkSemaphore signal_semaphores[] = { RGFW_vulkan_info.finished_semaphore[RGFW_vulkan_info.current_frame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signal_semaphores;

    vkResetFences(RGFW_vulkan_info.device, 1, &RGFW_vulkan_info.in_flight_fences[RGFW_vulkan_info.current_frame]);

    if (vkQueueSubmit(RGFW_vulkan_info.graphics_queue, 1, &submitInfo, RGFW_vulkan_info.in_flight_fences[RGFW_vulkan_info.current_frame]) != VK_SUCCESS) {
        printf("failed to submit draw command buffer\n");
        return -1; //"failed to submit draw command buffer
    }

    VkPresentInfoKHR present_info = {0};
    present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    present_info.waitSemaphoreCount = 1;
    present_info.pWaitSemaphores = signal_semaphores;

    VkSwapchainKHR swapChains[] = { win->swapchain };
    present_info.swapchainCount = 1;
    present_info.pSwapchains = swapChains;

    present_info.pImageIndices = &image_index;

    result = vkQueuePresentKHR(RGFW_vulkan_info.present_queue, &present_info);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
        return RGFW_recreate_swapchain(win);
    } else if (result != VK_SUCCESS) {
        printf("failed to present swapchain image\n");
        return -1;
    }

    RGFW_vulkan_info.current_frame = (RGFW_vulkan_info.current_frame + 1) % RGFW_MAX_FRAMES_IN_FLIGHT;
    return 0;
}

int createGraphicsPipeline(RGFW_window* win) {
    size_t vert_fileSize = sizeof(vert_code);
    size_t frag_fileSize = sizeof(frag_code);

    VkShaderModule vert_module = RGFW_createShaderModule(vert_code, vert_fileSize);
    VkShaderModule frag_module = RGFW_createShaderModule(frag_code, frag_fileSize);
    if (vert_module == VK_NULL_HANDLE || frag_module == VK_NULL_HANDLE) {
        printf("failed to create shader module\n");
        return -1; // failed to create shader modules
    }

    VkPipelineShaderStageCreateInfo vert_stage_info = {0};
    vert_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vert_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vert_stage_info.module = vert_module;
    vert_stage_info.pName = "main";

    VkPipelineShaderStageCreateInfo frag_stage_info = {0};
    frag_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    frag_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    frag_stage_info.module = frag_module;
    frag_stage_info.pName = "main";

    VkPipelineShaderStageCreateInfo shader_stages[] = { vert_stage_info, frag_stage_info };

    VkPipelineVertexInputStateCreateInfo vertex_input_info = {0};
    vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_input_info.vertexBindingDescriptionCount = 0;
    vertex_input_info.vertexAttributeDescriptionCount = 0;

    VkPipelineInputAssemblyStateCreateInfo input_assembly = {0};
    input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    input_assembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport;
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)win->w;
    viewport.height = (float)win->h;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor;
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent = (VkExtent2D){win->w, win->h};

    VkPipelineViewportStateCreateInfo viewport_state = {0};
    viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.viewportCount = 1;
    viewport_state.pViewports = &viewport;
    viewport_state.scissorCount = 1;
    viewport_state.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer = {0};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo multisampling = {0};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState colorBlendAttachment = {0};
    colorBlendAttachment.colorWriteMask =
        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo color_blending = {0};
    color_blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    color_blending.logicOpEnable = VK_FALSE;
    color_blending.logicOp = VK_LOGIC_OP_COPY;
    color_blending.attachmentCount = 1;
    color_blending.pAttachments = &colorBlendAttachment;
    color_blending.blendConstants[0] = 0.0f;
    color_blending.blendConstants[1] = 0.0f;
    color_blending.blendConstants[2] = 0.0f;
    color_blending.blendConstants[3] = 0.0f;

    VkPipelineLayoutCreateInfo pipeline_layout_info = {0};
    pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layout_info.setLayoutCount = 0;
    pipeline_layout_info.pushConstantRangeCount = 0;

    if (vkCreatePipelineLayout(RGFW_vulkan_info.device, &pipeline_layout_info, NULL, &RGFW_vulkan_info.pipeline_layout) != VK_SUCCESS) {
        printf("failed to create pipeline layout\n");
        return -1; // failed to create pipeline layout
    }

    VkDynamicState dynamic_states[] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

    VkPipelineDynamicStateCreateInfo dynamic_info = {0};
    dynamic_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamic_info.dynamicStateCount = 2;
    dynamic_info.pDynamicStates = dynamic_states;

    VkGraphicsPipelineCreateInfo pipeline_info = {0};
    pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_info.stageCount = 2;
    pipeline_info.pStages = shader_stages;
    pipeline_info.pVertexInputState = &vertex_input_info;
    pipeline_info.pInputAssemblyState = &input_assembly;
    pipeline_info.pViewportState = &viewport_state;
    pipeline_info.pRasterizationState = &rasterizer;
    pipeline_info.pMultisampleState = &multisampling;
    pipeline_info.pColorBlendState = &color_blending;
    pipeline_info.pDynamicState = &dynamic_info;
    pipeline_info.layout = RGFW_vulkan_info.pipeline_layout;
    pipeline_info.renderPass = RGFW_vulkan_info.render_pass;
    pipeline_info.subpass = 0;
    pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

    if (vkCreateGraphicsPipelines(RGFW_vulkan_info.device, VK_NULL_HANDLE, 1, &pipeline_info, NULL, &RGFW_vulkan_info.graphics_pipeline) != VK_SUCCESS) {
        printf("failed to create pipline\n");
        return -1; // failed to create graphics pipeline
    }

    vkDestroyShaderModule(RGFW_vulkan_info.device, frag_module, NULL);
    vkDestroyShaderModule(RGFW_vulkan_info.device, vert_module, NULL);
    return 0;
}

int commandBuffers(RGFW_window* win) {
    for (size_t i = 0; i < win->image_count; i++) {
        VkCommandBufferBeginInfo begin_info = {0};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(RGFW_vulkan_info.command_buffers[i], &begin_info) != VK_SUCCESS) {
            return -1; // failed to begin recording command buffer
        }

        VkRenderPassBeginInfo render_pass_info = {0};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_info.renderPass = RGFW_vulkan_info.render_pass;
        render_pass_info.framebuffer = RGFW_vulkan_info.framebuffers[i];
        render_pass_info.renderArea.offset.x = 0;
        render_pass_info.renderArea.offset.y = 0;
        render_pass_info.renderArea.extent = (VkExtent2D){win->w, win->h};
        VkClearValue clearColor;
        clearColor.color.float32[0] = 1.0f;
        clearColor.color.float32[1] = 1.0f;
        clearColor.color.float32[2] = 1.0f;
        clearColor.color.float32[3] = 1.0f;
        render_pass_info.clearValueCount = 1;
        render_pass_info.pClearValues = &clearColor;

        VkViewport viewport;
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)win->w;
        viewport.height = (float)win->h;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor;
        scissor.offset.x = 0;
        scissor.offset.y = 0;
        scissor.extent = (VkExtent2D){win->w, win->h};

        vkCmdSetViewport(RGFW_vulkan_info.command_buffers[i], 0, 1, &viewport);
        vkCmdSetScissor(RGFW_vulkan_info.command_buffers[i], 0, 1, &scissor);

        vkCmdBeginRenderPass(RGFW_vulkan_info.command_buffers[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(RGFW_vulkan_info.command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, RGFW_vulkan_info.graphics_pipeline);

        vkCmdDraw(RGFW_vulkan_info.command_buffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(RGFW_vulkan_info.command_buffers[i]);

        if (vkEndCommandBuffer(RGFW_vulkan_info.command_buffers[i]) != VK_SUCCESS) {
            printf("failed to record command buffer\n");
            return -1; // failed to record command buffer!
        }
    }
    return 0;
}
 
int main() {
    RGFW_window* win = RGFW_createWindow("Vulkan Example", SCR_WIDTH, SCR_HEIGHT, SCR_WIDTH, SCR_HEIGHT, RGFW_ALLOW_DND | RGFW_CENTER);;
    RGFW_initVulkan(win);   

    createGraphicsPipeline(win);

    uint32_t running = 1;
    while (running && !RGFW_isPressedI(win, RGFW_Escape)) {
        while (RGFW_window_checkEvent(win)) {
            if (win->event.type == RGFW_quit) {
                running = 0;
                break;
            }
        }

        draw_frame(win);
        commandBuffers(win);
    }
    
    vkDeviceWaitIdle(RGFW_vulkan_info.device);
    
    RGFW_freeVulkan();
    RGFW_window_close(win);
    return 0;
}
