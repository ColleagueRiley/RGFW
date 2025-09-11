#include <stdio.h>
#include <stdlib.h>

#define RGFW_DEBUG
#define RGFW_VULKAN
#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
#include <RGFW.h>
/*
    This isn't included in RGFW.h itself because
    you'd want to define that stuff yourself in most usecases
*/

#define MAX_FRAMES_IN_FLIGHT 2
#define VKINIT_IMPLEMENTATION
//#define VKINIT_DEBUG_VULKAN
#include "vkinit.h"

/**
 * ```bash
 * glslangValidator -V shader/vert.glsl -o vert.glsl.h --vn vert_code
 * glslangValidator -V shaders/vert.glsl -o vertexShader.spv
 * ```
 */

#include "shaders/frag.h"
#include "shaders/vert.h"

vulkanInfo* vkinit_vulkan_info;

int createGraphicsPipeline(vulkanContext* ctx);
int commandBuffers(vulkanContext *ctx);
int draw_frame(vulkanContext *ctx);

float mouse_data[2] = {0.0f, 0.0f};
RGFWDEF void mousePosCallback(RGFW_window *win, i32 x, i32 y, float vecX, float vecY);
void mousePosCallback(RGFW_window *win, i32 x, i32 y, float vecX, float vecY) {
  RGFW_UNUSED(vecX);  RGFW_UNUSED(vecY);
  printf("mouse moved %i %i\n", x, y);
  float halfWidth = (float)(win->w / 2.0f);
  float halfHeight = (float)(win->h / 2.0f);
  mouse_data[0] = (float)(x - halfWidth) / halfWidth;
  mouse_data[1] = (float)(y - halfHeight) / halfHeight;
}

int main(void) {
  RGFW_window *win =
      RGFW_createWindow("Vulkan Example", 0, 0, 500, 500,
                        RGFW_windowAllowDND | RGFW_windowCenter);
  RGFW_window_setExitKey(win, RGFW_escape);
  RGFW_setMousePosCallback(mousePosCallback);

  vulkanContext ctx;

  int res = initVulkanDevice(win, &ctx);
  if (res == 0) {
    vkinit_vulkan_info = initVulkan(&ctx);

    if (vkinit_vulkan_info != NULL)
      createGraphicsPipeline(&ctx);
    else return 0;
  }

  u8 running = 1;
  while (running && !RGFW_window_isKeyPressed(win, RGFW_escape)) {
    RGFW_event event;
    while (RGFW_window_checkEvent(win, &event)) {
      if (event.type == RGFW_quit) {
        running = 0;
        break;
      }
    }

    if (vkinit_vulkan_info != NULL) {
      draw_frame(&ctx);
    }
  }

  if (vkinit_vulkan_info != NULL)
    freeVulkan(&ctx);

  RGFW_window_close(win);
  return 0;
}

int createGraphicsPipeline(vulkanContext* ctx) {
  VkShaderModule vert_module =
      createShaderModule(vert_code, sizeof(vert_code));
  VkShaderModule frag_module =
      createShaderModule(frag_code, sizeof(frag_code));

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

  VkPipelineShaderStageCreateInfo shader_stages[] = {vert_stage_info,
                                                     frag_stage_info};

  VkPipelineVertexInputStateCreateInfo vertex_input_info = {0};
  vertex_input_info.sType =
      VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertex_input_info.vertexBindingDescriptionCount = 0;
  vertex_input_info.vertexAttributeDescriptionCount = 0;

  VkPipelineInputAssemblyStateCreateInfo input_assembly = {0};
  input_assembly.sType =
      VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  input_assembly.primitiveRestartEnable = VK_FALSE;

  VkViewport viewport;
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = (float)ctx->width;
  viewport.height = (float)ctx->height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  VkRect2D scissor;
  scissor.offset.x = 0;
  scissor.offset.y = 0;
  scissor.extent = (VkExtent2D){ctx->width, ctx->height};

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
  multisampling.sType =
      VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

  VkPipelineColorBlendAttachmentState colorBlendAttachment = {0};
  colorBlendAttachment.colorWriteMask =
      VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
      VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  colorBlendAttachment.blendEnable = VK_FALSE;

  VkPipelineColorBlendStateCreateInfo color_blending = {0};
  color_blending.sType =
      VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blending.logicOpEnable = VK_FALSE;
  color_blending.logicOp = VK_LOGIC_OP_COPY;
  color_blending.attachmentCount = 1;
  color_blending.pAttachments = &colorBlendAttachment;
  color_blending.blendConstants[0] = 0.0f;
  color_blending.blendConstants[1] = 0.0f;
  color_blending.blendConstants[2] = 0.0f;
  color_blending.blendConstants[3] = 0.0f;

  VkPushConstantRange range = {};
  range.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  range.offset = 0;
  range.size = sizeof(mouse_data);
  VkPipelineLayoutCreateInfo pipeline_layout_info = {0};
  pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipeline_layout_info.setLayoutCount = 0;
  pipeline_layout_info.pushConstantRangeCount = 1;
  pipeline_layout_info.pPushConstantRanges = &range;

  if (vkCreatePipelineLayout(vkinit_vulkan_info->device, &pipeline_layout_info, NULL,
                             &vkinit_vulkan_info->pipeline_layout) != VK_SUCCESS) {
    printf("failed to create pipeline layout\n");
    return -1; // failed to create pipeline layout
  }

  VkDynamicState dynamic_states[] = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};

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
  pipeline_info.layout = vkinit_vulkan_info->pipeline_layout;
  pipeline_info.renderPass = vkinit_vulkan_info->render_pass;
  pipeline_info.subpass = 0;
  pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

  if (vkCreateGraphicsPipelines(
          vkinit_vulkan_info->device, VK_NULL_HANDLE, 1, &pipeline_info, NULL,
          &vkinit_vulkan_info->graphics_pipeline) != VK_SUCCESS) {
    printf("failed to create pipline\n");
    return -1; // failed to create graphics pipeline
  }

  vkDestroyShaderModule(vkinit_vulkan_info->device, frag_module, NULL);
  vkDestroyShaderModule(vkinit_vulkan_info->device, vert_module, NULL);
  return 0;
}

