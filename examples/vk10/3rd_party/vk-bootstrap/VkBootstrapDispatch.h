/*
 * Copyright © 2021 Cody Goodson (contact@vibimanx.com)
 * Copyright © 2022 Charles Giessen (charles@lunarg.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the “Software”), to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
// This file is a part of VkBootstrap
// https://github.com/charles-lunarg/vk-bootstrap


#pragma once

#include <vulkan/vulkan.h>

namespace vkb {

struct InstanceDispatchTable {
    InstanceDispatchTable() = default;
    InstanceDispatchTable(VkInstance instance, PFN_vkGetInstanceProcAddr procAddr) : instance(instance), populated(true) {
        fp_vkDestroyInstance = reinterpret_cast<PFN_vkDestroyInstance>(procAddr(instance, "vkDestroyInstance"));
        fp_vkEnumeratePhysicalDevices = reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(procAddr(instance, "vkEnumeratePhysicalDevices"));
        fp_vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(procAddr(instance, "vkGetInstanceProcAddr"));
        fp_vkGetPhysicalDeviceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(procAddr(instance, "vkGetPhysicalDeviceProperties"));
        fp_vkGetPhysicalDeviceQueueFamilyProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties>(procAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties"));
        fp_vkGetPhysicalDeviceMemoryProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties>(procAddr(instance, "vkGetPhysicalDeviceMemoryProperties"));
        fp_vkGetPhysicalDeviceFeatures = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures>(procAddr(instance, "vkGetPhysicalDeviceFeatures"));
        fp_vkGetPhysicalDeviceFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties>(procAddr(instance, "vkGetPhysicalDeviceFormatProperties"));
        fp_vkGetPhysicalDeviceImageFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties>(procAddr(instance, "vkGetPhysicalDeviceImageFormatProperties"));
        fp_vkEnumerateDeviceLayerProperties = reinterpret_cast<PFN_vkEnumerateDeviceLayerProperties>(procAddr(instance, "vkEnumerateDeviceLayerProperties"));
        fp_vkEnumerateDeviceExtensionProperties = reinterpret_cast<PFN_vkEnumerateDeviceExtensionProperties>(procAddr(instance, "vkEnumerateDeviceExtensionProperties"));
        fp_vkGetPhysicalDeviceSparseImageFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties>(procAddr(instance, "vkGetPhysicalDeviceSparseImageFormatProperties"));
#if (defined(VK_KHR_android_surface))
        fp_vkCreateAndroidSurfaceKHR = reinterpret_cast<PFN_vkCreateAndroidSurfaceKHR>(procAddr(instance, "vkCreateAndroidSurfaceKHR"));
#endif
#if (defined(VK_KHR_display))
        fp_vkGetPhysicalDeviceDisplayPropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPropertiesKHR>(procAddr(instance, "vkGetPhysicalDeviceDisplayPropertiesKHR"));
#endif
#if (defined(VK_KHR_display))
        fp_vkGetPhysicalDeviceDisplayPlanePropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR>(procAddr(instance, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR"));
#endif
#if (defined(VK_KHR_display))
        fp_vkGetDisplayPlaneSupportedDisplaysKHR = reinterpret_cast<PFN_vkGetDisplayPlaneSupportedDisplaysKHR>(procAddr(instance, "vkGetDisplayPlaneSupportedDisplaysKHR"));
#endif
#if (defined(VK_KHR_display))
        fp_vkGetDisplayModePropertiesKHR = reinterpret_cast<PFN_vkGetDisplayModePropertiesKHR>(procAddr(instance, "vkGetDisplayModePropertiesKHR"));
#endif
#if (defined(VK_KHR_display))
        fp_vkCreateDisplayModeKHR = reinterpret_cast<PFN_vkCreateDisplayModeKHR>(procAddr(instance, "vkCreateDisplayModeKHR"));
#endif
#if (defined(VK_KHR_display))
        fp_vkGetDisplayPlaneCapabilitiesKHR = reinterpret_cast<PFN_vkGetDisplayPlaneCapabilitiesKHR>(procAddr(instance, "vkGetDisplayPlaneCapabilitiesKHR"));
#endif
#if (defined(VK_KHR_display))
        fp_vkCreateDisplayPlaneSurfaceKHR = reinterpret_cast<PFN_vkCreateDisplayPlaneSurfaceKHR>(procAddr(instance, "vkCreateDisplayPlaneSurfaceKHR"));
#endif
#if (defined(VK_KHR_surface))
        fp_vkDestroySurfaceKHR = reinterpret_cast<PFN_vkDestroySurfaceKHR>(procAddr(instance, "vkDestroySurfaceKHR"));
#endif
#if (defined(VK_KHR_surface))
        fp_vkGetPhysicalDeviceSurfaceSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceSupportKHR>(procAddr(instance, "vkGetPhysicalDeviceSurfaceSupportKHR"));
#endif
#if (defined(VK_KHR_surface))
        fp_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR>(procAddr(instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR"));
#endif
#if (defined(VK_KHR_surface))
        fp_vkGetPhysicalDeviceSurfaceFormatsKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormatsKHR>(procAddr(instance, "vkGetPhysicalDeviceSurfaceFormatsKHR"));
#endif
#if (defined(VK_KHR_surface))
        fp_vkGetPhysicalDeviceSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModesKHR>(procAddr(instance, "vkGetPhysicalDeviceSurfacePresentModesKHR"));
#endif
#if (defined(VK_NN_vi_surface))
        fp_vkCreateViSurfaceNN = reinterpret_cast<PFN_vkCreateViSurfaceNN>(procAddr(instance, "vkCreateViSurfaceNN"));
#endif
#if (defined(VK_KHR_wayland_surface))
        fp_vkCreateWaylandSurfaceKHR = reinterpret_cast<PFN_vkCreateWaylandSurfaceKHR>(procAddr(instance, "vkCreateWaylandSurfaceKHR"));
#endif
#if (defined(VK_KHR_wayland_surface))
        fp_vkGetPhysicalDeviceWaylandPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR>(procAddr(instance, "vkGetPhysicalDeviceWaylandPresentationSupportKHR"));
#endif
#if (defined(VK_KHR_win32_surface))
        fp_vkCreateWin32SurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(procAddr(instance, "vkCreateWin32SurfaceKHR"));
#endif
#if (defined(VK_KHR_win32_surface))
        fp_vkGetPhysicalDeviceWin32PresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR>(procAddr(instance, "vkGetPhysicalDeviceWin32PresentationSupportKHR"));
#endif
#if (defined(VK_KHR_xlib_surface))
        fp_vkCreateXlibSurfaceKHR = reinterpret_cast<PFN_vkCreateXlibSurfaceKHR>(procAddr(instance, "vkCreateXlibSurfaceKHR"));
#endif
#if (defined(VK_KHR_xlib_surface))
        fp_vkGetPhysicalDeviceXlibPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR>(procAddr(instance, "vkGetPhysicalDeviceXlibPresentationSupportKHR"));
#endif
#if (defined(VK_KHR_xcb_surface))
        fp_vkCreateXcbSurfaceKHR = reinterpret_cast<PFN_vkCreateXcbSurfaceKHR>(procAddr(instance, "vkCreateXcbSurfaceKHR"));
#endif
#if (defined(VK_KHR_xcb_surface))
        fp_vkGetPhysicalDeviceXcbPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR>(procAddr(instance, "vkGetPhysicalDeviceXcbPresentationSupportKHR"));
#endif
#if (defined(VK_EXT_directfb_surface))
        fp_vkCreateDirectFBSurfaceEXT = reinterpret_cast<PFN_vkCreateDirectFBSurfaceEXT>(procAddr(instance, "vkCreateDirectFBSurfaceEXT"));
#endif
#if (defined(VK_EXT_directfb_surface))
        fp_vkGetPhysicalDeviceDirectFBPresentationSupportEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT>(procAddr(instance, "vkGetPhysicalDeviceDirectFBPresentationSupportEXT"));
#endif
#if (defined(VK_FUCHSIA_imagepipe_surface))
        fp_vkCreateImagePipeSurfaceFUCHSIA = reinterpret_cast<PFN_vkCreateImagePipeSurfaceFUCHSIA>(procAddr(instance, "vkCreateImagePipeSurfaceFUCHSIA"));
#endif
#if (defined(VK_GGP_stream_descriptor_surface))
        fp_vkCreateStreamDescriptorSurfaceGGP = reinterpret_cast<PFN_vkCreateStreamDescriptorSurfaceGGP>(procAddr(instance, "vkCreateStreamDescriptorSurfaceGGP"));
#endif
#if (defined(VK_QNX_screen_surface))
        fp_vkCreateScreenSurfaceQNX = reinterpret_cast<PFN_vkCreateScreenSurfaceQNX>(procAddr(instance, "vkCreateScreenSurfaceQNX"));
#endif
#if (defined(VK_QNX_screen_surface))
        fp_vkGetPhysicalDeviceScreenPresentationSupportQNX = reinterpret_cast<PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX>(procAddr(instance, "vkGetPhysicalDeviceScreenPresentationSupportQNX"));
#endif
#if (defined(VK_EXT_debug_report))
        fp_vkCreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(procAddr(instance, "vkCreateDebugReportCallbackEXT"));
#endif
#if (defined(VK_EXT_debug_report))
        fp_vkDestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(procAddr(instance, "vkDestroyDebugReportCallbackEXT"));
#endif
#if (defined(VK_EXT_debug_report))
        fp_vkDebugReportMessageEXT = reinterpret_cast<PFN_vkDebugReportMessageEXT>(procAddr(instance, "vkDebugReportMessageEXT"));
#endif
#if (defined(VK_NV_external_memory_capabilities))
        fp_vkGetPhysicalDeviceExternalImageFormatPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV>(procAddr(instance, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetPhysicalDeviceFeatures2 = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2>(procAddr(instance, "vkGetPhysicalDeviceFeatures2"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetPhysicalDeviceProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2>(procAddr(instance, "vkGetPhysicalDeviceProperties2"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetPhysicalDeviceFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties2>(procAddr(instance, "vkGetPhysicalDeviceFormatProperties2"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetPhysicalDeviceImageFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties2>(procAddr(instance, "vkGetPhysicalDeviceImageFormatProperties2"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetPhysicalDeviceQueueFamilyProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties2>(procAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties2"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetPhysicalDeviceMemoryProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2>(procAddr(instance, "vkGetPhysicalDeviceMemoryProperties2"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetPhysicalDeviceSparseImageFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties2>(procAddr(instance, "vkGetPhysicalDeviceSparseImageFormatProperties2"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetPhysicalDeviceExternalBufferProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalBufferProperties>(procAddr(instance, "vkGetPhysicalDeviceExternalBufferProperties"));
#endif
#if (defined(VK_NV_external_memory_sci_buf))
        fp_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV>(procAddr(instance, "vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV"));
#endif
#if (defined(VK_NV_external_memory_sci_buf))
        fp_vkGetPhysicalDeviceSciBufAttributesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceSciBufAttributesNV>(procAddr(instance, "vkGetPhysicalDeviceSciBufAttributesNV"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetPhysicalDeviceExternalSemaphoreProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalSemaphoreProperties>(procAddr(instance, "vkGetPhysicalDeviceExternalSemaphoreProperties"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetPhysicalDeviceExternalFenceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalFenceProperties>(procAddr(instance, "vkGetPhysicalDeviceExternalFenceProperties"));
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
        fp_vkGetPhysicalDeviceSciSyncAttributesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceSciSyncAttributesNV>(procAddr(instance, "vkGetPhysicalDeviceSciSyncAttributesNV"));
#endif
#if (defined(VK_EXT_direct_mode_display))
        fp_vkReleaseDisplayEXT = reinterpret_cast<PFN_vkReleaseDisplayEXT>(procAddr(instance, "vkReleaseDisplayEXT"));
#endif
#if (defined(VK_EXT_acquire_xlib_display))
        fp_vkAcquireXlibDisplayEXT = reinterpret_cast<PFN_vkAcquireXlibDisplayEXT>(procAddr(instance, "vkAcquireXlibDisplayEXT"));
#endif
#if (defined(VK_EXT_acquire_xlib_display))
        fp_vkGetRandROutputDisplayEXT = reinterpret_cast<PFN_vkGetRandROutputDisplayEXT>(procAddr(instance, "vkGetRandROutputDisplayEXT"));
#endif
#if (defined(VK_NV_acquire_winrt_display))
        fp_vkAcquireWinrtDisplayNV = reinterpret_cast<PFN_vkAcquireWinrtDisplayNV>(procAddr(instance, "vkAcquireWinrtDisplayNV"));
#endif
#if (defined(VK_NV_acquire_winrt_display))
        fp_vkGetWinrtDisplayNV = reinterpret_cast<PFN_vkGetWinrtDisplayNV>(procAddr(instance, "vkGetWinrtDisplayNV"));
#endif
#if (defined(VK_EXT_display_surface_counter))
        fp_vkGetPhysicalDeviceSurfaceCapabilities2EXT = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT>(procAddr(instance, "vkGetPhysicalDeviceSurfaceCapabilities2EXT"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkEnumeratePhysicalDeviceGroups = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceGroups>(procAddr(instance, "vkEnumeratePhysicalDeviceGroups"));
#endif
#if (defined(VK_KHR_swapchain)) || (defined(VK_KHR_device_group))
        fp_vkGetPhysicalDevicePresentRectanglesKHR = reinterpret_cast<PFN_vkGetPhysicalDevicePresentRectanglesKHR>(procAddr(instance, "vkGetPhysicalDevicePresentRectanglesKHR"));
#endif
#if (defined(VK_MVK_ios_surface))
        fp_vkCreateIOSSurfaceMVK = reinterpret_cast<PFN_vkCreateIOSSurfaceMVK>(procAddr(instance, "vkCreateIOSSurfaceMVK"));
#endif
#if (defined(VK_MVK_macos_surface))
        fp_vkCreateMacOSSurfaceMVK = reinterpret_cast<PFN_vkCreateMacOSSurfaceMVK>(procAddr(instance, "vkCreateMacOSSurfaceMVK"));
#endif
#if (defined(VK_EXT_metal_surface))
        fp_vkCreateMetalSurfaceEXT = reinterpret_cast<PFN_vkCreateMetalSurfaceEXT>(procAddr(instance, "vkCreateMetalSurfaceEXT"));
#endif
#if (defined(VK_EXT_sample_locations))
        fp_vkGetPhysicalDeviceMultisamplePropertiesEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT>(procAddr(instance, "vkGetPhysicalDeviceMultisamplePropertiesEXT"));
#endif
#if (defined(VK_KHR_get_surface_capabilities2))
        fp_vkGetPhysicalDeviceSurfaceCapabilities2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR>(procAddr(instance, "vkGetPhysicalDeviceSurfaceCapabilities2KHR"));
#endif
#if (defined(VK_KHR_get_surface_capabilities2))
        fp_vkGetPhysicalDeviceSurfaceFormats2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormats2KHR>(procAddr(instance, "vkGetPhysicalDeviceSurfaceFormats2KHR"));
#endif
#if (defined(VK_KHR_get_display_properties2))
        fp_vkGetPhysicalDeviceDisplayProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayProperties2KHR>(procAddr(instance, "vkGetPhysicalDeviceDisplayProperties2KHR"));
#endif
#if (defined(VK_KHR_get_display_properties2))
        fp_vkGetPhysicalDeviceDisplayPlaneProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR>(procAddr(instance, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR"));
#endif
#if (defined(VK_KHR_get_display_properties2))
        fp_vkGetDisplayModeProperties2KHR = reinterpret_cast<PFN_vkGetDisplayModeProperties2KHR>(procAddr(instance, "vkGetDisplayModeProperties2KHR"));
#endif
#if (defined(VK_KHR_get_display_properties2))
        fp_vkGetDisplayPlaneCapabilities2KHR = reinterpret_cast<PFN_vkGetDisplayPlaneCapabilities2KHR>(procAddr(instance, "vkGetDisplayPlaneCapabilities2KHR"));
#endif
#if (defined(VK_KHR_calibrated_timestamps))
        fp_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR>(procAddr(instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR"));
#endif
#if (defined(VK_EXT_debug_utils))
        fp_vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(procAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
#endif
#if (defined(VK_EXT_debug_utils))
        fp_vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(procAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
#endif
#if (defined(VK_EXT_debug_utils))
        fp_vkSubmitDebugUtilsMessageEXT = reinterpret_cast<PFN_vkSubmitDebugUtilsMessageEXT>(procAddr(instance, "vkSubmitDebugUtilsMessageEXT"));
#endif
#if (defined(VK_NV_cooperative_matrix))
        fp_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV>(procAddr(instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV"));
#endif
#if (defined(VK_EXT_full_screen_exclusive))
        fp_vkGetPhysicalDeviceSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT>(procAddr(instance, "vkGetPhysicalDeviceSurfacePresentModes2EXT"));
#endif
#if (defined(VK_KHR_performance_query))
        fp_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR>(procAddr(instance, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR"));
#endif
#if (defined(VK_KHR_performance_query))
        fp_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR>(procAddr(instance, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR"));
#endif
#if (defined(VK_EXT_headless_surface))
        fp_vkCreateHeadlessSurfaceEXT = reinterpret_cast<PFN_vkCreateHeadlessSurfaceEXT>(procAddr(instance, "vkCreateHeadlessSurfaceEXT"));
#endif
#if (defined(VK_NV_coverage_reduction_mode))
        fp_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = reinterpret_cast<PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV>(procAddr(instance, "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkGetPhysicalDeviceToolProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceToolProperties>(procAddr(instance, "vkGetPhysicalDeviceToolProperties"));
#endif
#if (defined(VK_KHR_object_refresh))
        fp_vkGetPhysicalDeviceRefreshableObjectTypesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceRefreshableObjectTypesKHR>(procAddr(instance, "vkGetPhysicalDeviceRefreshableObjectTypesKHR"));
#endif
#if (defined(VK_KHR_fragment_shading_rate))
        fp_vkGetPhysicalDeviceFragmentShadingRatesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR>(procAddr(instance, "vkGetPhysicalDeviceFragmentShadingRatesKHR"));
#endif
#if (defined(VK_KHR_video_queue))
        fp_vkGetPhysicalDeviceVideoCapabilitiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR>(procAddr(instance, "vkGetPhysicalDeviceVideoCapabilitiesKHR"));
#endif
#if (defined(VK_KHR_video_queue))
        fp_vkGetPhysicalDeviceVideoFormatPropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR>(procAddr(instance, "vkGetPhysicalDeviceVideoFormatPropertiesKHR"));
#endif
#if (defined(VK_KHR_video_encode_queue))
        fp_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR>(procAddr(instance, "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR"));
#endif
#if (defined(VK_EXT_acquire_drm_display))
        fp_vkAcquireDrmDisplayEXT = reinterpret_cast<PFN_vkAcquireDrmDisplayEXT>(procAddr(instance, "vkAcquireDrmDisplayEXT"));
#endif
#if (defined(VK_EXT_acquire_drm_display))
        fp_vkGetDrmDisplayEXT = reinterpret_cast<PFN_vkGetDrmDisplayEXT>(procAddr(instance, "vkGetDrmDisplayEXT"));
#endif
#if (defined(VK_NV_optical_flow))
        fp_vkGetPhysicalDeviceOpticalFlowImageFormatsNV = reinterpret_cast<PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV>(procAddr(instance, "vkGetPhysicalDeviceOpticalFlowImageFormatsNV"));
#endif
#if (defined(VK_KHR_cooperative_matrix))
        fp_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR>(procAddr(instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR"));
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
        fp_vkGetPhysicalDeviceFeatures2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2KHR>(procAddr(instance, "vkGetPhysicalDeviceFeatures2KHR"));
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
        fp_vkGetPhysicalDeviceProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2KHR>(procAddr(instance, "vkGetPhysicalDeviceProperties2KHR"));
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
        fp_vkGetPhysicalDeviceFormatProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties2KHR>(procAddr(instance, "vkGetPhysicalDeviceFormatProperties2KHR"));
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
        fp_vkGetPhysicalDeviceImageFormatProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties2KHR>(procAddr(instance, "vkGetPhysicalDeviceImageFormatProperties2KHR"));
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
        fp_vkGetPhysicalDeviceQueueFamilyProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR>(procAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties2KHR"));
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
        fp_vkGetPhysicalDeviceMemoryProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2KHR>(procAddr(instance, "vkGetPhysicalDeviceMemoryProperties2KHR"));
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
        fp_vkGetPhysicalDeviceSparseImageFormatProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR>(procAddr(instance, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR"));
#endif
#if (defined(VK_KHR_external_memory_capabilities))
        fp_vkGetPhysicalDeviceExternalBufferPropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR>(procAddr(instance, "vkGetPhysicalDeviceExternalBufferPropertiesKHR"));
#endif
#if (defined(VK_KHR_external_semaphore_capabilities))
        fp_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR>(procAddr(instance, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR"));
#endif
#if (defined(VK_KHR_external_fence_capabilities))
        fp_vkGetPhysicalDeviceExternalFencePropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR>(procAddr(instance, "vkGetPhysicalDeviceExternalFencePropertiesKHR"));
#endif
#if (defined(VK_KHR_device_group_creation))
        fp_vkEnumeratePhysicalDeviceGroupsKHR = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceGroupsKHR>(procAddr(instance, "vkEnumeratePhysicalDeviceGroupsKHR"));
#endif
#if (defined(VK_EXT_calibrated_timestamps))
        fp_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT>(procAddr(instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT"));
#endif
#if (defined(VK_EXT_tooling_info))
        fp_vkGetPhysicalDeviceToolPropertiesEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceToolPropertiesEXT>(procAddr(instance, "vkGetPhysicalDeviceToolPropertiesEXT"));
#endif
    }
    void destroyInstance(const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyInstance(instance, pAllocator);
    }
    VkResult enumeratePhysicalDevices(uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices) const noexcept {
        return fp_vkEnumeratePhysicalDevices(instance, pPhysicalDeviceCount, pPhysicalDevices);
    }
    PFN_vkVoidFunction getInstanceProcAddr(const char* pName) const noexcept {
        return fp_vkGetInstanceProcAddr(instance, pName);
    }
    void getPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties) const noexcept {
        fp_vkGetPhysicalDeviceProperties(physicalDevice, pProperties);
    }
    void getPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties) const noexcept {
        fp_vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    }
    void getPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties) const noexcept {
        fp_vkGetPhysicalDeviceMemoryProperties(physicalDevice, pMemoryProperties);
    }
    void getPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures) const noexcept {
        fp_vkGetPhysicalDeviceFeatures(physicalDevice, pFeatures);
    }
    void getPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties) const noexcept {
        fp_vkGetPhysicalDeviceFormatProperties(physicalDevice, format, pFormatProperties);
    }
    VkResult getPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties) const noexcept {
        return fp_vkGetPhysicalDeviceImageFormatProperties(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
    }
    VkResult enumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkLayerProperties* pProperties) const noexcept {
        return fp_vkEnumerateDeviceLayerProperties(physicalDevice, pPropertyCount, pProperties);
    }
    VkResult enumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties) const noexcept {
        return fp_vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount, pProperties);
    }
    void getPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t* pPropertyCount, VkSparseImageFormatProperties* pProperties) const noexcept {
        fp_vkGetPhysicalDeviceSparseImageFormatProperties(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
    }
#if (defined(VK_KHR_android_surface))
    VkResult createAndroidSurfaceKHR(const VkAndroidSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateAndroidSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_KHR_display))
    VkResult getPhysicalDeviceDisplayPropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPropertiesKHR* pProperties) const noexcept {
        return fp_vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, pPropertyCount, pProperties);
    }
#endif
#if (defined(VK_KHR_display))
    VkResult getPhysicalDeviceDisplayPlanePropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlanePropertiesKHR* pProperties) const noexcept {
        return fp_vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, pPropertyCount, pProperties);
    }
#endif
#if (defined(VK_KHR_display))
    VkResult getDisplayPlaneSupportedDisplaysKHR(VkPhysicalDevice physicalDevice, uint32_t planeIndex, uint32_t* pDisplayCount, VkDisplayKHR* pDisplays) const noexcept {
        return fp_vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, planeIndex, pDisplayCount, pDisplays);
    }
#endif
#if (defined(VK_KHR_display))
    VkResult getDisplayModePropertiesKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModePropertiesKHR* pProperties) const noexcept {
        return fp_vkGetDisplayModePropertiesKHR(physicalDevice, display, pPropertyCount, pProperties);
    }
#endif
#if (defined(VK_KHR_display))
    VkResult createDisplayModeKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, const VkDisplayModeCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDisplayModeKHR* pMode) const noexcept {
        return fp_vkCreateDisplayModeKHR(physicalDevice, display, pCreateInfo, pAllocator, pMode);
    }
#endif
#if (defined(VK_KHR_display))
    VkResult getDisplayPlaneCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkDisplayModeKHR mode, uint32_t planeIndex, VkDisplayPlaneCapabilitiesKHR* pCapabilities) const noexcept {
        return fp_vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, mode, planeIndex, pCapabilities);
    }
#endif
#if (defined(VK_KHR_display))
    VkResult createDisplayPlaneSurfaceKHR(const VkDisplaySurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateDisplayPlaneSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_KHR_surface))
    void destroySurfaceKHR(VkSurfaceKHR surface, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroySurfaceKHR(instance, surface, pAllocator);
    }
#endif
#if (defined(VK_KHR_surface))
    VkResult getPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported) const noexcept {
        return fp_vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, pSupported);
    }
#endif
#if (defined(VK_KHR_surface))
    VkResult getPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities) const noexcept {
        return fp_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, pSurfaceCapabilities);
    }
#endif
#if (defined(VK_KHR_surface))
    VkResult getPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats) const noexcept {
        return fp_vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
    }
#endif
#if (defined(VK_KHR_surface))
    VkResult getPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes) const noexcept {
        return fp_vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, pPresentModeCount, pPresentModes);
    }
#endif
#if (defined(VK_NN_vi_surface))
    VkResult createViSurfaceNN(const VkViSurfaceCreateInfoNN* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateViSurfaceNN(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_KHR_wayland_surface))
    VkResult createWaylandSurfaceKHR(const VkWaylandSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateWaylandSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_KHR_wayland_surface))
    VkBool32 getPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display* display) const noexcept {
        return fp_vkGetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice, queueFamilyIndex, display);
    }
#endif
#if (defined(VK_KHR_win32_surface))
    VkResult createWin32SurfaceKHR(const VkWin32SurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateWin32SurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_KHR_win32_surface))
    VkBool32 getPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex) const noexcept {
        return fp_vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice, queueFamilyIndex);
    }
#endif
#if (defined(VK_KHR_xlib_surface))
    VkResult createXlibSurfaceKHR(const VkXlibSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateXlibSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_KHR_xlib_surface))
    VkBool32 getPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display* dpy, VisualID visualID) const noexcept {
        return fp_vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice, queueFamilyIndex, dpy, visualID);
    }
#endif
#if (defined(VK_KHR_xcb_surface))
    VkResult createXcbSurfaceKHR(const VkXcbSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateXcbSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_KHR_xcb_surface))
    VkBool32 getPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t* connection, xcb_visualid_t visual_id) const noexcept {
        return fp_vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice, queueFamilyIndex, connection, visual_id);
    }
#endif
#if (defined(VK_EXT_directfb_surface))
    VkResult createDirectFBSurfaceEXT(const VkDirectFBSurfaceCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateDirectFBSurfaceEXT(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_EXT_directfb_surface))
    VkBool32 getPhysicalDeviceDirectFBPresentationSupportEXT(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, IDirectFB* dfb) const noexcept {
        return fp_vkGetPhysicalDeviceDirectFBPresentationSupportEXT(physicalDevice, queueFamilyIndex, dfb);
    }
#endif
#if (defined(VK_FUCHSIA_imagepipe_surface))
    VkResult createImagePipeSurfaceFUCHSIA(const VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateImagePipeSurfaceFUCHSIA(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_GGP_stream_descriptor_surface))
    VkResult createStreamDescriptorSurfaceGGP(const VkStreamDescriptorSurfaceCreateInfoGGP* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateStreamDescriptorSurfaceGGP(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_QNX_screen_surface))
    VkResult createScreenSurfaceQNX(const VkScreenSurfaceCreateInfoQNX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateScreenSurfaceQNX(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_QNX_screen_surface))
    VkBool32 getPhysicalDeviceScreenPresentationSupportQNX(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct _screen_window* window) const noexcept {
        return fp_vkGetPhysicalDeviceScreenPresentationSupportQNX(physicalDevice, queueFamilyIndex, window);
    }
#endif
#if (defined(VK_EXT_debug_report))
    VkResult createDebugReportCallbackEXT(const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) const noexcept {
        return fp_vkCreateDebugReportCallbackEXT(instance, pCreateInfo, pAllocator, pCallback);
    }
#endif
#if (defined(VK_EXT_debug_report))
    void destroyDebugReportCallbackEXT(VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyDebugReportCallbackEXT(instance, callback, pAllocator);
    }
#endif
#if (defined(VK_EXT_debug_report))
    void debugReportMessageEXT(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage) const noexcept {
        fp_vkDebugReportMessageEXT(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage);
    }
#endif
#if (defined(VK_NV_external_memory_capabilities))
    VkResult getPhysicalDeviceExternalImageFormatPropertiesNV(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType, VkExternalImageFormatPropertiesNV* pExternalImageFormatProperties) const noexcept {
        return fp_vkGetPhysicalDeviceExternalImageFormatPropertiesNV(physicalDevice, format, type, tiling, usage, flags, externalHandleType, pExternalImageFormatProperties);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2KHR* pFeatures) const noexcept {
        fp_vkGetPhysicalDeviceFeatures2(physicalDevice, pFeatures);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2KHR* pProperties) const noexcept {
        fp_vkGetPhysicalDeviceProperties2(physicalDevice, pProperties);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getPhysicalDeviceFormatProperties2(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2KHR* pFormatProperties) const noexcept {
        fp_vkGetPhysicalDeviceFormatProperties2(physicalDevice, format, pFormatProperties);
    }
#endif
#if (defined(VK_VERSION_1_1))
    VkResult getPhysicalDeviceImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2KHR* pImageFormatInfo, VkImageFormatProperties2KHR* pImageFormatProperties) const noexcept {
        return fp_vkGetPhysicalDeviceImageFormatProperties2(physicalDevice, pImageFormatInfo, pImageFormatProperties);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getPhysicalDeviceQueueFamilyProperties2(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2KHR* pQueueFamilyProperties) const noexcept {
        fp_vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getPhysicalDeviceMemoryProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2KHR* pMemoryProperties) const noexcept {
        fp_vkGetPhysicalDeviceMemoryProperties2(physicalDevice, pMemoryProperties);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getPhysicalDeviceSparseImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2KHR* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2KHR* pProperties) const noexcept {
        fp_vkGetPhysicalDeviceSparseImageFormatProperties2(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getPhysicalDeviceExternalBufferProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfoKHR* pExternalBufferInfo, VkExternalBufferPropertiesKHR* pExternalBufferProperties) const noexcept {
        fp_vkGetPhysicalDeviceExternalBufferProperties(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    }
#endif
#if (defined(VK_NV_external_memory_sci_buf))
    VkResult getPhysicalDeviceExternalMemorySciBufPropertiesNV(VkPhysicalDevice physicalDevice, VkExternalMemoryHandleTypeFlagBitsKHR handleType, NvSciBufObj handle, VkMemorySciBufPropertiesNV* pMemorySciBufProperties) const noexcept {
        return fp_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV(physicalDevice, handleType, handle, pMemorySciBufProperties);
    }
#endif
#if (defined(VK_NV_external_memory_sci_buf))
    VkResult getPhysicalDeviceSciBufAttributesNV(VkPhysicalDevice physicalDevice, NvSciBufAttrList pAttributes) const noexcept {
        return fp_vkGetPhysicalDeviceSciBufAttributesNV(physicalDevice, pAttributes);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getPhysicalDeviceExternalSemaphoreProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfoKHR* pExternalSemaphoreInfo, VkExternalSemaphorePropertiesKHR* pExternalSemaphoreProperties) const noexcept {
        fp_vkGetPhysicalDeviceExternalSemaphoreProperties(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getPhysicalDeviceExternalFenceProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfoKHR* pExternalFenceInfo, VkExternalFencePropertiesKHR* pExternalFenceProperties) const noexcept {
        fp_vkGetPhysicalDeviceExternalFenceProperties(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    }
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
    VkResult getPhysicalDeviceSciSyncAttributesNV(VkPhysicalDevice physicalDevice, const VkSciSyncAttributesInfoNV* pSciSyncAttributesInfo, NvSciSyncAttrList pAttributes) const noexcept {
        return fp_vkGetPhysicalDeviceSciSyncAttributesNV(physicalDevice, pSciSyncAttributesInfo, pAttributes);
    }
#endif
#if (defined(VK_EXT_direct_mode_display))
    VkResult releaseDisplayEXT(VkPhysicalDevice physicalDevice, VkDisplayKHR display) const noexcept {
        return fp_vkReleaseDisplayEXT(physicalDevice, display);
    }
#endif
#if (defined(VK_EXT_acquire_xlib_display))
    VkResult acquireXlibDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, VkDisplayKHR display) const noexcept {
        return fp_vkAcquireXlibDisplayEXT(physicalDevice, dpy, display);
    }
#endif
#if (defined(VK_EXT_acquire_xlib_display))
    VkResult getRandROutputDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, RROutput rrOutput, VkDisplayKHR* pDisplay) const noexcept {
        return fp_vkGetRandROutputDisplayEXT(physicalDevice, dpy, rrOutput, pDisplay);
    }
#endif
#if (defined(VK_NV_acquire_winrt_display))
    VkResult acquireWinrtDisplayNV(VkPhysicalDevice physicalDevice, VkDisplayKHR display) const noexcept {
        return fp_vkAcquireWinrtDisplayNV(physicalDevice, display);
    }
#endif
#if (defined(VK_NV_acquire_winrt_display))
    VkResult getWinrtDisplayNV(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay) const noexcept {
        return fp_vkGetWinrtDisplayNV(physicalDevice, deviceRelativeId, pDisplay);
    }
#endif
#if (defined(VK_EXT_display_surface_counter))
    VkResult getPhysicalDeviceSurfaceCapabilities2EXT(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilities2EXT* pSurfaceCapabilities) const noexcept {
        return fp_vkGetPhysicalDeviceSurfaceCapabilities2EXT(physicalDevice, surface, pSurfaceCapabilities);
    }
#endif
#if (defined(VK_VERSION_1_1))
    VkResult enumeratePhysicalDeviceGroups(uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupPropertiesKHR* pPhysicalDeviceGroupProperties) const noexcept {
        return fp_vkEnumeratePhysicalDeviceGroups(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    }
#endif
#if (defined(VK_KHR_swapchain)) || (defined(VK_KHR_device_group))
    VkResult getPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pRectCount, VkRect2D* pRects) const noexcept {
        return fp_vkGetPhysicalDevicePresentRectanglesKHR(physicalDevice, surface, pRectCount, pRects);
    }
#endif
#if (defined(VK_MVK_ios_surface))
    VkResult createIOSSurfaceMVK(const VkIOSSurfaceCreateInfoMVK* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateIOSSurfaceMVK(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_MVK_macos_surface))
    VkResult createMacOSSurfaceMVK(const VkMacOSSurfaceCreateInfoMVK* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateMacOSSurfaceMVK(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_EXT_metal_surface))
    VkResult createMetalSurfaceEXT(const VkMetalSurfaceCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateMetalSurfaceEXT(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_EXT_sample_locations))
    void getPhysicalDeviceMultisamplePropertiesEXT(VkPhysicalDevice physicalDevice, VkSampleCountFlagBits samples, VkMultisamplePropertiesEXT* pMultisampleProperties) const noexcept {
        fp_vkGetPhysicalDeviceMultisamplePropertiesEXT(physicalDevice, samples, pMultisampleProperties);
    }
#endif
#if (defined(VK_KHR_get_surface_capabilities2))
    VkResult getPhysicalDeviceSurfaceCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkSurfaceCapabilities2KHR* pSurfaceCapabilities) const noexcept {
        return fp_vkGetPhysicalDeviceSurfaceCapabilities2KHR(physicalDevice, pSurfaceInfo, pSurfaceCapabilities);
    }
#endif
#if (defined(VK_KHR_get_surface_capabilities2))
    VkResult getPhysicalDeviceSurfaceFormats2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pSurfaceFormatCount, VkSurfaceFormat2KHR* pSurfaceFormats) const noexcept {
        return fp_vkGetPhysicalDeviceSurfaceFormats2KHR(physicalDevice, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats);
    }
#endif
#if (defined(VK_KHR_get_display_properties2))
    VkResult getPhysicalDeviceDisplayProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayProperties2KHR* pProperties) const noexcept {
        return fp_vkGetPhysicalDeviceDisplayProperties2KHR(physicalDevice, pPropertyCount, pProperties);
    }
#endif
#if (defined(VK_KHR_get_display_properties2))
    VkResult getPhysicalDeviceDisplayPlaneProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlaneProperties2KHR* pProperties) const noexcept {
        return fp_vkGetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice, pPropertyCount, pProperties);
    }
#endif
#if (defined(VK_KHR_get_display_properties2))
    VkResult getDisplayModeProperties2KHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModeProperties2KHR* pProperties) const noexcept {
        return fp_vkGetDisplayModeProperties2KHR(physicalDevice, display, pPropertyCount, pProperties);
    }
#endif
#if (defined(VK_KHR_get_display_properties2))
    VkResult getDisplayPlaneCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo, VkDisplayPlaneCapabilities2KHR* pCapabilities) const noexcept {
        return fp_vkGetDisplayPlaneCapabilities2KHR(physicalDevice, pDisplayPlaneInfo, pCapabilities);
    }
#endif
#if (defined(VK_KHR_calibrated_timestamps))
    VkResult getPhysicalDeviceCalibrateableTimeDomainsKHR(VkPhysicalDevice physicalDevice, uint32_t* pTimeDomainCount, VkTimeDomainEXT* pTimeDomains) const noexcept {
        return fp_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR(physicalDevice, pTimeDomainCount, pTimeDomains);
    }
#endif
#if (defined(VK_EXT_debug_utils))
    VkResult createDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pMessenger) const noexcept {
        return fp_vkCreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pMessenger);
    }
#endif
#if (defined(VK_EXT_debug_utils))
    void destroyDebugUtilsMessengerEXT(VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyDebugUtilsMessengerEXT(instance, messenger, pAllocator);
    }
#endif
#if (defined(VK_EXT_debug_utils))
    void submitDebugUtilsMessageEXT(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData) const noexcept {
        fp_vkSubmitDebugUtilsMessageEXT(instance, messageSeverity, messageTypes, pCallbackData);
    }
#endif
#if (defined(VK_NV_cooperative_matrix))
    VkResult getPhysicalDeviceCooperativeMatrixPropertiesNV(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkCooperativeMatrixPropertiesNV* pProperties) const noexcept {
        return fp_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV(physicalDevice, pPropertyCount, pProperties);
    }
#endif
#if (defined(VK_EXT_full_screen_exclusive))
    VkResult getPhysicalDeviceSurfacePresentModes2EXT(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes) const noexcept {
        return fp_vkGetPhysicalDeviceSurfacePresentModes2EXT(physicalDevice, pSurfaceInfo, pPresentModeCount, pPresentModes);
    }
#endif
#if (defined(VK_KHR_performance_query))
    VkResult enumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, uint32_t* pCounterCount, VkPerformanceCounterKHR* pCounters, VkPerformanceCounterDescriptionKHR* pCounterDescriptions) const noexcept {
        return fp_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(physicalDevice, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions);
    }
#endif
#if (defined(VK_KHR_performance_query))
    void getPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(VkPhysicalDevice physicalDevice, const VkQueryPoolPerformanceCreateInfoKHR* pPerformanceQueryCreateInfo, uint32_t* pNumPasses) const noexcept {
        fp_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(physicalDevice, pPerformanceQueryCreateInfo, pNumPasses);
    }
#endif
#if (defined(VK_EXT_headless_surface))
    VkResult createHeadlessSurfaceEXT(const VkHeadlessSurfaceCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) const noexcept {
        return fp_vkCreateHeadlessSurfaceEXT(instance, pCreateInfo, pAllocator, pSurface);
    }
#endif
#if (defined(VK_NV_coverage_reduction_mode))
    VkResult getPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(VkPhysicalDevice physicalDevice, uint32_t* pCombinationCount, VkFramebufferMixedSamplesCombinationNV* pCombinations) const noexcept {
        return fp_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(physicalDevice, pCombinationCount, pCombinations);
    }
#endif
#if (defined(VK_VERSION_1_3))
    VkResult getPhysicalDeviceToolProperties(VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolPropertiesEXT* pToolProperties) const noexcept {
        return fp_vkGetPhysicalDeviceToolProperties(physicalDevice, pToolCount, pToolProperties);
    }
#endif
#if (defined(VK_KHR_object_refresh))
    VkResult getPhysicalDeviceRefreshableObjectTypesKHR(VkPhysicalDevice physicalDevice, uint32_t* pRefreshableObjectTypeCount, VkObjectType* pRefreshableObjectTypes) const noexcept {
        return fp_vkGetPhysicalDeviceRefreshableObjectTypesKHR(physicalDevice, pRefreshableObjectTypeCount, pRefreshableObjectTypes);
    }
#endif
#if (defined(VK_KHR_fragment_shading_rate))
    VkResult getPhysicalDeviceFragmentShadingRatesKHR(VkPhysicalDevice physicalDevice, uint32_t* pFragmentShadingRateCount, VkPhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates) const noexcept {
        return fp_vkGetPhysicalDeviceFragmentShadingRatesKHR(physicalDevice, pFragmentShadingRateCount, pFragmentShadingRates);
    }
#endif
#if (defined(VK_KHR_video_queue))
    VkResult getPhysicalDeviceVideoCapabilitiesKHR(VkPhysicalDevice physicalDevice, const VkVideoProfileInfoKHR* pVideoProfile, VkVideoCapabilitiesKHR* pCapabilities) const noexcept {
        return fp_vkGetPhysicalDeviceVideoCapabilitiesKHR(physicalDevice, pVideoProfile, pCapabilities);
    }
#endif
#if (defined(VK_KHR_video_queue))
    VkResult getPhysicalDeviceVideoFormatPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceVideoFormatInfoKHR* pVideoFormatInfo, uint32_t* pVideoFormatPropertyCount, VkVideoFormatPropertiesKHR* pVideoFormatProperties) const noexcept {
        return fp_vkGetPhysicalDeviceVideoFormatPropertiesKHR(physicalDevice, pVideoFormatInfo, pVideoFormatPropertyCount, pVideoFormatProperties);
    }
#endif
#if (defined(VK_KHR_video_encode_queue))
    VkResult getPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR* pQualityLevelInfo, VkVideoEncodeQualityLevelPropertiesKHR* pQualityLevelProperties) const noexcept {
        return fp_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(physicalDevice, pQualityLevelInfo, pQualityLevelProperties);
    }
#endif
#if (defined(VK_EXT_acquire_drm_display))
    VkResult acquireDrmDisplayEXT(VkPhysicalDevice physicalDevice, int32_t drmFd, VkDisplayKHR display) const noexcept {
        return fp_vkAcquireDrmDisplayEXT(physicalDevice, drmFd, display);
    }
#endif
#if (defined(VK_EXT_acquire_drm_display))
    VkResult getDrmDisplayEXT(VkPhysicalDevice physicalDevice, int32_t drmFd, uint32_t connectorId, VkDisplayKHR* display) const noexcept {
        return fp_vkGetDrmDisplayEXT(physicalDevice, drmFd, connectorId, display);
    }
#endif
#if (defined(VK_NV_optical_flow))
    VkResult getPhysicalDeviceOpticalFlowImageFormatsNV(VkPhysicalDevice physicalDevice, const VkOpticalFlowImageFormatInfoNV* pOpticalFlowImageFormatInfo, uint32_t* pFormatCount, VkOpticalFlowImageFormatPropertiesNV* pImageFormatProperties) const noexcept {
        return fp_vkGetPhysicalDeviceOpticalFlowImageFormatsNV(physicalDevice, pOpticalFlowImageFormatInfo, pFormatCount, pImageFormatProperties);
    }
#endif
#if (defined(VK_KHR_cooperative_matrix))
    VkResult getPhysicalDeviceCooperativeMatrixPropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkCooperativeMatrixPropertiesKHR* pProperties) const noexcept {
        return fp_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(physicalDevice, pPropertyCount, pProperties);
    }
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
    void getPhysicalDeviceFeatures2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2KHR* pFeatures) const noexcept {
        fp_vkGetPhysicalDeviceFeatures2KHR(physicalDevice, pFeatures);
    }
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
    void getPhysicalDeviceProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2KHR* pProperties) const noexcept {
        fp_vkGetPhysicalDeviceProperties2KHR(physicalDevice, pProperties);
    }
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
    void getPhysicalDeviceFormatProperties2KHR(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2KHR* pFormatProperties) const noexcept {
        fp_vkGetPhysicalDeviceFormatProperties2KHR(physicalDevice, format, pFormatProperties);
    }
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
    VkResult getPhysicalDeviceImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2KHR* pImageFormatInfo, VkImageFormatProperties2KHR* pImageFormatProperties) const noexcept {
        return fp_vkGetPhysicalDeviceImageFormatProperties2KHR(physicalDevice, pImageFormatInfo, pImageFormatProperties);
    }
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
    void getPhysicalDeviceQueueFamilyProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2KHR* pQueueFamilyProperties) const noexcept {
        fp_vkGetPhysicalDeviceQueueFamilyProperties2KHR(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    }
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
    void getPhysicalDeviceMemoryProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2KHR* pMemoryProperties) const noexcept {
        fp_vkGetPhysicalDeviceMemoryProperties2KHR(physicalDevice, pMemoryProperties);
    }
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
    void getPhysicalDeviceSparseImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2KHR* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2KHR* pProperties) const noexcept {
        fp_vkGetPhysicalDeviceSparseImageFormatProperties2KHR(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    }
#endif
#if (defined(VK_KHR_external_memory_capabilities))
    void getPhysicalDeviceExternalBufferPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfoKHR* pExternalBufferInfo, VkExternalBufferPropertiesKHR* pExternalBufferProperties) const noexcept {
        fp_vkGetPhysicalDeviceExternalBufferPropertiesKHR(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    }
#endif
#if (defined(VK_KHR_external_semaphore_capabilities))
    void getPhysicalDeviceExternalSemaphorePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfoKHR* pExternalSemaphoreInfo, VkExternalSemaphorePropertiesKHR* pExternalSemaphoreProperties) const noexcept {
        fp_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    }
#endif
#if (defined(VK_KHR_external_fence_capabilities))
    void getPhysicalDeviceExternalFencePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfoKHR* pExternalFenceInfo, VkExternalFencePropertiesKHR* pExternalFenceProperties) const noexcept {
        fp_vkGetPhysicalDeviceExternalFencePropertiesKHR(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    }
#endif
#if (defined(VK_KHR_device_group_creation))
    VkResult enumeratePhysicalDeviceGroupsKHR(uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupPropertiesKHR* pPhysicalDeviceGroupProperties) const noexcept {
        return fp_vkEnumeratePhysicalDeviceGroupsKHR(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    }
#endif
#if (defined(VK_EXT_calibrated_timestamps))
    VkResult getPhysicalDeviceCalibrateableTimeDomainsEXT(VkPhysicalDevice physicalDevice, uint32_t* pTimeDomainCount, VkTimeDomainEXT* pTimeDomains) const noexcept {
        return fp_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(physicalDevice, pTimeDomainCount, pTimeDomains);
    }
#endif
#if (defined(VK_EXT_tooling_info))
    VkResult getPhysicalDeviceToolPropertiesEXT(VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolPropertiesEXT* pToolProperties) const noexcept {
        return fp_vkGetPhysicalDeviceToolPropertiesEXT(physicalDevice, pToolCount, pToolProperties);
    }
#endif
    PFN_vkDestroyInstance fp_vkDestroyInstance = nullptr;
    PFN_vkEnumeratePhysicalDevices fp_vkEnumeratePhysicalDevices = nullptr;
    PFN_vkGetInstanceProcAddr fp_vkGetInstanceProcAddr = nullptr;
    PFN_vkGetPhysicalDeviceProperties fp_vkGetPhysicalDeviceProperties = nullptr;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties fp_vkGetPhysicalDeviceQueueFamilyProperties = nullptr;
    PFN_vkGetPhysicalDeviceMemoryProperties fp_vkGetPhysicalDeviceMemoryProperties = nullptr;
    PFN_vkGetPhysicalDeviceFeatures fp_vkGetPhysicalDeviceFeatures = nullptr;
    PFN_vkGetPhysicalDeviceFormatProperties fp_vkGetPhysicalDeviceFormatProperties = nullptr;
    PFN_vkGetPhysicalDeviceImageFormatProperties fp_vkGetPhysicalDeviceImageFormatProperties = nullptr;
    PFN_vkEnumerateDeviceLayerProperties fp_vkEnumerateDeviceLayerProperties = nullptr;
    PFN_vkEnumerateDeviceExtensionProperties fp_vkEnumerateDeviceExtensionProperties = nullptr;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties fp_vkGetPhysicalDeviceSparseImageFormatProperties = nullptr;
#if (defined(VK_KHR_android_surface))
    PFN_vkCreateAndroidSurfaceKHR fp_vkCreateAndroidSurfaceKHR = nullptr;
#else
    void * fp_vkCreateAndroidSurfaceKHR{};
#endif
#if (defined(VK_KHR_display))
    PFN_vkGetPhysicalDeviceDisplayPropertiesKHR fp_vkGetPhysicalDeviceDisplayPropertiesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceDisplayPropertiesKHR{};
#endif
#if (defined(VK_KHR_display))
    PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR fp_vkGetPhysicalDeviceDisplayPlanePropertiesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceDisplayPlanePropertiesKHR{};
#endif
#if (defined(VK_KHR_display))
    PFN_vkGetDisplayPlaneSupportedDisplaysKHR fp_vkGetDisplayPlaneSupportedDisplaysKHR = nullptr;
#else
    void * fp_vkGetDisplayPlaneSupportedDisplaysKHR{};
#endif
#if (defined(VK_KHR_display))
    PFN_vkGetDisplayModePropertiesKHR fp_vkGetDisplayModePropertiesKHR = nullptr;
#else
    void * fp_vkGetDisplayModePropertiesKHR{};
#endif
#if (defined(VK_KHR_display))
    PFN_vkCreateDisplayModeKHR fp_vkCreateDisplayModeKHR = nullptr;
#else
    void * fp_vkCreateDisplayModeKHR{};
#endif
#if (defined(VK_KHR_display))
    PFN_vkGetDisplayPlaneCapabilitiesKHR fp_vkGetDisplayPlaneCapabilitiesKHR = nullptr;
#else
    void * fp_vkGetDisplayPlaneCapabilitiesKHR{};
#endif
#if (defined(VK_KHR_display))
    PFN_vkCreateDisplayPlaneSurfaceKHR fp_vkCreateDisplayPlaneSurfaceKHR = nullptr;
#else
    void * fp_vkCreateDisplayPlaneSurfaceKHR{};
#endif
#if (defined(VK_KHR_surface))
    PFN_vkDestroySurfaceKHR fp_vkDestroySurfaceKHR = nullptr;
#else
    void * fp_vkDestroySurfaceKHR{};
#endif
#if (defined(VK_KHR_surface))
    PFN_vkGetPhysicalDeviceSurfaceSupportKHR fp_vkGetPhysicalDeviceSurfaceSupportKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceSurfaceSupportKHR{};
#endif
#if (defined(VK_KHR_surface))
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR fp_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceSurfaceCapabilitiesKHR{};
#endif
#if (defined(VK_KHR_surface))
    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR fp_vkGetPhysicalDeviceSurfaceFormatsKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceSurfaceFormatsKHR{};
#endif
#if (defined(VK_KHR_surface))
    PFN_vkGetPhysicalDeviceSurfacePresentModesKHR fp_vkGetPhysicalDeviceSurfacePresentModesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceSurfacePresentModesKHR{};
#endif
#if (defined(VK_NN_vi_surface))
    PFN_vkCreateViSurfaceNN fp_vkCreateViSurfaceNN = nullptr;
#else
    void * fp_vkCreateViSurfaceNN{};
#endif
#if (defined(VK_KHR_wayland_surface))
    PFN_vkCreateWaylandSurfaceKHR fp_vkCreateWaylandSurfaceKHR = nullptr;
#else
    void * fp_vkCreateWaylandSurfaceKHR{};
#endif
#if (defined(VK_KHR_wayland_surface))
    PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR fp_vkGetPhysicalDeviceWaylandPresentationSupportKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceWaylandPresentationSupportKHR{};
#endif
#if (defined(VK_KHR_win32_surface))
    PFN_vkCreateWin32SurfaceKHR fp_vkCreateWin32SurfaceKHR = nullptr;
#else
    void * fp_vkCreateWin32SurfaceKHR{};
#endif
#if (defined(VK_KHR_win32_surface))
    PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR fp_vkGetPhysicalDeviceWin32PresentationSupportKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceWin32PresentationSupportKHR{};
#endif
#if (defined(VK_KHR_xlib_surface))
    PFN_vkCreateXlibSurfaceKHR fp_vkCreateXlibSurfaceKHR = nullptr;
#else
    void * fp_vkCreateXlibSurfaceKHR{};
#endif
#if (defined(VK_KHR_xlib_surface))
    PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR fp_vkGetPhysicalDeviceXlibPresentationSupportKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceXlibPresentationSupportKHR{};
#endif
#if (defined(VK_KHR_xcb_surface))
    PFN_vkCreateXcbSurfaceKHR fp_vkCreateXcbSurfaceKHR = nullptr;
#else
    void * fp_vkCreateXcbSurfaceKHR{};
#endif
#if (defined(VK_KHR_xcb_surface))
    PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR fp_vkGetPhysicalDeviceXcbPresentationSupportKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceXcbPresentationSupportKHR{};
#endif
#if (defined(VK_EXT_directfb_surface))
    PFN_vkCreateDirectFBSurfaceEXT fp_vkCreateDirectFBSurfaceEXT = nullptr;
#else
    void * fp_vkCreateDirectFBSurfaceEXT{};
#endif
#if (defined(VK_EXT_directfb_surface))
    PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT fp_vkGetPhysicalDeviceDirectFBPresentationSupportEXT = nullptr;
#else
    void * fp_vkGetPhysicalDeviceDirectFBPresentationSupportEXT{};
#endif
#if (defined(VK_FUCHSIA_imagepipe_surface))
    PFN_vkCreateImagePipeSurfaceFUCHSIA fp_vkCreateImagePipeSurfaceFUCHSIA = nullptr;
#else
    void * fp_vkCreateImagePipeSurfaceFUCHSIA{};
#endif
#if (defined(VK_GGP_stream_descriptor_surface))
    PFN_vkCreateStreamDescriptorSurfaceGGP fp_vkCreateStreamDescriptorSurfaceGGP = nullptr;
#else
    void * fp_vkCreateStreamDescriptorSurfaceGGP{};
#endif
#if (defined(VK_QNX_screen_surface))
    PFN_vkCreateScreenSurfaceQNX fp_vkCreateScreenSurfaceQNX = nullptr;
#else
    void * fp_vkCreateScreenSurfaceQNX{};
#endif
#if (defined(VK_QNX_screen_surface))
    PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX fp_vkGetPhysicalDeviceScreenPresentationSupportQNX = nullptr;
#else
    void * fp_vkGetPhysicalDeviceScreenPresentationSupportQNX{};
#endif
#if (defined(VK_EXT_debug_report))
    PFN_vkCreateDebugReportCallbackEXT fp_vkCreateDebugReportCallbackEXT = nullptr;
#else
    void * fp_vkCreateDebugReportCallbackEXT{};
#endif
#if (defined(VK_EXT_debug_report))
    PFN_vkDestroyDebugReportCallbackEXT fp_vkDestroyDebugReportCallbackEXT = nullptr;
#else
    void * fp_vkDestroyDebugReportCallbackEXT{};
#endif
#if (defined(VK_EXT_debug_report))
    PFN_vkDebugReportMessageEXT fp_vkDebugReportMessageEXT = nullptr;
#else
    void * fp_vkDebugReportMessageEXT{};
#endif
#if (defined(VK_NV_external_memory_capabilities))
    PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV fp_vkGetPhysicalDeviceExternalImageFormatPropertiesNV = nullptr;
#else
    void * fp_vkGetPhysicalDeviceExternalImageFormatPropertiesNV{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetPhysicalDeviceFeatures2 fp_vkGetPhysicalDeviceFeatures2 = nullptr;
#else
    void * fp_vkGetPhysicalDeviceFeatures2{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetPhysicalDeviceProperties2 fp_vkGetPhysicalDeviceProperties2 = nullptr;
#else
    void * fp_vkGetPhysicalDeviceProperties2{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetPhysicalDeviceFormatProperties2 fp_vkGetPhysicalDeviceFormatProperties2 = nullptr;
#else
    void * fp_vkGetPhysicalDeviceFormatProperties2{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetPhysicalDeviceImageFormatProperties2 fp_vkGetPhysicalDeviceImageFormatProperties2 = nullptr;
#else
    void * fp_vkGetPhysicalDeviceImageFormatProperties2{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2 fp_vkGetPhysicalDeviceQueueFamilyProperties2 = nullptr;
#else
    void * fp_vkGetPhysicalDeviceQueueFamilyProperties2{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetPhysicalDeviceMemoryProperties2 fp_vkGetPhysicalDeviceMemoryProperties2 = nullptr;
#else
    void * fp_vkGetPhysicalDeviceMemoryProperties2{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 fp_vkGetPhysicalDeviceSparseImageFormatProperties2 = nullptr;
#else
    void * fp_vkGetPhysicalDeviceSparseImageFormatProperties2{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetPhysicalDeviceExternalBufferProperties fp_vkGetPhysicalDeviceExternalBufferProperties = nullptr;
#else
    void * fp_vkGetPhysicalDeviceExternalBufferProperties{};
#endif
#if (defined(VK_NV_external_memory_sci_buf))
    PFN_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV fp_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV = nullptr;
#else
    void * fp_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV{};
#endif
#if (defined(VK_NV_external_memory_sci_buf))
    PFN_vkGetPhysicalDeviceSciBufAttributesNV fp_vkGetPhysicalDeviceSciBufAttributesNV = nullptr;
#else
    void * fp_vkGetPhysicalDeviceSciBufAttributesNV{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetPhysicalDeviceExternalSemaphoreProperties fp_vkGetPhysicalDeviceExternalSemaphoreProperties = nullptr;
#else
    void * fp_vkGetPhysicalDeviceExternalSemaphoreProperties{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetPhysicalDeviceExternalFenceProperties fp_vkGetPhysicalDeviceExternalFenceProperties = nullptr;
#else
    void * fp_vkGetPhysicalDeviceExternalFenceProperties{};
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
    PFN_vkGetPhysicalDeviceSciSyncAttributesNV fp_vkGetPhysicalDeviceSciSyncAttributesNV = nullptr;
#else
    void * fp_vkGetPhysicalDeviceSciSyncAttributesNV{};
#endif
#if (defined(VK_EXT_direct_mode_display))
    PFN_vkReleaseDisplayEXT fp_vkReleaseDisplayEXT = nullptr;
#else
    void * fp_vkReleaseDisplayEXT{};
#endif
#if (defined(VK_EXT_acquire_xlib_display))
    PFN_vkAcquireXlibDisplayEXT fp_vkAcquireXlibDisplayEXT = nullptr;
#else
    void * fp_vkAcquireXlibDisplayEXT{};
#endif
#if (defined(VK_EXT_acquire_xlib_display))
    PFN_vkGetRandROutputDisplayEXT fp_vkGetRandROutputDisplayEXT = nullptr;
#else
    void * fp_vkGetRandROutputDisplayEXT{};
#endif
#if (defined(VK_NV_acquire_winrt_display))
    PFN_vkAcquireWinrtDisplayNV fp_vkAcquireWinrtDisplayNV = nullptr;
#else
    void * fp_vkAcquireWinrtDisplayNV{};
#endif
#if (defined(VK_NV_acquire_winrt_display))
    PFN_vkGetWinrtDisplayNV fp_vkGetWinrtDisplayNV = nullptr;
#else
    void * fp_vkGetWinrtDisplayNV{};
#endif
#if (defined(VK_EXT_display_surface_counter))
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT fp_vkGetPhysicalDeviceSurfaceCapabilities2EXT = nullptr;
#else
    void * fp_vkGetPhysicalDeviceSurfaceCapabilities2EXT{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkEnumeratePhysicalDeviceGroups fp_vkEnumeratePhysicalDeviceGroups = nullptr;
#else
    void * fp_vkEnumeratePhysicalDeviceGroups{};
#endif
#if (defined(VK_KHR_swapchain)) || (defined(VK_KHR_device_group))
    PFN_vkGetPhysicalDevicePresentRectanglesKHR fp_vkGetPhysicalDevicePresentRectanglesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDevicePresentRectanglesKHR{};
#endif
#if (defined(VK_MVK_ios_surface))
    PFN_vkCreateIOSSurfaceMVK fp_vkCreateIOSSurfaceMVK = nullptr;
#else
    void * fp_vkCreateIOSSurfaceMVK{};
#endif
#if (defined(VK_MVK_macos_surface))
    PFN_vkCreateMacOSSurfaceMVK fp_vkCreateMacOSSurfaceMVK = nullptr;
#else
    void * fp_vkCreateMacOSSurfaceMVK{};
#endif
#if (defined(VK_EXT_metal_surface))
    PFN_vkCreateMetalSurfaceEXT fp_vkCreateMetalSurfaceEXT = nullptr;
#else
    void * fp_vkCreateMetalSurfaceEXT{};
#endif
#if (defined(VK_EXT_sample_locations))
    PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT fp_vkGetPhysicalDeviceMultisamplePropertiesEXT = nullptr;
#else
    void * fp_vkGetPhysicalDeviceMultisamplePropertiesEXT{};
#endif
#if (defined(VK_KHR_get_surface_capabilities2))
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR fp_vkGetPhysicalDeviceSurfaceCapabilities2KHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceSurfaceCapabilities2KHR{};
#endif
#if (defined(VK_KHR_get_surface_capabilities2))
    PFN_vkGetPhysicalDeviceSurfaceFormats2KHR fp_vkGetPhysicalDeviceSurfaceFormats2KHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceSurfaceFormats2KHR{};
#endif
#if (defined(VK_KHR_get_display_properties2))
    PFN_vkGetPhysicalDeviceDisplayProperties2KHR fp_vkGetPhysicalDeviceDisplayProperties2KHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceDisplayProperties2KHR{};
#endif
#if (defined(VK_KHR_get_display_properties2))
    PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR fp_vkGetPhysicalDeviceDisplayPlaneProperties2KHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceDisplayPlaneProperties2KHR{};
#endif
#if (defined(VK_KHR_get_display_properties2))
    PFN_vkGetDisplayModeProperties2KHR fp_vkGetDisplayModeProperties2KHR = nullptr;
#else
    void * fp_vkGetDisplayModeProperties2KHR{};
#endif
#if (defined(VK_KHR_get_display_properties2))
    PFN_vkGetDisplayPlaneCapabilities2KHR fp_vkGetDisplayPlaneCapabilities2KHR = nullptr;
#else
    void * fp_vkGetDisplayPlaneCapabilities2KHR{};
#endif
#if (defined(VK_KHR_calibrated_timestamps))
    PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR fp_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR{};
#endif
#if (defined(VK_EXT_debug_utils))
    PFN_vkCreateDebugUtilsMessengerEXT fp_vkCreateDebugUtilsMessengerEXT = nullptr;
#else
    void * fp_vkCreateDebugUtilsMessengerEXT{};
#endif
#if (defined(VK_EXT_debug_utils))
    PFN_vkDestroyDebugUtilsMessengerEXT fp_vkDestroyDebugUtilsMessengerEXT = nullptr;
#else
    void * fp_vkDestroyDebugUtilsMessengerEXT{};
#endif
#if (defined(VK_EXT_debug_utils))
    PFN_vkSubmitDebugUtilsMessageEXT fp_vkSubmitDebugUtilsMessageEXT = nullptr;
#else
    void * fp_vkSubmitDebugUtilsMessageEXT{};
#endif
#if (defined(VK_NV_cooperative_matrix))
    PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV fp_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = nullptr;
#else
    void * fp_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV{};
#endif
#if (defined(VK_EXT_full_screen_exclusive))
    PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT fp_vkGetPhysicalDeviceSurfacePresentModes2EXT = nullptr;
#else
    void * fp_vkGetPhysicalDeviceSurfacePresentModes2EXT{};
#endif
#if (defined(VK_KHR_performance_query))
    PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR fp_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = nullptr;
#else
    void * fp_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR{};
#endif
#if (defined(VK_KHR_performance_query))
    PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR fp_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR{};
#endif
#if (defined(VK_EXT_headless_surface))
    PFN_vkCreateHeadlessSurfaceEXT fp_vkCreateHeadlessSurfaceEXT = nullptr;
#else
    void * fp_vkCreateHeadlessSurfaceEXT{};
#endif
#if (defined(VK_NV_coverage_reduction_mode))
    PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV fp_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = nullptr;
#else
    void * fp_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkGetPhysicalDeviceToolProperties fp_vkGetPhysicalDeviceToolProperties = nullptr;
#else
    void * fp_vkGetPhysicalDeviceToolProperties{};
#endif
#if (defined(VK_KHR_object_refresh))
    PFN_vkGetPhysicalDeviceRefreshableObjectTypesKHR fp_vkGetPhysicalDeviceRefreshableObjectTypesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceRefreshableObjectTypesKHR{};
#endif
#if (defined(VK_KHR_fragment_shading_rate))
    PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR fp_vkGetPhysicalDeviceFragmentShadingRatesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceFragmentShadingRatesKHR{};
#endif
#if (defined(VK_KHR_video_queue))
    PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR fp_vkGetPhysicalDeviceVideoCapabilitiesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceVideoCapabilitiesKHR{};
#endif
#if (defined(VK_KHR_video_queue))
    PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR fp_vkGetPhysicalDeviceVideoFormatPropertiesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceVideoFormatPropertiesKHR{};
#endif
#if (defined(VK_KHR_video_encode_queue))
    PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR fp_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR{};
#endif
#if (defined(VK_EXT_acquire_drm_display))
    PFN_vkAcquireDrmDisplayEXT fp_vkAcquireDrmDisplayEXT = nullptr;
#else
    void * fp_vkAcquireDrmDisplayEXT{};
#endif
#if (defined(VK_EXT_acquire_drm_display))
    PFN_vkGetDrmDisplayEXT fp_vkGetDrmDisplayEXT = nullptr;
#else
    void * fp_vkGetDrmDisplayEXT{};
#endif
#if (defined(VK_NV_optical_flow))
    PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV fp_vkGetPhysicalDeviceOpticalFlowImageFormatsNV = nullptr;
#else
    void * fp_vkGetPhysicalDeviceOpticalFlowImageFormatsNV{};
#endif
#if (defined(VK_KHR_cooperative_matrix))
    PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR fp_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR{};
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
    PFN_vkGetPhysicalDeviceFeatures2KHR fp_vkGetPhysicalDeviceFeatures2KHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceFeatures2KHR{};
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
    PFN_vkGetPhysicalDeviceProperties2KHR fp_vkGetPhysicalDeviceProperties2KHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceProperties2KHR{};
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
    PFN_vkGetPhysicalDeviceFormatProperties2KHR fp_vkGetPhysicalDeviceFormatProperties2KHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceFormatProperties2KHR{};
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
    PFN_vkGetPhysicalDeviceImageFormatProperties2KHR fp_vkGetPhysicalDeviceImageFormatProperties2KHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceImageFormatProperties2KHR{};
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR fp_vkGetPhysicalDeviceQueueFamilyProperties2KHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceQueueFamilyProperties2KHR{};
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
    PFN_vkGetPhysicalDeviceMemoryProperties2KHR fp_vkGetPhysicalDeviceMemoryProperties2KHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceMemoryProperties2KHR{};
#endif
#if (defined(VK_KHR_get_physical_device_properties2))
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR fp_vkGetPhysicalDeviceSparseImageFormatProperties2KHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceSparseImageFormatProperties2KHR{};
#endif
#if (defined(VK_KHR_external_memory_capabilities))
    PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR fp_vkGetPhysicalDeviceExternalBufferPropertiesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceExternalBufferPropertiesKHR{};
#endif
#if (defined(VK_KHR_external_semaphore_capabilities))
    PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR fp_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR{};
#endif
#if (defined(VK_KHR_external_fence_capabilities))
    PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR fp_vkGetPhysicalDeviceExternalFencePropertiesKHR = nullptr;
#else
    void * fp_vkGetPhysicalDeviceExternalFencePropertiesKHR{};
#endif
#if (defined(VK_KHR_device_group_creation))
    PFN_vkEnumeratePhysicalDeviceGroupsKHR fp_vkEnumeratePhysicalDeviceGroupsKHR = nullptr;
#else
    void * fp_vkEnumeratePhysicalDeviceGroupsKHR{};
#endif
#if (defined(VK_EXT_calibrated_timestamps))
    PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT fp_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT = nullptr;
#else
    void * fp_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT{};
#endif
#if (defined(VK_EXT_tooling_info))
    PFN_vkGetPhysicalDeviceToolPropertiesEXT fp_vkGetPhysicalDeviceToolPropertiesEXT = nullptr;
#else
    void * fp_vkGetPhysicalDeviceToolPropertiesEXT{};
#endif
    bool is_populated() const { return populated; }
    VkInstance instance = VK_NULL_HANDLE;
private:
     bool populated = false;
};

struct DispatchTable {
    DispatchTable() = default;
    DispatchTable(VkDevice device, PFN_vkGetDeviceProcAddr procAddr) : device(device), populated(true) {
        fp_vkGetDeviceQueue = reinterpret_cast<PFN_vkGetDeviceQueue>(procAddr(device, "vkGetDeviceQueue"));
        fp_vkQueueSubmit = reinterpret_cast<PFN_vkQueueSubmit>(procAddr(device, "vkQueueSubmit"));
        fp_vkQueueWaitIdle = reinterpret_cast<PFN_vkQueueWaitIdle>(procAddr(device, "vkQueueWaitIdle"));
        fp_vkDeviceWaitIdle = reinterpret_cast<PFN_vkDeviceWaitIdle>(procAddr(device, "vkDeviceWaitIdle"));
        fp_vkAllocateMemory = reinterpret_cast<PFN_vkAllocateMemory>(procAddr(device, "vkAllocateMemory"));
        fp_vkFreeMemory = reinterpret_cast<PFN_vkFreeMemory>(procAddr(device, "vkFreeMemory"));
        fp_vkMapMemory = reinterpret_cast<PFN_vkMapMemory>(procAddr(device, "vkMapMemory"));
        fp_vkUnmapMemory = reinterpret_cast<PFN_vkUnmapMemory>(procAddr(device, "vkUnmapMemory"));
        fp_vkFlushMappedMemoryRanges = reinterpret_cast<PFN_vkFlushMappedMemoryRanges>(procAddr(device, "vkFlushMappedMemoryRanges"));
        fp_vkInvalidateMappedMemoryRanges = reinterpret_cast<PFN_vkInvalidateMappedMemoryRanges>(procAddr(device, "vkInvalidateMappedMemoryRanges"));
        fp_vkGetDeviceMemoryCommitment = reinterpret_cast<PFN_vkGetDeviceMemoryCommitment>(procAddr(device, "vkGetDeviceMemoryCommitment"));
        fp_vkGetBufferMemoryRequirements = reinterpret_cast<PFN_vkGetBufferMemoryRequirements>(procAddr(device, "vkGetBufferMemoryRequirements"));
        fp_vkBindBufferMemory = reinterpret_cast<PFN_vkBindBufferMemory>(procAddr(device, "vkBindBufferMemory"));
        fp_vkGetImageMemoryRequirements = reinterpret_cast<PFN_vkGetImageMemoryRequirements>(procAddr(device, "vkGetImageMemoryRequirements"));
        fp_vkBindImageMemory = reinterpret_cast<PFN_vkBindImageMemory>(procAddr(device, "vkBindImageMemory"));
        fp_vkGetImageSparseMemoryRequirements = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements>(procAddr(device, "vkGetImageSparseMemoryRequirements"));
        fp_vkQueueBindSparse = reinterpret_cast<PFN_vkQueueBindSparse>(procAddr(device, "vkQueueBindSparse"));
        fp_vkCreateFence = reinterpret_cast<PFN_vkCreateFence>(procAddr(device, "vkCreateFence"));
        fp_vkDestroyFence = reinterpret_cast<PFN_vkDestroyFence>(procAddr(device, "vkDestroyFence"));
        fp_vkResetFences = reinterpret_cast<PFN_vkResetFences>(procAddr(device, "vkResetFences"));
        fp_vkGetFenceStatus = reinterpret_cast<PFN_vkGetFenceStatus>(procAddr(device, "vkGetFenceStatus"));
        fp_vkWaitForFences = reinterpret_cast<PFN_vkWaitForFences>(procAddr(device, "vkWaitForFences"));
        fp_vkCreateSemaphore = reinterpret_cast<PFN_vkCreateSemaphore>(procAddr(device, "vkCreateSemaphore"));
        fp_vkDestroySemaphore = reinterpret_cast<PFN_vkDestroySemaphore>(procAddr(device, "vkDestroySemaphore"));
        fp_vkCreateEvent = reinterpret_cast<PFN_vkCreateEvent>(procAddr(device, "vkCreateEvent"));
        fp_vkDestroyEvent = reinterpret_cast<PFN_vkDestroyEvent>(procAddr(device, "vkDestroyEvent"));
        fp_vkGetEventStatus = reinterpret_cast<PFN_vkGetEventStatus>(procAddr(device, "vkGetEventStatus"));
        fp_vkSetEvent = reinterpret_cast<PFN_vkSetEvent>(procAddr(device, "vkSetEvent"));
        fp_vkResetEvent = reinterpret_cast<PFN_vkResetEvent>(procAddr(device, "vkResetEvent"));
        fp_vkCreateQueryPool = reinterpret_cast<PFN_vkCreateQueryPool>(procAddr(device, "vkCreateQueryPool"));
        fp_vkDestroyQueryPool = reinterpret_cast<PFN_vkDestroyQueryPool>(procAddr(device, "vkDestroyQueryPool"));
        fp_vkGetQueryPoolResults = reinterpret_cast<PFN_vkGetQueryPoolResults>(procAddr(device, "vkGetQueryPoolResults"));
#if (defined(VK_VERSION_1_2))
        fp_vkResetQueryPool = reinterpret_cast<PFN_vkResetQueryPool>(procAddr(device, "vkResetQueryPool"));
#endif
        fp_vkCreateBuffer = reinterpret_cast<PFN_vkCreateBuffer>(procAddr(device, "vkCreateBuffer"));
        fp_vkDestroyBuffer = reinterpret_cast<PFN_vkDestroyBuffer>(procAddr(device, "vkDestroyBuffer"));
        fp_vkCreateBufferView = reinterpret_cast<PFN_vkCreateBufferView>(procAddr(device, "vkCreateBufferView"));
        fp_vkDestroyBufferView = reinterpret_cast<PFN_vkDestroyBufferView>(procAddr(device, "vkDestroyBufferView"));
        fp_vkCreateImage = reinterpret_cast<PFN_vkCreateImage>(procAddr(device, "vkCreateImage"));
        fp_vkDestroyImage = reinterpret_cast<PFN_vkDestroyImage>(procAddr(device, "vkDestroyImage"));
        fp_vkGetImageSubresourceLayout = reinterpret_cast<PFN_vkGetImageSubresourceLayout>(procAddr(device, "vkGetImageSubresourceLayout"));
        fp_vkCreateImageView = reinterpret_cast<PFN_vkCreateImageView>(procAddr(device, "vkCreateImageView"));
        fp_vkDestroyImageView = reinterpret_cast<PFN_vkDestroyImageView>(procAddr(device, "vkDestroyImageView"));
        fp_vkCreateShaderModule = reinterpret_cast<PFN_vkCreateShaderModule>(procAddr(device, "vkCreateShaderModule"));
        fp_vkDestroyShaderModule = reinterpret_cast<PFN_vkDestroyShaderModule>(procAddr(device, "vkDestroyShaderModule"));
        fp_vkCreatePipelineCache = reinterpret_cast<PFN_vkCreatePipelineCache>(procAddr(device, "vkCreatePipelineCache"));
        fp_vkDestroyPipelineCache = reinterpret_cast<PFN_vkDestroyPipelineCache>(procAddr(device, "vkDestroyPipelineCache"));
        fp_vkGetPipelineCacheData = reinterpret_cast<PFN_vkGetPipelineCacheData>(procAddr(device, "vkGetPipelineCacheData"));
        fp_vkMergePipelineCaches = reinterpret_cast<PFN_vkMergePipelineCaches>(procAddr(device, "vkMergePipelineCaches"));
        fp_vkCreateGraphicsPipelines = reinterpret_cast<PFN_vkCreateGraphicsPipelines>(procAddr(device, "vkCreateGraphicsPipelines"));
        fp_vkCreateComputePipelines = reinterpret_cast<PFN_vkCreateComputePipelines>(procAddr(device, "vkCreateComputePipelines"));
#if (defined(VK_HUAWEI_subpass_shading))
        fp_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI = reinterpret_cast<PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI>(procAddr(device, "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI"));
#endif
        fp_vkDestroyPipeline = reinterpret_cast<PFN_vkDestroyPipeline>(procAddr(device, "vkDestroyPipeline"));
        fp_vkCreatePipelineLayout = reinterpret_cast<PFN_vkCreatePipelineLayout>(procAddr(device, "vkCreatePipelineLayout"));
        fp_vkDestroyPipelineLayout = reinterpret_cast<PFN_vkDestroyPipelineLayout>(procAddr(device, "vkDestroyPipelineLayout"));
        fp_vkCreateSampler = reinterpret_cast<PFN_vkCreateSampler>(procAddr(device, "vkCreateSampler"));
        fp_vkDestroySampler = reinterpret_cast<PFN_vkDestroySampler>(procAddr(device, "vkDestroySampler"));
        fp_vkCreateDescriptorSetLayout = reinterpret_cast<PFN_vkCreateDescriptorSetLayout>(procAddr(device, "vkCreateDescriptorSetLayout"));
        fp_vkDestroyDescriptorSetLayout = reinterpret_cast<PFN_vkDestroyDescriptorSetLayout>(procAddr(device, "vkDestroyDescriptorSetLayout"));
        fp_vkCreateDescriptorPool = reinterpret_cast<PFN_vkCreateDescriptorPool>(procAddr(device, "vkCreateDescriptorPool"));
        fp_vkDestroyDescriptorPool = reinterpret_cast<PFN_vkDestroyDescriptorPool>(procAddr(device, "vkDestroyDescriptorPool"));
        fp_vkResetDescriptorPool = reinterpret_cast<PFN_vkResetDescriptorPool>(procAddr(device, "vkResetDescriptorPool"));
        fp_vkAllocateDescriptorSets = reinterpret_cast<PFN_vkAllocateDescriptorSets>(procAddr(device, "vkAllocateDescriptorSets"));
        fp_vkFreeDescriptorSets = reinterpret_cast<PFN_vkFreeDescriptorSets>(procAddr(device, "vkFreeDescriptorSets"));
        fp_vkUpdateDescriptorSets = reinterpret_cast<PFN_vkUpdateDescriptorSets>(procAddr(device, "vkUpdateDescriptorSets"));
        fp_vkCreateFramebuffer = reinterpret_cast<PFN_vkCreateFramebuffer>(procAddr(device, "vkCreateFramebuffer"));
        fp_vkDestroyFramebuffer = reinterpret_cast<PFN_vkDestroyFramebuffer>(procAddr(device, "vkDestroyFramebuffer"));
        fp_vkCreateRenderPass = reinterpret_cast<PFN_vkCreateRenderPass>(procAddr(device, "vkCreateRenderPass"));
        fp_vkDestroyRenderPass = reinterpret_cast<PFN_vkDestroyRenderPass>(procAddr(device, "vkDestroyRenderPass"));
        fp_vkGetRenderAreaGranularity = reinterpret_cast<PFN_vkGetRenderAreaGranularity>(procAddr(device, "vkGetRenderAreaGranularity"));
#if (defined(VK_KHR_maintenance5))
        fp_vkGetRenderingAreaGranularityKHR = reinterpret_cast<PFN_vkGetRenderingAreaGranularityKHR>(procAddr(device, "vkGetRenderingAreaGranularityKHR"));
#endif
        fp_vkCreateCommandPool = reinterpret_cast<PFN_vkCreateCommandPool>(procAddr(device, "vkCreateCommandPool"));
        fp_vkDestroyCommandPool = reinterpret_cast<PFN_vkDestroyCommandPool>(procAddr(device, "vkDestroyCommandPool"));
        fp_vkResetCommandPool = reinterpret_cast<PFN_vkResetCommandPool>(procAddr(device, "vkResetCommandPool"));
        fp_vkAllocateCommandBuffers = reinterpret_cast<PFN_vkAllocateCommandBuffers>(procAddr(device, "vkAllocateCommandBuffers"));
        fp_vkFreeCommandBuffers = reinterpret_cast<PFN_vkFreeCommandBuffers>(procAddr(device, "vkFreeCommandBuffers"));
        fp_vkBeginCommandBuffer = reinterpret_cast<PFN_vkBeginCommandBuffer>(procAddr(device, "vkBeginCommandBuffer"));
        fp_vkEndCommandBuffer = reinterpret_cast<PFN_vkEndCommandBuffer>(procAddr(device, "vkEndCommandBuffer"));
        fp_vkResetCommandBuffer = reinterpret_cast<PFN_vkResetCommandBuffer>(procAddr(device, "vkResetCommandBuffer"));
        fp_vkCmdBindPipeline = reinterpret_cast<PFN_vkCmdBindPipeline>(procAddr(device, "vkCmdBindPipeline"));
#if (defined(VK_EXT_attachment_feedback_loop_dynamic_state))
        fp_vkCmdSetAttachmentFeedbackLoopEnableEXT = reinterpret_cast<PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT>(procAddr(device, "vkCmdSetAttachmentFeedbackLoopEnableEXT"));
#endif
        fp_vkCmdSetViewport = reinterpret_cast<PFN_vkCmdSetViewport>(procAddr(device, "vkCmdSetViewport"));
        fp_vkCmdSetScissor = reinterpret_cast<PFN_vkCmdSetScissor>(procAddr(device, "vkCmdSetScissor"));
        fp_vkCmdSetLineWidth = reinterpret_cast<PFN_vkCmdSetLineWidth>(procAddr(device, "vkCmdSetLineWidth"));
        fp_vkCmdSetDepthBias = reinterpret_cast<PFN_vkCmdSetDepthBias>(procAddr(device, "vkCmdSetDepthBias"));
        fp_vkCmdSetBlendConstants = reinterpret_cast<PFN_vkCmdSetBlendConstants>(procAddr(device, "vkCmdSetBlendConstants"));
        fp_vkCmdSetDepthBounds = reinterpret_cast<PFN_vkCmdSetDepthBounds>(procAddr(device, "vkCmdSetDepthBounds"));
        fp_vkCmdSetStencilCompareMask = reinterpret_cast<PFN_vkCmdSetStencilCompareMask>(procAddr(device, "vkCmdSetStencilCompareMask"));
        fp_vkCmdSetStencilWriteMask = reinterpret_cast<PFN_vkCmdSetStencilWriteMask>(procAddr(device, "vkCmdSetStencilWriteMask"));
        fp_vkCmdSetStencilReference = reinterpret_cast<PFN_vkCmdSetStencilReference>(procAddr(device, "vkCmdSetStencilReference"));
        fp_vkCmdBindDescriptorSets = reinterpret_cast<PFN_vkCmdBindDescriptorSets>(procAddr(device, "vkCmdBindDescriptorSets"));
        fp_vkCmdBindIndexBuffer = reinterpret_cast<PFN_vkCmdBindIndexBuffer>(procAddr(device, "vkCmdBindIndexBuffer"));
        fp_vkCmdBindVertexBuffers = reinterpret_cast<PFN_vkCmdBindVertexBuffers>(procAddr(device, "vkCmdBindVertexBuffers"));
        fp_vkCmdDraw = reinterpret_cast<PFN_vkCmdDraw>(procAddr(device, "vkCmdDraw"));
        fp_vkCmdDrawIndexed = reinterpret_cast<PFN_vkCmdDrawIndexed>(procAddr(device, "vkCmdDrawIndexed"));
#if (defined(VK_EXT_multi_draw))
        fp_vkCmdDrawMultiEXT = reinterpret_cast<PFN_vkCmdDrawMultiEXT>(procAddr(device, "vkCmdDrawMultiEXT"));
#endif
#if (defined(VK_EXT_multi_draw))
        fp_vkCmdDrawMultiIndexedEXT = reinterpret_cast<PFN_vkCmdDrawMultiIndexedEXT>(procAddr(device, "vkCmdDrawMultiIndexedEXT"));
#endif
        fp_vkCmdDrawIndirect = reinterpret_cast<PFN_vkCmdDrawIndirect>(procAddr(device, "vkCmdDrawIndirect"));
        fp_vkCmdDrawIndexedIndirect = reinterpret_cast<PFN_vkCmdDrawIndexedIndirect>(procAddr(device, "vkCmdDrawIndexedIndirect"));
        fp_vkCmdDispatch = reinterpret_cast<PFN_vkCmdDispatch>(procAddr(device, "vkCmdDispatch"));
        fp_vkCmdDispatchIndirect = reinterpret_cast<PFN_vkCmdDispatchIndirect>(procAddr(device, "vkCmdDispatchIndirect"));
#if (defined(VK_HUAWEI_subpass_shading))
        fp_vkCmdSubpassShadingHUAWEI = reinterpret_cast<PFN_vkCmdSubpassShadingHUAWEI>(procAddr(device, "vkCmdSubpassShadingHUAWEI"));
#endif
#if (defined(VK_HUAWEI_cluster_culling_shader))
        fp_vkCmdDrawClusterHUAWEI = reinterpret_cast<PFN_vkCmdDrawClusterHUAWEI>(procAddr(device, "vkCmdDrawClusterHUAWEI"));
#endif
#if (defined(VK_HUAWEI_cluster_culling_shader))
        fp_vkCmdDrawClusterIndirectHUAWEI = reinterpret_cast<PFN_vkCmdDrawClusterIndirectHUAWEI>(procAddr(device, "vkCmdDrawClusterIndirectHUAWEI"));
#endif
#if (defined(VK_NV_device_generated_commands_compute))
        fp_vkCmdUpdatePipelineIndirectBufferNV = reinterpret_cast<PFN_vkCmdUpdatePipelineIndirectBufferNV>(procAddr(device, "vkCmdUpdatePipelineIndirectBufferNV"));
#endif
        fp_vkCmdCopyBuffer = reinterpret_cast<PFN_vkCmdCopyBuffer>(procAddr(device, "vkCmdCopyBuffer"));
        fp_vkCmdCopyImage = reinterpret_cast<PFN_vkCmdCopyImage>(procAddr(device, "vkCmdCopyImage"));
        fp_vkCmdBlitImage = reinterpret_cast<PFN_vkCmdBlitImage>(procAddr(device, "vkCmdBlitImage"));
        fp_vkCmdCopyBufferToImage = reinterpret_cast<PFN_vkCmdCopyBufferToImage>(procAddr(device, "vkCmdCopyBufferToImage"));
        fp_vkCmdCopyImageToBuffer = reinterpret_cast<PFN_vkCmdCopyImageToBuffer>(procAddr(device, "vkCmdCopyImageToBuffer"));
#if (defined(VK_NV_copy_memory_indirect))
        fp_vkCmdCopyMemoryIndirectNV = reinterpret_cast<PFN_vkCmdCopyMemoryIndirectNV>(procAddr(device, "vkCmdCopyMemoryIndirectNV"));
#endif
#if (defined(VK_NV_copy_memory_indirect))
        fp_vkCmdCopyMemoryToImageIndirectNV = reinterpret_cast<PFN_vkCmdCopyMemoryToImageIndirectNV>(procAddr(device, "vkCmdCopyMemoryToImageIndirectNV"));
#endif
        fp_vkCmdUpdateBuffer = reinterpret_cast<PFN_vkCmdUpdateBuffer>(procAddr(device, "vkCmdUpdateBuffer"));
        fp_vkCmdFillBuffer = reinterpret_cast<PFN_vkCmdFillBuffer>(procAddr(device, "vkCmdFillBuffer"));
        fp_vkCmdClearColorImage = reinterpret_cast<PFN_vkCmdClearColorImage>(procAddr(device, "vkCmdClearColorImage"));
        fp_vkCmdClearDepthStencilImage = reinterpret_cast<PFN_vkCmdClearDepthStencilImage>(procAddr(device, "vkCmdClearDepthStencilImage"));
        fp_vkCmdClearAttachments = reinterpret_cast<PFN_vkCmdClearAttachments>(procAddr(device, "vkCmdClearAttachments"));
        fp_vkCmdResolveImage = reinterpret_cast<PFN_vkCmdResolveImage>(procAddr(device, "vkCmdResolveImage"));
        fp_vkCmdSetEvent = reinterpret_cast<PFN_vkCmdSetEvent>(procAddr(device, "vkCmdSetEvent"));
        fp_vkCmdResetEvent = reinterpret_cast<PFN_vkCmdResetEvent>(procAddr(device, "vkCmdResetEvent"));
        fp_vkCmdWaitEvents = reinterpret_cast<PFN_vkCmdWaitEvents>(procAddr(device, "vkCmdWaitEvents"));
        fp_vkCmdPipelineBarrier = reinterpret_cast<PFN_vkCmdPipelineBarrier>(procAddr(device, "vkCmdPipelineBarrier"));
        fp_vkCmdBeginQuery = reinterpret_cast<PFN_vkCmdBeginQuery>(procAddr(device, "vkCmdBeginQuery"));
        fp_vkCmdEndQuery = reinterpret_cast<PFN_vkCmdEndQuery>(procAddr(device, "vkCmdEndQuery"));
#if (defined(VK_EXT_conditional_rendering))
        fp_vkCmdBeginConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdBeginConditionalRenderingEXT>(procAddr(device, "vkCmdBeginConditionalRenderingEXT"));
#endif
#if (defined(VK_EXT_conditional_rendering))
        fp_vkCmdEndConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdEndConditionalRenderingEXT>(procAddr(device, "vkCmdEndConditionalRenderingEXT"));
#endif
        fp_vkCmdResetQueryPool = reinterpret_cast<PFN_vkCmdResetQueryPool>(procAddr(device, "vkCmdResetQueryPool"));
        fp_vkCmdWriteTimestamp = reinterpret_cast<PFN_vkCmdWriteTimestamp>(procAddr(device, "vkCmdWriteTimestamp"));
        fp_vkCmdCopyQueryPoolResults = reinterpret_cast<PFN_vkCmdCopyQueryPoolResults>(procAddr(device, "vkCmdCopyQueryPoolResults"));
        fp_vkCmdPushConstants = reinterpret_cast<PFN_vkCmdPushConstants>(procAddr(device, "vkCmdPushConstants"));
        fp_vkCmdBeginRenderPass = reinterpret_cast<PFN_vkCmdBeginRenderPass>(procAddr(device, "vkCmdBeginRenderPass"));
        fp_vkCmdNextSubpass = reinterpret_cast<PFN_vkCmdNextSubpass>(procAddr(device, "vkCmdNextSubpass"));
        fp_vkCmdEndRenderPass = reinterpret_cast<PFN_vkCmdEndRenderPass>(procAddr(device, "vkCmdEndRenderPass"));
        fp_vkCmdExecuteCommands = reinterpret_cast<PFN_vkCmdExecuteCommands>(procAddr(device, "vkCmdExecuteCommands"));
#if (defined(VK_KHR_display_swapchain))
        fp_vkCreateSharedSwapchainsKHR = reinterpret_cast<PFN_vkCreateSharedSwapchainsKHR>(procAddr(device, "vkCreateSharedSwapchainsKHR"));
#endif
#if (defined(VK_KHR_swapchain))
        fp_vkCreateSwapchainKHR = reinterpret_cast<PFN_vkCreateSwapchainKHR>(procAddr(device, "vkCreateSwapchainKHR"));
#endif
#if (defined(VK_KHR_swapchain))
        fp_vkDestroySwapchainKHR = reinterpret_cast<PFN_vkDestroySwapchainKHR>(procAddr(device, "vkDestroySwapchainKHR"));
#endif
#if (defined(VK_KHR_swapchain))
        fp_vkGetSwapchainImagesKHR = reinterpret_cast<PFN_vkGetSwapchainImagesKHR>(procAddr(device, "vkGetSwapchainImagesKHR"));
#endif
#if (defined(VK_KHR_swapchain))
        fp_vkAcquireNextImageKHR = reinterpret_cast<PFN_vkAcquireNextImageKHR>(procAddr(device, "vkAcquireNextImageKHR"));
#endif
#if (defined(VK_KHR_swapchain))
        fp_vkQueuePresentKHR = reinterpret_cast<PFN_vkQueuePresentKHR>(procAddr(device, "vkQueuePresentKHR"));
#endif
#if (defined(VK_EXT_debug_marker))
        fp_vkDebugMarkerSetObjectNameEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectNameEXT>(procAddr(device, "vkDebugMarkerSetObjectNameEXT"));
#endif
#if (defined(VK_EXT_debug_marker))
        fp_vkDebugMarkerSetObjectTagEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectTagEXT>(procAddr(device, "vkDebugMarkerSetObjectTagEXT"));
#endif
#if (defined(VK_EXT_debug_marker))
        fp_vkCmdDebugMarkerBeginEXT = reinterpret_cast<PFN_vkCmdDebugMarkerBeginEXT>(procAddr(device, "vkCmdDebugMarkerBeginEXT"));
#endif
#if (defined(VK_EXT_debug_marker))
        fp_vkCmdDebugMarkerEndEXT = reinterpret_cast<PFN_vkCmdDebugMarkerEndEXT>(procAddr(device, "vkCmdDebugMarkerEndEXT"));
#endif
#if (defined(VK_EXT_debug_marker))
        fp_vkCmdDebugMarkerInsertEXT = reinterpret_cast<PFN_vkCmdDebugMarkerInsertEXT>(procAddr(device, "vkCmdDebugMarkerInsertEXT"));
#endif
#if (defined(VK_NV_external_memory_win32))
        fp_vkGetMemoryWin32HandleNV = reinterpret_cast<PFN_vkGetMemoryWin32HandleNV>(procAddr(device, "vkGetMemoryWin32HandleNV"));
#endif
#if (defined(VK_NV_device_generated_commands))
        fp_vkCmdExecuteGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdExecuteGeneratedCommandsNV>(procAddr(device, "vkCmdExecuteGeneratedCommandsNV"));
#endif
#if (defined(VK_NV_device_generated_commands))
        fp_vkCmdPreprocessGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdPreprocessGeneratedCommandsNV>(procAddr(device, "vkCmdPreprocessGeneratedCommandsNV"));
#endif
#if (defined(VK_NV_device_generated_commands))
        fp_vkCmdBindPipelineShaderGroupNV = reinterpret_cast<PFN_vkCmdBindPipelineShaderGroupNV>(procAddr(device, "vkCmdBindPipelineShaderGroupNV"));
#endif
#if (defined(VK_NV_device_generated_commands))
        fp_vkGetGeneratedCommandsMemoryRequirementsNV = reinterpret_cast<PFN_vkGetGeneratedCommandsMemoryRequirementsNV>(procAddr(device, "vkGetGeneratedCommandsMemoryRequirementsNV"));
#endif
#if (defined(VK_NV_device_generated_commands))
        fp_vkCreateIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkCreateIndirectCommandsLayoutNV>(procAddr(device, "vkCreateIndirectCommandsLayoutNV"));
#endif
#if (defined(VK_NV_device_generated_commands))
        fp_vkDestroyIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkDestroyIndirectCommandsLayoutNV>(procAddr(device, "vkDestroyIndirectCommandsLayoutNV"));
#endif
#if (defined(VK_KHR_push_descriptor))
        fp_vkCmdPushDescriptorSetKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetKHR>(procAddr(device, "vkCmdPushDescriptorSetKHR"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkTrimCommandPool = reinterpret_cast<PFN_vkTrimCommandPool>(procAddr(device, "vkTrimCommandPool"));
#endif
#if (defined(VK_KHR_external_memory_win32))
        fp_vkGetMemoryWin32HandleKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandleKHR>(procAddr(device, "vkGetMemoryWin32HandleKHR"));
#endif
#if (defined(VK_KHR_external_memory_win32))
        fp_vkGetMemoryWin32HandlePropertiesKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandlePropertiesKHR>(procAddr(device, "vkGetMemoryWin32HandlePropertiesKHR"));
#endif
#if (defined(VK_KHR_external_memory_fd))
        fp_vkGetMemoryFdKHR = reinterpret_cast<PFN_vkGetMemoryFdKHR>(procAddr(device, "vkGetMemoryFdKHR"));
#endif
#if (defined(VK_KHR_external_memory_fd))
        fp_vkGetMemoryFdPropertiesKHR = reinterpret_cast<PFN_vkGetMemoryFdPropertiesKHR>(procAddr(device, "vkGetMemoryFdPropertiesKHR"));
#endif
#if (defined(VK_FUCHSIA_external_memory))
        fp_vkGetMemoryZirconHandleFUCHSIA = reinterpret_cast<PFN_vkGetMemoryZirconHandleFUCHSIA>(procAddr(device, "vkGetMemoryZirconHandleFUCHSIA"));
#endif
#if (defined(VK_FUCHSIA_external_memory))
        fp_vkGetMemoryZirconHandlePropertiesFUCHSIA = reinterpret_cast<PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA>(procAddr(device, "vkGetMemoryZirconHandlePropertiesFUCHSIA"));
#endif
#if (defined(VK_NV_external_memory_rdma))
        fp_vkGetMemoryRemoteAddressNV = reinterpret_cast<PFN_vkGetMemoryRemoteAddressNV>(procAddr(device, "vkGetMemoryRemoteAddressNV"));
#endif
#if (defined(VK_NV_external_memory_sci_buf))
        fp_vkGetMemorySciBufNV = reinterpret_cast<PFN_vkGetMemorySciBufNV>(procAddr(device, "vkGetMemorySciBufNV"));
#endif
#if (defined(VK_KHR_external_semaphore_win32))
        fp_vkGetSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkGetSemaphoreWin32HandleKHR>(procAddr(device, "vkGetSemaphoreWin32HandleKHR"));
#endif
#if (defined(VK_KHR_external_semaphore_win32))
        fp_vkImportSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkImportSemaphoreWin32HandleKHR>(procAddr(device, "vkImportSemaphoreWin32HandleKHR"));
#endif
#if (defined(VK_KHR_external_semaphore_fd))
        fp_vkGetSemaphoreFdKHR = reinterpret_cast<PFN_vkGetSemaphoreFdKHR>(procAddr(device, "vkGetSemaphoreFdKHR"));
#endif
#if (defined(VK_KHR_external_semaphore_fd))
        fp_vkImportSemaphoreFdKHR = reinterpret_cast<PFN_vkImportSemaphoreFdKHR>(procAddr(device, "vkImportSemaphoreFdKHR"));
#endif
#if (defined(VK_FUCHSIA_external_semaphore))
        fp_vkGetSemaphoreZirconHandleFUCHSIA = reinterpret_cast<PFN_vkGetSemaphoreZirconHandleFUCHSIA>(procAddr(device, "vkGetSemaphoreZirconHandleFUCHSIA"));
#endif
#if (defined(VK_FUCHSIA_external_semaphore))
        fp_vkImportSemaphoreZirconHandleFUCHSIA = reinterpret_cast<PFN_vkImportSemaphoreZirconHandleFUCHSIA>(procAddr(device, "vkImportSemaphoreZirconHandleFUCHSIA"));
#endif
#if (defined(VK_KHR_external_fence_win32))
        fp_vkGetFenceWin32HandleKHR = reinterpret_cast<PFN_vkGetFenceWin32HandleKHR>(procAddr(device, "vkGetFenceWin32HandleKHR"));
#endif
#if (defined(VK_KHR_external_fence_win32))
        fp_vkImportFenceWin32HandleKHR = reinterpret_cast<PFN_vkImportFenceWin32HandleKHR>(procAddr(device, "vkImportFenceWin32HandleKHR"));
#endif
#if (defined(VK_KHR_external_fence_fd))
        fp_vkGetFenceFdKHR = reinterpret_cast<PFN_vkGetFenceFdKHR>(procAddr(device, "vkGetFenceFdKHR"));
#endif
#if (defined(VK_KHR_external_fence_fd))
        fp_vkImportFenceFdKHR = reinterpret_cast<PFN_vkImportFenceFdKHR>(procAddr(device, "vkImportFenceFdKHR"));
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
        fp_vkGetFenceSciSyncFenceNV = reinterpret_cast<PFN_vkGetFenceSciSyncFenceNV>(procAddr(device, "vkGetFenceSciSyncFenceNV"));
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
        fp_vkGetFenceSciSyncObjNV = reinterpret_cast<PFN_vkGetFenceSciSyncObjNV>(procAddr(device, "vkGetFenceSciSyncObjNV"));
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
        fp_vkImportFenceSciSyncFenceNV = reinterpret_cast<PFN_vkImportFenceSciSyncFenceNV>(procAddr(device, "vkImportFenceSciSyncFenceNV"));
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
        fp_vkImportFenceSciSyncObjNV = reinterpret_cast<PFN_vkImportFenceSciSyncObjNV>(procAddr(device, "vkImportFenceSciSyncObjNV"));
#endif
#if (defined(VK_NV_external_sci_sync))
        fp_vkGetSemaphoreSciSyncObjNV = reinterpret_cast<PFN_vkGetSemaphoreSciSyncObjNV>(procAddr(device, "vkGetSemaphoreSciSyncObjNV"));
#endif
#if (defined(VK_NV_external_sci_sync))
        fp_vkImportSemaphoreSciSyncObjNV = reinterpret_cast<PFN_vkImportSemaphoreSciSyncObjNV>(procAddr(device, "vkImportSemaphoreSciSyncObjNV"));
#endif
#if (defined(VK_NV_external_sci_sync2))
        fp_vkCreateSemaphoreSciSyncPoolNV = reinterpret_cast<PFN_vkCreateSemaphoreSciSyncPoolNV>(procAddr(device, "vkCreateSemaphoreSciSyncPoolNV"));
#endif
#if (defined(VK_NV_external_sci_sync2))
        fp_vkDestroySemaphoreSciSyncPoolNV = reinterpret_cast<PFN_vkDestroySemaphoreSciSyncPoolNV>(procAddr(device, "vkDestroySemaphoreSciSyncPoolNV"));
#endif
#if (defined(VK_EXT_display_control))
        fp_vkDisplayPowerControlEXT = reinterpret_cast<PFN_vkDisplayPowerControlEXT>(procAddr(device, "vkDisplayPowerControlEXT"));
#endif
#if (defined(VK_EXT_display_control))
        fp_vkRegisterDeviceEventEXT = reinterpret_cast<PFN_vkRegisterDeviceEventEXT>(procAddr(device, "vkRegisterDeviceEventEXT"));
#endif
#if (defined(VK_EXT_display_control))
        fp_vkRegisterDisplayEventEXT = reinterpret_cast<PFN_vkRegisterDisplayEventEXT>(procAddr(device, "vkRegisterDisplayEventEXT"));
#endif
#if (defined(VK_EXT_display_control))
        fp_vkGetSwapchainCounterEXT = reinterpret_cast<PFN_vkGetSwapchainCounterEXT>(procAddr(device, "vkGetSwapchainCounterEXT"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetDeviceGroupPeerMemoryFeatures = reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeatures>(procAddr(device, "vkGetDeviceGroupPeerMemoryFeatures"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkBindBufferMemory2 = reinterpret_cast<PFN_vkBindBufferMemory2>(procAddr(device, "vkBindBufferMemory2"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkBindImageMemory2 = reinterpret_cast<PFN_vkBindImageMemory2>(procAddr(device, "vkBindImageMemory2"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkCmdSetDeviceMask = reinterpret_cast<PFN_vkCmdSetDeviceMask>(procAddr(device, "vkCmdSetDeviceMask"));
#endif
#if (defined(VK_KHR_swapchain)) || (defined(VK_KHR_device_group))
        fp_vkGetDeviceGroupPresentCapabilitiesKHR = reinterpret_cast<PFN_vkGetDeviceGroupPresentCapabilitiesKHR>(procAddr(device, "vkGetDeviceGroupPresentCapabilitiesKHR"));
#endif
#if (defined(VK_KHR_swapchain)) || (defined(VK_KHR_device_group))
        fp_vkGetDeviceGroupSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModesKHR>(procAddr(device, "vkGetDeviceGroupSurfacePresentModesKHR"));
#endif
#if (defined(VK_KHR_swapchain)) || (defined(VK_KHR_device_group))
        fp_vkAcquireNextImage2KHR = reinterpret_cast<PFN_vkAcquireNextImage2KHR>(procAddr(device, "vkAcquireNextImage2KHR"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkCmdDispatchBase = reinterpret_cast<PFN_vkCmdDispatchBase>(procAddr(device, "vkCmdDispatchBase"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkCreateDescriptorUpdateTemplate = reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplate>(procAddr(device, "vkCreateDescriptorUpdateTemplate"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkDestroyDescriptorUpdateTemplate = reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplate>(procAddr(device, "vkDestroyDescriptorUpdateTemplate"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkUpdateDescriptorSetWithTemplate = reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplate>(procAddr(device, "vkUpdateDescriptorSetWithTemplate"));
#endif
#if (defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_descriptor_update_template))
        fp_vkCmdPushDescriptorSetWithTemplateKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetWithTemplateKHR>(procAddr(device, "vkCmdPushDescriptorSetWithTemplateKHR"));
#endif
#if (defined(VK_EXT_hdr_metadata))
        fp_vkSetHdrMetadataEXT = reinterpret_cast<PFN_vkSetHdrMetadataEXT>(procAddr(device, "vkSetHdrMetadataEXT"));
#endif
#if (defined(VK_KHR_shared_presentable_image))
        fp_vkGetSwapchainStatusKHR = reinterpret_cast<PFN_vkGetSwapchainStatusKHR>(procAddr(device, "vkGetSwapchainStatusKHR"));
#endif
#if (defined(VK_GOOGLE_display_timing))
        fp_vkGetRefreshCycleDurationGOOGLE = reinterpret_cast<PFN_vkGetRefreshCycleDurationGOOGLE>(procAddr(device, "vkGetRefreshCycleDurationGOOGLE"));
#endif
#if (defined(VK_GOOGLE_display_timing))
        fp_vkGetPastPresentationTimingGOOGLE = reinterpret_cast<PFN_vkGetPastPresentationTimingGOOGLE>(procAddr(device, "vkGetPastPresentationTimingGOOGLE"));
#endif
#if (defined(VK_NV_clip_space_w_scaling))
        fp_vkCmdSetViewportWScalingNV = reinterpret_cast<PFN_vkCmdSetViewportWScalingNV>(procAddr(device, "vkCmdSetViewportWScalingNV"));
#endif
#if (defined(VK_EXT_discard_rectangles))
        fp_vkCmdSetDiscardRectangleEXT = reinterpret_cast<PFN_vkCmdSetDiscardRectangleEXT>(procAddr(device, "vkCmdSetDiscardRectangleEXT"));
#endif
#if ((defined(VK_EXT_discard_rectangles))) && VK_HEADER_VERSION >= 241
        fp_vkCmdSetDiscardRectangleEnableEXT = reinterpret_cast<PFN_vkCmdSetDiscardRectangleEnableEXT>(procAddr(device, "vkCmdSetDiscardRectangleEnableEXT"));
#endif
#if ((defined(VK_EXT_discard_rectangles))) && VK_HEADER_VERSION >= 241
        fp_vkCmdSetDiscardRectangleModeEXT = reinterpret_cast<PFN_vkCmdSetDiscardRectangleModeEXT>(procAddr(device, "vkCmdSetDiscardRectangleModeEXT"));
#endif
#if (defined(VK_EXT_sample_locations))
        fp_vkCmdSetSampleLocationsEXT = reinterpret_cast<PFN_vkCmdSetSampleLocationsEXT>(procAddr(device, "vkCmdSetSampleLocationsEXT"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetBufferMemoryRequirements2 = reinterpret_cast<PFN_vkGetBufferMemoryRequirements2>(procAddr(device, "vkGetBufferMemoryRequirements2"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetImageMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageMemoryRequirements2>(procAddr(device, "vkGetImageMemoryRequirements2"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetImageSparseMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2>(procAddr(device, "vkGetImageSparseMemoryRequirements2"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkGetDeviceBufferMemoryRequirements = reinterpret_cast<PFN_vkGetDeviceBufferMemoryRequirements>(procAddr(device, "vkGetDeviceBufferMemoryRequirements"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkGetDeviceImageMemoryRequirements = reinterpret_cast<PFN_vkGetDeviceImageMemoryRequirements>(procAddr(device, "vkGetDeviceImageMemoryRequirements"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkGetDeviceImageSparseMemoryRequirements = reinterpret_cast<PFN_vkGetDeviceImageSparseMemoryRequirements>(procAddr(device, "vkGetDeviceImageSparseMemoryRequirements"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkCreateSamplerYcbcrConversion = reinterpret_cast<PFN_vkCreateSamplerYcbcrConversion>(procAddr(device, "vkCreateSamplerYcbcrConversion"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkDestroySamplerYcbcrConversion = reinterpret_cast<PFN_vkDestroySamplerYcbcrConversion>(procAddr(device, "vkDestroySamplerYcbcrConversion"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetDeviceQueue2 = reinterpret_cast<PFN_vkGetDeviceQueue2>(procAddr(device, "vkGetDeviceQueue2"));
#endif
#if (defined(VK_EXT_validation_cache))
        fp_vkCreateValidationCacheEXT = reinterpret_cast<PFN_vkCreateValidationCacheEXT>(procAddr(device, "vkCreateValidationCacheEXT"));
#endif
#if (defined(VK_EXT_validation_cache))
        fp_vkDestroyValidationCacheEXT = reinterpret_cast<PFN_vkDestroyValidationCacheEXT>(procAddr(device, "vkDestroyValidationCacheEXT"));
#endif
#if (defined(VK_EXT_validation_cache))
        fp_vkGetValidationCacheDataEXT = reinterpret_cast<PFN_vkGetValidationCacheDataEXT>(procAddr(device, "vkGetValidationCacheDataEXT"));
#endif
#if (defined(VK_EXT_validation_cache))
        fp_vkMergeValidationCachesEXT = reinterpret_cast<PFN_vkMergeValidationCachesEXT>(procAddr(device, "vkMergeValidationCachesEXT"));
#endif
#if (defined(VK_VERSION_1_1))
        fp_vkGetDescriptorSetLayoutSupport = reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupport>(procAddr(device, "vkGetDescriptorSetLayoutSupport"));
#endif
#if (defined(VK_ANDROID_native_buffer))
        fp_vkGetSwapchainGrallocUsageANDROID = reinterpret_cast<PFN_vkGetSwapchainGrallocUsageANDROID>(procAddr(device, "vkGetSwapchainGrallocUsageANDROID"));
#endif
#if (defined(VK_ANDROID_native_buffer))
        fp_vkGetSwapchainGrallocUsage2ANDROID = reinterpret_cast<PFN_vkGetSwapchainGrallocUsage2ANDROID>(procAddr(device, "vkGetSwapchainGrallocUsage2ANDROID"));
#endif
#if (defined(VK_ANDROID_native_buffer))
        fp_vkAcquireImageANDROID = reinterpret_cast<PFN_vkAcquireImageANDROID>(procAddr(device, "vkAcquireImageANDROID"));
#endif
#if (defined(VK_ANDROID_native_buffer))
        fp_vkQueueSignalReleaseImageANDROID = reinterpret_cast<PFN_vkQueueSignalReleaseImageANDROID>(procAddr(device, "vkQueueSignalReleaseImageANDROID"));
#endif
#if (defined(VK_AMD_shader_info))
        fp_vkGetShaderInfoAMD = reinterpret_cast<PFN_vkGetShaderInfoAMD>(procAddr(device, "vkGetShaderInfoAMD"));
#endif
#if (defined(VK_AMD_display_native_hdr))
        fp_vkSetLocalDimmingAMD = reinterpret_cast<PFN_vkSetLocalDimmingAMD>(procAddr(device, "vkSetLocalDimmingAMD"));
#endif
#if (defined(VK_KHR_calibrated_timestamps))
        fp_vkGetCalibratedTimestampsKHR = reinterpret_cast<PFN_vkGetCalibratedTimestampsKHR>(procAddr(device, "vkGetCalibratedTimestampsKHR"));
#endif
#if (defined(VK_EXT_debug_utils))
        fp_vkSetDebugUtilsObjectNameEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectNameEXT>(procAddr(device, "vkSetDebugUtilsObjectNameEXT"));
#endif
#if (defined(VK_EXT_debug_utils))
        fp_vkSetDebugUtilsObjectTagEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectTagEXT>(procAddr(device, "vkSetDebugUtilsObjectTagEXT"));
#endif
#if (defined(VK_EXT_debug_utils))
        fp_vkQueueBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueBeginDebugUtilsLabelEXT>(procAddr(device, "vkQueueBeginDebugUtilsLabelEXT"));
#endif
#if (defined(VK_EXT_debug_utils))
        fp_vkQueueEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueEndDebugUtilsLabelEXT>(procAddr(device, "vkQueueEndDebugUtilsLabelEXT"));
#endif
#if (defined(VK_EXT_debug_utils))
        fp_vkQueueInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueInsertDebugUtilsLabelEXT>(procAddr(device, "vkQueueInsertDebugUtilsLabelEXT"));
#endif
#if (defined(VK_EXT_debug_utils))
        fp_vkCmdBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdBeginDebugUtilsLabelEXT>(procAddr(device, "vkCmdBeginDebugUtilsLabelEXT"));
#endif
#if (defined(VK_EXT_debug_utils))
        fp_vkCmdEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdEndDebugUtilsLabelEXT>(procAddr(device, "vkCmdEndDebugUtilsLabelEXT"));
#endif
#if (defined(VK_EXT_debug_utils))
        fp_vkCmdInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdInsertDebugUtilsLabelEXT>(procAddr(device, "vkCmdInsertDebugUtilsLabelEXT"));
#endif
#if (defined(VK_EXT_external_memory_host))
        fp_vkGetMemoryHostPointerPropertiesEXT = reinterpret_cast<PFN_vkGetMemoryHostPointerPropertiesEXT>(procAddr(device, "vkGetMemoryHostPointerPropertiesEXT"));
#endif
#if (defined(VK_AMD_buffer_marker))
        fp_vkCmdWriteBufferMarkerAMD = reinterpret_cast<PFN_vkCmdWriteBufferMarkerAMD>(procAddr(device, "vkCmdWriteBufferMarkerAMD"));
#endif
#if (defined(VK_VERSION_1_2))
        fp_vkCreateRenderPass2 = reinterpret_cast<PFN_vkCreateRenderPass2>(procAddr(device, "vkCreateRenderPass2"));
#endif
#if (defined(VK_VERSION_1_2))
        fp_vkCmdBeginRenderPass2 = reinterpret_cast<PFN_vkCmdBeginRenderPass2>(procAddr(device, "vkCmdBeginRenderPass2"));
#endif
#if (defined(VK_VERSION_1_2))
        fp_vkCmdNextSubpass2 = reinterpret_cast<PFN_vkCmdNextSubpass2>(procAddr(device, "vkCmdNextSubpass2"));
#endif
#if (defined(VK_VERSION_1_2))
        fp_vkCmdEndRenderPass2 = reinterpret_cast<PFN_vkCmdEndRenderPass2>(procAddr(device, "vkCmdEndRenderPass2"));
#endif
#if (defined(VK_VERSION_1_2))
        fp_vkGetSemaphoreCounterValue = reinterpret_cast<PFN_vkGetSemaphoreCounterValue>(procAddr(device, "vkGetSemaphoreCounterValue"));
#endif
#if (defined(VK_VERSION_1_2))
        fp_vkWaitSemaphores = reinterpret_cast<PFN_vkWaitSemaphores>(procAddr(device, "vkWaitSemaphores"));
#endif
#if (defined(VK_VERSION_1_2))
        fp_vkSignalSemaphore = reinterpret_cast<PFN_vkSignalSemaphore>(procAddr(device, "vkSignalSemaphore"));
#endif
#if (defined(VK_ANDROID_external_memory_android_hardware_buffer))
        fp_vkGetAndroidHardwareBufferPropertiesANDROID = reinterpret_cast<PFN_vkGetAndroidHardwareBufferPropertiesANDROID>(procAddr(device, "vkGetAndroidHardwareBufferPropertiesANDROID"));
#endif
#if (defined(VK_ANDROID_external_memory_android_hardware_buffer))
        fp_vkGetMemoryAndroidHardwareBufferANDROID = reinterpret_cast<PFN_vkGetMemoryAndroidHardwareBufferANDROID>(procAddr(device, "vkGetMemoryAndroidHardwareBufferANDROID"));
#endif
#if (defined(VK_VERSION_1_2))
        fp_vkCmdDrawIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndirectCount>(procAddr(device, "vkCmdDrawIndirectCount"));
#endif
#if (defined(VK_VERSION_1_2))
        fp_vkCmdDrawIndexedIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCount>(procAddr(device, "vkCmdDrawIndexedIndirectCount"));
#endif
#if (defined(VK_NV_device_diagnostic_checkpoints))
        fp_vkCmdSetCheckpointNV = reinterpret_cast<PFN_vkCmdSetCheckpointNV>(procAddr(device, "vkCmdSetCheckpointNV"));
#endif
#if (defined(VK_NV_device_diagnostic_checkpoints))
        fp_vkGetQueueCheckpointDataNV = reinterpret_cast<PFN_vkGetQueueCheckpointDataNV>(procAddr(device, "vkGetQueueCheckpointDataNV"));
#endif
#if (defined(VK_EXT_transform_feedback))
        fp_vkCmdBindTransformFeedbackBuffersEXT = reinterpret_cast<PFN_vkCmdBindTransformFeedbackBuffersEXT>(procAddr(device, "vkCmdBindTransformFeedbackBuffersEXT"));
#endif
#if (defined(VK_EXT_transform_feedback))
        fp_vkCmdBeginTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdBeginTransformFeedbackEXT>(procAddr(device, "vkCmdBeginTransformFeedbackEXT"));
#endif
#if (defined(VK_EXT_transform_feedback))
        fp_vkCmdEndTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdEndTransformFeedbackEXT>(procAddr(device, "vkCmdEndTransformFeedbackEXT"));
#endif
#if (defined(VK_EXT_transform_feedback))
        fp_vkCmdBeginQueryIndexedEXT = reinterpret_cast<PFN_vkCmdBeginQueryIndexedEXT>(procAddr(device, "vkCmdBeginQueryIndexedEXT"));
#endif
#if (defined(VK_EXT_transform_feedback))
        fp_vkCmdEndQueryIndexedEXT = reinterpret_cast<PFN_vkCmdEndQueryIndexedEXT>(procAddr(device, "vkCmdEndQueryIndexedEXT"));
#endif
#if (defined(VK_EXT_transform_feedback))
        fp_vkCmdDrawIndirectByteCountEXT = reinterpret_cast<PFN_vkCmdDrawIndirectByteCountEXT>(procAddr(device, "vkCmdDrawIndirectByteCountEXT"));
#endif
#if (defined(VK_NV_scissor_exclusive))
        fp_vkCmdSetExclusiveScissorNV = reinterpret_cast<PFN_vkCmdSetExclusiveScissorNV>(procAddr(device, "vkCmdSetExclusiveScissorNV"));
#endif
#if ((defined(VK_NV_scissor_exclusive))) && VK_HEADER_VERSION >= 241
        fp_vkCmdSetExclusiveScissorEnableNV = reinterpret_cast<PFN_vkCmdSetExclusiveScissorEnableNV>(procAddr(device, "vkCmdSetExclusiveScissorEnableNV"));
#endif
#if (defined(VK_NV_shading_rate_image))
        fp_vkCmdBindShadingRateImageNV = reinterpret_cast<PFN_vkCmdBindShadingRateImageNV>(procAddr(device, "vkCmdBindShadingRateImageNV"));
#endif
#if (defined(VK_NV_shading_rate_image))
        fp_vkCmdSetViewportShadingRatePaletteNV = reinterpret_cast<PFN_vkCmdSetViewportShadingRatePaletteNV>(procAddr(device, "vkCmdSetViewportShadingRatePaletteNV"));
#endif
#if (defined(VK_NV_shading_rate_image))
        fp_vkCmdSetCoarseSampleOrderNV = reinterpret_cast<PFN_vkCmdSetCoarseSampleOrderNV>(procAddr(device, "vkCmdSetCoarseSampleOrderNV"));
#endif
#if (defined(VK_NV_mesh_shader))
        fp_vkCmdDrawMeshTasksNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksNV>(procAddr(device, "vkCmdDrawMeshTasksNV"));
#endif
#if (defined(VK_NV_mesh_shader))
        fp_vkCmdDrawMeshTasksIndirectNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectNV>(procAddr(device, "vkCmdDrawMeshTasksIndirectNV"));
#endif
#if (defined(VK_NV_mesh_shader))
        fp_vkCmdDrawMeshTasksIndirectCountNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectCountNV>(procAddr(device, "vkCmdDrawMeshTasksIndirectCountNV"));
#endif
#if (defined(VK_EXT_mesh_shader))
        fp_vkCmdDrawMeshTasksEXT = reinterpret_cast<PFN_vkCmdDrawMeshTasksEXT>(procAddr(device, "vkCmdDrawMeshTasksEXT"));
#endif
#if (defined(VK_EXT_mesh_shader))
        fp_vkCmdDrawMeshTasksIndirectEXT = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectEXT>(procAddr(device, "vkCmdDrawMeshTasksIndirectEXT"));
#endif
#if (defined(VK_EXT_mesh_shader))
        fp_vkCmdDrawMeshTasksIndirectCountEXT = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectCountEXT>(procAddr(device, "vkCmdDrawMeshTasksIndirectCountEXT"));
#endif
#if (defined(VK_NV_ray_tracing))
        fp_vkCompileDeferredNV = reinterpret_cast<PFN_vkCompileDeferredNV>(procAddr(device, "vkCompileDeferredNV"));
#endif
#if (defined(VK_NV_ray_tracing))
        fp_vkCreateAccelerationStructureNV = reinterpret_cast<PFN_vkCreateAccelerationStructureNV>(procAddr(device, "vkCreateAccelerationStructureNV"));
#endif
#if (defined(VK_HUAWEI_invocation_mask))
        fp_vkCmdBindInvocationMaskHUAWEI = reinterpret_cast<PFN_vkCmdBindInvocationMaskHUAWEI>(procAddr(device, "vkCmdBindInvocationMaskHUAWEI"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkDestroyAccelerationStructureKHR = reinterpret_cast<PFN_vkDestroyAccelerationStructureKHR>(procAddr(device, "vkDestroyAccelerationStructureKHR"));
#endif
#if (defined(VK_NV_ray_tracing))
        fp_vkDestroyAccelerationStructureNV = reinterpret_cast<PFN_vkDestroyAccelerationStructureNV>(procAddr(device, "vkDestroyAccelerationStructureNV"));
#endif
#if (defined(VK_NV_ray_tracing))
        fp_vkGetAccelerationStructureMemoryRequirementsNV = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsNV>(procAddr(device, "vkGetAccelerationStructureMemoryRequirementsNV"));
#endif
#if (defined(VK_NV_ray_tracing))
        fp_vkBindAccelerationStructureMemoryNV = reinterpret_cast<PFN_vkBindAccelerationStructureMemoryNV>(procAddr(device, "vkBindAccelerationStructureMemoryNV"));
#endif
#if (defined(VK_NV_ray_tracing))
        fp_vkCmdCopyAccelerationStructureNV = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureNV>(procAddr(device, "vkCmdCopyAccelerationStructureNV"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkCmdCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureKHR>(procAddr(device, "vkCmdCopyAccelerationStructureKHR"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureKHR>(procAddr(device, "vkCopyAccelerationStructureKHR"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkCmdCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureToMemoryKHR>(procAddr(device, "vkCmdCopyAccelerationStructureToMemoryKHR"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureToMemoryKHR>(procAddr(device, "vkCopyAccelerationStructureToMemoryKHR"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkCmdCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyMemoryToAccelerationStructureKHR>(procAddr(device, "vkCmdCopyMemoryToAccelerationStructureKHR"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyMemoryToAccelerationStructureKHR>(procAddr(device, "vkCopyMemoryToAccelerationStructureKHR"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkCmdWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesKHR>(procAddr(device, "vkCmdWriteAccelerationStructuresPropertiesKHR"));
#endif
#if (defined(VK_NV_ray_tracing))
        fp_vkCmdWriteAccelerationStructuresPropertiesNV = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesNV>(procAddr(device, "vkCmdWriteAccelerationStructuresPropertiesNV"));
#endif
#if (defined(VK_NV_ray_tracing))
        fp_vkCmdBuildAccelerationStructureNV = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureNV>(procAddr(device, "vkCmdBuildAccelerationStructureNV"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkWriteAccelerationStructuresPropertiesKHR>(procAddr(device, "vkWriteAccelerationStructuresPropertiesKHR"));
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
        fp_vkCmdTraceRaysKHR = reinterpret_cast<PFN_vkCmdTraceRaysKHR>(procAddr(device, "vkCmdTraceRaysKHR"));
#endif
#if (defined(VK_NV_ray_tracing))
        fp_vkCmdTraceRaysNV = reinterpret_cast<PFN_vkCmdTraceRaysNV>(procAddr(device, "vkCmdTraceRaysNV"));
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
        fp_vkGetRayTracingShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesKHR>(procAddr(device, "vkGetRayTracingShaderGroupHandlesKHR"));
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
        fp_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR>(procAddr(device, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR"));
#endif
#if (defined(VK_NV_ray_tracing))
        fp_vkGetAccelerationStructureHandleNV = reinterpret_cast<PFN_vkGetAccelerationStructureHandleNV>(procAddr(device, "vkGetAccelerationStructureHandleNV"));
#endif
#if (defined(VK_NV_ray_tracing))
        fp_vkCreateRayTracingPipelinesNV = reinterpret_cast<PFN_vkCreateRayTracingPipelinesNV>(procAddr(device, "vkCreateRayTracingPipelinesNV"));
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
        fp_vkCreateRayTracingPipelinesKHR = reinterpret_cast<PFN_vkCreateRayTracingPipelinesKHR>(procAddr(device, "vkCreateRayTracingPipelinesKHR"));
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
        fp_vkCmdTraceRaysIndirectKHR = reinterpret_cast<PFN_vkCmdTraceRaysIndirectKHR>(procAddr(device, "vkCmdTraceRaysIndirectKHR"));
#endif
#if (defined(VK_KHR_ray_tracing_maintenance1))
        fp_vkCmdTraceRaysIndirect2KHR = reinterpret_cast<PFN_vkCmdTraceRaysIndirect2KHR>(procAddr(device, "vkCmdTraceRaysIndirect2KHR"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkGetDeviceAccelerationStructureCompatibilityKHR = reinterpret_cast<PFN_vkGetDeviceAccelerationStructureCompatibilityKHR>(procAddr(device, "vkGetDeviceAccelerationStructureCompatibilityKHR"));
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
        fp_vkGetRayTracingShaderGroupStackSizeKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupStackSizeKHR>(procAddr(device, "vkGetRayTracingShaderGroupStackSizeKHR"));
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
        fp_vkCmdSetRayTracingPipelineStackSizeKHR = reinterpret_cast<PFN_vkCmdSetRayTracingPipelineStackSizeKHR>(procAddr(device, "vkCmdSetRayTracingPipelineStackSizeKHR"));
#endif
#if (defined(VK_EXT_full_screen_exclusive)) || (defined(VK_EXT_full_screen_exclusive))
        fp_vkGetDeviceGroupSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModes2EXT>(procAddr(device, "vkGetDeviceGroupSurfacePresentModes2EXT"));
#endif
#if (defined(VK_EXT_full_screen_exclusive))
        fp_vkAcquireFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkAcquireFullScreenExclusiveModeEXT>(procAddr(device, "vkAcquireFullScreenExclusiveModeEXT"));
#endif
#if (defined(VK_EXT_full_screen_exclusive))
        fp_vkReleaseFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkReleaseFullScreenExclusiveModeEXT>(procAddr(device, "vkReleaseFullScreenExclusiveModeEXT"));
#endif
#if (defined(VK_KHR_performance_query))
        fp_vkAcquireProfilingLockKHR = reinterpret_cast<PFN_vkAcquireProfilingLockKHR>(procAddr(device, "vkAcquireProfilingLockKHR"));
#endif
#if (defined(VK_KHR_performance_query))
        fp_vkReleaseProfilingLockKHR = reinterpret_cast<PFN_vkReleaseProfilingLockKHR>(procAddr(device, "vkReleaseProfilingLockKHR"));
#endif
#if (defined(VK_EXT_image_drm_format_modifier))
        fp_vkGetImageDrmFormatModifierPropertiesEXT = reinterpret_cast<PFN_vkGetImageDrmFormatModifierPropertiesEXT>(procAddr(device, "vkGetImageDrmFormatModifierPropertiesEXT"));
#endif
#if (defined(VK_VERSION_1_2))
        fp_vkGetBufferOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetBufferOpaqueCaptureAddress>(procAddr(device, "vkGetBufferOpaqueCaptureAddress"));
#endif
#if (defined(VK_VERSION_1_2))
        fp_vkGetBufferDeviceAddress = reinterpret_cast<PFN_vkGetBufferDeviceAddress>(procAddr(device, "vkGetBufferDeviceAddress"));
#endif
#if (defined(VK_INTEL_performance_query))
        fp_vkInitializePerformanceApiINTEL = reinterpret_cast<PFN_vkInitializePerformanceApiINTEL>(procAddr(device, "vkInitializePerformanceApiINTEL"));
#endif
#if (defined(VK_INTEL_performance_query))
        fp_vkUninitializePerformanceApiINTEL = reinterpret_cast<PFN_vkUninitializePerformanceApiINTEL>(procAddr(device, "vkUninitializePerformanceApiINTEL"));
#endif
#if (defined(VK_INTEL_performance_query))
        fp_vkCmdSetPerformanceMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceMarkerINTEL>(procAddr(device, "vkCmdSetPerformanceMarkerINTEL"));
#endif
#if (defined(VK_INTEL_performance_query))
        fp_vkCmdSetPerformanceStreamMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceStreamMarkerINTEL>(procAddr(device, "vkCmdSetPerformanceStreamMarkerINTEL"));
#endif
#if (defined(VK_INTEL_performance_query))
        fp_vkCmdSetPerformanceOverrideINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceOverrideINTEL>(procAddr(device, "vkCmdSetPerformanceOverrideINTEL"));
#endif
#if (defined(VK_INTEL_performance_query))
        fp_vkAcquirePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkAcquirePerformanceConfigurationINTEL>(procAddr(device, "vkAcquirePerformanceConfigurationINTEL"));
#endif
#if (defined(VK_INTEL_performance_query))
        fp_vkReleasePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkReleasePerformanceConfigurationINTEL>(procAddr(device, "vkReleasePerformanceConfigurationINTEL"));
#endif
#if (defined(VK_INTEL_performance_query))
        fp_vkQueueSetPerformanceConfigurationINTEL = reinterpret_cast<PFN_vkQueueSetPerformanceConfigurationINTEL>(procAddr(device, "vkQueueSetPerformanceConfigurationINTEL"));
#endif
#if (defined(VK_INTEL_performance_query))
        fp_vkGetPerformanceParameterINTEL = reinterpret_cast<PFN_vkGetPerformanceParameterINTEL>(procAddr(device, "vkGetPerformanceParameterINTEL"));
#endif
#if (defined(VK_VERSION_1_2))
        fp_vkGetDeviceMemoryOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetDeviceMemoryOpaqueCaptureAddress>(procAddr(device, "vkGetDeviceMemoryOpaqueCaptureAddress"));
#endif
#if (defined(VK_KHR_pipeline_executable_properties))
        fp_vkGetPipelineExecutablePropertiesKHR = reinterpret_cast<PFN_vkGetPipelineExecutablePropertiesKHR>(procAddr(device, "vkGetPipelineExecutablePropertiesKHR"));
#endif
#if (defined(VK_KHR_pipeline_executable_properties))
        fp_vkGetPipelineExecutableStatisticsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableStatisticsKHR>(procAddr(device, "vkGetPipelineExecutableStatisticsKHR"));
#endif
#if (defined(VK_KHR_pipeline_executable_properties))
        fp_vkGetPipelineExecutableInternalRepresentationsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableInternalRepresentationsKHR>(procAddr(device, "vkGetPipelineExecutableInternalRepresentationsKHR"));
#endif
#if (defined(VK_EXT_line_rasterization))
        fp_vkCmdSetLineStippleEXT = reinterpret_cast<PFN_vkCmdSetLineStippleEXT>(procAddr(device, "vkCmdSetLineStippleEXT"));
#endif
#if (defined(VKSC_VERSION_1_0))
        fp_vkGetFaultData = reinterpret_cast<PFN_vkGetFaultData>(procAddr(device, "vkGetFaultData"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkCreateAccelerationStructureKHR = reinterpret_cast<PFN_vkCreateAccelerationStructureKHR>(procAddr(device, "vkCreateAccelerationStructureKHR"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkCmdBuildAccelerationStructuresKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructuresKHR>(procAddr(device, "vkCmdBuildAccelerationStructuresKHR"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkCmdBuildAccelerationStructuresIndirectKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructuresIndirectKHR>(procAddr(device, "vkCmdBuildAccelerationStructuresIndirectKHR"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkBuildAccelerationStructuresKHR = reinterpret_cast<PFN_vkBuildAccelerationStructuresKHR>(procAddr(device, "vkBuildAccelerationStructuresKHR"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkGetAccelerationStructureDeviceAddressKHR = reinterpret_cast<PFN_vkGetAccelerationStructureDeviceAddressKHR>(procAddr(device, "vkGetAccelerationStructureDeviceAddressKHR"));
#endif
#if (defined(VK_KHR_deferred_host_operations))
        fp_vkCreateDeferredOperationKHR = reinterpret_cast<PFN_vkCreateDeferredOperationKHR>(procAddr(device, "vkCreateDeferredOperationKHR"));
#endif
#if (defined(VK_KHR_deferred_host_operations))
        fp_vkDestroyDeferredOperationKHR = reinterpret_cast<PFN_vkDestroyDeferredOperationKHR>(procAddr(device, "vkDestroyDeferredOperationKHR"));
#endif
#if (defined(VK_KHR_deferred_host_operations))
        fp_vkGetDeferredOperationMaxConcurrencyKHR = reinterpret_cast<PFN_vkGetDeferredOperationMaxConcurrencyKHR>(procAddr(device, "vkGetDeferredOperationMaxConcurrencyKHR"));
#endif
#if (defined(VK_KHR_deferred_host_operations))
        fp_vkGetDeferredOperationResultKHR = reinterpret_cast<PFN_vkGetDeferredOperationResultKHR>(procAddr(device, "vkGetDeferredOperationResultKHR"));
#endif
#if (defined(VK_KHR_deferred_host_operations))
        fp_vkDeferredOperationJoinKHR = reinterpret_cast<PFN_vkDeferredOperationJoinKHR>(procAddr(device, "vkDeferredOperationJoinKHR"));
#endif
#if (defined(VK_NV_device_generated_commands_compute))
        fp_vkGetPipelineIndirectMemoryRequirementsNV = reinterpret_cast<PFN_vkGetPipelineIndirectMemoryRequirementsNV>(procAddr(device, "vkGetPipelineIndirectMemoryRequirementsNV"));
#endif
#if (defined(VK_NV_device_generated_commands_compute))
        fp_vkGetPipelineIndirectDeviceAddressNV = reinterpret_cast<PFN_vkGetPipelineIndirectDeviceAddressNV>(procAddr(device, "vkGetPipelineIndirectDeviceAddressNV"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetCullMode = reinterpret_cast<PFN_vkCmdSetCullMode>(procAddr(device, "vkCmdSetCullMode"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetFrontFace = reinterpret_cast<PFN_vkCmdSetFrontFace>(procAddr(device, "vkCmdSetFrontFace"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetPrimitiveTopology = reinterpret_cast<PFN_vkCmdSetPrimitiveTopology>(procAddr(device, "vkCmdSetPrimitiveTopology"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetViewportWithCount = reinterpret_cast<PFN_vkCmdSetViewportWithCount>(procAddr(device, "vkCmdSetViewportWithCount"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetScissorWithCount = reinterpret_cast<PFN_vkCmdSetScissorWithCount>(procAddr(device, "vkCmdSetScissorWithCount"));
#endif
#if (defined(VK_KHR_maintenance5))
        fp_vkCmdBindIndexBuffer2KHR = reinterpret_cast<PFN_vkCmdBindIndexBuffer2KHR>(procAddr(device, "vkCmdBindIndexBuffer2KHR"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdBindVertexBuffers2 = reinterpret_cast<PFN_vkCmdBindVertexBuffers2>(procAddr(device, "vkCmdBindVertexBuffers2"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetDepthTestEnable = reinterpret_cast<PFN_vkCmdSetDepthTestEnable>(procAddr(device, "vkCmdSetDepthTestEnable"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetDepthWriteEnable = reinterpret_cast<PFN_vkCmdSetDepthWriteEnable>(procAddr(device, "vkCmdSetDepthWriteEnable"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetDepthCompareOp = reinterpret_cast<PFN_vkCmdSetDepthCompareOp>(procAddr(device, "vkCmdSetDepthCompareOp"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetDepthBoundsTestEnable = reinterpret_cast<PFN_vkCmdSetDepthBoundsTestEnable>(procAddr(device, "vkCmdSetDepthBoundsTestEnable"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetStencilTestEnable = reinterpret_cast<PFN_vkCmdSetStencilTestEnable>(procAddr(device, "vkCmdSetStencilTestEnable"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetStencilOp = reinterpret_cast<PFN_vkCmdSetStencilOp>(procAddr(device, "vkCmdSetStencilOp"));
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetPatchControlPointsEXT = reinterpret_cast<PFN_vkCmdSetPatchControlPointsEXT>(procAddr(device, "vkCmdSetPatchControlPointsEXT"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetRasterizerDiscardEnable = reinterpret_cast<PFN_vkCmdSetRasterizerDiscardEnable>(procAddr(device, "vkCmdSetRasterizerDiscardEnable"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetDepthBiasEnable = reinterpret_cast<PFN_vkCmdSetDepthBiasEnable>(procAddr(device, "vkCmdSetDepthBiasEnable"));
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetLogicOpEXT = reinterpret_cast<PFN_vkCmdSetLogicOpEXT>(procAddr(device, "vkCmdSetLogicOpEXT"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetPrimitiveRestartEnable = reinterpret_cast<PFN_vkCmdSetPrimitiveRestartEnable>(procAddr(device, "vkCmdSetPrimitiveRestartEnable"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetTessellationDomainOriginEXT = reinterpret_cast<PFN_vkCmdSetTessellationDomainOriginEXT>(procAddr(device, "vkCmdSetTessellationDomainOriginEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetDepthClampEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthClampEnableEXT>(procAddr(device, "vkCmdSetDepthClampEnableEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetPolygonModeEXT = reinterpret_cast<PFN_vkCmdSetPolygonModeEXT>(procAddr(device, "vkCmdSetPolygonModeEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetRasterizationSamplesEXT = reinterpret_cast<PFN_vkCmdSetRasterizationSamplesEXT>(procAddr(device, "vkCmdSetRasterizationSamplesEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetSampleMaskEXT = reinterpret_cast<PFN_vkCmdSetSampleMaskEXT>(procAddr(device, "vkCmdSetSampleMaskEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetAlphaToCoverageEnableEXT = reinterpret_cast<PFN_vkCmdSetAlphaToCoverageEnableEXT>(procAddr(device, "vkCmdSetAlphaToCoverageEnableEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetAlphaToOneEnableEXT = reinterpret_cast<PFN_vkCmdSetAlphaToOneEnableEXT>(procAddr(device, "vkCmdSetAlphaToOneEnableEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetLogicOpEnableEXT = reinterpret_cast<PFN_vkCmdSetLogicOpEnableEXT>(procAddr(device, "vkCmdSetLogicOpEnableEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetColorBlendEnableEXT = reinterpret_cast<PFN_vkCmdSetColorBlendEnableEXT>(procAddr(device, "vkCmdSetColorBlendEnableEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetColorBlendEquationEXT = reinterpret_cast<PFN_vkCmdSetColorBlendEquationEXT>(procAddr(device, "vkCmdSetColorBlendEquationEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetColorWriteMaskEXT = reinterpret_cast<PFN_vkCmdSetColorWriteMaskEXT>(procAddr(device, "vkCmdSetColorWriteMaskEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetRasterizationStreamEXT = reinterpret_cast<PFN_vkCmdSetRasterizationStreamEXT>(procAddr(device, "vkCmdSetRasterizationStreamEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetConservativeRasterizationModeEXT = reinterpret_cast<PFN_vkCmdSetConservativeRasterizationModeEXT>(procAddr(device, "vkCmdSetConservativeRasterizationModeEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetExtraPrimitiveOverestimationSizeEXT = reinterpret_cast<PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT>(procAddr(device, "vkCmdSetExtraPrimitiveOverestimationSizeEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetDepthClipEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthClipEnableEXT>(procAddr(device, "vkCmdSetDepthClipEnableEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetSampleLocationsEnableEXT = reinterpret_cast<PFN_vkCmdSetSampleLocationsEnableEXT>(procAddr(device, "vkCmdSetSampleLocationsEnableEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetColorBlendAdvancedEXT = reinterpret_cast<PFN_vkCmdSetColorBlendAdvancedEXT>(procAddr(device, "vkCmdSetColorBlendAdvancedEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetProvokingVertexModeEXT = reinterpret_cast<PFN_vkCmdSetProvokingVertexModeEXT>(procAddr(device, "vkCmdSetProvokingVertexModeEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetLineRasterizationModeEXT = reinterpret_cast<PFN_vkCmdSetLineRasterizationModeEXT>(procAddr(device, "vkCmdSetLineRasterizationModeEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetLineStippleEnableEXT = reinterpret_cast<PFN_vkCmdSetLineStippleEnableEXT>(procAddr(device, "vkCmdSetLineStippleEnableEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetDepthClipNegativeOneToOneEXT = reinterpret_cast<PFN_vkCmdSetDepthClipNegativeOneToOneEXT>(procAddr(device, "vkCmdSetDepthClipNegativeOneToOneEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetViewportWScalingEnableNV = reinterpret_cast<PFN_vkCmdSetViewportWScalingEnableNV>(procAddr(device, "vkCmdSetViewportWScalingEnableNV"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetViewportSwizzleNV = reinterpret_cast<PFN_vkCmdSetViewportSwizzleNV>(procAddr(device, "vkCmdSetViewportSwizzleNV"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetCoverageToColorEnableNV = reinterpret_cast<PFN_vkCmdSetCoverageToColorEnableNV>(procAddr(device, "vkCmdSetCoverageToColorEnableNV"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetCoverageToColorLocationNV = reinterpret_cast<PFN_vkCmdSetCoverageToColorLocationNV>(procAddr(device, "vkCmdSetCoverageToColorLocationNV"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetCoverageModulationModeNV = reinterpret_cast<PFN_vkCmdSetCoverageModulationModeNV>(procAddr(device, "vkCmdSetCoverageModulationModeNV"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetCoverageModulationTableEnableNV = reinterpret_cast<PFN_vkCmdSetCoverageModulationTableEnableNV>(procAddr(device, "vkCmdSetCoverageModulationTableEnableNV"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetCoverageModulationTableNV = reinterpret_cast<PFN_vkCmdSetCoverageModulationTableNV>(procAddr(device, "vkCmdSetCoverageModulationTableNV"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetShadingRateImageEnableNV = reinterpret_cast<PFN_vkCmdSetShadingRateImageEnableNV>(procAddr(device, "vkCmdSetShadingRateImageEnableNV"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetCoverageReductionModeNV = reinterpret_cast<PFN_vkCmdSetCoverageReductionModeNV>(procAddr(device, "vkCmdSetCoverageReductionModeNV"));
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetRepresentativeFragmentTestEnableNV = reinterpret_cast<PFN_vkCmdSetRepresentativeFragmentTestEnableNV>(procAddr(device, "vkCmdSetRepresentativeFragmentTestEnableNV"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCreatePrivateDataSlot = reinterpret_cast<PFN_vkCreatePrivateDataSlot>(procAddr(device, "vkCreatePrivateDataSlot"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkDestroyPrivateDataSlot = reinterpret_cast<PFN_vkDestroyPrivateDataSlot>(procAddr(device, "vkDestroyPrivateDataSlot"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkSetPrivateData = reinterpret_cast<PFN_vkSetPrivateData>(procAddr(device, "vkSetPrivateData"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkGetPrivateData = reinterpret_cast<PFN_vkGetPrivateData>(procAddr(device, "vkGetPrivateData"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdCopyBuffer2 = reinterpret_cast<PFN_vkCmdCopyBuffer2>(procAddr(device, "vkCmdCopyBuffer2"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdCopyImage2 = reinterpret_cast<PFN_vkCmdCopyImage2>(procAddr(device, "vkCmdCopyImage2"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdBlitImage2 = reinterpret_cast<PFN_vkCmdBlitImage2>(procAddr(device, "vkCmdBlitImage2"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdCopyBufferToImage2 = reinterpret_cast<PFN_vkCmdCopyBufferToImage2>(procAddr(device, "vkCmdCopyBufferToImage2"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdCopyImageToBuffer2 = reinterpret_cast<PFN_vkCmdCopyImageToBuffer2>(procAddr(device, "vkCmdCopyImageToBuffer2"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdResolveImage2 = reinterpret_cast<PFN_vkCmdResolveImage2>(procAddr(device, "vkCmdResolveImage2"));
#endif
#if (defined(VK_KHR_object_refresh))
        fp_vkCmdRefreshObjectsKHR = reinterpret_cast<PFN_vkCmdRefreshObjectsKHR>(procAddr(device, "vkCmdRefreshObjectsKHR"));
#endif
#if (defined(VK_KHR_fragment_shading_rate))
        fp_vkCmdSetFragmentShadingRateKHR = reinterpret_cast<PFN_vkCmdSetFragmentShadingRateKHR>(procAddr(device, "vkCmdSetFragmentShadingRateKHR"));
#endif
#if (defined(VK_NV_fragment_shading_rate_enums))
        fp_vkCmdSetFragmentShadingRateEnumNV = reinterpret_cast<PFN_vkCmdSetFragmentShadingRateEnumNV>(procAddr(device, "vkCmdSetFragmentShadingRateEnumNV"));
#endif
#if (defined(VK_KHR_acceleration_structure))
        fp_vkGetAccelerationStructureBuildSizesKHR = reinterpret_cast<PFN_vkGetAccelerationStructureBuildSizesKHR>(procAddr(device, "vkGetAccelerationStructureBuildSizesKHR"));
#endif
#if (defined(VK_EXT_vertex_input_dynamic_state)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetVertexInputEXT = reinterpret_cast<PFN_vkCmdSetVertexInputEXT>(procAddr(device, "vkCmdSetVertexInputEXT"));
#endif
#if (defined(VK_EXT_color_write_enable))
        fp_vkCmdSetColorWriteEnableEXT = reinterpret_cast<PFN_vkCmdSetColorWriteEnableEXT>(procAddr(device, "vkCmdSetColorWriteEnableEXT"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdSetEvent2 = reinterpret_cast<PFN_vkCmdSetEvent2>(procAddr(device, "vkCmdSetEvent2"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdResetEvent2 = reinterpret_cast<PFN_vkCmdResetEvent2>(procAddr(device, "vkCmdResetEvent2"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdWaitEvents2 = reinterpret_cast<PFN_vkCmdWaitEvents2>(procAddr(device, "vkCmdWaitEvents2"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdPipelineBarrier2 = reinterpret_cast<PFN_vkCmdPipelineBarrier2>(procAddr(device, "vkCmdPipelineBarrier2"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkQueueSubmit2 = reinterpret_cast<PFN_vkQueueSubmit2>(procAddr(device, "vkQueueSubmit2"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdWriteTimestamp2 = reinterpret_cast<PFN_vkCmdWriteTimestamp2>(procAddr(device, "vkCmdWriteTimestamp2"));
#endif
#if (defined(VK_KHR_synchronization2))
        fp_vkCmdWriteBufferMarker2AMD = reinterpret_cast<PFN_vkCmdWriteBufferMarker2AMD>(procAddr(device, "vkCmdWriteBufferMarker2AMD"));
#endif
#if (defined(VK_KHR_synchronization2))
        fp_vkGetQueueCheckpointData2NV = reinterpret_cast<PFN_vkGetQueueCheckpointData2NV>(procAddr(device, "vkGetQueueCheckpointData2NV"));
#endif
#if (defined(VK_EXT_host_image_copy))
        fp_vkCopyMemoryToImageEXT = reinterpret_cast<PFN_vkCopyMemoryToImageEXT>(procAddr(device, "vkCopyMemoryToImageEXT"));
#endif
#if (defined(VK_EXT_host_image_copy))
        fp_vkCopyImageToMemoryEXT = reinterpret_cast<PFN_vkCopyImageToMemoryEXT>(procAddr(device, "vkCopyImageToMemoryEXT"));
#endif
#if (defined(VK_EXT_host_image_copy))
        fp_vkCopyImageToImageEXT = reinterpret_cast<PFN_vkCopyImageToImageEXT>(procAddr(device, "vkCopyImageToImageEXT"));
#endif
#if (defined(VK_EXT_host_image_copy))
        fp_vkTransitionImageLayoutEXT = reinterpret_cast<PFN_vkTransitionImageLayoutEXT>(procAddr(device, "vkTransitionImageLayoutEXT"));
#endif
#if (defined(VKSC_VERSION_1_0))
        fp_vkGetCommandPoolMemoryConsumption = reinterpret_cast<PFN_vkGetCommandPoolMemoryConsumption>(procAddr(device, "vkGetCommandPoolMemoryConsumption"));
#endif
#if (defined(VK_KHR_video_queue))
        fp_vkCreateVideoSessionKHR = reinterpret_cast<PFN_vkCreateVideoSessionKHR>(procAddr(device, "vkCreateVideoSessionKHR"));
#endif
#if (defined(VK_KHR_video_queue))
        fp_vkDestroyVideoSessionKHR = reinterpret_cast<PFN_vkDestroyVideoSessionKHR>(procAddr(device, "vkDestroyVideoSessionKHR"));
#endif
#if (defined(VK_KHR_video_queue))
        fp_vkCreateVideoSessionParametersKHR = reinterpret_cast<PFN_vkCreateVideoSessionParametersKHR>(procAddr(device, "vkCreateVideoSessionParametersKHR"));
#endif
#if (defined(VK_KHR_video_queue))
        fp_vkUpdateVideoSessionParametersKHR = reinterpret_cast<PFN_vkUpdateVideoSessionParametersKHR>(procAddr(device, "vkUpdateVideoSessionParametersKHR"));
#endif
#if (defined(VK_KHR_video_encode_queue))
        fp_vkGetEncodedVideoSessionParametersKHR = reinterpret_cast<PFN_vkGetEncodedVideoSessionParametersKHR>(procAddr(device, "vkGetEncodedVideoSessionParametersKHR"));
#endif
#if (defined(VK_KHR_video_queue))
        fp_vkDestroyVideoSessionParametersKHR = reinterpret_cast<PFN_vkDestroyVideoSessionParametersKHR>(procAddr(device, "vkDestroyVideoSessionParametersKHR"));
#endif
#if (defined(VK_KHR_video_queue))
        fp_vkGetVideoSessionMemoryRequirementsKHR = reinterpret_cast<PFN_vkGetVideoSessionMemoryRequirementsKHR>(procAddr(device, "vkGetVideoSessionMemoryRequirementsKHR"));
#endif
#if (defined(VK_KHR_video_queue))
        fp_vkBindVideoSessionMemoryKHR = reinterpret_cast<PFN_vkBindVideoSessionMemoryKHR>(procAddr(device, "vkBindVideoSessionMemoryKHR"));
#endif
#if (defined(VK_KHR_video_decode_queue))
        fp_vkCmdDecodeVideoKHR = reinterpret_cast<PFN_vkCmdDecodeVideoKHR>(procAddr(device, "vkCmdDecodeVideoKHR"));
#endif
#if (defined(VK_KHR_video_queue))
        fp_vkCmdBeginVideoCodingKHR = reinterpret_cast<PFN_vkCmdBeginVideoCodingKHR>(procAddr(device, "vkCmdBeginVideoCodingKHR"));
#endif
#if (defined(VK_KHR_video_queue))
        fp_vkCmdControlVideoCodingKHR = reinterpret_cast<PFN_vkCmdControlVideoCodingKHR>(procAddr(device, "vkCmdControlVideoCodingKHR"));
#endif
#if (defined(VK_KHR_video_queue))
        fp_vkCmdEndVideoCodingKHR = reinterpret_cast<PFN_vkCmdEndVideoCodingKHR>(procAddr(device, "vkCmdEndVideoCodingKHR"));
#endif
#if (defined(VK_KHR_video_encode_queue))
        fp_vkCmdEncodeVideoKHR = reinterpret_cast<PFN_vkCmdEncodeVideoKHR>(procAddr(device, "vkCmdEncodeVideoKHR"));
#endif
#if (defined(VK_NV_memory_decompression))
        fp_vkCmdDecompressMemoryNV = reinterpret_cast<PFN_vkCmdDecompressMemoryNV>(procAddr(device, "vkCmdDecompressMemoryNV"));
#endif
#if (defined(VK_NV_memory_decompression))
        fp_vkCmdDecompressMemoryIndirectCountNV = reinterpret_cast<PFN_vkCmdDecompressMemoryIndirectCountNV>(procAddr(device, "vkCmdDecompressMemoryIndirectCountNV"));
#endif
#if (defined(VK_EXT_descriptor_buffer))
        fp_vkGetDescriptorSetLayoutSizeEXT = reinterpret_cast<PFN_vkGetDescriptorSetLayoutSizeEXT>(procAddr(device, "vkGetDescriptorSetLayoutSizeEXT"));
#endif
#if (defined(VK_EXT_descriptor_buffer))
        fp_vkGetDescriptorSetLayoutBindingOffsetEXT = reinterpret_cast<PFN_vkGetDescriptorSetLayoutBindingOffsetEXT>(procAddr(device, "vkGetDescriptorSetLayoutBindingOffsetEXT"));
#endif
#if (defined(VK_EXT_descriptor_buffer))
        fp_vkGetDescriptorEXT = reinterpret_cast<PFN_vkGetDescriptorEXT>(procAddr(device, "vkGetDescriptorEXT"));
#endif
#if (defined(VK_EXT_descriptor_buffer))
        fp_vkCmdBindDescriptorBuffersEXT = reinterpret_cast<PFN_vkCmdBindDescriptorBuffersEXT>(procAddr(device, "vkCmdBindDescriptorBuffersEXT"));
#endif
#if (defined(VK_EXT_descriptor_buffer))
        fp_vkCmdSetDescriptorBufferOffsetsEXT = reinterpret_cast<PFN_vkCmdSetDescriptorBufferOffsetsEXT>(procAddr(device, "vkCmdSetDescriptorBufferOffsetsEXT"));
#endif
#if (defined(VK_EXT_descriptor_buffer))
        fp_vkCmdBindDescriptorBufferEmbeddedSamplersEXT = reinterpret_cast<PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT>(procAddr(device, "vkCmdBindDescriptorBufferEmbeddedSamplersEXT"));
#endif
#if (defined(VK_EXT_descriptor_buffer))
        fp_vkGetBufferOpaqueCaptureDescriptorDataEXT = reinterpret_cast<PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT>(procAddr(device, "vkGetBufferOpaqueCaptureDescriptorDataEXT"));
#endif
#if (defined(VK_EXT_descriptor_buffer))
        fp_vkGetImageOpaqueCaptureDescriptorDataEXT = reinterpret_cast<PFN_vkGetImageOpaqueCaptureDescriptorDataEXT>(procAddr(device, "vkGetImageOpaqueCaptureDescriptorDataEXT"));
#endif
#if (defined(VK_EXT_descriptor_buffer))
        fp_vkGetImageViewOpaqueCaptureDescriptorDataEXT = reinterpret_cast<PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT>(procAddr(device, "vkGetImageViewOpaqueCaptureDescriptorDataEXT"));
#endif
#if (defined(VK_EXT_descriptor_buffer))
        fp_vkGetSamplerOpaqueCaptureDescriptorDataEXT = reinterpret_cast<PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT>(procAddr(device, "vkGetSamplerOpaqueCaptureDescriptorDataEXT"));
#endif
#if (defined(VK_EXT_descriptor_buffer))
        fp_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT = reinterpret_cast<PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT>(procAddr(device, "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT"));
#endif
#if (defined(VK_EXT_pageable_device_local_memory))
        fp_vkSetDeviceMemoryPriorityEXT = reinterpret_cast<PFN_vkSetDeviceMemoryPriorityEXT>(procAddr(device, "vkSetDeviceMemoryPriorityEXT"));
#endif
#if (defined(VK_KHR_present_wait))
        fp_vkWaitForPresentKHR = reinterpret_cast<PFN_vkWaitForPresentKHR>(procAddr(device, "vkWaitForPresentKHR"));
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
        fp_vkCreateBufferCollectionFUCHSIA = reinterpret_cast<PFN_vkCreateBufferCollectionFUCHSIA>(procAddr(device, "vkCreateBufferCollectionFUCHSIA"));
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
        fp_vkSetBufferCollectionBufferConstraintsFUCHSIA = reinterpret_cast<PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA>(procAddr(device, "vkSetBufferCollectionBufferConstraintsFUCHSIA"));
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
        fp_vkSetBufferCollectionImageConstraintsFUCHSIA = reinterpret_cast<PFN_vkSetBufferCollectionImageConstraintsFUCHSIA>(procAddr(device, "vkSetBufferCollectionImageConstraintsFUCHSIA"));
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
        fp_vkDestroyBufferCollectionFUCHSIA = reinterpret_cast<PFN_vkDestroyBufferCollectionFUCHSIA>(procAddr(device, "vkDestroyBufferCollectionFUCHSIA"));
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
        fp_vkGetBufferCollectionPropertiesFUCHSIA = reinterpret_cast<PFN_vkGetBufferCollectionPropertiesFUCHSIA>(procAddr(device, "vkGetBufferCollectionPropertiesFUCHSIA"));
#endif
#if (defined(VK_NV_cuda_kernel_launch))
        fp_vkCreateCudaModuleNV = reinterpret_cast<PFN_vkCreateCudaModuleNV>(procAddr(device, "vkCreateCudaModuleNV"));
#endif
#if (defined(VK_NV_cuda_kernel_launch))
        fp_vkGetCudaModuleCacheNV = reinterpret_cast<PFN_vkGetCudaModuleCacheNV>(procAddr(device, "vkGetCudaModuleCacheNV"));
#endif
#if (defined(VK_NV_cuda_kernel_launch))
        fp_vkCreateCudaFunctionNV = reinterpret_cast<PFN_vkCreateCudaFunctionNV>(procAddr(device, "vkCreateCudaFunctionNV"));
#endif
#if (defined(VK_NV_cuda_kernel_launch))
        fp_vkDestroyCudaModuleNV = reinterpret_cast<PFN_vkDestroyCudaModuleNV>(procAddr(device, "vkDestroyCudaModuleNV"));
#endif
#if (defined(VK_NV_cuda_kernel_launch))
        fp_vkDestroyCudaFunctionNV = reinterpret_cast<PFN_vkDestroyCudaFunctionNV>(procAddr(device, "vkDestroyCudaFunctionNV"));
#endif
#if (defined(VK_NV_cuda_kernel_launch))
        fp_vkCmdCudaLaunchKernelNV = reinterpret_cast<PFN_vkCmdCudaLaunchKernelNV>(procAddr(device, "vkCmdCudaLaunchKernelNV"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdBeginRendering = reinterpret_cast<PFN_vkCmdBeginRendering>(procAddr(device, "vkCmdBeginRendering"));
#endif
#if (defined(VK_VERSION_1_3))
        fp_vkCmdEndRendering = reinterpret_cast<PFN_vkCmdEndRendering>(procAddr(device, "vkCmdEndRendering"));
#endif
#if (defined(VK_VALVE_descriptor_set_host_mapping))
        fp_vkGetDescriptorSetLayoutHostMappingInfoVALVE = reinterpret_cast<PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE>(procAddr(device, "vkGetDescriptorSetLayoutHostMappingInfoVALVE"));
#endif
#if (defined(VK_VALVE_descriptor_set_host_mapping))
        fp_vkGetDescriptorSetHostMappingVALVE = reinterpret_cast<PFN_vkGetDescriptorSetHostMappingVALVE>(procAddr(device, "vkGetDescriptorSetHostMappingVALVE"));
#endif
#if (defined(VK_EXT_opacity_micromap))
        fp_vkCreateMicromapEXT = reinterpret_cast<PFN_vkCreateMicromapEXT>(procAddr(device, "vkCreateMicromapEXT"));
#endif
#if (defined(VK_EXT_opacity_micromap))
        fp_vkCmdBuildMicromapsEXT = reinterpret_cast<PFN_vkCmdBuildMicromapsEXT>(procAddr(device, "vkCmdBuildMicromapsEXT"));
#endif
#if (defined(VK_EXT_opacity_micromap))
        fp_vkBuildMicromapsEXT = reinterpret_cast<PFN_vkBuildMicromapsEXT>(procAddr(device, "vkBuildMicromapsEXT"));
#endif
#if (defined(VK_EXT_opacity_micromap))
        fp_vkDestroyMicromapEXT = reinterpret_cast<PFN_vkDestroyMicromapEXT>(procAddr(device, "vkDestroyMicromapEXT"));
#endif
#if (defined(VK_EXT_opacity_micromap))
        fp_vkCmdCopyMicromapEXT = reinterpret_cast<PFN_vkCmdCopyMicromapEXT>(procAddr(device, "vkCmdCopyMicromapEXT"));
#endif
#if (defined(VK_EXT_opacity_micromap))
        fp_vkCopyMicromapEXT = reinterpret_cast<PFN_vkCopyMicromapEXT>(procAddr(device, "vkCopyMicromapEXT"));
#endif
#if (defined(VK_EXT_opacity_micromap))
        fp_vkCmdCopyMicromapToMemoryEXT = reinterpret_cast<PFN_vkCmdCopyMicromapToMemoryEXT>(procAddr(device, "vkCmdCopyMicromapToMemoryEXT"));
#endif
#if (defined(VK_EXT_opacity_micromap))
        fp_vkCopyMicromapToMemoryEXT = reinterpret_cast<PFN_vkCopyMicromapToMemoryEXT>(procAddr(device, "vkCopyMicromapToMemoryEXT"));
#endif
#if (defined(VK_EXT_opacity_micromap))
        fp_vkCmdCopyMemoryToMicromapEXT = reinterpret_cast<PFN_vkCmdCopyMemoryToMicromapEXT>(procAddr(device, "vkCmdCopyMemoryToMicromapEXT"));
#endif
#if (defined(VK_EXT_opacity_micromap))
        fp_vkCopyMemoryToMicromapEXT = reinterpret_cast<PFN_vkCopyMemoryToMicromapEXT>(procAddr(device, "vkCopyMemoryToMicromapEXT"));
#endif
#if (defined(VK_EXT_opacity_micromap))
        fp_vkCmdWriteMicromapsPropertiesEXT = reinterpret_cast<PFN_vkCmdWriteMicromapsPropertiesEXT>(procAddr(device, "vkCmdWriteMicromapsPropertiesEXT"));
#endif
#if (defined(VK_EXT_opacity_micromap))
        fp_vkWriteMicromapsPropertiesEXT = reinterpret_cast<PFN_vkWriteMicromapsPropertiesEXT>(procAddr(device, "vkWriteMicromapsPropertiesEXT"));
#endif
#if (defined(VK_EXT_opacity_micromap))
        fp_vkGetDeviceMicromapCompatibilityEXT = reinterpret_cast<PFN_vkGetDeviceMicromapCompatibilityEXT>(procAddr(device, "vkGetDeviceMicromapCompatibilityEXT"));
#endif
#if (defined(VK_EXT_opacity_micromap))
        fp_vkGetMicromapBuildSizesEXT = reinterpret_cast<PFN_vkGetMicromapBuildSizesEXT>(procAddr(device, "vkGetMicromapBuildSizesEXT"));
#endif
#if (defined(VK_EXT_shader_module_identifier))
        fp_vkGetShaderModuleIdentifierEXT = reinterpret_cast<PFN_vkGetShaderModuleIdentifierEXT>(procAddr(device, "vkGetShaderModuleIdentifierEXT"));
#endif
#if (defined(VK_EXT_shader_module_identifier))
        fp_vkGetShaderModuleCreateInfoIdentifierEXT = reinterpret_cast<PFN_vkGetShaderModuleCreateInfoIdentifierEXT>(procAddr(device, "vkGetShaderModuleCreateInfoIdentifierEXT"));
#endif
#if (defined(VK_KHR_maintenance5))
        fp_vkGetImageSubresourceLayout2KHR = reinterpret_cast<PFN_vkGetImageSubresourceLayout2KHR>(procAddr(device, "vkGetImageSubresourceLayout2KHR"));
#endif
#if (defined(VK_EXT_pipeline_properties))
        fp_vkGetPipelinePropertiesEXT = reinterpret_cast<PFN_vkGetPipelinePropertiesEXT>(procAddr(device, "vkGetPipelinePropertiesEXT"));
#endif
#if (defined(VK_EXT_metal_objects))
        fp_vkExportMetalObjectsEXT = reinterpret_cast<PFN_vkExportMetalObjectsEXT>(procAddr(device, "vkExportMetalObjectsEXT"));
#endif
#if (defined(VK_QCOM_tile_properties))
        fp_vkGetFramebufferTilePropertiesQCOM = reinterpret_cast<PFN_vkGetFramebufferTilePropertiesQCOM>(procAddr(device, "vkGetFramebufferTilePropertiesQCOM"));
#endif
#if (defined(VK_QCOM_tile_properties))
        fp_vkGetDynamicRenderingTilePropertiesQCOM = reinterpret_cast<PFN_vkGetDynamicRenderingTilePropertiesQCOM>(procAddr(device, "vkGetDynamicRenderingTilePropertiesQCOM"));
#endif
#if (defined(VK_NV_optical_flow))
        fp_vkCreateOpticalFlowSessionNV = reinterpret_cast<PFN_vkCreateOpticalFlowSessionNV>(procAddr(device, "vkCreateOpticalFlowSessionNV"));
#endif
#if (defined(VK_NV_optical_flow))
        fp_vkDestroyOpticalFlowSessionNV = reinterpret_cast<PFN_vkDestroyOpticalFlowSessionNV>(procAddr(device, "vkDestroyOpticalFlowSessionNV"));
#endif
#if (defined(VK_NV_optical_flow))
        fp_vkBindOpticalFlowSessionImageNV = reinterpret_cast<PFN_vkBindOpticalFlowSessionImageNV>(procAddr(device, "vkBindOpticalFlowSessionImageNV"));
#endif
#if (defined(VK_NV_optical_flow))
        fp_vkCmdOpticalFlowExecuteNV = reinterpret_cast<PFN_vkCmdOpticalFlowExecuteNV>(procAddr(device, "vkCmdOpticalFlowExecuteNV"));
#endif
#if (defined(VK_EXT_device_fault))
        fp_vkGetDeviceFaultInfoEXT = reinterpret_cast<PFN_vkGetDeviceFaultInfoEXT>(procAddr(device, "vkGetDeviceFaultInfoEXT"));
#endif
#if (defined(VK_EXT_depth_bias_control))
        fp_vkCmdSetDepthBias2EXT = reinterpret_cast<PFN_vkCmdSetDepthBias2EXT>(procAddr(device, "vkCmdSetDepthBias2EXT"));
#endif
#if (defined(VK_EXT_swapchain_maintenance1))
        fp_vkReleaseSwapchainImagesEXT = reinterpret_cast<PFN_vkReleaseSwapchainImagesEXT>(procAddr(device, "vkReleaseSwapchainImagesEXT"));
#endif
#if (defined(VK_KHR_maintenance5))
        fp_vkGetDeviceImageSubresourceLayoutKHR = reinterpret_cast<PFN_vkGetDeviceImageSubresourceLayoutKHR>(procAddr(device, "vkGetDeviceImageSubresourceLayoutKHR"));
#endif
#if (defined(VK_KHR_map_memory2))
        fp_vkMapMemory2KHR = reinterpret_cast<PFN_vkMapMemory2KHR>(procAddr(device, "vkMapMemory2KHR"));
#endif
#if (defined(VK_KHR_map_memory2))
        fp_vkUnmapMemory2KHR = reinterpret_cast<PFN_vkUnmapMemory2KHR>(procAddr(device, "vkUnmapMemory2KHR"));
#endif
#if (defined(VK_EXT_shader_object))
        fp_vkCreateShadersEXT = reinterpret_cast<PFN_vkCreateShadersEXT>(procAddr(device, "vkCreateShadersEXT"));
#endif
#if (defined(VK_EXT_shader_object))
        fp_vkDestroyShaderEXT = reinterpret_cast<PFN_vkDestroyShaderEXT>(procAddr(device, "vkDestroyShaderEXT"));
#endif
#if (defined(VK_EXT_shader_object))
        fp_vkGetShaderBinaryDataEXT = reinterpret_cast<PFN_vkGetShaderBinaryDataEXT>(procAddr(device, "vkGetShaderBinaryDataEXT"));
#endif
#if (defined(VK_EXT_shader_object))
        fp_vkCmdBindShadersEXT = reinterpret_cast<PFN_vkCmdBindShadersEXT>(procAddr(device, "vkCmdBindShadersEXT"));
#endif
#if (defined(VK_QNX_external_memory_screen_buffer))
        fp_vkGetScreenBufferPropertiesQNX = reinterpret_cast<PFN_vkGetScreenBufferPropertiesQNX>(procAddr(device, "vkGetScreenBufferPropertiesQNX"));
#endif
#if (defined(VK_AMDX_shader_enqueue))
        fp_vkGetExecutionGraphPipelineScratchSizeAMDX = reinterpret_cast<PFN_vkGetExecutionGraphPipelineScratchSizeAMDX>(procAddr(device, "vkGetExecutionGraphPipelineScratchSizeAMDX"));
#endif
#if (defined(VK_AMDX_shader_enqueue))
        fp_vkGetExecutionGraphPipelineNodeIndexAMDX = reinterpret_cast<PFN_vkGetExecutionGraphPipelineNodeIndexAMDX>(procAddr(device, "vkGetExecutionGraphPipelineNodeIndexAMDX"));
#endif
#if (defined(VK_AMDX_shader_enqueue))
        fp_vkCreateExecutionGraphPipelinesAMDX = reinterpret_cast<PFN_vkCreateExecutionGraphPipelinesAMDX>(procAddr(device, "vkCreateExecutionGraphPipelinesAMDX"));
#endif
#if (defined(VK_AMDX_shader_enqueue))
        fp_vkCmdInitializeGraphScratchMemoryAMDX = reinterpret_cast<PFN_vkCmdInitializeGraphScratchMemoryAMDX>(procAddr(device, "vkCmdInitializeGraphScratchMemoryAMDX"));
#endif
#if (defined(VK_AMDX_shader_enqueue))
        fp_vkCmdDispatchGraphAMDX = reinterpret_cast<PFN_vkCmdDispatchGraphAMDX>(procAddr(device, "vkCmdDispatchGraphAMDX"));
#endif
#if (defined(VK_AMDX_shader_enqueue))
        fp_vkCmdDispatchGraphIndirectAMDX = reinterpret_cast<PFN_vkCmdDispatchGraphIndirectAMDX>(procAddr(device, "vkCmdDispatchGraphIndirectAMDX"));
#endif
#if (defined(VK_AMDX_shader_enqueue))
        fp_vkCmdDispatchGraphIndirectCountAMDX = reinterpret_cast<PFN_vkCmdDispatchGraphIndirectCountAMDX>(procAddr(device, "vkCmdDispatchGraphIndirectCountAMDX"));
#endif
#if (defined(VK_KHR_maintenance6))
        fp_vkCmdBindDescriptorSets2KHR = reinterpret_cast<PFN_vkCmdBindDescriptorSets2KHR>(procAddr(device, "vkCmdBindDescriptorSets2KHR"));
#endif
#if (defined(VK_KHR_maintenance6))
        fp_vkCmdPushConstants2KHR = reinterpret_cast<PFN_vkCmdPushConstants2KHR>(procAddr(device, "vkCmdPushConstants2KHR"));
#endif
#if (defined(VK_KHR_maintenance6))
        fp_vkCmdPushDescriptorSet2KHR = reinterpret_cast<PFN_vkCmdPushDescriptorSet2KHR>(procAddr(device, "vkCmdPushDescriptorSet2KHR"));
#endif
#if (defined(VK_KHR_maintenance6))
        fp_vkCmdPushDescriptorSetWithTemplate2KHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetWithTemplate2KHR>(procAddr(device, "vkCmdPushDescriptorSetWithTemplate2KHR"));
#endif
#if (defined(VK_KHR_maintenance6))
        fp_vkCmdSetDescriptorBufferOffsets2EXT = reinterpret_cast<PFN_vkCmdSetDescriptorBufferOffsets2EXT>(procAddr(device, "vkCmdSetDescriptorBufferOffsets2EXT"));
#endif
#if (defined(VK_KHR_maintenance6))
        fp_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT = reinterpret_cast<PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT>(procAddr(device, "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT"));
#endif
#if (defined(VK_NV_low_latency2))
        fp_vkSetLatencySleepModeNV = reinterpret_cast<PFN_vkSetLatencySleepModeNV>(procAddr(device, "vkSetLatencySleepModeNV"));
#endif
#if (defined(VK_NV_low_latency2))
        fp_vkLatencySleepNV = reinterpret_cast<PFN_vkLatencySleepNV>(procAddr(device, "vkLatencySleepNV"));
#endif
#if (defined(VK_NV_low_latency2))
        fp_vkSetLatencyMarkerNV = reinterpret_cast<PFN_vkSetLatencyMarkerNV>(procAddr(device, "vkSetLatencyMarkerNV"));
#endif
#if ((defined(VK_NV_low_latency2))) && VK_HEADER_VERSION >= 271
        fp_vkGetLatencyTimingsNV = reinterpret_cast<PFN_vkGetLatencyTimingsNV>(procAddr(device, "vkGetLatencyTimingsNV"));
#endif
#if (defined(VK_NV_low_latency2))
        fp_vkQueueNotifyOutOfBandNV = reinterpret_cast<PFN_vkQueueNotifyOutOfBandNV>(procAddr(device, "vkQueueNotifyOutOfBandNV"));
#endif
#if (defined(VK_EXT_host_query_reset))
        fp_vkResetQueryPoolEXT = reinterpret_cast<PFN_vkResetQueryPoolEXT>(procAddr(device, "vkResetQueryPoolEXT"));
#endif
#if (defined(VK_KHR_maintenance1))
        fp_vkTrimCommandPoolKHR = reinterpret_cast<PFN_vkTrimCommandPoolKHR>(procAddr(device, "vkTrimCommandPoolKHR"));
#endif
#if (defined(VK_KHR_device_group))
        fp_vkGetDeviceGroupPeerMemoryFeaturesKHR = reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR>(procAddr(device, "vkGetDeviceGroupPeerMemoryFeaturesKHR"));
#endif
#if (defined(VK_KHR_bind_memory2))
        fp_vkBindBufferMemory2KHR = reinterpret_cast<PFN_vkBindBufferMemory2KHR>(procAddr(device, "vkBindBufferMemory2KHR"));
#endif
#if (defined(VK_KHR_bind_memory2))
        fp_vkBindImageMemory2KHR = reinterpret_cast<PFN_vkBindImageMemory2KHR>(procAddr(device, "vkBindImageMemory2KHR"));
#endif
#if (defined(VK_KHR_device_group))
        fp_vkCmdSetDeviceMaskKHR = reinterpret_cast<PFN_vkCmdSetDeviceMaskKHR>(procAddr(device, "vkCmdSetDeviceMaskKHR"));
#endif
#if (defined(VK_KHR_device_group))
        fp_vkCmdDispatchBaseKHR = reinterpret_cast<PFN_vkCmdDispatchBaseKHR>(procAddr(device, "vkCmdDispatchBaseKHR"));
#endif
#if (defined(VK_KHR_descriptor_update_template))
        fp_vkCreateDescriptorUpdateTemplateKHR = reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplateKHR>(procAddr(device, "vkCreateDescriptorUpdateTemplateKHR"));
#endif
#if (defined(VK_KHR_descriptor_update_template))
        fp_vkDestroyDescriptorUpdateTemplateKHR = reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplateKHR>(procAddr(device, "vkDestroyDescriptorUpdateTemplateKHR"));
#endif
#if (defined(VK_KHR_descriptor_update_template))
        fp_vkUpdateDescriptorSetWithTemplateKHR = reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplateKHR>(procAddr(device, "vkUpdateDescriptorSetWithTemplateKHR"));
#endif
#if (defined(VK_KHR_get_memory_requirements2))
        fp_vkGetBufferMemoryRequirements2KHR = reinterpret_cast<PFN_vkGetBufferMemoryRequirements2KHR>(procAddr(device, "vkGetBufferMemoryRequirements2KHR"));
#endif
#if (defined(VK_KHR_get_memory_requirements2))
        fp_vkGetImageMemoryRequirements2KHR = reinterpret_cast<PFN_vkGetImageMemoryRequirements2KHR>(procAddr(device, "vkGetImageMemoryRequirements2KHR"));
#endif
#if (defined(VK_KHR_get_memory_requirements2))
        fp_vkGetImageSparseMemoryRequirements2KHR = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2KHR>(procAddr(device, "vkGetImageSparseMemoryRequirements2KHR"));
#endif
#if (defined(VK_KHR_maintenance4))
        fp_vkGetDeviceBufferMemoryRequirementsKHR = reinterpret_cast<PFN_vkGetDeviceBufferMemoryRequirementsKHR>(procAddr(device, "vkGetDeviceBufferMemoryRequirementsKHR"));
#endif
#if (defined(VK_KHR_maintenance4))
        fp_vkGetDeviceImageMemoryRequirementsKHR = reinterpret_cast<PFN_vkGetDeviceImageMemoryRequirementsKHR>(procAddr(device, "vkGetDeviceImageMemoryRequirementsKHR"));
#endif
#if (defined(VK_KHR_maintenance4))
        fp_vkGetDeviceImageSparseMemoryRequirementsKHR = reinterpret_cast<PFN_vkGetDeviceImageSparseMemoryRequirementsKHR>(procAddr(device, "vkGetDeviceImageSparseMemoryRequirementsKHR"));
#endif
#if (defined(VK_KHR_sampler_ycbcr_conversion))
        fp_vkCreateSamplerYcbcrConversionKHR = reinterpret_cast<PFN_vkCreateSamplerYcbcrConversionKHR>(procAddr(device, "vkCreateSamplerYcbcrConversionKHR"));
#endif
#if (defined(VK_KHR_sampler_ycbcr_conversion))
        fp_vkDestroySamplerYcbcrConversionKHR = reinterpret_cast<PFN_vkDestroySamplerYcbcrConversionKHR>(procAddr(device, "vkDestroySamplerYcbcrConversionKHR"));
#endif
#if (defined(VK_KHR_maintenance3))
        fp_vkGetDescriptorSetLayoutSupportKHR = reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupportKHR>(procAddr(device, "vkGetDescriptorSetLayoutSupportKHR"));
#endif
#if (defined(VK_EXT_calibrated_timestamps))
        fp_vkGetCalibratedTimestampsEXT = reinterpret_cast<PFN_vkGetCalibratedTimestampsEXT>(procAddr(device, "vkGetCalibratedTimestampsEXT"));
#endif
#if (defined(VK_KHR_create_renderpass2))
        fp_vkCreateRenderPass2KHR = reinterpret_cast<PFN_vkCreateRenderPass2KHR>(procAddr(device, "vkCreateRenderPass2KHR"));
#endif
#if (defined(VK_KHR_create_renderpass2))
        fp_vkCmdBeginRenderPass2KHR = reinterpret_cast<PFN_vkCmdBeginRenderPass2KHR>(procAddr(device, "vkCmdBeginRenderPass2KHR"));
#endif
#if (defined(VK_KHR_create_renderpass2))
        fp_vkCmdNextSubpass2KHR = reinterpret_cast<PFN_vkCmdNextSubpass2KHR>(procAddr(device, "vkCmdNextSubpass2KHR"));
#endif
#if (defined(VK_KHR_create_renderpass2))
        fp_vkCmdEndRenderPass2KHR = reinterpret_cast<PFN_vkCmdEndRenderPass2KHR>(procAddr(device, "vkCmdEndRenderPass2KHR"));
#endif
#if (defined(VK_KHR_timeline_semaphore))
        fp_vkGetSemaphoreCounterValueKHR = reinterpret_cast<PFN_vkGetSemaphoreCounterValueKHR>(procAddr(device, "vkGetSemaphoreCounterValueKHR"));
#endif
#if (defined(VK_KHR_timeline_semaphore))
        fp_vkWaitSemaphoresKHR = reinterpret_cast<PFN_vkWaitSemaphoresKHR>(procAddr(device, "vkWaitSemaphoresKHR"));
#endif
#if (defined(VK_KHR_timeline_semaphore))
        fp_vkSignalSemaphoreKHR = reinterpret_cast<PFN_vkSignalSemaphoreKHR>(procAddr(device, "vkSignalSemaphoreKHR"));
#endif
#if (defined(VK_AMD_draw_indirect_count))
        fp_vkCmdDrawIndirectCountAMD = reinterpret_cast<PFN_vkCmdDrawIndirectCountAMD>(procAddr(device, "vkCmdDrawIndirectCountAMD"));
#endif
#if (defined(VK_AMD_draw_indirect_count))
        fp_vkCmdDrawIndexedIndirectCountAMD = reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCountAMD>(procAddr(device, "vkCmdDrawIndexedIndirectCountAMD"));
#endif
#if (defined(VK_NV_ray_tracing))
        fp_vkGetRayTracingShaderGroupHandlesNV = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesNV>(procAddr(device, "vkGetRayTracingShaderGroupHandlesNV"));
#endif
#if (defined(VK_KHR_buffer_device_address))
        fp_vkGetBufferOpaqueCaptureAddressKHR = reinterpret_cast<PFN_vkGetBufferOpaqueCaptureAddressKHR>(procAddr(device, "vkGetBufferOpaqueCaptureAddressKHR"));
#endif
#if (defined(VK_EXT_buffer_device_address))
        fp_vkGetBufferDeviceAddressEXT = reinterpret_cast<PFN_vkGetBufferDeviceAddressEXT>(procAddr(device, "vkGetBufferDeviceAddressEXT"));
#endif
#if (defined(VK_KHR_buffer_device_address))
        fp_vkGetDeviceMemoryOpaqueCaptureAddressKHR = reinterpret_cast<PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR>(procAddr(device, "vkGetDeviceMemoryOpaqueCaptureAddressKHR"));
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetCullModeEXT = reinterpret_cast<PFN_vkCmdSetCullModeEXT>(procAddr(device, "vkCmdSetCullModeEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetFrontFaceEXT = reinterpret_cast<PFN_vkCmdSetFrontFaceEXT>(procAddr(device, "vkCmdSetFrontFaceEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetPrimitiveTopologyEXT = reinterpret_cast<PFN_vkCmdSetPrimitiveTopologyEXT>(procAddr(device, "vkCmdSetPrimitiveTopologyEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetViewportWithCountEXT = reinterpret_cast<PFN_vkCmdSetViewportWithCountEXT>(procAddr(device, "vkCmdSetViewportWithCountEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetScissorWithCountEXT = reinterpret_cast<PFN_vkCmdSetScissorWithCountEXT>(procAddr(device, "vkCmdSetScissorWithCountEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
        fp_vkCmdBindVertexBuffers2EXT = reinterpret_cast<PFN_vkCmdBindVertexBuffers2EXT>(procAddr(device, "vkCmdBindVertexBuffers2EXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetDepthTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthTestEnableEXT>(procAddr(device, "vkCmdSetDepthTestEnableEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetDepthWriteEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthWriteEnableEXT>(procAddr(device, "vkCmdSetDepthWriteEnableEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetDepthCompareOpEXT = reinterpret_cast<PFN_vkCmdSetDepthCompareOpEXT>(procAddr(device, "vkCmdSetDepthCompareOpEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetDepthBoundsTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthBoundsTestEnableEXT>(procAddr(device, "vkCmdSetDepthBoundsTestEnableEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetStencilTestEnableEXT = reinterpret_cast<PFN_vkCmdSetStencilTestEnableEXT>(procAddr(device, "vkCmdSetStencilTestEnableEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetStencilOpEXT = reinterpret_cast<PFN_vkCmdSetStencilOpEXT>(procAddr(device, "vkCmdSetStencilOpEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetRasterizerDiscardEnableEXT = reinterpret_cast<PFN_vkCmdSetRasterizerDiscardEnableEXT>(procAddr(device, "vkCmdSetRasterizerDiscardEnableEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetDepthBiasEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthBiasEnableEXT>(procAddr(device, "vkCmdSetDepthBiasEnableEXT"));
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
        fp_vkCmdSetPrimitiveRestartEnableEXT = reinterpret_cast<PFN_vkCmdSetPrimitiveRestartEnableEXT>(procAddr(device, "vkCmdSetPrimitiveRestartEnableEXT"));
#endif
#if (defined(VK_EXT_private_data))
        fp_vkCreatePrivateDataSlotEXT = reinterpret_cast<PFN_vkCreatePrivateDataSlotEXT>(procAddr(device, "vkCreatePrivateDataSlotEXT"));
#endif
#if (defined(VK_EXT_private_data))
        fp_vkDestroyPrivateDataSlotEXT = reinterpret_cast<PFN_vkDestroyPrivateDataSlotEXT>(procAddr(device, "vkDestroyPrivateDataSlotEXT"));
#endif
#if (defined(VK_EXT_private_data))
        fp_vkSetPrivateDataEXT = reinterpret_cast<PFN_vkSetPrivateDataEXT>(procAddr(device, "vkSetPrivateDataEXT"));
#endif
#if (defined(VK_EXT_private_data))
        fp_vkGetPrivateDataEXT = reinterpret_cast<PFN_vkGetPrivateDataEXT>(procAddr(device, "vkGetPrivateDataEXT"));
#endif
#if (defined(VK_KHR_copy_commands2))
        fp_vkCmdCopyBuffer2KHR = reinterpret_cast<PFN_vkCmdCopyBuffer2KHR>(procAddr(device, "vkCmdCopyBuffer2KHR"));
#endif
#if (defined(VK_KHR_copy_commands2))
        fp_vkCmdCopyImage2KHR = reinterpret_cast<PFN_vkCmdCopyImage2KHR>(procAddr(device, "vkCmdCopyImage2KHR"));
#endif
#if (defined(VK_KHR_copy_commands2))
        fp_vkCmdBlitImage2KHR = reinterpret_cast<PFN_vkCmdBlitImage2KHR>(procAddr(device, "vkCmdBlitImage2KHR"));
#endif
#if (defined(VK_KHR_copy_commands2))
        fp_vkCmdCopyBufferToImage2KHR = reinterpret_cast<PFN_vkCmdCopyBufferToImage2KHR>(procAddr(device, "vkCmdCopyBufferToImage2KHR"));
#endif
#if (defined(VK_KHR_copy_commands2))
        fp_vkCmdCopyImageToBuffer2KHR = reinterpret_cast<PFN_vkCmdCopyImageToBuffer2KHR>(procAddr(device, "vkCmdCopyImageToBuffer2KHR"));
#endif
#if (defined(VK_KHR_copy_commands2))
        fp_vkCmdResolveImage2KHR = reinterpret_cast<PFN_vkCmdResolveImage2KHR>(procAddr(device, "vkCmdResolveImage2KHR"));
#endif
#if (defined(VK_KHR_synchronization2))
        fp_vkCmdSetEvent2KHR = reinterpret_cast<PFN_vkCmdSetEvent2KHR>(procAddr(device, "vkCmdSetEvent2KHR"));
#endif
#if (defined(VK_KHR_synchronization2))
        fp_vkCmdResetEvent2KHR = reinterpret_cast<PFN_vkCmdResetEvent2KHR>(procAddr(device, "vkCmdResetEvent2KHR"));
#endif
#if (defined(VK_KHR_synchronization2))
        fp_vkCmdWaitEvents2KHR = reinterpret_cast<PFN_vkCmdWaitEvents2KHR>(procAddr(device, "vkCmdWaitEvents2KHR"));
#endif
#if (defined(VK_KHR_synchronization2))
        fp_vkCmdPipelineBarrier2KHR = reinterpret_cast<PFN_vkCmdPipelineBarrier2KHR>(procAddr(device, "vkCmdPipelineBarrier2KHR"));
#endif
#if (defined(VK_KHR_synchronization2))
        fp_vkQueueSubmit2KHR = reinterpret_cast<PFN_vkQueueSubmit2KHR>(procAddr(device, "vkQueueSubmit2KHR"));
#endif
#if (defined(VK_KHR_synchronization2))
        fp_vkCmdWriteTimestamp2KHR = reinterpret_cast<PFN_vkCmdWriteTimestamp2KHR>(procAddr(device, "vkCmdWriteTimestamp2KHR"));
#endif
#if (defined(VK_KHR_dynamic_rendering))
        fp_vkCmdBeginRenderingKHR = reinterpret_cast<PFN_vkCmdBeginRenderingKHR>(procAddr(device, "vkCmdBeginRenderingKHR"));
#endif
#if (defined(VK_KHR_dynamic_rendering))
        fp_vkCmdEndRenderingKHR = reinterpret_cast<PFN_vkCmdEndRenderingKHR>(procAddr(device, "vkCmdEndRenderingKHR"));
#endif
#if (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))
        fp_vkGetImageSubresourceLayout2EXT = reinterpret_cast<PFN_vkGetImageSubresourceLayout2EXT>(procAddr(device, "vkGetImageSubresourceLayout2EXT"));
#endif
    }
    void getDeviceQueue(uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) const noexcept {
        fp_vkGetDeviceQueue(device, queueFamilyIndex, queueIndex, pQueue);
    }
    VkResult queueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) const noexcept {
        return fp_vkQueueSubmit(queue, submitCount, pSubmits, fence);
    }
    VkResult queueWaitIdle(VkQueue queue) const noexcept {
        return fp_vkQueueWaitIdle(queue);
    }
    VkResult deviceWaitIdle() const noexcept {
        return fp_vkDeviceWaitIdle(device);
    }
    VkResult allocateMemory(const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) const noexcept {
        return fp_vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory);
    }
    void freeMemory(VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkFreeMemory(device, memory, pAllocator);
    }
    VkResult mapMemory(VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) const noexcept {
        return fp_vkMapMemory(device, memory, offset, size, flags, ppData);
    }
    void unmapMemory(VkDeviceMemory memory) const noexcept {
        fp_vkUnmapMemory(device, memory);
    }
    VkResult flushMappedMemoryRanges(uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) const noexcept {
        return fp_vkFlushMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
    }
    VkResult invalidateMappedMemoryRanges(uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) const noexcept {
        return fp_vkInvalidateMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
    }
    void getDeviceMemoryCommitment(VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes) const noexcept {
        fp_vkGetDeviceMemoryCommitment(device, memory, pCommittedMemoryInBytes);
    }
    void getBufferMemoryRequirements(VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements) const noexcept {
        fp_vkGetBufferMemoryRequirements(device, buffer, pMemoryRequirements);
    }
    VkResult bindBufferMemory(VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) const noexcept {
        return fp_vkBindBufferMemory(device, buffer, memory, memoryOffset);
    }
    void getImageMemoryRequirements(VkImage image, VkMemoryRequirements* pMemoryRequirements) const noexcept {
        fp_vkGetImageMemoryRequirements(device, image, pMemoryRequirements);
    }
    VkResult bindImageMemory(VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) const noexcept {
        return fp_vkBindImageMemory(device, image, memory, memoryOffset);
    }
    void getImageSparseMemoryRequirements(VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements) const noexcept {
        fp_vkGetImageSparseMemoryRequirements(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    }
    VkResult queueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence) const noexcept {
        return fp_vkQueueBindSparse(queue, bindInfoCount, pBindInfo, fence);
    }
    VkResult createFence(const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) const noexcept {
        return fp_vkCreateFence(device, pCreateInfo, pAllocator, pFence);
    }
    void destroyFence(VkFence fence, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyFence(device, fence, pAllocator);
    }
    VkResult resetFences(uint32_t fenceCount, const VkFence* pFences) const noexcept {
        return fp_vkResetFences(device, fenceCount, pFences);
    }
    VkResult getFenceStatus(VkFence fence) const noexcept {
        return fp_vkGetFenceStatus(device, fence);
    }
    VkResult waitForFences(uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout) const noexcept {
        return fp_vkWaitForFences(device, fenceCount, pFences, waitAll, timeout);
    }
    VkResult createSemaphore(const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) const noexcept {
        return fp_vkCreateSemaphore(device, pCreateInfo, pAllocator, pSemaphore);
    }
    void destroySemaphore(VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroySemaphore(device, semaphore, pAllocator);
    }
    VkResult createEvent(const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent) const noexcept {
        return fp_vkCreateEvent(device, pCreateInfo, pAllocator, pEvent);
    }
    void destroyEvent(VkEvent event, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyEvent(device, event, pAllocator);
    }
    VkResult getEventStatus(VkEvent event) const noexcept {
        return fp_vkGetEventStatus(device, event);
    }
    VkResult setEvent(VkEvent event) const noexcept {
        return fp_vkSetEvent(device, event);
    }
    VkResult resetEvent(VkEvent event) const noexcept {
        return fp_vkResetEvent(device, event);
    }
    VkResult createQueryPool(const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool) const noexcept {
        return fp_vkCreateQueryPool(device, pCreateInfo, pAllocator, pQueryPool);
    }
    void destroyQueryPool(VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyQueryPool(device, queryPool, pAllocator);
    }
    VkResult getQueryPoolResults(VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags) const noexcept {
        return fp_vkGetQueryPoolResults(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
    }
#if (defined(VK_VERSION_1_2))
    void resetQueryPool(VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) const noexcept {
        fp_vkResetQueryPool(device, queryPool, firstQuery, queryCount);
    }
#endif
    VkResult createBuffer(const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer) const noexcept {
        return fp_vkCreateBuffer(device, pCreateInfo, pAllocator, pBuffer);
    }
    void destroyBuffer(VkBuffer buffer, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyBuffer(device, buffer, pAllocator);
    }
    VkResult createBufferView(const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView) const noexcept {
        return fp_vkCreateBufferView(device, pCreateInfo, pAllocator, pView);
    }
    void destroyBufferView(VkBufferView bufferView, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyBufferView(device, bufferView, pAllocator);
    }
    VkResult createImage(const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage) const noexcept {
        return fp_vkCreateImage(device, pCreateInfo, pAllocator, pImage);
    }
    void destroyImage(VkImage image, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyImage(device, image, pAllocator);
    }
    void getImageSubresourceLayout(VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout) const noexcept {
        fp_vkGetImageSubresourceLayout(device, image, pSubresource, pLayout);
    }
    VkResult createImageView(const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView) const noexcept {
        return fp_vkCreateImageView(device, pCreateInfo, pAllocator, pView);
    }
    void destroyImageView(VkImageView imageView, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyImageView(device, imageView, pAllocator);
    }
    VkResult createShaderModule(const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule) const noexcept {
        return fp_vkCreateShaderModule(device, pCreateInfo, pAllocator, pShaderModule);
    }
    void destroyShaderModule(VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyShaderModule(device, shaderModule, pAllocator);
    }
    VkResult createPipelineCache(const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache) const noexcept {
        return fp_vkCreatePipelineCache(device, pCreateInfo, pAllocator, pPipelineCache);
    }
    void destroyPipelineCache(VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyPipelineCache(device, pipelineCache, pAllocator);
    }
    VkResult getPipelineCacheData(VkPipelineCache pipelineCache, size_t* pDataSize, void* pData) const noexcept {
        return fp_vkGetPipelineCacheData(device, pipelineCache, pDataSize, pData);
    }
    VkResult mergePipelineCaches(VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches) const noexcept {
        return fp_vkMergePipelineCaches(device, dstCache, srcCacheCount, pSrcCaches);
    }
    VkResult createGraphicsPipelines(VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) const noexcept {
        return fp_vkCreateGraphicsPipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    }
    VkResult createComputePipelines(VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) const noexcept {
        return fp_vkCreateComputePipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    }
#if (defined(VK_HUAWEI_subpass_shading))
    VkResult getDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(VkRenderPass renderpass, VkExtent2D* pMaxWorkgroupSize) const noexcept {
        return fp_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(device, renderpass, pMaxWorkgroupSize);
    }
#endif
    void destroyPipeline(VkPipeline pipeline, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyPipeline(device, pipeline, pAllocator);
    }
    VkResult createPipelineLayout(const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout) const noexcept {
        return fp_vkCreatePipelineLayout(device, pCreateInfo, pAllocator, pPipelineLayout);
    }
    void destroyPipelineLayout(VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyPipelineLayout(device, pipelineLayout, pAllocator);
    }
    VkResult createSampler(const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler) const noexcept {
        return fp_vkCreateSampler(device, pCreateInfo, pAllocator, pSampler);
    }
    void destroySampler(VkSampler sampler, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroySampler(device, sampler, pAllocator);
    }
    VkResult createDescriptorSetLayout(const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout) const noexcept {
        return fp_vkCreateDescriptorSetLayout(device, pCreateInfo, pAllocator, pSetLayout);
    }
    void destroyDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyDescriptorSetLayout(device, descriptorSetLayout, pAllocator);
    }
    VkResult createDescriptorPool(const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool) const noexcept {
        return fp_vkCreateDescriptorPool(device, pCreateInfo, pAllocator, pDescriptorPool);
    }
    void destroyDescriptorPool(VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyDescriptorPool(device, descriptorPool, pAllocator);
    }
    VkResult resetDescriptorPool(VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) const noexcept {
        return fp_vkResetDescriptorPool(device, descriptorPool, flags);
    }
    VkResult allocateDescriptorSets(const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) const noexcept {
        return fp_vkAllocateDescriptorSets(device, pAllocateInfo, pDescriptorSets);
    }
    VkResult freeDescriptorSets(VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets) const noexcept {
        return fp_vkFreeDescriptorSets(device, descriptorPool, descriptorSetCount, pDescriptorSets);
    }
    void updateDescriptorSets(uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) const noexcept {
        fp_vkUpdateDescriptorSets(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
    }
    VkResult createFramebuffer(const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) const noexcept {
        return fp_vkCreateFramebuffer(device, pCreateInfo, pAllocator, pFramebuffer);
    }
    void destroyFramebuffer(VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyFramebuffer(device, framebuffer, pAllocator);
    }
    VkResult createRenderPass(const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) const noexcept {
        return fp_vkCreateRenderPass(device, pCreateInfo, pAllocator, pRenderPass);
    }
    void destroyRenderPass(VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyRenderPass(device, renderPass, pAllocator);
    }
    void getRenderAreaGranularity(VkRenderPass renderPass, VkExtent2D* pGranularity) const noexcept {
        fp_vkGetRenderAreaGranularity(device, renderPass, pGranularity);
    }
#if (defined(VK_KHR_maintenance5))
    void getRenderingAreaGranularityKHR(const VkRenderingAreaInfoKHR* pRenderingAreaInfo, VkExtent2D* pGranularity) const noexcept {
        fp_vkGetRenderingAreaGranularityKHR(device, pRenderingAreaInfo, pGranularity);
    }
#endif
    VkResult createCommandPool(const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) const noexcept {
        return fp_vkCreateCommandPool(device, pCreateInfo, pAllocator, pCommandPool);
    }
    void destroyCommandPool(VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyCommandPool(device, commandPool, pAllocator);
    }
    VkResult resetCommandPool(VkCommandPool commandPool, VkCommandPoolResetFlags flags) const noexcept {
        return fp_vkResetCommandPool(device, commandPool, flags);
    }
    VkResult allocateCommandBuffers(const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) const noexcept {
        return fp_vkAllocateCommandBuffers(device, pAllocateInfo, pCommandBuffers);
    }
    void freeCommandBuffers(VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) const noexcept {
        fp_vkFreeCommandBuffers(device, commandPool, commandBufferCount, pCommandBuffers);
    }
    VkResult beginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) const noexcept {
        return fp_vkBeginCommandBuffer(commandBuffer, pBeginInfo);
    }
    VkResult endCommandBuffer(VkCommandBuffer commandBuffer) const noexcept {
        return fp_vkEndCommandBuffer(commandBuffer);
    }
    VkResult resetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) const noexcept {
        return fp_vkResetCommandBuffer(commandBuffer, flags);
    }
    void cmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) const noexcept {
        fp_vkCmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline);
    }
#if (defined(VK_EXT_attachment_feedback_loop_dynamic_state))
    void cmdSetAttachmentFeedbackLoopEnableEXT(VkCommandBuffer commandBuffer, VkImageAspectFlags aspectMask) const noexcept {
        fp_vkCmdSetAttachmentFeedbackLoopEnableEXT(commandBuffer, aspectMask);
    }
#endif
    void cmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) const noexcept {
        fp_vkCmdSetViewport(commandBuffer, firstViewport, viewportCount, pViewports);
    }
    void cmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) const noexcept {
        fp_vkCmdSetScissor(commandBuffer, firstScissor, scissorCount, pScissors);
    }
    void cmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) const noexcept {
        fp_vkCmdSetLineWidth(commandBuffer, lineWidth);
    }
    void cmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) const noexcept {
        fp_vkCmdSetDepthBias(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
    }
    void cmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]) const noexcept {
        fp_vkCmdSetBlendConstants(commandBuffer, blendConstants);
    }
    void cmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) const noexcept {
        fp_vkCmdSetDepthBounds(commandBuffer, minDepthBounds, maxDepthBounds);
    }
    void cmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) const noexcept {
        fp_vkCmdSetStencilCompareMask(commandBuffer, faceMask, compareMask);
    }
    void cmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) const noexcept {
        fp_vkCmdSetStencilWriteMask(commandBuffer, faceMask, writeMask);
    }
    void cmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) const noexcept {
        fp_vkCmdSetStencilReference(commandBuffer, faceMask, reference);
    }
    void cmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) const noexcept {
        fp_vkCmdBindDescriptorSets(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
    }
    void cmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) const noexcept {
        fp_vkCmdBindIndexBuffer(commandBuffer, buffer, offset, indexType);
    }
    void cmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) const noexcept {
        fp_vkCmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
    }
    void cmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const noexcept {
        fp_vkCmdDraw(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    }
    void cmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const noexcept {
        fp_vkCmdDrawIndexed(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
    }
#if (defined(VK_EXT_multi_draw))
    void cmdDrawMultiEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride) const noexcept {
        fp_vkCmdDrawMultiEXT(commandBuffer, drawCount, pVertexInfo, instanceCount, firstInstance, stride);
    }
#endif
#if (defined(VK_EXT_multi_draw))
    void cmdDrawMultiIndexedEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset) const noexcept {
        fp_vkCmdDrawMultiIndexedEXT(commandBuffer, drawCount, pIndexInfo, instanceCount, firstInstance, stride, pVertexOffset);
    }
#endif
    void cmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const noexcept {
        fp_vkCmdDrawIndirect(commandBuffer, buffer, offset, drawCount, stride);
    }
    void cmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const noexcept {
        fp_vkCmdDrawIndexedIndirect(commandBuffer, buffer, offset, drawCount, stride);
    }
    void cmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const noexcept {
        fp_vkCmdDispatch(commandBuffer, groupCountX, groupCountY, groupCountZ);
    }
    void cmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) const noexcept {
        fp_vkCmdDispatchIndirect(commandBuffer, buffer, offset);
    }
#if (defined(VK_HUAWEI_subpass_shading))
    void cmdSubpassShadingHUAWEI(VkCommandBuffer commandBuffer) const noexcept {
        fp_vkCmdSubpassShadingHUAWEI(commandBuffer);
    }
#endif
#if (defined(VK_HUAWEI_cluster_culling_shader))
    void cmdDrawClusterHUAWEI(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const noexcept {
        fp_vkCmdDrawClusterHUAWEI(commandBuffer, groupCountX, groupCountY, groupCountZ);
    }
#endif
#if (defined(VK_HUAWEI_cluster_culling_shader))
    void cmdDrawClusterIndirectHUAWEI(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) const noexcept {
        fp_vkCmdDrawClusterIndirectHUAWEI(commandBuffer, buffer, offset);
    }
#endif
#if (defined(VK_NV_device_generated_commands_compute))
    void cmdUpdatePipelineIndirectBufferNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) const noexcept {
        fp_vkCmdUpdatePipelineIndirectBufferNV(commandBuffer, pipelineBindPoint, pipeline);
    }
#endif
    void cmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions) const noexcept {
        fp_vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
    }
    void cmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions) const noexcept {
        fp_vkCmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    }
    void cmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter) const noexcept {
        fp_vkCmdBlitImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
    }
    void cmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions) const noexcept {
        fp_vkCmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
    }
    void cmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) const noexcept {
        fp_vkCmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
    }
#if (defined(VK_NV_copy_memory_indirect))
    void cmdCopyMemoryIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride) const noexcept {
        fp_vkCmdCopyMemoryIndirectNV(commandBuffer, copyBufferAddress, copyCount, stride);
    }
#endif
#if (defined(VK_NV_copy_memory_indirect))
    void cmdCopyMemoryToImageIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources) const noexcept {
        fp_vkCmdCopyMemoryToImageIndirectNV(commandBuffer, copyBufferAddress, copyCount, stride, dstImage, dstImageLayout, pImageSubresources);
    }
#endif
    void cmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData) const noexcept {
        fp_vkCmdUpdateBuffer(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
    }
    void cmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) const noexcept {
        fp_vkCmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data);
    }
    void cmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) const noexcept {
        fp_vkCmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
    }
    void cmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) const noexcept {
        fp_vkCmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
    }
    void cmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) const noexcept {
        fp_vkCmdClearAttachments(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
    }
    void cmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions) const noexcept {
        fp_vkCmdResolveImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    }
    void cmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) const noexcept {
        fp_vkCmdSetEvent(commandBuffer, event, stageMask);
    }
    void cmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) const noexcept {
        fp_vkCmdResetEvent(commandBuffer, event, stageMask);
    }
    void cmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) const noexcept {
        fp_vkCmdWaitEvents(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    }
    void cmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) const noexcept {
        fp_vkCmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    }
    void cmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) const noexcept {
        fp_vkCmdBeginQuery(commandBuffer, queryPool, query, flags);
    }
    void cmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) const noexcept {
        fp_vkCmdEndQuery(commandBuffer, queryPool, query);
    }
#if (defined(VK_EXT_conditional_rendering))
    void cmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin) const noexcept {
        fp_vkCmdBeginConditionalRenderingEXT(commandBuffer, pConditionalRenderingBegin);
    }
#endif
#if (defined(VK_EXT_conditional_rendering))
    void cmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer) const noexcept {
        fp_vkCmdEndConditionalRenderingEXT(commandBuffer);
    }
#endif
    void cmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) const noexcept {
        fp_vkCmdResetQueryPool(commandBuffer, queryPool, firstQuery, queryCount);
    }
    void cmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) const noexcept {
        fp_vkCmdWriteTimestamp(commandBuffer, pipelineStage, queryPool, query);
    }
    void cmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) const noexcept {
        fp_vkCmdCopyQueryPoolResults(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
    }
    void cmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) const noexcept {
        fp_vkCmdPushConstants(commandBuffer, layout, stageFlags, offset, size, pValues);
    }
    void cmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) const noexcept {
        fp_vkCmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents);
    }
    void cmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) const noexcept {
        fp_vkCmdNextSubpass(commandBuffer, contents);
    }
    void cmdEndRenderPass(VkCommandBuffer commandBuffer) const noexcept {
        fp_vkCmdEndRenderPass(commandBuffer);
    }
    void cmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) const noexcept {
        fp_vkCmdExecuteCommands(commandBuffer, commandBufferCount, pCommandBuffers);
    }
#if (defined(VK_KHR_display_swapchain))
    VkResult createSharedSwapchainsKHR(uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains) const noexcept {
        return fp_vkCreateSharedSwapchainsKHR(device, swapchainCount, pCreateInfos, pAllocator, pSwapchains);
    }
#endif
#if (defined(VK_KHR_swapchain))
    VkResult createSwapchainKHR(const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) const noexcept {
        return fp_vkCreateSwapchainKHR(device, pCreateInfo, pAllocator, pSwapchain);
    }
#endif
#if (defined(VK_KHR_swapchain))
    void destroySwapchainKHR(VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroySwapchainKHR(device, swapchain, pAllocator);
    }
#endif
#if (defined(VK_KHR_swapchain))
    VkResult getSwapchainImagesKHR(VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) const noexcept {
        return fp_vkGetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages);
    }
#endif
#if (defined(VK_KHR_swapchain))
    VkResult acquireNextImageKHR(VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) const noexcept {
        return fp_vkAcquireNextImageKHR(device, swapchain, timeout, semaphore, fence, pImageIndex);
    }
#endif
#if (defined(VK_KHR_swapchain))
    VkResult queuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo) const noexcept {
        return fp_vkQueuePresentKHR(queue, pPresentInfo);
    }
#endif
#if (defined(VK_EXT_debug_marker))
    VkResult debugMarkerSetObjectNameEXT(const VkDebugMarkerObjectNameInfoEXT* pNameInfo) const noexcept {
        return fp_vkDebugMarkerSetObjectNameEXT(device, pNameInfo);
    }
#endif
#if (defined(VK_EXT_debug_marker))
    VkResult debugMarkerSetObjectTagEXT(const VkDebugMarkerObjectTagInfoEXT* pTagInfo) const noexcept {
        return fp_vkDebugMarkerSetObjectTagEXT(device, pTagInfo);
    }
#endif
#if (defined(VK_EXT_debug_marker))
    void cmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) const noexcept {
        fp_vkCmdDebugMarkerBeginEXT(commandBuffer, pMarkerInfo);
    }
#endif
#if (defined(VK_EXT_debug_marker))
    void cmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) const noexcept {
        fp_vkCmdDebugMarkerEndEXT(commandBuffer);
    }
#endif
#if (defined(VK_EXT_debug_marker))
    void cmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) const noexcept {
        fp_vkCmdDebugMarkerInsertEXT(commandBuffer, pMarkerInfo);
    }
#endif
#if (defined(VK_NV_external_memory_win32))
    VkResult getMemoryWin32HandleNV(VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle) const noexcept {
        return fp_vkGetMemoryWin32HandleNV(device, memory, handleType, pHandle);
    }
#endif
#if (defined(VK_NV_device_generated_commands))
    void cmdExecuteGeneratedCommandsNV(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) const noexcept {
        fp_vkCmdExecuteGeneratedCommandsNV(commandBuffer, isPreprocessed, pGeneratedCommandsInfo);
    }
#endif
#if (defined(VK_NV_device_generated_commands))
    void cmdPreprocessGeneratedCommandsNV(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) const noexcept {
        fp_vkCmdPreprocessGeneratedCommandsNV(commandBuffer, pGeneratedCommandsInfo);
    }
#endif
#if (defined(VK_NV_device_generated_commands))
    void cmdBindPipelineShaderGroupNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex) const noexcept {
        fp_vkCmdBindPipelineShaderGroupNV(commandBuffer, pipelineBindPoint, pipeline, groupIndex);
    }
#endif
#if (defined(VK_NV_device_generated_commands))
    void getGeneratedCommandsMemoryRequirementsNV(const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) const noexcept {
        fp_vkGetGeneratedCommandsMemoryRequirementsNV(device, pInfo, pMemoryRequirements);
    }
#endif
#if (defined(VK_NV_device_generated_commands))
    VkResult createIndirectCommandsLayoutNV(const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout) const noexcept {
        return fp_vkCreateIndirectCommandsLayoutNV(device, pCreateInfo, pAllocator, pIndirectCommandsLayout);
    }
#endif
#if (defined(VK_NV_device_generated_commands))
    void destroyIndirectCommandsLayoutNV(VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyIndirectCommandsLayoutNV(device, indirectCommandsLayout, pAllocator);
    }
#endif
#if (defined(VK_KHR_push_descriptor))
    void cmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites) const noexcept {
        fp_vkCmdPushDescriptorSetKHR(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void trimCommandPool(VkCommandPool commandPool, VkCommandPoolTrimFlagsKHR flags) const noexcept {
        fp_vkTrimCommandPool(device, commandPool, flags);
    }
#endif
#if (defined(VK_KHR_external_memory_win32))
    VkResult getMemoryWin32HandleKHR(const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) const noexcept {
        return fp_vkGetMemoryWin32HandleKHR(device, pGetWin32HandleInfo, pHandle);
    }
#endif
#if (defined(VK_KHR_external_memory_win32))
    VkResult getMemoryWin32HandlePropertiesKHR(VkExternalMemoryHandleTypeFlagBitsKHR handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties) const noexcept {
        return fp_vkGetMemoryWin32HandlePropertiesKHR(device, handleType, handle, pMemoryWin32HandleProperties);
    }
#endif
#if (defined(VK_KHR_external_memory_fd))
    VkResult getMemoryFdKHR(const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd) const noexcept {
        return fp_vkGetMemoryFdKHR(device, pGetFdInfo, pFd);
    }
#endif
#if (defined(VK_KHR_external_memory_fd))
    VkResult getMemoryFdPropertiesKHR(VkExternalMemoryHandleTypeFlagBitsKHR handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties) const noexcept {
        return fp_vkGetMemoryFdPropertiesKHR(device, handleType, fd, pMemoryFdProperties);
    }
#endif
#if (defined(VK_FUCHSIA_external_memory))
    VkResult getMemoryZirconHandleFUCHSIA(const VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) const noexcept {
        return fp_vkGetMemoryZirconHandleFUCHSIA(device, pGetZirconHandleInfo, pZirconHandle);
    }
#endif
#if (defined(VK_FUCHSIA_external_memory))
    VkResult getMemoryZirconHandlePropertiesFUCHSIA(VkExternalMemoryHandleTypeFlagBitsKHR handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties) const noexcept {
        return fp_vkGetMemoryZirconHandlePropertiesFUCHSIA(device, handleType, zirconHandle, pMemoryZirconHandleProperties);
    }
#endif
#if (defined(VK_NV_external_memory_rdma))
    VkResult getMemoryRemoteAddressNV(const VkMemoryGetRemoteAddressInfoNV* pMemoryGetRemoteAddressInfo, VkRemoteAddressNV* pAddress) const noexcept {
        return fp_vkGetMemoryRemoteAddressNV(device, pMemoryGetRemoteAddressInfo, pAddress);
    }
#endif
#if (defined(VK_NV_external_memory_sci_buf))
    VkResult getMemorySciBufNV(const VkMemoryGetSciBufInfoNV* pGetSciBufInfo, NvSciBufObj* pHandle) const noexcept {
        return fp_vkGetMemorySciBufNV(device, pGetSciBufInfo, pHandle);
    }
#endif
#if (defined(VK_KHR_external_semaphore_win32))
    VkResult getSemaphoreWin32HandleKHR(const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) const noexcept {
        return fp_vkGetSemaphoreWin32HandleKHR(device, pGetWin32HandleInfo, pHandle);
    }
#endif
#if (defined(VK_KHR_external_semaphore_win32))
    VkResult importSemaphoreWin32HandleKHR(const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo) const noexcept {
        return fp_vkImportSemaphoreWin32HandleKHR(device, pImportSemaphoreWin32HandleInfo);
    }
#endif
#if (defined(VK_KHR_external_semaphore_fd))
    VkResult getSemaphoreFdKHR(const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd) const noexcept {
        return fp_vkGetSemaphoreFdKHR(device, pGetFdInfo, pFd);
    }
#endif
#if (defined(VK_KHR_external_semaphore_fd))
    VkResult importSemaphoreFdKHR(const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo) const noexcept {
        return fp_vkImportSemaphoreFdKHR(device, pImportSemaphoreFdInfo);
    }
#endif
#if (defined(VK_FUCHSIA_external_semaphore))
    VkResult getSemaphoreZirconHandleFUCHSIA(const VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) const noexcept {
        return fp_vkGetSemaphoreZirconHandleFUCHSIA(device, pGetZirconHandleInfo, pZirconHandle);
    }
#endif
#if (defined(VK_FUCHSIA_external_semaphore))
    VkResult importSemaphoreZirconHandleFUCHSIA(const VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo) const noexcept {
        return fp_vkImportSemaphoreZirconHandleFUCHSIA(device, pImportSemaphoreZirconHandleInfo);
    }
#endif
#if (defined(VK_KHR_external_fence_win32))
    VkResult getFenceWin32HandleKHR(const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) const noexcept {
        return fp_vkGetFenceWin32HandleKHR(device, pGetWin32HandleInfo, pHandle);
    }
#endif
#if (defined(VK_KHR_external_fence_win32))
    VkResult importFenceWin32HandleKHR(const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo) const noexcept {
        return fp_vkImportFenceWin32HandleKHR(device, pImportFenceWin32HandleInfo);
    }
#endif
#if (defined(VK_KHR_external_fence_fd))
    VkResult getFenceFdKHR(const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd) const noexcept {
        return fp_vkGetFenceFdKHR(device, pGetFdInfo, pFd);
    }
#endif
#if (defined(VK_KHR_external_fence_fd))
    VkResult importFenceFdKHR(const VkImportFenceFdInfoKHR* pImportFenceFdInfo) const noexcept {
        return fp_vkImportFenceFdKHR(device, pImportFenceFdInfo);
    }
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
    VkResult getFenceSciSyncFenceNV(const VkFenceGetSciSyncInfoNV* pGetSciSyncHandleInfo, void* pHandle) const noexcept {
        return fp_vkGetFenceSciSyncFenceNV(device, pGetSciSyncHandleInfo, pHandle);
    }
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
    VkResult getFenceSciSyncObjNV(const VkFenceGetSciSyncInfoNV* pGetSciSyncHandleInfo, void* pHandle) const noexcept {
        return fp_vkGetFenceSciSyncObjNV(device, pGetSciSyncHandleInfo, pHandle);
    }
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
    VkResult importFenceSciSyncFenceNV(const VkImportFenceSciSyncInfoNV* pImportFenceSciSyncInfo) const noexcept {
        return fp_vkImportFenceSciSyncFenceNV(device, pImportFenceSciSyncInfo);
    }
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
    VkResult importFenceSciSyncObjNV(const VkImportFenceSciSyncInfoNV* pImportFenceSciSyncInfo) const noexcept {
        return fp_vkImportFenceSciSyncObjNV(device, pImportFenceSciSyncInfo);
    }
#endif
#if (defined(VK_NV_external_sci_sync))
    VkResult getSemaphoreSciSyncObjNV(const VkSemaphoreGetSciSyncInfoNV* pGetSciSyncInfo, void* pHandle) const noexcept {
        return fp_vkGetSemaphoreSciSyncObjNV(device, pGetSciSyncInfo, pHandle);
    }
#endif
#if (defined(VK_NV_external_sci_sync))
    VkResult importSemaphoreSciSyncObjNV(const VkImportSemaphoreSciSyncInfoNV* pImportSemaphoreSciSyncInfo) const noexcept {
        return fp_vkImportSemaphoreSciSyncObjNV(device, pImportSemaphoreSciSyncInfo);
    }
#endif
#if (defined(VK_NV_external_sci_sync2))
    VkResult createSemaphoreSciSyncPoolNV(const VkSemaphoreSciSyncPoolCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphoreSciSyncPoolNV* pSemaphorePool) const noexcept {
        return fp_vkCreateSemaphoreSciSyncPoolNV(device, pCreateInfo, pAllocator, pSemaphorePool);
    }
#endif
#if (defined(VK_NV_external_sci_sync2))
    void destroySemaphoreSciSyncPoolNV(VkSemaphoreSciSyncPoolNV semaphorePool, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroySemaphoreSciSyncPoolNV(device, semaphorePool, pAllocator);
    }
#endif
#if (defined(VK_EXT_display_control))
    VkResult displayPowerControlEXT(VkDisplayKHR display, const VkDisplayPowerInfoEXT* pDisplayPowerInfo) const noexcept {
        return fp_vkDisplayPowerControlEXT(device, display, pDisplayPowerInfo);
    }
#endif
#if (defined(VK_EXT_display_control))
    VkResult registerDeviceEventEXT(const VkDeviceEventInfoEXT* pDeviceEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) const noexcept {
        return fp_vkRegisterDeviceEventEXT(device, pDeviceEventInfo, pAllocator, pFence);
    }
#endif
#if (defined(VK_EXT_display_control))
    VkResult registerDisplayEventEXT(VkDisplayKHR display, const VkDisplayEventInfoEXT* pDisplayEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) const noexcept {
        return fp_vkRegisterDisplayEventEXT(device, display, pDisplayEventInfo, pAllocator, pFence);
    }
#endif
#if (defined(VK_EXT_display_control))
    VkResult getSwapchainCounterEXT(VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue) const noexcept {
        return fp_vkGetSwapchainCounterEXT(device, swapchain, counter, pCounterValue);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getDeviceGroupPeerMemoryFeatures(uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlagsKHR* pPeerMemoryFeatures) const noexcept {
        fp_vkGetDeviceGroupPeerMemoryFeatures(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    }
#endif
#if (defined(VK_VERSION_1_1))
    VkResult bindBufferMemory2(uint32_t bindInfoCount, const VkBindBufferMemoryInfoKHR* pBindInfos) const noexcept {
        return fp_vkBindBufferMemory2(device, bindInfoCount, pBindInfos);
    }
#endif
#if (defined(VK_VERSION_1_1))
    VkResult bindImageMemory2(uint32_t bindInfoCount, const VkBindImageMemoryInfoKHR* pBindInfos) const noexcept {
        return fp_vkBindImageMemory2(device, bindInfoCount, pBindInfos);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void cmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) const noexcept {
        fp_vkCmdSetDeviceMask(commandBuffer, deviceMask);
    }
#endif
#if (defined(VK_KHR_swapchain)) || (defined(VK_KHR_device_group))
    VkResult getDeviceGroupPresentCapabilitiesKHR(VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) const noexcept {
        return fp_vkGetDeviceGroupPresentCapabilitiesKHR(device, pDeviceGroupPresentCapabilities);
    }
#endif
#if (defined(VK_KHR_swapchain)) || (defined(VK_KHR_device_group))
    VkResult getDeviceGroupSurfacePresentModesKHR(VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes) const noexcept {
        return fp_vkGetDeviceGroupSurfacePresentModesKHR(device, surface, pModes);
    }
#endif
#if (defined(VK_KHR_swapchain)) || (defined(VK_KHR_device_group))
    VkResult acquireNextImage2KHR(const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex) const noexcept {
        return fp_vkAcquireNextImage2KHR(device, pAcquireInfo, pImageIndex);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void cmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const noexcept {
        fp_vkCmdDispatchBase(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    }
#endif
#if (defined(VK_VERSION_1_1))
    VkResult createDescriptorUpdateTemplate(const VkDescriptorUpdateTemplateCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplateKHR* pDescriptorUpdateTemplate) const noexcept {
        return fp_vkCreateDescriptorUpdateTemplate(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void destroyDescriptorUpdateTemplate(VkDescriptorUpdateTemplateKHR descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyDescriptorUpdateTemplate(device, descriptorUpdateTemplate, pAllocator);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void updateDescriptorSetWithTemplate(VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplateKHR descriptorUpdateTemplate, const void* pData) const noexcept {
        fp_vkUpdateDescriptorSetWithTemplate(device, descriptorSet, descriptorUpdateTemplate, pData);
    }
#endif
#if (defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_descriptor_update_template))
    void cmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplateKHR descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData) const noexcept {
        fp_vkCmdPushDescriptorSetWithTemplateKHR(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
    }
#endif
#if (defined(VK_EXT_hdr_metadata))
    void setHdrMetadataEXT(uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata) const noexcept {
        fp_vkSetHdrMetadataEXT(device, swapchainCount, pSwapchains, pMetadata);
    }
#endif
#if (defined(VK_KHR_shared_presentable_image))
    VkResult getSwapchainStatusKHR(VkSwapchainKHR swapchain) const noexcept {
        return fp_vkGetSwapchainStatusKHR(device, swapchain);
    }
#endif
#if (defined(VK_GOOGLE_display_timing))
    VkResult getRefreshCycleDurationGOOGLE(VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties) const noexcept {
        return fp_vkGetRefreshCycleDurationGOOGLE(device, swapchain, pDisplayTimingProperties);
    }
#endif
#if (defined(VK_GOOGLE_display_timing))
    VkResult getPastPresentationTimingGOOGLE(VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings) const noexcept {
        return fp_vkGetPastPresentationTimingGOOGLE(device, swapchain, pPresentationTimingCount, pPresentationTimings);
    }
#endif
#if (defined(VK_NV_clip_space_w_scaling))
    void cmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings) const noexcept {
        fp_vkCmdSetViewportWScalingNV(commandBuffer, firstViewport, viewportCount, pViewportWScalings);
    }
#endif
#if (defined(VK_EXT_discard_rectangles))
    void cmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles) const noexcept {
        fp_vkCmdSetDiscardRectangleEXT(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles);
    }
#endif
#if ((defined(VK_EXT_discard_rectangles))) && VK_HEADER_VERSION >= 241
    void cmdSetDiscardRectangleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable) const noexcept {
        fp_vkCmdSetDiscardRectangleEnableEXT(commandBuffer, discardRectangleEnable);
    }
#endif
#if ((defined(VK_EXT_discard_rectangles))) && VK_HEADER_VERSION >= 241
    void cmdSetDiscardRectangleModeEXT(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode) const noexcept {
        fp_vkCmdSetDiscardRectangleModeEXT(commandBuffer, discardRectangleMode);
    }
#endif
#if (defined(VK_EXT_sample_locations))
    void cmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo) const noexcept {
        fp_vkCmdSetSampleLocationsEXT(commandBuffer, pSampleLocationsInfo);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getBufferMemoryRequirements2(const VkBufferMemoryRequirementsInfo2KHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) const noexcept {
        fp_vkGetBufferMemoryRequirements2(device, pInfo, pMemoryRequirements);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getImageMemoryRequirements2(const VkImageMemoryRequirementsInfo2KHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) const noexcept {
        fp_vkGetImageMemoryRequirements2(device, pInfo, pMemoryRequirements);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getImageSparseMemoryRequirements2(const VkImageSparseMemoryRequirementsInfo2KHR* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2KHR* pSparseMemoryRequirements) const noexcept {
        fp_vkGetImageSparseMemoryRequirements2(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void getDeviceBufferMemoryRequirements(const VkDeviceBufferMemoryRequirementsKHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) const noexcept {
        fp_vkGetDeviceBufferMemoryRequirements(device, pInfo, pMemoryRequirements);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void getDeviceImageMemoryRequirements(const VkDeviceImageMemoryRequirementsKHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) const noexcept {
        fp_vkGetDeviceImageMemoryRequirements(device, pInfo, pMemoryRequirements);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void getDeviceImageSparseMemoryRequirements(const VkDeviceImageMemoryRequirementsKHR* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2KHR* pSparseMemoryRequirements) const noexcept {
        fp_vkGetDeviceImageSparseMemoryRequirements(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    }
#endif
#if (defined(VK_VERSION_1_1))
    VkResult createSamplerYcbcrConversion(const VkSamplerYcbcrConversionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversionKHR* pYcbcrConversion) const noexcept {
        return fp_vkCreateSamplerYcbcrConversion(device, pCreateInfo, pAllocator, pYcbcrConversion);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void destroySamplerYcbcrConversion(VkSamplerYcbcrConversionKHR ycbcrConversion, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroySamplerYcbcrConversion(device, ycbcrConversion, pAllocator);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getDeviceQueue2(const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue) const noexcept {
        fp_vkGetDeviceQueue2(device, pQueueInfo, pQueue);
    }
#endif
#if (defined(VK_EXT_validation_cache))
    VkResult createValidationCacheEXT(const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache) const noexcept {
        return fp_vkCreateValidationCacheEXT(device, pCreateInfo, pAllocator, pValidationCache);
    }
#endif
#if (defined(VK_EXT_validation_cache))
    void destroyValidationCacheEXT(VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyValidationCacheEXT(device, validationCache, pAllocator);
    }
#endif
#if (defined(VK_EXT_validation_cache))
    VkResult getValidationCacheDataEXT(VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData) const noexcept {
        return fp_vkGetValidationCacheDataEXT(device, validationCache, pDataSize, pData);
    }
#endif
#if (defined(VK_EXT_validation_cache))
    VkResult mergeValidationCachesEXT(VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches) const noexcept {
        return fp_vkMergeValidationCachesEXT(device, dstCache, srcCacheCount, pSrcCaches);
    }
#endif
#if (defined(VK_VERSION_1_1))
    void getDescriptorSetLayoutSupport(const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupportKHR* pSupport) const noexcept {
        fp_vkGetDescriptorSetLayoutSupport(device, pCreateInfo, pSupport);
    }
#endif
#if (defined(VK_ANDROID_native_buffer))
    VkResult getSwapchainGrallocUsageANDROID(VkFormat format, VkImageUsageFlags imageUsage, int* grallocUsage) const noexcept {
        return fp_vkGetSwapchainGrallocUsageANDROID(device, format, imageUsage, grallocUsage);
    }
#endif
#if (defined(VK_ANDROID_native_buffer))
    VkResult getSwapchainGrallocUsage2ANDROID(VkFormat format, VkImageUsageFlags imageUsage, VkSwapchainImageUsageFlagsANDROID swapchainImageUsage, uint64_t* grallocConsumerUsage, uint64_t* grallocProducerUsage) const noexcept {
        return fp_vkGetSwapchainGrallocUsage2ANDROID(device, format, imageUsage, swapchainImageUsage, grallocConsumerUsage, grallocProducerUsage);
    }
#endif
#if (defined(VK_ANDROID_native_buffer))
    VkResult acquireImageANDROID(VkImage image, int nativeFenceFd, VkSemaphore semaphore, VkFence fence) const noexcept {
        return fp_vkAcquireImageANDROID(device, image, nativeFenceFd, semaphore, fence);
    }
#endif
#if (defined(VK_ANDROID_native_buffer))
    VkResult queueSignalReleaseImageANDROID(VkQueue queue, uint32_t waitSemaphoreCount, const VkSemaphore* pWaitSemaphores, VkImage image, int* pNativeFenceFd) const noexcept {
        return fp_vkQueueSignalReleaseImageANDROID(queue, waitSemaphoreCount, pWaitSemaphores, image, pNativeFenceFd);
    }
#endif
#if (defined(VK_AMD_shader_info))
    VkResult getShaderInfoAMD(VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo) const noexcept {
        return fp_vkGetShaderInfoAMD(device, pipeline, shaderStage, infoType, pInfoSize, pInfo);
    }
#endif
#if (defined(VK_AMD_display_native_hdr))
    void setLocalDimmingAMD(VkSwapchainKHR swapChain, VkBool32 localDimmingEnable) const noexcept {
        fp_vkSetLocalDimmingAMD(device, swapChain, localDimmingEnable);
    }
#endif
#if (defined(VK_KHR_calibrated_timestamps))
    VkResult getCalibratedTimestampsKHR(uint32_t timestampCount, const VkCalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation) const noexcept {
        return fp_vkGetCalibratedTimestampsKHR(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
    }
#endif
#if (defined(VK_EXT_debug_utils))
    VkResult setDebugUtilsObjectNameEXT(const VkDebugUtilsObjectNameInfoEXT* pNameInfo) const noexcept {
        return fp_vkSetDebugUtilsObjectNameEXT(device, pNameInfo);
    }
#endif
#if (defined(VK_EXT_debug_utils))
    VkResult setDebugUtilsObjectTagEXT(const VkDebugUtilsObjectTagInfoEXT* pTagInfo) const noexcept {
        return fp_vkSetDebugUtilsObjectTagEXT(device, pTagInfo);
    }
#endif
#if (defined(VK_EXT_debug_utils))
    void queueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) const noexcept {
        fp_vkQueueBeginDebugUtilsLabelEXT(queue, pLabelInfo);
    }
#endif
#if (defined(VK_EXT_debug_utils))
    void queueEndDebugUtilsLabelEXT(VkQueue queue) const noexcept {
        fp_vkQueueEndDebugUtilsLabelEXT(queue);
    }
#endif
#if (defined(VK_EXT_debug_utils))
    void queueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) const noexcept {
        fp_vkQueueInsertDebugUtilsLabelEXT(queue, pLabelInfo);
    }
#endif
#if (defined(VK_EXT_debug_utils))
    void cmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) const noexcept {
        fp_vkCmdBeginDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
    }
#endif
#if (defined(VK_EXT_debug_utils))
    void cmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) const noexcept {
        fp_vkCmdEndDebugUtilsLabelEXT(commandBuffer);
    }
#endif
#if (defined(VK_EXT_debug_utils))
    void cmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) const noexcept {
        fp_vkCmdInsertDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
    }
#endif
#if (defined(VK_EXT_external_memory_host))
    VkResult getMemoryHostPointerPropertiesEXT(VkExternalMemoryHandleTypeFlagBitsKHR handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) const noexcept {
        return fp_vkGetMemoryHostPointerPropertiesEXT(device, handleType, pHostPointer, pMemoryHostPointerProperties);
    }
#endif
#if (defined(VK_AMD_buffer_marker))
    void cmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) const noexcept {
        fp_vkCmdWriteBufferMarkerAMD(commandBuffer, pipelineStage, dstBuffer, dstOffset, marker);
    }
#endif
#if (defined(VK_VERSION_1_2))
    VkResult createRenderPass2(const VkRenderPassCreateInfo2KHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) const noexcept {
        return fp_vkCreateRenderPass2(device, pCreateInfo, pAllocator, pRenderPass);
    }
#endif
#if (defined(VK_VERSION_1_2))
    void cmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, const VkSubpassBeginInfoKHR* pSubpassBeginInfo) const noexcept {
        fp_vkCmdBeginRenderPass2(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    }
#endif
#if (defined(VK_VERSION_1_2))
    void cmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfoKHR* pSubpassBeginInfo, const VkSubpassEndInfoKHR* pSubpassEndInfo) const noexcept {
        fp_vkCmdNextSubpass2(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    }
#endif
#if (defined(VK_VERSION_1_2))
    void cmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfoKHR* pSubpassEndInfo) const noexcept {
        fp_vkCmdEndRenderPass2(commandBuffer, pSubpassEndInfo);
    }
#endif
#if (defined(VK_VERSION_1_2))
    VkResult getSemaphoreCounterValue(VkSemaphore semaphore, uint64_t* pValue) const noexcept {
        return fp_vkGetSemaphoreCounterValue(device, semaphore, pValue);
    }
#endif
#if (defined(VK_VERSION_1_2))
    VkResult waitSemaphores(const VkSemaphoreWaitInfoKHR* pWaitInfo, uint64_t timeout) const noexcept {
        return fp_vkWaitSemaphores(device, pWaitInfo, timeout);
    }
#endif
#if (defined(VK_VERSION_1_2))
    VkResult signalSemaphore(const VkSemaphoreSignalInfoKHR* pSignalInfo) const noexcept {
        return fp_vkSignalSemaphore(device, pSignalInfo);
    }
#endif
#if (defined(VK_ANDROID_external_memory_android_hardware_buffer))
    VkResult getAndroidHardwareBufferPropertiesANDROID(const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties) const noexcept {
        return fp_vkGetAndroidHardwareBufferPropertiesANDROID(device, buffer, pProperties);
    }
#endif
#if (defined(VK_ANDROID_external_memory_android_hardware_buffer))
    VkResult getMemoryAndroidHardwareBufferANDROID(const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer) const noexcept {
        return fp_vkGetMemoryAndroidHardwareBufferANDROID(device, pInfo, pBuffer);
    }
#endif
#if (defined(VK_VERSION_1_2))
    void cmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const noexcept {
        fp_vkCmdDrawIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    }
#endif
#if (defined(VK_VERSION_1_2))
    void cmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const noexcept {
        fp_vkCmdDrawIndexedIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    }
#endif
#if (defined(VK_NV_device_diagnostic_checkpoints))
    void cmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void* pCheckpointMarker) const noexcept {
        fp_vkCmdSetCheckpointNV(commandBuffer, pCheckpointMarker);
    }
#endif
#if (defined(VK_NV_device_diagnostic_checkpoints))
    void getQueueCheckpointDataNV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData) const noexcept {
        fp_vkGetQueueCheckpointDataNV(queue, pCheckpointDataCount, pCheckpointData);
    }
#endif
#if (defined(VK_EXT_transform_feedback))
    void cmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes) const noexcept {
        fp_vkCmdBindTransformFeedbackBuffersEXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes);
    }
#endif
#if (defined(VK_EXT_transform_feedback))
    void cmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) const noexcept {
        fp_vkCmdBeginTransformFeedbackEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
    }
#endif
#if (defined(VK_EXT_transform_feedback))
    void cmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) const noexcept {
        fp_vkCmdEndTransformFeedbackEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
    }
#endif
#if (defined(VK_EXT_transform_feedback))
    void cmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index) const noexcept {
        fp_vkCmdBeginQueryIndexedEXT(commandBuffer, queryPool, query, flags, index);
    }
#endif
#if (defined(VK_EXT_transform_feedback))
    void cmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index) const noexcept {
        fp_vkCmdEndQueryIndexedEXT(commandBuffer, queryPool, query, index);
    }
#endif
#if (defined(VK_EXT_transform_feedback))
    void cmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) const noexcept {
        fp_vkCmdDrawIndirectByteCountEXT(commandBuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride);
    }
#endif
#if (defined(VK_NV_scissor_exclusive))
    void cmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors) const noexcept {
        fp_vkCmdSetExclusiveScissorNV(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissors);
    }
#endif
#if ((defined(VK_NV_scissor_exclusive))) && VK_HEADER_VERSION >= 241
    void cmdSetExclusiveScissorEnableNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables) const noexcept {
        fp_vkCmdSetExclusiveScissorEnableNV(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissorEnables);
    }
#endif
#if (defined(VK_NV_shading_rate_image))
    void cmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) const noexcept {
        fp_vkCmdBindShadingRateImageNV(commandBuffer, imageView, imageLayout);
    }
#endif
#if (defined(VK_NV_shading_rate_image))
    void cmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes) const noexcept {
        fp_vkCmdSetViewportShadingRatePaletteNV(commandBuffer, firstViewport, viewportCount, pShadingRatePalettes);
    }
#endif
#if (defined(VK_NV_shading_rate_image))
    void cmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders) const noexcept {
        fp_vkCmdSetCoarseSampleOrderNV(commandBuffer, sampleOrderType, customSampleOrderCount, pCustomSampleOrders);
    }
#endif
#if (defined(VK_NV_mesh_shader))
    void cmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask) const noexcept {
        fp_vkCmdDrawMeshTasksNV(commandBuffer, taskCount, firstTask);
    }
#endif
#if (defined(VK_NV_mesh_shader))
    void cmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const noexcept {
        fp_vkCmdDrawMeshTasksIndirectNV(commandBuffer, buffer, offset, drawCount, stride);
    }
#endif
#if (defined(VK_NV_mesh_shader))
    void cmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const noexcept {
        fp_vkCmdDrawMeshTasksIndirectCountNV(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    }
#endif
#if (defined(VK_EXT_mesh_shader))
    void cmdDrawMeshTasksEXT(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const noexcept {
        fp_vkCmdDrawMeshTasksEXT(commandBuffer, groupCountX, groupCountY, groupCountZ);
    }
#endif
#if (defined(VK_EXT_mesh_shader))
    void cmdDrawMeshTasksIndirectEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const noexcept {
        fp_vkCmdDrawMeshTasksIndirectEXT(commandBuffer, buffer, offset, drawCount, stride);
    }
#endif
#if (defined(VK_EXT_mesh_shader))
    void cmdDrawMeshTasksIndirectCountEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const noexcept {
        fp_vkCmdDrawMeshTasksIndirectCountEXT(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    }
#endif
#if (defined(VK_NV_ray_tracing))
    VkResult compileDeferredNV(VkPipeline pipeline, uint32_t shader) const noexcept {
        return fp_vkCompileDeferredNV(device, pipeline, shader);
    }
#endif
#if (defined(VK_NV_ray_tracing))
    VkResult createAccelerationStructureNV(const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure) const noexcept {
        return fp_vkCreateAccelerationStructureNV(device, pCreateInfo, pAllocator, pAccelerationStructure);
    }
#endif
#if (defined(VK_HUAWEI_invocation_mask))
    void cmdBindInvocationMaskHUAWEI(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) const noexcept {
        fp_vkCmdBindInvocationMaskHUAWEI(commandBuffer, imageView, imageLayout);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    void destroyAccelerationStructureKHR(VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyAccelerationStructureKHR(device, accelerationStructure, pAllocator);
    }
#endif
#if (defined(VK_NV_ray_tracing))
    void destroyAccelerationStructureNV(VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyAccelerationStructureNV(device, accelerationStructure, pAllocator);
    }
#endif
#if (defined(VK_NV_ray_tracing))
    void getAccelerationStructureMemoryRequirementsNV(const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) const noexcept {
        fp_vkGetAccelerationStructureMemoryRequirementsNV(device, pInfo, pMemoryRequirements);
    }
#endif
#if (defined(VK_NV_ray_tracing))
    VkResult bindAccelerationStructureMemoryNV(uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos) const noexcept {
        return fp_vkBindAccelerationStructureMemoryNV(device, bindInfoCount, pBindInfos);
    }
#endif
#if (defined(VK_NV_ray_tracing))
    void cmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeNV mode) const noexcept {
        fp_vkCmdCopyAccelerationStructureNV(commandBuffer, dst, src, mode);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    void cmdCopyAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo) const noexcept {
        fp_vkCmdCopyAccelerationStructureKHR(commandBuffer, pInfo);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    VkResult copyAccelerationStructureKHR(VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo) const noexcept {
        return fp_vkCopyAccelerationStructureKHR(device, deferredOperation, pInfo);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    void cmdCopyAccelerationStructureToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) const noexcept {
        fp_vkCmdCopyAccelerationStructureToMemoryKHR(commandBuffer, pInfo);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    VkResult copyAccelerationStructureToMemoryKHR(VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) const noexcept {
        return fp_vkCopyAccelerationStructureToMemoryKHR(device, deferredOperation, pInfo);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    void cmdCopyMemoryToAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) const noexcept {
        fp_vkCmdCopyMemoryToAccelerationStructureKHR(commandBuffer, pInfo);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    VkResult copyMemoryToAccelerationStructureKHR(VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) const noexcept {
        return fp_vkCopyMemoryToAccelerationStructureKHR(device, deferredOperation, pInfo);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    void cmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) const noexcept {
        fp_vkCmdWriteAccelerationStructuresPropertiesKHR(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
    }
#endif
#if (defined(VK_NV_ray_tracing))
    void cmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) const noexcept {
        fp_vkCmdWriteAccelerationStructuresPropertiesNV(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
    }
#endif
#if (defined(VK_NV_ray_tracing))
    void cmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset) const noexcept {
        fp_vkCmdBuildAccelerationStructureNV(commandBuffer, pInfo, instanceData, instanceOffset, update, dst, src, scratch, scratchOffset);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    VkResult writeAccelerationStructuresPropertiesKHR(uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, size_t dataSize, void* pData, size_t stride) const noexcept {
        return fp_vkWriteAccelerationStructuresPropertiesKHR(device, accelerationStructureCount, pAccelerationStructures, queryType, dataSize, pData, stride);
    }
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
    void cmdTraceRaysKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) const noexcept {
        fp_vkCmdTraceRaysKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, width, height, depth);
    }
#endif
#if (defined(VK_NV_ray_tracing))
    void cmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) const noexcept {
        fp_vkCmdTraceRaysNV(commandBuffer, raygenShaderBindingTableBuffer, raygenShaderBindingOffset, missShaderBindingTableBuffer, missShaderBindingOffset, missShaderBindingStride, hitShaderBindingTableBuffer, hitShaderBindingOffset, hitShaderBindingStride, callableShaderBindingTableBuffer, callableShaderBindingOffset, callableShaderBindingStride, width, height, depth);
    }
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
    VkResult getRayTracingShaderGroupHandlesKHR(VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) const noexcept {
        return fp_vkGetRayTracingShaderGroupHandlesKHR(device, pipeline, firstGroup, groupCount, dataSize, pData);
    }
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
    VkResult getRayTracingCaptureReplayShaderGroupHandlesKHR(VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) const noexcept {
        return fp_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR(device, pipeline, firstGroup, groupCount, dataSize, pData);
    }
#endif
#if (defined(VK_NV_ray_tracing))
    VkResult getAccelerationStructureHandleNV(VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData) const noexcept {
        return fp_vkGetAccelerationStructureHandleNV(device, accelerationStructure, dataSize, pData);
    }
#endif
#if (defined(VK_NV_ray_tracing))
    VkResult createRayTracingPipelinesNV(VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) const noexcept {
        return fp_vkCreateRayTracingPipelinesNV(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    }
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
    VkResult createRayTracingPipelinesKHR(VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) const noexcept {
        return fp_vkCreateRayTracingPipelinesKHR(device, deferredOperation, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    }
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
    void cmdTraceRaysIndirectKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress) const noexcept {
        fp_vkCmdTraceRaysIndirectKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, indirectDeviceAddress);
    }
#endif
#if (defined(VK_KHR_ray_tracing_maintenance1))
    void cmdTraceRaysIndirect2KHR(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress) const noexcept {
        fp_vkCmdTraceRaysIndirect2KHR(commandBuffer, indirectDeviceAddress);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    void getDeviceAccelerationStructureCompatibilityKHR(const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) const noexcept {
        fp_vkGetDeviceAccelerationStructureCompatibilityKHR(device, pVersionInfo, pCompatibility);
    }
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
    VkDeviceSize getRayTracingShaderGroupStackSizeKHR(VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader) const noexcept {
        return fp_vkGetRayTracingShaderGroupStackSizeKHR(device, pipeline, group, groupShader);
    }
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
    void cmdSetRayTracingPipelineStackSizeKHR(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize) const noexcept {
        fp_vkCmdSetRayTracingPipelineStackSizeKHR(commandBuffer, pipelineStackSize);
    }
#endif
#if (defined(VK_EXT_full_screen_exclusive)) || (defined(VK_EXT_full_screen_exclusive))
    VkResult getDeviceGroupSurfacePresentModes2EXT(const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes) const noexcept {
        return fp_vkGetDeviceGroupSurfacePresentModes2EXT(device, pSurfaceInfo, pModes);
    }
#endif
#if (defined(VK_EXT_full_screen_exclusive))
    VkResult acquireFullScreenExclusiveModeEXT(VkSwapchainKHR swapchain) const noexcept {
        return fp_vkAcquireFullScreenExclusiveModeEXT(device, swapchain);
    }
#endif
#if (defined(VK_EXT_full_screen_exclusive))
    VkResult releaseFullScreenExclusiveModeEXT(VkSwapchainKHR swapchain) const noexcept {
        return fp_vkReleaseFullScreenExclusiveModeEXT(device, swapchain);
    }
#endif
#if (defined(VK_KHR_performance_query))
    VkResult acquireProfilingLockKHR(const VkAcquireProfilingLockInfoKHR* pInfo) const noexcept {
        return fp_vkAcquireProfilingLockKHR(device, pInfo);
    }
#endif
#if (defined(VK_KHR_performance_query))
    void releaseProfilingLockKHR() const noexcept {
        fp_vkReleaseProfilingLockKHR(device);
    }
#endif
#if (defined(VK_EXT_image_drm_format_modifier))
    VkResult getImageDrmFormatModifierPropertiesEXT(VkImage image, VkImageDrmFormatModifierPropertiesEXT* pProperties) const noexcept {
        return fp_vkGetImageDrmFormatModifierPropertiesEXT(device, image, pProperties);
    }
#endif
#if (defined(VK_VERSION_1_2))
    uint64_t getBufferOpaqueCaptureAddress(const VkBufferDeviceAddressInfoEXT* pInfo) const noexcept {
        return fp_vkGetBufferOpaqueCaptureAddress(device, pInfo);
    }
#endif
#if (defined(VK_VERSION_1_2))
    VkDeviceAddress getBufferDeviceAddress(const VkBufferDeviceAddressInfoEXT* pInfo) const noexcept {
        return fp_vkGetBufferDeviceAddress(device, pInfo);
    }
#endif
#if (defined(VK_INTEL_performance_query))
    VkResult initializePerformanceApiINTEL(const VkInitializePerformanceApiInfoINTEL* pInitializeInfo) const noexcept {
        return fp_vkInitializePerformanceApiINTEL(device, pInitializeInfo);
    }
#endif
#if (defined(VK_INTEL_performance_query))
    void uninitializePerformanceApiINTEL() const noexcept {
        fp_vkUninitializePerformanceApiINTEL(device);
    }
#endif
#if (defined(VK_INTEL_performance_query))
    VkResult cmdSetPerformanceMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceMarkerInfoINTEL* pMarkerInfo) const noexcept {
        return fp_vkCmdSetPerformanceMarkerINTEL(commandBuffer, pMarkerInfo);
    }
#endif
#if (defined(VK_INTEL_performance_query))
    VkResult cmdSetPerformanceStreamMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceStreamMarkerInfoINTEL* pMarkerInfo) const noexcept {
        return fp_vkCmdSetPerformanceStreamMarkerINTEL(commandBuffer, pMarkerInfo);
    }
#endif
#if (defined(VK_INTEL_performance_query))
    VkResult cmdSetPerformanceOverrideINTEL(VkCommandBuffer commandBuffer, const VkPerformanceOverrideInfoINTEL* pOverrideInfo) const noexcept {
        return fp_vkCmdSetPerformanceOverrideINTEL(commandBuffer, pOverrideInfo);
    }
#endif
#if (defined(VK_INTEL_performance_query))
    VkResult acquirePerformanceConfigurationINTEL(const VkPerformanceConfigurationAcquireInfoINTEL* pAcquireInfo, VkPerformanceConfigurationINTEL* pConfiguration) const noexcept {
        return fp_vkAcquirePerformanceConfigurationINTEL(device, pAcquireInfo, pConfiguration);
    }
#endif
#if (defined(VK_INTEL_performance_query))
    VkResult releasePerformanceConfigurationINTEL(VkPerformanceConfigurationINTEL configuration) const noexcept {
        return fp_vkReleasePerformanceConfigurationINTEL(device, configuration);
    }
#endif
#if (defined(VK_INTEL_performance_query))
    VkResult queueSetPerformanceConfigurationINTEL(VkQueue queue, VkPerformanceConfigurationINTEL configuration) const noexcept {
        return fp_vkQueueSetPerformanceConfigurationINTEL(queue, configuration);
    }
#endif
#if (defined(VK_INTEL_performance_query))
    VkResult getPerformanceParameterINTEL(VkPerformanceParameterTypeINTEL parameter, VkPerformanceValueINTEL* pValue) const noexcept {
        return fp_vkGetPerformanceParameterINTEL(device, parameter, pValue);
    }
#endif
#if (defined(VK_VERSION_1_2))
    uint64_t getDeviceMemoryOpaqueCaptureAddress(const VkDeviceMemoryOpaqueCaptureAddressInfoKHR* pInfo) const noexcept {
        return fp_vkGetDeviceMemoryOpaqueCaptureAddress(device, pInfo);
    }
#endif
#if (defined(VK_KHR_pipeline_executable_properties))
    VkResult getPipelineExecutablePropertiesKHR(const VkPipelineInfoKHR* pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties) const noexcept {
        return fp_vkGetPipelineExecutablePropertiesKHR(device, pPipelineInfo, pExecutableCount, pProperties);
    }
#endif
#if (defined(VK_KHR_pipeline_executable_properties))
    VkResult getPipelineExecutableStatisticsKHR(const VkPipelineExecutableInfoKHR* pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics) const noexcept {
        return fp_vkGetPipelineExecutableStatisticsKHR(device, pExecutableInfo, pStatisticCount, pStatistics);
    }
#endif
#if (defined(VK_KHR_pipeline_executable_properties))
    VkResult getPipelineExecutableInternalRepresentationsKHR(const VkPipelineExecutableInfoKHR* pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations) const noexcept {
        return fp_vkGetPipelineExecutableInternalRepresentationsKHR(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations);
    }
#endif
#if (defined(VK_EXT_line_rasterization))
    void cmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) const noexcept {
        fp_vkCmdSetLineStippleEXT(commandBuffer, lineStippleFactor, lineStipplePattern);
    }
#endif
#if (defined(VKSC_VERSION_1_0))
    VkResult getFaultData(VkFaultQueryBehavior faultQueryBehavior, VkBool32* pUnrecordedFaults, uint32_t* pFaultCount, VkFaultData* pFaults) const noexcept {
        return fp_vkGetFaultData(device, faultQueryBehavior, pUnrecordedFaults, pFaultCount, pFaults);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    VkResult createAccelerationStructureKHR(const VkAccelerationStructureCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureKHR* pAccelerationStructure) const noexcept {
        return fp_vkCreateAccelerationStructureKHR(device, pCreateInfo, pAllocator, pAccelerationStructure);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    void cmdBuildAccelerationStructuresKHR(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) const noexcept {
        fp_vkCmdBuildAccelerationStructuresKHR(commandBuffer, infoCount, pInfos, ppBuildRangeInfos);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    void cmdBuildAccelerationStructuresIndirectKHR(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress* pIndirectDeviceAddresses, const uint32_t* pIndirectStrides, const uint32_t* const* ppMaxPrimitiveCounts) const noexcept {
        fp_vkCmdBuildAccelerationStructuresIndirectKHR(commandBuffer, infoCount, pInfos, pIndirectDeviceAddresses, pIndirectStrides, ppMaxPrimitiveCounts);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    VkResult buildAccelerationStructuresKHR(VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) const noexcept {
        return fp_vkBuildAccelerationStructuresKHR(device, deferredOperation, infoCount, pInfos, ppBuildRangeInfos);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    VkDeviceAddress getAccelerationStructureDeviceAddressKHR(const VkAccelerationStructureDeviceAddressInfoKHR* pInfo) const noexcept {
        return fp_vkGetAccelerationStructureDeviceAddressKHR(device, pInfo);
    }
#endif
#if (defined(VK_KHR_deferred_host_operations))
    VkResult createDeferredOperationKHR(const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation) const noexcept {
        return fp_vkCreateDeferredOperationKHR(device, pAllocator, pDeferredOperation);
    }
#endif
#if (defined(VK_KHR_deferred_host_operations))
    void destroyDeferredOperationKHR(VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyDeferredOperationKHR(device, operation, pAllocator);
    }
#endif
#if (defined(VK_KHR_deferred_host_operations))
    uint32_t getDeferredOperationMaxConcurrencyKHR(VkDeferredOperationKHR operation) const noexcept {
        return fp_vkGetDeferredOperationMaxConcurrencyKHR(device, operation);
    }
#endif
#if (defined(VK_KHR_deferred_host_operations))
    VkResult getDeferredOperationResultKHR(VkDeferredOperationKHR operation) const noexcept {
        return fp_vkGetDeferredOperationResultKHR(device, operation);
    }
#endif
#if (defined(VK_KHR_deferred_host_operations))
    VkResult deferredOperationJoinKHR(VkDeferredOperationKHR operation) const noexcept {
        return fp_vkDeferredOperationJoinKHR(device, operation);
    }
#endif
#if (defined(VK_NV_device_generated_commands_compute))
    void getPipelineIndirectMemoryRequirementsNV(const VkComputePipelineCreateInfo* pCreateInfo, VkMemoryRequirements2KHR* pMemoryRequirements) const noexcept {
        fp_vkGetPipelineIndirectMemoryRequirementsNV(device, pCreateInfo, pMemoryRequirements);
    }
#endif
#if (defined(VK_NV_device_generated_commands_compute))
    VkDeviceAddress getPipelineIndirectDeviceAddressNV(const VkPipelineIndirectDeviceAddressInfoNV* pInfo) const noexcept {
        return fp_vkGetPipelineIndirectDeviceAddressNV(device, pInfo);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) const noexcept {
        fp_vkCmdSetCullMode(commandBuffer, cullMode);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace) const noexcept {
        fp_vkCmdSetFrontFace(commandBuffer, frontFace);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) const noexcept {
        fp_vkCmdSetPrimitiveTopology(commandBuffer, primitiveTopology);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) const noexcept {
        fp_vkCmdSetViewportWithCount(commandBuffer, viewportCount, pViewports);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) const noexcept {
        fp_vkCmdSetScissorWithCount(commandBuffer, scissorCount, pScissors);
    }
#endif
#if (defined(VK_KHR_maintenance5))
    void cmdBindIndexBuffer2KHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, VkIndexType indexType) const noexcept {
        fp_vkCmdBindIndexBuffer2KHR(commandBuffer, buffer, offset, size, indexType);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) const noexcept {
        fp_vkCmdBindVertexBuffers2(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) const noexcept {
        fp_vkCmdSetDepthTestEnable(commandBuffer, depthTestEnable);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) const noexcept {
        fp_vkCmdSetDepthWriteEnable(commandBuffer, depthWriteEnable);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) const noexcept {
        fp_vkCmdSetDepthCompareOp(commandBuffer, depthCompareOp);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) const noexcept {
        fp_vkCmdSetDepthBoundsTestEnable(commandBuffer, depthBoundsTestEnable);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) const noexcept {
        fp_vkCmdSetStencilTestEnable(commandBuffer, stencilTestEnable);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) const noexcept {
        fp_vkCmdSetStencilOp(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
    void cmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints) const noexcept {
        fp_vkCmdSetPatchControlPointsEXT(commandBuffer, patchControlPoints);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) const noexcept {
        fp_vkCmdSetRasterizerDiscardEnable(commandBuffer, rasterizerDiscardEnable);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) const noexcept {
        fp_vkCmdSetDepthBiasEnable(commandBuffer, depthBiasEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
    void cmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp) const noexcept {
        fp_vkCmdSetLogicOpEXT(commandBuffer, logicOp);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) const noexcept {
        fp_vkCmdSetPrimitiveRestartEnable(commandBuffer, primitiveRestartEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOriginKHR domainOrigin) const noexcept {
        fp_vkCmdSetTessellationDomainOriginEXT(commandBuffer, domainOrigin);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable) const noexcept {
        fp_vkCmdSetDepthClampEnableEXT(commandBuffer, depthClampEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode) const noexcept {
        fp_vkCmdSetPolygonModeEXT(commandBuffer, polygonMode);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits rasterizationSamples) const noexcept {
        fp_vkCmdSetRasterizationSamplesEXT(commandBuffer, rasterizationSamples);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits samples, const VkSampleMask* pSampleMask) const noexcept {
        fp_vkCmdSetSampleMaskEXT(commandBuffer, samples, pSampleMask);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable) const noexcept {
        fp_vkCmdSetAlphaToCoverageEnableEXT(commandBuffer, alphaToCoverageEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable) const noexcept {
        fp_vkCmdSetAlphaToOneEnableEXT(commandBuffer, alphaToOneEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable) const noexcept {
        fp_vkCmdSetLogicOpEnableEXT(commandBuffer, logicOpEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables) const noexcept {
        fp_vkCmdSetColorBlendEnableEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations) const noexcept {
        fp_vkCmdSetColorBlendEquationEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks) const noexcept {
        fp_vkCmdSetColorWriteMaskEXT(commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream) const noexcept {
        fp_vkCmdSetRasterizationStreamEXT(commandBuffer, rasterizationStream);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode) const noexcept {
        fp_vkCmdSetConservativeRasterizationModeEXT(commandBuffer, conservativeRasterizationMode);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize) const noexcept {
        fp_vkCmdSetExtraPrimitiveOverestimationSizeEXT(commandBuffer, extraPrimitiveOverestimationSize);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable) const noexcept {
        fp_vkCmdSetDepthClipEnableEXT(commandBuffer, depthClipEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable) const noexcept {
        fp_vkCmdSetSampleLocationsEnableEXT(commandBuffer, sampleLocationsEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced) const noexcept {
        fp_vkCmdSetColorBlendAdvancedEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode) const noexcept {
        fp_vkCmdSetProvokingVertexModeEXT(commandBuffer, provokingVertexMode);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode) const noexcept {
        fp_vkCmdSetLineRasterizationModeEXT(commandBuffer, lineRasterizationMode);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable) const noexcept {
        fp_vkCmdSetLineStippleEnableEXT(commandBuffer, stippledLineEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne) const noexcept {
        fp_vkCmdSetDepthClipNegativeOneToOneEXT(commandBuffer, negativeOneToOne);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable) const noexcept {
        fp_vkCmdSetViewportWScalingEnableNV(commandBuffer, viewportWScalingEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles) const noexcept {
        fp_vkCmdSetViewportSwizzleNV(commandBuffer, firstViewport, viewportCount, pViewportSwizzles);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable) const noexcept {
        fp_vkCmdSetCoverageToColorEnableNV(commandBuffer, coverageToColorEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation) const noexcept {
        fp_vkCmdSetCoverageToColorLocationNV(commandBuffer, coverageToColorLocation);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode) const noexcept {
        fp_vkCmdSetCoverageModulationModeNV(commandBuffer, coverageModulationMode);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable) const noexcept {
        fp_vkCmdSetCoverageModulationTableEnableNV(commandBuffer, coverageModulationTableEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable) const noexcept {
        fp_vkCmdSetCoverageModulationTableNV(commandBuffer, coverageModulationTableCount, pCoverageModulationTable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable) const noexcept {
        fp_vkCmdSetShadingRateImageEnableNV(commandBuffer, shadingRateImageEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode) const noexcept {
        fp_vkCmdSetCoverageReductionModeNV(commandBuffer, coverageReductionMode);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    void cmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable) const noexcept {
        fp_vkCmdSetRepresentativeFragmentTestEnableNV(commandBuffer, representativeFragmentTestEnable);
    }
#endif
#if (defined(VK_VERSION_1_3))
    VkResult createPrivateDataSlot(const VkPrivateDataSlotCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlotEXT* pPrivateDataSlot) const noexcept {
        return fp_vkCreatePrivateDataSlot(device, pCreateInfo, pAllocator, pPrivateDataSlot);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void destroyPrivateDataSlot(VkPrivateDataSlotEXT privateDataSlot, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyPrivateDataSlot(device, privateDataSlot, pAllocator);
    }
#endif
#if (defined(VK_VERSION_1_3))
    VkResult setPrivateData(VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlotEXT privateDataSlot, uint64_t data) const noexcept {
        return fp_vkSetPrivateData(device, objectType, objectHandle, privateDataSlot, data);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void getPrivateData(VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlotEXT privateDataSlot, uint64_t* pData) const noexcept {
        fp_vkGetPrivateData(device, objectType, objectHandle, privateDataSlot, pData);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2KHR* pCopyBufferInfo) const noexcept {
        fp_vkCmdCopyBuffer2(commandBuffer, pCopyBufferInfo);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2KHR* pCopyImageInfo) const noexcept {
        fp_vkCmdCopyImage2(commandBuffer, pCopyImageInfo);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2KHR* pBlitImageInfo) const noexcept {
        fp_vkCmdBlitImage2(commandBuffer, pBlitImageInfo);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2KHR* pCopyBufferToImageInfo) const noexcept {
        fp_vkCmdCopyBufferToImage2(commandBuffer, pCopyBufferToImageInfo);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2KHR* pCopyImageToBufferInfo) const noexcept {
        fp_vkCmdCopyImageToBuffer2(commandBuffer, pCopyImageToBufferInfo);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2KHR* pResolveImageInfo) const noexcept {
        fp_vkCmdResolveImage2(commandBuffer, pResolveImageInfo);
    }
#endif
#if (defined(VK_KHR_object_refresh))
    void cmdRefreshObjectsKHR(VkCommandBuffer commandBuffer, const VkRefreshObjectListKHR* pRefreshObjects) const noexcept {
        fp_vkCmdRefreshObjectsKHR(commandBuffer, pRefreshObjects);
    }
#endif
#if (defined(VK_KHR_fragment_shading_rate))
    void cmdSetFragmentShadingRateKHR(VkCommandBuffer commandBuffer, const VkExtent2D* pFragmentSize, const VkFragmentShadingRateCombinerOpKHR combinerOps[2]) const noexcept {
        fp_vkCmdSetFragmentShadingRateKHR(commandBuffer, pFragmentSize, combinerOps);
    }
#endif
#if (defined(VK_NV_fragment_shading_rate_enums))
    void cmdSetFragmentShadingRateEnumNV(VkCommandBuffer commandBuffer, VkFragmentShadingRateNV shadingRate, const VkFragmentShadingRateCombinerOpKHR combinerOps[2]) const noexcept {
        fp_vkCmdSetFragmentShadingRateEnumNV(commandBuffer, shadingRate, combinerOps);
    }
#endif
#if (defined(VK_KHR_acceleration_structure))
    void getAccelerationStructureBuildSizesKHR(VkAccelerationStructureBuildTypeKHR buildType, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo) const noexcept {
        fp_vkGetAccelerationStructureBuildSizesKHR(device, buildType, pBuildInfo, pMaxPrimitiveCounts, pSizeInfo);
    }
#endif
#if (defined(VK_EXT_vertex_input_dynamic_state)) || (defined(VK_EXT_shader_object))
    void cmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) const noexcept {
        fp_vkCmdSetVertexInputEXT(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions);
    }
#endif
#if (defined(VK_EXT_color_write_enable))
    void cmdSetColorWriteEnableEXT(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkBool32* pColorWriteEnables) const noexcept {
        fp_vkCmdSetColorWriteEnableEXT(commandBuffer, attachmentCount, pColorWriteEnables);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdSetEvent2(VkCommandBuffer commandBuffer, VkEvent event, const VkDependencyInfoKHR* pDependencyInfo) const noexcept {
        fp_vkCmdSetEvent2(commandBuffer, event, pDependencyInfo);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdResetEvent2(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags2KHR stageMask) const noexcept {
        fp_vkCmdResetEvent2(commandBuffer, event, stageMask);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdWaitEvents2(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, const VkDependencyInfoKHR* pDependencyInfos) const noexcept {
        fp_vkCmdWaitEvents2(commandBuffer, eventCount, pEvents, pDependencyInfos);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdPipelineBarrier2(VkCommandBuffer commandBuffer, const VkDependencyInfoKHR* pDependencyInfo) const noexcept {
        fp_vkCmdPipelineBarrier2(commandBuffer, pDependencyInfo);
    }
#endif
#if (defined(VK_VERSION_1_3))
    VkResult queueSubmit2(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2KHR* pSubmits, VkFence fence) const noexcept {
        return fp_vkQueueSubmit2(queue, submitCount, pSubmits, fence);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdWriteTimestamp2(VkCommandBuffer commandBuffer, VkPipelineStageFlags2KHR stage, VkQueryPool queryPool, uint32_t query) const noexcept {
        fp_vkCmdWriteTimestamp2(commandBuffer, stage, queryPool, query);
    }
#endif
#if (defined(VK_KHR_synchronization2))
    void cmdWriteBufferMarker2AMD(VkCommandBuffer commandBuffer, VkPipelineStageFlags2KHR stage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) const noexcept {
        fp_vkCmdWriteBufferMarker2AMD(commandBuffer, stage, dstBuffer, dstOffset, marker);
    }
#endif
#if (defined(VK_KHR_synchronization2))
    void getQueueCheckpointData2NV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData) const noexcept {
        fp_vkGetQueueCheckpointData2NV(queue, pCheckpointDataCount, pCheckpointData);
    }
#endif
#if (defined(VK_EXT_host_image_copy))
    VkResult copyMemoryToImageEXT(const VkCopyMemoryToImageInfoEXT* pCopyMemoryToImageInfo) const noexcept {
        return fp_vkCopyMemoryToImageEXT(device, pCopyMemoryToImageInfo);
    }
#endif
#if (defined(VK_EXT_host_image_copy))
    VkResult copyImageToMemoryEXT(const VkCopyImageToMemoryInfoEXT* pCopyImageToMemoryInfo) const noexcept {
        return fp_vkCopyImageToMemoryEXT(device, pCopyImageToMemoryInfo);
    }
#endif
#if (defined(VK_EXT_host_image_copy))
    VkResult copyImageToImageEXT(const VkCopyImageToImageInfoEXT* pCopyImageToImageInfo) const noexcept {
        return fp_vkCopyImageToImageEXT(device, pCopyImageToImageInfo);
    }
#endif
#if (defined(VK_EXT_host_image_copy))
    VkResult transitionImageLayoutEXT(uint32_t transitionCount, const VkHostImageLayoutTransitionInfoEXT* pTransitions) const noexcept {
        return fp_vkTransitionImageLayoutEXT(device, transitionCount, pTransitions);
    }
#endif
#if (defined(VKSC_VERSION_1_0))
    void getCommandPoolMemoryConsumption(VkCommandPool commandPool, VkCommandBuffer commandBuffer, VkCommandPoolMemoryConsumption* pConsumption) const noexcept {
        fp_vkGetCommandPoolMemoryConsumption(device, commandPool, commandBuffer, pConsumption);
    }
#endif
#if (defined(VK_KHR_video_queue))
    VkResult createVideoSessionKHR(const VkVideoSessionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionKHR* pVideoSession) const noexcept {
        return fp_vkCreateVideoSessionKHR(device, pCreateInfo, pAllocator, pVideoSession);
    }
#endif
#if (defined(VK_KHR_video_queue))
    void destroyVideoSessionKHR(VkVideoSessionKHR videoSession, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyVideoSessionKHR(device, videoSession, pAllocator);
    }
#endif
#if (defined(VK_KHR_video_queue))
    VkResult createVideoSessionParametersKHR(const VkVideoSessionParametersCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionParametersKHR* pVideoSessionParameters) const noexcept {
        return fp_vkCreateVideoSessionParametersKHR(device, pCreateInfo, pAllocator, pVideoSessionParameters);
    }
#endif
#if (defined(VK_KHR_video_queue))
    VkResult updateVideoSessionParametersKHR(VkVideoSessionParametersKHR videoSessionParameters, const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo) const noexcept {
        return fp_vkUpdateVideoSessionParametersKHR(device, videoSessionParameters, pUpdateInfo);
    }
#endif
#if (defined(VK_KHR_video_encode_queue))
    VkResult getEncodedVideoSessionParametersKHR(const VkVideoEncodeSessionParametersGetInfoKHR* pVideoSessionParametersInfo, VkVideoEncodeSessionParametersFeedbackInfoKHR* pFeedbackInfo, size_t* pDataSize, void* pData) const noexcept {
        return fp_vkGetEncodedVideoSessionParametersKHR(device, pVideoSessionParametersInfo, pFeedbackInfo, pDataSize, pData);
    }
#endif
#if (defined(VK_KHR_video_queue))
    void destroyVideoSessionParametersKHR(VkVideoSessionParametersKHR videoSessionParameters, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyVideoSessionParametersKHR(device, videoSessionParameters, pAllocator);
    }
#endif
#if (defined(VK_KHR_video_queue))
    VkResult getVideoSessionMemoryRequirementsKHR(VkVideoSessionKHR videoSession, uint32_t* pMemoryRequirementsCount, VkVideoSessionMemoryRequirementsKHR* pMemoryRequirements) const noexcept {
        return fp_vkGetVideoSessionMemoryRequirementsKHR(device, videoSession, pMemoryRequirementsCount, pMemoryRequirements);
    }
#endif
#if (defined(VK_KHR_video_queue))
    VkResult bindVideoSessionMemoryKHR(VkVideoSessionKHR videoSession, uint32_t bindSessionMemoryInfoCount, const VkBindVideoSessionMemoryInfoKHR* pBindSessionMemoryInfos) const noexcept {
        return fp_vkBindVideoSessionMemoryKHR(device, videoSession, bindSessionMemoryInfoCount, pBindSessionMemoryInfos);
    }
#endif
#if (defined(VK_KHR_video_decode_queue))
    void cmdDecodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoDecodeInfoKHR* pDecodeInfo) const noexcept {
        fp_vkCmdDecodeVideoKHR(commandBuffer, pDecodeInfo);
    }
#endif
#if (defined(VK_KHR_video_queue))
    void cmdBeginVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoBeginCodingInfoKHR* pBeginInfo) const noexcept {
        fp_vkCmdBeginVideoCodingKHR(commandBuffer, pBeginInfo);
    }
#endif
#if (defined(VK_KHR_video_queue))
    void cmdControlVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoCodingControlInfoKHR* pCodingControlInfo) const noexcept {
        fp_vkCmdControlVideoCodingKHR(commandBuffer, pCodingControlInfo);
    }
#endif
#if (defined(VK_KHR_video_queue))
    void cmdEndVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoEndCodingInfoKHR* pEndCodingInfo) const noexcept {
        fp_vkCmdEndVideoCodingKHR(commandBuffer, pEndCodingInfo);
    }
#endif
#if (defined(VK_KHR_video_encode_queue))
    void cmdEncodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoEncodeInfoKHR* pEncodeInfo) const noexcept {
        fp_vkCmdEncodeVideoKHR(commandBuffer, pEncodeInfo);
    }
#endif
#if (defined(VK_NV_memory_decompression))
    void cmdDecompressMemoryNV(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions) const noexcept {
        fp_vkCmdDecompressMemoryNV(commandBuffer, decompressRegionCount, pDecompressMemoryRegions);
    }
#endif
#if (defined(VK_NV_memory_decompression))
    void cmdDecompressMemoryIndirectCountNV(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride) const noexcept {
        fp_vkCmdDecompressMemoryIndirectCountNV(commandBuffer, indirectCommandsAddress, indirectCommandsCountAddress, stride);
    }
#endif
#if (defined(VK_EXT_descriptor_buffer))
    void getDescriptorSetLayoutSizeEXT(VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes) const noexcept {
        fp_vkGetDescriptorSetLayoutSizeEXT(device, layout, pLayoutSizeInBytes);
    }
#endif
#if (defined(VK_EXT_descriptor_buffer))
    void getDescriptorSetLayoutBindingOffsetEXT(VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset) const noexcept {
        fp_vkGetDescriptorSetLayoutBindingOffsetEXT(device, layout, binding, pOffset);
    }
#endif
#if (defined(VK_EXT_descriptor_buffer))
    void getDescriptorEXT(const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor) const noexcept {
        fp_vkGetDescriptorEXT(device, pDescriptorInfo, dataSize, pDescriptor);
    }
#endif
#if (defined(VK_EXT_descriptor_buffer))
    void cmdBindDescriptorBuffersEXT(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos) const noexcept {
        fp_vkCmdBindDescriptorBuffersEXT(commandBuffer, bufferCount, pBindingInfos);
    }
#endif
#if (defined(VK_EXT_descriptor_buffer))
    void cmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets) const noexcept {
        fp_vkCmdSetDescriptorBufferOffsetsEXT(commandBuffer, pipelineBindPoint, layout, firstSet, setCount, pBufferIndices, pOffsets);
    }
#endif
#if (defined(VK_EXT_descriptor_buffer))
    void cmdBindDescriptorBufferEmbeddedSamplersEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set) const noexcept {
        fp_vkCmdBindDescriptorBufferEmbeddedSamplersEXT(commandBuffer, pipelineBindPoint, layout, set);
    }
#endif
#if (defined(VK_EXT_descriptor_buffer))
    VkResult getBufferOpaqueCaptureDescriptorDataEXT(const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData) const noexcept {
        return fp_vkGetBufferOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
    }
#endif
#if (defined(VK_EXT_descriptor_buffer))
    VkResult getImageOpaqueCaptureDescriptorDataEXT(const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData) const noexcept {
        return fp_vkGetImageOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
    }
#endif
#if (defined(VK_EXT_descriptor_buffer))
    VkResult getImageViewOpaqueCaptureDescriptorDataEXT(const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData) const noexcept {
        return fp_vkGetImageViewOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
    }
#endif
#if (defined(VK_EXT_descriptor_buffer))
    VkResult getSamplerOpaqueCaptureDescriptorDataEXT(const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData) const noexcept {
        return fp_vkGetSamplerOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
    }
#endif
#if (defined(VK_EXT_descriptor_buffer))
    VkResult getAccelerationStructureOpaqueCaptureDescriptorDataEXT(const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData) const noexcept {
        return fp_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
    }
#endif
#if (defined(VK_EXT_pageable_device_local_memory))
    void setDeviceMemoryPriorityEXT(VkDeviceMemory memory, float priority) const noexcept {
        fp_vkSetDeviceMemoryPriorityEXT(device, memory, priority);
    }
#endif
#if (defined(VK_KHR_present_wait))
    VkResult waitForPresentKHR(VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout) const noexcept {
        return fp_vkWaitForPresentKHR(device, swapchain, presentId, timeout);
    }
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
    VkResult createBufferCollectionFUCHSIA(const VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection) const noexcept {
        return fp_vkCreateBufferCollectionFUCHSIA(device, pCreateInfo, pAllocator, pCollection);
    }
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
    VkResult setBufferCollectionBufferConstraintsFUCHSIA(VkBufferCollectionFUCHSIA collection, const VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo) const noexcept {
        return fp_vkSetBufferCollectionBufferConstraintsFUCHSIA(device, collection, pBufferConstraintsInfo);
    }
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
    VkResult setBufferCollectionImageConstraintsFUCHSIA(VkBufferCollectionFUCHSIA collection, const VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo) const noexcept {
        return fp_vkSetBufferCollectionImageConstraintsFUCHSIA(device, collection, pImageConstraintsInfo);
    }
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
    void destroyBufferCollectionFUCHSIA(VkBufferCollectionFUCHSIA collection, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyBufferCollectionFUCHSIA(device, collection, pAllocator);
    }
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
    VkResult getBufferCollectionPropertiesFUCHSIA(VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties) const noexcept {
        return fp_vkGetBufferCollectionPropertiesFUCHSIA(device, collection, pProperties);
    }
#endif
#if (defined(VK_NV_cuda_kernel_launch))
    VkResult createCudaModuleNV(const VkCudaModuleCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCudaModuleNV* pModule) const noexcept {
        return fp_vkCreateCudaModuleNV(device, pCreateInfo, pAllocator, pModule);
    }
#endif
#if (defined(VK_NV_cuda_kernel_launch))
    VkResult getCudaModuleCacheNV(VkCudaModuleNV module, size_t* pCacheSize, void* pCacheData) const noexcept {
        return fp_vkGetCudaModuleCacheNV(device, module, pCacheSize, pCacheData);
    }
#endif
#if (defined(VK_NV_cuda_kernel_launch))
    VkResult createCudaFunctionNV(const VkCudaFunctionCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCudaFunctionNV* pFunction) const noexcept {
        return fp_vkCreateCudaFunctionNV(device, pCreateInfo, pAllocator, pFunction);
    }
#endif
#if (defined(VK_NV_cuda_kernel_launch))
    void destroyCudaModuleNV(VkCudaModuleNV module, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyCudaModuleNV(device, module, pAllocator);
    }
#endif
#if (defined(VK_NV_cuda_kernel_launch))
    void destroyCudaFunctionNV(VkCudaFunctionNV function, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyCudaFunctionNV(device, function, pAllocator);
    }
#endif
#if (defined(VK_NV_cuda_kernel_launch))
    void cmdCudaLaunchKernelNV(VkCommandBuffer commandBuffer, const VkCudaLaunchInfoNV* pLaunchInfo) const noexcept {
        fp_vkCmdCudaLaunchKernelNV(commandBuffer, pLaunchInfo);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdBeginRendering(VkCommandBuffer commandBuffer, const VkRenderingInfoKHR* pRenderingInfo) const noexcept {
        fp_vkCmdBeginRendering(commandBuffer, pRenderingInfo);
    }
#endif
#if (defined(VK_VERSION_1_3))
    void cmdEndRendering(VkCommandBuffer commandBuffer) const noexcept {
        fp_vkCmdEndRendering(commandBuffer);
    }
#endif
#if (defined(VK_VALVE_descriptor_set_host_mapping))
    void getDescriptorSetLayoutHostMappingInfoVALVE(const VkDescriptorSetBindingReferenceVALVE* pBindingReference, VkDescriptorSetLayoutHostMappingInfoVALVE* pHostMapping) const noexcept {
        fp_vkGetDescriptorSetLayoutHostMappingInfoVALVE(device, pBindingReference, pHostMapping);
    }
#endif
#if (defined(VK_VALVE_descriptor_set_host_mapping))
    void getDescriptorSetHostMappingVALVE(VkDescriptorSet descriptorSet, void** ppData) const noexcept {
        fp_vkGetDescriptorSetHostMappingVALVE(device, descriptorSet, ppData);
    }
#endif
#if (defined(VK_EXT_opacity_micromap))
    VkResult createMicromapEXT(const VkMicromapCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkMicromapEXT* pMicromap) const noexcept {
        return fp_vkCreateMicromapEXT(device, pCreateInfo, pAllocator, pMicromap);
    }
#endif
#if (defined(VK_EXT_opacity_micromap))
    void cmdBuildMicromapsEXT(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) const noexcept {
        fp_vkCmdBuildMicromapsEXT(commandBuffer, infoCount, pInfos);
    }
#endif
#if (defined(VK_EXT_opacity_micromap))
    VkResult buildMicromapsEXT(VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos) const noexcept {
        return fp_vkBuildMicromapsEXT(device, deferredOperation, infoCount, pInfos);
    }
#endif
#if (defined(VK_EXT_opacity_micromap))
    void destroyMicromapEXT(VkMicromapEXT micromap, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyMicromapEXT(device, micromap, pAllocator);
    }
#endif
#if (defined(VK_EXT_opacity_micromap))
    void cmdCopyMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT* pInfo) const noexcept {
        fp_vkCmdCopyMicromapEXT(commandBuffer, pInfo);
    }
#endif
#if (defined(VK_EXT_opacity_micromap))
    VkResult copyMicromapEXT(VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT* pInfo) const noexcept {
        return fp_vkCopyMicromapEXT(device, deferredOperation, pInfo);
    }
#endif
#if (defined(VK_EXT_opacity_micromap))
    void cmdCopyMicromapToMemoryEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo) const noexcept {
        fp_vkCmdCopyMicromapToMemoryEXT(commandBuffer, pInfo);
    }
#endif
#if (defined(VK_EXT_opacity_micromap))
    VkResult copyMicromapToMemoryEXT(VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT* pInfo) const noexcept {
        return fp_vkCopyMicromapToMemoryEXT(device, deferredOperation, pInfo);
    }
#endif
#if (defined(VK_EXT_opacity_micromap))
    void cmdCopyMemoryToMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo) const noexcept {
        fp_vkCmdCopyMemoryToMicromapEXT(commandBuffer, pInfo);
    }
#endif
#if (defined(VK_EXT_opacity_micromap))
    VkResult copyMemoryToMicromapEXT(VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT* pInfo) const noexcept {
        return fp_vkCopyMemoryToMicromapEXT(device, deferredOperation, pInfo);
    }
#endif
#if (defined(VK_EXT_opacity_micromap))
    void cmdWriteMicromapsPropertiesEXT(VkCommandBuffer commandBuffer, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) const noexcept {
        fp_vkCmdWriteMicromapsPropertiesEXT(commandBuffer, micromapCount, pMicromaps, queryType, queryPool, firstQuery);
    }
#endif
#if (defined(VK_EXT_opacity_micromap))
    VkResult writeMicromapsPropertiesEXT(uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, size_t dataSize, void* pData, size_t stride) const noexcept {
        return fp_vkWriteMicromapsPropertiesEXT(device, micromapCount, pMicromaps, queryType, dataSize, pData, stride);
    }
#endif
#if (defined(VK_EXT_opacity_micromap))
    void getDeviceMicromapCompatibilityEXT(const VkMicromapVersionInfoEXT* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) const noexcept {
        fp_vkGetDeviceMicromapCompatibilityEXT(device, pVersionInfo, pCompatibility);
    }
#endif
#if (defined(VK_EXT_opacity_micromap))
    void getMicromapBuildSizesEXT(VkAccelerationStructureBuildTypeKHR buildType, const VkMicromapBuildInfoEXT* pBuildInfo, VkMicromapBuildSizesInfoEXT* pSizeInfo) const noexcept {
        fp_vkGetMicromapBuildSizesEXT(device, buildType, pBuildInfo, pSizeInfo);
    }
#endif
#if (defined(VK_EXT_shader_module_identifier))
    void getShaderModuleIdentifierEXT(VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier) const noexcept {
        fp_vkGetShaderModuleIdentifierEXT(device, shaderModule, pIdentifier);
    }
#endif
#if (defined(VK_EXT_shader_module_identifier))
    void getShaderModuleCreateInfoIdentifierEXT(const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier) const noexcept {
        fp_vkGetShaderModuleCreateInfoIdentifierEXT(device, pCreateInfo, pIdentifier);
    }
#endif
#if (defined(VK_KHR_maintenance5))
    void getImageSubresourceLayout2KHR(VkImage image, const VkImageSubresource2EXT* pSubresource, VkSubresourceLayout2EXT* pLayout) const noexcept {
        fp_vkGetImageSubresourceLayout2KHR(device, image, pSubresource, pLayout);
    }
#endif
#if (defined(VK_EXT_pipeline_properties))
    VkResult getPipelinePropertiesEXT(const VkPipelineInfoEXT* pPipelineInfo, VkBaseOutStructure* pPipelineProperties) const noexcept {
        return fp_vkGetPipelinePropertiesEXT(device, pPipelineInfo, pPipelineProperties);
    }
#endif
#if (defined(VK_EXT_metal_objects))
    void exportMetalObjectsEXT(VkExportMetalObjectsInfoEXT* pMetalObjectsInfo) const noexcept {
        fp_vkExportMetalObjectsEXT(device, pMetalObjectsInfo);
    }
#endif
#if (defined(VK_QCOM_tile_properties))
    VkResult getFramebufferTilePropertiesQCOM(VkFramebuffer framebuffer, uint32_t* pPropertiesCount, VkTilePropertiesQCOM* pProperties) const noexcept {
        return fp_vkGetFramebufferTilePropertiesQCOM(device, framebuffer, pPropertiesCount, pProperties);
    }
#endif
#if (defined(VK_QCOM_tile_properties))
    VkResult getDynamicRenderingTilePropertiesQCOM(const VkRenderingInfoKHR* pRenderingInfo, VkTilePropertiesQCOM* pProperties) const noexcept {
        return fp_vkGetDynamicRenderingTilePropertiesQCOM(device, pRenderingInfo, pProperties);
    }
#endif
#if (defined(VK_NV_optical_flow))
    VkResult createOpticalFlowSessionNV(const VkOpticalFlowSessionCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkOpticalFlowSessionNV* pSession) const noexcept {
        return fp_vkCreateOpticalFlowSessionNV(device, pCreateInfo, pAllocator, pSession);
    }
#endif
#if (defined(VK_NV_optical_flow))
    void destroyOpticalFlowSessionNV(VkOpticalFlowSessionNV session, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyOpticalFlowSessionNV(device, session, pAllocator);
    }
#endif
#if (defined(VK_NV_optical_flow))
    VkResult bindOpticalFlowSessionImageNV(VkOpticalFlowSessionNV session, VkOpticalFlowSessionBindingPointNV bindingPoint, VkImageView view, VkImageLayout layout) const noexcept {
        return fp_vkBindOpticalFlowSessionImageNV(device, session, bindingPoint, view, layout);
    }
#endif
#if (defined(VK_NV_optical_flow))
    void cmdOpticalFlowExecuteNV(VkCommandBuffer commandBuffer, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV* pExecuteInfo) const noexcept {
        fp_vkCmdOpticalFlowExecuteNV(commandBuffer, session, pExecuteInfo);
    }
#endif
#if (defined(VK_EXT_device_fault))
    VkResult getDeviceFaultInfoEXT(VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo) const noexcept {
        return fp_vkGetDeviceFaultInfoEXT(device, pFaultCounts, pFaultInfo);
    }
#endif
#if (defined(VK_EXT_depth_bias_control))
    void cmdSetDepthBias2EXT(VkCommandBuffer commandBuffer, const VkDepthBiasInfoEXT* pDepthBiasInfo) const noexcept {
        fp_vkCmdSetDepthBias2EXT(commandBuffer, pDepthBiasInfo);
    }
#endif
#if (defined(VK_EXT_swapchain_maintenance1))
    VkResult releaseSwapchainImagesEXT(const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo) const noexcept {
        return fp_vkReleaseSwapchainImagesEXT(device, pReleaseInfo);
    }
#endif
#if (defined(VK_KHR_maintenance5))
    void getDeviceImageSubresourceLayoutKHR(const VkDeviceImageSubresourceInfoKHR* pInfo, VkSubresourceLayout2EXT* pLayout) const noexcept {
        fp_vkGetDeviceImageSubresourceLayoutKHR(device, pInfo, pLayout);
    }
#endif
#if (defined(VK_KHR_map_memory2))
    VkResult mapMemory2KHR(const VkMemoryMapInfoKHR* pMemoryMapInfo, void** ppData) const noexcept {
        return fp_vkMapMemory2KHR(device, pMemoryMapInfo, ppData);
    }
#endif
#if (defined(VK_KHR_map_memory2))
    VkResult unmapMemory2KHR(const VkMemoryUnmapInfoKHR* pMemoryUnmapInfo) const noexcept {
        return fp_vkUnmapMemory2KHR(device, pMemoryUnmapInfo);
    }
#endif
#if (defined(VK_EXT_shader_object))
    VkResult createShadersEXT(uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders) const noexcept {
        return fp_vkCreateShadersEXT(device, createInfoCount, pCreateInfos, pAllocator, pShaders);
    }
#endif
#if (defined(VK_EXT_shader_object))
    void destroyShaderEXT(VkShaderEXT shader, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyShaderEXT(device, shader, pAllocator);
    }
#endif
#if (defined(VK_EXT_shader_object))
    VkResult getShaderBinaryDataEXT(VkShaderEXT shader, size_t* pDataSize, void* pData) const noexcept {
        return fp_vkGetShaderBinaryDataEXT(device, shader, pDataSize, pData);
    }
#endif
#if (defined(VK_EXT_shader_object))
    void cmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders) const noexcept {
        fp_vkCmdBindShadersEXT(commandBuffer, stageCount, pStages, pShaders);
    }
#endif
#if (defined(VK_QNX_external_memory_screen_buffer))
    VkResult getScreenBufferPropertiesQNX(const struct _screen_buffer* buffer, VkScreenBufferPropertiesQNX* pProperties) const noexcept {
        return fp_vkGetScreenBufferPropertiesQNX(device, buffer, pProperties);
    }
#endif
#if (defined(VK_AMDX_shader_enqueue))
    VkResult getExecutionGraphPipelineScratchSizeAMDX(VkPipeline executionGraph, VkExecutionGraphPipelineScratchSizeAMDX* pSizeInfo) const noexcept {
        return fp_vkGetExecutionGraphPipelineScratchSizeAMDX(device, executionGraph, pSizeInfo);
    }
#endif
#if (defined(VK_AMDX_shader_enqueue))
    VkResult getExecutionGraphPipelineNodeIndexAMDX(VkPipeline executionGraph, const VkPipelineShaderStageNodeCreateInfoAMDX* pNodeInfo, uint32_t* pNodeIndex) const noexcept {
        return fp_vkGetExecutionGraphPipelineNodeIndexAMDX(device, executionGraph, pNodeInfo, pNodeIndex);
    }
#endif
#if (defined(VK_AMDX_shader_enqueue))
    VkResult createExecutionGraphPipelinesAMDX(VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) const noexcept {
        return fp_vkCreateExecutionGraphPipelinesAMDX(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    }
#endif
#if (defined(VK_AMDX_shader_enqueue))
    void cmdInitializeGraphScratchMemoryAMDX(VkCommandBuffer commandBuffer, VkDeviceAddress scratch) const noexcept {
        fp_vkCmdInitializeGraphScratchMemoryAMDX(commandBuffer, scratch);
    }
#endif
#if (defined(VK_AMDX_shader_enqueue))
    void cmdDispatchGraphAMDX(VkCommandBuffer commandBuffer, VkDeviceAddress scratch, const VkDispatchGraphCountInfoAMDX* pCountInfo) const noexcept {
        fp_vkCmdDispatchGraphAMDX(commandBuffer, scratch, pCountInfo);
    }
#endif
#if (defined(VK_AMDX_shader_enqueue))
    void cmdDispatchGraphIndirectAMDX(VkCommandBuffer commandBuffer, VkDeviceAddress scratch, const VkDispatchGraphCountInfoAMDX* pCountInfo) const noexcept {
        fp_vkCmdDispatchGraphIndirectAMDX(commandBuffer, scratch, pCountInfo);
    }
#endif
#if (defined(VK_AMDX_shader_enqueue))
    void cmdDispatchGraphIndirectCountAMDX(VkCommandBuffer commandBuffer, VkDeviceAddress scratch, VkDeviceAddress countInfo) const noexcept {
        fp_vkCmdDispatchGraphIndirectCountAMDX(commandBuffer, scratch, countInfo);
    }
#endif
#if (defined(VK_KHR_maintenance6))
    void cmdBindDescriptorSets2KHR(VkCommandBuffer commandBuffer, const VkBindDescriptorSetsInfoKHR* pBindDescriptorSetsInfo) const noexcept {
        fp_vkCmdBindDescriptorSets2KHR(commandBuffer, pBindDescriptorSetsInfo);
    }
#endif
#if (defined(VK_KHR_maintenance6))
    void cmdPushConstants2KHR(VkCommandBuffer commandBuffer, const VkPushConstantsInfoKHR* pPushConstantsInfo) const noexcept {
        fp_vkCmdPushConstants2KHR(commandBuffer, pPushConstantsInfo);
    }
#endif
#if (defined(VK_KHR_maintenance6))
    void cmdPushDescriptorSet2KHR(VkCommandBuffer commandBuffer, const VkPushDescriptorSetInfoKHR* pPushDescriptorSetInfo) const noexcept {
        fp_vkCmdPushDescriptorSet2KHR(commandBuffer, pPushDescriptorSetInfo);
    }
#endif
#if (defined(VK_KHR_maintenance6))
    void cmdPushDescriptorSetWithTemplate2KHR(VkCommandBuffer commandBuffer, const VkPushDescriptorSetWithTemplateInfoKHR* pPushDescriptorSetWithTemplateInfo) const noexcept {
        fp_vkCmdPushDescriptorSetWithTemplate2KHR(commandBuffer, pPushDescriptorSetWithTemplateInfo);
    }
#endif
#if (defined(VK_KHR_maintenance6))
    void cmdSetDescriptorBufferOffsets2EXT(VkCommandBuffer commandBuffer, const VkSetDescriptorBufferOffsetsInfoEXT* pSetDescriptorBufferOffsetsInfo) const noexcept {
        fp_vkCmdSetDescriptorBufferOffsets2EXT(commandBuffer, pSetDescriptorBufferOffsetsInfo);
    }
#endif
#if (defined(VK_KHR_maintenance6))
    void cmdBindDescriptorBufferEmbeddedSamplers2EXT(VkCommandBuffer commandBuffer, const VkBindDescriptorBufferEmbeddedSamplersInfoEXT* pBindDescriptorBufferEmbeddedSamplersInfo) const noexcept {
        fp_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT(commandBuffer, pBindDescriptorBufferEmbeddedSamplersInfo);
    }
#endif
#if (defined(VK_NV_low_latency2))
    VkResult setLatencySleepModeNV(VkSwapchainKHR swapchain, const VkLatencySleepModeInfoNV* pSleepModeInfo) const noexcept {
        return fp_vkSetLatencySleepModeNV(device, swapchain, pSleepModeInfo);
    }
#endif
#if (defined(VK_NV_low_latency2))
    VkResult latencySleepNV(VkSwapchainKHR swapchain, const VkLatencySleepInfoNV* pSleepInfo) const noexcept {
        return fp_vkLatencySleepNV(device, swapchain, pSleepInfo);
    }
#endif
#if (defined(VK_NV_low_latency2))
    void setLatencyMarkerNV(VkSwapchainKHR swapchain, const VkSetLatencyMarkerInfoNV* pLatencyMarkerInfo) const noexcept {
        fp_vkSetLatencyMarkerNV(device, swapchain, pLatencyMarkerInfo);
    }
#endif
#if ((defined(VK_NV_low_latency2))) && VK_HEADER_VERSION >= 271
    void getLatencyTimingsNV(VkSwapchainKHR swapchain, VkGetLatencyMarkerInfoNV* pLatencyMarkerInfo) const noexcept {
        fp_vkGetLatencyTimingsNV(device, swapchain, pLatencyMarkerInfo);
    }
#endif
#if (defined(VK_NV_low_latency2))
    void queueNotifyOutOfBandNV(VkQueue queue, const VkOutOfBandQueueTypeInfoNV* pQueueTypeInfo) const noexcept {
        fp_vkQueueNotifyOutOfBandNV(queue, pQueueTypeInfo);
    }
#endif
#if (defined(VK_EXT_host_query_reset))
    void resetQueryPoolEXT(VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) const noexcept {
        fp_vkResetQueryPoolEXT(device, queryPool, firstQuery, queryCount);
    }
#endif
#if (defined(VK_KHR_maintenance1))
    void trimCommandPoolKHR(VkCommandPool commandPool, VkCommandPoolTrimFlagsKHR flags) const noexcept {
        fp_vkTrimCommandPoolKHR(device, commandPool, flags);
    }
#endif
#if (defined(VK_KHR_device_group))
    void getDeviceGroupPeerMemoryFeaturesKHR(uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlagsKHR* pPeerMemoryFeatures) const noexcept {
        fp_vkGetDeviceGroupPeerMemoryFeaturesKHR(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    }
#endif
#if (defined(VK_KHR_bind_memory2))
    VkResult bindBufferMemory2KHR(uint32_t bindInfoCount, const VkBindBufferMemoryInfoKHR* pBindInfos) const noexcept {
        return fp_vkBindBufferMemory2KHR(device, bindInfoCount, pBindInfos);
    }
#endif
#if (defined(VK_KHR_bind_memory2))
    VkResult bindImageMemory2KHR(uint32_t bindInfoCount, const VkBindImageMemoryInfoKHR* pBindInfos) const noexcept {
        return fp_vkBindImageMemory2KHR(device, bindInfoCount, pBindInfos);
    }
#endif
#if (defined(VK_KHR_device_group))
    void cmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) const noexcept {
        fp_vkCmdSetDeviceMaskKHR(commandBuffer, deviceMask);
    }
#endif
#if (defined(VK_KHR_device_group))
    void cmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const noexcept {
        fp_vkCmdDispatchBaseKHR(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    }
#endif
#if (defined(VK_KHR_descriptor_update_template))
    VkResult createDescriptorUpdateTemplateKHR(const VkDescriptorUpdateTemplateCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplateKHR* pDescriptorUpdateTemplate) const noexcept {
        return fp_vkCreateDescriptorUpdateTemplateKHR(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    }
#endif
#if (defined(VK_KHR_descriptor_update_template))
    void destroyDescriptorUpdateTemplateKHR(VkDescriptorUpdateTemplateKHR descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyDescriptorUpdateTemplateKHR(device, descriptorUpdateTemplate, pAllocator);
    }
#endif
#if (defined(VK_KHR_descriptor_update_template))
    void updateDescriptorSetWithTemplateKHR(VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplateKHR descriptorUpdateTemplate, const void* pData) const noexcept {
        fp_vkUpdateDescriptorSetWithTemplateKHR(device, descriptorSet, descriptorUpdateTemplate, pData);
    }
#endif
#if (defined(VK_KHR_get_memory_requirements2))
    void getBufferMemoryRequirements2KHR(const VkBufferMemoryRequirementsInfo2KHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) const noexcept {
        fp_vkGetBufferMemoryRequirements2KHR(device, pInfo, pMemoryRequirements);
    }
#endif
#if (defined(VK_KHR_get_memory_requirements2))
    void getImageMemoryRequirements2KHR(const VkImageMemoryRequirementsInfo2KHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) const noexcept {
        fp_vkGetImageMemoryRequirements2KHR(device, pInfo, pMemoryRequirements);
    }
#endif
#if (defined(VK_KHR_get_memory_requirements2))
    void getImageSparseMemoryRequirements2KHR(const VkImageSparseMemoryRequirementsInfo2KHR* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2KHR* pSparseMemoryRequirements) const noexcept {
        fp_vkGetImageSparseMemoryRequirements2KHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    }
#endif
#if (defined(VK_KHR_maintenance4))
    void getDeviceBufferMemoryRequirementsKHR(const VkDeviceBufferMemoryRequirementsKHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) const noexcept {
        fp_vkGetDeviceBufferMemoryRequirementsKHR(device, pInfo, pMemoryRequirements);
    }
#endif
#if (defined(VK_KHR_maintenance4))
    void getDeviceImageMemoryRequirementsKHR(const VkDeviceImageMemoryRequirementsKHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements) const noexcept {
        fp_vkGetDeviceImageMemoryRequirementsKHR(device, pInfo, pMemoryRequirements);
    }
#endif
#if (defined(VK_KHR_maintenance4))
    void getDeviceImageSparseMemoryRequirementsKHR(const VkDeviceImageMemoryRequirementsKHR* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2KHR* pSparseMemoryRequirements) const noexcept {
        fp_vkGetDeviceImageSparseMemoryRequirementsKHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    }
#endif
#if (defined(VK_KHR_sampler_ycbcr_conversion))
    VkResult createSamplerYcbcrConversionKHR(const VkSamplerYcbcrConversionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversionKHR* pYcbcrConversion) const noexcept {
        return fp_vkCreateSamplerYcbcrConversionKHR(device, pCreateInfo, pAllocator, pYcbcrConversion);
    }
#endif
#if (defined(VK_KHR_sampler_ycbcr_conversion))
    void destroySamplerYcbcrConversionKHR(VkSamplerYcbcrConversionKHR ycbcrConversion, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroySamplerYcbcrConversionKHR(device, ycbcrConversion, pAllocator);
    }
#endif
#if (defined(VK_KHR_maintenance3))
    void getDescriptorSetLayoutSupportKHR(const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupportKHR* pSupport) const noexcept {
        fp_vkGetDescriptorSetLayoutSupportKHR(device, pCreateInfo, pSupport);
    }
#endif
#if (defined(VK_EXT_calibrated_timestamps))
    VkResult getCalibratedTimestampsEXT(uint32_t timestampCount, const VkCalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation) const noexcept {
        return fp_vkGetCalibratedTimestampsEXT(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
    }
#endif
#if (defined(VK_KHR_create_renderpass2))
    VkResult createRenderPass2KHR(const VkRenderPassCreateInfo2KHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) const noexcept {
        return fp_vkCreateRenderPass2KHR(device, pCreateInfo, pAllocator, pRenderPass);
    }
#endif
#if (defined(VK_KHR_create_renderpass2))
    void cmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, const VkSubpassBeginInfoKHR* pSubpassBeginInfo) const noexcept {
        fp_vkCmdBeginRenderPass2KHR(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    }
#endif
#if (defined(VK_KHR_create_renderpass2))
    void cmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfoKHR* pSubpassBeginInfo, const VkSubpassEndInfoKHR* pSubpassEndInfo) const noexcept {
        fp_vkCmdNextSubpass2KHR(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    }
#endif
#if (defined(VK_KHR_create_renderpass2))
    void cmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfoKHR* pSubpassEndInfo) const noexcept {
        fp_vkCmdEndRenderPass2KHR(commandBuffer, pSubpassEndInfo);
    }
#endif
#if (defined(VK_KHR_timeline_semaphore))
    VkResult getSemaphoreCounterValueKHR(VkSemaphore semaphore, uint64_t* pValue) const noexcept {
        return fp_vkGetSemaphoreCounterValueKHR(device, semaphore, pValue);
    }
#endif
#if (defined(VK_KHR_timeline_semaphore))
    VkResult waitSemaphoresKHR(const VkSemaphoreWaitInfoKHR* pWaitInfo, uint64_t timeout) const noexcept {
        return fp_vkWaitSemaphoresKHR(device, pWaitInfo, timeout);
    }
#endif
#if (defined(VK_KHR_timeline_semaphore))
    VkResult signalSemaphoreKHR(const VkSemaphoreSignalInfoKHR* pSignalInfo) const noexcept {
        return fp_vkSignalSemaphoreKHR(device, pSignalInfo);
    }
#endif
#if (defined(VK_AMD_draw_indirect_count))
    void cmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const noexcept {
        fp_vkCmdDrawIndirectCountAMD(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    }
#endif
#if (defined(VK_AMD_draw_indirect_count))
    void cmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const noexcept {
        fp_vkCmdDrawIndexedIndirectCountAMD(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    }
#endif
#if (defined(VK_NV_ray_tracing))
    VkResult getRayTracingShaderGroupHandlesNV(VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) const noexcept {
        return fp_vkGetRayTracingShaderGroupHandlesNV(device, pipeline, firstGroup, groupCount, dataSize, pData);
    }
#endif
#if (defined(VK_KHR_buffer_device_address))
    uint64_t getBufferOpaqueCaptureAddressKHR(const VkBufferDeviceAddressInfoEXT* pInfo) const noexcept {
        return fp_vkGetBufferOpaqueCaptureAddressKHR(device, pInfo);
    }
#endif
#if (defined(VK_EXT_buffer_device_address))
    VkDeviceAddress getBufferDeviceAddressEXT(const VkBufferDeviceAddressInfoEXT* pInfo) const noexcept {
        return fp_vkGetBufferDeviceAddressEXT(device, pInfo);
    }
#endif
#if (defined(VK_KHR_buffer_device_address))
    uint64_t getDeviceMemoryOpaqueCaptureAddressKHR(const VkDeviceMemoryOpaqueCaptureAddressInfoKHR* pInfo) const noexcept {
        return fp_vkGetDeviceMemoryOpaqueCaptureAddressKHR(device, pInfo);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    void cmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) const noexcept {
        fp_vkCmdSetCullModeEXT(commandBuffer, cullMode);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    void cmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace) const noexcept {
        fp_vkCmdSetFrontFaceEXT(commandBuffer, frontFace);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    void cmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) const noexcept {
        fp_vkCmdSetPrimitiveTopologyEXT(commandBuffer, primitiveTopology);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    void cmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) const noexcept {
        fp_vkCmdSetViewportWithCountEXT(commandBuffer, viewportCount, pViewports);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    void cmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) const noexcept {
        fp_vkCmdSetScissorWithCountEXT(commandBuffer, scissorCount, pScissors);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    void cmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) const noexcept {
        fp_vkCmdBindVertexBuffers2EXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    void cmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) const noexcept {
        fp_vkCmdSetDepthTestEnableEXT(commandBuffer, depthTestEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    void cmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) const noexcept {
        fp_vkCmdSetDepthWriteEnableEXT(commandBuffer, depthWriteEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    void cmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) const noexcept {
        fp_vkCmdSetDepthCompareOpEXT(commandBuffer, depthCompareOp);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    void cmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) const noexcept {
        fp_vkCmdSetDepthBoundsTestEnableEXT(commandBuffer, depthBoundsTestEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    void cmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) const noexcept {
        fp_vkCmdSetStencilTestEnableEXT(commandBuffer, stencilTestEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    void cmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) const noexcept {
        fp_vkCmdSetStencilOpEXT(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
    void cmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) const noexcept {
        fp_vkCmdSetRasterizerDiscardEnableEXT(commandBuffer, rasterizerDiscardEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
    void cmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) const noexcept {
        fp_vkCmdSetDepthBiasEnableEXT(commandBuffer, depthBiasEnable);
    }
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
    void cmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) const noexcept {
        fp_vkCmdSetPrimitiveRestartEnableEXT(commandBuffer, primitiveRestartEnable);
    }
#endif
#if (defined(VK_EXT_private_data))
    VkResult createPrivateDataSlotEXT(const VkPrivateDataSlotCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlotEXT* pPrivateDataSlot) const noexcept {
        return fp_vkCreatePrivateDataSlotEXT(device, pCreateInfo, pAllocator, pPrivateDataSlot);
    }
#endif
#if (defined(VK_EXT_private_data))
    void destroyPrivateDataSlotEXT(VkPrivateDataSlotEXT privateDataSlot, const VkAllocationCallbacks* pAllocator) const noexcept {
        fp_vkDestroyPrivateDataSlotEXT(device, privateDataSlot, pAllocator);
    }
#endif
#if (defined(VK_EXT_private_data))
    VkResult setPrivateDataEXT(VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlotEXT privateDataSlot, uint64_t data) const noexcept {
        return fp_vkSetPrivateDataEXT(device, objectType, objectHandle, privateDataSlot, data);
    }
#endif
#if (defined(VK_EXT_private_data))
    void getPrivateDataEXT(VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlotEXT privateDataSlot, uint64_t* pData) const noexcept {
        fp_vkGetPrivateDataEXT(device, objectType, objectHandle, privateDataSlot, pData);
    }
#endif
#if (defined(VK_KHR_copy_commands2))
    void cmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2KHR* pCopyBufferInfo) const noexcept {
        fp_vkCmdCopyBuffer2KHR(commandBuffer, pCopyBufferInfo);
    }
#endif
#if (defined(VK_KHR_copy_commands2))
    void cmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2KHR* pCopyImageInfo) const noexcept {
        fp_vkCmdCopyImage2KHR(commandBuffer, pCopyImageInfo);
    }
#endif
#if (defined(VK_KHR_copy_commands2))
    void cmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2KHR* pBlitImageInfo) const noexcept {
        fp_vkCmdBlitImage2KHR(commandBuffer, pBlitImageInfo);
    }
#endif
#if (defined(VK_KHR_copy_commands2))
    void cmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2KHR* pCopyBufferToImageInfo) const noexcept {
        fp_vkCmdCopyBufferToImage2KHR(commandBuffer, pCopyBufferToImageInfo);
    }
#endif
#if (defined(VK_KHR_copy_commands2))
    void cmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2KHR* pCopyImageToBufferInfo) const noexcept {
        fp_vkCmdCopyImageToBuffer2KHR(commandBuffer, pCopyImageToBufferInfo);
    }
#endif
#if (defined(VK_KHR_copy_commands2))
    void cmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2KHR* pResolveImageInfo) const noexcept {
        fp_vkCmdResolveImage2KHR(commandBuffer, pResolveImageInfo);
    }
#endif
#if (defined(VK_KHR_synchronization2))
    void cmdSetEvent2KHR(VkCommandBuffer commandBuffer, VkEvent event, const VkDependencyInfoKHR* pDependencyInfo) const noexcept {
        fp_vkCmdSetEvent2KHR(commandBuffer, event, pDependencyInfo);
    }
#endif
#if (defined(VK_KHR_synchronization2))
    void cmdResetEvent2KHR(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags2KHR stageMask) const noexcept {
        fp_vkCmdResetEvent2KHR(commandBuffer, event, stageMask);
    }
#endif
#if (defined(VK_KHR_synchronization2))
    void cmdWaitEvents2KHR(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, const VkDependencyInfoKHR* pDependencyInfos) const noexcept {
        fp_vkCmdWaitEvents2KHR(commandBuffer, eventCount, pEvents, pDependencyInfos);
    }
#endif
#if (defined(VK_KHR_synchronization2))
    void cmdPipelineBarrier2KHR(VkCommandBuffer commandBuffer, const VkDependencyInfoKHR* pDependencyInfo) const noexcept {
        fp_vkCmdPipelineBarrier2KHR(commandBuffer, pDependencyInfo);
    }
#endif
#if (defined(VK_KHR_synchronization2))
    VkResult queueSubmit2KHR(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2KHR* pSubmits, VkFence fence) const noexcept {
        return fp_vkQueueSubmit2KHR(queue, submitCount, pSubmits, fence);
    }
#endif
#if (defined(VK_KHR_synchronization2))
    void cmdWriteTimestamp2KHR(VkCommandBuffer commandBuffer, VkPipelineStageFlags2KHR stage, VkQueryPool queryPool, uint32_t query) const noexcept {
        fp_vkCmdWriteTimestamp2KHR(commandBuffer, stage, queryPool, query);
    }
#endif
#if (defined(VK_KHR_dynamic_rendering))
    void cmdBeginRenderingKHR(VkCommandBuffer commandBuffer, const VkRenderingInfoKHR* pRenderingInfo) const noexcept {
        fp_vkCmdBeginRenderingKHR(commandBuffer, pRenderingInfo);
    }
#endif
#if (defined(VK_KHR_dynamic_rendering))
    void cmdEndRenderingKHR(VkCommandBuffer commandBuffer) const noexcept {
        fp_vkCmdEndRenderingKHR(commandBuffer);
    }
#endif
#if (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))
    void getImageSubresourceLayout2EXT(VkImage image, const VkImageSubresource2EXT* pSubresource, VkSubresourceLayout2EXT* pLayout) const noexcept {
        fp_vkGetImageSubresourceLayout2EXT(device, image, pSubresource, pLayout);
    }
#endif
    PFN_vkGetDeviceQueue fp_vkGetDeviceQueue = nullptr;
    PFN_vkQueueSubmit fp_vkQueueSubmit = nullptr;
    PFN_vkQueueWaitIdle fp_vkQueueWaitIdle = nullptr;
    PFN_vkDeviceWaitIdle fp_vkDeviceWaitIdle = nullptr;
    PFN_vkAllocateMemory fp_vkAllocateMemory = nullptr;
    PFN_vkFreeMemory fp_vkFreeMemory = nullptr;
    PFN_vkMapMemory fp_vkMapMemory = nullptr;
    PFN_vkUnmapMemory fp_vkUnmapMemory = nullptr;
    PFN_vkFlushMappedMemoryRanges fp_vkFlushMappedMemoryRanges = nullptr;
    PFN_vkInvalidateMappedMemoryRanges fp_vkInvalidateMappedMemoryRanges = nullptr;
    PFN_vkGetDeviceMemoryCommitment fp_vkGetDeviceMemoryCommitment = nullptr;
    PFN_vkGetBufferMemoryRequirements fp_vkGetBufferMemoryRequirements = nullptr;
    PFN_vkBindBufferMemory fp_vkBindBufferMemory = nullptr;
    PFN_vkGetImageMemoryRequirements fp_vkGetImageMemoryRequirements = nullptr;
    PFN_vkBindImageMemory fp_vkBindImageMemory = nullptr;
    PFN_vkGetImageSparseMemoryRequirements fp_vkGetImageSparseMemoryRequirements = nullptr;
    PFN_vkQueueBindSparse fp_vkQueueBindSparse = nullptr;
    PFN_vkCreateFence fp_vkCreateFence = nullptr;
    PFN_vkDestroyFence fp_vkDestroyFence = nullptr;
    PFN_vkResetFences fp_vkResetFences = nullptr;
    PFN_vkGetFenceStatus fp_vkGetFenceStatus = nullptr;
    PFN_vkWaitForFences fp_vkWaitForFences = nullptr;
    PFN_vkCreateSemaphore fp_vkCreateSemaphore = nullptr;
    PFN_vkDestroySemaphore fp_vkDestroySemaphore = nullptr;
    PFN_vkCreateEvent fp_vkCreateEvent = nullptr;
    PFN_vkDestroyEvent fp_vkDestroyEvent = nullptr;
    PFN_vkGetEventStatus fp_vkGetEventStatus = nullptr;
    PFN_vkSetEvent fp_vkSetEvent = nullptr;
    PFN_vkResetEvent fp_vkResetEvent = nullptr;
    PFN_vkCreateQueryPool fp_vkCreateQueryPool = nullptr;
    PFN_vkDestroyQueryPool fp_vkDestroyQueryPool = nullptr;
    PFN_vkGetQueryPoolResults fp_vkGetQueryPoolResults = nullptr;
#if (defined(VK_VERSION_1_2))
    PFN_vkResetQueryPool fp_vkResetQueryPool = nullptr;
#else
    void * fp_vkResetQueryPool{};
#endif
    PFN_vkCreateBuffer fp_vkCreateBuffer = nullptr;
    PFN_vkDestroyBuffer fp_vkDestroyBuffer = nullptr;
    PFN_vkCreateBufferView fp_vkCreateBufferView = nullptr;
    PFN_vkDestroyBufferView fp_vkDestroyBufferView = nullptr;
    PFN_vkCreateImage fp_vkCreateImage = nullptr;
    PFN_vkDestroyImage fp_vkDestroyImage = nullptr;
    PFN_vkGetImageSubresourceLayout fp_vkGetImageSubresourceLayout = nullptr;
    PFN_vkCreateImageView fp_vkCreateImageView = nullptr;
    PFN_vkDestroyImageView fp_vkDestroyImageView = nullptr;
    PFN_vkCreateShaderModule fp_vkCreateShaderModule = nullptr;
    PFN_vkDestroyShaderModule fp_vkDestroyShaderModule = nullptr;
    PFN_vkCreatePipelineCache fp_vkCreatePipelineCache = nullptr;
    PFN_vkDestroyPipelineCache fp_vkDestroyPipelineCache = nullptr;
    PFN_vkGetPipelineCacheData fp_vkGetPipelineCacheData = nullptr;
    PFN_vkMergePipelineCaches fp_vkMergePipelineCaches = nullptr;
    PFN_vkCreateGraphicsPipelines fp_vkCreateGraphicsPipelines = nullptr;
    PFN_vkCreateComputePipelines fp_vkCreateComputePipelines = nullptr;
#if (defined(VK_HUAWEI_subpass_shading))
    PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI fp_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI = nullptr;
#else
    void * fp_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI{};
#endif
    PFN_vkDestroyPipeline fp_vkDestroyPipeline = nullptr;
    PFN_vkCreatePipelineLayout fp_vkCreatePipelineLayout = nullptr;
    PFN_vkDestroyPipelineLayout fp_vkDestroyPipelineLayout = nullptr;
    PFN_vkCreateSampler fp_vkCreateSampler = nullptr;
    PFN_vkDestroySampler fp_vkDestroySampler = nullptr;
    PFN_vkCreateDescriptorSetLayout fp_vkCreateDescriptorSetLayout = nullptr;
    PFN_vkDestroyDescriptorSetLayout fp_vkDestroyDescriptorSetLayout = nullptr;
    PFN_vkCreateDescriptorPool fp_vkCreateDescriptorPool = nullptr;
    PFN_vkDestroyDescriptorPool fp_vkDestroyDescriptorPool = nullptr;
    PFN_vkResetDescriptorPool fp_vkResetDescriptorPool = nullptr;
    PFN_vkAllocateDescriptorSets fp_vkAllocateDescriptorSets = nullptr;
    PFN_vkFreeDescriptorSets fp_vkFreeDescriptorSets = nullptr;
    PFN_vkUpdateDescriptorSets fp_vkUpdateDescriptorSets = nullptr;
    PFN_vkCreateFramebuffer fp_vkCreateFramebuffer = nullptr;
    PFN_vkDestroyFramebuffer fp_vkDestroyFramebuffer = nullptr;
    PFN_vkCreateRenderPass fp_vkCreateRenderPass = nullptr;
    PFN_vkDestroyRenderPass fp_vkDestroyRenderPass = nullptr;
    PFN_vkGetRenderAreaGranularity fp_vkGetRenderAreaGranularity = nullptr;
#if (defined(VK_KHR_maintenance5))
    PFN_vkGetRenderingAreaGranularityKHR fp_vkGetRenderingAreaGranularityKHR = nullptr;
#else
    void * fp_vkGetRenderingAreaGranularityKHR{};
#endif
    PFN_vkCreateCommandPool fp_vkCreateCommandPool = nullptr;
    PFN_vkDestroyCommandPool fp_vkDestroyCommandPool = nullptr;
    PFN_vkResetCommandPool fp_vkResetCommandPool = nullptr;
    PFN_vkAllocateCommandBuffers fp_vkAllocateCommandBuffers = nullptr;
    PFN_vkFreeCommandBuffers fp_vkFreeCommandBuffers = nullptr;
    PFN_vkBeginCommandBuffer fp_vkBeginCommandBuffer = nullptr;
    PFN_vkEndCommandBuffer fp_vkEndCommandBuffer = nullptr;
    PFN_vkResetCommandBuffer fp_vkResetCommandBuffer = nullptr;
    PFN_vkCmdBindPipeline fp_vkCmdBindPipeline = nullptr;
#if (defined(VK_EXT_attachment_feedback_loop_dynamic_state))
    PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT fp_vkCmdSetAttachmentFeedbackLoopEnableEXT = nullptr;
#else
    void * fp_vkCmdSetAttachmentFeedbackLoopEnableEXT{};
#endif
    PFN_vkCmdSetViewport fp_vkCmdSetViewport = nullptr;
    PFN_vkCmdSetScissor fp_vkCmdSetScissor = nullptr;
    PFN_vkCmdSetLineWidth fp_vkCmdSetLineWidth = nullptr;
    PFN_vkCmdSetDepthBias fp_vkCmdSetDepthBias = nullptr;
    PFN_vkCmdSetBlendConstants fp_vkCmdSetBlendConstants = nullptr;
    PFN_vkCmdSetDepthBounds fp_vkCmdSetDepthBounds = nullptr;
    PFN_vkCmdSetStencilCompareMask fp_vkCmdSetStencilCompareMask = nullptr;
    PFN_vkCmdSetStencilWriteMask fp_vkCmdSetStencilWriteMask = nullptr;
    PFN_vkCmdSetStencilReference fp_vkCmdSetStencilReference = nullptr;
    PFN_vkCmdBindDescriptorSets fp_vkCmdBindDescriptorSets = nullptr;
    PFN_vkCmdBindIndexBuffer fp_vkCmdBindIndexBuffer = nullptr;
    PFN_vkCmdBindVertexBuffers fp_vkCmdBindVertexBuffers = nullptr;
    PFN_vkCmdDraw fp_vkCmdDraw = nullptr;
    PFN_vkCmdDrawIndexed fp_vkCmdDrawIndexed = nullptr;
#if (defined(VK_EXT_multi_draw))
    PFN_vkCmdDrawMultiEXT fp_vkCmdDrawMultiEXT = nullptr;
#else
    void * fp_vkCmdDrawMultiEXT{};
#endif
#if (defined(VK_EXT_multi_draw))
    PFN_vkCmdDrawMultiIndexedEXT fp_vkCmdDrawMultiIndexedEXT = nullptr;
#else
    void * fp_vkCmdDrawMultiIndexedEXT{};
#endif
    PFN_vkCmdDrawIndirect fp_vkCmdDrawIndirect = nullptr;
    PFN_vkCmdDrawIndexedIndirect fp_vkCmdDrawIndexedIndirect = nullptr;
    PFN_vkCmdDispatch fp_vkCmdDispatch = nullptr;
    PFN_vkCmdDispatchIndirect fp_vkCmdDispatchIndirect = nullptr;
#if (defined(VK_HUAWEI_subpass_shading))
    PFN_vkCmdSubpassShadingHUAWEI fp_vkCmdSubpassShadingHUAWEI = nullptr;
#else
    void * fp_vkCmdSubpassShadingHUAWEI{};
#endif
#if (defined(VK_HUAWEI_cluster_culling_shader))
    PFN_vkCmdDrawClusterHUAWEI fp_vkCmdDrawClusterHUAWEI = nullptr;
#else
    void * fp_vkCmdDrawClusterHUAWEI{};
#endif
#if (defined(VK_HUAWEI_cluster_culling_shader))
    PFN_vkCmdDrawClusterIndirectHUAWEI fp_vkCmdDrawClusterIndirectHUAWEI = nullptr;
#else
    void * fp_vkCmdDrawClusterIndirectHUAWEI{};
#endif
#if (defined(VK_NV_device_generated_commands_compute))
    PFN_vkCmdUpdatePipelineIndirectBufferNV fp_vkCmdUpdatePipelineIndirectBufferNV = nullptr;
#else
    void * fp_vkCmdUpdatePipelineIndirectBufferNV{};
#endif
    PFN_vkCmdCopyBuffer fp_vkCmdCopyBuffer = nullptr;
    PFN_vkCmdCopyImage fp_vkCmdCopyImage = nullptr;
    PFN_vkCmdBlitImage fp_vkCmdBlitImage = nullptr;
    PFN_vkCmdCopyBufferToImage fp_vkCmdCopyBufferToImage = nullptr;
    PFN_vkCmdCopyImageToBuffer fp_vkCmdCopyImageToBuffer = nullptr;
#if (defined(VK_NV_copy_memory_indirect))
    PFN_vkCmdCopyMemoryIndirectNV fp_vkCmdCopyMemoryIndirectNV = nullptr;
#else
    void * fp_vkCmdCopyMemoryIndirectNV{};
#endif
#if (defined(VK_NV_copy_memory_indirect))
    PFN_vkCmdCopyMemoryToImageIndirectNV fp_vkCmdCopyMemoryToImageIndirectNV = nullptr;
#else
    void * fp_vkCmdCopyMemoryToImageIndirectNV{};
#endif
    PFN_vkCmdUpdateBuffer fp_vkCmdUpdateBuffer = nullptr;
    PFN_vkCmdFillBuffer fp_vkCmdFillBuffer = nullptr;
    PFN_vkCmdClearColorImage fp_vkCmdClearColorImage = nullptr;
    PFN_vkCmdClearDepthStencilImage fp_vkCmdClearDepthStencilImage = nullptr;
    PFN_vkCmdClearAttachments fp_vkCmdClearAttachments = nullptr;
    PFN_vkCmdResolveImage fp_vkCmdResolveImage = nullptr;
    PFN_vkCmdSetEvent fp_vkCmdSetEvent = nullptr;
    PFN_vkCmdResetEvent fp_vkCmdResetEvent = nullptr;
    PFN_vkCmdWaitEvents fp_vkCmdWaitEvents = nullptr;
    PFN_vkCmdPipelineBarrier fp_vkCmdPipelineBarrier = nullptr;
    PFN_vkCmdBeginQuery fp_vkCmdBeginQuery = nullptr;
    PFN_vkCmdEndQuery fp_vkCmdEndQuery = nullptr;
#if (defined(VK_EXT_conditional_rendering))
    PFN_vkCmdBeginConditionalRenderingEXT fp_vkCmdBeginConditionalRenderingEXT = nullptr;
#else
    void * fp_vkCmdBeginConditionalRenderingEXT{};
#endif
#if (defined(VK_EXT_conditional_rendering))
    PFN_vkCmdEndConditionalRenderingEXT fp_vkCmdEndConditionalRenderingEXT = nullptr;
#else
    void * fp_vkCmdEndConditionalRenderingEXT{};
#endif
    PFN_vkCmdResetQueryPool fp_vkCmdResetQueryPool = nullptr;
    PFN_vkCmdWriteTimestamp fp_vkCmdWriteTimestamp = nullptr;
    PFN_vkCmdCopyQueryPoolResults fp_vkCmdCopyQueryPoolResults = nullptr;
    PFN_vkCmdPushConstants fp_vkCmdPushConstants = nullptr;
    PFN_vkCmdBeginRenderPass fp_vkCmdBeginRenderPass = nullptr;
    PFN_vkCmdNextSubpass fp_vkCmdNextSubpass = nullptr;
    PFN_vkCmdEndRenderPass fp_vkCmdEndRenderPass = nullptr;
    PFN_vkCmdExecuteCommands fp_vkCmdExecuteCommands = nullptr;
#if (defined(VK_KHR_display_swapchain))
    PFN_vkCreateSharedSwapchainsKHR fp_vkCreateSharedSwapchainsKHR = nullptr;
#else
    void * fp_vkCreateSharedSwapchainsKHR{};
#endif
#if (defined(VK_KHR_swapchain))
    PFN_vkCreateSwapchainKHR fp_vkCreateSwapchainKHR = nullptr;
#else
    void * fp_vkCreateSwapchainKHR{};
#endif
#if (defined(VK_KHR_swapchain))
    PFN_vkDestroySwapchainKHR fp_vkDestroySwapchainKHR = nullptr;
#else
    void * fp_vkDestroySwapchainKHR{};
#endif
#if (defined(VK_KHR_swapchain))
    PFN_vkGetSwapchainImagesKHR fp_vkGetSwapchainImagesKHR = nullptr;
#else
    void * fp_vkGetSwapchainImagesKHR{};
#endif
#if (defined(VK_KHR_swapchain))
    PFN_vkAcquireNextImageKHR fp_vkAcquireNextImageKHR = nullptr;
#else
    void * fp_vkAcquireNextImageKHR{};
#endif
#if (defined(VK_KHR_swapchain))
    PFN_vkQueuePresentKHR fp_vkQueuePresentKHR = nullptr;
#else
    void * fp_vkQueuePresentKHR{};
#endif
#if (defined(VK_EXT_debug_marker))
    PFN_vkDebugMarkerSetObjectNameEXT fp_vkDebugMarkerSetObjectNameEXT = nullptr;
#else
    void * fp_vkDebugMarkerSetObjectNameEXT{};
#endif
#if (defined(VK_EXT_debug_marker))
    PFN_vkDebugMarkerSetObjectTagEXT fp_vkDebugMarkerSetObjectTagEXT = nullptr;
#else
    void * fp_vkDebugMarkerSetObjectTagEXT{};
#endif
#if (defined(VK_EXT_debug_marker))
    PFN_vkCmdDebugMarkerBeginEXT fp_vkCmdDebugMarkerBeginEXT = nullptr;
#else
    void * fp_vkCmdDebugMarkerBeginEXT{};
#endif
#if (defined(VK_EXT_debug_marker))
    PFN_vkCmdDebugMarkerEndEXT fp_vkCmdDebugMarkerEndEXT = nullptr;
#else
    void * fp_vkCmdDebugMarkerEndEXT{};
#endif
#if (defined(VK_EXT_debug_marker))
    PFN_vkCmdDebugMarkerInsertEXT fp_vkCmdDebugMarkerInsertEXT = nullptr;
#else
    void * fp_vkCmdDebugMarkerInsertEXT{};
#endif
#if (defined(VK_NV_external_memory_win32))
    PFN_vkGetMemoryWin32HandleNV fp_vkGetMemoryWin32HandleNV = nullptr;
#else
    void * fp_vkGetMemoryWin32HandleNV{};
#endif
#if (defined(VK_NV_device_generated_commands))
    PFN_vkCmdExecuteGeneratedCommandsNV fp_vkCmdExecuteGeneratedCommandsNV = nullptr;
#else
    void * fp_vkCmdExecuteGeneratedCommandsNV{};
#endif
#if (defined(VK_NV_device_generated_commands))
    PFN_vkCmdPreprocessGeneratedCommandsNV fp_vkCmdPreprocessGeneratedCommandsNV = nullptr;
#else
    void * fp_vkCmdPreprocessGeneratedCommandsNV{};
#endif
#if (defined(VK_NV_device_generated_commands))
    PFN_vkCmdBindPipelineShaderGroupNV fp_vkCmdBindPipelineShaderGroupNV = nullptr;
#else
    void * fp_vkCmdBindPipelineShaderGroupNV{};
#endif
#if (defined(VK_NV_device_generated_commands))
    PFN_vkGetGeneratedCommandsMemoryRequirementsNV fp_vkGetGeneratedCommandsMemoryRequirementsNV = nullptr;
#else
    void * fp_vkGetGeneratedCommandsMemoryRequirementsNV{};
#endif
#if (defined(VK_NV_device_generated_commands))
    PFN_vkCreateIndirectCommandsLayoutNV fp_vkCreateIndirectCommandsLayoutNV = nullptr;
#else
    void * fp_vkCreateIndirectCommandsLayoutNV{};
#endif
#if (defined(VK_NV_device_generated_commands))
    PFN_vkDestroyIndirectCommandsLayoutNV fp_vkDestroyIndirectCommandsLayoutNV = nullptr;
#else
    void * fp_vkDestroyIndirectCommandsLayoutNV{};
#endif
#if (defined(VK_KHR_push_descriptor))
    PFN_vkCmdPushDescriptorSetKHR fp_vkCmdPushDescriptorSetKHR = nullptr;
#else
    void * fp_vkCmdPushDescriptorSetKHR{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkTrimCommandPool fp_vkTrimCommandPool = nullptr;
#else
    void * fp_vkTrimCommandPool{};
#endif
#if (defined(VK_KHR_external_memory_win32))
    PFN_vkGetMemoryWin32HandleKHR fp_vkGetMemoryWin32HandleKHR = nullptr;
#else
    void * fp_vkGetMemoryWin32HandleKHR{};
#endif
#if (defined(VK_KHR_external_memory_win32))
    PFN_vkGetMemoryWin32HandlePropertiesKHR fp_vkGetMemoryWin32HandlePropertiesKHR = nullptr;
#else
    void * fp_vkGetMemoryWin32HandlePropertiesKHR{};
#endif
#if (defined(VK_KHR_external_memory_fd))
    PFN_vkGetMemoryFdKHR fp_vkGetMemoryFdKHR = nullptr;
#else
    void * fp_vkGetMemoryFdKHR{};
#endif
#if (defined(VK_KHR_external_memory_fd))
    PFN_vkGetMemoryFdPropertiesKHR fp_vkGetMemoryFdPropertiesKHR = nullptr;
#else
    void * fp_vkGetMemoryFdPropertiesKHR{};
#endif
#if (defined(VK_FUCHSIA_external_memory))
    PFN_vkGetMemoryZirconHandleFUCHSIA fp_vkGetMemoryZirconHandleFUCHSIA = nullptr;
#else
    void * fp_vkGetMemoryZirconHandleFUCHSIA{};
#endif
#if (defined(VK_FUCHSIA_external_memory))
    PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA fp_vkGetMemoryZirconHandlePropertiesFUCHSIA = nullptr;
#else
    void * fp_vkGetMemoryZirconHandlePropertiesFUCHSIA{};
#endif
#if (defined(VK_NV_external_memory_rdma))
    PFN_vkGetMemoryRemoteAddressNV fp_vkGetMemoryRemoteAddressNV = nullptr;
#else
    void * fp_vkGetMemoryRemoteAddressNV{};
#endif
#if (defined(VK_NV_external_memory_sci_buf))
    PFN_vkGetMemorySciBufNV fp_vkGetMemorySciBufNV = nullptr;
#else
    void * fp_vkGetMemorySciBufNV{};
#endif
#if (defined(VK_KHR_external_semaphore_win32))
    PFN_vkGetSemaphoreWin32HandleKHR fp_vkGetSemaphoreWin32HandleKHR = nullptr;
#else
    void * fp_vkGetSemaphoreWin32HandleKHR{};
#endif
#if (defined(VK_KHR_external_semaphore_win32))
    PFN_vkImportSemaphoreWin32HandleKHR fp_vkImportSemaphoreWin32HandleKHR = nullptr;
#else
    void * fp_vkImportSemaphoreWin32HandleKHR{};
#endif
#if (defined(VK_KHR_external_semaphore_fd))
    PFN_vkGetSemaphoreFdKHR fp_vkGetSemaphoreFdKHR = nullptr;
#else
    void * fp_vkGetSemaphoreFdKHR{};
#endif
#if (defined(VK_KHR_external_semaphore_fd))
    PFN_vkImportSemaphoreFdKHR fp_vkImportSemaphoreFdKHR = nullptr;
#else
    void * fp_vkImportSemaphoreFdKHR{};
#endif
#if (defined(VK_FUCHSIA_external_semaphore))
    PFN_vkGetSemaphoreZirconHandleFUCHSIA fp_vkGetSemaphoreZirconHandleFUCHSIA = nullptr;
#else
    void * fp_vkGetSemaphoreZirconHandleFUCHSIA{};
#endif
#if (defined(VK_FUCHSIA_external_semaphore))
    PFN_vkImportSemaphoreZirconHandleFUCHSIA fp_vkImportSemaphoreZirconHandleFUCHSIA = nullptr;
#else
    void * fp_vkImportSemaphoreZirconHandleFUCHSIA{};
#endif
#if (defined(VK_KHR_external_fence_win32))
    PFN_vkGetFenceWin32HandleKHR fp_vkGetFenceWin32HandleKHR = nullptr;
#else
    void * fp_vkGetFenceWin32HandleKHR{};
#endif
#if (defined(VK_KHR_external_fence_win32))
    PFN_vkImportFenceWin32HandleKHR fp_vkImportFenceWin32HandleKHR = nullptr;
#else
    void * fp_vkImportFenceWin32HandleKHR{};
#endif
#if (defined(VK_KHR_external_fence_fd))
    PFN_vkGetFenceFdKHR fp_vkGetFenceFdKHR = nullptr;
#else
    void * fp_vkGetFenceFdKHR{};
#endif
#if (defined(VK_KHR_external_fence_fd))
    PFN_vkImportFenceFdKHR fp_vkImportFenceFdKHR = nullptr;
#else
    void * fp_vkImportFenceFdKHR{};
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
    PFN_vkGetFenceSciSyncFenceNV fp_vkGetFenceSciSyncFenceNV = nullptr;
#else
    void * fp_vkGetFenceSciSyncFenceNV{};
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
    PFN_vkGetFenceSciSyncObjNV fp_vkGetFenceSciSyncObjNV = nullptr;
#else
    void * fp_vkGetFenceSciSyncObjNV{};
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
    PFN_vkImportFenceSciSyncFenceNV fp_vkImportFenceSciSyncFenceNV = nullptr;
#else
    void * fp_vkImportFenceSciSyncFenceNV{};
#endif
#if (defined(VK_NV_external_sci_sync)) || (defined(VK_NV_external_sci_sync2))
    PFN_vkImportFenceSciSyncObjNV fp_vkImportFenceSciSyncObjNV = nullptr;
#else
    void * fp_vkImportFenceSciSyncObjNV{};
#endif
#if (defined(VK_NV_external_sci_sync))
    PFN_vkGetSemaphoreSciSyncObjNV fp_vkGetSemaphoreSciSyncObjNV = nullptr;
#else
    void * fp_vkGetSemaphoreSciSyncObjNV{};
#endif
#if (defined(VK_NV_external_sci_sync))
    PFN_vkImportSemaphoreSciSyncObjNV fp_vkImportSemaphoreSciSyncObjNV = nullptr;
#else
    void * fp_vkImportSemaphoreSciSyncObjNV{};
#endif
#if (defined(VK_NV_external_sci_sync2))
    PFN_vkCreateSemaphoreSciSyncPoolNV fp_vkCreateSemaphoreSciSyncPoolNV = nullptr;
#else
    void * fp_vkCreateSemaphoreSciSyncPoolNV{};
#endif
#if (defined(VK_NV_external_sci_sync2))
    PFN_vkDestroySemaphoreSciSyncPoolNV fp_vkDestroySemaphoreSciSyncPoolNV = nullptr;
#else
    void * fp_vkDestroySemaphoreSciSyncPoolNV{};
#endif
#if (defined(VK_EXT_display_control))
    PFN_vkDisplayPowerControlEXT fp_vkDisplayPowerControlEXT = nullptr;
#else
    void * fp_vkDisplayPowerControlEXT{};
#endif
#if (defined(VK_EXT_display_control))
    PFN_vkRegisterDeviceEventEXT fp_vkRegisterDeviceEventEXT = nullptr;
#else
    void * fp_vkRegisterDeviceEventEXT{};
#endif
#if (defined(VK_EXT_display_control))
    PFN_vkRegisterDisplayEventEXT fp_vkRegisterDisplayEventEXT = nullptr;
#else
    void * fp_vkRegisterDisplayEventEXT{};
#endif
#if (defined(VK_EXT_display_control))
    PFN_vkGetSwapchainCounterEXT fp_vkGetSwapchainCounterEXT = nullptr;
#else
    void * fp_vkGetSwapchainCounterEXT{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetDeviceGroupPeerMemoryFeatures fp_vkGetDeviceGroupPeerMemoryFeatures = nullptr;
#else
    void * fp_vkGetDeviceGroupPeerMemoryFeatures{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkBindBufferMemory2 fp_vkBindBufferMemory2 = nullptr;
#else
    void * fp_vkBindBufferMemory2{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkBindImageMemory2 fp_vkBindImageMemory2 = nullptr;
#else
    void * fp_vkBindImageMemory2{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkCmdSetDeviceMask fp_vkCmdSetDeviceMask = nullptr;
#else
    void * fp_vkCmdSetDeviceMask{};
#endif
#if (defined(VK_KHR_swapchain)) || (defined(VK_KHR_device_group))
    PFN_vkGetDeviceGroupPresentCapabilitiesKHR fp_vkGetDeviceGroupPresentCapabilitiesKHR = nullptr;
#else
    void * fp_vkGetDeviceGroupPresentCapabilitiesKHR{};
#endif
#if (defined(VK_KHR_swapchain)) || (defined(VK_KHR_device_group))
    PFN_vkGetDeviceGroupSurfacePresentModesKHR fp_vkGetDeviceGroupSurfacePresentModesKHR = nullptr;
#else
    void * fp_vkGetDeviceGroupSurfacePresentModesKHR{};
#endif
#if (defined(VK_KHR_swapchain)) || (defined(VK_KHR_device_group))
    PFN_vkAcquireNextImage2KHR fp_vkAcquireNextImage2KHR = nullptr;
#else
    void * fp_vkAcquireNextImage2KHR{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkCmdDispatchBase fp_vkCmdDispatchBase = nullptr;
#else
    void * fp_vkCmdDispatchBase{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkCreateDescriptorUpdateTemplate fp_vkCreateDescriptorUpdateTemplate = nullptr;
#else
    void * fp_vkCreateDescriptorUpdateTemplate{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkDestroyDescriptorUpdateTemplate fp_vkDestroyDescriptorUpdateTemplate = nullptr;
#else
    void * fp_vkDestroyDescriptorUpdateTemplate{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkUpdateDescriptorSetWithTemplate fp_vkUpdateDescriptorSetWithTemplate = nullptr;
#else
    void * fp_vkUpdateDescriptorSetWithTemplate{};
#endif
#if (defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_push_descriptor)) || (defined(VK_KHR_descriptor_update_template))
    PFN_vkCmdPushDescriptorSetWithTemplateKHR fp_vkCmdPushDescriptorSetWithTemplateKHR = nullptr;
#else
    void * fp_vkCmdPushDescriptorSetWithTemplateKHR{};
#endif
#if (defined(VK_EXT_hdr_metadata))
    PFN_vkSetHdrMetadataEXT fp_vkSetHdrMetadataEXT = nullptr;
#else
    void * fp_vkSetHdrMetadataEXT{};
#endif
#if (defined(VK_KHR_shared_presentable_image))
    PFN_vkGetSwapchainStatusKHR fp_vkGetSwapchainStatusKHR = nullptr;
#else
    void * fp_vkGetSwapchainStatusKHR{};
#endif
#if (defined(VK_GOOGLE_display_timing))
    PFN_vkGetRefreshCycleDurationGOOGLE fp_vkGetRefreshCycleDurationGOOGLE = nullptr;
#else
    void * fp_vkGetRefreshCycleDurationGOOGLE{};
#endif
#if (defined(VK_GOOGLE_display_timing))
    PFN_vkGetPastPresentationTimingGOOGLE fp_vkGetPastPresentationTimingGOOGLE = nullptr;
#else
    void * fp_vkGetPastPresentationTimingGOOGLE{};
#endif
#if (defined(VK_NV_clip_space_w_scaling))
    PFN_vkCmdSetViewportWScalingNV fp_vkCmdSetViewportWScalingNV = nullptr;
#else
    void * fp_vkCmdSetViewportWScalingNV{};
#endif
#if (defined(VK_EXT_discard_rectangles))
    PFN_vkCmdSetDiscardRectangleEXT fp_vkCmdSetDiscardRectangleEXT = nullptr;
#else
    void * fp_vkCmdSetDiscardRectangleEXT{};
#endif
#if ((defined(VK_EXT_discard_rectangles))) && VK_HEADER_VERSION >= 241
    PFN_vkCmdSetDiscardRectangleEnableEXT fp_vkCmdSetDiscardRectangleEnableEXT = nullptr;
#else
    void * fp_vkCmdSetDiscardRectangleEnableEXT{};
#endif
#if ((defined(VK_EXT_discard_rectangles))) && VK_HEADER_VERSION >= 241
    PFN_vkCmdSetDiscardRectangleModeEXT fp_vkCmdSetDiscardRectangleModeEXT = nullptr;
#else
    void * fp_vkCmdSetDiscardRectangleModeEXT{};
#endif
#if (defined(VK_EXT_sample_locations))
    PFN_vkCmdSetSampleLocationsEXT fp_vkCmdSetSampleLocationsEXT = nullptr;
#else
    void * fp_vkCmdSetSampleLocationsEXT{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetBufferMemoryRequirements2 fp_vkGetBufferMemoryRequirements2 = nullptr;
#else
    void * fp_vkGetBufferMemoryRequirements2{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetImageMemoryRequirements2 fp_vkGetImageMemoryRequirements2 = nullptr;
#else
    void * fp_vkGetImageMemoryRequirements2{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetImageSparseMemoryRequirements2 fp_vkGetImageSparseMemoryRequirements2 = nullptr;
#else
    void * fp_vkGetImageSparseMemoryRequirements2{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkGetDeviceBufferMemoryRequirements fp_vkGetDeviceBufferMemoryRequirements = nullptr;
#else
    void * fp_vkGetDeviceBufferMemoryRequirements{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkGetDeviceImageMemoryRequirements fp_vkGetDeviceImageMemoryRequirements = nullptr;
#else
    void * fp_vkGetDeviceImageMemoryRequirements{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkGetDeviceImageSparseMemoryRequirements fp_vkGetDeviceImageSparseMemoryRequirements = nullptr;
#else
    void * fp_vkGetDeviceImageSparseMemoryRequirements{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkCreateSamplerYcbcrConversion fp_vkCreateSamplerYcbcrConversion = nullptr;
#else
    void * fp_vkCreateSamplerYcbcrConversion{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkDestroySamplerYcbcrConversion fp_vkDestroySamplerYcbcrConversion = nullptr;
#else
    void * fp_vkDestroySamplerYcbcrConversion{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetDeviceQueue2 fp_vkGetDeviceQueue2 = nullptr;
#else
    void * fp_vkGetDeviceQueue2{};
#endif
#if (defined(VK_EXT_validation_cache))
    PFN_vkCreateValidationCacheEXT fp_vkCreateValidationCacheEXT = nullptr;
#else
    void * fp_vkCreateValidationCacheEXT{};
#endif
#if (defined(VK_EXT_validation_cache))
    PFN_vkDestroyValidationCacheEXT fp_vkDestroyValidationCacheEXT = nullptr;
#else
    void * fp_vkDestroyValidationCacheEXT{};
#endif
#if (defined(VK_EXT_validation_cache))
    PFN_vkGetValidationCacheDataEXT fp_vkGetValidationCacheDataEXT = nullptr;
#else
    void * fp_vkGetValidationCacheDataEXT{};
#endif
#if (defined(VK_EXT_validation_cache))
    PFN_vkMergeValidationCachesEXT fp_vkMergeValidationCachesEXT = nullptr;
#else
    void * fp_vkMergeValidationCachesEXT{};
#endif
#if (defined(VK_VERSION_1_1))
    PFN_vkGetDescriptorSetLayoutSupport fp_vkGetDescriptorSetLayoutSupport = nullptr;
#else
    void * fp_vkGetDescriptorSetLayoutSupport{};
#endif
#if (defined(VK_ANDROID_native_buffer))
    PFN_vkGetSwapchainGrallocUsageANDROID fp_vkGetSwapchainGrallocUsageANDROID = nullptr;
#else
    void * fp_vkGetSwapchainGrallocUsageANDROID{};
#endif
#if (defined(VK_ANDROID_native_buffer))
    PFN_vkGetSwapchainGrallocUsage2ANDROID fp_vkGetSwapchainGrallocUsage2ANDROID = nullptr;
#else
    void * fp_vkGetSwapchainGrallocUsage2ANDROID{};
#endif
#if (defined(VK_ANDROID_native_buffer))
    PFN_vkAcquireImageANDROID fp_vkAcquireImageANDROID = nullptr;
#else
    void * fp_vkAcquireImageANDROID{};
#endif
#if (defined(VK_ANDROID_native_buffer))
    PFN_vkQueueSignalReleaseImageANDROID fp_vkQueueSignalReleaseImageANDROID = nullptr;
#else
    void * fp_vkQueueSignalReleaseImageANDROID{};
#endif
#if (defined(VK_AMD_shader_info))
    PFN_vkGetShaderInfoAMD fp_vkGetShaderInfoAMD = nullptr;
#else
    void * fp_vkGetShaderInfoAMD{};
#endif
#if (defined(VK_AMD_display_native_hdr))
    PFN_vkSetLocalDimmingAMD fp_vkSetLocalDimmingAMD = nullptr;
#else
    void * fp_vkSetLocalDimmingAMD{};
#endif
#if (defined(VK_KHR_calibrated_timestamps))
    PFN_vkGetCalibratedTimestampsKHR fp_vkGetCalibratedTimestampsKHR = nullptr;
#else
    void * fp_vkGetCalibratedTimestampsKHR{};
#endif
#if (defined(VK_EXT_debug_utils))
    PFN_vkSetDebugUtilsObjectNameEXT fp_vkSetDebugUtilsObjectNameEXT = nullptr;
#else
    void * fp_vkSetDebugUtilsObjectNameEXT{};
#endif
#if (defined(VK_EXT_debug_utils))
    PFN_vkSetDebugUtilsObjectTagEXT fp_vkSetDebugUtilsObjectTagEXT = nullptr;
#else
    void * fp_vkSetDebugUtilsObjectTagEXT{};
#endif
#if (defined(VK_EXT_debug_utils))
    PFN_vkQueueBeginDebugUtilsLabelEXT fp_vkQueueBeginDebugUtilsLabelEXT = nullptr;
#else
    void * fp_vkQueueBeginDebugUtilsLabelEXT{};
#endif
#if (defined(VK_EXT_debug_utils))
    PFN_vkQueueEndDebugUtilsLabelEXT fp_vkQueueEndDebugUtilsLabelEXT = nullptr;
#else
    void * fp_vkQueueEndDebugUtilsLabelEXT{};
#endif
#if (defined(VK_EXT_debug_utils))
    PFN_vkQueueInsertDebugUtilsLabelEXT fp_vkQueueInsertDebugUtilsLabelEXT = nullptr;
#else
    void * fp_vkQueueInsertDebugUtilsLabelEXT{};
#endif
#if (defined(VK_EXT_debug_utils))
    PFN_vkCmdBeginDebugUtilsLabelEXT fp_vkCmdBeginDebugUtilsLabelEXT = nullptr;
#else
    void * fp_vkCmdBeginDebugUtilsLabelEXT{};
#endif
#if (defined(VK_EXT_debug_utils))
    PFN_vkCmdEndDebugUtilsLabelEXT fp_vkCmdEndDebugUtilsLabelEXT = nullptr;
#else
    void * fp_vkCmdEndDebugUtilsLabelEXT{};
#endif
#if (defined(VK_EXT_debug_utils))
    PFN_vkCmdInsertDebugUtilsLabelEXT fp_vkCmdInsertDebugUtilsLabelEXT = nullptr;
#else
    void * fp_vkCmdInsertDebugUtilsLabelEXT{};
#endif
#if (defined(VK_EXT_external_memory_host))
    PFN_vkGetMemoryHostPointerPropertiesEXT fp_vkGetMemoryHostPointerPropertiesEXT = nullptr;
#else
    void * fp_vkGetMemoryHostPointerPropertiesEXT{};
#endif
#if (defined(VK_AMD_buffer_marker))
    PFN_vkCmdWriteBufferMarkerAMD fp_vkCmdWriteBufferMarkerAMD = nullptr;
#else
    void * fp_vkCmdWriteBufferMarkerAMD{};
#endif
#if (defined(VK_VERSION_1_2))
    PFN_vkCreateRenderPass2 fp_vkCreateRenderPass2 = nullptr;
#else
    void * fp_vkCreateRenderPass2{};
#endif
#if (defined(VK_VERSION_1_2))
    PFN_vkCmdBeginRenderPass2 fp_vkCmdBeginRenderPass2 = nullptr;
#else
    void * fp_vkCmdBeginRenderPass2{};
#endif
#if (defined(VK_VERSION_1_2))
    PFN_vkCmdNextSubpass2 fp_vkCmdNextSubpass2 = nullptr;
#else
    void * fp_vkCmdNextSubpass2{};
#endif
#if (defined(VK_VERSION_1_2))
    PFN_vkCmdEndRenderPass2 fp_vkCmdEndRenderPass2 = nullptr;
#else
    void * fp_vkCmdEndRenderPass2{};
#endif
#if (defined(VK_VERSION_1_2))
    PFN_vkGetSemaphoreCounterValue fp_vkGetSemaphoreCounterValue = nullptr;
#else
    void * fp_vkGetSemaphoreCounterValue{};
#endif
#if (defined(VK_VERSION_1_2))
    PFN_vkWaitSemaphores fp_vkWaitSemaphores = nullptr;
#else
    void * fp_vkWaitSemaphores{};
#endif
#if (defined(VK_VERSION_1_2))
    PFN_vkSignalSemaphore fp_vkSignalSemaphore = nullptr;
#else
    void * fp_vkSignalSemaphore{};
#endif
#if (defined(VK_ANDROID_external_memory_android_hardware_buffer))
    PFN_vkGetAndroidHardwareBufferPropertiesANDROID fp_vkGetAndroidHardwareBufferPropertiesANDROID = nullptr;
#else
    void * fp_vkGetAndroidHardwareBufferPropertiesANDROID{};
#endif
#if (defined(VK_ANDROID_external_memory_android_hardware_buffer))
    PFN_vkGetMemoryAndroidHardwareBufferANDROID fp_vkGetMemoryAndroidHardwareBufferANDROID = nullptr;
#else
    void * fp_vkGetMemoryAndroidHardwareBufferANDROID{};
#endif
#if (defined(VK_VERSION_1_2))
    PFN_vkCmdDrawIndirectCount fp_vkCmdDrawIndirectCount = nullptr;
#else
    void * fp_vkCmdDrawIndirectCount{};
#endif
#if (defined(VK_VERSION_1_2))
    PFN_vkCmdDrawIndexedIndirectCount fp_vkCmdDrawIndexedIndirectCount = nullptr;
#else
    void * fp_vkCmdDrawIndexedIndirectCount{};
#endif
#if (defined(VK_NV_device_diagnostic_checkpoints))
    PFN_vkCmdSetCheckpointNV fp_vkCmdSetCheckpointNV = nullptr;
#else
    void * fp_vkCmdSetCheckpointNV{};
#endif
#if (defined(VK_NV_device_diagnostic_checkpoints))
    PFN_vkGetQueueCheckpointDataNV fp_vkGetQueueCheckpointDataNV = nullptr;
#else
    void * fp_vkGetQueueCheckpointDataNV{};
#endif
#if (defined(VK_EXT_transform_feedback))
    PFN_vkCmdBindTransformFeedbackBuffersEXT fp_vkCmdBindTransformFeedbackBuffersEXT = nullptr;
#else
    void * fp_vkCmdBindTransformFeedbackBuffersEXT{};
#endif
#if (defined(VK_EXT_transform_feedback))
    PFN_vkCmdBeginTransformFeedbackEXT fp_vkCmdBeginTransformFeedbackEXT = nullptr;
#else
    void * fp_vkCmdBeginTransformFeedbackEXT{};
#endif
#if (defined(VK_EXT_transform_feedback))
    PFN_vkCmdEndTransformFeedbackEXT fp_vkCmdEndTransformFeedbackEXT = nullptr;
#else
    void * fp_vkCmdEndTransformFeedbackEXT{};
#endif
#if (defined(VK_EXT_transform_feedback))
    PFN_vkCmdBeginQueryIndexedEXT fp_vkCmdBeginQueryIndexedEXT = nullptr;
#else
    void * fp_vkCmdBeginQueryIndexedEXT{};
#endif
#if (defined(VK_EXT_transform_feedback))
    PFN_vkCmdEndQueryIndexedEXT fp_vkCmdEndQueryIndexedEXT = nullptr;
#else
    void * fp_vkCmdEndQueryIndexedEXT{};
#endif
#if (defined(VK_EXT_transform_feedback))
    PFN_vkCmdDrawIndirectByteCountEXT fp_vkCmdDrawIndirectByteCountEXT = nullptr;
#else
    void * fp_vkCmdDrawIndirectByteCountEXT{};
#endif
#if (defined(VK_NV_scissor_exclusive))
    PFN_vkCmdSetExclusiveScissorNV fp_vkCmdSetExclusiveScissorNV = nullptr;
#else
    void * fp_vkCmdSetExclusiveScissorNV{};
#endif
#if ((defined(VK_NV_scissor_exclusive))) && VK_HEADER_VERSION >= 241
    PFN_vkCmdSetExclusiveScissorEnableNV fp_vkCmdSetExclusiveScissorEnableNV = nullptr;
#else
    void * fp_vkCmdSetExclusiveScissorEnableNV{};
#endif
#if (defined(VK_NV_shading_rate_image))
    PFN_vkCmdBindShadingRateImageNV fp_vkCmdBindShadingRateImageNV = nullptr;
#else
    void * fp_vkCmdBindShadingRateImageNV{};
#endif
#if (defined(VK_NV_shading_rate_image))
    PFN_vkCmdSetViewportShadingRatePaletteNV fp_vkCmdSetViewportShadingRatePaletteNV = nullptr;
#else
    void * fp_vkCmdSetViewportShadingRatePaletteNV{};
#endif
#if (defined(VK_NV_shading_rate_image))
    PFN_vkCmdSetCoarseSampleOrderNV fp_vkCmdSetCoarseSampleOrderNV = nullptr;
#else
    void * fp_vkCmdSetCoarseSampleOrderNV{};
#endif
#if (defined(VK_NV_mesh_shader))
    PFN_vkCmdDrawMeshTasksNV fp_vkCmdDrawMeshTasksNV = nullptr;
#else
    void * fp_vkCmdDrawMeshTasksNV{};
#endif
#if (defined(VK_NV_mesh_shader))
    PFN_vkCmdDrawMeshTasksIndirectNV fp_vkCmdDrawMeshTasksIndirectNV = nullptr;
#else
    void * fp_vkCmdDrawMeshTasksIndirectNV{};
#endif
#if (defined(VK_NV_mesh_shader))
    PFN_vkCmdDrawMeshTasksIndirectCountNV fp_vkCmdDrawMeshTasksIndirectCountNV = nullptr;
#else
    void * fp_vkCmdDrawMeshTasksIndirectCountNV{};
#endif
#if (defined(VK_EXT_mesh_shader))
    PFN_vkCmdDrawMeshTasksEXT fp_vkCmdDrawMeshTasksEXT = nullptr;
#else
    void * fp_vkCmdDrawMeshTasksEXT{};
#endif
#if (defined(VK_EXT_mesh_shader))
    PFN_vkCmdDrawMeshTasksIndirectEXT fp_vkCmdDrawMeshTasksIndirectEXT = nullptr;
#else
    void * fp_vkCmdDrawMeshTasksIndirectEXT{};
#endif
#if (defined(VK_EXT_mesh_shader))
    PFN_vkCmdDrawMeshTasksIndirectCountEXT fp_vkCmdDrawMeshTasksIndirectCountEXT = nullptr;
#else
    void * fp_vkCmdDrawMeshTasksIndirectCountEXT{};
#endif
#if (defined(VK_NV_ray_tracing))
    PFN_vkCompileDeferredNV fp_vkCompileDeferredNV = nullptr;
#else
    void * fp_vkCompileDeferredNV{};
#endif
#if (defined(VK_NV_ray_tracing))
    PFN_vkCreateAccelerationStructureNV fp_vkCreateAccelerationStructureNV = nullptr;
#else
    void * fp_vkCreateAccelerationStructureNV{};
#endif
#if (defined(VK_HUAWEI_invocation_mask))
    PFN_vkCmdBindInvocationMaskHUAWEI fp_vkCmdBindInvocationMaskHUAWEI = nullptr;
#else
    void * fp_vkCmdBindInvocationMaskHUAWEI{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkDestroyAccelerationStructureKHR fp_vkDestroyAccelerationStructureKHR = nullptr;
#else
    void * fp_vkDestroyAccelerationStructureKHR{};
#endif
#if (defined(VK_NV_ray_tracing))
    PFN_vkDestroyAccelerationStructureNV fp_vkDestroyAccelerationStructureNV = nullptr;
#else
    void * fp_vkDestroyAccelerationStructureNV{};
#endif
#if (defined(VK_NV_ray_tracing))
    PFN_vkGetAccelerationStructureMemoryRequirementsNV fp_vkGetAccelerationStructureMemoryRequirementsNV = nullptr;
#else
    void * fp_vkGetAccelerationStructureMemoryRequirementsNV{};
#endif
#if (defined(VK_NV_ray_tracing))
    PFN_vkBindAccelerationStructureMemoryNV fp_vkBindAccelerationStructureMemoryNV = nullptr;
#else
    void * fp_vkBindAccelerationStructureMemoryNV{};
#endif
#if (defined(VK_NV_ray_tracing))
    PFN_vkCmdCopyAccelerationStructureNV fp_vkCmdCopyAccelerationStructureNV = nullptr;
#else
    void * fp_vkCmdCopyAccelerationStructureNV{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkCmdCopyAccelerationStructureKHR fp_vkCmdCopyAccelerationStructureKHR = nullptr;
#else
    void * fp_vkCmdCopyAccelerationStructureKHR{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkCopyAccelerationStructureKHR fp_vkCopyAccelerationStructureKHR = nullptr;
#else
    void * fp_vkCopyAccelerationStructureKHR{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkCmdCopyAccelerationStructureToMemoryKHR fp_vkCmdCopyAccelerationStructureToMemoryKHR = nullptr;
#else
    void * fp_vkCmdCopyAccelerationStructureToMemoryKHR{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkCopyAccelerationStructureToMemoryKHR fp_vkCopyAccelerationStructureToMemoryKHR = nullptr;
#else
    void * fp_vkCopyAccelerationStructureToMemoryKHR{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkCmdCopyMemoryToAccelerationStructureKHR fp_vkCmdCopyMemoryToAccelerationStructureKHR = nullptr;
#else
    void * fp_vkCmdCopyMemoryToAccelerationStructureKHR{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkCopyMemoryToAccelerationStructureKHR fp_vkCopyMemoryToAccelerationStructureKHR = nullptr;
#else
    void * fp_vkCopyMemoryToAccelerationStructureKHR{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkCmdWriteAccelerationStructuresPropertiesKHR fp_vkCmdWriteAccelerationStructuresPropertiesKHR = nullptr;
#else
    void * fp_vkCmdWriteAccelerationStructuresPropertiesKHR{};
#endif
#if (defined(VK_NV_ray_tracing))
    PFN_vkCmdWriteAccelerationStructuresPropertiesNV fp_vkCmdWriteAccelerationStructuresPropertiesNV = nullptr;
#else
    void * fp_vkCmdWriteAccelerationStructuresPropertiesNV{};
#endif
#if (defined(VK_NV_ray_tracing))
    PFN_vkCmdBuildAccelerationStructureNV fp_vkCmdBuildAccelerationStructureNV = nullptr;
#else
    void * fp_vkCmdBuildAccelerationStructureNV{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkWriteAccelerationStructuresPropertiesKHR fp_vkWriteAccelerationStructuresPropertiesKHR = nullptr;
#else
    void * fp_vkWriteAccelerationStructuresPropertiesKHR{};
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
    PFN_vkCmdTraceRaysKHR fp_vkCmdTraceRaysKHR = nullptr;
#else
    void * fp_vkCmdTraceRaysKHR{};
#endif
#if (defined(VK_NV_ray_tracing))
    PFN_vkCmdTraceRaysNV fp_vkCmdTraceRaysNV = nullptr;
#else
    void * fp_vkCmdTraceRaysNV{};
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
    PFN_vkGetRayTracingShaderGroupHandlesKHR fp_vkGetRayTracingShaderGroupHandlesKHR = nullptr;
#else
    void * fp_vkGetRayTracingShaderGroupHandlesKHR{};
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
    PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR fp_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = nullptr;
#else
    void * fp_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR{};
#endif
#if (defined(VK_NV_ray_tracing))
    PFN_vkGetAccelerationStructureHandleNV fp_vkGetAccelerationStructureHandleNV = nullptr;
#else
    void * fp_vkGetAccelerationStructureHandleNV{};
#endif
#if (defined(VK_NV_ray_tracing))
    PFN_vkCreateRayTracingPipelinesNV fp_vkCreateRayTracingPipelinesNV = nullptr;
#else
    void * fp_vkCreateRayTracingPipelinesNV{};
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
    PFN_vkCreateRayTracingPipelinesKHR fp_vkCreateRayTracingPipelinesKHR = nullptr;
#else
    void * fp_vkCreateRayTracingPipelinesKHR{};
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
    PFN_vkCmdTraceRaysIndirectKHR fp_vkCmdTraceRaysIndirectKHR = nullptr;
#else
    void * fp_vkCmdTraceRaysIndirectKHR{};
#endif
#if (defined(VK_KHR_ray_tracing_maintenance1))
    PFN_vkCmdTraceRaysIndirect2KHR fp_vkCmdTraceRaysIndirect2KHR = nullptr;
#else
    void * fp_vkCmdTraceRaysIndirect2KHR{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkGetDeviceAccelerationStructureCompatibilityKHR fp_vkGetDeviceAccelerationStructureCompatibilityKHR = nullptr;
#else
    void * fp_vkGetDeviceAccelerationStructureCompatibilityKHR{};
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
    PFN_vkGetRayTracingShaderGroupStackSizeKHR fp_vkGetRayTracingShaderGroupStackSizeKHR = nullptr;
#else
    void * fp_vkGetRayTracingShaderGroupStackSizeKHR{};
#endif
#if (defined(VK_KHR_ray_tracing_pipeline))
    PFN_vkCmdSetRayTracingPipelineStackSizeKHR fp_vkCmdSetRayTracingPipelineStackSizeKHR = nullptr;
#else
    void * fp_vkCmdSetRayTracingPipelineStackSizeKHR{};
#endif
#if (defined(VK_EXT_full_screen_exclusive)) || (defined(VK_EXT_full_screen_exclusive))
    PFN_vkGetDeviceGroupSurfacePresentModes2EXT fp_vkGetDeviceGroupSurfacePresentModes2EXT = nullptr;
#else
    void * fp_vkGetDeviceGroupSurfacePresentModes2EXT{};
#endif
#if (defined(VK_EXT_full_screen_exclusive))
    PFN_vkAcquireFullScreenExclusiveModeEXT fp_vkAcquireFullScreenExclusiveModeEXT = nullptr;
#else
    void * fp_vkAcquireFullScreenExclusiveModeEXT{};
#endif
#if (defined(VK_EXT_full_screen_exclusive))
    PFN_vkReleaseFullScreenExclusiveModeEXT fp_vkReleaseFullScreenExclusiveModeEXT = nullptr;
#else
    void * fp_vkReleaseFullScreenExclusiveModeEXT{};
#endif
#if (defined(VK_KHR_performance_query))
    PFN_vkAcquireProfilingLockKHR fp_vkAcquireProfilingLockKHR = nullptr;
#else
    void * fp_vkAcquireProfilingLockKHR{};
#endif
#if (defined(VK_KHR_performance_query))
    PFN_vkReleaseProfilingLockKHR fp_vkReleaseProfilingLockKHR = nullptr;
#else
    void * fp_vkReleaseProfilingLockKHR{};
#endif
#if (defined(VK_EXT_image_drm_format_modifier))
    PFN_vkGetImageDrmFormatModifierPropertiesEXT fp_vkGetImageDrmFormatModifierPropertiesEXT = nullptr;
#else
    void * fp_vkGetImageDrmFormatModifierPropertiesEXT{};
#endif
#if (defined(VK_VERSION_1_2))
    PFN_vkGetBufferOpaqueCaptureAddress fp_vkGetBufferOpaqueCaptureAddress = nullptr;
#else
    void * fp_vkGetBufferOpaqueCaptureAddress{};
#endif
#if (defined(VK_VERSION_1_2))
    PFN_vkGetBufferDeviceAddress fp_vkGetBufferDeviceAddress = nullptr;
#else
    void * fp_vkGetBufferDeviceAddress{};
#endif
#if (defined(VK_INTEL_performance_query))
    PFN_vkInitializePerformanceApiINTEL fp_vkInitializePerformanceApiINTEL = nullptr;
#else
    void * fp_vkInitializePerformanceApiINTEL{};
#endif
#if (defined(VK_INTEL_performance_query))
    PFN_vkUninitializePerformanceApiINTEL fp_vkUninitializePerformanceApiINTEL = nullptr;
#else
    void * fp_vkUninitializePerformanceApiINTEL{};
#endif
#if (defined(VK_INTEL_performance_query))
    PFN_vkCmdSetPerformanceMarkerINTEL fp_vkCmdSetPerformanceMarkerINTEL = nullptr;
#else
    void * fp_vkCmdSetPerformanceMarkerINTEL{};
#endif
#if (defined(VK_INTEL_performance_query))
    PFN_vkCmdSetPerformanceStreamMarkerINTEL fp_vkCmdSetPerformanceStreamMarkerINTEL = nullptr;
#else
    void * fp_vkCmdSetPerformanceStreamMarkerINTEL{};
#endif
#if (defined(VK_INTEL_performance_query))
    PFN_vkCmdSetPerformanceOverrideINTEL fp_vkCmdSetPerformanceOverrideINTEL = nullptr;
#else
    void * fp_vkCmdSetPerformanceOverrideINTEL{};
#endif
#if (defined(VK_INTEL_performance_query))
    PFN_vkAcquirePerformanceConfigurationINTEL fp_vkAcquirePerformanceConfigurationINTEL = nullptr;
#else
    void * fp_vkAcquirePerformanceConfigurationINTEL{};
#endif
#if (defined(VK_INTEL_performance_query))
    PFN_vkReleasePerformanceConfigurationINTEL fp_vkReleasePerformanceConfigurationINTEL = nullptr;
#else
    void * fp_vkReleasePerformanceConfigurationINTEL{};
#endif
#if (defined(VK_INTEL_performance_query))
    PFN_vkQueueSetPerformanceConfigurationINTEL fp_vkQueueSetPerformanceConfigurationINTEL = nullptr;
#else
    void * fp_vkQueueSetPerformanceConfigurationINTEL{};
#endif
#if (defined(VK_INTEL_performance_query))
    PFN_vkGetPerformanceParameterINTEL fp_vkGetPerformanceParameterINTEL = nullptr;
#else
    void * fp_vkGetPerformanceParameterINTEL{};
#endif
#if (defined(VK_VERSION_1_2))
    PFN_vkGetDeviceMemoryOpaqueCaptureAddress fp_vkGetDeviceMemoryOpaqueCaptureAddress = nullptr;
#else
    void * fp_vkGetDeviceMemoryOpaqueCaptureAddress{};
#endif
#if (defined(VK_KHR_pipeline_executable_properties))
    PFN_vkGetPipelineExecutablePropertiesKHR fp_vkGetPipelineExecutablePropertiesKHR = nullptr;
#else
    void * fp_vkGetPipelineExecutablePropertiesKHR{};
#endif
#if (defined(VK_KHR_pipeline_executable_properties))
    PFN_vkGetPipelineExecutableStatisticsKHR fp_vkGetPipelineExecutableStatisticsKHR = nullptr;
#else
    void * fp_vkGetPipelineExecutableStatisticsKHR{};
#endif
#if (defined(VK_KHR_pipeline_executable_properties))
    PFN_vkGetPipelineExecutableInternalRepresentationsKHR fp_vkGetPipelineExecutableInternalRepresentationsKHR = nullptr;
#else
    void * fp_vkGetPipelineExecutableInternalRepresentationsKHR{};
#endif
#if (defined(VK_EXT_line_rasterization))
    PFN_vkCmdSetLineStippleEXT fp_vkCmdSetLineStippleEXT = nullptr;
#else
    void * fp_vkCmdSetLineStippleEXT{};
#endif
#if (defined(VKSC_VERSION_1_0))
    PFN_vkGetFaultData fp_vkGetFaultData = nullptr;
#else
    void * fp_vkGetFaultData{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkCreateAccelerationStructureKHR fp_vkCreateAccelerationStructureKHR = nullptr;
#else
    void * fp_vkCreateAccelerationStructureKHR{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkCmdBuildAccelerationStructuresKHR fp_vkCmdBuildAccelerationStructuresKHR = nullptr;
#else
    void * fp_vkCmdBuildAccelerationStructuresKHR{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkCmdBuildAccelerationStructuresIndirectKHR fp_vkCmdBuildAccelerationStructuresIndirectKHR = nullptr;
#else
    void * fp_vkCmdBuildAccelerationStructuresIndirectKHR{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkBuildAccelerationStructuresKHR fp_vkBuildAccelerationStructuresKHR = nullptr;
#else
    void * fp_vkBuildAccelerationStructuresKHR{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkGetAccelerationStructureDeviceAddressKHR fp_vkGetAccelerationStructureDeviceAddressKHR = nullptr;
#else
    void * fp_vkGetAccelerationStructureDeviceAddressKHR{};
#endif
#if (defined(VK_KHR_deferred_host_operations))
    PFN_vkCreateDeferredOperationKHR fp_vkCreateDeferredOperationKHR = nullptr;
#else
    void * fp_vkCreateDeferredOperationKHR{};
#endif
#if (defined(VK_KHR_deferred_host_operations))
    PFN_vkDestroyDeferredOperationKHR fp_vkDestroyDeferredOperationKHR = nullptr;
#else
    void * fp_vkDestroyDeferredOperationKHR{};
#endif
#if (defined(VK_KHR_deferred_host_operations))
    PFN_vkGetDeferredOperationMaxConcurrencyKHR fp_vkGetDeferredOperationMaxConcurrencyKHR = nullptr;
#else
    void * fp_vkGetDeferredOperationMaxConcurrencyKHR{};
#endif
#if (defined(VK_KHR_deferred_host_operations))
    PFN_vkGetDeferredOperationResultKHR fp_vkGetDeferredOperationResultKHR = nullptr;
#else
    void * fp_vkGetDeferredOperationResultKHR{};
#endif
#if (defined(VK_KHR_deferred_host_operations))
    PFN_vkDeferredOperationJoinKHR fp_vkDeferredOperationJoinKHR = nullptr;
#else
    void * fp_vkDeferredOperationJoinKHR{};
#endif
#if (defined(VK_NV_device_generated_commands_compute))
    PFN_vkGetPipelineIndirectMemoryRequirementsNV fp_vkGetPipelineIndirectMemoryRequirementsNV = nullptr;
#else
    void * fp_vkGetPipelineIndirectMemoryRequirementsNV{};
#endif
#if (defined(VK_NV_device_generated_commands_compute))
    PFN_vkGetPipelineIndirectDeviceAddressNV fp_vkGetPipelineIndirectDeviceAddressNV = nullptr;
#else
    void * fp_vkGetPipelineIndirectDeviceAddressNV{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetCullMode fp_vkCmdSetCullMode = nullptr;
#else
    void * fp_vkCmdSetCullMode{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetFrontFace fp_vkCmdSetFrontFace = nullptr;
#else
    void * fp_vkCmdSetFrontFace{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetPrimitiveTopology fp_vkCmdSetPrimitiveTopology = nullptr;
#else
    void * fp_vkCmdSetPrimitiveTopology{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetViewportWithCount fp_vkCmdSetViewportWithCount = nullptr;
#else
    void * fp_vkCmdSetViewportWithCount{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetScissorWithCount fp_vkCmdSetScissorWithCount = nullptr;
#else
    void * fp_vkCmdSetScissorWithCount{};
#endif
#if (defined(VK_KHR_maintenance5))
    PFN_vkCmdBindIndexBuffer2KHR fp_vkCmdBindIndexBuffer2KHR = nullptr;
#else
    void * fp_vkCmdBindIndexBuffer2KHR{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdBindVertexBuffers2 fp_vkCmdBindVertexBuffers2 = nullptr;
#else
    void * fp_vkCmdBindVertexBuffers2{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetDepthTestEnable fp_vkCmdSetDepthTestEnable = nullptr;
#else
    void * fp_vkCmdSetDepthTestEnable{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetDepthWriteEnable fp_vkCmdSetDepthWriteEnable = nullptr;
#else
    void * fp_vkCmdSetDepthWriteEnable{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetDepthCompareOp fp_vkCmdSetDepthCompareOp = nullptr;
#else
    void * fp_vkCmdSetDepthCompareOp{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetDepthBoundsTestEnable fp_vkCmdSetDepthBoundsTestEnable = nullptr;
#else
    void * fp_vkCmdSetDepthBoundsTestEnable{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetStencilTestEnable fp_vkCmdSetStencilTestEnable = nullptr;
#else
    void * fp_vkCmdSetStencilTestEnable{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetStencilOp fp_vkCmdSetStencilOp = nullptr;
#else
    void * fp_vkCmdSetStencilOp{};
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetPatchControlPointsEXT fp_vkCmdSetPatchControlPointsEXT = nullptr;
#else
    void * fp_vkCmdSetPatchControlPointsEXT{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetRasterizerDiscardEnable fp_vkCmdSetRasterizerDiscardEnable = nullptr;
#else
    void * fp_vkCmdSetRasterizerDiscardEnable{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetDepthBiasEnable fp_vkCmdSetDepthBiasEnable = nullptr;
#else
    void * fp_vkCmdSetDepthBiasEnable{};
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetLogicOpEXT fp_vkCmdSetLogicOpEXT = nullptr;
#else
    void * fp_vkCmdSetLogicOpEXT{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetPrimitiveRestartEnable fp_vkCmdSetPrimitiveRestartEnable = nullptr;
#else
    void * fp_vkCmdSetPrimitiveRestartEnable{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetTessellationDomainOriginEXT fp_vkCmdSetTessellationDomainOriginEXT = nullptr;
#else
    void * fp_vkCmdSetTessellationDomainOriginEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetDepthClampEnableEXT fp_vkCmdSetDepthClampEnableEXT = nullptr;
#else
    void * fp_vkCmdSetDepthClampEnableEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetPolygonModeEXT fp_vkCmdSetPolygonModeEXT = nullptr;
#else
    void * fp_vkCmdSetPolygonModeEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetRasterizationSamplesEXT fp_vkCmdSetRasterizationSamplesEXT = nullptr;
#else
    void * fp_vkCmdSetRasterizationSamplesEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetSampleMaskEXT fp_vkCmdSetSampleMaskEXT = nullptr;
#else
    void * fp_vkCmdSetSampleMaskEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetAlphaToCoverageEnableEXT fp_vkCmdSetAlphaToCoverageEnableEXT = nullptr;
#else
    void * fp_vkCmdSetAlphaToCoverageEnableEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetAlphaToOneEnableEXT fp_vkCmdSetAlphaToOneEnableEXT = nullptr;
#else
    void * fp_vkCmdSetAlphaToOneEnableEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetLogicOpEnableEXT fp_vkCmdSetLogicOpEnableEXT = nullptr;
#else
    void * fp_vkCmdSetLogicOpEnableEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetColorBlendEnableEXT fp_vkCmdSetColorBlendEnableEXT = nullptr;
#else
    void * fp_vkCmdSetColorBlendEnableEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetColorBlendEquationEXT fp_vkCmdSetColorBlendEquationEXT = nullptr;
#else
    void * fp_vkCmdSetColorBlendEquationEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetColorWriteMaskEXT fp_vkCmdSetColorWriteMaskEXT = nullptr;
#else
    void * fp_vkCmdSetColorWriteMaskEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetRasterizationStreamEXT fp_vkCmdSetRasterizationStreamEXT = nullptr;
#else
    void * fp_vkCmdSetRasterizationStreamEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetConservativeRasterizationModeEXT fp_vkCmdSetConservativeRasterizationModeEXT = nullptr;
#else
    void * fp_vkCmdSetConservativeRasterizationModeEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT fp_vkCmdSetExtraPrimitiveOverestimationSizeEXT = nullptr;
#else
    void * fp_vkCmdSetExtraPrimitiveOverestimationSizeEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetDepthClipEnableEXT fp_vkCmdSetDepthClipEnableEXT = nullptr;
#else
    void * fp_vkCmdSetDepthClipEnableEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetSampleLocationsEnableEXT fp_vkCmdSetSampleLocationsEnableEXT = nullptr;
#else
    void * fp_vkCmdSetSampleLocationsEnableEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetColorBlendAdvancedEXT fp_vkCmdSetColorBlendAdvancedEXT = nullptr;
#else
    void * fp_vkCmdSetColorBlendAdvancedEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetProvokingVertexModeEXT fp_vkCmdSetProvokingVertexModeEXT = nullptr;
#else
    void * fp_vkCmdSetProvokingVertexModeEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetLineRasterizationModeEXT fp_vkCmdSetLineRasterizationModeEXT = nullptr;
#else
    void * fp_vkCmdSetLineRasterizationModeEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetLineStippleEnableEXT fp_vkCmdSetLineStippleEnableEXT = nullptr;
#else
    void * fp_vkCmdSetLineStippleEnableEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetDepthClipNegativeOneToOneEXT fp_vkCmdSetDepthClipNegativeOneToOneEXT = nullptr;
#else
    void * fp_vkCmdSetDepthClipNegativeOneToOneEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetViewportWScalingEnableNV fp_vkCmdSetViewportWScalingEnableNV = nullptr;
#else
    void * fp_vkCmdSetViewportWScalingEnableNV{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetViewportSwizzleNV fp_vkCmdSetViewportSwizzleNV = nullptr;
#else
    void * fp_vkCmdSetViewportSwizzleNV{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetCoverageToColorEnableNV fp_vkCmdSetCoverageToColorEnableNV = nullptr;
#else
    void * fp_vkCmdSetCoverageToColorEnableNV{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetCoverageToColorLocationNV fp_vkCmdSetCoverageToColorLocationNV = nullptr;
#else
    void * fp_vkCmdSetCoverageToColorLocationNV{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetCoverageModulationModeNV fp_vkCmdSetCoverageModulationModeNV = nullptr;
#else
    void * fp_vkCmdSetCoverageModulationModeNV{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetCoverageModulationTableEnableNV fp_vkCmdSetCoverageModulationTableEnableNV = nullptr;
#else
    void * fp_vkCmdSetCoverageModulationTableEnableNV{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetCoverageModulationTableNV fp_vkCmdSetCoverageModulationTableNV = nullptr;
#else
    void * fp_vkCmdSetCoverageModulationTableNV{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetShadingRateImageEnableNV fp_vkCmdSetShadingRateImageEnableNV = nullptr;
#else
    void * fp_vkCmdSetShadingRateImageEnableNV{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetCoverageReductionModeNV fp_vkCmdSetCoverageReductionModeNV = nullptr;
#else
    void * fp_vkCmdSetCoverageReductionModeNV{};
#endif
#if (defined(VK_EXT_extended_dynamic_state3)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetRepresentativeFragmentTestEnableNV fp_vkCmdSetRepresentativeFragmentTestEnableNV = nullptr;
#else
    void * fp_vkCmdSetRepresentativeFragmentTestEnableNV{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCreatePrivateDataSlot fp_vkCreatePrivateDataSlot = nullptr;
#else
    void * fp_vkCreatePrivateDataSlot{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkDestroyPrivateDataSlot fp_vkDestroyPrivateDataSlot = nullptr;
#else
    void * fp_vkDestroyPrivateDataSlot{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkSetPrivateData fp_vkSetPrivateData = nullptr;
#else
    void * fp_vkSetPrivateData{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkGetPrivateData fp_vkGetPrivateData = nullptr;
#else
    void * fp_vkGetPrivateData{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdCopyBuffer2 fp_vkCmdCopyBuffer2 = nullptr;
#else
    void * fp_vkCmdCopyBuffer2{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdCopyImage2 fp_vkCmdCopyImage2 = nullptr;
#else
    void * fp_vkCmdCopyImage2{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdBlitImage2 fp_vkCmdBlitImage2 = nullptr;
#else
    void * fp_vkCmdBlitImage2{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdCopyBufferToImage2 fp_vkCmdCopyBufferToImage2 = nullptr;
#else
    void * fp_vkCmdCopyBufferToImage2{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdCopyImageToBuffer2 fp_vkCmdCopyImageToBuffer2 = nullptr;
#else
    void * fp_vkCmdCopyImageToBuffer2{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdResolveImage2 fp_vkCmdResolveImage2 = nullptr;
#else
    void * fp_vkCmdResolveImage2{};
#endif
#if (defined(VK_KHR_object_refresh))
    PFN_vkCmdRefreshObjectsKHR fp_vkCmdRefreshObjectsKHR = nullptr;
#else
    void * fp_vkCmdRefreshObjectsKHR{};
#endif
#if (defined(VK_KHR_fragment_shading_rate))
    PFN_vkCmdSetFragmentShadingRateKHR fp_vkCmdSetFragmentShadingRateKHR = nullptr;
#else
    void * fp_vkCmdSetFragmentShadingRateKHR{};
#endif
#if (defined(VK_NV_fragment_shading_rate_enums))
    PFN_vkCmdSetFragmentShadingRateEnumNV fp_vkCmdSetFragmentShadingRateEnumNV = nullptr;
#else
    void * fp_vkCmdSetFragmentShadingRateEnumNV{};
#endif
#if (defined(VK_KHR_acceleration_structure))
    PFN_vkGetAccelerationStructureBuildSizesKHR fp_vkGetAccelerationStructureBuildSizesKHR = nullptr;
#else
    void * fp_vkGetAccelerationStructureBuildSizesKHR{};
#endif
#if (defined(VK_EXT_vertex_input_dynamic_state)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetVertexInputEXT fp_vkCmdSetVertexInputEXT = nullptr;
#else
    void * fp_vkCmdSetVertexInputEXT{};
#endif
#if (defined(VK_EXT_color_write_enable))
    PFN_vkCmdSetColorWriteEnableEXT fp_vkCmdSetColorWriteEnableEXT = nullptr;
#else
    void * fp_vkCmdSetColorWriteEnableEXT{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdSetEvent2 fp_vkCmdSetEvent2 = nullptr;
#else
    void * fp_vkCmdSetEvent2{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdResetEvent2 fp_vkCmdResetEvent2 = nullptr;
#else
    void * fp_vkCmdResetEvent2{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdWaitEvents2 fp_vkCmdWaitEvents2 = nullptr;
#else
    void * fp_vkCmdWaitEvents2{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdPipelineBarrier2 fp_vkCmdPipelineBarrier2 = nullptr;
#else
    void * fp_vkCmdPipelineBarrier2{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkQueueSubmit2 fp_vkQueueSubmit2 = nullptr;
#else
    void * fp_vkQueueSubmit2{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdWriteTimestamp2 fp_vkCmdWriteTimestamp2 = nullptr;
#else
    void * fp_vkCmdWriteTimestamp2{};
#endif
#if (defined(VK_KHR_synchronization2))
    PFN_vkCmdWriteBufferMarker2AMD fp_vkCmdWriteBufferMarker2AMD = nullptr;
#else
    void * fp_vkCmdWriteBufferMarker2AMD{};
#endif
#if (defined(VK_KHR_synchronization2))
    PFN_vkGetQueueCheckpointData2NV fp_vkGetQueueCheckpointData2NV = nullptr;
#else
    void * fp_vkGetQueueCheckpointData2NV{};
#endif
#if (defined(VK_EXT_host_image_copy))
    PFN_vkCopyMemoryToImageEXT fp_vkCopyMemoryToImageEXT = nullptr;
#else
    void * fp_vkCopyMemoryToImageEXT{};
#endif
#if (defined(VK_EXT_host_image_copy))
    PFN_vkCopyImageToMemoryEXT fp_vkCopyImageToMemoryEXT = nullptr;
#else
    void * fp_vkCopyImageToMemoryEXT{};
#endif
#if (defined(VK_EXT_host_image_copy))
    PFN_vkCopyImageToImageEXT fp_vkCopyImageToImageEXT = nullptr;
#else
    void * fp_vkCopyImageToImageEXT{};
#endif
#if (defined(VK_EXT_host_image_copy))
    PFN_vkTransitionImageLayoutEXT fp_vkTransitionImageLayoutEXT = nullptr;
#else
    void * fp_vkTransitionImageLayoutEXT{};
#endif
#if (defined(VKSC_VERSION_1_0))
    PFN_vkGetCommandPoolMemoryConsumption fp_vkGetCommandPoolMemoryConsumption = nullptr;
#else
    void * fp_vkGetCommandPoolMemoryConsumption{};
#endif
#if (defined(VK_KHR_video_queue))
    PFN_vkCreateVideoSessionKHR fp_vkCreateVideoSessionKHR = nullptr;
#else
    void * fp_vkCreateVideoSessionKHR{};
#endif
#if (defined(VK_KHR_video_queue))
    PFN_vkDestroyVideoSessionKHR fp_vkDestroyVideoSessionKHR = nullptr;
#else
    void * fp_vkDestroyVideoSessionKHR{};
#endif
#if (defined(VK_KHR_video_queue))
    PFN_vkCreateVideoSessionParametersKHR fp_vkCreateVideoSessionParametersKHR = nullptr;
#else
    void * fp_vkCreateVideoSessionParametersKHR{};
#endif
#if (defined(VK_KHR_video_queue))
    PFN_vkUpdateVideoSessionParametersKHR fp_vkUpdateVideoSessionParametersKHR = nullptr;
#else
    void * fp_vkUpdateVideoSessionParametersKHR{};
#endif
#if (defined(VK_KHR_video_encode_queue))
    PFN_vkGetEncodedVideoSessionParametersKHR fp_vkGetEncodedVideoSessionParametersKHR = nullptr;
#else
    void * fp_vkGetEncodedVideoSessionParametersKHR{};
#endif
#if (defined(VK_KHR_video_queue))
    PFN_vkDestroyVideoSessionParametersKHR fp_vkDestroyVideoSessionParametersKHR = nullptr;
#else
    void * fp_vkDestroyVideoSessionParametersKHR{};
#endif
#if (defined(VK_KHR_video_queue))
    PFN_vkGetVideoSessionMemoryRequirementsKHR fp_vkGetVideoSessionMemoryRequirementsKHR = nullptr;
#else
    void * fp_vkGetVideoSessionMemoryRequirementsKHR{};
#endif
#if (defined(VK_KHR_video_queue))
    PFN_vkBindVideoSessionMemoryKHR fp_vkBindVideoSessionMemoryKHR = nullptr;
#else
    void * fp_vkBindVideoSessionMemoryKHR{};
#endif
#if (defined(VK_KHR_video_decode_queue))
    PFN_vkCmdDecodeVideoKHR fp_vkCmdDecodeVideoKHR = nullptr;
#else
    void * fp_vkCmdDecodeVideoKHR{};
#endif
#if (defined(VK_KHR_video_queue))
    PFN_vkCmdBeginVideoCodingKHR fp_vkCmdBeginVideoCodingKHR = nullptr;
#else
    void * fp_vkCmdBeginVideoCodingKHR{};
#endif
#if (defined(VK_KHR_video_queue))
    PFN_vkCmdControlVideoCodingKHR fp_vkCmdControlVideoCodingKHR = nullptr;
#else
    void * fp_vkCmdControlVideoCodingKHR{};
#endif
#if (defined(VK_KHR_video_queue))
    PFN_vkCmdEndVideoCodingKHR fp_vkCmdEndVideoCodingKHR = nullptr;
#else
    void * fp_vkCmdEndVideoCodingKHR{};
#endif
#if (defined(VK_KHR_video_encode_queue))
    PFN_vkCmdEncodeVideoKHR fp_vkCmdEncodeVideoKHR = nullptr;
#else
    void * fp_vkCmdEncodeVideoKHR{};
#endif
#if (defined(VK_NV_memory_decompression))
    PFN_vkCmdDecompressMemoryNV fp_vkCmdDecompressMemoryNV = nullptr;
#else
    void * fp_vkCmdDecompressMemoryNV{};
#endif
#if (defined(VK_NV_memory_decompression))
    PFN_vkCmdDecompressMemoryIndirectCountNV fp_vkCmdDecompressMemoryIndirectCountNV = nullptr;
#else
    void * fp_vkCmdDecompressMemoryIndirectCountNV{};
#endif
#if (defined(VK_EXT_descriptor_buffer))
    PFN_vkGetDescriptorSetLayoutSizeEXT fp_vkGetDescriptorSetLayoutSizeEXT = nullptr;
#else
    void * fp_vkGetDescriptorSetLayoutSizeEXT{};
#endif
#if (defined(VK_EXT_descriptor_buffer))
    PFN_vkGetDescriptorSetLayoutBindingOffsetEXT fp_vkGetDescriptorSetLayoutBindingOffsetEXT = nullptr;
#else
    void * fp_vkGetDescriptorSetLayoutBindingOffsetEXT{};
#endif
#if (defined(VK_EXT_descriptor_buffer))
    PFN_vkGetDescriptorEXT fp_vkGetDescriptorEXT = nullptr;
#else
    void * fp_vkGetDescriptorEXT{};
#endif
#if (defined(VK_EXT_descriptor_buffer))
    PFN_vkCmdBindDescriptorBuffersEXT fp_vkCmdBindDescriptorBuffersEXT = nullptr;
#else
    void * fp_vkCmdBindDescriptorBuffersEXT{};
#endif
#if (defined(VK_EXT_descriptor_buffer))
    PFN_vkCmdSetDescriptorBufferOffsetsEXT fp_vkCmdSetDescriptorBufferOffsetsEXT = nullptr;
#else
    void * fp_vkCmdSetDescriptorBufferOffsetsEXT{};
#endif
#if (defined(VK_EXT_descriptor_buffer))
    PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT fp_vkCmdBindDescriptorBufferEmbeddedSamplersEXT = nullptr;
#else
    void * fp_vkCmdBindDescriptorBufferEmbeddedSamplersEXT{};
#endif
#if (defined(VK_EXT_descriptor_buffer))
    PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT fp_vkGetBufferOpaqueCaptureDescriptorDataEXT = nullptr;
#else
    void * fp_vkGetBufferOpaqueCaptureDescriptorDataEXT{};
#endif
#if (defined(VK_EXT_descriptor_buffer))
    PFN_vkGetImageOpaqueCaptureDescriptorDataEXT fp_vkGetImageOpaqueCaptureDescriptorDataEXT = nullptr;
#else
    void * fp_vkGetImageOpaqueCaptureDescriptorDataEXT{};
#endif
#if (defined(VK_EXT_descriptor_buffer))
    PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT fp_vkGetImageViewOpaqueCaptureDescriptorDataEXT = nullptr;
#else
    void * fp_vkGetImageViewOpaqueCaptureDescriptorDataEXT{};
#endif
#if (defined(VK_EXT_descriptor_buffer))
    PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT fp_vkGetSamplerOpaqueCaptureDescriptorDataEXT = nullptr;
#else
    void * fp_vkGetSamplerOpaqueCaptureDescriptorDataEXT{};
#endif
#if (defined(VK_EXT_descriptor_buffer))
    PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT fp_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT = nullptr;
#else
    void * fp_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT{};
#endif
#if (defined(VK_EXT_pageable_device_local_memory))
    PFN_vkSetDeviceMemoryPriorityEXT fp_vkSetDeviceMemoryPriorityEXT = nullptr;
#else
    void * fp_vkSetDeviceMemoryPriorityEXT{};
#endif
#if (defined(VK_KHR_present_wait))
    PFN_vkWaitForPresentKHR fp_vkWaitForPresentKHR = nullptr;
#else
    void * fp_vkWaitForPresentKHR{};
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
    PFN_vkCreateBufferCollectionFUCHSIA fp_vkCreateBufferCollectionFUCHSIA = nullptr;
#else
    void * fp_vkCreateBufferCollectionFUCHSIA{};
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
    PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA fp_vkSetBufferCollectionBufferConstraintsFUCHSIA = nullptr;
#else
    void * fp_vkSetBufferCollectionBufferConstraintsFUCHSIA{};
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
    PFN_vkSetBufferCollectionImageConstraintsFUCHSIA fp_vkSetBufferCollectionImageConstraintsFUCHSIA = nullptr;
#else
    void * fp_vkSetBufferCollectionImageConstraintsFUCHSIA{};
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
    PFN_vkDestroyBufferCollectionFUCHSIA fp_vkDestroyBufferCollectionFUCHSIA = nullptr;
#else
    void * fp_vkDestroyBufferCollectionFUCHSIA{};
#endif
#if (defined(VK_FUCHSIA_buffer_collection))
    PFN_vkGetBufferCollectionPropertiesFUCHSIA fp_vkGetBufferCollectionPropertiesFUCHSIA = nullptr;
#else
    void * fp_vkGetBufferCollectionPropertiesFUCHSIA{};
#endif
#if (defined(VK_NV_cuda_kernel_launch))
    PFN_vkCreateCudaModuleNV fp_vkCreateCudaModuleNV = nullptr;
#else
    void * fp_vkCreateCudaModuleNV{};
#endif
#if (defined(VK_NV_cuda_kernel_launch))
    PFN_vkGetCudaModuleCacheNV fp_vkGetCudaModuleCacheNV = nullptr;
#else
    void * fp_vkGetCudaModuleCacheNV{};
#endif
#if (defined(VK_NV_cuda_kernel_launch))
    PFN_vkCreateCudaFunctionNV fp_vkCreateCudaFunctionNV = nullptr;
#else
    void * fp_vkCreateCudaFunctionNV{};
#endif
#if (defined(VK_NV_cuda_kernel_launch))
    PFN_vkDestroyCudaModuleNV fp_vkDestroyCudaModuleNV = nullptr;
#else
    void * fp_vkDestroyCudaModuleNV{};
#endif
#if (defined(VK_NV_cuda_kernel_launch))
    PFN_vkDestroyCudaFunctionNV fp_vkDestroyCudaFunctionNV = nullptr;
#else
    void * fp_vkDestroyCudaFunctionNV{};
#endif
#if (defined(VK_NV_cuda_kernel_launch))
    PFN_vkCmdCudaLaunchKernelNV fp_vkCmdCudaLaunchKernelNV = nullptr;
#else
    void * fp_vkCmdCudaLaunchKernelNV{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdBeginRendering fp_vkCmdBeginRendering = nullptr;
#else
    void * fp_vkCmdBeginRendering{};
#endif
#if (defined(VK_VERSION_1_3))
    PFN_vkCmdEndRendering fp_vkCmdEndRendering = nullptr;
#else
    void * fp_vkCmdEndRendering{};
#endif
#if (defined(VK_VALVE_descriptor_set_host_mapping))
    PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE fp_vkGetDescriptorSetLayoutHostMappingInfoVALVE = nullptr;
#else
    void * fp_vkGetDescriptorSetLayoutHostMappingInfoVALVE{};
#endif
#if (defined(VK_VALVE_descriptor_set_host_mapping))
    PFN_vkGetDescriptorSetHostMappingVALVE fp_vkGetDescriptorSetHostMappingVALVE = nullptr;
#else
    void * fp_vkGetDescriptorSetHostMappingVALVE{};
#endif
#if (defined(VK_EXT_opacity_micromap))
    PFN_vkCreateMicromapEXT fp_vkCreateMicromapEXT = nullptr;
#else
    void * fp_vkCreateMicromapEXT{};
#endif
#if (defined(VK_EXT_opacity_micromap))
    PFN_vkCmdBuildMicromapsEXT fp_vkCmdBuildMicromapsEXT = nullptr;
#else
    void * fp_vkCmdBuildMicromapsEXT{};
#endif
#if (defined(VK_EXT_opacity_micromap))
    PFN_vkBuildMicromapsEXT fp_vkBuildMicromapsEXT = nullptr;
#else
    void * fp_vkBuildMicromapsEXT{};
#endif
#if (defined(VK_EXT_opacity_micromap))
    PFN_vkDestroyMicromapEXT fp_vkDestroyMicromapEXT = nullptr;
#else
    void * fp_vkDestroyMicromapEXT{};
#endif
#if (defined(VK_EXT_opacity_micromap))
    PFN_vkCmdCopyMicromapEXT fp_vkCmdCopyMicromapEXT = nullptr;
#else
    void * fp_vkCmdCopyMicromapEXT{};
#endif
#if (defined(VK_EXT_opacity_micromap))
    PFN_vkCopyMicromapEXT fp_vkCopyMicromapEXT = nullptr;
#else
    void * fp_vkCopyMicromapEXT{};
#endif
#if (defined(VK_EXT_opacity_micromap))
    PFN_vkCmdCopyMicromapToMemoryEXT fp_vkCmdCopyMicromapToMemoryEXT = nullptr;
#else
    void * fp_vkCmdCopyMicromapToMemoryEXT{};
#endif
#if (defined(VK_EXT_opacity_micromap))
    PFN_vkCopyMicromapToMemoryEXT fp_vkCopyMicromapToMemoryEXT = nullptr;
#else
    void * fp_vkCopyMicromapToMemoryEXT{};
#endif
#if (defined(VK_EXT_opacity_micromap))
    PFN_vkCmdCopyMemoryToMicromapEXT fp_vkCmdCopyMemoryToMicromapEXT = nullptr;
#else
    void * fp_vkCmdCopyMemoryToMicromapEXT{};
#endif
#if (defined(VK_EXT_opacity_micromap))
    PFN_vkCopyMemoryToMicromapEXT fp_vkCopyMemoryToMicromapEXT = nullptr;
#else
    void * fp_vkCopyMemoryToMicromapEXT{};
#endif
#if (defined(VK_EXT_opacity_micromap))
    PFN_vkCmdWriteMicromapsPropertiesEXT fp_vkCmdWriteMicromapsPropertiesEXT = nullptr;
#else
    void * fp_vkCmdWriteMicromapsPropertiesEXT{};
#endif
#if (defined(VK_EXT_opacity_micromap))
    PFN_vkWriteMicromapsPropertiesEXT fp_vkWriteMicromapsPropertiesEXT = nullptr;
#else
    void * fp_vkWriteMicromapsPropertiesEXT{};
#endif
#if (defined(VK_EXT_opacity_micromap))
    PFN_vkGetDeviceMicromapCompatibilityEXT fp_vkGetDeviceMicromapCompatibilityEXT = nullptr;
#else
    void * fp_vkGetDeviceMicromapCompatibilityEXT{};
#endif
#if (defined(VK_EXT_opacity_micromap))
    PFN_vkGetMicromapBuildSizesEXT fp_vkGetMicromapBuildSizesEXT = nullptr;
#else
    void * fp_vkGetMicromapBuildSizesEXT{};
#endif
#if (defined(VK_EXT_shader_module_identifier))
    PFN_vkGetShaderModuleIdentifierEXT fp_vkGetShaderModuleIdentifierEXT = nullptr;
#else
    void * fp_vkGetShaderModuleIdentifierEXT{};
#endif
#if (defined(VK_EXT_shader_module_identifier))
    PFN_vkGetShaderModuleCreateInfoIdentifierEXT fp_vkGetShaderModuleCreateInfoIdentifierEXT = nullptr;
#else
    void * fp_vkGetShaderModuleCreateInfoIdentifierEXT{};
#endif
#if (defined(VK_KHR_maintenance5))
    PFN_vkGetImageSubresourceLayout2KHR fp_vkGetImageSubresourceLayout2KHR = nullptr;
#else
    void * fp_vkGetImageSubresourceLayout2KHR{};
#endif
#if (defined(VK_EXT_pipeline_properties))
    PFN_vkGetPipelinePropertiesEXT fp_vkGetPipelinePropertiesEXT = nullptr;
#else
    void * fp_vkGetPipelinePropertiesEXT{};
#endif
#if (defined(VK_EXT_metal_objects))
    PFN_vkExportMetalObjectsEXT fp_vkExportMetalObjectsEXT = nullptr;
#else
    void * fp_vkExportMetalObjectsEXT{};
#endif
#if (defined(VK_QCOM_tile_properties))
    PFN_vkGetFramebufferTilePropertiesQCOM fp_vkGetFramebufferTilePropertiesQCOM = nullptr;
#else
    void * fp_vkGetFramebufferTilePropertiesQCOM{};
#endif
#if (defined(VK_QCOM_tile_properties))
    PFN_vkGetDynamicRenderingTilePropertiesQCOM fp_vkGetDynamicRenderingTilePropertiesQCOM = nullptr;
#else
    void * fp_vkGetDynamicRenderingTilePropertiesQCOM{};
#endif
#if (defined(VK_NV_optical_flow))
    PFN_vkCreateOpticalFlowSessionNV fp_vkCreateOpticalFlowSessionNV = nullptr;
#else
    void * fp_vkCreateOpticalFlowSessionNV{};
#endif
#if (defined(VK_NV_optical_flow))
    PFN_vkDestroyOpticalFlowSessionNV fp_vkDestroyOpticalFlowSessionNV = nullptr;
#else
    void * fp_vkDestroyOpticalFlowSessionNV{};
#endif
#if (defined(VK_NV_optical_flow))
    PFN_vkBindOpticalFlowSessionImageNV fp_vkBindOpticalFlowSessionImageNV = nullptr;
#else
    void * fp_vkBindOpticalFlowSessionImageNV{};
#endif
#if (defined(VK_NV_optical_flow))
    PFN_vkCmdOpticalFlowExecuteNV fp_vkCmdOpticalFlowExecuteNV = nullptr;
#else
    void * fp_vkCmdOpticalFlowExecuteNV{};
#endif
#if (defined(VK_EXT_device_fault))
    PFN_vkGetDeviceFaultInfoEXT fp_vkGetDeviceFaultInfoEXT = nullptr;
#else
    void * fp_vkGetDeviceFaultInfoEXT{};
#endif
#if (defined(VK_EXT_depth_bias_control))
    PFN_vkCmdSetDepthBias2EXT fp_vkCmdSetDepthBias2EXT = nullptr;
#else
    void * fp_vkCmdSetDepthBias2EXT{};
#endif
#if (defined(VK_EXT_swapchain_maintenance1))
    PFN_vkReleaseSwapchainImagesEXT fp_vkReleaseSwapchainImagesEXT = nullptr;
#else
    void * fp_vkReleaseSwapchainImagesEXT{};
#endif
#if (defined(VK_KHR_maintenance5))
    PFN_vkGetDeviceImageSubresourceLayoutKHR fp_vkGetDeviceImageSubresourceLayoutKHR = nullptr;
#else
    void * fp_vkGetDeviceImageSubresourceLayoutKHR{};
#endif
#if (defined(VK_KHR_map_memory2))
    PFN_vkMapMemory2KHR fp_vkMapMemory2KHR = nullptr;
#else
    void * fp_vkMapMemory2KHR{};
#endif
#if (defined(VK_KHR_map_memory2))
    PFN_vkUnmapMemory2KHR fp_vkUnmapMemory2KHR = nullptr;
#else
    void * fp_vkUnmapMemory2KHR{};
#endif
#if (defined(VK_EXT_shader_object))
    PFN_vkCreateShadersEXT fp_vkCreateShadersEXT = nullptr;
#else
    void * fp_vkCreateShadersEXT{};
#endif
#if (defined(VK_EXT_shader_object))
    PFN_vkDestroyShaderEXT fp_vkDestroyShaderEXT = nullptr;
#else
    void * fp_vkDestroyShaderEXT{};
#endif
#if (defined(VK_EXT_shader_object))
    PFN_vkGetShaderBinaryDataEXT fp_vkGetShaderBinaryDataEXT = nullptr;
#else
    void * fp_vkGetShaderBinaryDataEXT{};
#endif
#if (defined(VK_EXT_shader_object))
    PFN_vkCmdBindShadersEXT fp_vkCmdBindShadersEXT = nullptr;
#else
    void * fp_vkCmdBindShadersEXT{};
#endif
#if (defined(VK_QNX_external_memory_screen_buffer))
    PFN_vkGetScreenBufferPropertiesQNX fp_vkGetScreenBufferPropertiesQNX = nullptr;
#else
    void * fp_vkGetScreenBufferPropertiesQNX{};
#endif
#if (defined(VK_AMDX_shader_enqueue))
    PFN_vkGetExecutionGraphPipelineScratchSizeAMDX fp_vkGetExecutionGraphPipelineScratchSizeAMDX = nullptr;
#else
    void * fp_vkGetExecutionGraphPipelineScratchSizeAMDX{};
#endif
#if (defined(VK_AMDX_shader_enqueue))
    PFN_vkGetExecutionGraphPipelineNodeIndexAMDX fp_vkGetExecutionGraphPipelineNodeIndexAMDX = nullptr;
#else
    void * fp_vkGetExecutionGraphPipelineNodeIndexAMDX{};
#endif
#if (defined(VK_AMDX_shader_enqueue))
    PFN_vkCreateExecutionGraphPipelinesAMDX fp_vkCreateExecutionGraphPipelinesAMDX = nullptr;
#else
    void * fp_vkCreateExecutionGraphPipelinesAMDX{};
#endif
#if (defined(VK_AMDX_shader_enqueue))
    PFN_vkCmdInitializeGraphScratchMemoryAMDX fp_vkCmdInitializeGraphScratchMemoryAMDX = nullptr;
#else
    void * fp_vkCmdInitializeGraphScratchMemoryAMDX{};
#endif
#if (defined(VK_AMDX_shader_enqueue))
    PFN_vkCmdDispatchGraphAMDX fp_vkCmdDispatchGraphAMDX = nullptr;
#else
    void * fp_vkCmdDispatchGraphAMDX{};
#endif
#if (defined(VK_AMDX_shader_enqueue))
    PFN_vkCmdDispatchGraphIndirectAMDX fp_vkCmdDispatchGraphIndirectAMDX = nullptr;
#else
    void * fp_vkCmdDispatchGraphIndirectAMDX{};
#endif
#if (defined(VK_AMDX_shader_enqueue))
    PFN_vkCmdDispatchGraphIndirectCountAMDX fp_vkCmdDispatchGraphIndirectCountAMDX = nullptr;
#else
    void * fp_vkCmdDispatchGraphIndirectCountAMDX{};
#endif
#if (defined(VK_KHR_maintenance6))
    PFN_vkCmdBindDescriptorSets2KHR fp_vkCmdBindDescriptorSets2KHR = nullptr;
#else
    void * fp_vkCmdBindDescriptorSets2KHR{};
#endif
#if (defined(VK_KHR_maintenance6))
    PFN_vkCmdPushConstants2KHR fp_vkCmdPushConstants2KHR = nullptr;
#else
    void * fp_vkCmdPushConstants2KHR{};
#endif
#if (defined(VK_KHR_maintenance6))
    PFN_vkCmdPushDescriptorSet2KHR fp_vkCmdPushDescriptorSet2KHR = nullptr;
#else
    void * fp_vkCmdPushDescriptorSet2KHR{};
#endif
#if (defined(VK_KHR_maintenance6))
    PFN_vkCmdPushDescriptorSetWithTemplate2KHR fp_vkCmdPushDescriptorSetWithTemplate2KHR = nullptr;
#else
    void * fp_vkCmdPushDescriptorSetWithTemplate2KHR{};
#endif
#if (defined(VK_KHR_maintenance6))
    PFN_vkCmdSetDescriptorBufferOffsets2EXT fp_vkCmdSetDescriptorBufferOffsets2EXT = nullptr;
#else
    void * fp_vkCmdSetDescriptorBufferOffsets2EXT{};
#endif
#if (defined(VK_KHR_maintenance6))
    PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT fp_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT = nullptr;
#else
    void * fp_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT{};
#endif
#if (defined(VK_NV_low_latency2))
    PFN_vkSetLatencySleepModeNV fp_vkSetLatencySleepModeNV = nullptr;
#else
    void * fp_vkSetLatencySleepModeNV{};
#endif
#if (defined(VK_NV_low_latency2))
    PFN_vkLatencySleepNV fp_vkLatencySleepNV = nullptr;
#else
    void * fp_vkLatencySleepNV{};
#endif
#if (defined(VK_NV_low_latency2))
    PFN_vkSetLatencyMarkerNV fp_vkSetLatencyMarkerNV = nullptr;
#else
    void * fp_vkSetLatencyMarkerNV{};
#endif
#if ((defined(VK_NV_low_latency2))) && VK_HEADER_VERSION >= 271
    PFN_vkGetLatencyTimingsNV fp_vkGetLatencyTimingsNV = nullptr;
#else
    void * fp_vkGetLatencyTimingsNV{};
#endif
#if (defined(VK_NV_low_latency2))
    PFN_vkQueueNotifyOutOfBandNV fp_vkQueueNotifyOutOfBandNV = nullptr;
#else
    void * fp_vkQueueNotifyOutOfBandNV{};
#endif
#if (defined(VK_EXT_host_query_reset))
    PFN_vkResetQueryPoolEXT fp_vkResetQueryPoolEXT = nullptr;
#else
    void * fp_vkResetQueryPoolEXT{};
#endif
#if (defined(VK_KHR_maintenance1))
    PFN_vkTrimCommandPoolKHR fp_vkTrimCommandPoolKHR = nullptr;
#else
    void * fp_vkTrimCommandPoolKHR{};
#endif
#if (defined(VK_KHR_device_group))
    PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR fp_vkGetDeviceGroupPeerMemoryFeaturesKHR = nullptr;
#else
    void * fp_vkGetDeviceGroupPeerMemoryFeaturesKHR{};
#endif
#if (defined(VK_KHR_bind_memory2))
    PFN_vkBindBufferMemory2KHR fp_vkBindBufferMemory2KHR = nullptr;
#else
    void * fp_vkBindBufferMemory2KHR{};
#endif
#if (defined(VK_KHR_bind_memory2))
    PFN_vkBindImageMemory2KHR fp_vkBindImageMemory2KHR = nullptr;
#else
    void * fp_vkBindImageMemory2KHR{};
#endif
#if (defined(VK_KHR_device_group))
    PFN_vkCmdSetDeviceMaskKHR fp_vkCmdSetDeviceMaskKHR = nullptr;
#else
    void * fp_vkCmdSetDeviceMaskKHR{};
#endif
#if (defined(VK_KHR_device_group))
    PFN_vkCmdDispatchBaseKHR fp_vkCmdDispatchBaseKHR = nullptr;
#else
    void * fp_vkCmdDispatchBaseKHR{};
#endif
#if (defined(VK_KHR_descriptor_update_template))
    PFN_vkCreateDescriptorUpdateTemplateKHR fp_vkCreateDescriptorUpdateTemplateKHR = nullptr;
#else
    void * fp_vkCreateDescriptorUpdateTemplateKHR{};
#endif
#if (defined(VK_KHR_descriptor_update_template))
    PFN_vkDestroyDescriptorUpdateTemplateKHR fp_vkDestroyDescriptorUpdateTemplateKHR = nullptr;
#else
    void * fp_vkDestroyDescriptorUpdateTemplateKHR{};
#endif
#if (defined(VK_KHR_descriptor_update_template))
    PFN_vkUpdateDescriptorSetWithTemplateKHR fp_vkUpdateDescriptorSetWithTemplateKHR = nullptr;
#else
    void * fp_vkUpdateDescriptorSetWithTemplateKHR{};
#endif
#if (defined(VK_KHR_get_memory_requirements2))
    PFN_vkGetBufferMemoryRequirements2KHR fp_vkGetBufferMemoryRequirements2KHR = nullptr;
#else
    void * fp_vkGetBufferMemoryRequirements2KHR{};
#endif
#if (defined(VK_KHR_get_memory_requirements2))
    PFN_vkGetImageMemoryRequirements2KHR fp_vkGetImageMemoryRequirements2KHR = nullptr;
#else
    void * fp_vkGetImageMemoryRequirements2KHR{};
#endif
#if (defined(VK_KHR_get_memory_requirements2))
    PFN_vkGetImageSparseMemoryRequirements2KHR fp_vkGetImageSparseMemoryRequirements2KHR = nullptr;
#else
    void * fp_vkGetImageSparseMemoryRequirements2KHR{};
#endif
#if (defined(VK_KHR_maintenance4))
    PFN_vkGetDeviceBufferMemoryRequirementsKHR fp_vkGetDeviceBufferMemoryRequirementsKHR = nullptr;
#else
    void * fp_vkGetDeviceBufferMemoryRequirementsKHR{};
#endif
#if (defined(VK_KHR_maintenance4))
    PFN_vkGetDeviceImageMemoryRequirementsKHR fp_vkGetDeviceImageMemoryRequirementsKHR = nullptr;
#else
    void * fp_vkGetDeviceImageMemoryRequirementsKHR{};
#endif
#if (defined(VK_KHR_maintenance4))
    PFN_vkGetDeviceImageSparseMemoryRequirementsKHR fp_vkGetDeviceImageSparseMemoryRequirementsKHR = nullptr;
#else
    void * fp_vkGetDeviceImageSparseMemoryRequirementsKHR{};
#endif
#if (defined(VK_KHR_sampler_ycbcr_conversion))
    PFN_vkCreateSamplerYcbcrConversionKHR fp_vkCreateSamplerYcbcrConversionKHR = nullptr;
#else
    void * fp_vkCreateSamplerYcbcrConversionKHR{};
#endif
#if (defined(VK_KHR_sampler_ycbcr_conversion))
    PFN_vkDestroySamplerYcbcrConversionKHR fp_vkDestroySamplerYcbcrConversionKHR = nullptr;
#else
    void * fp_vkDestroySamplerYcbcrConversionKHR{};
#endif
#if (defined(VK_KHR_maintenance3))
    PFN_vkGetDescriptorSetLayoutSupportKHR fp_vkGetDescriptorSetLayoutSupportKHR = nullptr;
#else
    void * fp_vkGetDescriptorSetLayoutSupportKHR{};
#endif
#if (defined(VK_EXT_calibrated_timestamps))
    PFN_vkGetCalibratedTimestampsEXT fp_vkGetCalibratedTimestampsEXT = nullptr;
#else
    void * fp_vkGetCalibratedTimestampsEXT{};
#endif
#if (defined(VK_KHR_create_renderpass2))
    PFN_vkCreateRenderPass2KHR fp_vkCreateRenderPass2KHR = nullptr;
#else
    void * fp_vkCreateRenderPass2KHR{};
#endif
#if (defined(VK_KHR_create_renderpass2))
    PFN_vkCmdBeginRenderPass2KHR fp_vkCmdBeginRenderPass2KHR = nullptr;
#else
    void * fp_vkCmdBeginRenderPass2KHR{};
#endif
#if (defined(VK_KHR_create_renderpass2))
    PFN_vkCmdNextSubpass2KHR fp_vkCmdNextSubpass2KHR = nullptr;
#else
    void * fp_vkCmdNextSubpass2KHR{};
#endif
#if (defined(VK_KHR_create_renderpass2))
    PFN_vkCmdEndRenderPass2KHR fp_vkCmdEndRenderPass2KHR = nullptr;
#else
    void * fp_vkCmdEndRenderPass2KHR{};
#endif
#if (defined(VK_KHR_timeline_semaphore))
    PFN_vkGetSemaphoreCounterValueKHR fp_vkGetSemaphoreCounterValueKHR = nullptr;
#else
    void * fp_vkGetSemaphoreCounterValueKHR{};
#endif
#if (defined(VK_KHR_timeline_semaphore))
    PFN_vkWaitSemaphoresKHR fp_vkWaitSemaphoresKHR = nullptr;
#else
    void * fp_vkWaitSemaphoresKHR{};
#endif
#if (defined(VK_KHR_timeline_semaphore))
    PFN_vkSignalSemaphoreKHR fp_vkSignalSemaphoreKHR = nullptr;
#else
    void * fp_vkSignalSemaphoreKHR{};
#endif
#if (defined(VK_AMD_draw_indirect_count))
    PFN_vkCmdDrawIndirectCountAMD fp_vkCmdDrawIndirectCountAMD = nullptr;
#else
    void * fp_vkCmdDrawIndirectCountAMD{};
#endif
#if (defined(VK_AMD_draw_indirect_count))
    PFN_vkCmdDrawIndexedIndirectCountAMD fp_vkCmdDrawIndexedIndirectCountAMD = nullptr;
#else
    void * fp_vkCmdDrawIndexedIndirectCountAMD{};
#endif
#if (defined(VK_NV_ray_tracing))
    PFN_vkGetRayTracingShaderGroupHandlesNV fp_vkGetRayTracingShaderGroupHandlesNV = nullptr;
#else
    void * fp_vkGetRayTracingShaderGroupHandlesNV{};
#endif
#if (defined(VK_KHR_buffer_device_address))
    PFN_vkGetBufferOpaqueCaptureAddressKHR fp_vkGetBufferOpaqueCaptureAddressKHR = nullptr;
#else
    void * fp_vkGetBufferOpaqueCaptureAddressKHR{};
#endif
#if (defined(VK_EXT_buffer_device_address))
    PFN_vkGetBufferDeviceAddressEXT fp_vkGetBufferDeviceAddressEXT = nullptr;
#else
    void * fp_vkGetBufferDeviceAddressEXT{};
#endif
#if (defined(VK_KHR_buffer_device_address))
    PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR fp_vkGetDeviceMemoryOpaqueCaptureAddressKHR = nullptr;
#else
    void * fp_vkGetDeviceMemoryOpaqueCaptureAddressKHR{};
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetCullModeEXT fp_vkCmdSetCullModeEXT = nullptr;
#else
    void * fp_vkCmdSetCullModeEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetFrontFaceEXT fp_vkCmdSetFrontFaceEXT = nullptr;
#else
    void * fp_vkCmdSetFrontFaceEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetPrimitiveTopologyEXT fp_vkCmdSetPrimitiveTopologyEXT = nullptr;
#else
    void * fp_vkCmdSetPrimitiveTopologyEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetViewportWithCountEXT fp_vkCmdSetViewportWithCountEXT = nullptr;
#else
    void * fp_vkCmdSetViewportWithCountEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetScissorWithCountEXT fp_vkCmdSetScissorWithCountEXT = nullptr;
#else
    void * fp_vkCmdSetScissorWithCountEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdBindVertexBuffers2EXT fp_vkCmdBindVertexBuffers2EXT = nullptr;
#else
    void * fp_vkCmdBindVertexBuffers2EXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetDepthTestEnableEXT fp_vkCmdSetDepthTestEnableEXT = nullptr;
#else
    void * fp_vkCmdSetDepthTestEnableEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetDepthWriteEnableEXT fp_vkCmdSetDepthWriteEnableEXT = nullptr;
#else
    void * fp_vkCmdSetDepthWriteEnableEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetDepthCompareOpEXT fp_vkCmdSetDepthCompareOpEXT = nullptr;
#else
    void * fp_vkCmdSetDepthCompareOpEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetDepthBoundsTestEnableEXT fp_vkCmdSetDepthBoundsTestEnableEXT = nullptr;
#else
    void * fp_vkCmdSetDepthBoundsTestEnableEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetStencilTestEnableEXT fp_vkCmdSetStencilTestEnableEXT = nullptr;
#else
    void * fp_vkCmdSetStencilTestEnableEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetStencilOpEXT fp_vkCmdSetStencilOpEXT = nullptr;
#else
    void * fp_vkCmdSetStencilOpEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetRasterizerDiscardEnableEXT fp_vkCmdSetRasterizerDiscardEnableEXT = nullptr;
#else
    void * fp_vkCmdSetRasterizerDiscardEnableEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetDepthBiasEnableEXT fp_vkCmdSetDepthBiasEnableEXT = nullptr;
#else
    void * fp_vkCmdSetDepthBiasEnableEXT{};
#endif
#if (defined(VK_EXT_extended_dynamic_state2)) || (defined(VK_EXT_shader_object))
    PFN_vkCmdSetPrimitiveRestartEnableEXT fp_vkCmdSetPrimitiveRestartEnableEXT = nullptr;
#else
    void * fp_vkCmdSetPrimitiveRestartEnableEXT{};
#endif
#if (defined(VK_EXT_private_data))
    PFN_vkCreatePrivateDataSlotEXT fp_vkCreatePrivateDataSlotEXT = nullptr;
#else
    void * fp_vkCreatePrivateDataSlotEXT{};
#endif
#if (defined(VK_EXT_private_data))
    PFN_vkDestroyPrivateDataSlotEXT fp_vkDestroyPrivateDataSlotEXT = nullptr;
#else
    void * fp_vkDestroyPrivateDataSlotEXT{};
#endif
#if (defined(VK_EXT_private_data))
    PFN_vkSetPrivateDataEXT fp_vkSetPrivateDataEXT = nullptr;
#else
    void * fp_vkSetPrivateDataEXT{};
#endif
#if (defined(VK_EXT_private_data))
    PFN_vkGetPrivateDataEXT fp_vkGetPrivateDataEXT = nullptr;
#else
    void * fp_vkGetPrivateDataEXT{};
#endif
#if (defined(VK_KHR_copy_commands2))
    PFN_vkCmdCopyBuffer2KHR fp_vkCmdCopyBuffer2KHR = nullptr;
#else
    void * fp_vkCmdCopyBuffer2KHR{};
#endif
#if (defined(VK_KHR_copy_commands2))
    PFN_vkCmdCopyImage2KHR fp_vkCmdCopyImage2KHR = nullptr;
#else
    void * fp_vkCmdCopyImage2KHR{};
#endif
#if (defined(VK_KHR_copy_commands2))
    PFN_vkCmdBlitImage2KHR fp_vkCmdBlitImage2KHR = nullptr;
#else
    void * fp_vkCmdBlitImage2KHR{};
#endif
#if (defined(VK_KHR_copy_commands2))
    PFN_vkCmdCopyBufferToImage2KHR fp_vkCmdCopyBufferToImage2KHR = nullptr;
#else
    void * fp_vkCmdCopyBufferToImage2KHR{};
#endif
#if (defined(VK_KHR_copy_commands2))
    PFN_vkCmdCopyImageToBuffer2KHR fp_vkCmdCopyImageToBuffer2KHR = nullptr;
#else
    void * fp_vkCmdCopyImageToBuffer2KHR{};
#endif
#if (defined(VK_KHR_copy_commands2))
    PFN_vkCmdResolveImage2KHR fp_vkCmdResolveImage2KHR = nullptr;
#else
    void * fp_vkCmdResolveImage2KHR{};
#endif
#if (defined(VK_KHR_synchronization2))
    PFN_vkCmdSetEvent2KHR fp_vkCmdSetEvent2KHR = nullptr;
#else
    void * fp_vkCmdSetEvent2KHR{};
#endif
#if (defined(VK_KHR_synchronization2))
    PFN_vkCmdResetEvent2KHR fp_vkCmdResetEvent2KHR = nullptr;
#else
    void * fp_vkCmdResetEvent2KHR{};
#endif
#if (defined(VK_KHR_synchronization2))
    PFN_vkCmdWaitEvents2KHR fp_vkCmdWaitEvents2KHR = nullptr;
#else
    void * fp_vkCmdWaitEvents2KHR{};
#endif
#if (defined(VK_KHR_synchronization2))
    PFN_vkCmdPipelineBarrier2KHR fp_vkCmdPipelineBarrier2KHR = nullptr;
#else
    void * fp_vkCmdPipelineBarrier2KHR{};
#endif
#if (defined(VK_KHR_synchronization2))
    PFN_vkQueueSubmit2KHR fp_vkQueueSubmit2KHR = nullptr;
#else
    void * fp_vkQueueSubmit2KHR{};
#endif
#if (defined(VK_KHR_synchronization2))
    PFN_vkCmdWriteTimestamp2KHR fp_vkCmdWriteTimestamp2KHR = nullptr;
#else
    void * fp_vkCmdWriteTimestamp2KHR{};
#endif
#if (defined(VK_KHR_dynamic_rendering))
    PFN_vkCmdBeginRenderingKHR fp_vkCmdBeginRenderingKHR = nullptr;
#else
    void * fp_vkCmdBeginRenderingKHR{};
#endif
#if (defined(VK_KHR_dynamic_rendering))
    PFN_vkCmdEndRenderingKHR fp_vkCmdEndRenderingKHR = nullptr;
#else
    void * fp_vkCmdEndRenderingKHR{};
#endif
#if (defined(VK_EXT_host_image_copy)) || (defined(VK_EXT_image_compression_control))
    PFN_vkGetImageSubresourceLayout2EXT fp_vkGetImageSubresourceLayout2EXT = nullptr;
#else
    void * fp_vkGetImageSubresourceLayout2EXT{};
#endif
    bool is_populated() const { return populated; }
    VkDevice device = VK_NULL_HANDLE;
private:
     bool populated = false;
};

} // namespace vkb