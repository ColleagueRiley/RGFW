#ifndef RGFW_HEADER
#error RGFW must be included before this header
#endif

#ifndef RGFW_VULKAN_H
#define RGFW_VULKAN_H

#ifndef RGFW_MAX_FRAMES_IN_FLIGHT
#define RGFW_MAX_FRAMES_IN_FLIGHT 2
#endif

#ifdef RGFW_X11
#define VK_USE_PLATFORM_XLIB_KHR
#endif
#ifdef RGFW_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#ifdef RGFW_MACOS
#define VK_USE_PLATFORM_MACOS_MVK
#endif

#include <vulkan/vulkan.h>


typedef struct RGFW_window_vulkanInfo {
    VkSurfaceKHR rSurf; /*!< source graphics context */

    /* vulkan data */
    VkSwapchainKHR swapchain;
    u32 image_count;
    VkImage* swapchain_images;
    VkImageView* swapchain_image_views;
} RGFW_window_vulkanInfo;

typedef struct RGFW_vulkanInfo {
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
} RGFW_vulkanInfo;

RGFWDEF RGFW_vulkanInfo* RGFW_initVulkan(RGFW_window* win, RGFW_window_vulkanInfo* vulkWin);
RGFWDEF void RGFW_freeVulkan(RGFW_window_vulkanInfo* vulkWin);

RGFWDEF RGFW_vulkanInfo* RGFW_getVulkanInfo(void);

RGFWDEF int RGFW_initData(RGFW_window_vulkanInfo* vulkWin);
RGFWDEF void RGFW_createSurface(VkInstance instance, RGFW_window* win, RGFW_window_vulkanInfo* vulkWin);
int RGFW_deviceInitialization(RGFW_window* win, RGFW_window_vulkanInfo* vulkWin);
int RGFW_createSwapchain(RGFW_window* win, RGFW_window_vulkanInfo* vulkWin);
RGFWDEF int RGFW_createRenderPass(void);
int RGFW_createCommandPool(void);
int RGFW_createCommandBuffers(RGFW_window_vulkanInfo* vulkWin);
int RGFW_createSyncObjects(RGFW_window_vulkanInfo* vulkWin);
RGFWDEF int RGFW_createFramebuffers(RGFW_window* win, RGFW_window_vulkanInfo* vulkWin);
RGFWDEF VkShaderModule RGFW_createShaderModule(const u32* code, size_t code_size);
void  RGFW_createDebugCallback();
const char* RGFW_getDebugSeverityStr(VkDebugUtilsMessageSeverityFlagBitsEXT Severity);
const char* RGFW_getDebugType(VkDebugUtilsMessageTypeFlagsEXT Type);

#endif

#ifdef RGFW_VULKAN_IMPLEMENTATION

RGFW_vulkanInfo RGFW_vulkan_info;


RGFW_vulkanInfo* RGFW_initVulkan(RGFW_window* win, RGFW_window_vulkanInfo* vulkWin) {
    assert(win != NULL);

    if (
        RGFW_initData(vulkWin) ||
        RGFW_deviceInitialization(win, vulkWin) ||
        RGFW_createSwapchain(win, vulkWin)
        )
        return NULL;

    u32 graphics_family_index = 0;
    u32 present_family_index = 0;

    vkGetDeviceQueue(RGFW_vulkan_info.device, graphics_family_index, 0, &RGFW_vulkan_info.graphics_queue);
    vkGetDeviceQueue(RGFW_vulkan_info.device, present_family_index, 0, &RGFW_vulkan_info.present_queue);

    if (
        RGFW_createRenderPass() ||
        RGFW_createFramebuffers(win, vulkWin) ||
        RGFW_createCommandPool() ||
        RGFW_createCommandBuffers(vulkWin) ||
        RGFW_createSyncObjects(vulkWin)
        )
        return NULL;

    return &RGFW_vulkan_info;
}
static VKAPI_ATTR VkBool32 VKAPI_CALL RGFW_debugCallback(
  VkDebugUtilsMessageSeverityFlagBitsEXT Severity,
  VkDebugUtilsMessageTypeFlagsEXT Type,
  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
  void* pUserData
){
  printf("\nDebug callback: %s\n",pCallbackData->pMessage);
  printf(" Severity: %s\n",RGFW_getDebugSeverityStr(Severity));
  printf(" Type: %s\n",RGFW_getDebugType(Type));
  printf(" Objects ");

  for (u32 i= 0; i < pCallbackData->objectCount; i++) {
    printf("%I64X", pCallbackData->pObjects[i].objectHandle);
  }
}

