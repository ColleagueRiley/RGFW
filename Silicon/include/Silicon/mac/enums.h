/*
Copyright (C) 2022-2023 EimaMei/Sacode

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "../macros.h"
#include "types.h"

#include "headers/NSWindow.h"
#include "headers/NSView.h"
#include "headers/NSEvent.h"
#include "headers/NSFontManager.h"
#include "headers/NSFontDescriptor.h"
#include "headers/NSCell.h"
#include "headers/NSButtonCell.h"
#include "headers/NSPasteboard.h"
#include "headers/NSBitmapImageRep.h"
#include "headers/NSDragging.h"

#include "headers/NSPathUtilities.h"


typedef NS_ENUM(NSUInteger, NSBackingStoreType) {
    NSBackingStoreRetained = 0U,
    NSBackingStoreNonretained = 1U,
    NSBackingStoreBuffered = 2U
};

typedef enum NSApplicationActivationPolicy {
    NSApplicationActivationPolicyRegular,
    NSApplicationActivationPolicyAccessory,
    NSApplicationActivationPolicyProhibited
} NSApplicationActivationPolicy;


/*
 ** Attribute names for [NSOpenGLPixelFormat initWithAttributes]
 ** and [NSOpenGLPixelFormat getValues:forAttribute:forVirtualScreen].
 */
enum {
    NSOpenGLPFAAllRenderers          NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   1,	/* choose from all available renderers          */
    NSOpenGLPFATripleBuffer          NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   3,	/* choose a triple buffered pixel format        */
    NSOpenGLPFADoubleBuffer          NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   5,	/* choose a double buffered pixel format        */
    NSOpenGLPFAAuxBuffers            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   7,	/* number of aux buffers                        */
    NSOpenGLPFAColorSize             NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   8,	/* number of color buffer bits                  */
    NSOpenGLPFAAlphaSize             NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  11,	/* number of alpha component bits               */
    NSOpenGLPFADepthSize             NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  12,	/* number of depth buffer bits                  */
    NSOpenGLPFAStencilSize           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  13,	/* number of stencil buffer bits                */
    NSOpenGLPFAAccumSize             NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  14,	/* number of accum buffer bits                  */
    NSOpenGLPFAMinimumPolicy         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  51,	/* never choose smaller buffers than requested  */
    NSOpenGLPFAMaximumPolicy         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  52,	/* choose largest buffers of type requested     */
    NSOpenGLPFASampleBuffers         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  55,	/* number of multi sample buffers               */
    NSOpenGLPFASamples               NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  56,	/* number of samples per multi sample buffer    */
    NSOpenGLPFAAuxDepthStencil       NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  57,	/* each aux buffer has its own depth stencil    */
    NSOpenGLPFAColorFloat            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  58,	/* color buffers store floating point pixels    */
    NSOpenGLPFAMultisample           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  59,    /* choose multisampling                         */
    NSOpenGLPFASupersample           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  60,    /* choose supersampling                         */
    NSOpenGLPFASampleAlpha           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  61,    /* request alpha filtering                      */
    NSOpenGLPFARendererID            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  70,	/* request renderer by ID                       */
    NSOpenGLPFANoRecovery            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  72,	/* disable all failure recovery systems         */
    NSOpenGLPFAAccelerated           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  73,	/* choose a hardware accelerated renderer       */
    NSOpenGLPFAClosestPolicy         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  74,	/* choose the closest color buffer to request   */
    NSOpenGLPFABackingStore          NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  76,	/* back buffer contents are valid after swap    */
    NSOpenGLPFAScreenMask            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  84,	/* bit mask of supported physical screens       */
    NSOpenGLPFAAllowOfflineRenderers NS_OPENGL_ENUM_DEPRECATED(10.5, 10.14)  =  96,  /* allow use of offline renderers               */
    NSOpenGLPFAAcceleratedCompute    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  97,	/* choose a hardware accelerated compute device */
    
    NSOpenGLPFAOpenGLProfile         NS_OPENGL_ENUM_DEPRECATED(10.7, 10.14)  =  99,    /* specify an OpenGL Profile to use             */
    NSOpenGLProfileVersion3_2Core    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  = 0x3200, /* The 3.2 Profile of OpenGL */
    NSOpenGLProfileVersion4_1Core    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  = 0x3200, /* The 4.1 profile of OpenGL */

