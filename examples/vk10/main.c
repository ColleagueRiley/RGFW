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


const int MAX_FRAMES_IN_FLIGHT = 2;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

#ifdef NDEBUG
const int enableValidationLayers = 0;
#else
const int enableValidationLayers = 1;
#endif
const char* validation_layer_name[] = {"VK_LAYER_KHRONOS_validation"};

const char* device_extensions[] = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    printf( "validation layer: %s\n", pCallbackData->pMessage);

    return VK_FALSE;
}

static struct {
    RGFW_window* window;
    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physical_device;
    VkDevice device;

    uint32_t graphics_family_index;
    uint32_t present_family_index;

    struct {
        VkSwapchainKHR swapchain;
        uint32_t image_count;
        VkFormat image_format;
        VkColorSpaceKHR color_space;
        VkImageUsageFlags image_usage_flags;
        VkExtent2D extent;
        uint32_t requested_min_image_count;
        VkPresentModeKHR present_mode;
        VkImage* swapchain_images;
        VkImageView* swapchain_image_views;
    } swapchain;

    VkDebugUtilsMessengerEXT debugMessenger;
} init;

static struct {
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
} data;

int init_data() {
    init.swapchain.swapchain = VK_NULL_HANDLE;
    init.swapchain.image_count = 0;
    init.swapchain.image_format = VK_FORMAT_B8G8R8A8_SRGB; // The image format actually used when creating the swapchain.
    init.swapchain.color_space = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR; // The color space actually used when creating the swapchain.
    init.swapchain.image_usage_flags = 0;
    init.swapchain.extent.width = SCR_WIDTH;
    init.swapchain.extent.height = SCR_HEIGHT;
    init.swapchain.requested_min_image_count = 0;
    init.swapchain.present_mode = VK_PRESENT_MODE_FIFO_KHR;

    data.current_frame = 0;

    return 0;
}

RGFW_window* create_window_rgfw(const char* window_name) {
    return RGFW_createWindow( "Vulkan", SCR_WIDTH, SCR_HEIGHT, SCR_WIDTH, SCR_HEIGHT, RGFW_ALLOW_DND | RGFW_CENTER);
}

void destroy_window_rgfw(RGFW_window* window) {
    RGFW_window_close(window);
}

VkSurfaceKHR create_surface_rgfw(VkInstance instance, RGFW_window* window) {
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    RGFW_initVulkan(window, instance);
    surface = (VkSurfaceKHR)window->rSurf;
    
    if (surface == VK_NULL_HANDLE) {
        printf("failed to create shader module\n");
        exit(0);
    }

    return surface;
}