const char* RGFW_getDebugSeverityStr(VkDebugUtilsMessageSeverityFlagBitsEXT Severity)
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
const char* RGFW_getDebugType(VkDebugUtilsMessageTypeFlagsEXT Type)
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
void  RGFW_createDebugCallback(){
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
    .pfnUserCallback = &RGFW_debugCallback,
    .pUserData = NULL
  };

  PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessenger = VK_NULL_HANDLE;
  vkCreateDebugUtilsMessenger=(PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(RGFW_vulkan_info.instance,"vkCreateDebugUtilsMessengerEXT");
  if(!vkCreateDebugUtilsMessenger) {
    printf("vkCreateDebugUtilsMessenger Failed\n");
    exit(1);
  }
  VkResult debug_result = vkCreateDebugUtilsMessenger(
    RGFW_vulkan_info.instance,
    &MessengerCreateInfo,
    NULL,
    &RGFW_vulkan_info.debugMessenger
  );
  if (debug_result != VK_SUCCESS) {
        printf("Failed to create debug messenger!");
    }
}
int RGFW_initData(RGFW_window_vulkanInfo* vulkWin) {
    assert(vulkWin != NULL);

    vulkWin->swapchain = VK_NULL_HANDLE;
    vulkWin->image_count = 0;
    RGFW_vulkan_info.current_frame = 0;

    return 0;
}

void RGFW_createSurface(VkInstance instance, RGFW_window* win, RGFW_window_vulkanInfo* vulkWin) {
    assert(win != NULL);
    assert(instance);

    vulkWin->rSurf = VK_NULL_HANDLE;

#ifdef RGFW_X11
    VkXlibSurfaceCreateInfoKHR x11 = { VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR, 0, 0, (Display*) win->src.display, (Window) win->src.window };

    vkCreateXlibSurfaceKHR(RGFW_vulkan_info.instance, &x11, NULL, &vulkWin->rSurf);
#endif
#ifdef RGFW_WINDOWS
    VkWin32SurfaceCreateInfoKHR win32 = { VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR, 0, 0, GetModuleHandle(NULL), (HWND)win->src.window };

    vkCreateWin32SurfaceKHR(RGFW_vulkan_info.instance, &win32, NULL, &vulkWin->rSurf);
#endif
#if defined(RGFW_MACOS) && !defined(RGFW_MACOS_X11)
    VkMacOSSurfaceCreateFlagsMVK macos = { VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK, 0, 0, vulkWin->display, (void *)win->src.window };

    vkCreateMacOSSurfaceMVK(RGFW_vulkan_info.instance, &macos, NULL, &vulkWin->rSurf);
#endif
}

RGFW_vulkanInfo* RGFW_getVulkanInfo(void) {
    return &RGFW_vulkan_info;
}

int RGFW_deviceInitialization(RGFW_window* win, RGFW_window_vulkanInfo* vulkWin) {
    assert(win != NULL);

    VkApplicationInfo appInfo = { 0 };
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "RGFW app";
    appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);

const char* ppEnabledExtensionNames[] = {VK_KHR_SURFACE_EXTENSION_NAME};
uint32_t enabledExtensionCount = 1;

    char* extension =
#ifdef RGFW_WINDOWS
        "VK_KHR_win32_surface";
#elif defined(RGFW_X11)
        VK_KHR_XLIB_SURFACE_EXTENSION_NAME;
#elif defined(RGFW_MACOS)
        "VK_MVK_macos_surface";
#else
        NULL;
#endif

if (extension != NULL) {
    ppEnabledExtensionNames[enabledExtensionCount++] = extension;
}

  char* debugExtension =
#ifdef RGFW_DEBUG_VULKAN
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
    VkInstanceCreateInfo instance_create_info = { 0 };
    instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_create_info.pApplicationInfo = &appInfo;
    instance_create_info.enabledExtensionCount = enabledExtensionCount;
    instance_create_info.ppEnabledExtensionNames = ppEnabledExtensionNames;

    if (vkCreateInstance(&instance_create_info, NULL, &RGFW_vulkan_info.instance) != VK_SUCCESS) {
        fprintf(stderr, "failed to create instance!\n");
        return -1;
    }

