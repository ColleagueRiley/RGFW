/*
	NSView.h
	Application Kit
	Copyright (c) 1994-2021, Apple Inc.
	All rights reserved.
*/

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "../../macros.h"
#include "../types.h"


// Bitset options for the autoresizingMask
typedef NS_OPTIONS(NSUInteger, NSAutoresizingMaskOptions) {
	NSViewNotSizable			=  0,
	NSViewMinXMargin			=  1,
	NSViewWidthSizable			=  2,
	NSViewMaxXMargin			=  4,
	NSViewMinYMargin			=  8,
	NSViewHeightSizable			= 16,
	NSViewMaxYMargin			= 32
};

typedef NS_ENUM(NSUInteger, NSBorderType) {
	NSNoBorder				= 0,
	NSLineBorder			= 1,
	NSBezelBorder			= 2,
	NSGrooveBorder			= 3
};

typedef NS_ENUM(NSInteger, NSViewLayerContentsRedrawPolicy) {
	// Leave the layer's contents alone. Never mark the layer as needing display, or draw the view's contents to the layer
	NSViewLayerContentsRedrawNever = 0,
	// Map view -setNeedsDisplay...: activity to the layer, and redraw affected layer parts by invoking the view's -drawRect:, but don't mark the view or layer as needing display when the view's size changes.
	NSViewLayerContentsRedrawOnSetNeedsDisplay = 1,
	// Resize the layer and redraw the view to the layer when the view's size changes. If the resize is animated, AppKit will drive the resize animation itself and will do this resize+redraw at each step of the animation. Affected parts of the layer will also be redrawn when the view is marked as needing display. (This mode is a superset of NSViewLayerContentsRedrawOnSetNeedsDisplay.)
	NSViewLayerContentsRedrawDuringViewResize = 2,
	// Resize the layer and redraw the view to the layer when the view's size changes. This will be done just once at the beginning of a resize animation, not at each frame of the animation. Affected parts of the layer will also be redrawn when the view is marked as needing display. (This mode is a superset of NSViewLayerContentsRedrawOnSetNeedsDisplay.)
	NSViewLayerContentsRedrawBeforeViewResize = 3,
	// When a view is resized, the layer contents will be redrawn once and the contents will crossfade from the old value to the new value. Use this in conjunction with the layerContentsPlacement to get a nice crossfade animation for complex layer-backed views that can't correctly update on each step of the animation
	NSViewLayerContentsRedrawCrossfade API_AVAILABLE(macos(10.9)) = 4
} API_AVAILABLE(macos(10.6));

typedef NS_ENUM(NSInteger, NSViewLayerContentsPlacement) {
	NSViewLayerContentsPlacementScaleAxesIndependently      =  0,
	NSViewLayerContentsPlacementScaleProportionallyToFit    =  1,
	NSViewLayerContentsPlacementScaleProportionallyToFill   =  2,
	NSViewLayerContentsPlacementCenter                      =  3,
	NSViewLayerContentsPlacementTop                         =  4,
	NSViewLayerContentsPlacementTopRight                    =  5,
	NSViewLayerContentsPlacementRight                       =  6,
	NSViewLayerContentsPlacementBottomRight                 =  7,
	NSViewLayerContentsPlacementBottom                      =  8,
	NSViewLayerContentsPlacementBottomLeft                  =  9,
	NSViewLayerContentsPlacementLeft                        = 10,
	NSViewLayerContentsPlacementTopLeft                     = 11
} API_AVAILABLE(macos(10.6));

typedef NSInteger NSTrackingRectTag;
typedef NSInteger NSToolTipTag;

// /* Constants for options when entering and exiting full screen mode */
// typedef const char* NSViewFullScreenModeOptionKey NS_TYPED_ENUM;
// APPKIT_EXTERN NSViewFullScreenModeOptionKey const NSFullScreenModeAllScreens API_AVAILABLE(macos(10.5));                      // NSNumber numberWithBool:YES/NO
// APPKIT_EXTERN NSViewFullScreenModeOptionKey const NSFullScreenModeSetting API_AVAILABLE(macos(10.5));                         // NSDictionary (obtained from CGSDisplay based functions)
// APPKIT_EXTERN NSViewFullScreenModeOptionKey const NSFullScreenModeWindowLevel API_AVAILABLE(macos(10.5));                     // NSNumber numberWithInt:windowLevel
// APPKIT_EXTERN NSViewFullScreenModeOptionKey const NSFullScreenModeApplicationPresentationOptions API_AVAILABLE(macos(10.5));  // NSNumber numberWithUnsignedInteger:(NSApplicationPresentationOptions flags)
//
//
//
// /* NSDefinitionPresentationTypeKey is an optional key in 'options' that specifies the presentation type of the definition display.  The possible values are NSDefinitionPresentationTypeOverlay that produces a small overlay window at the string location, or NSDefinitionPresentationTypeDictionaryApplication that invokes 'Dictionary' application to display the definition.  Without this option, the definition will be shown in either of those presentation forms depending on the 'Contextual Menu:' setting in Dictionary application preferences.
//  */
// typedef const char* NSDefinitionOptionKey NS_TYPED_ENUM;
// APPKIT_EXTERN NSDefinitionOptionKey const NSDefinitionPresentationTypeKey API_AVAILABLE(macos(10.6));
//
// typedef const char* NSDefinitionPresentationType NS_TYPED_ENUM;
// APPKIT_EXTERN NSDefinitionPresentationType const NSDefinitionPresentationTypeOverlay API_AVAILABLE(macos(10.6));
// APPKIT_EXTERN NSDefinitionPresentationType const NSDefinitionPresentationTypeDictionaryApplication API_AVAILABLE(macos(10.6));

/* Notifications */

/* Sent when the frame changes for a view. This is only sent if postsFrameChangedNotifications is set to YES.
 */
APPKIT_EXTERN NSNotificationName NSViewFrameDidChangeNotification;
APPKIT_EXTERN NSNotificationName NSViewFocusDidChangeNotification API_DEPRECATED("", macos(10.0,10.4));

/* This notification is sent whenever the views bounds change and the frame does not.  That is, it is sent whenever the view's bounds are translated, scaled or rotated, but NOT when the bounds change as a result of, for example, setFrameSize:.
 */
APPKIT_EXTERN NSNotificationName NSViewBoundsDidChangeNotification;


/* This notification is sent whenever an NSView that has an attached NSOpenGLContext changes size or changes screens (thus potentially changing graphics hardware drivers).
 */
APPKIT_EXTERN NSNotificationName NSViewGlobalFrameDidChangeNotification API_DEPRECATED("Use NSOpenGLView instead.", macos(10.0,10.14));

/* This notification is sent whenever tracking areas should be recalculated for the view.  It is sent after the view receives -updateTrackingAreas.
 */
APPKIT_EXTERN NSNotificationName NSViewDidUpdateTrackingAreasNotification API_AVAILABLE(macos(10.5));


#ifdef __cplusplus
}
#endif