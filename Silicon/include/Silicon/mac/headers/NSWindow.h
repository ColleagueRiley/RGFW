/*
	NSWindow.h
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


typedef NS_OPTIONS(NSUInteger, NSWindowStyleMask) {
	NSWindowStyleMaskBorderless = 0,
	NSWindowStyleMaskTitled = 1 << 0,
	NSWindowStyleMaskClosable = 1 << 1,
	NSWindowStyleMaskMiniaturizable = 1 << 2,
	NSWindowStyleMaskResizable	= 1 << 3,

	/* Specifies a window with textured background. Textured windows generally don't draw a top border line under the titlebar/toolbar. To get that line, use the NSUnifiedTitleAndToolbarWindowMask mask.
	 */
	NSWindowStyleMaskTexturedBackground API_DEPRECATED("Textured window style should no longer be used", macos(10.2, 11.0)) = 1 << 8,

	/* Specifies a window whose titlebar and toolbar have a unified look - that is, a continuous background. Under the titlebar and toolbar a horizontal separator line will appear.
	 */
	NSWindowStyleMaskUnifiedTitleAndToolbar = 1 << 12,

	/* When present, the window will appear full screen. This mask is automatically toggled when toggleFullScreen: is called.
	 */
	NSWindowStyleMaskFullScreen API_AVAILABLE(macos(10.7)) = 1 << 14,

	/* If set, the contentView will consume the full size of the window; it can be combined with other window style masks, but is only respected for windows with a titlebar.
	 Utilizing this mask opts-in to layer-backing. Utilize the contentLayoutRect or auto-layout contentLayoutGuide to layout views underneath the titlebar/toolbar area.
	 */
	NSWindowStyleMaskFullSizeContentView API_AVAILABLE(macos(10.10)) = 1 << 15,

	/* The following are only applicable for NSPanel (or a subclass thereof)
	 */
	NSWindowStyleMaskUtilityWindow			= 1 << 4,
	NSWindowStyleMaskDocModalWindow 		= 1 << 6,
	NSWindowStyleMaskNonactivatingPanel		= 1 << 7, // Specifies that a panel that does not activate the owning application
	NSWindowStyleMaskHUDWindow API_AVAILABLE(macos(10.6)) = 1 << 13 // Specifies a heads up display panel
};

// Additional NSModalResponse values
static const NSModalResponse NSModalResponseOK = 1;
static const NSModalResponse NSModalResponseCancel = 0;

/* used with NSRunLoop's performSelector:target:argument:order:modes: */
enum {
	NSDisplayWindowRunLoopOrdering	= 600000,
	NSResetCursorRectsRunLoopOrdering	= 700000
};

typedef NS_ENUM(NSUInteger, NSWindowSharingType) {
	NSWindowSharingNone = 0,                // Window contents may not be read by another process
	NSWindowSharingReadOnly = 1,            // Window contents may be read but not modified by another process
	NSWindowSharingReadWrite = 2            // Window contents may be read or modified by another process
} API_AVAILABLE(macos(10.5));