int device_initialization() {
    init.window = create_window_rgfw("Vulkan Triangle");

    VkApplicationInfo appInfo = { 0 };
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    uint32_t rgfwExtensionCount = 2;
    const char* rgfwExtensions[2] = {
        {"VK_KHR_surface"},
#ifdef RGFW_WINDOWS
        {"VK_KHR_win32_surface"},
#elif defined(RGFW_RGFW_X11)
        {"VK_KHR_xlib_surface"},
#elif (defined(__APPLE__) && !defined(RGFW_MACOS_X11))
        {"VK_MVK_macos_surface"},
#endif
    };

    const char** extensions;
    uint32_t extension_count;
    if (enableValidationLayers) {
        extension_count = rgfwExtensionCount + 1;
        extensions = (const char**)malloc(sizeof(const char*) * extension_count);
        for (int i = 0; i < rgfwExtensionCount; i++) {
            extensions[i] = rgfwExtensions[i];
        }
        extensions[extension_count - 1] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
    } else {
        extension_count = rgfwExtensionCount;
        extensions = rgfwExtensions;
    }

    VkInstanceCreateInfo instance_create_info = {0};
    instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_create_info.pApplicationInfo = &appInfo;
    instance_create_info.enabledExtensionCount = extension_count;
    instance_create_info.ppEnabledExtensionNames = extensions;

    if (enableValidationLayers) {
        VkDebugUtilsMessengerCreateInfoEXT debug_create_info = {0};
        debug_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debug_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debug_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debug_create_info.pfnUserCallback = debugCallback;

        instance_create_info.enabledLayerCount = 1;
        instance_create_info.ppEnabledLayerNames = validation_layer_name;
        instance_create_info.pNext = &debug_create_info;
    } else {
        instance_create_info.enabledLayerCount = 0;
    }

    if (vkCreateInstance(&instance_create_info, NULL, &init.instance) != VK_SUCCESS) {
        printf("failed to create instance!\n");
        return -1;
    }

    // setup debug messenger
    if (enableValidationLayers) {
        VkDebugUtilsMessengerCreateInfoEXT debug_create_info = {0};
        debug_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debug_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debug_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debug_create_info.pfnUserCallback = debugCallback;

        PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(init.instance, "vkCreateDebugUtilsMessengerEXT");
        if (func == NULL) {
            printf("vkCreateDebugUtilsMessengerEXT not found!\n");
            return -1;
        } else {
            if (func(init.instance, &debug_create_info, NULL, &init.debugMessenger) != VK_SUCCESS) {
                printf("failed to set up debug messenger!\n");
                return -1;
            }
        }
    }

    init.surface = create_surface_rgfw(init.instance, init.window);

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(init.instance, &deviceCount, NULL);
    VkPhysicalDevice* devices = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * deviceCount);
    vkEnumeratePhysicalDevices(init.instance, &deviceCount, devices);

    init.physical_device = devices[0];

    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(init.physical_device, &queue_family_count, NULL);
    VkQueueFamilyProperties* queueFamilies = (VkQueueFamilyProperties*)malloc(sizeof(VkQueueFamilyProperties) * queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(init.physical_device, &queue_family_count, queueFamilies);

    VkBool32 graphics_family_index_found = 0;
    for (int i = 0; i < queue_family_count; i++) {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            init.graphics_family_index = i;
            graphics_family_index_found = 1;
            break;
        }
    }
    if (!graphics_family_index_found) {
        printf("failed to found graphics family index!\n");
        return -1;
    }

    VkBool32 present_family_index_found = 0;
    for (int i = 0; i < queue_family_count; i++) {
        VkBool32 present_support = 0;
        vkGetPhysicalDeviceSurfaceSupportKHR(init.physical_device, i, init.surface, &present_support);

        if (present_support) {
            init.present_family_index = i;
            present_family_index_found = 1;
            break;
        }
    }
    if (!present_family_index_found) {
        printf("failed to found present family index!\n");
        //return -1;
    }

    float queuePriority = 1.0f;

    VkPhysicalDeviceFeatures device_features = {0};

    VkDeviceCreateInfo device_create_info = {0};
    device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    if (init.graphics_family_index != init.present_family_index) {
        VkDeviceQueueCreateInfo queue_create_infos[2] = {
            {0},
            {0},
        };
        queue_create_infos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_infos[0].queueFamilyIndex = init.graphics_family_index;
        queue_create_infos[0].queueCount = 1;
        queue_create_infos[0].pQueuePriorities = &queuePriority;
        queue_create_infos[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_infos[1].queueFamilyIndex = init.present_family_index;
        queue_create_infos[1].queueCount = 1;
        queue_create_infos[1].pQueuePriorities = &queuePriority;
        device_create_info.queueCreateInfoCount = 2;
        device_create_info.pQueueCreateInfos = queue_create_infos;
    } else {
        VkDeviceQueueCreateInfo queue_create_infos[1] = {
            {0}
        };
        queue_create_infos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_infos[0].queueFamilyIndex = init.graphics_family_index;
        queue_create_infos[0].queueCount = 1;
        queue_create_infos[0].pQueuePriorities = &queuePriority;
        device_create_info.queueCreateInfoCount = 1;
        device_create_info.pQueueCreateInfos = queue_create_infos;
    }

    device_create_info.enabledExtensionCount = 1;
    device_create_info.ppEnabledExtensionNames = device_extensions;
    if (enableValidationLayers) {
        device_create_info.enabledLayerCount = 1;
        device_create_info.ppEnabledLayerNames = validation_layer_name;
    } else {
        device_create_info.enabledLayerCount = 0;
    }
    device_create_info.pEnabledFeatures = &device_features;

    if (vkCreateDevice(init.physical_device, &device_create_info, NULL, &init.device) != VK_SUCCESS) {
        printf("failed to create logical device!\n");
        return -1;
    }

    return 0;
}

