#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define RGFW_VULKAN
#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS

#include "RGFW.h"

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include "vert.h"
#include "frag.h"

static RGFW_window window = {0};

typedef struct Mat4 {
	float f[4][4];
} Mat4;

static inline Mat4 mat4Ident(void)
{
	Mat4 result = {0};
	result.f[0][0] = 1.0f;
	result.f[1][1] = 1.0f;
	result.f[2][2] = 1.0f;
	result.f[3][3] = 1.0f;
	return result;
}

static inline Mat4 mat4Mul(Mat4 x, Mat4 y)
{
	Mat4 result;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.f[i][j] = x.f[i][0] * y.f[0][j] +
				         x.f[i][1] * y.f[1][j] +
				         x.f[i][2] * y.f[2][j] +
				         x.f[i][3] * y.f[3][j];
	return result;
}

static inline Mat4 mat4EulerX(float theta)
{
	Mat4 result = mat4Ident();
	float sin = sinf(theta);
	float cos = cosf(theta);
	result.f[1][1] = cos;
	result.f[1][2] = sin;
	result.f[2][1] = -sin;
	result.f[2][2] = cos;
	return result;
}

static inline Mat4 mat4EulerY(float theta)
{
	Mat4 result = mat4Ident();
	float sin = sinf(theta);
	float cos = cosf(theta);
	result.f[0][0] = cos;
	result.f[0][2] = -sin;
	result.f[2][0] = sin;
	result.f[2][2] = cos;
	return result;
}

static inline Mat4 mat4EulerZ(float theta)
{
	Mat4 result = mat4Ident();
	float sin = sinf(theta);
	float cos = cosf(theta);
	result.f[0][0] = cos;
	result.f[0][1] = sin;
	result.f[1][0] = -sin;
	result.f[1][1] = cos;
	return result;
}

static inline Mat4 mat4Perspective(float fov, float aspect_ratio, float near, float far)
{
	Mat4 result = {0};
	float scale = tan(fov * 0.5f);
	result.f[0][0] = 1.0f / (aspect_ratio * scale);
	result.f[1][1] = -(1.0f / scale);
	result.f[2][2] = far / (far - near);
	result.f[2][3] = -((far * near) / (far - near));
	result.f[3][2] = 1.0f;
	return result;
}

static struct {
	VkInstance instance;
	VkPhysicalDevice physical_device;
	VkDevice device;

	u32 queue_index_count;
	union {
		u32 u[4];
		struct {
			u32 graphics;
			u32 present;
			u32 transfer;
			u32 compute;
		} queue;
	} queues;
	VkQueue graphics_queue;
	VkQueue present_queue;
	VkQueue transfer_queue;

	VkRenderPass renderpass;

	VkDescriptorSetLayout descriptor_layout;
	VkDescriptorPool descriptor_pool;
	VkDescriptorSet descriptor_set;
	VkPipelineLayout pipeline_layout;

	VkPipeline pipeline;

	VkSurfaceKHR surface;
	VkSwapchainKHR swapchain;

	u32 image_index;
	u32 current_frame;
	u32 image_count;
	u32 memory_index;
	VkCommandPool graphics_command_pool;
	VkCommandBuffer cmd[4];
	VkCommandPool transfer_command_pool;
	VkCommandBuffer transfer_cmd;

	VkFence fences[4];
	VkFence images_in_flight[4];
	VkSemaphore image_semaphores[4];
	VkSemaphore submit_semaphores[4];

	VkImage swapchain_images[4];
	VkImage depth_image;
	VkDeviceMemory depth_image_memory;
	VkImageView depth_image_view;
	VkImageView swapchain_image_views[4];
	VkFormat color_format;
	VkFormat depth_format;
	VkFramebuffer framebuffers[4];

	VkImage texture_image;
	VkDeviceMemory texture_memory;
	VkImageView texture_image_view;
	VkSampler texture_sampler;
	VkBuffer texture_buffer;

	int exclusive;
	i32 w;
	i32 h;
	u32 format_count;

	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceMemoryProperties memory_properties;
	VkPhysicalDeviceFeatures features;
	VkSurfaceCapabilitiesKHR capabilities;
} vk = {0};

int vulkanResultCheck(VkResult result)
{
	switch (result) {
		case VK_SUCCESS:
		case VK_NOT_READY:
		case VK_TIMEOUT:
		case VK_EVENT_SET:
		case VK_EVENT_RESET:
		case VK_SUBOPTIMAL_KHR:
		case VK_THREAD_IDLE_KHR:
		case VK_THREAD_DONE_KHR:
		case VK_OPERATION_DEFERRED_KHR:
		case VK_OPERATION_NOT_DEFERRED_KHR:
		case VK_PIPELINE_COMPILE_REQUIRED_EXT:
			return 1;
		default:
			return 0;
	}
}

