#ifndef RGFW_HEADER
#error RGFW must be included before this header
#endif

#ifndef VKINIT_H
#define VKINIT_H

#include <vulkan/vulkan.h>


typedef struct vulkanContext {
    VkSurfaceKHR surface; /*!< source graphics context */
    u32 width, height; /* size*/

    /* vulkan data */
    VkSwapchainKHR swapchain;
    u32 image_count;
    VkImage* swapchain_images;
    VkImageView* swapchain_image_views;
} vulkanContext;

typedef struct vulkanInfo {
    VkInstance instance;
    VkPhysicalDevice physical_device;
    VkDevice device;

    VkDebugUtilsMessengerEXT debugMessenger;

    VkQueue graphics_queue;
    VkQueue present_queue;

    VkFramebuffer* framebuffers;

    VkRenderPass render_pass;
    VkPipelineLayout pipeline_layout;
    VkPipeline graphics_pipeline;

    VkCommandPool command_pool;
    VkCommandBuffer* command_buffers;

    VkSemaphore* available_semaphores;
    VkSemaphore* finished_semaphore;
    VkFence* in_flight_fences;
    VkFence* image_in_flight;
    size_t current_frame;
} vulkanInfo;


#ifndef VKDEF
	#define VKDEF inline
#endif

VKDEF int initVulkanDevice(RGFW_window* win, vulkanContext* ctx);
VKDEF vulkanInfo* initVulkan(vulkanContext* ctx);
VKDEF void freeVulkan(vulkanContext* ctx);

VKDEF vulkanInfo* getVulkanInfo(void);

int createSwapchain(vulkanContext* ctx);
VKDEF int createRenderPass(void);
int createCommandPool(void);
int createCommandBuffers(vulkanContext* ctx);
int createSyncObjects(vulkanContext* ctx);
VKDEF int createFramebuffers(vulkanContext* ctx);
VKDEF VkShaderModule createShaderModule(const u32* code, size_t code_size);
void  createDebugCallback();
const char* getDebugSeverityStr(VkDebugUtilsMessageSeverityFlagBitsEXT Severity);
const char* getDebugType(VkDebugUtilsMessageTypeFlagsEXT Type);

#endif

#ifdef VKINIT_IMPLEMENTATION

vulkanInfo vkInit_vulkan_info;


vulkanInfo* initVulkan(vulkanContext* ctx) {
    if (createSwapchain(ctx))
        return NULL;

    u32 graphics_family_index = 0;
    u32 present_family_index = 0;

    vkGetDeviceQueue(vkInit_vulkan_info.device, graphics_family_index, 0, &vkInit_vulkan_info.graphics_queue);
    vkGetDeviceQueue(vkInit_vulkan_info.device, present_family_index, 0, &vkInit_vulkan_info.present_queue);

    if (
        createRenderPass() ||
        createFramebuffers(ctx) ||
        createCommandPool() ||
        createCommandBuffers(ctx) ||
        createSyncObjects(ctx)
        )
        return NULL;

    return &vkInit_vulkan_info;
}
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
  VkDebugUtilsMessageSeverityFlagBitsEXT Severity,
  VkDebugUtilsMessageTypeFlagsEXT Type,
  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
  void* pUserData
){
    printf("\nDebug callback: %s\n",pCallbackData->pMessage);
    printf(" Severity: %s\n",getDebugSeverityStr(Severity));
    printf(" Type: %s\n",getDebugType(Type));
    printf(" Objects ");

    for (u32 i= 0; i < pCallbackData->objectCount; i++) {
#ifdef _WIN32
    printf("%llx ", pCallbackData->pObjects[i].objectHandle);
#else
    printf("%lx ", pCallbackData->pObjects[i].objectHandle);
#endif
    }
    return 1;
}