int create_swapchain() {
    VkSurfaceFormatKHR surfaceFormat = { init.swapchain.image_format, init.swapchain.color_space };
    VkPresentModeKHR presentMode = init.swapchain.present_mode;
    VkExtent2D extent = init.swapchain.extent;

    VkSurfaceCapabilitiesKHR capabilities = {0};
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(init.physical_device, init.surface, &capabilities);

    init.swapchain.requested_min_image_count = capabilities.minImageCount;
    init.swapchain.image_count = capabilities.minImageCount + 1;
    if (capabilities.maxImageCount > 0 && init.swapchain.image_count > capabilities.maxImageCount) {
        init.swapchain.image_count = capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR swapchain_create_info = {0};
    swapchain_create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchain_create_info.surface = init.surface;
    swapchain_create_info.minImageCount = init.swapchain.image_count;
    swapchain_create_info.imageFormat = surfaceFormat.format;
    swapchain_create_info.imageColorSpace = surfaceFormat.colorSpace;
    swapchain_create_info.imageExtent = extent;
    swapchain_create_info.imageArrayLayers = 1;
    swapchain_create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    uint32_t queue_family_indices[] = { init.graphics_family_index, init.present_family_index };
    if (init.graphics_family_index != init.present_family_index) {
        swapchain_create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        swapchain_create_info.queueFamilyIndexCount = 2;
        swapchain_create_info.pQueueFamilyIndices = queue_family_indices;
    } else {
        swapchain_create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }
    swapchain_create_info.preTransform = capabilities.currentTransform;
    swapchain_create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchain_create_info.presentMode = presentMode;
    swapchain_create_info.clipped = VK_TRUE;
    swapchain_create_info.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(init.device, &swapchain_create_info, NULL, &init.swapchain.swapchain) != VK_SUCCESS) {
        printf("failed to create swap chain!\n");
        return -1;
    }

    uint32_t imageCount;
    vkGetSwapchainImagesKHR(init.device, init.swapchain.swapchain, &imageCount, NULL);
    init.swapchain.swapchain_images = (VkImage*)malloc(sizeof(VkImage) * imageCount);
    vkGetSwapchainImagesKHR(init.device, init.swapchain.swapchain, &imageCount, init.swapchain.swapchain_images);

    init.swapchain.swapchain_image_views = (VkImageView*)malloc(sizeof(VkImageView) * imageCount);
    for(uint32_t i=0; i < imageCount; i++){
        VkImageViewCreateInfo image_view_cre_infos = {0};
        image_view_cre_infos.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        image_view_cre_infos.image = init.swapchain.swapchain_images[i];
        image_view_cre_infos.viewType =VK_IMAGE_VIEW_TYPE_2D;
        image_view_cre_infos.format = init.swapchain.image_format;
        image_view_cre_infos.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_cre_infos.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_cre_infos.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_cre_infos.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_cre_infos.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        image_view_cre_infos.subresourceRange.baseMipLevel = 0;
        image_view_cre_infos.subresourceRange.levelCount = 1;
        image_view_cre_infos.subresourceRange.baseArrayLayer = 0;
        image_view_cre_infos.subresourceRange.layerCount = 1;
        if (vkCreateImageView(init.device, &image_view_cre_infos, NULL, &init.swapchain.swapchain_image_views[i]) != VK_SUCCESS) {
            printf("failed to create image views!");
            return -1;
        }
    }

    return 0;
}

int get_queues() {
    vkGetDeviceQueue(init.device, init.graphics_family_index, 0, &data.graphics_queue);
    vkGetDeviceQueue(init.device, init.present_family_index, 0, &data.present_queue);

    return 0;
}

