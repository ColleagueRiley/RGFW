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

#ifdef __cplusplus
extern "C" {
#endif

#include <AppKit/AppKit.h>
#include <objc/runtime.h>
#include <Availability.h>
#include <string.h>

#include <Silicon/mac_load.h>
#include <Silicon/macros.h>
#include <Silicon/siArray.h>
#include "../implementation.h" /* All of the macros that aren't from 'Silicon/macros.h' reside here. */


const NSSize _NSZeroSize = {0, 0};

/* Key stuff. */
const char* NSKEYS[] = {
	"Up", "Down", "Left", "Right",
	"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
	"Delete", "Insert", "Home", "End", "PageUp", "PageDown",
	"Backspace", "Tab", "Enter", "Return",
	"Escape", "Space", "Shift", "CapsLock", "BackSpace"
};
const unsigned short NSKEYI[si_sizeof(NSKEYS)] = {
	NSUpArrowFunctionKey, NSDownArrowFunctionKey, NSLeftArrowFunctionKey, NSRightArrowFunctionKey,
	NSF1FunctionKey, NSF2FunctionKey, NSF3FunctionKey, NSF4FunctionKey, NSF5FunctionKey, NSF6FunctionKey, NSF7FunctionKey, NSF8FunctionKey, NSF9FunctionKey, NSF10FunctionKey, NSF11FunctionKey, NSF12FunctionKey,
	NSDeleteFunctionKey, NSInsertFunctionKey, NSHomeFunctionKey, NSEndFunctionKey, NSPageUpFunctionKey, NSPageDownFunctionKey,
	NSBackspaceCharacter, NSTabCharacter, NSNewlineCharacter, NSCarriageReturnCharacter,
	0x1B, 0x20, 0x56, 0x57, 0x51
};
const unsigned char NSKEYCOUNT = si_sizeof(NSKEYS);


@interface WindowClass : NSWindow {}
@end

@implementation WindowClass
	- (instancetype) returnWin {
		return self;
	}
@end


@interface ViewClass : NSView {}
@end

@implementation ViewClass
	- (NSTextField*)label {
		return [NSTextField alloc];
	}
@end


/* Converts siArray to a NSArray. */
NSArray* si_array_to_NSArray(siArray(void) array) {
	size_t len = si_array_len(array);
	return [[NSArray alloc] initWithObjects:(array) count:(len)];
}


/* Returns the logon name of the current user. */
const char* _NSUserName() {
	return NSString_to_char(NSUserName());
}

/* Returns the path to either the user’s or application’s home directory, depending on the platform. */
const char* _NSHomeDirectory() {
	return NSString_to_char(NSHomeDirectory());
}

/* Creates a list of directory search paths. */
siArray(const char*) _NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory directory, NSSearchPathDomainMask domainMask, bool expandTilde) {
	NSArray<NSString*>* output = NSSearchPathForDirectoriesInDomains(directory, domainMask, expandTilde); /* wtf is this C++ faker doing in Objective-C??? */
	siArray(const char*) res = si_array_init_reserve(si_sizeof(const char*), output.count);

    for (NSUInteger i = 0; i < output.count; i++)
        res[i] = NSString_to_char([output objectAtIndex:(i)]);

	return res;
}

/* ============ NSControl class ============ */
/* ====== NSControl properties ======*/
/* */
implement_property(NSControl, id, target, Target, control);
/* */
implement_property(NSControl, SEL, action, Action, control);
/* */
implement_property(NSControl, NSFont*, font, Font, control);
/* */
implement_property(NSControl, double, doubleValue, DoubleValue, control);

/* ====== NSControl functions ======*/
/**/
NSControl* NSControl_initWithFrame(NSRect frameRect) {
	return [[NSControl alloc] initWithFrame:(frameRect)];
}