const char* getDebugSeverityStr(VkDebugUtilsMessageSeverityFlagBitsEXT Severity)
{
	switch (Severity) {
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
		return "Verbose";

	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
		return "Info";

	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
		return "Warning";

	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
		return "Error";

	default:
		printf("Invalid severity code %d\n", Severity);
		exit(1);
	}

	return "NO SUCH SEVERITY!";
}
const char* getDebugType(VkDebugUtilsMessageTypeFlagsEXT Type)
{
	switch (Type) {
	case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
		return "General";

	case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
		return "Validation";

	case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
		return "Performance";

#ifdef _WIN64 // doesn't work on my Linux for some reason
	case VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT:
		return "Device address binding";
#endif

	default:
		printf("Invalid type code %d\n", Type);
		exit(1);
	}

	return "NO SUCH TYPE!";
}
void  createDebugCallback(){
printf("Creating debug callback\n");
  VkDebugUtilsMessengerCreateInfoEXT MessengerCreateInfo = {
    .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
    .pNext = NULL,
    .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
    .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
    .pfnUserCallback = &debugCallback,
    .pUserData = NULL
  };

  PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessenger = VK_NULL_HANDLE;
  vkCreateDebugUtilsMessenger=(PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(vkInit_vulkan_info.instance,"vkCreateDebugUtilsMessengerEXT");
  if(!vkCreateDebugUtilsMessenger) {
    printf("vkCreateDebugUtilsMessenger Failed\n");
    exit(1);
  }
  VkResult debug_result = vkCreateDebugUtilsMessenger(
    vkInit_vulkan_info.instance,
    &MessengerCreateInfo,
    NULL,
    &vkInit_vulkan_info.debugMessenger
  );
  if (debug_result != VK_SUCCESS) {
        printf("Failed to create debug messenger!");
    }
}

vulkanInfo* getVulkanInfo(void) {
    return &vkInit_vulkan_info;
}

int initVulkanDevice(RGFW_window* win, vulkanContext* ctx) {
    assert(win != NULL);

    ctx->swapchain = VK_NULL_HANDLE;
    ctx->image_count = 0;
    vkInit_vulkan_info.current_frame = 0;

    ctx->width = win->r.w;
    ctx->height = win->r.h;

    VkApplicationInfo appInfo = (VkApplicationInfo){ 0 };
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "vkapp";
    appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);

    const char* ppEnabledExtensionNames[] = {VK_KHR_SURFACE_EXTENSION_NAME, RGFW_VK_SURFACE};
    uint32_t enabledExtensionCount = 2;

    char* debugExtension =
    #ifdef VKINIT_DEBUG_VULKAN
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
    #else
        NULL;
    #endif

    if (debugExtension != NULL) {
        ppEnabledExtensionNames[enabledExtensionCount++] = debugExtension;
    }
    // Print each extension name
    for (int i = 0; i < enabledExtensionCount; i++) {
        printf("%s\n", ppEnabledExtensionNames[i]);
    }
    VkInstanceCreateInfo instance_create_info = (VkInstanceCreateInfo){ 0 };
    instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_create_info.pApplicationInfo = &appInfo;
    instance_create_info.enabledExtensionCount = enabledExtensionCount;
    instance_create_info.ppEnabledExtensionNames = ppEnabledExtensionNames;

    if (vkCreateInstance(&instance_create_info, NULL, &vkInit_vulkan_info.instance) != VK_SUCCESS) {
        fprintf(stderr, "failed to create instance!\n");
        return -1;
    }

#ifdef VKINIT_DEBUG_VULKAN
    vkInit_vulkan_info.debugMessenger= VK_NULL_HANDLE;
    createDebugCallback();
#endif
    RGFW_window_createSurface_Vulkan(win, vkInit_vulkan_info.instance, &ctx->surface);

    u32 deviceCount = 0;
    vkEnumeratePhysicalDevices(vkInit_vulkan_info.instance, &deviceCount, NULL);
    VkPhysicalDevice* devices = (VkPhysicalDevice*) malloc(sizeof(VkPhysicalDevice) * deviceCount);
    vkEnumeratePhysicalDevices(vkInit_vulkan_info.instance, &deviceCount, devices);

    vkInit_vulkan_info.physical_device = devices[0];
    free(devices);

    u32 graphics_queue_family = 0;

    if (vkInit_vulkan_info.physical_device != NULL && deviceCount) {
        u32 queue_family_count = 0;
        VkQueueFamilyProperties* queueFamilies;

        vkGetPhysicalDeviceQueueFamilyProperties(vkInit_vulkan_info.physical_device, &queue_family_count, NULL);
        queueFamilies = (VkQueueFamilyProperties*) malloc(sizeof(VkQueueFamilyProperties) * queue_family_count);

        vkGetPhysicalDeviceQueueFamilyProperties(vkInit_vulkan_info.physical_device, &queue_family_count, queueFamilies);

        for(u32 i = 0; i < queue_family_count; i++) {
            if(queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                graphics_queue_family = i;
                break;
            }
        }

        free(queueFamilies);
    }

    float queuePriority = 1.0f;

    VkPhysicalDeviceFeatures device_features = (VkPhysicalDeviceFeatures){ 0 };

    VkDeviceCreateInfo device_create_info = (VkDeviceCreateInfo){ 0 };
    device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    VkDeviceQueueCreateInfo queue_create_info = {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueCount = 1,
            .pQueuePriorities = &queuePriority,
            .queueFamilyIndex = graphics_queue_family,
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO
    };

    device_create_info.queueCreateInfoCount = 1;
    device_create_info.pQueueCreateInfos = &queue_create_info;

    device_create_info.enabledExtensionCount = 1;

    const char* device_extensions[] = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    device_create_info.ppEnabledExtensionNames = device_extensions;
    device_create_info.pEnabledFeatures = &device_features;

    if ((vkInit_vulkan_info.physical_device == NULL || deviceCount == 0) ||
        vkCreateDevice(vkInit_vulkan_info.physical_device, &device_create_info, NULL, &vkInit_vulkan_info.device) != VK_SUCCESS) {
        fprintf(stderr, "failed to create logical device!\n");
        return -1;
    }

    return 0;
}