#define VK_CHECK(f)\
	do {\
		VkResult result = (f);\
		if (vulkanResultCheck(result) == 0) {\
			fprintf(stderr, "'%s' returned error code %d\n", #f, result);\
			fflush(stderr);\
		}\
	} while (0)

typedef struct QueueFamilies {
	struct {
		int graphics, present, transfer, compute;
		int count;
		int used_queue_count;
	} pQueues[4];
	int graphics_index, present_index, transfer_index, compute_index;
	int queue_index_count;
} QueueFamilies;

// i copied this function from another project
static QueueFamilies getQueueFamilies(VkInstance instance, VkPhysicalDevice physical_device)
{
	// output queue families
	QueueFamilies queue_families = {0};
	queue_families.graphics_index = -1;
	queue_families.present_index = -1;
	queue_families.transfer_index = -1;
	queue_families.compute_index = -1;

	// number of available queue families
	u32 count = 0;

	// 16 should be more than enough
	VkQueueFamilyProperties properties[16] = {0};

	vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, NULL);
	vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, properties);

	if (count > 16)
		count = 16;

	for (int i = 0; i < count - 1; i++) {
		if (properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			queue_families.pQueues[i].graphics = 1;
			queue_families.pQueues[i].count++;
		}
		if (properties[i].queueFlags & VK_QUEUE_TRANSFER_BIT) {
			queue_families.pQueues[i].transfer = 1;
			queue_families.pQueues[i].count++;
		}
		if (properties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
			queue_families.pQueues[i].compute = 1;
			queue_families.pQueues[i].count++;
		}
		if (RGFW_getPresentationSupport_Vulkan(vk.instance, physical_device, i)) {
			queue_families.pQueues[i].present = 1;
			queue_families.pQueues[i].count++;
		}

		// change the current graphics/present/transfer/compute queue index to this one if its better (or if it hasent already been set)
		if (queue_families.pQueues[i].graphics && (queue_families.graphics_index == -1 || (queue_families.pQueues[queue_families.graphics_index].count > queue_families.pQueues[i].count)))
			queue_families.graphics_index = i;

		if (queue_families.pQueues[i].present && (queue_families.present_index == -1 || (queue_families.pQueues[queue_families.present_index].count > queue_families.pQueues[i].count)))
			queue_families.present_index = i;

		if (queue_families.pQueues[i].transfer && (queue_families.transfer_index == -1 || (queue_families.pQueues[queue_families.transfer_index].count > queue_families.pQueues[i].count)))
			queue_families.transfer_index = i;

		if (queue_families.pQueues[i].compute && (queue_families.compute_index == -1 || (queue_families.pQueues[queue_families.compute_index].count > queue_families.pQueues[i].count)))
			queue_families.compute_index = i;

		printf("queue family %d: %d %d %d %d\n", i, queue_families.pQueues[i].graphics, queue_families.pQueues[i].present, queue_families.pQueues[i].transfer, queue_families.pQueues[i].compute);
	}

	i32 indices[4] = {
		queue_families.graphics_index,
		queue_families.present_index,
		queue_families.transfer_index,
		queue_families.compute_index
	};

	// count the unique indices
	for (int i = 0; i < 4; i++) {
		int unique = 1;
		for (int j = 0; j < 4; j++) {
			if (i == j) continue;
			if (indices[i] == indices[j]) unique = 0;
		}
		if (unique) queue_families.queue_index_count++;
	}
	
	queue_families.pQueues[queue_families.graphics_index].used_queue_count += 1;
	queue_families.pQueues[queue_families.present_index].used_queue_count += 1;
	queue_families.pQueues[queue_families.transfer_index].used_queue_count += 1;
	queue_families.pQueues[queue_families.compute_index].used_queue_count += 1;

	// increment it again since it starts at 0
	queue_families.queue_index_count++;

	printf("selected queues: %d: %d %d %d %d\n", queue_families.queue_index_count, queue_families.graphics_index, queue_families.present_index, queue_families.transfer_index, queue_families.compute_index);

	return queue_families;
}