int create_render_pass() {
    VkAttachmentDescription color_attachment = {0};
    color_attachment.format = init.swapchain.image_format;
    color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
    color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference color_attachment_ref = {0};
    color_attachment_ref.attachment = 0;
    color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {0};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &color_attachment_ref;

    VkSubpassDependency dependency = {0};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo render_pass_info = {0};
    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    render_pass_info.attachmentCount = 1;
    render_pass_info.pAttachments = &color_attachment;
    render_pass_info.subpassCount = 1;
    render_pass_info.pSubpasses = &subpass;
    render_pass_info.dependencyCount = 1;
    render_pass_info.pDependencies = &dependency;

    if (vkCreateRenderPass(init.device, &render_pass_info, NULL, &data.render_pass) != VK_SUCCESS) {
        printf("failed to create render pass\n");
        return -1; // failed to create render pass!
    }
    return 0;
}

VkShaderModule createShaderModule(const uint32_t* code, size_t code_size) {
    VkShaderModuleCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.codeSize = code_size;
    create_info.pCode = code;

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(init.device, &create_info, NULL, &shaderModule) != VK_SUCCESS) {
        return VK_NULL_HANDLE; // failed to create shader module
    }

    return shaderModule;
}

int create_graphics_pipeline() {
    size_t vert_fileSize = sizeof(vert_code);
    size_t frag_fileSize = sizeof(frag_code);

    VkShaderModule vert_module = createShaderModule(vert_code, vert_fileSize);
    VkShaderModule frag_module = createShaderModule(frag_code, frag_fileSize);
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
    viewport.width = (float)init.swapchain.extent.width;
    viewport.height = (float)init.swapchain.extent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor;
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent = init.swapchain.extent;

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

    if (vkCreatePipelineLayout(init.device, &pipeline_layout_info, NULL, &data.pipeline_layout) != VK_SUCCESS) {
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
    pipeline_info.layout = data.pipeline_layout;
    pipeline_info.renderPass = data.render_pass;
    pipeline_info.subpass = 0;
    pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

    if (vkCreateGraphicsPipelines(init.device, VK_NULL_HANDLE, 1, &pipeline_info, NULL, &data.graphics_pipeline) != VK_SUCCESS) {
        printf("failed to create pipline\n");
        return -1; // failed to create graphics pipeline
    }

    vkDestroyShaderModule(init.device, frag_module, NULL);
    vkDestroyShaderModule(init.device, vert_module, NULL);
    return 0;
}

int create_framebuffers() {
    data.framebuffers = (VkFramebuffer*)malloc(sizeof(VkFramebuffer) * init.swapchain.image_count);

    for (size_t i = 0; i < init.swapchain.image_count; i++) {
        VkImageView attachments[] = { init.swapchain.swapchain_image_views[i] };

        VkFramebufferCreateInfo framebuffer_info = {0};
        framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebuffer_info.renderPass = data.render_pass;
        framebuffer_info.attachmentCount = 1;
        framebuffer_info.pAttachments = attachments;
        framebuffer_info.width = init.swapchain.extent.width;
        framebuffer_info.height = init.swapchain.extent.height;
        framebuffer_info.layers = 1;

        if (vkCreateFramebuffer(init.device, &framebuffer_info, NULL, &data.framebuffers[i]) != VK_SUCCESS) {
            return -1; // failed to create framebuffer
        }
    }
    return 0;
}

int create_command_pool() {
    VkCommandPoolCreateInfo pool_info = {0};
    pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pool_info.queueFamilyIndex = 0;

    if (vkCreateCommandPool(init.device, &pool_info, NULL, &data.command_pool) != VK_SUCCESS) {
        printf("failed to create command pool\n");
        return -1; // failed to create command pool
    }
    return 0;
}

int create_command_buffers() {
    data.command_buffers = (VkCommandBuffer*)malloc(sizeof(VkCommandBuffer) * init.swapchain.image_count);

    VkCommandBufferAllocateInfo allocInfo = {0};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = data.command_pool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)init.swapchain.image_count;

    if (vkAllocateCommandBuffers(init.device, &allocInfo, data.command_buffers) != VK_SUCCESS) {
        return -1; // failed to allocate command buffers;
    }

    for (size_t i = 0; i < init.swapchain.image_count; i++) {
        VkCommandBufferBeginInfo begin_info = {0};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(data.command_buffers[i], &begin_info) != VK_SUCCESS) {
            return -1; // failed to begin recording command buffer
        }

        VkRenderPassBeginInfo render_pass_info = {0};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_info.renderPass = data.render_pass;
        render_pass_info.framebuffer = data.framebuffers[i];
        render_pass_info.renderArea.offset.x = 0;
        render_pass_info.renderArea.offset.y = 0;
        render_pass_info.renderArea.extent = init.swapchain.extent;
        VkClearValue clearColor;
        clearColor.color.float32[0] = 0.0f;
        clearColor.color.float32[1] = 0.0f;
        clearColor.color.float32[2] = 0.0f;
        clearColor.color.float32[3] = 1.0f;
        render_pass_info.clearValueCount = 1;
        render_pass_info.pClearValues = &clearColor;

        VkViewport viewport;
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)init.swapchain.extent.width;
        viewport.height = (float)init.swapchain.extent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor;
        scissor.offset.x = 0;
        scissor.offset.y = 0;
        scissor.extent = init.swapchain.extent;

        vkCmdSetViewport(data.command_buffers[i], 0, 1, &viewport);
        vkCmdSetScissor(data.command_buffers[i], 0, 1, &scissor);

        vkCmdBeginRenderPass(data.command_buffers[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(data.command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, data.graphics_pipeline);

        vkCmdDraw(data.command_buffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(data.command_buffers[i]);

        if (vkEndCommandBuffer(data.command_buffers[i]) != VK_SUCCESS) {
            printf("failed to record command buffer\n");
            return -1; // failed to record command buffer!
        }
    }
    return 0;
}

int create_sync_objects() {
    data.available_semaphores = (VkSemaphore*)malloc(sizeof(VkSemaphore) * MAX_FRAMES_IN_FLIGHT);
    data.finished_semaphore = (VkSemaphore*)malloc(sizeof(VkSemaphore) * MAX_FRAMES_IN_FLIGHT);
    data.in_flight_fences = (VkFence*)malloc(sizeof(VkFence) * MAX_FRAMES_IN_FLIGHT);
    data.image_in_flight = (VkFence*)malloc(sizeof(VkFence) * init.swapchain.image_count);

    VkSemaphoreCreateInfo semaphore_info = {0};
    semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fence_info = {0};
    fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(init.device, &semaphore_info, NULL, &data.available_semaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(init.device, &semaphore_info, NULL, &data.finished_semaphore[i]) != VK_SUCCESS ||
            vkCreateFence(init.device, &fence_info, NULL, &data.in_flight_fences[i]) != VK_SUCCESS) {
            printf("failed to create sync objects\n");
            return -1; // failed to create synchronization objects for a frame
        }
    }

    for (size_t i = 0; i < init.swapchain.image_count; i++) {
        data.image_in_flight[i] = VK_NULL_HANDLE;
    }

    return 0;
}