/* ============ NSWindow class ============ */
/* ====== NSWindow properties ====== */
/* Get/Set the title of the window. */
implement_str_property(NSWindow, const char*, title, Title, window);
/* Get/Set the delegate of the window. */
implement_property(NSWindow, NSView*, contentView, ContentView, window);
/* Get/Set the NSView of the window. */
implement_property(NSWindow, id, delegate, Delegate, window);
/* Get/Set the visbility of the window. */
implement_property(NSWindow, bool, isVisible, IsVisible, window);
/* */
implement_property(NSWindow, NSColor*, backgroundColor, BackgroundColor, window);
/* Toggle opaque for the window. */
implement_property(NSWindow, bool, isOpaque, Opaque, window);
/* The window’s alpha value. */
implement_property(NSWindow, CGFloat, alphaValue, AlphaValue, window);
/* A Boolean value that indicates whether the window accepts mouse-moved events. */
implement_property(NSWindow, bool, acceptsMouseMovedEvents, AcceptsMouseMovedEvents, window);
/* Get the frame of the window. */
NSRect NSWindow_frame(NSWindow* window) { return [window frame]; }

/* ====== NSWindow functions ====== */
/* Get/Set the title of the window. */
NSWindow* NSWindow_init(NSRect contentRect, NSWindowStyleMask style, NSBackingStoreType backingStoreType, bool flag) {
	return [[WindowClass alloc] initWithContentRect:(contentRect) styleMask:(style) backing:(backingStoreType) defer:(flag)];
}
/* */
void NSWindow_orderFront(NSWindow* window, NSWindow* sender){
	[window orderFront:(sender)];
}
/* */
void NSWindow_makeKeyWindow(NSWindow* window) {
	[window makeKeyWindow];
}
/* */
bool NSWindow_isKeyWindow(NSWindow* window) {
	return [window isKeyWindow];
}
/* */
void NSWindow_center(NSWindow* window) {
	[window center];
}
/* */
void NSWindow_makeMainWindow(NSWindow* window) {
	[window makeMainWindow];
}
/* Set the frame of the window. */
void NSWindow_setFrameAndDisplay(NSWindow* window, NSRect frame, bool display, bool animate) {
	[window setFrame:(frame) display:(display) animate:(animate)];
}
/* */
NSPoint NSWindow_convertPointFromScreen(NSWindow* window, NSPoint point) {
    //return [window convertPointFromScreen:(point)];
}
/* Passes a display message down the window’s view hierarchy, thus redrawing all views within the window. */
void NSWindow_display(NSWindow* window) {
	return [window display];
}


/* ============ NSView class ============ */
/* ====== NSView functions ====== */
/* */
NSView* NSView_init() {
	return [[ViewClass alloc] init];
}
/* */
NSView* NSView_initWithFrame(NSRect frameRect) {
	return [[ViewClass alloc] initWithFrame:(frameRect)];
}
/* */
void NSView_addSubview(NSView* view, NSView* subview) {
	[view addSubview:(subview)];
}
/* */
void NSView_registerForDraggedTypes(NSView* view, siArray(NSPasteboardType) newTypes) {
	NSArray* new_array = si_array_to_NSArray(newTypes);

	[view registerForDraggedTypes:(new_array)];
	[new_array release];
}


/* ============ NSTextField class ============ */
/* ====== NSTextField properties ====== */
/* */
implement_str_property(NSTextField, const char*, stringValue, StringValue, field);
/* */
implement_property(NSTextField, bool, isBezeled, Bezeled, field);
/* */
implement_property(NSTextField, bool, drawsBackground, DrawsBackground, field);
/* */
implement_property(NSTextField, bool, isEditable, Editable, field);
/* */
implement_property(NSTextField, bool, isSelectable, Selectable, field);
/* */
implement_property(NSTextField, NSColor*, textColor, TextColor, field);
/* */
implement_property(NSTextField, NSFont*, font, Font, field);

/* ====== NSTextField functions ====== */
/* Initializes a NSTextField handle. */
NSTextField* NSTextField_initWithFrame(NSRect frameRect) {
	return [[NSTextField alloc] initWithFrame:(frameRect)];
}


/* ============ NSFontManager class ============ */
/* ====== NSFontManager functions ====== */
/* */
NSFontManager* NSFontManager_sharedFontManager() {
	return [NSFontManager sharedFontManager];
}
/* */
NSFont* NSFontManager_convertFont(NSFontManager* manager, NSFont* fontObj) {
	return [manager convertFont:(fontObj)];
}
/* */
NSFont* NSFontManager_convertFontToHaveTrait(NSFontManager* manager, NSFont* fontObj, NSFontTraitMask trait) {
	return [manager convertFont:(fontObj) toHaveTrait:(trait)];
}