void createSwapchain(VkSurfaceKHR surface, VkPresentModeKHR present_mode)
{
	memset(vk.images_in_flight, 0, sizeof(vk.images_in_flight));
	RGFW_window_getSize(&window, &vk.w, &vk.h);

	vkDeviceWaitIdle(vk.device);
	VkSwapchainCreateInfoKHR swapchain_info = {0};
	swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchain_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchain_info.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	swapchain_info.imageArrayLayers = 1;
	swapchain_info.clipped = VK_TRUE;
	swapchain_info.surface = surface;
	swapchain_info.minImageCount = vk.image_count;
	swapchain_info.imageFormat = vk.color_format;
	swapchain_info.imageExtent.width = vk.w;
	swapchain_info.imageExtent.height = vk.h;
	swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchain_info.queueFamilyIndexCount = vk.queue_index_count;
	swapchain_info.pQueueFamilyIndices = vk.queues.u;
	swapchain_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchain_info.presentMode = present_mode;
	swapchain_info.preTransform = vk.capabilities.currentTransform;
	if (vk.exclusive)
		swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	else
		swapchain_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;

	if (vk.swapchain != VK_NULL_HANDLE) {
		for (int i = 0; i < vk.image_count; i++) {
			vkDestroyFramebuffer(vk.device, vk.framebuffers[i], NULL);
			vkDestroyImageView(vk.device, vk.swapchain_image_views[i], NULL);
		}
		vkDestroyImageView(vk.device, vk.depth_image_view, NULL);
		vkDestroyImage(vk.device, vk.depth_image, NULL);
		vkFreeMemory(vk.device, vk.depth_image_memory, NULL);
		vkDestroySwapchainKHR(vk.device, vk.swapchain, NULL);
	}

	VK_CHECK(vkCreateSwapchainKHR(vk.device, &swapchain_info, NULL, &vk.swapchain));

	VkImageCreateInfo depth_info = {0};
	depth_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	depth_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	depth_info.imageType = VK_IMAGE_TYPE_2D;
	depth_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	depth_info.samples = VK_SAMPLE_COUNT_1_BIT;
	depth_info.tiling = VK_IMAGE_TILING_OPTIMAL;
	depth_info.format = vk.depth_format;
	depth_info.pQueueFamilyIndices = vk.queues.u;
	depth_info.queueFamilyIndexCount = vk.queue_index_count;
	depth_info.sharingMode = swapchain_info.imageSharingMode;
	depth_info.arrayLayers = 1;
	depth_info.mipLevels = 1;
	depth_info.extent.depth = 1;
	depth_info.extent.width = vk.w;
	depth_info.extent.height = vk.h;
	VK_CHECK(vkCreateImage(vk.device, &depth_info, NULL, &vk.depth_image));

	VkMemoryRequirements memory_requirements = {0};
	vkGetImageMemoryRequirements(vk.device, vk.depth_image, &memory_requirements);

	for (int i = 0; i < vk.memory_properties.memoryTypeCount; i++) {
		if (memory_requirements.memoryTypeBits & (1 << i) &&
				(vk.memory_properties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) == VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) {
			vk.memory_index = i;
			break;
		}
	}

	VkMemoryAllocateInfo allocate_info = {0};
	allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocate_info.memoryTypeIndex = vk.memory_index;
	allocate_info.allocationSize = memory_requirements.size;
	VK_CHECK(vkAllocateMemory(vk.device, &allocate_info, NULL, &vk.depth_image_memory));
	VK_CHECK(vkBindImageMemory(vk.device, vk.depth_image, vk.depth_image_memory, 0));

	VkImageViewCreateInfo depth_view_info = {0};
	depth_view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	depth_view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
	depth_view_info.format = vk.depth_format;
	depth_view_info.image = vk.depth_image;
	depth_view_info.components.r = VK_COMPONENT_SWIZZLE_R;
	depth_view_info.components.g = VK_COMPONENT_SWIZZLE_G;
	depth_view_info.components.b = VK_COMPONENT_SWIZZLE_B;
	depth_view_info.components.a = VK_COMPONENT_SWIZZLE_A;
	depth_view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	depth_view_info.subresourceRange.baseArrayLayer = 0;
	depth_view_info.subresourceRange.baseMipLevel = 0;
	depth_view_info.subresourceRange.layerCount = 1;
	depth_view_info.subresourceRange.levelCount = 1;
	VK_CHECK(vkCreateImageView(vk.device, &depth_view_info, NULL, &vk.depth_image_view));

	vkGetSwapchainImagesKHR(vk.device, vk.swapchain, &vk.image_count, vk.swapchain_images);
	for (int i = 0; i < vk.image_count; i++) {
		VkImageViewCreateInfo image_view_info = {0};
		image_view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		image_view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		image_view_info.image = vk.swapchain_images[i];
		image_view_info.components.r = VK_COMPONENT_SWIZZLE_R;
		image_view_info.components.g = VK_COMPONENT_SWIZZLE_G;
		image_view_info.components.b = VK_COMPONENT_SWIZZLE_B;
		image_view_info.components.a = VK_COMPONENT_SWIZZLE_A;
		image_view_info.format = vk.color_format;
		image_view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		image_view_info.subresourceRange.baseArrayLayer = 0;
		image_view_info.subresourceRange.baseMipLevel = 0;
		image_view_info.subresourceRange.layerCount = 1;
		image_view_info.subresourceRange.levelCount = 1;
		VK_CHECK(vkCreateImageView(vk.device, &image_view_info, NULL, &vk.swapchain_image_views[i]));

		VkImageView attachments[2] = {
			vk.swapchain_image_views[i],
			vk.depth_image_view
		};
		VkFramebufferCreateInfo framebuffer_info = {0};
		framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebuffer_info.pAttachments = attachments;
		framebuffer_info.attachmentCount = 2;
		framebuffer_info.width = vk.w;
		framebuffer_info.height = vk.h;
		framebuffer_info.layers = 1;
		framebuffer_info.renderPass = vk.renderpass;
		VK_CHECK(vkCreateFramebuffer(vk.device, &framebuffer_info, NULL, &vk.framebuffers[i]));
	}
}