int recreate_swapchain() {
    vkDeviceWaitIdle(init.device);

    vkDestroyCommandPool(init.device, data.command_pool, NULL);

    for (int i = 0; i < init.swapchain.image_count; i++) {
        vkDestroyFramebuffer(init.device, data.framebuffers[i], NULL);
    }

    for (int i = 0; i < init.swapchain.image_count; i++) {
        vkDestroyImageView(init.device, init.swapchain.swapchain_image_views[i], NULL);
    }

    if (0 != create_swapchain()) return -1;
    if (0 != create_framebuffers()) return -1;
    if (0 != create_command_pool()) return -1;
    if (0 != create_command_buffers()) return -1;
    return 0;
}

int draw_frame() {
    vkWaitForFences(init.device, 1, &data.in_flight_fences[data.current_frame], VK_TRUE, UINT64_MAX);

    uint32_t image_index = 0;
    VkResult result = vkAcquireNextImageKHR(init.device, init.swapchain.swapchain, UINT64_MAX, data.available_semaphores[data.current_frame], VK_NULL_HANDLE, &image_index);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        return recreate_swapchain();
    } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        printf("failed to acquire swapchain image. Error %i\n", result);
        return -1;
    }

    if (data.image_in_flight[image_index] != VK_NULL_HANDLE) {
        vkWaitForFences(init.device, 1, &data.image_in_flight[image_index], VK_TRUE, UINT64_MAX);
    }
    data.image_in_flight[image_index] = data.in_flight_fences[data.current_frame];

    VkSubmitInfo submitInfo = {0};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore wait_semaphores[] = { data.available_semaphores[data.current_frame] };
    VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = wait_semaphores;
    submitInfo.pWaitDstStageMask = wait_stages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &data.command_buffers[image_index];

    VkSemaphore signal_semaphores[] = { data.finished_semaphore[data.current_frame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signal_semaphores;

    vkResetFences(init.device, 1, &data.in_flight_fences[data.current_frame]);

    if (vkQueueSubmit(data.graphics_queue, 1, &submitInfo, data.in_flight_fences[data.current_frame]) != VK_SUCCESS) {
        printf("failed to submit draw command buffer\n");
        return -1; //"failed to submit draw command buffer
    }

    VkPresentInfoKHR present_info = {0};
    present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    present_info.waitSemaphoreCount = 1;
    present_info.pWaitSemaphores = signal_semaphores;

    VkSwapchainKHR swapChains[] = { init.swapchain.swapchain };
    present_info.swapchainCount = 1;
    present_info.pSwapchains = swapChains;

    present_info.pImageIndices = &image_index;

    result = vkQueuePresentKHR(data.present_queue, &present_info);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
        return recreate_swapchain();
    } else if (result != VK_SUCCESS) {
        printf("failed to present swapchain image\n");
        return -1;
    }

    data.current_frame = (data.current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
    return 0;
}

void cleanup() {
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(init.device, data.finished_semaphore[i], NULL);
        vkDestroySemaphore(init.device, data.available_semaphores[i], NULL);
        vkDestroyFence(init.device, data.in_flight_fences[i], NULL);
    }

    vkDestroyCommandPool(init.device, data.command_pool, NULL);

    for (int i = 0; i < init.swapchain.image_count; i++) {
        vkDestroyFramebuffer(init.device, data.framebuffers[i], NULL);
    }

    vkDestroyPipeline(init.device, data.graphics_pipeline, NULL);
    vkDestroyPipelineLayout(init.device, data.pipeline_layout, NULL);
    vkDestroyRenderPass(init.device, data.render_pass, NULL);

    for (int i = 0; i < init.swapchain.image_count; i++) {
        vkDestroyImageView(init.device, init.swapchain.swapchain_image_views[i], NULL);
    }

    vkDestroySwapchainKHR(init.device, init.swapchain.swapchain, NULL);
    vkDestroyDevice(init.device, NULL);
    vkDestroySurfaceKHR(init.instance, init.surface, NULL);
    if (enableValidationLayers) {
        PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(init.instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != NULL) {
            func(init.instance, init.debugMessenger, NULL);
        }
    }
    vkDestroyInstance(init.instance, NULL);
    destroy_window_rgfw(init.window);

    free(init.swapchain.swapchain_image_views);
    free(init.swapchain.swapchain_images);

    free(data.framebuffers);
    free(data.command_buffers);
    free(data.available_semaphores);
    free(data.finished_semaphore);
    free(data.in_flight_fences);
    free(data.image_in_flight);
}

int main() {

    if (0 != init_data()) return -1;
    if (0 != device_initialization()) return -1;
    if (0 != create_swapchain()) return -1;
    if (0 != get_queues()) return -1;
    if (0 != create_render_pass()) return -1;
    if (0 != create_graphics_pipeline()) return -1;
    if (0 != create_framebuffers()) return -1;
    if (0 != create_command_pool()) return -1;
    if (0 != create_command_buffers()) return -1;
    if (0 != create_sync_objects()) return -1;

    uint32_t running = 1;
    while (running && !RGFW_isPressedI(init.window, RGFW_Escape)) {
        while (RGFW_window_checkEvent(init.window)) {
            if (init.window->event.type == RGFW_quit) {
                running = 0;
                break;
            }
        }

        if (running) {
            int res = draw_frame();
            if (res != 0) {
                printf("failed to draw frame \n");
                return -1;
            }
        }
    }
    vkDeviceWaitIdle(init.device);

    cleanup();
    return 0;
}