/* ============ NSFont class ============ */
/* ====== NSFont functions ====== */
/* */
NSFont* NSFont_init(const char* fontName, CGFloat fontSize) {
	NSString* str = char_to_NSString(fontName);
	NSFont* res = [NSFont fontWithName:(str) size:(fontSize)];

	[str release];
	return res;
}
/* */
const char* NSFont_fontName(NSFont* font) {
	return NSString_to_char([font fontName]);
}


/* ============ NSButton class ============ */
/* ====== NSButton properties ====== */
/* */
implement_str_property(NSButton, const char*, title, Title, button);
/* */
implement_property(NSButton, NSBezelStyle, bezelStyle, BezelStyle, button);
/* */
implement_property(NSButton, id, target, Target, button);
/* */
implement_property(NSButton, SEL, action, Action, button);
/* */
implement_property(NSButton, NSAutoresizingMaskOptions, autoresizingMask, AutoresizingMask, button);
/* */
implement_property(NSButton, NSControlStateValue, state, State, button);
/* */
implement_property(NSButton, bool, allowsMixedState, AllowsMixedState, button);

/* ====== NSButton functions ====== */
/* */
NSButton* NSButton_initWithFrame(NSRect frameRect) {
	return [[NSButton alloc] initWithFrame:(frameRect)];
}
/* */
void NSButton_setButtonType(NSButton* button, NSButtonType buttonType) {
	return [button setButtonType:(buttonType)];
}


/* ============ NSComboBox class ============ */
/* ====== NSComboBox properties ====== */
/* */
/* (read-only) */
NSInteger NSComboBox_indexOfSelectedItem(NSComboBox* comboBox) {
	return [comboBox indexOfSelectedItem];
}
/* */
implement_str_property(NSComboBox, const char*, stringValue, StringValue, field);
/* */
implement_property(NSComboBox, bool, isBezeled, Bezeled, field);
/* */
implement_property(NSComboBox, bool, drawsBackground, DrawsBackground, field);
/* */
implement_property(NSComboBox, bool, isEditable, Editable, field);
/* */
implement_property(NSComboBox, bool, isSelectable, Selectable, field);
/* */
implement_property(NSComboBox, NSColor*, textColor, TextColor, field);
/* */
implement_property(NSComboBox, id, target, Target, comboBox);
/* */
implement_property(NSComboBox, SEL, action, Action, comboBox);

/* ====== NSComboBox functions ====== */
/**/
NSComboBox* NSComboBox_initWithFrame(NSRect frameRect) {
	return [[NSComboBox alloc] initWithFrame:(frameRect)];
}
/* */
void NSComboBox_addItem(NSComboBox* comboBox, const char* str) {
	[comboBox addItemWithObjectValue:([char_to_NSString(str) retain])];
}
/* */
void NSComboBox_selectItem(NSComboBox* comboBox, NSInteger index) {
	[comboBox selectItemAtIndex:(index)];
}


/* ============ NSApplication class ============ */
NSApplication* _NSApp;
/* ====== NSApplication properties ====== */
/* */
implement_property(NSApplication, NSMenu*, mainMenu, MainMenu, application);
/* */
implement_property(NSApplication, NSMenu*, servicesMenu, ServicesMenu, application);
/* */
implement_property(NSApplication, NSMenu*, helpMenu, HelpMenu, application);
/* */
implement_property(NSApplication, NSMenu*, windowsMenu, WindowsMenu, application);
/* */
implement_property(NSApplication, NSApplicationActivationPolicy, activationPolicy, ActivationPolicy, application);
/* */
implement_property(NSApplication, NSImage*, applicationIconImage, ApplicationIconImage, application);