int main(void)
{
	{
		VkApplicationInfo application_info = {0};
		application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		application_info.pNext = NULL;
		application_info.engineVersion = 1;
		application_info.applicationVersion = 1;
		application_info.apiVersion = VK_API_VERSION_1_0;
		application_info.pApplicationName = "RGFW vulkan 1.0 example";
		application_info.pEngineName = "vulkan";

		const char *extensions[] = {
#ifdef VULKAN_DEBUG
			"VK_EXT_debug_utils",
#endif
			RGFW_VK_SURFACE,
			VK_KHR_SURFACE_EXTENSION_NAME
		};

		const char *const layers[] = {
#ifdef VULKAN_DEBUG
			"VK_LAYER_KHRONOS_validation"
#endif
		};

		VkInstanceCreateInfo instance_info = {0};
		instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instance_info.pApplicationInfo = &application_info;
		instance_info.enabledExtensionCount = sizeof(extensions) / sizeof(extensions[0]);
		instance_info.enabledLayerCount = sizeof(layers) / sizeof(layers[0]);
		instance_info.ppEnabledExtensionNames = extensions;
		instance_info.ppEnabledLayerNames = layers;

		VK_CHECK(vkCreateInstance(&instance_info, NULL, &vk.instance));
	}

	{
		u32 device_count = 0;
		VK_CHECK(vkEnumeratePhysicalDevices(vk.instance, &device_count, NULL));
		static VkPhysicalDevice physical_devices[8]; // 8 should be way more than enough
		VK_CHECK(vkEnumeratePhysicalDevices(vk.instance, &device_count, physical_devices));

		for (int i = 0; i < device_count; i++) {
			vkGetPhysicalDeviceProperties(physical_devices[i], &vk.properties);

			if (vk.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
				vk.physical_device = physical_devices[i];
				break;
			}
		}

		QueueFamilies queue_families = getQueueFamilies(vk.instance, vk.physical_device);
		
		if (queue_families.graphics_index == -1 || queue_families.present_index == -1) {
			vkDestroyInstance(vk.instance, NULL);
			fprintf(stderr, "could not find suitable GPU (please report this bug)\n");
			return EXIT_FAILURE;
		}

		vk.queues.queue.graphics = queue_families.graphics_index;
		vk.queues.queue.present = queue_families.present_index;
		vk.queues.queue.transfer = queue_families.transfer_index;
		vk.queues.queue.compute = queue_families.compute_index;
		vk.queue_index_count = queue_families.queue_index_count;

		VkDeviceQueueCreateInfo queues[3] = {0};
		for (int i = 0; i < 3; i++) {
			queues[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queues[i].queueCount = 1;
			queues[i].pQueuePriorities = (float[]){1.0f};
			queues[i].queueFamilyIndex = vk.queues.u[i];
		}

		if (vk.queues.queue.graphics == vk.queues.queue.present)
			vk.exclusive = 1;

		const char *const extensions[] = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		VkDeviceCreateInfo device_info = {0};
		device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		device_info.enabledExtensionCount = sizeof(extensions) / sizeof(extensions[0]);
		device_info.ppEnabledExtensionNames = extensions;
		device_info.queueCreateInfoCount = vk.queue_index_count;
		device_info.pQueueCreateInfos = queues;

		VK_CHECK(vkCreateDevice(vk.physical_device, &device_info, NULL, &vk.device));
		vkGetDeviceQueue(vk.device, queue_families.graphics_index, 0, &vk.graphics_queue);
		vkGetDeviceQueue(vk.device, queue_families.present_index, 0, &vk.present_queue);
		vkGetDeviceQueue(vk.device, queue_families.transfer_index, 0, &vk.transfer_queue);

		vkGetPhysicalDeviceFeatures(vk.physical_device, &vk.features);
	}

	{
		RGFW_createWindowPtr("Vulkan 1.0 Example", 0, 0, 500, 500, 0, &window);
		VK_CHECK(RGFW_window_createSurface_Vulkan(&window, vk.instance, &vk.surface));
		VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vk.physical_device, vk.surface, &vk.capabilities));
		vkGetPhysicalDeviceMemoryProperties(vk.physical_device, &vk.memory_properties);
		VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(vk.physical_device, vk.surface, &vk.format_count, NULL));

		VkFormat formats[4] = {
			VK_FORMAT_B8G8R8A8_UNORM,
			VK_FORMAT_B8G8R8A8_UINT,
			VK_FORMAT_R8G8B8A8_UNORM,
			VK_FORMAT_R8G8B8A8_UINT
		};

		vk.color_format = VK_FORMAT_UNDEFINED;
		vk.depth_format = VK_FORMAT_UNDEFINED;

		for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); i++) {
			VkFormatProperties properties = {0};
			vkGetPhysicalDeviceFormatProperties(vk.physical_device, formats[i], &properties);
			if (properties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) {
				vk.color_format = formats[i];
				break;
			}
		}

		if (vk.color_format == VK_FORMAT_UNDEFINED) {
			fprintf(stderr, "could not find suitable image format (please report this bug)\n");
			vk.color_format = VK_FORMAT_B8G8R8A8_UNORM;
		}

		const VkFormat depth_formats[5] = {
			VK_FORMAT_D32_SFLOAT,
			VK_FORMAT_D32_SFLOAT_S8_UINT,
			VK_FORMAT_D24_UNORM_S8_UINT,
			VK_FORMAT_D16_UNORM,
			VK_FORMAT_D16_UNORM_S8_UINT
		};

		for (int i = 0; i < sizeof(depth_formats) / sizeof(depth_formats[0]); i++) {
			VkFormatProperties properties = {0};
			vkGetPhysicalDeviceFormatProperties(vk.physical_device, depth_formats[i], &properties);
			if (properties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
				vk.depth_format = depth_formats[i];
				break;
			}
		}

		if (vk.capabilities.minImageCount == 0) {
			vk.image_count = 4;
		}
		else {
			if (vk.capabilities.minImageCount < 4)
				vk.image_count = vk.capabilities.minImageCount + 1;
			else
				vk.image_count = 4;
		}
	}

	{
		VkCommandPoolCreateInfo graphics_pool_info = {0};
		graphics_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		graphics_pool_info.queueFamilyIndex = vk.queues.queue.graphics;
		graphics_pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		VK_CHECK(vkCreateCommandPool(vk.device, &graphics_pool_info, NULL, &vk.graphics_command_pool));

		VkCommandBufferAllocateInfo graphics_cmd_info = {0};
		graphics_cmd_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		graphics_cmd_info.commandBufferCount = vk.image_count;
		graphics_cmd_info.commandPool = vk.graphics_command_pool;
		graphics_cmd_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		VK_CHECK(vkAllocateCommandBuffers(vk.device, &graphics_cmd_info, vk.cmd));

		VkCommandPoolCreateInfo transfer_pool_info = {0};
		transfer_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		transfer_pool_info.queueFamilyIndex = vk.queues.queue.transfer;
		transfer_pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		VK_CHECK(vkCreateCommandPool(vk.device, &transfer_pool_info, NULL, &vk.transfer_command_pool));

		VkCommandBufferAllocateInfo transfer_cmd_info = {0};
		transfer_cmd_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		transfer_cmd_info.commandBufferCount = 1;
		transfer_cmd_info.commandPool = vk.transfer_command_pool;
		transfer_cmd_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		VK_CHECK(vkAllocateCommandBuffers(vk.device, &transfer_cmd_info, &vk.transfer_cmd));

		for (int i = 0; i < vk.image_count; i++) {
			VkFenceCreateInfo fence_info = {0};
			fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
			VK_CHECK(vkCreateFence(vk.device, &fence_info, NULL, &vk.fences[i]));

			VkSemaphoreCreateInfo semaphore_info = {0};
			semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
			VK_CHECK(vkCreateSemaphore(vk.device, &semaphore_info, NULL, &vk.image_semaphores[i]));
			VK_CHECK(vkCreateSemaphore(vk.device, &semaphore_info, NULL, &vk.submit_semaphores[i]));
		}
	}

	{
		VkAttachmentDescription attachments[2] = {0};
		attachments[0].format = vk.color_format;
		attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
		attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference color_reference = {0};
		color_reference.attachment = 0;
		color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkAttachmentReference depth_reference = {0};
		depth_reference.attachment = 1;
		depth_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass = {0};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &color_reference;
		subpass.pDepthStencilAttachment = &depth_reference;

		VkSubpassDependency dependency = {0};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

		attachments[1].format = vk.depth_format;
		attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
		attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkRenderPassCreateInfo renderpass_info = {0};
		renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderpass_info.attachmentCount = 2;
		renderpass_info.pAttachments = attachments;
		renderpass_info.subpassCount = 1;
		renderpass_info.pSubpasses = &subpass;
		renderpass_info.dependencyCount = 1;
		renderpass_info.pDependencies = &dependency;

		VK_CHECK(vkCreateRenderPass(vk.device, &renderpass_info, NULL, &vk.renderpass));
	}

	{
		size_t size = 0;
		char *buf = NULL;
		int skipped_texture = 0;
		FILE *f = fopen("./lonic.raw", "r");
		if (f == NULL)
			f = fopen("./vulkan/lonic.raw", "r");
		if (f == NULL)
			f = fopen("./examples/vulkan/lonic.raw", "r");
		if (f == NULL) {
			printf("./lonic.raw not found (skipping texture)\n");
			buf = (char[4]){
				0xFF, 0xFF, 0xFF, 0xFF,
			};
			skipped_texture = 1;
			size = 4;
		}
		else {
			fseek(f, 0, SEEK_END);
			size = ftell(f);
			fseek(f, 0, SEEK_SET);
			buf = malloc(size);
			size_t b = 0;
			while (b < size)
				b += fread(buf, 1, size, f);
			fclose(f);
		}

		u32 width = sqrt((double)size / 4.0);
		u32 height = width; // assuming the image is a square

		printf("%u %u\n", width, height);

		VkImageCreateInfo image_info = {0};
		image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
		image_info.samples = VK_SAMPLE_COUNT_1_BIT;
		image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		image_info.format = VK_FORMAT_R8G8B8A8_UNORM;
		image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		image_info.imageType = VK_IMAGE_TYPE_2D;
		image_info.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
		image_info.extent.width = width;
		image_info.extent.height = height;
		image_info.extent.depth = 1;
		image_info.mipLevels = 1;
		image_info.arrayLayers = 1;
		VK_CHECK(vkCreateImage(vk.device, &image_info, NULL, &vk.texture_image));

		VkMemoryRequirements memory_requirements = {0};
		vkGetImageMemoryRequirements(vk.device, vk.texture_image, &memory_requirements);
		
		VkMemoryAllocateInfo allocate_info = {0};
		allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocate_info.allocationSize = memory_requirements.size;
		allocate_info.memoryTypeIndex = vk.memory_index;
		VK_CHECK(vkAllocateMemory(vk.device, &allocate_info, NULL, &vk.texture_memory));
		VK_CHECK(vkBindImageMemory(vk.device, vk.texture_image, vk.texture_memory, 0));

		VkBufferCreateInfo buffer_info = {0};
		buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_info.size = width * height * 4;
		buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		buffer_info.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
		VkBuffer staging_buffer = {0};
		VK_CHECK(vkCreateBuffer(vk.device, &buffer_info, NULL, &staging_buffer));

		VkMemoryRequirements buffer_memory_requirements = {0};
		vkGetBufferMemoryRequirements(vk.device, staging_buffer, &buffer_memory_requirements);

		u32 host_index = 0;
		for (int i = 0; i < vk.memory_properties.memoryTypeCount; i++) {
			if (memory_requirements.memoryTypeBits & (1 << i) &&
					(vk.memory_properties.memoryTypes[i].propertyFlags & (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))) {
				host_index = i;
				break;
			}
		}
		VkMemoryAllocateInfo staging_allocate_info = {0};
		staging_allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		staging_allocate_info.memoryTypeIndex = host_index;
		staging_allocate_info.allocationSize = buffer_memory_requirements.size;
		VkDeviceMemory staging_memory = {0};
		VK_CHECK(vkAllocateMemory(vk.device, &staging_allocate_info, NULL, &staging_memory));
		VK_CHECK(vkBindBufferMemory(vk.device, staging_buffer, staging_memory, 0));

		if (size > buffer_info.size)
			size = buffer_info.size; // just to be safe

		void *map = NULL;
		VK_CHECK(vkMapMemory(vk.device, staging_memory, 0, size, 0, &map));
		memcpy(map, buf, size);
		vkUnmapMemory(vk.device, staging_memory);
		if (!skipped_texture)
			free(buf);

		VkCommandBufferBeginInfo begin_info = {0};
		begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		VK_CHECK(vkBeginCommandBuffer(vk.transfer_cmd, &begin_info));

		VkImageMemoryBarrier barrier = {0};
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.image = vk.texture_image;
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		barrier.subresourceRange.levelCount = 1;
		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.layerCount = 1;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		vkCmdPipelineBarrier(vk.transfer_cmd, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, NULL, 0, NULL, 1, &barrier);

		VkBufferImageCopy region = {0};
		region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		region.imageSubresource.layerCount = 1;
		region.imageExtent.width = width;
		region.imageExtent.height = height;
		region.imageExtent.depth = 1;
		vkCmdCopyBufferToImage(vk.transfer_cmd, staging_buffer, vk.texture_image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

		barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		vkCmdPipelineBarrier(vk.transfer_cmd, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, NULL, 0, NULL, 1, &barrier);

		VK_CHECK(vkEndCommandBuffer(vk.transfer_cmd));

		VkSubmitInfo submit_info = {0};
		submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submit_info.pCommandBuffers = &vk.transfer_cmd;
		submit_info.commandBufferCount = 1;

		vkQueueSubmit(vk.transfer_queue, 1, &submit_info, VK_NULL_HANDLE);
		vkDeviceWaitIdle(vk.device);

		vkResetCommandBuffer(vk.transfer_cmd, 0);
		vkDestroyBuffer(vk.device, staging_buffer, NULL);
		vkFreeMemory(vk.device, staging_memory, NULL);

		VkImageViewCreateInfo view_info = {0};
		view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		view_info.image = vk.texture_image;
		view_info.format = VK_FORMAT_R8G8B8A8_UNORM;
		view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		view_info.subresourceRange.layerCount = 1;
		view_info.subresourceRange.baseArrayLayer = 0;
		view_info.subresourceRange.levelCount = 1;
		view_info.subresourceRange.baseMipLevel = 0;
		view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		VK_CHECK(vkCreateImageView(vk.device, &view_info, NULL, &vk.texture_image_view));

		VkDescriptorSetLayoutBinding binding = {0};
		binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
		binding.binding = 0;
		binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		binding.descriptorCount = 1;

		VkDescriptorSetLayoutCreateInfo layout_info = {0};
		layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layout_info.pBindings = &binding;
		layout_info.bindingCount = 1;
		VK_CHECK(vkCreateDescriptorSetLayout(vk.device, &layout_info, NULL, &vk.descriptor_layout));

		VkDescriptorPoolSize pool_size = {0};
		pool_size.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		pool_size.descriptorCount = 1;

		VkDescriptorPoolCreateInfo pool_info = {0};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.maxSets = 1;
		pool_info.pPoolSizes = &pool_size;
		pool_info.poolSizeCount = 1;
		VK_CHECK(vkCreateDescriptorPool(vk.device, &pool_info, NULL, &vk.descriptor_pool));

		VkDescriptorSetAllocateInfo descriptor_allocate_info = {0};
		descriptor_allocate_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptor_allocate_info.pSetLayouts = &vk.descriptor_layout;
		descriptor_allocate_info.descriptorSetCount = 1;
		descriptor_allocate_info.descriptorPool = vk.descriptor_pool;
		VK_CHECK(vkAllocateDescriptorSets(vk.device, &descriptor_allocate_info, &vk.descriptor_set));

		VkSamplerCreateInfo sampler_info = {0};
		sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
		sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
		sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
		sampler_info.magFilter = VK_FILTER_LINEAR;
		sampler_info.minFilter = VK_FILTER_LINEAR;
		sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		sampler_info.mipLodBias = 0.0f;
		sampler_info.anisotropyEnable = VK_FALSE;
		sampler_info.maxAnisotropy = 0.0f;
		sampler_info.compareEnable = VK_FALSE;
		sampler_info.minLod = 0.0f;
		sampler_info.maxLod = VK_LOD_CLAMP_NONE;
		sampler_info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		sampler_info.unnormalizedCoordinates = VK_FALSE;
		VK_CHECK(vkCreateSampler(vk.device, &sampler_info, NULL, &vk.texture_sampler));

		VkDescriptorImageInfo descriptor_image_info = {0};
		descriptor_image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		descriptor_image_info.sampler = vk.texture_sampler;
		descriptor_image_info.imageView = vk.texture_image_view;

		VkWriteDescriptorSet write = {0};
		write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.descriptorCount = 1;
		write.dstBinding = 0;
		write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		write.pImageInfo = &descriptor_image_info;
		write.dstSet = vk.descriptor_set;
		vkUpdateDescriptorSets(vk.device, 1, &write, 0, NULL);
	}

	{
		VkShaderModuleCreateInfo vertex_info = {0};
		vertex_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		vertex_info.codeSize = sizeof(vert_code);
		vertex_info.pCode = vert_code;

		VkShaderModuleCreateInfo fragment_info = {0};
		fragment_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		fragment_info.codeSize = sizeof(frag_code);
		fragment_info.pCode = frag_code;

		VkPipelineShaderStageCreateInfo stages[2] = {0};
		stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		stages[0].pName = "main";
		stages[0].pSpecializationInfo = NULL;
		VK_CHECK(vkCreateShaderModule(vk.device, &vertex_info, NULL, &stages[0].module));

		stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		stages[1].pName = "main";
		stages[1].pSpecializationInfo = NULL;
		VK_CHECK(vkCreateShaderModule(vk.device, &fragment_info, NULL, &stages[1].module));

		VkPipelineVertexInputStateCreateInfo vertex_input = {0};
		vertex_input.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		VkPipelineInputAssemblyStateCreateInfo input_assembly = {0};
		input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

		VkPipelineViewportStateCreateInfo viewport_state = {0};
		viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewport_state.viewportCount = 1;
		viewport_state.scissorCount = 1;

		VkPipelineRasterizationStateCreateInfo rasterization_state = {0};
		rasterization_state.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterization_state.cullMode = VK_CULL_MODE_NONE;
		rasterization_state.polygonMode = VK_POLYGON_MODE_FILL;
		rasterization_state.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterization_state.lineWidth = 1.0f;

		VkPipelineMultisampleStateCreateInfo multisample_state = {0};
		multisample_state.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisample_state.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkPipelineColorBlendAttachmentState color_attachment = {0};
		color_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT
		                                  | VK_COLOR_COMPONENT_G_BIT
		                                  | VK_COLOR_COMPONENT_B_BIT
		                                  | VK_COLOR_COMPONENT_A_BIT;
		color_attachment.blendEnable = VK_FALSE;

		VkPipelineColorBlendStateCreateInfo color_blend_state = {0};
		color_blend_state.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;               
		color_blend_state.attachmentCount = 1;
		color_blend_state.pAttachments = &color_attachment;

		VkPipelineDepthStencilStateCreateInfo depth_state = {0};
		depth_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depth_state.depthTestEnable = VK_TRUE;
		depth_state.depthWriteEnable = VK_TRUE;
		depth_state.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;

		VkPipelineDynamicStateCreateInfo dynamic_state = {0};
		dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamic_state.dynamicStateCount = 2;
		dynamic_state.pDynamicStates = (VkDynamicState[]) {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};

		VkPushConstantRange push_constant_range = {0};
		push_constant_range.size = sizeof(Mat4);
		push_constant_range.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

		VkPipelineLayoutCreateInfo layout_info = {0};
		layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		layout_info.pushConstantRangeCount = 1;
		layout_info.pPushConstantRanges = &push_constant_range;
		layout_info.setLayoutCount = 1;
		layout_info.pSetLayouts = &vk.descriptor_layout;

		VK_CHECK(vkCreatePipelineLayout(vk.device, &layout_info, NULL, &vk.pipeline_layout));

		VkGraphicsPipelineCreateInfo pipeline_info = {0};
		pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipeline_info.layout = vk.pipeline_layout;
		pipeline_info.renderPass = vk.renderpass;
		pipeline_info.subpass = 0;
		pipeline_info.stageCount = 2;
		pipeline_info.pViewportState = &viewport_state;
		pipeline_info.pVertexInputState = &vertex_input;
		pipeline_info.pStages = stages;
		pipeline_info.pRasterizationState = &rasterization_state;
		pipeline_info.pMultisampleState = &multisample_state;
		pipeline_info.pInputAssemblyState = &input_assembly;
		pipeline_info.pDynamicState = &dynamic_state;
		pipeline_info.pColorBlendState = &color_blend_state;
		pipeline_info.pDepthStencilState = &depth_state;

		VK_CHECK(vkCreateGraphicsPipelines(vk.device, VK_NULL_HANDLE, 1, &pipeline_info, NULL, &vk.pipeline));

		vkDestroyShaderModule(vk.device, stages[0].module, NULL);
		vkDestroyShaderModule(vk.device, stages[1].module, NULL);
	}
	
	createSwapchain(vk.surface, VK_PRESENT_MODE_FIFO_KHR);

	while (!RGFW_window_shouldClose(&window)) {
		RGFW_event event = {0};
		while (RGFW_window_checkEvent(&window, &event)) {
			switch (event.type) {
				case RGFW_windowResized:
					vkDeviceWaitIdle(vk.device);
					printf("%dx%d\n", window.w, window.h);
					VkSurfaceKHR surface = vk.surface;
					VK_CHECK(RGFW_window_createSurface_Vulkan(&window, vk.instance, &vk.surface));
					createSwapchain(vk.surface, VK_PRESENT_MODE_FIFO_KHR);
					vkDestroySurfaceKHR(vk.instance, surface, NULL);
					vkDeviceWaitIdle(vk.device);
					break;
			}
		}

		VkFence frame_fence = vk.fences[vk.current_frame];
		VkSemaphore acquire_semaphore = vk.image_semaphores[vk.current_frame];
		VkCommandBuffer cmd = vk.cmd[vk.current_frame];

		VK_CHECK(vkWaitForFences(vk.device, 1, &frame_fence, VK_TRUE, 1000 * 1000 * 1000));
		VK_CHECK(vkResetFences(vk.device, 1, &frame_fence));

		VK_CHECK(vkAcquireNextImageKHR(vk.device, vk.swapchain, 1000 * 1000 * 1000, acquire_semaphore, VK_NULL_HANDLE, &vk.image_index));

		VkSemaphore submit_semaphore = vk.submit_semaphores[vk.current_frame];

		VK_CHECK(vkResetCommandBuffer(cmd, 0));

		VkCommandBufferBeginInfo begin_info = {0};
		begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		begin_info.pInheritanceInfo = NULL;

		VkClearValue clear_values[2] = {0};
		clear_values[0].color.float32[0] = 0.5f;
		clear_values[0].color.float32[1] = 0.5f;
		clear_values[0].color.float32[2] = 0.5f;
		clear_values[0].color.float32[3] = 1.0f;
		clear_values[1].depthStencil.depth = 1.0f;

		VkRenderPassBeginInfo renderpass_info = {0};
		renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderpass_info.renderPass = vk.renderpass;
		renderpass_info.framebuffer = vk.framebuffers[vk.image_index];
		renderpass_info.renderArea.extent.width = vk.w;
		renderpass_info.renderArea.extent.height = vk.h;
		renderpass_info.clearValueCount = 2;
		renderpass_info.pClearValues = clear_values;

		VK_CHECK(vkBeginCommandBuffer(cmd, &begin_info));
		vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, vk.pipeline);
		vkCmdBeginRenderPass(cmd, &renderpass_info, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport = {0};
		viewport.width = (float)vk.w;
		viewport.height = (float)vk.h;
		viewport.minDepth = 0.0;
		viewport.maxDepth = 1.0;
		viewport.x = 0.0;
		viewport.y = 0.0;
		vkCmdSetViewport(cmd, 0, 1, &viewport);

		VkRect2D scissor = {0};
		scissor.extent.width = vk.w;
		scissor.extent.height = vk.h;
		scissor.offset.x = 0;
		scissor.offset.y = 0;
		vkCmdSetScissor(cmd, 0, 1, &scissor);

		vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, vk.pipeline_layout, 0, 1, &vk.descriptor_set, 0, NULL);

		static float current_x = 0.0f;
		static float current_y = M_PI;

#define CONVERT(n, a, b, c, d) ((float)(c) + ((float)(n) - (float)(a)) * ((float)(d) - (float)(c)) / ((float)(b) - (float)(a)))

		if (RGFW_isMouseDown(RGFW_mouseLeft)) {
			int32_t mouse_x = 0;
			int32_t mouse_y = 0;
			RGFW_window_getMouse(&window, &mouse_x, &mouse_y);
			current_x = CONVERT(mouse_x, 0, vk.w, -2.5f, 2.5f);
			current_y = CONVERT(mouse_y, 0, vk.h, 0.5f, 5.5f);
		}

		Mat4 rx = mat4EulerX(current_y);
		Mat4 ry = mat4EulerY(current_x);
		Mat4 p = mat4Perspective(1.5f, (float)vk.w / (float)vk.h, 0.1f, 50.0f);
		Mat4 rot = mat4Mul(ry, rx);
		rot.f[2][3] = 3.0f; // puts camera further away from the cube
		Mat4 mvp = mat4Mul(p, rot);
		vkCmdPushConstants(cmd, vk.pipeline_layout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(mvp), &mvp);

		vkCmdDraw(cmd, 36, 1, 0, 0);
		vkCmdEndRenderPass(cmd);
		VK_CHECK(vkEndCommandBuffer(cmd));

		VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		VkSubmitInfo submit_info = {0};
		submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submit_info.waitSemaphoreCount = 1;
		submit_info.pWaitSemaphores = &acquire_semaphore;
		submit_info.pWaitDstStageMask = &wait_stage;
		submit_info.commandBufferCount = 1;
		submit_info.pCommandBuffers = &cmd;
		submit_info.signalSemaphoreCount = 1;
		submit_info.pSignalSemaphores = &submit_semaphore;

		VK_CHECK(vkQueueSubmit(vk.graphics_queue, 1, &submit_info, vk.fences[vk.current_frame]));

		VkPresentInfoKHR present_info = {0};
		present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		present_info.waitSemaphoreCount = 1;
		present_info.pWaitSemaphores = &submit_semaphore;
		present_info.swapchainCount = 1;
		present_info.pSwapchains = &vk.swapchain;
		present_info.pImageIndices = &vk.image_index;
		present_info.pResults = NULL;

		VkResult result = vkQueuePresentKHR(vk.present_queue, &present_info);
		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
			vkDeviceWaitIdle(vk.device);
			VkSurfaceKHR surface = vk.surface;
			VK_CHECK(RGFW_window_createSurface_Vulkan(&window, vk.instance, &vk.surface));
			createSwapchain(vk.surface, VK_PRESENT_MODE_FIFO_KHR);
			vkDestroySurfaceKHR(vk.instance, surface, NULL);
			vkDeviceWaitIdle(vk.device);
			continue;
		}
		else if (!vulkanResultCheck(result)) {
			fprintf(stderr, "failed to present: %d\n", result);
			RGFW_window_closePtr(&window);
			break;
		}

 		vk.current_frame = (vk.current_frame + 1) % vk.image_count;
	}

	{
		vkDeviceWaitIdle(vk.device);

		vkDestroyRenderPass(vk.device, vk.renderpass, NULL);

		vkDestroyPipeline(vk.device, vk.pipeline, NULL);
		vkDestroyPipelineLayout(vk.device, vk.pipeline_layout, NULL);

		vkDestroyDescriptorPool(vk.device, vk.descriptor_pool, NULL);
		vkDestroyDescriptorSetLayout(vk.device, vk.descriptor_layout, NULL);

		vkDestroySampler(vk.device, vk.texture_sampler, NULL);
		vkDestroyImageView(vk.device, vk.texture_image_view, NULL);
		vkDestroyImage(vk.device, vk.texture_image, NULL);
		vkFreeMemory(vk.device, vk.texture_memory, NULL);

		for (int i = 0; i < vk.image_count; i++) {
			vkDestroyFramebuffer(vk.device, vk.framebuffers[i], NULL);
			vkDestroyImageView(vk.device, vk.swapchain_image_views[i], NULL);
			vkDestroyFence(vk.device, vk.fences[i], NULL);
			vkDestroySemaphore(vk.device, vk.image_semaphores[i], NULL);
			vkDestroySemaphore(vk.device, vk.submit_semaphores[i], NULL);
		}

		vkDestroyImageView(vk.device, vk.depth_image_view, NULL);
		vkDestroyImage(vk.device, vk.depth_image, NULL);
		vkFreeMemory(vk.device, vk.depth_image_memory, NULL);

		vkDestroySwapchainKHR(vk.device, vk.swapchain, NULL);
		vkDestroySurfaceKHR(vk.instance, vk.surface, NULL);

		vkFreeCommandBuffers(vk.device, vk.transfer_command_pool, 1, &vk.transfer_cmd);
		vkDestroyCommandPool(vk.device, vk.transfer_command_pool, NULL);
		vkFreeCommandBuffers(vk.device, vk.graphics_command_pool, vk.image_count, vk.cmd);
		vkDestroyCommandPool(vk.device, vk.graphics_command_pool, NULL);

		vkDestroyDevice(vk.device, NULL);

		vkDestroyInstance(vk.instance, NULL);
	}

	RGFW_window_closePtr(&window);
}