    NSOpenGLPFAVirtualScreenCount    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  = 128,	/* number of virtual screens in this format     */

    NSOpenGLPFAStereo                API_DEPRECATED("", macos(10.0,10.12))     =   6,
    NSOpenGLPFAOffScreen             API_DEPRECATED("", macos(10.0,10.7))      =  53,
    NSOpenGLPFAFullScreen            API_DEPRECATED("", macos(10.0,10.6))      =  54,
    NSOpenGLPFASingleRenderer        API_DEPRECATED("", macos(10.0,10.9))      =  71,
    NSOpenGLPFARobust                API_DEPRECATED("", macos(10.0,10.5))      =  75,
    NSOpenGLPFAMPSafe                API_DEPRECATED("", macos(10.0,10.5))      =  78,
    NSOpenGLPFAWindow                API_DEPRECATED("", macos(10.0,10.9))      =  80,
    NSOpenGLPFAMultiScreen           API_DEPRECATED("", macos(10.0,10.5))      =  81,
    NSOpenGLPFACompliant             API_DEPRECATED("", macos(10.0,10.9))      =  83,
    NSOpenGLPFAPixelBuffer           API_DEPRECATED("", macos(10.3,10.7))      =  90,
    NSOpenGLPFARemotePixelBuffer     API_DEPRECATED("", macos(10.3,10.7))      =  91,
};
typedef uint32_t NSOpenGLPixelFormatAttribute NS_OPENGL_DEPRECATED(10.0, 10.14);


/* Parameter names for NSOpenGLContext -setValues:forParameter: and -getValues:forParameter: */
typedef NS_ENUM(NSInteger, NSOpenGLContextParameter) {
    NSOpenGLContextParameterSwapInterval           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 222, /* 1 param.  0 -> Don't sync, 1 -> Sync to vertical retrace     */
    NSOpenGLContextParameterSurfaceOrder           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 235, /* 1 param.  1 -> Above Window (default), -1 -> Below Window    */
    NSOpenGLContextParameterSurfaceOpacity         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 236, /* 1 param.  1-> Surface is opaque (default), 0 -> non-opaque   */
    NSOpenGLContextParameterSurfaceBackingSize     NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 304, /* 2 params.  Width/height of surface backing size              */
    NSOpenGLContextParameterReclaimResources       NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 308, /* 0 params.                                                    */
    NSOpenGLContextParameterCurrentRendererID      NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 309, /* 1 param.   Retrieves the current renderer ID                 */
    NSOpenGLContextParameterGPUVertexProcessing    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 310, /* 1 param.   Currently processing vertices with GPU (get)      */
    NSOpenGLContextParameterGPUFragmentProcessing  NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 311, /* 1 param.   Currently processing fragments with GPU (get)     */
    NSOpenGLContextParameterHasDrawable            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 314, /* 1 param.   Boolean returned if drawable is attached          */
    NSOpenGLContextParameterMPSwapsInFlight        NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 315, /* 1 param.   Max number of swaps queued by the MP GL engine    */

    NSOpenGLContextParameterSwapRectangle API_DEPRECATED("", macos(10.0,10.14)) = 200, /* 4 params.  Set or get the swap rectangle {x, y, w, h} */
    NSOpenGLContextParameterSwapRectangleEnable API_DEPRECATED("", macos(10.0,10.14)) = 201, /* Enable or disable the swap rectangle */
    NSOpenGLContextParameterRasterizationEnable API_DEPRECATED("", macos(10.0,10.14)) = 221, /* Enable or disable all rasterization */
    NSOpenGLContextParameterStateValidation API_DEPRECATED("", macos(10.0,10.14)) = 301, /* Validate state for multi-screen functionality */
    NSOpenGLContextParameterSurfaceSurfaceVolatile API_DEPRECATED("", macos(10.0,10.14))  = 306, /* 1 param.   Surface volatile state */
} NS_OPENGL_DEPRECATED(10.0, 10.14);

#ifdef __cplusplus
}
#endif