/* ====== NSApplication functions ====== */
/* */
NSApplication* NSApplication_sharedApplication() {
	_NSApp = [NSApplication sharedApplication];

	return _NSApp;
}
/* */
void NSApplication_finishLaunching(NSApplication* application) {
	[application finishLaunching];
}
/* */
void NSApplication_run(NSApplication* application) {
	[application run];
}
/* */
void NSApplication_stop(NSApplication* application, NSView* view) {
	[application stop:(view)];
}
/* */
void NSApplication_terminate(NSApplication* application, id sender) {
	[application terminate:(sender)];
}
/* */
void NSApplication_sendEvent(NSApplication* application, NSEvent* event) {
	[application sendEvent:(event)];
}
/* */
void NSApplication_updateWindows(NSApplication* application) {
	[application updateWindows];
}
/* */
void NSApplication_activateIgnoringOtherApps(NSApplication* application, bool flag) {
	[application activateIgnoringOtherApps:(flag)];
}
/* */
NSEvent* NSApplication_nextEventMatchingMask(NSApplication* application, NSEventMask mask, NSDate* expiration, int mode, bool deqFlag) {
	return [application nextEventMatchingMask:(mask) untilDate:(expiration) inMode:(NSDefaultRunLoopMode) dequeue:(deqFlag)];;
}


/* ============ NSScreen class ============*/
/* ====== NSScreen properties ====== */
/* Returns the screen object containing the window with the keyboard focus. */
NSScreen* NSScreen_mainScreen() {
	return [NSScreen mainScreen];
}
/* The dimensions and location of the screen. */
NSRect NSScreen_frame(NSScreen* screen) {
	return [screen frame];
}
/* The current location and dimensions of the visible screen. */
NSRect NSScreen_visibleFrame(NSScreen* screen) {
	return [screen visibleFrame];
}


/* ============ NSEvent class ============ */
/* ====== NSEvent functions ====== */
/* */
NSEventType NSEvent_type(NSEvent* event) {
	return [event type];
}
/* */
NSPoint NSEvent_locationInWindow(NSEvent* event) {
	return [event locationInWindow];
}
/* */
NSEventModifierFlags NSEvent_modifierFlags(NSEvent* event) {
	return [event modifierFlags];
}
/* */
unsigned short NSEvent_keyCode(NSEvent* event) {
	return [event keyCode];
}
/* */
NSPoint NSEvent_mouseLocation(NSEvent* event) {
	return [NSEvent mouseLocation];
}
/* */
unsigned short NSEvent_keyCodeForChar(char* keyStr){
	for (NSUInteger i = 0; i < NSKEYCOUNT; i++) {
		if (strcmp(keyStr, NSKEYS[i]))
			return NSKEYI[i + 1];
	}

	NSString* keyString = char_to_NSString(keyStr);
	unichar keyCode = [keyString characterAtIndex:(0)];

	[keyString release];
	return keyCode;
}
/* */
const char* NSEvent_characters(NSEvent* event) {
	unichar keyCode = [[event charactersIgnoringModifiers] characterAtIndex:(0)];
	NSUInteger flags = [event modifierFlags] & (NSEventModifierFlagShift | NSEventModifierFlagControl | NSEventModifierFlagOption | NSEventModifierFlagCommand);

	for (NSUInteger i = 0; i < NSKEYCOUNT; i++) {
		if (keyCode == NSKEYI[i])
			return NSKEYS[i];
	}

	return NSString_to_char([event characters]);
}
/* */
CGFloat NSEvent_deltaY(NSEvent* event) {
	return [event deltaY];
}
/* */
NSWindow* NSEvent_window(NSEvent* event){
	return [event window];
}


/* ============ NSMenu class ============ */
/* ====== NSMenu functions ====== */
/* */
NSMenu* NSMenu_init(const char* title) {
	return [[NSMenu alloc] initWithTitle:(char_to_NSString(title))];
}
/* */
void NSMenu_addItem(NSMenu* menu, NSMenuItem* newItem) {
	[menu addItem:(newItem)];
}


/* ============ NSMenuItem class ============ */
/* ====== NSMenuItem properties ====== */
/* */
implement_property(NSMenuItem, NSMenu*, submenu, Submenu, item);
/* */
implement_str_property(NSMenuItem, const char*, title, Title, item);