typedef NS_OPTIONS(NSUInteger, NSWindowCollectionBehavior) {
	NSWindowCollectionBehaviorDefault = 0,
	NSWindowCollectionBehaviorCanJoinAllSpaces = 1 << 0,
	NSWindowCollectionBehaviorMoveToActiveSpace = 1 << 1,

	/* You may specify at most one of NSWindowCollectionBehaviorManaged, NSWindowCollectionBehaviorTransient, or NSWindowCollectionBehaviorStationary.  If unspecified, the window gets the default behavior determined by its window level */
	NSWindowCollectionBehaviorManaged API_AVAILABLE(macos(10.6)) = 1 << 2,         // participates in spaces, exposé.  Default behavior if windowLevel == NSNormalWindowLevel
	NSWindowCollectionBehaviorTransient API_AVAILABLE(macos(10.6)) = 1 << 3,       // floats in spaces, hidden by exposé.  Default behavior if windowLevel != NSNormalWindowLevel
	NSWindowCollectionBehaviorStationary API_AVAILABLE(macos(10.6)) = 1 << 4,      // unaffected by exposé.  Stays visible and stationary, like desktop window

	/* You may specify at most one of NSWindowCollectionBehaviorParticipatesInCycle or NSWindowCollectionBehaviorIgnoresCycle.  If unspecified, the window gets the default behavior determined by its window level */
	NSWindowCollectionBehaviorParticipatesInCycle API_AVAILABLE(macos(10.6)) = 1 << 5,     // default behavior if windowLevel == NSNormalWindowLevel
	NSWindowCollectionBehaviorIgnoresCycle API_AVAILABLE(macos(10.6)) = 1 << 6,            // default behavior if windowLevel != NSNormalWindowLevel

	/* You may specify at most one of NSWindowCollectionBehaviorFullScreenPrimary, NSWindowCollectionBehaviorFullScreenAuxiliary, or NSWindowCollectionBehaviorFullScreenNone. */
	NSWindowCollectionBehaviorFullScreenPrimary API_AVAILABLE(macos(10.7)) = 1 << 7,       // the frontmost window with this collection behavior will be the fullscreen window.
	NSWindowCollectionBehaviorFullScreenAuxiliary API_AVAILABLE(macos(10.7)) = 1 << 8,     // windows with this collection behavior can be shown with the fullscreen window.
	NSWindowCollectionBehaviorFullScreenNone API_AVAILABLE(macos(10.7)) = 1 << 9, // The window can not be made fullscreen when this bit is set

	/* 	You may specify at most one of NSWindowCollectionBehaviorFullScreenAllowsTiling or NSWindowCollectionBehaviorFullScreenDisallowsTiling, or an assertion will be raised.

	 The default behavior is to allow any window to participate in full screen tiling, as long as it meets certain requirements, such as being resizable and not a panel or sheet. Windows which are not full screen capable can still become a secondary tile in full screen. A window can explicitly allow itself to be placed into a full screen tile by including NSWindowCollectionBehaviorFullScreenAllowsTiling. Even if a window allows itself to be placed in a tile, it still may not be put in the tile if its minFullScreenContentSize is too large to fit. A window can explicitly disallow itself from being placed in a full screen tile by including NSWindowCollectionBehaviorFullScreenDisallowsTiling. This is useful for non-full screen capable windows to explicitly prevent themselves from being tiled. It can also be used by a full screen window to prevent any other windows from being placed in its full screen tile. */
	NSWindowCollectionBehaviorFullScreenAllowsTiling API_AVAILABLE(macos(10.11)) = 1 << 11,       // This window can be a full screen tile window. It does not have to have FullScreenPrimary set.
	NSWindowCollectionBehaviorFullScreenDisallowsTiling API_AVAILABLE(macos(10.11)) = 1 << 12      // This window can NOT be made a full screen tile window; it still may be allowed to be a regular FullScreenPrimary window.
} API_AVAILABLE(macos(10.5));


typedef NS_ENUM(NSInteger, NSWindowAnimationBehavior) {
	NSWindowAnimationBehaviorDefault = 0,       // let AppKit infer animation behavior for this window
	NSWindowAnimationBehaviorNone = 2,          // suppress inferred animations (don't animate)

	NSWindowAnimationBehaviorDocumentWindow = 3,
	NSWindowAnimationBehaviorUtilityWindow = 4,
	NSWindowAnimationBehaviorAlertPanel = 5
} API_AVAILABLE(macos(10.7));


/* Options used in +windowNumbersWithOptions:.  If no options are specified, the returned list contains window numbers for visible windows on the active space belonging to the calling application. */
typedef NS_OPTIONS(NSUInteger, NSWindowNumberListOptions) {
	NSWindowNumberListAllApplications = 1 << 0,
	NSWindowNumberListAllSpaces = 1 << 4
} API_AVAILABLE(macos(10.6));

typedef NS_OPTIONS(NSUInteger, NSWindowOcclusionState) {
	/* If set, at least part of the window is visible. If not set, the entire window is occluded. Windows with non-rectangular shapes may be completely occluded on screen but still count as visible, if their bounding box falls into a visible region. Windows that are completely transparent may also still count as visible. */
	NSWindowOcclusionStateVisible = 1UL << 1,
} API_AVAILABLE(macos(10.9));

