/*
	NSPasteboard.h
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


/* Standard Pasteboard Types */
typedef const char* NSPasteboardType;
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeString	 		API_AVAILABLE(macos(10.6)); // Replaces NSStringPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypePDF			API_AVAILABLE(macos(10.6)); // Replaces NSPDFPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeTIFF	 		API_AVAILABLE(macos(10.6)); // Replaces NSTIFFPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypePNG	 		API_AVAILABLE(macos(10.6));
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeRTF	 		API_AVAILABLE(macos(10.6)); // Replaces NSRTFPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeRTFD	 		API_AVAILABLE(macos(10.6)); // Replaces NSRTFDPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeHTML	 		API_AVAILABLE(macos(10.6)); // Replaces NSHTMLPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeTabularText 		API_AVAILABLE(macos(10.6)); // Replaces NSTabularTextPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeFont 			API_AVAILABLE(macos(10.6)); // Replaces NSFontPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeRuler 			API_AVAILABLE(macos(10.6)); // Replaces NSRulerPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeColor 			API_AVAILABLE(macos(10.6)); // Replaces NSColorPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeSound 			API_AVAILABLE(macos(10.6)); // Replaces NSSoundPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeMultipleTextSelection 	API_AVAILABLE(macos(10.6)); // Replaces NSMultipleTextSelectionPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeTextFinderOptions		API_AVAILABLE(macos(10.7)); // Replaces NSPasteboardTypeFindPanelSearchOptions
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeURL                        API_AVAILABLE(macos(10.13)); // Equivalent to kUTTypeURL
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeFileURL                    API_AVAILABLE(macos(10.13)); // Equivalent to kUTTypeFileURL


/* Standard Pasteboard Names */

typedef const char* NSPasteboardName;
APPKIT_EXTERN NSPasteboardName NSPasteboardNameGeneral API_AVAILABLE(macos(10.13));
APPKIT_EXTERN NSPasteboardName NSPasteboardNameFont API_AVAILABLE(macos(10.13));
APPKIT_EXTERN NSPasteboardName NSPasteboardNameRuler API_AVAILABLE(macos(10.13));
APPKIT_EXTERN NSPasteboardName NSPasteboardNameFind API_AVAILABLE(macos(10.13));
APPKIT_EXTERN NSPasteboardName NSPasteboardNameDrag API_AVAILABLE(macos(10.13));

/* Options for prepareForNewContentsWithOptions: */

typedef NS_OPTIONS(NSUInteger, NSPasteboardContentsOptions) {
	NSPasteboardContentsCurrentHostOnly = 1 << 0, // Specifies that the pasteboard contents should not be available to other devices
} API_AVAILABLE(macos(10.12));


/* Pasteboard Reading Options
 These options can be used for both the -readObjectsForClasses:options: and -canReadObjectForClasses:options: methods, unless otherwise specified.  The currently available options allow for customization of how NSURLs are read from the pasteboard.
 */
typedef const char* NSPasteboardReadingOptionKey;
/* Option for reading NSURLs to restrict the results to file URLs only.  The value for this key is an NSNumber with a boolean value.
 */
APPKIT_EXTERN NSPasteboardReadingOptionKey const NSPasteboardURLReadingFileURLsOnlyKey API_AVAILABLE(macos(10.6));
/* Option for reading NSURLs to restrict the results to URLs with contents that conform to any of the provided UTI types.  If the content type of a URL cannot be determined, it will not be considered to match.  The value for this key is an array of UTI type strings.
 */
APPKIT_EXTERN NSPasteboardReadingOptionKey const NSPasteboardURLReadingContentsConformToTypesKey API_AVAILABLE(macos(10.6));


/* The NSPasteboardWriting protocol enables instances of a class to be used with the -writeObjects: method of NSPasteboard.  The Cocoa framework classes NSString, NSAttributedString, NSURL, NSColor, NSSound, NSImage, and NSPasteboardItem implement this protocol.  The protocol can also be implemented by custom application classes for use with -writeObjects:
 */
typedef NS_OPTIONS(NSUInteger, NSPasteboardWritingOptions) {
	NSPasteboardWritingPromised = 1 << 9, // Data for a type with this option will be promised, not immediately written
} API_AVAILABLE(macos(10.6));


/*  NSPasteboardReadingOptions specify how data is read from the pasteboard.  You can specify only one option from this list.  If you do not specify an option, the default NSPasteboardReadingAsData is used.  The first three options specify how and if pasteboard data should be pre-processed by the pasteboard before being passed to -initWithPasteboardPropertyList:ofType.  The fourth option, NSPasteboardReadingAsKeyedArchive, should be used when the data on the pasteboard is a keyed archive of this class.  Using this option, a keyed unarchiver will be used and -initWithCoder: will be called to initialize the new instance.
 */