/* ====== NSMenuItem functions ====== */
/* */
NSMenuItem* NSMenuItem_init(const char* title, SEL selector, const char* keyEquivalent) {
	NSString* menu_title = char_to_NSString(title);
	NSString* key = char_to_NSString(keyEquivalent);

	return  [[NSMenuItem alloc] initWithTitle:(menu_title) action:(selector) keyEquivalent:(key)];
}
/* */
siArray(NSMenuItem*) NSMenu_itemArray(NSMenu* menu) {
	NSArray<NSMenuItem*>* item_array = [menu itemArray];
	siArray(NSMenuItem*) result = si_array_init_reserve(si_sizeof(*result), item_array.count);

	for (NSUInteger i = 0; i < item_array.count; i++) {
		result[i] = [item_array objectAtIndex:(i)];
		[result[i] retain];
	}
	/* TODO(EimaMei): Maybe release item_array here? */

	return result;
}
/* */
NSMenuItem* NSMenuItem_separatorItem() {
	return [NSMenuItem separatorItem];
}


/* ============ NSColor class ============ */
/* ====== NSColor properties ====== */
/* */
NSColor* NSColor_clearColor() {
	return [NSColor clearColor];
}
/* */
NSColor* NSColor_keyboardFocusIndicatorColor() {
	return [NSColor keyboardFocusIndicatorColor];
}

/* ====== NSColor functions ====== */
/* */
void NSColor_set(NSColor* color) {
	[color set];
}
/* */
NSColor* NSColor_colorWithRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha) {
	return [NSColor colorWithRed:(red) green:(green) blue:(blue) alpha:(alpha)];
}
/* */
NSColor* NSColor_colorWithSRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha) {
	return [NSColor colorWithSRGBRed:(red) green:(green) blue:(blue) alpha:(alpha)];
}
/* Creates a color object using the given opacity and grayscale values. */
NSColor* NSColor_colorWithCalibrated(CGFloat white, CGFloat alpha) {
	return [NSColor colorWithCalibratedWhite:(white) alpha:(alpha)];
}


/* ============ NSBezierPath class ============ */
/* ====== NSBezierPath functions ====== */
/* */
void NSBezierPath_strokeLine(NSPoint from, NSPoint to) {
	[NSBezierPath strokeLineFromPoint:(from) toPoint:(to)];
}


/* ============ NSDate class ============ */
/* ====== NSDate functions ====== */
/* */
NSDate* NSDate_distantFuture() {
	return [NSDate distantFuture];
}


/* ============ NSProcessInfo class ============ */
/* ====== NSProcessInfo functions ====== */
/* */
NSProcessInfo* NSProcessInfo_processInfo() {
	return [NSProcessInfo processInfo];
}
/* */
const char* NSProcessInfo_processName(NSProcessInfo* processInfo) {
	return NSString_to_char([processInfo processName]);
}


/* ============ NSImage class ============ */
/* ====== NSImage functions ====== */
/* Initializes and returns an image object with the specified dimensions. */
NSImage* NSImage_initWithSize(NSSize size) {
	return [[NSImage alloc] initWithSize:(size)];
}
/* */
NSImage* NSImage_initWithData(unsigned char* bitmapData, NSUInteger length) {
	NSData* data = [NSData dataWithBytes:(bitmapData) length:(length)];
	NSImage* result = [[NSImage alloc] initWithData:(data)];
	[data release];

	return result;
}
/* Initializes a data object with the content of the file at a given path. */
NSImage* NSImage_initWithFile(const char* path) {
	NSString* filepath = char_to_NSString(path);
	NSImage* result = [[NSImage alloc] initWithContentsOfFile:(filepath)];
	[filepath release];

	return result;
}
/* */
NSImage* NSImage_initWithCGImage(CGImageRef cgImage, NSSize size) {
	return [[NSImage alloc] initWithCGImage:(cgImage) size:(size)];
}
/* Adds the specified image representation object to the image. */
void NSImage_addRepresentation(NSImage* image, NSImageRep* imageRep) {
	[image addRepresentation:(imageRep)];
}


/* ============ NSGraphicsContext class ============ */
/* ====== NSGraphicsContext properties ====== */
#if (OS_X_VERSION_MAX_ALLOWED < macos_version(10, 5)) /* 'currentContext' doesn't exist in OS X 10.5+. */
/* */
implement_deprecated_property(NSGraphicsContext, NSGraphicsContext*, currentContext, CurrentContext, context, macos(10.5));
#endif


