/*
	NSFontDescriptor.h
	Application Kit
	Copyright (c) 2003-2021, Apple Inc.
	All rights reserved.
*/
#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "../../macros.h"
#include "../types.h"


/* Symbolic Font Traits */
typedef uint32_t NSFontSymbolicTraits; // Deprecated. Use NSFontDescriptorSymbolicTraits instead

typedef NS_OPTIONS(uint32_t, NSFontDescriptorSymbolicTraits) {
	NSFontDescriptorTraitItalic = 1u << 0,
	NSFontDescriptorTraitBold = 1u << 1,
	NSFontDescriptorTraitExpanded = 1u << 5,
	NSFontDescriptorTraitCondensed = 1u << 6,
	NSFontDescriptorTraitMonoSpace = 1u << 10,
	NSFontDescriptorTraitVertical = 1u << 11,
	NSFontDescriptorTraitUIOptimized = 1u << 12,
	NSFontDescriptorTraitTightLeading = 1u << 15,
	NSFontDescriptorTraitLooseLeading = 1u << 16,

	NSFontDescriptorTraitEmphasized API_UNAVAILABLE(macos) = NSFontDescriptorTraitBold,

	NSFontDescriptorClassMask = 0xF0000000,

	NSFontDescriptorClassUnknown = 0u << 28,
	NSFontDescriptorClassOldStyleSerifs = 1u << 28,
	NSFontDescriptorClassTransitionalSerifs = 2u << 28,
	NSFontDescriptorClassModernSerifs = 3u << 28,
	NSFontDescriptorClassClarendonSerifs = 4u << 28,
	NSFontDescriptorClassSlabSerifs = 5u << 28,
	NSFontDescriptorClassFreeformSerifs = 7u << 28,
	NSFontDescriptorClassSansSerif = 8u << 28,
	NSFontDescriptorClassOrnamentals = 9u << 28,
	NSFontDescriptorClassScripts = 10u << 28,
	NSFontDescriptorClassSymbolic = 12u << 28
};

// The following enum items are deprecated. Use NSFontDescriptorSymbolicTraits instead
enum {
	NSFontUnknownClass = 0 << 28,
	NSFontOldStyleSerifsClass = 1 << 28,
	NSFontTransitionalSerifsClass = 2 << 28,
	NSFontModernSerifsClass = 3 << 28,
	NSFontClarendonSerifsClass = 4 << 28,
	NSFontSlabSerifsClass = 5 << 28,
	NSFontFreeformSerifsClass = 7 << 28,
	NSFontSansSerifClass = 8 << 28,
	NSFontOrnamentalsClass = 9 << 28,
	NSFontScriptsClass = 10 << 28,
	NSFontSymbolicClass = 12 << 28
};

enum {
	NSFontFamilyClassMask = 0xF0000000
};

enum {
	NSFontItalicTrait = (1 << 0),
	NSFontBoldTrait = (1 << 1),
	NSFontExpandedTrait = (1 << 5),
	NSFontCondensedTrait = (1 << 6),
	NSFontMonoSpaceTrait = (1 << 10),
	NSFontVerticalTrait = (1 << 11),
	NSFontUIOptimizedTrait = (1 << 12)
};

#ifdef __cplusplus
}
#endif