static const NSInteger NSNormalWindowLevel = kCGNormalWindowLevel;
static const NSInteger NSFloatingWindowLevel = kCGFloatingWindowLevel;
static const NSInteger NSSubmenuWindowLevel = kCGTornOffMenuWindowLevel;
static const NSInteger NSTornOffMenuWindowLevel = kCGTornOffMenuWindowLevel;
static const NSInteger NSMainMenuWindowLevel = kCGMainMenuWindowLevel;
static const NSInteger NSStatusWindowLevel = kCGStatusWindowLevel;
static const NSInteger NSModalPanelWindowLevel = kCGModalPanelWindowLevel;
static const NSInteger NSPopUpMenuWindowLevel = kCGPopUpMenuWindowLevel;
static const NSInteger NSScreenSaverWindowLevel = kCGScreenSaverWindowLevel;

typedef NS_ENUM(NSUInteger, NSSelectionDirection) {
	NSDirectSelection = 0,
	NSSelectingNext,
	NSSelectingPrevious
};

/* Standard window buttons */
typedef NS_ENUM(NSUInteger, NSWindowButton) {
	NSWindowCloseButton,
	NSWindowMiniaturizeButton,
	NSWindowZoomButton,
	NSWindowToolbarButton,
	NSWindowDocumentIconButton,
	NSWindowDocumentVersionsButton API_AVAILABLE(macos(10.7)) = 6,
};

typedef NS_ENUM(NSInteger, NSWindowTitleVisibility) {
	/* The default mode has a normal window title and titlebar buttons. */
	NSWindowTitleVisible = 0,
	/* The always hidden mode hides the title and moves the toolbar up into the area previously occupied by the title. */
	NSWindowTitleHidden = 1,
} API_AVAILABLE(macos(10.10));

typedef NS_ENUM(NSInteger, NSWindowToolbarStyle) {
	// The default value. The style will be determined by the window's given configuration
	NSWindowToolbarStyleAutomatic,
	// The toolbar will appear below the window title
	NSWindowToolbarStyleExpanded,
	// The toolbar will appear below the window title and the items in the toolbar will attempt to have equal widths when possible
	NSWindowToolbarStylePreference,
	// The window title will appear inline with the toolbar when visible
	NSWindowToolbarStyleUnified,
	// Same as NSWindowToolbarStyleUnified, but with reduced margins in the toolbar allowing more focus to be on the contents of the window
	NSWindowToolbarStyleUnifiedCompact
} API_AVAILABLE(macos(11.0));

static const NSTimeInterval NSEventDurationForever = DBL_MAX;

typedef NS_ENUM(NSInteger, NSWindowUserTabbingPreference) {
	NSWindowUserTabbingPreferenceManual,
	NSWindowUserTabbingPreferenceAlways,
	NSWindowUserTabbingPreferenceInFullScreen,
} API_AVAILABLE(macos(10.12));

typedef NS_ENUM(NSInteger, NSWindowTabbingMode) {
	NSWindowTabbingModeAutomatic, // The system automatically prefers to tab this window when appropriate
	NSWindowTabbingModePreferred, // The window explicitly should prefer to tab when shown
	NSWindowTabbingModeDisallowed // The window explicitly should not prefer to tab when shown
}  API_AVAILABLE(macos(10.12));

typedef NS_ENUM(NSInteger, NSTitlebarSeparatorStyle) {
	NSTitlebarSeparatorStyleAutomatic,
	NSTitlebarSeparatorStyleNone,
	NSTitlebarSeparatorStyleLine,
	NSTitlebarSeparatorStyleShadow
} API_AVAILABLE(macos(11.0));


/*typedef NSString * NSWindowFrameAutosaveName NS_SWIFT_BRIDGED_TYPEDEF;
typedef NSString * NSWindowPersistableFrameDescriptor NS_SWIFT_BRIDGED_TYPEDEF;
typedef NSString * NSWindowTabbingIdentifier NS_SWIFT_BRIDGED_TYPEDEF;*/