/* =========== NSPasteboard class ============ */
/* ====== NSPasteboard functions ====== */
/* */
NSPasteboard* NSPasteboard_generalPasteboard() {
	return [NSPasteboard generalPasteboard];
}
const char* NSPasteboard_stringForType(NSPasteboard* pasteboard, NSPasteboardType dataType) {
	return NSString_to_char([pasteboard stringForType:(dataType)]);
}
/* */
NSInteger NSPasteBoard_declareTypes(NSPasteboard* pasteboard, siArray(NSPasteboardType) newTypes, void* owner) {
	NSArray* new_array = si_array_to_NSArray(newTypes);

	NSInteger res = [pasteboard declareTypes:(new_array) owner:(owner)];
	[new_array release];

	return res;
}
/* */
bool NSPasteBoard_setString(NSPasteboard* pasteboard, const char* stringToWrite, NSPasteboardType dataType) {
	return [pasteboard setString:(char_to_NSString(stringToWrite)) forType:(dataType)];
}
/* */
siArray(const char*) NSPasteboard_readObjectsForClasses(NSPasteboard* pasteboard, siArray(Class) classArray, void* options) {
    NSArray* new_array = si_array_to_NSArray(classArray);
    NSArray* filenames = [pasteboard readObjectsForClasses:(new_array) options:(options)];

	siArray(const char*) output = si_array_init_reserve(si_sizeof(*output), filenames.count);

    for (NSUInteger i = 0; i < si_array_len(output); i++)
        output[i] = NSString_to_char([[filenames objectAtIndex:(i)] path]);

	[new_array release];

	return output;
}


/* ============ NSSlider class ============ */
/* ====== NSSlider properties ====== */
/**/
implement_property(NSSlider, id, target, Target, slider);
/**/
implement_property(NSSlider, SEL, action, Action, slider);
/**/
implement_property(NSSlider, NSFont*, font, Font, slider);
/* */
implement_property(NSSlider, double, doubleValue, DoubleValue, slider);
/* */
implement_property(NSSlider, double, maxValue, MaxValue, slider);

/* ====== NSSlider functions ====== */
/* */
NSSlider* NSSlider_initWithFrame(NSRect frameRect) {
	return [[NSSlider alloc] initWithFrame:(frameRect)];
}


/* ============ NSProgressIndicator class ============ */
/* ====== NSProgressIndicator properties ====== */
/* */
implement_property(NSProgressIndicator, double, doubleValue, DoubleValue, progressIndicator);
/* */
implement_property(NSProgressIndicator, double, maxValue, MaxValue, progressIndicator);
/* */
implement_property(NSProgressIndicator, bool, isIndeterminate, Indeterminate, progressIndicator);

/* ====== NSProgressIndicator functions ====== */
/* */
NSProgressIndicator* NSProgressIndicator_init(NSRect frameRect) {
	return [[NSProgressIndicator alloc] initWithFrame:(frameRect)];
}


/* ============ NSDraggingInfo class ============ */
/* ====== NSDraggingInfo properties ====== */
/* */
NSPasteboard* NSDraggingInfo_draggingPasteboard(id<NSDraggingInfo> info) {
	return [info draggingPasteboard];
}
/* */
NSPoint NSDraggingInfo_draggingLocation(id<NSDraggingInfo> info) {
    return [info draggingLocation];
}
/* */
NSInteger NSDraggingInfo_numberOfValidItemsForDrop(id<NSDraggingInfo> info) {
	return [info numberOfValidItemsForDrop];
}
void NSDraggingInfo_setNumberOfValidItemsForDrop(id<NSDraggingInfo> info, NSInteger number) {
	[info setNumberOfValidItemsForDrop:(number)];
}
/* */
NSWindow* NSDraggingInfo_draggingDestinationWindow(id<NSDraggingInfo> info) {
    return [info draggingDestinationWindow];
}


/* ============ NSColorPanel class ============ */
/* ====== NSColorPanel properties ====== */
implement_property(NSColorPanel, NSColor*, color, Color, colorPanel);


/* ============ NSBitmapImageRep class ============ */
/* ====== NSBitmapImageRep properties ====== */
unsigned char* NSBitmapImageRep_bitmapData(NSBitmapImageRep* imageRep) {
	return [imageRep bitmapData];
}