int createSwapchain(vulkanContext* ctx) {
    VkSurfaceFormatKHR surfaceFormat = { VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
    VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;

    VkSurfaceCapabilitiesKHR capabilities = { 0 };
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkInit_vulkan_info.physical_device, ctx->surface, &capabilities);

    ctx->image_count = capabilities.minImageCount + 1;
    if (capabilities.maxImageCount > 0 && ctx->image_count > capabilities.maxImageCount) {
        ctx->image_count = capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR swapchain_create_info = { 0 };
    swapchain_create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchain_create_info.surface = ctx->surface;
    swapchain_create_info.minImageCount = ctx->image_count;
    swapchain_create_info.imageFormat = surfaceFormat.format;
    swapchain_create_info.imageColorSpace = surfaceFormat.colorSpace;
    swapchain_create_info.imageExtent = (VkExtent2D){ ctx->width, ctx->height };
    swapchain_create_info.imageArrayLayers = 1;
    swapchain_create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchain_create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapchain_create_info.queueFamilyIndexCount = 2;
    swapchain_create_info.preTransform = capabilities.currentTransform;
    swapchain_create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchain_create_info.presentMode = presentMode;
    swapchain_create_info.clipped = VK_TRUE;
    swapchain_create_info.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(vkInit_vulkan_info.device, &swapchain_create_info, NULL, &ctx->swapchain) != VK_SUCCESS) {
        fprintf(stderr, "failed to create swap chain!\n");
        return -1;
    }

    u32 imageCount;
    vkGetSwapchainImagesKHR(vkInit_vulkan_info.device, ctx->swapchain, &imageCount, NULL);
    ctx->swapchain_images = (VkImage*) malloc(sizeof(VkImage) * imageCount);
    vkGetSwapchainImagesKHR(vkInit_vulkan_info.device, ctx->swapchain, &imageCount, ctx->swapchain_images);

    ctx->swapchain_image_views = (VkImageView*) malloc(sizeof(VkImageView) * imageCount);
    for (u32 i = 0; i < imageCount; i++) {
        VkImageViewCreateInfo image_view_cre_infos = { 0 };
        image_view_cre_infos.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        image_view_cre_infos.image = ctx->swapchain_images[i];
        image_view_cre_infos.viewType = VK_IMAGE_VIEW_TYPE_2D;
        image_view_cre_infos.format = VK_FORMAT_B8G8R8A8_SRGB;
        image_view_cre_infos.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_cre_infos.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_cre_infos.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_cre_infos.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_cre_infos.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        image_view_cre_infos.subresourceRange.baseMipLevel = 0;
        image_view_cre_infos.subresourceRange.levelCount = 1;
        image_view_cre_infos.subresourceRange.baseArrayLayer = 0;
        image_view_cre_infos.subresourceRange.layerCount = 1;
        if (vkCreateImageView(vkInit_vulkan_info.device, &image_view_cre_infos, NULL, &ctx->swapchain_image_views[i]) != VK_SUCCESS) {
            fprintf(stderr, "failed to create image views!");
            return -1;
        }
    }

    return 0;
}

