/*
	NSBitmapImageRep.h
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


typedef NS_ENUM(NSUInteger, NSTIFFCompression) {
    NSTIFFCompressionNone		= 1,
    NSTIFFCompressionCCITTFAX3		= 3,		/* 1 bps only */
    NSTIFFCompressionCCITTFAX4		= 4,		/* 1 bps only */
    NSTIFFCompressionLZW		= 5,
    NSTIFFCompressionJPEG		= 6,		/* No longer supported for input or output */
    NSTIFFCompressionNEXT		= 32766,	/* Input only */
    NSTIFFCompressionPackBits		= 32773,
    NSTIFFCompressionOldJPEG		= 32865		/* No longer supported for input or output */
};

typedef NS_ENUM(NSUInteger, NSBitmapImageFileType) {
    NSBitmapImageFileTypeTIFF,
    NSBitmapImageFileTypeBMP,
    NSBitmapImageFileTypeGIF,
    NSBitmapImageFileTypeJPEG,
    NSBitmapImageFileTypePNG,
    NSBitmapImageFileTypeJPEG2000
};

typedef NS_ENUM(NSInteger, NSImageRepLoadStatus) {
    NSImageRepLoadStatusUnknownType     = -1, // not enough data to determine image format. please feed me more data
    NSImageRepLoadStatusReadingHeader   = -2, // image format known, reading header. not yet valid. more data needed
    NSImageRepLoadStatusWillNeedAllData = -3, // can't read incrementally. will wait for complete data to become avail.
    NSImageRepLoadStatusInvalidData     = -4, // image decompression encountered error.
    NSImageRepLoadStatusUnexpectedEOF   = -5, // ran out of data before full image was decompressed.
    NSImageRepLoadStatusCompleted       = -6  // all is well, the full pixelsHigh image is valid.
};

typedef NS_OPTIONS(NSUInteger, NSBitmapFormat) {
    NSBitmapFormatAlphaFirst            = 1 << 0,       // 0 means is alpha last (RGBA, CMYKA, etc.)
    NSBitmapFormatAlphaNonpremultiplied = 1 << 1,       // 0 means is premultiplied
    NSBitmapFormatFloatingPointSamples  = 1 << 2,  // 0 is integer

    NSBitmapFormatSixteenBitLittleEndian API_AVAILABLE(macos(10.10)) = (1 << 8),
    NSBitmapFormatThirtyTwoBitLittleEndian API_AVAILABLE(macos(10.10)) = (1 << 9),
    NSBitmapFormatSixteenBitBigEndian API_AVAILABLE(macos(10.10)) = (1 << 10),
    NSBitmapFormatThirtyTwoBitBigEndian API_AVAILABLE(macos(10.10)) = (1 << 11)
};

typedef const char* NSBitmapImageRepPropertyKey;

APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageCompressionMethod;       // TIFF input/output (NSTIFFCompression in NSNumber)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageCompressionFactor;	// TIFF/JPEG input/output (float in NSNumber)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageDitherTransparency;	// GIF output (BOOL in NSNumber)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageRGBColorTable;		// GIF input/output (packed RGB in NSData)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageInterlaced;                     // PNG output (BOOL in NSNumber)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageColorSyncProfileData; // TIFF,GIF input/output (NSData)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageFrameCount;                     // GIF input (int in NSNumber) (read-only)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageCurrentFrame;                 // GIF input (int in NSNumber)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageCurrentFrameDuration; // GIF input (float in NSNumber) (read-only)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageLoopCount;                       // GIF input (int in NSNumber) (read-only)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageGamma;                               // PNG input/output (float in NSNumber)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageProgressive;                   // JPEG input/output (BOOL in NSNumber)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageEXIFData;                         // JPEG input/output (NSDictionary)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageIPTCData;                      // Photo Metadata (NSDictionary)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageFallbackBackgroundColor API_AVAILABLE(macos(10.5)); // JPEG output (NSColor)


static const NSBitmapImageFileType NSTIFFFileType API_DEPRECATED_WITH_REPLACEMENT("NSBitmapImageFileTypeTIFF", macos(10.0,10.14)) = NSBitmapImageFileTypeTIFF;
static const NSBitmapImageFileType NSBMPFileType API_DEPRECATED_WITH_REPLACEMENT("NSBitmapImageFileTypeBMP", macos(10.0,10.14)) = NSBitmapImageFileTypeBMP;
static const NSBitmapImageFileType NSGIFFileType API_DEPRECATED_WITH_REPLACEMENT("NSBitmapImageFileTypeGIF", macos(10.0,10.14)) = NSBitmapImageFileTypeGIF;
static const NSBitmapImageFileType NSJPEGFileType API_DEPRECATED_WITH_REPLACEMENT("NSBitmapImageFileTypeJPEG", macos(10.0,10.14)) = NSBitmapImageFileTypeJPEG;
static const NSBitmapImageFileType NSPNGFileType API_DEPRECATED_WITH_REPLACEMENT("NSBitmapImageFileTypePNG", macos(10.0,10.14)) = NSBitmapImageFileTypePNG;
static const NSBitmapImageFileType NSJPEG2000FileType API_DEPRECATED_WITH_REPLACEMENT("NSBitmapImageFileTypeJPEG2000", macos(10.0,10.14)) = NSBitmapImageFileTypeJPEG2000;

static const NSBitmapFormat NSAlphaFirstBitmapFormat API_DEPRECATED_WITH_REPLACEMENT("NSBitmapFormatAlphaFirst", macos(10.5,10.14)) = NSBitmapFormatAlphaFirst;
static const NSBitmapFormat NSAlphaNonpremultipliedBitmapFormat API_DEPRECATED_WITH_REPLACEMENT("NSBitmapFormatAlphaNonpremultiplied", macos(10.0,10.14)) = NSBitmapFormatAlphaNonpremultiplied;
static const NSBitmapFormat NSFloatingPointSamplesBitmapFormat API_DEPRECATED_WITH_REPLACEMENT("NSBitmapFormatFloatingPointSamples", macos(10.0,10.14)) = NSBitmapFormatFloatingPointSamples;
static const NSBitmapFormat NS16BitLittleEndianBitmapFormat API_DEPRECATED_WITH_REPLACEMENT("NSBitmapFormatSixteenBitLittleEndian", macos(10.5,10.14)) = NSBitmapFormatSixteenBitLittleEndian;
static const NSBitmapFormat NS32BitLittleEndianBitmapFormat API_DEPRECATED_WITH_REPLACEMENT("NSBitmapFormatThirtyTwoBitLittleEndian", macos(10.0,10.14)) = NSBitmapFormatThirtyTwoBitLittleEndian;
static const NSBitmapFormat NS16BitBigEndianBitmapFormat API_DEPRECATED_WITH_REPLACEMENT("NSBitmapFormatSixteenBitBigEndian", macos(10.0,10.14)) = NSBitmapFormatSixteenBitBigEndian;
static const NSBitmapFormat NS32BitBigEndianBitmapFormat API_DEPRECATED_WITH_REPLACEMENT("NSBitmapFormatThirtyTwoBitBigEndian", macos(10.0,10.14)) = NSBitmapFormatThirtyTwoBitBigEndian;


#ifdef __cplusplus
}
#endif