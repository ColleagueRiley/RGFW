/*
	NSFontManager.h
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


/*
 * Font Traits
 *
 * This list should be kept small since the more traits that are assigned
 * to a given font, the harder it will be to map it to some other family.
 * Some traits are mutually exclusive such as NSExpanded and NSCondensed.
 */
typedef NS_OPTIONS(NSUInteger, NSFontTraitMask) {
	NSItalicFontMask			= 0x00000001,
	NSBoldFontMask			= 0x00000002,
	NSUnboldFontMask			= 0x00000004,
	NSNonStandardCharacterSetFontMask	= 0x00000008,
	NSNarrowFontMask			= 0x00000010,
	NSExpandedFontMask			= 0x00000020,
	NSCondensedFontMask			= 0x00000040,
	NSSmallCapsFontMask			= 0x00000080,
	NSPosterFontMask			= 0x00000100,
	NSCompressedFontMask		= 0x00000200,
	NSFixedPitchFontMask		= 0x00000400,
	NSUnitalicFontMask			= 0x01000000
};


typedef NS_OPTIONS(NSUInteger, NSFontCollectionOptions) {
   NSFontCollectionApplicationOnlyMask = 1 << 0
};


/* And these "actions" are really tag values in Font Menu cells which send any of the action messages listed above.  Normally, they're pre-defined in the font panel.
 */
typedef NS_ENUM(NSUInteger, NSFontAction) {
	NSNoFontChangeAction		= 0,
	NSViaPanelFontAction		= 1,
	NSAddTraitFontAction		= 2,
	NSSizeUpFontAction			= 3,
	NSSizeDownFontAction		= 4,
	NSHeavierFontAction			= 5,
	NSLighterFontAction			= 6,
	NSRemoveTraitFontAction		= 7
};

#ifdef __cplusplus
}
#endif