int commandBuffers(vulkanContext* ctx) {
  for (size_t i = 0; i < ctx->image_count; i++) {
    VkCommandBufferBeginInfo begin_info = {0};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(vkinit_vulkan_info->command_buffers[i], &begin_info) !=
        VK_SUCCESS) {
      printf("Failed to begin recording command buffer\n");
      return -1;
    }

    VkRenderPassBeginInfo render_pass_info = {0};
    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    render_pass_info.renderPass = vkinit_vulkan_info->render_pass;
    render_pass_info.framebuffer = vkinit_vulkan_info->framebuffers[i];
    render_pass_info.renderArea.offset.x = 0;
    render_pass_info.renderArea.offset.y = 0;
    render_pass_info.renderArea.extent = (VkExtent2D){ctx->width, ctx->height};

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
    viewport.width = (float)ctx->width;
    viewport.height = (float)ctx->height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor;
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent = (VkExtent2D){ctx->width, ctx->height};
    vkCmdSetScissor(vkinit_vulkan_info->command_buffers[i], 0, 1, &scissor);

    vkCmdSetViewport(vkinit_vulkan_info->command_buffers[i], 0, 1, &viewport);

    vkCmdBeginRenderPass(vkinit_vulkan_info->command_buffers[i], &render_pass_info,
                         VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(vkinit_vulkan_info->command_buffers[i],
                      VK_PIPELINE_BIND_POINT_GRAPHICS,
                      vkinit_vulkan_info->graphics_pipeline);

    // Push mouse position as a push constant
    vkCmdPushConstants(vkinit_vulkan_info->command_buffers[i],
                       vkinit_vulkan_info->pipeline_layout, VK_SHADER_STAGE_VERTEX_BIT,
                       0, sizeof(mouse_data), &mouse_data);

    vkCmdDraw(vkinit_vulkan_info->command_buffers[i], 3, 1, 0, 0);
    vkCmdEndRenderPass(vkinit_vulkan_info->command_buffers[i]);

    if (vkEndCommandBuffer(vkinit_vulkan_info->command_buffers[i]) != VK_SUCCESS) {

      printf("failed to record command buffer\n");
      return -1; // failed to record command buffer!
    }
  }
  return 0;
}

int draw_frame(vulkanContext *ctx) {
  vkWaitForFences(vkinit_vulkan_info->device, 1,
                  &vkinit_vulkan_info->in_flight_fences[vkinit_vulkan_info->current_frame],
                  VK_TRUE, UINT64_MAX);

  u32 image_index = 0;
  vkAcquireNextImageKHR(
      vkinit_vulkan_info->device, ctx->swapchain, UINT64_MAX,
      vkinit_vulkan_info->available_semaphores[vkinit_vulkan_info->current_frame],
      VK_NULL_HANDLE, &image_index);

  if (vkinit_vulkan_info->image_in_flight[image_index] != VK_NULL_HANDLE) {
    vkWaitForFences(vkinit_vulkan_info->device, 1,
                    &vkinit_vulkan_info->image_in_flight[image_index], VK_TRUE,
                    UINT64_MAX);
  }
  vkinit_vulkan_info->image_in_flight[image_index] =
      vkinit_vulkan_info->in_flight_fences[vkinit_vulkan_info->current_frame];

  VkSubmitInfo submitInfo = {0};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

  VkSemaphore wait_semaphores[] = {
      vkinit_vulkan_info->available_semaphores[vkinit_vulkan_info->current_frame]};
  VkPipelineStageFlags wait_stages[] = {
      VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = wait_semaphores;
  submitInfo.pWaitDstStageMask = wait_stages;

  commandBuffers(ctx);
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &vkinit_vulkan_info->command_buffers[image_index];
  /**/
  VkSemaphore signal_semaphores[] = {
      vkinit_vulkan_info->finished_semaphore[vkinit_vulkan_info->current_frame]};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signal_semaphores;

  vkResetFences(vkinit_vulkan_info->device, 1,
                &vkinit_vulkan_info->in_flight_fences[vkinit_vulkan_info->current_frame]);

  if (vkQueueSubmit(
          vkinit_vulkan_info->graphics_queue, 1, &submitInfo,
          vkinit_vulkan_info->in_flight_fences[vkinit_vulkan_info->current_frame]) !=
      VK_SUCCESS) {
    printf("failed to submit draw command buffer\n");
    return -1; //"failed to submit draw command buffer
  }

  VkPresentInfoKHR present_info = {0};
  present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

  present_info.waitSemaphoreCount = 1;
  present_info.pWaitSemaphores = signal_semaphores;

  VkSwapchainKHR swapChains[] = {ctx->swapchain};
  present_info.swapchainCount = 1;
  present_info.pSwapchains = swapChains;

  present_info.pImageIndices = &image_index;

  vkQueuePresentKHR(vkinit_vulkan_info->present_queue, &present_info);

  vkinit_vulkan_info->current_frame =
      (vkinit_vulkan_info->current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
  return 0;
}