#ifdef RGFW_DEBUG_VULKAN
    RGFW_vulkan_info.debugMessenger= VK_NULL_HANDLE;
    RGFW_createDebugCallback();
#endif
    RGFW_createSurface(RGFW_vulkan_info.instance, win, vulkWin);

    u32 deviceCount = 0;
    vkEnumeratePhysicalDevices(RGFW_vulkan_info.instance, &deviceCount, NULL);
    VkPhysicalDevice* devices = (VkPhysicalDevice*) malloc(sizeof(VkPhysicalDevice) * deviceCount);
    vkEnumeratePhysicalDevices(RGFW_vulkan_info.instance, &deviceCount, devices);

    RGFW_vulkan_info.physical_device = devices[0];

    u32 queue_family_count = 0;
    
    if (RGFW_vulkan_info.physical_device != NULL && deviceCount) {
        vkGetPhysicalDeviceQueueFamilyProperties(RGFW_vulkan_info.physical_device, &queue_family_count, NULL);
        VkQueueFamilyProperties* queueFamilies = (VkQueueFamilyProperties*) malloc(sizeof(VkQueueFamilyProperties) * queue_family_count);

        vkGetPhysicalDeviceQueueFamilyProperties(RGFW_vulkan_info.physical_device, &queue_family_count, queueFamilies);
    }

    float queuePriority = 1.0f;

    VkPhysicalDeviceFeatures device_features = { 0 };

    VkDeviceCreateInfo device_create_info = { 0 };
    device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    VkDeviceQueueCreateInfo queue_create_infos[2] = {
        {0},
        {0},
    };
    queue_create_infos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_infos[0].queueCount = 1;
    queue_create_infos[0].pQueuePriorities = &queuePriority;
    queue_create_infos[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_infos[1].queueCount = 1;
    queue_create_infos[1].pQueuePriorities = &queuePriority;
    device_create_info.queueCreateInfoCount = 2;
    device_create_info.pQueueCreateInfos = queue_create_infos;

    device_create_info.enabledExtensionCount = 1;

    const char* device_extensions[] = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    device_create_info.ppEnabledExtensionNames = device_extensions;
    device_create_info.pEnabledFeatures = &device_features;
    if ((RGFW_vulkan_info.physical_device == NULL || deviceCount == 0) || 
        vkCreateDevice(RGFW_vulkan_info.physical_device, &device_create_info, NULL, &RGFW_vulkan_info.device) != VK_SUCCESS) {
        fprintf(stderr, "failed to create logical device!\n");
        return -1;
    }

    return 0;
}