typedef NS_OPTIONS(NSUInteger, NSPasteboardReadingOptions) {
	NSPasteboardReadingAsData           = 0,	  // Reads data from the pasteboard as-is and returns it as an NSData
	NSPasteboardReadingAsString         = 1 << 0, // Reads data from the pasteboard and converts it to an NSString
	NSPasteboardReadingAsPropertyList   = 1 << 1, // Reads data from the pasteboard and un-serializes it as a property list
	NSPasteboardReadingAsKeyedArchive   = 1 << 2, // Reads data from the pasteboard and uses initWithCoder: to create the object
} API_AVAILABLE(macos(10.6));



/*** Deprecated ***/
APPKIT_EXTERN NSPasteboardType NSStringPboardType API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardTypeString", macos(10.0,10.14));
APPKIT_EXTERN NSPasteboardType NSFilenamesPboardType API_DEPRECATED("Create multiple pasteboard items with NSPasteboardTypeFileURL or kUTTypeFileURL instead", macos(10.0,10.14));
APPKIT_EXTERN NSPasteboardType NSTIFFPboardType API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardTypeTIFF", macos(10.0,10.14));
APPKIT_EXTERN NSPasteboardType NSRTFPboardType API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardTypeRTF", macos(10.0,10.14));
APPKIT_EXTERN NSPasteboardType NSTabularTextPboardType API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardTypeTabularText", macos(10.0,10.14));
APPKIT_EXTERN NSPasteboardType NSFontPboardType API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardTypeFont", macos(10.0,10.14));
APPKIT_EXTERN NSPasteboardType NSRulerPboardType API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardTypeRuler", macos(10.0,10.14));
APPKIT_EXTERN NSPasteboardType NSColorPboardType API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardTypeColor", macos(10.0,10.14));
APPKIT_EXTERN NSPasteboardType NSRTFDPboardType API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardTypeRTFD", macos(10.0,10.14));
APPKIT_EXTERN NSPasteboardType NSHTMLPboardType API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardTypeHTML", macos(10.0,10.14));
APPKIT_EXTERN NSPasteboardType NSURLPboardType API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardTypeURL", macos(10.0,10.14));
APPKIT_EXTERN NSPasteboardType NSPDFPboardType API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardTypePDF", macos(10.0,10.14));
APPKIT_EXTERN NSPasteboardType NSMultipleTextSelectionPboardType API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardTypeMultipleTextSelection", macos(10.5,10.14));

APPKIT_EXTERN NSPasteboardType NSPostScriptPboardType API_DEPRECATED_WITH_REPLACEMENT("@\"com.adobe.encapsulated-postscript\"", macos(10.0,10.14));
APPKIT_EXTERN NSPasteboardType NSVCardPboardType API_DEPRECATED_WITH_REPLACEMENT("kUTTypeVCard", macos(10.0,10.14));
APPKIT_EXTERN NSPasteboardType NSInkTextPboardType API_DEPRECATED_WITH_REPLACEMENT("kUTTypeInkText", macos(10.0,10.14));

// HFS Promise type for dragging only
APPKIT_EXTERN NSPasteboardType NSFilesPromisePboardType API_DEPRECATED_WITH_REPLACEMENT("kPasteboardTypeFileURLPromise", macos(10.0,10.14));

APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeFindPanelSearchOptions API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardTypeTextFinderOptions", macos(10.6,10.14));

APPKIT_EXTERN NSPasteboardName NSGeneralPboard API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardNameGeneral", macos(10.0,10.13));
APPKIT_EXTERN NSPasteboardName NSFontPboard API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardNameFont", macos(10.0,10.13));
APPKIT_EXTERN NSPasteboardName NSRulerPboard API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardNameRuler", macos(10.0,10.13));
APPKIT_EXTERN NSPasteboardName NSFindPboard API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardNameFind", macos(10.0,10.13));
APPKIT_EXTERN NSPasteboardName NSDragPboard API_DEPRECATED_WITH_REPLACEMENT("NSPasteboardNameDrag", macos(10.0,10.13));

/* NSPICTPboardType is deprecated in SnowLeopard.  The PICT format was formally deprecated in Tiger along with QuickDraw.  Applications should not be explicitly providing or looking for PICT data on the pasteboard.

To aid in this deprecation, if PICT is the only image type on the pasteboard, as is sometimes the case when copying images from 32-bit Carbon applications, a translated image type will be automatically reported and provided by NSPasteboard.  The translated type is added to the types array ahead of PICT so that the deprecated PICT format is not the preferred format.  In addition, when an application provides image data to NSPasteboard, the Carbon Pasteboard Manager will automatically make a PICT translation available to 32-bit Carbon applications.

Although NSPICTPboardType and its UTI equivalent kUTTypePICT will appear in a pasteboard's type array retrieved from the existing NSPasteboard API, it may cease to be reported in future releases.
*/
APPKIT_EXTERN NSPasteboardType NSPICTPboardType API_DEPRECATED("", macos(10.0,10.6));

#ifdef __cplusplus
}
#endif