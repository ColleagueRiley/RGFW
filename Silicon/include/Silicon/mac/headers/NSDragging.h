/*
	NSDragging.h
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


typedef NS_OPTIONS(NSUInteger, NSDragOperation) {
    NSDragOperationNone		= 0,
    NSDragOperationCopy		= 1,
    NSDragOperationLink		= 2,
    NSDragOperationGeneric	= 4,
    NSDragOperationPrivate	= 8,
    NSDragOperationMove		= 16,
    NSDragOperationDelete	= 32,
    NSDragOperationEvery	= NSUIntegerMax,
    
    //NSDragOperationAll_Obsolete	API_DEPRECATED("", macos(10.0,10.10)) = 15, // Use NSDragOperationEvery
    //NSDragOperationAll API_DEPRECATED("", macos(10.0,10.10)) = NSDragOperationAll_Obsolete, // Use NSDragOperationEvery
};

typedef NS_ENUM(NSInteger, NSDraggingFormation) {
    NSDraggingFormationDefault = 0, // System determined formation.
    NSDraggingFormationNone,  // Drag images maintain their set positions relative to each other
    NSDraggingFormationPile,  // Drag images are placed on top of each other with random rotations
    NSDraggingFormationList,  // Drag images are laid out vertically, non-overlapping with the left edges aligned
    NSDraggingFormationStack // Drag images are laid out overlapping diagonally
} API_AVAILABLE(macos(10.7));

typedef NS_ENUM(NSInteger, NSDraggingContext) {
    NSDraggingContextOutsideApplication = 0,
    NSDraggingContextWithinApplication
} API_AVAILABLE(macos(10.7));

typedef NS_OPTIONS(NSUInteger, NSDraggingItemEnumerationOptions) {
    //NSDraggingItemEnumerationConcurrent			= NSEnumerationConcurrent,
    /* When the following option is set, AppKit will automatically set the imageComponentProvider to nil for all dragging items that do not meet the classes/searchOptions criteria. Effectively, this hides the drag image for non valid items for this destination. */
    NSDraggingItemEnumerationClearNonenumeratedImages 	= (1UL << 16),
} API_AVAILABLE(macos(10.7));

/* The spring loading highlight styles roughly correlate to {None: NotSpringLoadable, Light: SpringLoadable, Dark: SpringLoadingEngaged}. However, this not not strictly true as Drag & Drop may switch between highlight styles as an animated signal to the user. */
typedef NS_ENUM(NSInteger, NSSpringLoadingHighlight) {
    NSSpringLoadingHighlightNone = 0,
    NSSpringLoadingHighlightStandard,
    NSSpringLoadingHighlightEmphasized
} API_AVAILABLE(macos(10.11));


typedef NS_OPTIONS(NSUInteger, NSSpringLoadingOptions) {
    NSSpringLoadingDisabled	= 0,		// Spring loading disabled
    NSSpringLoadingEnabled	= 1UL << 0,	// Spring loading allowed (via Force Click release and hover timeout depending on user preferences)
    
    /* Activate spring loading when user enters Force Click as opposed to release from Force Click. Spring loading is de-activated when Force Click is released. If hover is enabled, spring loading is activated on hover timeout and deactivates when the drag exits the target. This option should be used sparingly. */
    NSSpringLoadingContinuousActivation    = 1UL << 1,
    
    /* Disable spring loading activation via hover. This option should be used sparingly, but there are some rare cases where spring loading via hover results in too many false positives, but is otherwise very useful with a Force Click. These are generally cases when the destination view is very large, such as a canvas. */
    NSSpringLoadingNoHover 	= 1UL << 3
} API_AVAILABLE(macos(10.11));


#ifdef __cplusplus
}
#endif