/* Notifications */
APPKIT_EXTERN NSNotificationName NSWindowDidBecomeKeyNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidBecomeMainNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidChangeScreenNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidDeminiaturizeNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidExposeNotification;			// userInfo key:  @"NSExposedRect"
APPKIT_EXTERN NSNotificationName NSWindowDidMiniaturizeNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidMoveNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidResignKeyNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidResignMainNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidResizeNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidUpdateNotification;
APPKIT_EXTERN NSNotificationName NSWindowWillCloseNotification;
APPKIT_EXTERN NSNotificationName NSWindowWillMiniaturizeNotification;
APPKIT_EXTERN NSNotificationName NSWindowWillMoveNotification;
APPKIT_EXTERN NSNotificationName NSWindowWillBeginSheetNotification;
APPKIT_EXTERN NSNotificationName NSWindowDidEndSheetNotification;

/* NSWindowDidChangeBackingPropertiesNotification is posted on 10.7.3 and later, when a window's backingScaleFactor and/or its colorSpace changes.  When running on a system version where this new notification is available, applications should use it instead of NSWindowDidChangeScreenProfileNotification to watch for changes to either of these backing store properties.  Many applications won't have any need to watch for this notification, but those that perform sophisticated color handling or manually manage their own caches of window-resolution-and/or/colorspace-appropriate bitmapped images will find this notification useful, as a prompt to invalidate their caches or schedule other reassessment for the new resolution and/or color space as needed.  The notification's userInfo dictionary specifies the window's previous backingScaleFactor and colorSpace.  You can compare these with the window's new backingScaleFactor and colorSpace at the time of the notification, to determine which of these two properties (potentially both) changed.
*/
APPKIT_EXTERN NSNotificationName const NSWindowDidChangeBackingPropertiesNotification API_AVAILABLE(macos(10.7)); // added in 10.7.3; userInfo keys: NSBackingPropertyOldScaleFactorKey, NSBackingPropertyOldColorSpaceKey

APPKIT_EXTERN const char* const NSBackingPropertyOldScaleFactorKey API_AVAILABLE(macos(10.7)); // added in 10.7.3; an NSNumber
APPKIT_EXTERN const char* const NSBackingPropertyOldColorSpaceKey API_AVAILABLE(macos(10.7));  // added in 10.7.3; an NSColorSpace


/* NSWindowDidChangeScreenProfileNotification is posted when a window's display's color profile changes, or when the window moves to a display that has a different color profile.  When running on 10.7.3 or later, this notification is still posted for compatibility, but modern applications should instead watch for NSWindowDidChangeBackingPropertiesNotification, which is posted for both color space and resolution changes, and facilitates handling both in a single update and redisplay pass.
*/
APPKIT_EXTERN NSNotificationName NSWindowDidChangeScreenProfileNotification;

/* NSWindowWillStartLiveResizeNotification is sent when the user starts a live resize operation via a mouseDown in the resize corner.  The notification will be sent before the window size is changed.  Note that this notification is sent once for a sequence of window resize operations */
APPKIT_EXTERN NSNotificationName const NSWindowWillStartLiveResizeNotification  API_AVAILABLE(macos(10.6));
/* NSWindowDidEndLiveResizeNotification is sent after the user ends a live resize operation via a mouseUp in the resize corner.  The notification will be sent after the final window size change.    Note that this notification is sent once for a sequence of window resize operations */
APPKIT_EXTERN NSNotificationName const NSWindowDidEndLiveResizeNotification  API_AVAILABLE(macos(10.6));
APPKIT_EXTERN NSNotificationName const NSWindowWillEnterFullScreenNotification API_AVAILABLE(macos(10.7));
APPKIT_EXTERN NSNotificationName const NSWindowDidEnterFullScreenNotification API_AVAILABLE(macos(10.7));
APPKIT_EXTERN NSNotificationName const NSWindowWillExitFullScreenNotification API_AVAILABLE(macos(10.7));
APPKIT_EXTERN NSNotificationName const NSWindowDidExitFullScreenNotification API_AVAILABLE(macos(10.7));
APPKIT_EXTERN NSNotificationName const NSWindowWillEnterVersionBrowserNotification API_AVAILABLE(macos(10.7));
APPKIT_EXTERN NSNotificationName const NSWindowDidEnterVersionBrowserNotification API_AVAILABLE(macos(10.7));
APPKIT_EXTERN NSNotificationName const NSWindowWillExitVersionBrowserNotification API_AVAILABLE(macos(10.7));
APPKIT_EXTERN NSNotificationName const NSWindowDidExitVersionBrowserNotification API_AVAILABLE(macos(10.7));
/* Upon receiving this notification, you can query the NSWindow for its current occlusion state. Note that this only notifies about changes in the state of the occlusion, not when the occlusion region changes. You can use this notification to increase responsiveness and save power, by halting any expensive calculations that the user can not see. */
APPKIT_EXTERN NSNotificationName const NSWindowDidChangeOcclusionStateNotification API_AVAILABLE(macos(10.9));