/* ====== NSBitmapImageRep functions ====== */
/* Initializes a newly allocated bitmap image representation so it can render the specified image. */
NSBitmapImageRep* NSBitmapImageRep_initWithBitmapData(unsigned char** planes, NSInteger width, NSInteger height, NSInteger bps, NSInteger spp, bool alpha, bool isPlanar, const char* colorSpaceName, NSBitmapFormat bitmapFormat, NSInteger rowBytes, NSInteger pixelBits) {
	return [[NSBitmapImageRep alloc]
        initWithBitmapDataPlanes:(planes)
        pixelsWide:(width)
        pixelsHigh:(height)
        bitsPerSample:(bps)
        samplesPerPixel:(spp)
        hasAlpha:(alpha)
        isPlanar:(isPlanar)
        colorSpaceName:(char_to_NSString(colorSpaceName))
        bitmapFormat:(bitmapFormat)
        bytesPerRow:(rowBytes)
        bitsPerPixel:(pixelBits)
	];
}


/* ============ NSSavePanel class ============ */
/* ====== NSSavePanel properties ====== */
/* A Boolean value that indicates whether the panel displays UI for creating directories. */
implement_property(NSSavePanel, bool, canCreateDirectories, CanCreateDirectories, savePanel);
/* (Deprecated!) An array of filename extensions or UTIs that represent the allowed file types for the panel. */
siArray(const char*) NSSavePanel_allowedFileTypes(NSSavePanel* savePanel) {
	NSArray<NSString*>* output = [savePanel allowedFileTypes];
	siArray(const char*) res = si_array_init_reserve(si_sizeof(const char*), output.count);

    for (NSUInteger i = 0; i < output.count; i++) {
        res[i] = NSString_to_char([output objectAtIndex:(i)]);
	}

	return res;
}
/* */
void NSSavePanel_setAllowedFileTypes(NSSavePanel* savePanel, siArray(const char*) allowedFileTypes) {
	siArray(NSString*) copy = si_array_init_reserve(si_sizeof(*copy), si_array_len(allowedFileTypes));

	for (usize i = 0; i < si_array_len(copy); i++) {
		copy[i] = char_to_NSString(allowedFileTypes[i]);
	}

	NSArray* array = si_array_to_NSArray(copy);
	[savePanel setAllowedFileTypes:(array)];

	si_array_free(copy);
	[array release];
}
/* The current directory shown in the panel. */
implement_property(NSSavePanel, NSURL*, directoryURL, DirectoryURL, savePanel);
/* The user-editable filename currently shown in the name field. */
implement_str_property(NSSavePanel, const char*, nameFieldStringValue, NameFieldStringValue, savePanel);
/* A URL that contains the fully specified location of the targeted file. */
NSURL* NSSavePanel_URL(NSSavePanel* savePanel) {
	return [savePanel URL];
}

/* ====== NSSavePanel functions ====== */
/* Displays the panel and begins its event loop with the current working (or last-selected) directory as the default starting point. */
NSModalResponse NSSavePanel_runModal(NSSavePanel* savePanel) {
	return [savePanel runModal];
}


/* ============ NSURL class ============ */
/* ====== NSURL properties ====== */
const char* NSURL_path(NSURL* url) {
	return NSString_to_char([url path]);
}

/* ====== NSURL functions ====== */
/* Initializes and returns a newly created NSURL object as a file URL with a specified path. */
NSURL* NSURL_fileURLWithPath(const char* path) {
	NSString* txt = char_to_NSString(path);
	NSURL* res = [NSURL fileURLWithPath:(txt)];

	return res;
}