int RGFW_createSwapchain(RGFW_window* win, RGFW_window_vulkanInfo* vulkWin) {
    assert(win != NULL);

    VkSurfaceFormatKHR surfaceFormat = { VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
    VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;

    VkSurfaceCapabilitiesKHR capabilities = { 0 };
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(RGFW_vulkan_info.physical_device, vulkWin->rSurf, &capabilities);

    vulkWin->image_count = capabilities.minImageCount + 1;
    if (capabilities.maxImageCount > 0 && vulkWin->image_count > capabilities.maxImageCount) {
        vulkWin->image_count = capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR swapchain_create_info = { 0 };
    swapchain_create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchain_create_info.surface = vulkWin->rSurf;
    swapchain_create_info.minImageCount = vulkWin->image_count;
    swapchain_create_info.imageFormat = surfaceFormat.format;
    swapchain_create_info.imageColorSpace = surfaceFormat.colorSpace;
    swapchain_create_info.imageExtent = (VkExtent2D){ win->r.w, win->r.h };
    swapchain_create_info.imageArrayLayers = 1;
    swapchain_create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchain_create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapchain_create_info.queueFamilyIndexCount = 2;
    swapchain_create_info.preTransform = capabilities.currentTransform;
    swapchain_create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchain_create_info.presentMode = presentMode;
    swapchain_create_info.clipped = VK_TRUE;
    swapchain_create_info.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(RGFW_vulkan_info.device, &swapchain_create_info, NULL, &vulkWin->swapchain) != VK_SUCCESS) {
        fprintf(stderr, "failed to create swap chain!\n");
        return -1;
    }

    u32 imageCount;
    vkGetSwapchainImagesKHR(RGFW_vulkan_info.device, vulkWin->swapchain, &imageCount, NULL);
    vulkWin->swapchain_images = (VkImage*) malloc(sizeof(VkImage) * imageCount);
    vkGetSwapchainImagesKHR(RGFW_vulkan_info.device, vulkWin->swapchain, &imageCount, vulkWin->swapchain_images);

    vulkWin->swapchain_image_views = (VkImageView*) malloc(sizeof(VkImageView) * imageCount);
    for (u32 i = 0; i < imageCount; i++) {
        VkImageViewCreateInfo image_view_cre_infos = { 0 };
        image_view_cre_infos.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        image_view_cre_infos.image = vulkWin->swapchain_images[i];
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
        if (vkCreateImageView(RGFW_vulkan_info.device, &image_view_cre_infos, NULL, &vulkWin->swapchain_image_views[i]) != VK_SUCCESS) {
            fprintf(stderr, "failed to create image views!");
            return -1;
        }
    }

    return 0;
}

int RGFW_createRenderPass(void) {
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

    if (vkCreateRenderPass(RGFW_vulkan_info.device, &render_pass_info, NULL, &RGFW_vulkan_info.render_pass) != VK_SUCCESS) {
        fprintf(stderr, "failed to create render pass\n");
        return -1; // failed to create render pass!
    }
    return 0;
}

int RGFW_createCommandPool(void) {
    VkCommandPoolCreateInfo pool_info = { 0 };
    pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pool_info.queueFamilyIndex = 0;

    if (vkCreateCommandPool(RGFW_vulkan_info.device, &pool_info, NULL, &RGFW_vulkan_info.command_pool) != VK_SUCCESS) {
        fprintf(stderr, "failed to create command pool\n");
        return -1; // failed to create command pool
    }
    return 0;
}

int RGFW_createCommandBuffers(RGFW_window_vulkanInfo* vulkWin) {
    assert(vulkWin != NULL);

    RGFW_vulkan_info.command_buffers = (VkCommandBuffer*) malloc(sizeof(VkCommandBuffer) * vulkWin->image_count);

    VkCommandBufferAllocateInfo allocInfo = { 0 };
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = RGFW_vulkan_info.command_pool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (u32) vulkWin->image_count;

    if (vkAllocateCommandBuffers(RGFW_vulkan_info.device, &allocInfo, RGFW_vulkan_info.command_buffers) != VK_SUCCESS) {
        return -1; // failed to allocate command buffers;
    }

    return 0;
}

int RGFW_createSyncObjects(RGFW_window_vulkanInfo* vulkWin) {
    assert(vulkWin != NULL);

    RGFW_vulkan_info.available_semaphores = (VkSemaphore*) malloc(sizeof(VkSemaphore) * RGFW_MAX_FRAMES_IN_FLIGHT);
    RGFW_vulkan_info.finished_semaphore = (VkSemaphore*) malloc(sizeof(VkSemaphore) * RGFW_MAX_FRAMES_IN_FLIGHT);
    RGFW_vulkan_info.in_flight_fences = (VkFence*) malloc(sizeof(VkFence) * RGFW_MAX_FRAMES_IN_FLIGHT);
    RGFW_vulkan_info.image_in_flight = (VkFence*) malloc(sizeof(VkFence) * vulkWin->image_count);

    VkSemaphoreCreateInfo semaphore_info = { 0 };
    semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fence_info = { 0 };
    fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < RGFW_MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(RGFW_vulkan_info.device, &semaphore_info, NULL, &RGFW_vulkan_info.available_semaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(RGFW_vulkan_info.device, &semaphore_info, NULL, &RGFW_vulkan_info.finished_semaphore[i]) != VK_SUCCESS ||
            vkCreateFence(RGFW_vulkan_info.device, &fence_info, NULL, &RGFW_vulkan_info.in_flight_fences[i]) != VK_SUCCESS) {
            fprintf(stderr, "failed to create sync objects\n");
            return -1; // failed to create synchronization objects for a frame
        }
    }

    for (size_t i = 0; i < vulkWin->image_count; i++) {
        RGFW_vulkan_info.image_in_flight[i] = VK_NULL_HANDLE;
    }

    return 0;
}