typedef NS_ENUM(NSUInteger, NSWindowBackingLocation) {
	NSWindowBackingLocationDefault = 0,        // System determines if window backing store is in VRAM or main memory
	NSWindowBackingLocationVideoMemory = 1,        // Window backing store is in VRAM
	NSWindowBackingLocationMainMemory = 2        // Window backing store is in main memory
} API_DEPRECATED("", macos(10.5,10.14));


/* Deprecated legacy style mask constants. Prefer to use NSWindowStyleMask values instead.
 */
static const NSWindowStyleMask NSBorderlessWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskBorderless", macos(10.0,10.12)) = NSWindowStyleMaskBorderless;
static const NSWindowStyleMask NSTitledWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskTitled", macos(10.0,10.12)) = NSWindowStyleMaskTitled;
static const NSWindowStyleMask NSClosableWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskClosable", macos(10.0,10.12)) = NSWindowStyleMaskClosable;
static const NSWindowStyleMask NSMiniaturizableWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskMiniaturizable", macos(10.0,10.12)) = NSWindowStyleMaskMiniaturizable;
static const NSWindowStyleMask NSResizableWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskResizable", macos(10.0,10.12)) = NSWindowStyleMaskResizable;
static const NSWindowStyleMask NSTexturedBackgroundWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskTexturedBackground", macos(10.0,10.12)) = NSWindowStyleMaskTexturedBackground;
static const NSWindowStyleMask NSUnifiedTitleAndToolbarWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskUnifiedTitleAndToolbar", macos(10.0,10.12)) = NSWindowStyleMaskUnifiedTitleAndToolbar;
static const NSWindowStyleMask NSFullScreenWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskFullScreen", macos(10.0,10.12)) = NSWindowStyleMaskFullScreen;
static const NSWindowStyleMask NSFullSizeContentViewWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskFullSizeContentView", macos(10.0,10.12)) = NSWindowStyleMaskFullSizeContentView;
static const NSWindowStyleMask NSUtilityWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskUtilityWindow", macos(10.0,10.12)) = NSWindowStyleMaskUtilityWindow;
static const NSWindowStyleMask NSDocModalWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskDocModalWindow", macos(10.0,10.12)) = NSWindowStyleMaskDocModalWindow;
static const NSWindowStyleMask NSNonactivatingPanelMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskNonactivatingPanel", macos(10.0,10.12)) = NSWindowStyleMaskNonactivatingPanel;
static const NSWindowStyleMask NSHUDWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskHUDWindow", macos(10.0,10.12)) = NSWindowStyleMaskHUDWindow;
static const NSWindowStyleMask NSUnscaledWindowMask API_DEPRECATED("NSUnscaledWindowMask is deprecated and has no effect. The scale factor for a window backing store is dynamic and dependent on the screen it is placed on.", macos(10.0,10.9)) = 1 << 11;

/* Deprecated window button constants
 */
static const NSWindowButton NSWindowFullScreenButton API_DEPRECATED("The standard window button for NSWindowFullScreenButton is always nil; use NSWindowZoomButton instead", macos(10.7,10.12)) = (NSWindowButton)7;

/* Deprecated window levels
 */
static const NSWindowLevel NSDockWindowLevel API_DEPRECATED("", macos(10.0,10.13)) = kCGDockWindowLevel;

#ifdef __cplusplus
}
#endif