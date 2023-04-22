/*
	NSButtonCell.h
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


typedef NS_ENUM(NSUInteger, NSButtonType) {
	NSButtonTypeMomentaryLight    = 0,
	NSButtonTypePushOnPushOff     = 1,
	NSButtonTypeToggle            = 2,
	NSButtonTypeSwitch            = 3,
	NSButtonTypeRadio             = 4,
	NSButtonTypeMomentaryChange   = 5,
	NSButtonTypeOnOff             = 6,
	NSButtonTypeMomentaryPushIn   = 7,
	NSButtonTypeAccelerator API_AVAILABLE(macos(10.10.3)) = 8,
	NSButtonTypeMultiLevelAccelerator API_AVAILABLE(macos(10.10.3)) = 9,
};

typedef NS_ENUM(NSUInteger, NSBezelStyle) {
	NSBezelStyleRounded           = 1,
	NSBezelStyleRegularSquare     = 2,
	NSBezelStyleDisclosure        = 5,
	NSBezelStyleShadowlessSquare  = 6,
	NSBezelStyleCircular          = 7,
	NSBezelStyleTexturedSquare    = 8,
	NSBezelStyleHelpButton        = 9,
	NSBezelStyleSmallSquare       = 10,
	NSBezelStyleTexturedRounded   = 11,
	NSBezelStyleRoundRect         = 12,
	NSBezelStyleRecessed          = 13,
	NSBezelStyleRoundedDisclosure = 14,
	NSBezelStyleInline API_AVAILABLE(macos(10.7)) = 15,
};


/* Deprecations */

typedef NS_ENUM(NSUInteger, NSGradientType) {
	NSGradientNone          = 0,
	NSGradientConcaveWeak   = 1,
	NSGradientConcaveStrong = 2,
	NSGradientConvexWeak    = 3,
	NSGradientConvexStrong  = 4
} API_DEPRECATED("", macos(10.0,10.12));

static const NSButtonType NSMomentaryLightButton API_DEPRECATED_WITH_REPLACEMENT("NSButtonTypeMomentaryLight", macos(10.0,10.14)) = NSButtonTypeMomentaryLight;
static const NSButtonType NSPushOnPushOffButton API_DEPRECATED_WITH_REPLACEMENT("NSButtonTypePushOnPushOff", macos(10.0,10.14)) = NSButtonTypePushOnPushOff;
static const NSButtonType NSToggleButton API_DEPRECATED_WITH_REPLACEMENT("NSButtonTypeToggle", macos(10.0,10.14)) = NSButtonTypeToggle;
static const NSButtonType NSSwitchButton API_DEPRECATED_WITH_REPLACEMENT("NSButtonTypeSwitch", macos(10.0,10.14)) = NSButtonTypeSwitch;
static const NSButtonType NSRadioButton API_DEPRECATED_WITH_REPLACEMENT("NSButtonTypeRadio", macos(10.0,10.14)) = NSButtonTypeRadio;
static const NSButtonType NSMomentaryChangeButton API_DEPRECATED_WITH_REPLACEMENT("NSButtonTypeMomentaryChange", macos(10.0,10.14)) = NSButtonTypeMomentaryChange;
static const NSButtonType NSOnOffButton API_DEPRECATED_WITH_REPLACEMENT("NSButtonTypeOnOff", macos(10.0,10.14)) = NSButtonTypeOnOff;
static const NSButtonType NSMomentaryPushInButton API_DEPRECATED_WITH_REPLACEMENT("NSButtonTypeMomentaryPushIn", macos(10.0,10.14)) = NSButtonTypeMomentaryPushIn;
static const NSButtonType NSAcceleratorButton API_DEPRECATED_WITH_REPLACEMENT("NSButtonTypeAccelerator", macos(10.10.3,10.14)) = NSButtonTypeAccelerator;
static const NSButtonType NSMultiLevelAcceleratorButton API_DEPRECATED_WITH_REPLACEMENT("NSButtonTypeMultiLevelAccelerator", macos(10.10.3,10.14)) = NSButtonTypeMultiLevelAccelerator;

/* These constants were accidentally reversed so that NSMomentaryPushButton lit and NSMomentaryLight pushed. These names are now deprecated */
static const NSButtonType NSMomentaryPushButton API_DEPRECATED("This constant is misnamed and has the same effect as NSButtonTypeMomentaryLight. Use that name instead, or switch to NSButtonTypeMomentaryPushIn.", macos(10.0,10.9)) = NSButtonTypeMomentaryLight;
static const NSButtonType NSMomentaryLight API_DEPRECATED("This constant is misnamed and has the same effect as NSButtonTypeMomentaryPushIn. Use that name instead, or switch to NSButtonTypeMomentaryLight.", macos(10.0,10.9)) = NSButtonTypeMomentaryPushIn;

static const NSBezelStyle NSRoundedBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleRounded", macos(10.0,10.14)) = NSBezelStyleRounded;
static const NSBezelStyle NSRegularSquareBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleRegularSquare", macos(10.0,10.14)) = NSBezelStyleRegularSquare;
static const NSBezelStyle NSDisclosureBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleDisclosure", macos(10.0,10.14)) = NSBezelStyleDisclosure;
static const NSBezelStyle NSShadowlessSquareBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleShadowlessSquare", macos(10.0,10.14)) = NSBezelStyleShadowlessSquare;
static const NSBezelStyle NSCircularBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleCircular", macos(10.0,10.14)) = NSBezelStyleCircular;
static const NSBezelStyle NSTexturedSquareBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleTexturedSquare", macos(10.0,10.14)) = NSBezelStyleTexturedSquare;
static const NSBezelStyle NSHelpButtonBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleHelpButton", macos(10.0,10.14)) = NSBezelStyleHelpButton;
static const NSBezelStyle NSSmallSquareBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleSmallSquare", macos(10.0,10.14)) = NSBezelStyleSmallSquare;
static const NSBezelStyle NSTexturedRoundedBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleTexturedRounded", macos(10.0,10.14)) = NSBezelStyleTexturedRounded;
static const NSBezelStyle NSRoundRectBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleRoundRect", macos(10.0,10.14)) = NSBezelStyleRoundRect;
static const NSBezelStyle NSRecessedBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleRecessed", macos(10.0,10.14)) = NSBezelStyleRecessed;
static const NSBezelStyle NSRoundedDisclosureBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleRoundedDisclosure", macos(10.0,10.14)) = NSBezelStyleRoundedDisclosure;
static const NSBezelStyle NSInlineBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleInline", macos(10.0,10.14)) = NSBezelStyleInline;

static const NSBezelStyle NSSmallIconButtonBezelStyle API_DEPRECATED("This bezel style is obsolete and should not be used.", macos(10.0,10.0)) = (NSBezelStyle)2;
static const NSBezelStyle NSThickSquareBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleRegularSquare", macos(10.0,10.12)) = (NSBezelStyle)3;
static const NSBezelStyle NSThickerSquareBezelStyle API_DEPRECATED_WITH_REPLACEMENT("NSBezelStyleRegularSquare", macos(10.0,10.12)) = (NSBezelStyle)4;


#ifdef __cplusplus
}
#endif