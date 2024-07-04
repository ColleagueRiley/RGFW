#include <stdio.h>
#include <stdlib.h>

#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
#define RGFW_NO_API
#include <RGFW.h>

/* 
    This isn't included in RGFW.h itself because 
    you'd want to define that stuff yourself in most usecases
*/
#define RGFW_VULKAN_IMPLEMENTATION
#include "RGFW_vulkan.h"

/**
 * ```bash
 * glslangValidator -V shader/vert.glsl -o vert.glsl.h --vn vert_code
 * glslangValidator -V shaders/vert.glsl -o vertexShader.spv
 * ```
 */

#include "shaders/vert.h"
#include "shaders/frag.h"

RGFW_vulkanInfo* vulkan_info;

int createGraphicsPipeline(RGFW_window_vulkanInfo* vulkWin);
int commandBuffers(RGFW_window_vulkanInfo* vulkWin);
int draw_frame(RGFW_window_vulkanInfo* vulkWin);


int main(void) {
    RGFW_window* win = RGFW_createWindow("Vulkan Example", RGFW_RECT(0, 0, 500, 500), RGFW_ALLOW_DND | RGFW_CENTER);;
    RGFW_window_vulkanInfo vulkWin;

    vulkan_info = RGFW_initVulkan(win, &vulkWin);    
    createGraphicsPipeline(&vulkWin);

    u8 running = 1;
    while (running && !RGFW_isPressed(win, RGFW_Escape)) {
        while (RGFW_window_checkEvent(win)) {
            if (win->event.type == RGFW_quit) {
                running = 0;
                break;
            }
        }

        draw_frame(&vulkWin);
        commandBuffers(&vulkWin);
    }
    
    RGFW_freeVulkan(&vulkWin);

    RGFW_window_close(win);
    return 0;
}

int createGraphicsPipeline(RGFW_window_vulkanInfo* vulkWin) {    
    VkShaderModule vert_module = RGFW_createShaderModule(vert_code, sizeof(vert_code));
    VkShaderModule frag_module = RGFW_createShaderModule(frag_code, sizeof(frag_code));

    if (vert_module == VK_NULL_HANDLE || frag_module == VK_NULL_HANDLE) {
        printf("failed to create shader module\n");
        return -1; // failed to create shader modules
    }

    VkPipelineShaderStageCreateInfo vert_stage_info = {0};
    vert_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vert_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vert_stage_info.module = vert_module;
    vert_stage_info.pName = "main";

    VkPipelineShaderStageCreateInfo frag_stage_info = vert_stage_info;
    frag_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    frag_stage_info.module = frag_module;

    VkPipelineShaderStageCreateInfo shader_stages[] = { vert_stage_info, frag_stage_info };

    VkPipelineVertexInputStateCreateInfo vertex_input_info = {0};
    vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_input_info.vertexBindingDescriptionCount = 0;
    vertex_input_info.vertexAttributeDescriptionCount = 0;

    VkPipelineInputAssemblyStateCreateInfo input_assembly = {0};
    input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    input_assembly.primitiveRestartEnable = VK_FALSE;

    /*RSGL_point3DF data[] = {
        (RSGL_point3DF){-0.6, -0.75, 0.0f}, 
        (RSGL_point3DF){0.6, -0.75, 0.0f}, 
        (RSGL_point3DF){0, 0.75, 0.0f};
    };

    vkMapMemory(vulkan_info->device, data, 0, 3, 0, &data);
    vkUnmapMemory(vulkan_info->device, DATA_BLOB);
    vkBindBufferMemory(vulkan_info->device, 3, data, 0);
    */

    VkViewport viewport;
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)500;
    viewport.height = (float)500;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor;
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent = (VkExtent2D){500, 500};

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

    if (vkCreatePipelineLayout(vulkan_info->device, &pipeline_layout_info, NULL, &vulkan_info->pipeline_layout) != VK_SUCCESS) {
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
    pipeline_info.layout = vulkan_info->pipeline_layout;
    pipeline_info.renderPass = vulkan_info->render_pass;
    pipeline_info.subpass = 0;
    pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

    if (vkCreateGraphicsPipelines(vulkan_info->device, VK_NULL_HANDLE, 1, &pipeline_info, NULL, &vulkan_info->graphics_pipeline) != VK_SUCCESS) {
        printf("failed to create pipline\n");
        return -1; // failed to create graphics pipeline
    }

    vkDestroyShaderModule(vulkan_info->device, frag_module, NULL);
    vkDestroyShaderModule(vulkan_info->device, vert_module, NULL);
    return 0;
}

