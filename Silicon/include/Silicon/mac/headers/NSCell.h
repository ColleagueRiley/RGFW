/*
	NSCell.h
	Application Kit
	Copyright (c) 1994-2021, Apple Inc.
	All rights reserved.
*/

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <Availability.h>

#include "../../macros.h"
#include "../types.h"

typedef NS_ENUM(NSUInteger, NSCellType) {
	NSNullCellType  = 0,
	NSTextCellType  = 1,
	NSImageCellType = 2
};

typedef NS_ENUM(NSUInteger, NSCellAttribute) {
	NSCellDisabled               = 0,
	NSCellState                  = 1,
	NSPushInCell                 = 2,
	NSCellEditable               = 3,
	NSChangeGrayCell             = 4,
	NSCellHighlighted            = 5,
	NSCellLightsByContents       = 6,
	NSCellLightsByGray           = 7,
	NSChangeBackgroundCell       = 8,
	NSCellLightsByBackground     = 9,
	NSCellIsBordered             = 10,
	NSCellHasOverlappingImage    = 11,
	NSCellHasImageHorizontal     = 12,
	NSCellHasImageOnLeftOrBottom = 13,
	NSCellChangesContents        = 14,
	NSCellIsInsetButton          = 15,
	NSCellAllowsMixedState       = 16
};

typedef NS_ENUM(NSUInteger, NSCellImagePosition) {
	NSNoImage       = 0,
	NSImageOnly     = 1,
	NSImageLeft     = 2,
	NSImageRight    = 3,
	NSImageBelow    = 4,
	NSImageAbove    = 5,
	NSImageOverlaps = 6,
	NSImageLeading  API_AVAILABLE(macos(10.12)) = 7,
	NSImageTrailing API_AVAILABLE(macos(10.12)) = 8
};

typedef NS_ENUM(NSUInteger, NSImageScaling) {
	NSImageScaleProportionallyDown = 0, // Scale image down if it is too large for destination. Preserve aspect ratio.
	NSImageScaleAxesIndependently,      // Scale each dimension to exactly fit destination. Do not preserve aspect ratio.
	NSImageScaleNone,                   // Do not scale.
	NSImageScaleProportionallyUpOrDown, // Scale image to maximum possible dimensions while (1) staying within destination area (2) preserving aspect ratio

	NSScaleProportionally API_DEPRECATED("Use NSImageScaleProportionallyDown instead", macos(10.0,10.10)) = 0,
	NSScaleToFit API_DEPRECATED("Use NSImageScaleAxesIndependently instead", macos(10.0,10.10)),
	NSScaleNone API_DEPRECATED("Use NSImageScaleNone instead", macos(10.0,10.10))
} API_AVAILABLE(macos(10.5));

typedef NSInteger NSControlStateValue;
static const NSControlStateValue NSControlStateValueMixed = -1;
static const NSControlStateValue NSControlStateValueOff = 0;
static const NSControlStateValue NSControlStateValueOn = 1;

typedef NS_OPTIONS(NSUInteger, NSCellStyleMask) {
	NSNoCellMask               = 0,
	NSContentsCellMask         = 1,
	NSPushInCellMask           = 2,
	NSChangeGrayCellMask       = 4,
	NSChangeBackgroundCellMask = 8
};

typedef NS_ENUM(NSUInteger, NSControlTint) {
	NSDefaultControlTint  = 0,
	NSBlueControlTint     = 1,
	NSGraphiteControlTint = 6,
	NSClearControlTint    = 7
};

typedef NS_ENUM(NSUInteger, NSControlSize) {
	NSControlSizeRegular = 0,
	NSControlSizeSmall = 1,
	NSControlSizeMini = 2,
	NSControlSizeLarge API_AVAILABLE(macos(11.0)) = 3
};

/* Cell Hit testing support */

typedef NS_OPTIONS(NSUInteger, NSCellHitResult) {
	// An empty area, or did not hit in the cell
	NSCellHitNone = 0,
	// A content area in the cell
	NSCellHitContentArea = 1 << 0,
	// An editable text area of the cell
	NSCellHitEditableTextArea = 1 << 1,
	// A trackable area in the cell
	NSCellHitTrackableArea = 1 << 2,
} API_AVAILABLE(macos(10.5));