/* ============ NSOpenPanel class ============ */
/* ====== NSOpenPanel properties ====== */
/* A Boolean that indicates whether the user can choose files in the panel. */
implement_property(NSOpenPanel, bool, canChooseFiles, CanChooseFiles, openPanel);
/* A Boolean that indicates whether the user can choose directories in the panel. */
implement_property(NSOpenPanel, bool, canChooseDirectories, CanChooseDirectories, openPanel);
/* A Boolean value that indicates whether the panel displays UI for creating directories. */
implement_property(NSOpenPanel, bool, canCreateDirectories, CanCreateDirectories, openPanel);
/* A Boolean that indicates whether the panel resolves aliases. */
implement_property(NSOpenPanel, bool, resolvesAliases, ResolvesAliases, openPanel);
/* A Boolean that indicates whether the user may select multiple files and directories. */
implement_property(NSOpenPanel, bool, allowsMultipleSelection, AllowsMultipleSelection, openPanel);
/* A Boolean value that indicates whether the panel's accessory view is visible. */
implement_property(NSOpenPanel, bool, isAccessoryViewDisclosed, AccessoryViewDisclosed, openPanel);
/* An array of URLs, each of which contains the fully specified location of a selected file or directory. */
siArray(NSURL*) NSOpenPanel_URLs(NSOpenPanel* openPanel) {
	NSArray<NSURL*>* output = [openPanel URLs];
	siArray(NSURL*) res = si_array_init_reserve(si_sizeof(NSURL*), output.count);

	for (NSUInteger i = 0; i < output.count; i++)
		res[i] = [output objectAtIndex:(i)];

	return res;
}
/* A Boolean value that indicates how the panel responds to iCloud documents that aren't fully downloaded locally. */
implement_property(NSOpenPanel, bool, canDownloadUbiquitousContents, CanDownloadUbiquitousContents, openPanel);
/* A Boolean value that indicates whether the panel's accessory view is visible. */
implement_property(NSOpenPanel, bool, canResolveUbiquitousConflicts, CanResolveUbiquitousConflicts, openPanel);
/* (Deprecated!) An array of filename extensions or UTIs that represent the allowed file types for the panel. */
siArray(const char*) NSOpenPanel_allowedFileTypes(NSOpenPanel* savePanel) { return NSSavePanel_allowedFileTypes((NSSavePanel*)savePanel); }
void NSOpenPanel_setAllowedFileTypes(NSOpenPanel* savePanel, siArray(const char*) allowedFileTypes) { NSSavePanel_setAllowedFileTypes((NSSavePanel*)savePanel, allowedFileTypes);}
/* The current directory shown in the panel. */
implement_property(NSOpenPanel, NSURL*, directoryURL, DirectoryURL, openPanel);
/* The user-editable filename currently shown in the name field. */
implement_str_property(NSOpenPanel, const char*, nameFieldStringValue, NameFieldStringValue, openPanel);
/* A URL that contains the fully specified location of the targeted file. */
NSURL* NSOpenPanel_URL(NSOpenPanel* openPanel) { return [openPanel URL]; }

/* ====== NSOpenPanel functions ====== */
/* Creates a new Open panel and initializes it with a default configuration. */
NSOpenPanel* NSOpenPanel_openPanel() {
	return [NSOpenPanel openPanel];
}
/* Displays the panel and begins its event loop with the current working (or last-selected) directory as the default starting point. */
NSModalResponse NSOpenPanel_runModal(NSOpenPanel* openPanel) {
	return [openPanel runModal];
}


/* ============ NSCursor class ============ */
/* ====== NSCursor properties ====== */
/* The cursor’s image. */
NSImage* NSCursor_image(NSCursor* cursor) {
	return [cursor image];
}
/* The position of the cursor's hot spot. */
NSPoint NSCursor_hotSpot(NSCursor* cursor) {
	return [cursor hotSpot];
}
/* Returns the application’s current cursor. */
NSCursor* NSCursor_currentCursor() {
	return [NSCursor currentCursor];
}
/* Returns the default cursor, the arrow cursor. */
NSCursor* NSCursor_arrowCursor() {
	return [NSCursor arrowCursor];
}

/* ====== NSCursor functions ====== */
/* Initializes a cursor with the given image and hot spot. */
NSCursor* NSCursor_initWithImage(NSImage* newImage, NSPoint aPoint) {
	return [[NSCursor alloc] initWithImage:(newImage) hotSpot:(aPoint)];
}
/* Makes the current cursor invisible. */
void NSCursor_hide() {
	[NSCursor hide];
}
/* Makes the current cursor invisible. */
void NSCursor_unhide() {
	[NSCursor unhide];
}
/* Pops the current cursor off the top of the stack. */
void NSCursor_pop(NSCursor* cursor) {
	[cursor pop];
}
/* Puts the receiver on top of the cursor stack and makes it the current cursor. */
void NSCursor_push(NSCursor* cursor) {
	[cursor push];
}
/* Makes the receiver the current cursor. */
void NSCursor_set(NSCursor* cursor) {
	[cursor set];
}


#ifdef __cplusplus
}
#endif