int commandBuffers(RGFW_window_vulkanInfo* vulkWin) {
    for (size_t i = 0; i < vulkWin->image_count; i++) {
        /* begin command buffer */
        VkCommandBufferBeginInfo begin_info = {0};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(vulkan_info->command_buffers[i], &begin_info) != VK_SUCCESS) {
            return -1; // failed to begin recording command buffer
        }

        VkRenderPassBeginInfo render_pass_info = {0};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_info.renderPass = vulkan_info->render_pass;
        render_pass_info.framebuffer = vulkan_info->framebuffers[i];
        render_pass_info.renderArea.offset.x = 0;
        render_pass_info.renderArea.offset.y = 0;
        render_pass_info.renderArea.extent = (VkExtent2D){500, 500};
        
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
        viewport.width = (float)500;
        viewport.height = (float)500;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor;
        scissor.offset.x = 0;
        scissor.offset.y = 0;
        scissor.extent = (VkExtent2D){500, 500};

        vkCmdSetViewport(vulkan_info->command_buffers[i], 0, 1, &viewport);
        vkCmdSetScissor(vulkan_info->command_buffers[i], 0, 1, &scissor);

        vkCmdBeginRenderPass(vulkan_info->command_buffers[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(vulkan_info->command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, vulkan_info->graphics_pipeline);

        vkCmdDraw(vulkan_info->command_buffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(vulkan_info->command_buffers[i]);

        if (vkEndCommandBuffer(vulkan_info->command_buffers[i]) != VK_SUCCESS) {
            printf("failed to record command buffer\n");
            return -1; // failed to record command buffer!
        }
    }
    return 0;
} 

int draw_frame(RGFW_window_vulkanInfo* vulkWin) { 
    vkWaitForFences(vulkan_info->device, 1, &vulkan_info->in_flight_fences[vulkan_info->current_frame], VK_TRUE, UINT64_MAX);

    u32 image_index = 0;
    vkAcquireNextImageKHR(vulkan_info->device, vulkWin->swapchain, UINT64_MAX, vulkan_info->available_semaphores[vulkan_info->current_frame], VK_NULL_HANDLE, &image_index);

    if (vulkan_info->image_in_flight[image_index] != VK_NULL_HANDLE) {
        vkWaitForFences(vulkan_info->device, 1, &vulkan_info->image_in_flight[image_index], VK_TRUE, UINT64_MAX);
    }
    vulkan_info->image_in_flight[image_index] = vulkan_info->in_flight_fences[vulkan_info->current_frame];

    VkSubmitInfo submitInfo = {0};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore wait_semaphores[] = { vulkan_info->available_semaphores[vulkan_info->current_frame] };
    VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = wait_semaphores;
    submitInfo.pWaitDstStageMask = wait_stages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &vulkan_info->command_buffers[image_index];

    VkSemaphore signal_semaphores[] = { vulkan_info->finished_semaphore[vulkan_info->current_frame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signal_semaphores;

    vkResetFences(vulkan_info->device, 1, &vulkan_info->in_flight_fences[vulkan_info->current_frame]);

    if (vkQueueSubmit(vulkan_info->graphics_queue, 1, &submitInfo, vulkan_info->in_flight_fences[vulkan_info->current_frame]) != VK_SUCCESS) {
        printf("failed to submit draw command buffer\n");
        return -1; //"failed to submit draw command buffer
    }

    VkPresentInfoKHR present_info = {0};
    present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    present_info.waitSemaphoreCount = 1;
    present_info.pWaitSemaphores = signal_semaphores;

    VkSwapchainKHR swapChains[] = { vulkWin->swapchain };
    present_info.swapchainCount = 1;
    present_info.pSwapchains = swapChains;

    present_info.pImageIndices = &image_index;

    vkQueuePresentKHR(vulkan_info->present_queue, &present_info);

    vulkan_info->current_frame = (vulkan_info->current_frame + 1) % RGFW_MAX_FRAMES_IN_FLIGHT;
    return 0;
}