typedef NS_ENUM(NSInteger, NSBackgroundStyle) {
	/* The background reflects the predominant color scheme of the view's appearance. */
	NSBackgroundStyleNormal = 0,

	/* The background is indicating emphasis (e.g. selection state) using an alternate color or visual effect. Content may alter its appearance to reflect this emphasis. */
	NSBackgroundStyleEmphasized,

	/* The background is intended to appear higher than the content drawn on it. Content might need to be inset. */
	NSBackgroundStyleRaised,

	/* The background is intended to appear lower than the content drawn on it. Content might need to be embossed. */
	NSBackgroundStyleLowered,
} API_AVAILABLE(macos(10.5));

/* In some appearances, NSBackgroundStyleLight may refer to a state where the background is actually a dark color. Use NSBackgroundStyleNormal instead. */
static const NSBackgroundStyle NSBackgroundStyleLight API_DEPRECATED_WITH_REPLACEMENT("NSBackgroundStyleNormal", macos(10.5, 11.0)) = NSBackgroundStyleNormal;
/* NSBackgroundStyleDark is not a reliable indicator of background states with visually dark or saturated colors. Use NSBackgroundStyleEmphasized instead. */
static const NSBackgroundStyle NSBackgroundStyleDark API_DEPRECATED_WITH_REPLACEMENT("NSBackgroundStyleEmphasized", macos(10.5, 11.0)) = NSBackgroundStyleEmphasized;

typedef NSControlStateValue NSCellStateValue API_DEPRECATED_WITH_REPLACEMENT("NSControlStateValue", macos(10.0,10.14));
static const NSControlStateValue NSMixedState API_DEPRECATED_WITH_REPLACEMENT("NSControlStateValueMixed", macos(10.0,10.14)) = NSControlStateValueMixed;
static const NSControlStateValue NSOffState API_DEPRECATED_WITH_REPLACEMENT("NSControlStateValueOff", macos(10.0,10.14)) = NSControlStateValueOff;
static const NSControlStateValue NSOnState API_DEPRECATED_WITH_REPLACEMENT("NSControlStateValueOn", macos(10.0,10.14)) = NSControlStateValueOn;

static const NSControlSize NSRegularControlSize API_DEPRECATED_WITH_REPLACEMENT("NSControlSizeRegular", macos(10.0,10.12)) = NSControlSizeRegular;
static const NSControlSize NSSmallControlSize API_DEPRECATED_WITH_REPLACEMENT("NSControlSizeSmall", macos(10.0,10.12)) = NSControlSizeSmall;
static const NSControlSize NSMiniControlSize API_DEPRECATED_WITH_REPLACEMENT("NSControlSizeMini", macos(10.0,10.12)) = NSControlSizeMini;

APPKIT_EXTERN NSNotificationName NSControlTintDidChangeNotification API_DEPRECATED("Changes to the accent color can be manually observed by implementing -viewDidChangeEffectiveAppearance in a NSView subclass, or by Key-Value Observing the -effectiveAppearance property on NSApplication. Views are automatically redisplayed when the accent color changes.", macos(10.0, 11.0));

enum {
	NSAnyType API_DEPRECATED("Use formatters instead", macos(10.0,10.0)) = 0,
	NSIntType API_DEPRECATED("Use formatters instead", macos(10.0,10.0)) = 1,
	NSPositiveIntType API_DEPRECATED("Use formatters instead", macos(10.0,10.0)) = 2,
	NSFloatType API_DEPRECATED("Use formatters instead", macos(10.0,10.0)) = 3,
	NSPositiveFloatType API_DEPRECATED("Use formatters instead", macos(10.0,10.0)) = 4,
	NSDoubleType API_DEPRECATED("Use formatters instead", macos(10.0,10.0)) = 6,
	NSPositiveDoubleType API_DEPRECATED("Use formatters instead", macos(10.0,10.0)) = 7
};


#ifdef __cplusplus
}
#endif