int RGFW_createFramebuffers(RGFW_window* win, RGFW_window_vulkanInfo* vulkWin) {
    assert(vulkWin != NULL);

    RGFW_vulkan_info.framebuffers = (VkFramebuffer*) malloc(sizeof(VkFramebuffer) * vulkWin->image_count);

    for (size_t i = 0; i < vulkWin->image_count; i++) {
        VkImageView attachments[] = { vulkWin->swapchain_image_views[i] };

        VkFramebufferCreateInfo framebuffer_info = { 0 };
        framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebuffer_info.renderPass = RGFW_vulkan_info.render_pass;
        framebuffer_info.attachmentCount = 1;
        framebuffer_info.pAttachments = attachments;
        framebuffer_info.width = win->r.w;
        framebuffer_info.height = win->r.h;
        framebuffer_info.layers = 1;

        if (vkCreateFramebuffer(RGFW_vulkan_info.device, &framebuffer_info, NULL, &RGFW_vulkan_info.framebuffers[i]) != VK_SUCCESS) {
            return -1; // failed to create framebuffer
        }
    }
    return 0;
}

void RGFW_freeVulkan(RGFW_window_vulkanInfo* vulkWin) {
    for (u32 i = 0; i < vulkWin->image_count; i++) {
        vkDestroyImageView(RGFW_vulkan_info.device, vulkWin->swapchain_image_views[i], NULL);
    }

    for (u32 i = 0; i < vulkWin->image_count; i++) {
        vkDestroyFramebuffer(RGFW_vulkan_info.device, RGFW_vulkan_info.framebuffers[i], NULL);
    }

    vkDestroySwapchainKHR(RGFW_vulkan_info.device, vulkWin->swapchain, NULL);
    vkDestroySurfaceKHR(RGFW_vulkan_info.instance, vulkWin->rSurf, NULL);
    free(vulkWin->swapchain_image_views);
    free(vulkWin->swapchain_images);

    vkDeviceWaitIdle(RGFW_vulkan_info.device);

    for (size_t i = 0; i < RGFW_MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(RGFW_vulkan_info.device, RGFW_vulkan_info.finished_semaphore[i], NULL);
        vkDestroySemaphore(RGFW_vulkan_info.device, RGFW_vulkan_info.available_semaphores[i], NULL);
        vkDestroyFence(RGFW_vulkan_info.device, RGFW_vulkan_info.in_flight_fences[i], NULL);
    }

    vkDestroyCommandPool(RGFW_vulkan_info.device, RGFW_vulkan_info.command_pool, NULL);

    vkDestroyPipeline(RGFW_vulkan_info.device, RGFW_vulkan_info.graphics_pipeline, NULL);
    vkDestroyPipelineLayout(RGFW_vulkan_info.device, RGFW_vulkan_info.pipeline_layout, NULL);
    vkDestroyRenderPass(RGFW_vulkan_info.device, RGFW_vulkan_info.render_pass, NULL);

#ifdef RGFW_DEBUG_VULKAN
    printf("RGFW_DEBUG_VULKAN is defined");
    PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(RGFW_vulkan_info.instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != NULL) {
        func(RGFW_vulkan_info.instance, RGFW_vulkan_info.debugMessenger, NULL);
    }
#endif

    vkDestroyDevice(RGFW_vulkan_info.device, NULL);
    vkDestroyInstance(RGFW_vulkan_info.instance, NULL);

    free(RGFW_vulkan_info.framebuffers);
    free(RGFW_vulkan_info.command_buffers);
    free(RGFW_vulkan_info.available_semaphores);
    free(RGFW_vulkan_info.finished_semaphore);
    free(RGFW_vulkan_info.in_flight_fences);
    free(RGFW_vulkan_info.image_in_flight);
}

VkShaderModule RGFW_createShaderModule(const u32* code, size_t code_size) {
    VkShaderModuleCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.codeSize = code_size;
    create_info.pCode = code;

    VkShaderModule shaderModule;
    if (RGFW_vulkan_info.device == NULL || vkCreateShaderModule(RGFW_vulkan_info.device, &create_info, NULL, &shaderModule) != VK_SUCCESS) {
        return VK_NULL_HANDLE;
    }

    return shaderModule;
}
#endif