int createRenderPass(void) {
    VkAttachmentDescription color_attachment = { 0 };
    color_attachment.format = VK_FORMAT_B8G8R8A8_SRGB;
    color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
    color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference color_attachment_ref = { 0 };
    color_attachment_ref.attachment = 0;
    color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = { 0 };
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &color_attachment_ref;

    VkSubpassDependency dependency = { 0 };
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo render_pass_info = { 0 };
    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    render_pass_info.attachmentCount = 1;
    render_pass_info.pAttachments = &color_attachment;
    render_pass_info.subpassCount = 1;
    render_pass_info.pSubpasses = &subpass;
    render_pass_info.dependencyCount = 1;
    render_pass_info.pDependencies = &dependency;

    if (vkCreateRenderPass(vkInit_vulkan_info.device, &render_pass_info, NULL, &vkInit_vulkan_info.render_pass) != VK_SUCCESS) {
        fprintf(stderr, "failed to create render pass\n");
        return -1; // failed to create render pass!
    }
    return 0;
}

int createCommandPool(void) {
    VkCommandPoolCreateInfo pool_info = { 0 };
    pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pool_info.queueFamilyIndex = 0;

    if (vkCreateCommandPool(vkInit_vulkan_info.device, &pool_info, NULL, &vkInit_vulkan_info.command_pool) != VK_SUCCESS) {
        fprintf(stderr, "failed to create command pool\n");
        return -1; // failed to create command pool
    }
    return 0;
}

int createCommandBuffers(vulkanContext* ctx) {
    assert(ctx != NULL);

    vkInit_vulkan_info.command_buffers = (VkCommandBuffer*) malloc(sizeof(VkCommandBuffer) * ctx->image_count);

    VkCommandBufferAllocateInfo allocInfo = { 0 };
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = vkInit_vulkan_info.command_pool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (u32) ctx->image_count;

    if (vkAllocateCommandBuffers(vkInit_vulkan_info.device, &allocInfo, vkInit_vulkan_info.command_buffers) != VK_SUCCESS) {
        return -1; // failed to allocate command buffers;
    }

    return 0;
}

int createSyncObjects(vulkanContext* ctx) {
    assert(ctx != NULL);

    vkInit_vulkan_info.available_semaphores = (VkSemaphore*) malloc(sizeof(VkSemaphore) * MAX_FRAMES_IN_FLIGHT);
    vkInit_vulkan_info.finished_semaphore = (VkSemaphore*) malloc(sizeof(VkSemaphore) * MAX_FRAMES_IN_FLIGHT);
    vkInit_vulkan_info.in_flight_fences = (VkFence*) malloc(sizeof(VkFence) * MAX_FRAMES_IN_FLIGHT);
    vkInit_vulkan_info.image_in_flight = (VkFence*) malloc(sizeof(VkFence) * ctx->image_count);

    VkSemaphoreCreateInfo semaphore_info = { 0 };
    semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fence_info = { 0 };
    fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(vkInit_vulkan_info.device, &semaphore_info, NULL, &vkInit_vulkan_info.available_semaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(vkInit_vulkan_info.device, &semaphore_info, NULL, &vkInit_vulkan_info.finished_semaphore[i]) != VK_SUCCESS ||
            vkCreateFence(vkInit_vulkan_info.device, &fence_info, NULL, &vkInit_vulkan_info.in_flight_fences[i]) != VK_SUCCESS) {
            fprintf(stderr, "failed to create sync objects\n");
            return -1; // failed to create synchronization objects for a frame
        }
    }

    for (size_t i = 0; i < ctx->image_count; i++) {
        vkInit_vulkan_info.image_in_flight[i] = VK_NULL_HANDLE;
    }

    return 0;
}

int createFramebuffers(vulkanContext* ctx) {
    assert(ctx != NULL);

    vkInit_vulkan_info.framebuffers = (VkFramebuffer*) malloc(sizeof(VkFramebuffer) * ctx->image_count);

    for (size_t i = 0; i < ctx->image_count; i++) {
        VkImageView attachments[] = { ctx->swapchain_image_views[i] };

        VkFramebufferCreateInfo framebuffer_info = { 0 };
        framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebuffer_info.renderPass = vkInit_vulkan_info.render_pass;
        framebuffer_info.attachmentCount = 1;
        framebuffer_info.pAttachments = attachments;
        framebuffer_info.width = ctx->width;
        framebuffer_info.height = ctx->height;
        framebuffer_info.layers = 1;

        if (vkCreateFramebuffer(vkInit_vulkan_info.device, &framebuffer_info, NULL, &vkInit_vulkan_info.framebuffers[i]) != VK_SUCCESS) {
            return -1; // failed to create framebuffer
        }
    }
    return 0;
}

void freeVulkan(vulkanContext* ctx) {
    for (u32 i = 0; i < ctx->image_count; i++) {
        vkDestroyImageView(vkInit_vulkan_info.device, ctx->swapchain_image_views[i], NULL);
    }

    for (u32 i = 0; i < ctx->image_count; i++) {
        vkDestroyFramebuffer(vkInit_vulkan_info.device, vkInit_vulkan_info.framebuffers[i], NULL);
    }

    vkDestroySwapchainKHR(vkInit_vulkan_info.device, ctx->swapchain, NULL);
    vkDestroySurfaceKHR(vkInit_vulkan_info.instance, ctx->surface, NULL);
    free(ctx->swapchain_image_views);
    free(ctx->swapchain_images);

    vkDeviceWaitIdle(vkInit_vulkan_info.device);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(vkInit_vulkan_info.device, vkInit_vulkan_info.finished_semaphore[i], NULL);
        vkDestroySemaphore(vkInit_vulkan_info.device, vkInit_vulkan_info.available_semaphores[i], NULL);
        vkDestroyFence(vkInit_vulkan_info.device, vkInit_vulkan_info.in_flight_fences[i], NULL);
    }

    vkDestroyCommandPool(vkInit_vulkan_info.device, vkInit_vulkan_info.command_pool, NULL);

    vkDestroyPipeline(vkInit_vulkan_info.device, vkInit_vulkan_info.graphics_pipeline, NULL);
    vkDestroyPipelineLayout(vkInit_vulkan_info.device, vkInit_vulkan_info.pipeline_layout, NULL);
    vkDestroyRenderPass(vkInit_vulkan_info.device, vkInit_vulkan_info.render_pass, NULL);

#ifdef VKINIT_DEBUG_VULKAN
    printf("VKINIT_DEBUG_VULKAN is defined");
    PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(vkInit_vulkan_info.instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != NULL) {
        func(vkInit_vulkan_info.instance, vkInit_vulkan_info.debugMessenger, NULL);
    }
#endif

    vkDestroyDevice(vkInit_vulkan_info.device, NULL);
    vkDestroyInstance(vkInit_vulkan_info.instance, NULL);

    free(vkInit_vulkan_info.framebuffers);
    free(vkInit_vulkan_info.command_buffers);
    free(vkInit_vulkan_info.available_semaphores);
    free(vkInit_vulkan_info.finished_semaphore);
    free(vkInit_vulkan_info.in_flight_fences);
    free(vkInit_vulkan_info.image_in_flight);
}

VkShaderModule createShaderModule(const u32* code, size_t code_size) {
    VkShaderModuleCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.codeSize = code_size;
    create_info.pCode = code;

    VkShaderModule shaderModule;
    if (vkInit_vulkan_info.device == NULL || vkCreateShaderModule(vkInit_vulkan_info.device, &create_info, NULL, &shaderModule) != VK_SUCCESS) {
        return VK_NULL_HANDLE;
    }

    return shaderModule;
}
#endif
