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

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#define GL_SILENCE_DEPRECATION
#include <CoreVideo/CVDisplayLink.h>
#include <ApplicationServices/ApplicationServices.h>


#include "../macros.h"
#include "../mac_load.h"
#include "types.h"
#include "enums.h"


extern const NSSize _NSZeroSize;
/* An NSSize structure set to 0 in both dimensions. */
#define NSZeroSize _NSZeroSize


/* Returns the logon name of the current user. */
#define NSUserName _NSUserName
const char* NSUserName();

/* Returns the path to either the user’s or application’s home directory, depending on the platform. */
#define NSHomeDirectory _NSHomeDirectory
const char* NSHomeDirectory();

/* Creates a list of directory search paths. */
#define NSSearchPathForDirectoriesInDomains _NSSearchPathForDirectoriesInDomains
siArray(const char*) NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory directory, NSSearchPathDomainMask domainMask, bool expandTilde);


/* ============ Geometry functions ============ */
/* Creates a new NSRect from the specified values. */
NSRect NSMakeRect(CGFloat x, CGFloat y, CGFloat w, CGFloat h);
/* Creates a new NSPoint from the specified values. */
NSPoint NSMakePoint(CGFloat x, CGFloat y);
/* Returns a new NSSize from the specified values. */
NSSize NSMakeSize(CGFloat w, CGFloat h);
/* Returns the largest x coordinate of a given rectangle. */
CGFloat NSMaxX(NSRect aRect);
/* Returns the largest y coordinate of a given rectangle. */
CGFloat NSMaxY(NSRect aRect);
/* Returns the x coordinate of a given rectangle’s midpoint. */
CGFloat NSMidX(NSRect aRect);
/* Returns the y coordinate of a given rectangle’s midpoint. */
CGFloat NSMidY(NSRect aRect);
/* Returns the smallest x coordinate of a given rectangle. */
CGFloat NSMinX(NSRect aRect);
/* Returns the smallest y coordinate of a given rectangle. */
CGFloat NSMinY(NSRect aRect);
/* Returns the width of the specified rectangle. */
CGFloat NSWidth(NSRect aRect);
/* Returns the height of a given rectangle. */
CGFloat NSHeight(NSRect aRect);
/* Returns an NSRect typecast from a CGRect. */
NSRect NSRectFromCGRect(CGRect cgrect);
/* Returns a CGRect typecast from an NSRect. */
CGRect NSRectToCGRect(NSRect nsrect);
/* Returns an NSPoint typecast from a CGPoint. */
NSPoint NSPointFromCGPoint(CGPoint cgpoint);
/* Returns a CGPoint typecast from an NSPoint. */
CGPoint NSPointToCGPoint(NSPoint nspoint);
/* Returns an NSSize typecast from a CGSize. */
NSSize NSSizeFromCGSize(CGSize cgsize);
/* Returns a CGSize typecast from an NSSize. */
CGSize NSSizeToCGSize(NSSize nssize);
/* Returns a Boolean value that indicates whether a given point is in a given rectangle. */
bool NSPointInRect(NSPoint aPoint, NSRect aRect);


/* ============ NSControl class ============ */
/* ====== NSControl properties ======*/
/**/
define_property(NSControl, id, target, Target, control);
/**/
define_property(NSControl, SEL, action, Action, control);
/**/
define_property(NSControl, NSFont*, font, Font, control);
/* */
define_property(NSControl, double, doubleValue, DoubleValue, control);

/* ====== NSControl functions ======*/
/**/
NSControl* NSControl_initWithFrame(NSRect frameRect);


/* ============ NSWindow class ============ */
/* ====== NSWindow properties ====== */
/* Get/Set the title of the window. */
define_property(NSWindow, const char*, title, Title, window);
/* Get/Set the NSView of the window. */
define_property(NSWindow, NSView*, contentView, ContentView, window);
/* Get/Set the delegate of the window. */
define_property(NSWindow, id, delegate, Delegate, window);
/* Get/Set the visbility of the window. */
define_property(NSWindow, bool, isVisible, IsVisible, window);
/* Get/Set the background color of the window. */
define_property(NSWindow, NSColor*, backgroundColor, BackgroundColor, window);
/* Get/set the opaque of the window. */
define_property(NSWindow, bool, isOpaque, Opaque, window);
/* The window’s alpha value. */
define_property(NSWindow, CGFloat, alphaValue, AlphaValue, window);
/* A Boolean value that indicates whether the window accepts mouse-moved events. */
define_property(NSWindow, bool, acceptsMouseMovedEvents, AcceptsMouseMovedEvents, window);
/* Get/Set the frame of the window. */
NSRect NSWindow_frame(NSWindow* window);

/* ====== NSWindow functions ====== */
/* Initializes a NSWindow handle. */
NSWindow* NSWindow_init(NSRect contentRect, NSWindowStyleMask style, NSBackingStoreType backingStoreType, bool flag);
/* */
void NSWindow_orderFront(NSWindow* window, NSWindow* sender);
/* */
void NSWindow_makeKeyWindow(NSWindow* window);
/* */
bool NSWindow_isKeyWindow(NSWindow* window);
/* */
void NSWindow_center(NSWindow* window);
/* */
void NSWindow_makeMainWindow(NSWindow* window);
/* */
void NSWindow_setFrameAndDisplay(NSWindow* window, NSRect frame, bool display, bool animate);
/* */
NSPoint NSWindow_convertPointFromScreen(NSWindow* window, NSPoint point);
/* Passes a display message down the window’s view hierarchy, thus redrawing all views within the window. */
void NSWindow_display(NSWindow* window);


/* ============ NSView class ============ */
/* ====== NSView functions ====== */
/* */
NSView* NSView_init();
/* */
NSView* NSView_initWithFrame(NSRect frameRect);
/* */
void NSView_addSubview(NSView* view, NSView* subview);
/* */
void NSView_registerForDraggedTypes(NSView* view, siArray(NSPasteboardType) newTypes);


/* ============ NSTextField class ============ */
/* ====== NSTextField properties ====== */
/* */
define_property(NSTextField, const char*, stringValue, StringValue, field);
/* */
define_property(NSTextField, bool, isBezeled, Bezeled, field);
/* */
define_property(NSTextField, bool, drawsBackground, DrawsBackground, field);
/* */
define_property(NSTextField, bool, isEditable, Editable, field);
/* */
define_property(NSTextField, bool, isSelectable, Selectable, field);
/* */
define_property(NSTextField, NSColor*, textColor, TextColor, field);
/**/
define_property(NSTextField, NSFont*, font, Font, field);

/* ====== NSTextField functions ====== */
/* Initializes a NSTextField handle. */
NSTextField* NSTextField_initWithFrame(NSRect frameRect);


/* ============ NSFontManager class ============ */
/* ====== NSFontManager functions ====== */
/* */
NSFontManager* NSFontManager_sharedFontManager();
/* */
NSFont* NSFontManager_convertFont(NSFontManager* manager, NSFont* fontObj);
/* */
NSFont* NSFontManager_convertFontToHaveTrait(NSFontManager* manager, NSFont* fontObj, NSFontTraitMask trait);


/* ============ NSFont class ============ */
/* ====== NSFont functions ====== */
/* */
NSFont* NSFont_init(const char* fontName, CGFloat fontSize);
/* */
const char* NSFont_fontName(NSFont* font);


/* ============ NSButton class ============ */
/* ====== NSButton properties ====== */
/* */
define_property(NSButton, const char*, title, Title, button);
/* */
define_property(NSButton, NSBezelStyle, bezelStyle, BezelStyle, button);
/* */
define_property(NSButton, id, target, Target, button);
/* */
define_property(NSButton, SEL, action, Action, button);
/* */
define_property(NSButton, NSAutoresizingMaskOptions, autoresizingMask, AutoresizingMask, button);
/* */
define_property(NSButton, NSControlStateValue, state, State, button);
/* */
define_property(NSButton, bool, allowsMixedState, AllowsMixedState, button);

/* ====== NSButton functions ====== */
/* */
NSButton* NSButton_initWithFrame(NSRect frameRect);
/* */
void NSButton_setButtonType(NSButton* button, NSButtonType buttonType);


/* ============ NSComboBox class ============ */
/* ====== NSComboBox properties ====== */
/* (read-only) */
NSInteger NSComboBox_indexOfSelectedItem(NSComboBox* comboBox);
/**/
define_property(NSComboBox, id, target, Target, comboBox);
/**/
define_property(NSComboBox, SEL, action, Action, comboBox);
/**/
define_property(NSComboBox, NSFont*, font, Font, comboBox);
/* */
define_property(NSComboBox, const char*, stringValue, StringValue, field);
/* */
define_property(NSComboBox, bool, isBezeled, Bezeled, field);
/* */
define_property(NSComboBox, bool, drawsBackground, DrawsBackground, field);
/* */
define_property(NSComboBox, bool, isEditable, Editable, field);
/* */
define_property(NSComboBox, bool, isSelectable, Selectable, field);
/* */
define_property(NSComboBox, NSColor*, textColor, TextColor, field);
/**/
define_property(NSComboBox, NSFont*, font, Font, field);


/* ====== NSComboBox functions ====== */
/**/
NSComboBox* NSComboBox_initWithFrame(NSRect frameRect);
/* */
void NSComboBox_addItem(NSComboBox* comboBox, void* item);
/* */
void NSComboBox_selectItem(NSComboBox* comboBox, NSInteger index);


/* ============ NSApplication class ============ */
extern NSApplication* _NSApp;
/* The global variable for the shared app instance. Get initialized after running the 'sharedApplication' function. */
#define NSApp _NSApp
/* ====== NSApplication properties ====== */
/* */
define_property(NSApplication, NSMenu*, mainMenu, MainMenu, application);
/* */
define_property(NSApplication, NSMenu*, servicesMenu, ServicesMenu, application);
/* */
define_property(NSApplication, NSMenu*, helpMenu, HelpMenu, application);
/* */
define_property(NSApplication, NSMenu*, windowsMenu, WindowsMenu, application);
/* */
define_property(NSApplication, NSApplicationActivationPolicy, activationPolicy, ActivationPolicy, application);
/* */
define_property(NSApplication, NSImage*, applicationIconImage, ApplicationIconImage, application);

/* ====== NSApplication functions ====== */
/* */
NSApplication* NSApplication_sharedApplication();
/* */
void NSApplication_finishLaunching(NSApplication* application);
/* */
void NSApplication_run(NSApplication* application);
/* */
void NSApplication_stop(NSApplication* application, void* view);
/* */
void NSApplication_terminate(NSApplication* application, id sender);
/* */
void NSApplication_sendEvent(NSApplication* application, NSEvent* event);
/* */
void NSApplication_updateWindows(NSApplication* application);
/* */
void NSApplication_activateIgnoringOtherApps(NSApplication* application, bool flag);
/* */
NSEvent* NSApplication_nextEventMatchingMask(NSApplication* application, NSEventMask mask, NSDate* expiration, int mode, bool deqFlag);


/* ============ NSScreen class ============ */
/* ====== NSScreen properties ====== */
/* Returns the screen object containing the window with the keyboard focus. */
NSScreen* NSScreen_mainScreen();
/* The dimensions and location of the screen. */
NSRect NSScreen_frame(NSScreen* screen);
/* The current location and dimensions of the visible screen. */
NSRect NSScreen_visibleFrame(NSScreen* screen);


/* ============ NSEvent class ============ */
/* ====== NSEvent functions ====== */
/* */
NSEventType NSEvent_type(NSEvent* event);
/* */
NSPoint NSEvent_locationInWindow(NSEvent* event);
/* */
NSEventModifierFlags NSEvent_modifierFlags(NSEvent* event);
/* */
unsigned short NSEvent_keyCode(NSEvent* event);
/* */
const char* NSEvent_characters(NSEvent* event);
/* */
CGFloat NSEvent_deltaY(NSEvent* event);
/* */
unsigned short NSEvent_keyCodeForChar(char* keyStr);
/* */
NSPoint NSEvent_mouseLocation(NSEvent* event);
/* */
NSWindow* NSEvent_window(NSEvent* event);


/* ============ NSMenu class ============ */
/* ====== NSMenu functions ====== */
/* */
NSMenu* NSMenu_init(const char* title);
/* */
void NSMenu_addItem(NSMenu* menu, NSMenuItem* newItem);


/* ============ NSMenuItem class ============ */
/* ====== NSMenuItem properties ====== */
/* */
define_property(NSMenuItem, NSMenu*, submenu, Submenu, item);
/* */
define_property(NSMenuItem, const char*, title, Title, item);

/* ====== NSMenuItem functions ====== */
/* */
NSMenuItem* NSMenuItem_init(const char* title, SEL selector, const char* keyEquivalent);
/* */
siArray(NSMenuItem*) NSMenu_itemArray(NSMenu* menu);
/* */
NSMenuItem* NSMenuItem_separatorItem();


/* ============ NSColor class ============ */
/* ====== NSColor properties ====== */
/* */
NSColor* NSColor_clearColor();
/* */
NSColor* NSColor_keyboardFocusIndicatorColor();

/* ====== NSColor functions ====== */
/* */
void NSColor_set(NSColor* color);
/* */
NSColor* NSColor_colorWithRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha);
/* */
NSColor* NSColor_colorWithSRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha);
/* Creates a color object using the given opacity and grayscale values. */
NSColor* NSColor_colorWithCalibrated(CGFloat white, CGFloat alpha);


/* ============ NSBezierPath class ============ */
/* ====== NSBezierPath functions ====== */
/* */
void NSBezierPath_strokeLine(NSPoint from, NSPoint to);


/* ============ NSDate class ============ */
/* ====== NSDate functions ====== */
/* */
NSDate* NSDate_distantFuture();


/* ============ NSProcessInfo class ============ */
/* ====== NSProcessInfo functions ====== */
/* */
NSProcessInfo* NSProcessInfo_processInfo();
/* */
const char* NSProcessInfo_processName(NSProcessInfo* processInfo);


/* ============ NSImage class ============ */
/* ====== NSImage functions ====== */
/* Initializes and returns an image object with the specified dimensions. */
NSImage* NSImage_initWithSize(NSSize size);
/* */
NSImage* NSImage_initWithData(unsigned char* bitmapData, NSUInteger length);
/* Initializes a data object with the content of the file at a given path. */
NSImage* NSImage_initWithFile(const char* path);
/* */
NSImage* NSImage_initWithCGImage(CGImageRef cgImage, NSSize size);
/* Adds the specified image representation object to the image. */
void NSImage_addRepresentation(NSImage* image, NSImageRep* imageRep);
/* Returns the application’s current cursor. */
NSCursor* NSCursor_currentCursor();

/* ============ NSGraphicsContext class ============ */
/* ====== NSGraphicsContext properties ====== */
/* */
#if (OS_X_VERSION_MAX_ALLOWED < macos_version(10, 5)) /* 'currentContext' doesn't exist in OS X 10.5+. */
/* */
implement_deprecated_property(NSGraphicsContext, NSGraphicsContext*, currentContext, CurrentContext, context, macos(10.5));
#endif


/* =========== NSPasteboard class ============ */
/* ====== NSPasteboard functions ====== */
/* */
NSPasteboard* NSPasteboard_generalPasteboard();
/* */
const char* NSPasteboard_stringForType(NSPasteboard* pasteboard, NSPasteboardType dataType);
/* */
NSInteger NSPasteBoard_declareTypes(NSPasteboard* pasteboard, siArray(NSPasteboardType) newTypes, void* owner);
/* */
bool NSPasteBoard_setString(NSPasteboard* pasteboard, const char* stringToWrite, NSPasteboardType dataType);
/* */
siArray(const char*) NSPasteboard_readObjectsForClasses(NSPasteboard* pasteboard, siArray(Class) classArray, void* options);



/* ============ NSSlider class ============ */
/* ====== NSSlider properties ====== */
/**/
define_property(NSSlider, id, target, Target, slider);
/**/
define_property(NSSlider, SEL, action, Action, slider);
/**/
define_property(NSSlider, NSFont*, font, Font, slider);
/* */
define_property(NSSlider, double, doubleValue, DoubleValue, slider);
/* */
define_property(NSSlider, double, maxValue, MaxValue, slider);

/* ====== NSSlider functions ====== */
/* */
NSSlider* NSSlider_initWithFrame(NSRect frameRect);



/* ============ NSProgressIndicator class ============ */
/* ====== NSProgressIndicator properties ====== */
/* */
define_property(NSProgressIndicator, double, doubleValue, DoubleValue, progressIndicator);
/* */
define_property(NSProgressIndicator, double, maxValue, MaxValue, progressIndicator);
/* */
define_property(NSProgressIndicator, bool, isIndeterminate, Indeterminate, progressIndicator);

/* ====== NSProgressIndicator functions ====== */
/* */
NSProgressIndicator* NSProgressIndicator_init(NSRect frameRect);


/* ============ NSDraggingInfo class ============ */
/* ====== NSDraggingInfo properties ====== */
/* */
NSPasteboard* NSDraggingInfo_draggingPasteboard(NSDraggingInfo* info);
/* */
NSPoint NSDraggingInfo_draggingLocation(NSDraggingInfo* info);
/* */
define_property(NSDraggingInfo, NSInteger, numberOfValidItemsForDrop, NumberOfValidItemsForDrop, info);
/* */
NSWindow* NSDraggingInfo_draggingDestinationWindow(NSDraggingInfo* info);


/* ============ NSColorPanel class ============ */
/* ====== NSColorPanel properties ====== */
define_property(NSColorPanel, NSColor*, color, Color, colorPanel);


/* ============ NSBitmapImageRep class ============ */
/* ====== NSBitmapImageRep properties ====== */
unsigned char* NSBitmapImageRep_bitmapData(NSBitmapImageRep* imageRep);

/* ====== NSBitmapImageRep functions ====== */
/* Initializes a newly allocated bitmap image representation so it can render the specified image. */
NSBitmapImageRep* NSBitmapImageRep_initWithBitmapData(unsigned char** planes, NSInteger width, NSInteger height, NSInteger bps, NSInteger spp, bool alpha, bool isPlanar, const char* colorSpaceName, NSBitmapFormat bitmapFormat, NSInteger rowBytes, NSInteger pixelBits);


/* ============ NSSavePanel class ============ */
/* ====== NSSavePanel properties ====== */
/* A Boolean value that indicates whether the panel displays UI for creating directories. */
define_property(NSSavePanel, bool, canCreateDirectories, CanCreateDirectories, savePanel);
/* (Deprecated!) An array of filename extensions or UTIs that represent the allowed file types for the panel. */
define_property(NSSavePanel, siArray(const char*), allowedFileTypes, AllowedFileTypes, savePanel);
/* The current directory shown in the panel. */
define_property(NSSavePanel, NSURL*, directoryURL, DirectoryURL, savePanel);
/* The user-editable filename currently shown in the name field. */
define_property(NSSavePanel, const char*, nameFieldStringValue, NameFieldStringValue, savePanel);
/* A URL that contains the fully specified location of the targeted file. */
NSURL* NSSavePanel_URL(NSSavePanel* savePanel);

/* ====== NSSavePanel functions ====== */
/* Displays the panel and begins its event loop with the current working (or last-selected) directory as the default starting point. */
NSModalResponse NSSavePanel_runModal(NSSavePanel* savePanel);


/* ============ NSURL class ============ */
/* ====== NSURL properties ====== */
const char* NSURL_path(NSURL* url);

/* ====== NSURL functions ====== */
/* Initializes and returns a newly created NSURL object as a file URL with a specified path. */
NSURL* NSURL_fileURLWithPath(const char* path);


/* ============ NSOpenPanel class ============ */
/* ====== NSOpenPanel properties ====== */
/* A Boolean that indicates whether the user can choose files in the panel. */
define_property(NSOpenPanel, bool, canChooseFiles, CanChooseFiles, openPanel);
/* A Boolean that indicates whether the user can choose directories in the panel. */
define_property(NSOpenPanel, bool, canChooseDirectories, CanChooseDirectories, openPanel);
/* A Boolean value that indicates whether the panel displays UI for creating directories. */
define_property(NSOpenPanel, bool, canCreateDirectories, CanCreateDirectories, openPanel);
/* A Boolean that indicates whether the panel resolves aliases. */
define_property(NSOpenPanel, bool, resolvesAliases, ResolvesAliases, openPanel);
/* A Boolean that indicates whether the user may select multiple files and directories. */
define_property(NSOpenPanel, bool, allowsMultipleSelection, AllowsMultipleSelection, openPanel);
/* A Boolean value that indicates whether the panel's accessory view is visible. */
define_property(NSOpenPanel, bool, accessoryViewDisclosed, AccessoryViewDisclosed, openPanel);
/* An array of URLs, each of which contains the fully specified location of a selected file or directory. */
siArray(NSURL*) NSOpenPanel_URLs(NSOpenPanel* openPanel);
/* A Boolean value that indicates how the panel responds to iCloud documents that aren't fully downloaded locally. */
define_property(NSOpenPanel, bool, canDownloadUbiquitousContents, CanDownloadUbiquitousContents, openPanel);
/* A Boolean value that indicates whether the panel's accessory view is visible. */
define_property(NSOpenPanel, bool, canResolveUbiquitousConflicts, CanResolveUbiquitousConflicts, openPanel);
/* (Deprecated!) An array of filename extensions or UTIs that represent the allowed file types for the panel. */
define_property(NSOpenPanel, siArray(const char*), allowedFileTypes, AllowedFileTypes, openPanel);
/* The current directory shown in the panel. */
define_property(NSOpenPanel, NSURL*, directoryURL, DirectoryURL, openPanel);
/* The user-editable filename currently shown in the name field. */
define_property(NSOpenPanel, const char*, nameFieldStringValue, NameFieldStringValue, openPanel);
/* A URL that contains the fully specified location of the targeted file. */
NSURL* NSOpenPanel_URL(NSOpenPanel* openPanel);

/* ====== NSOpenPanel functions ====== */
/* Creates a new Open panel and initializes it with a default configuration. */
NSOpenPanel* NSOpenPanel_openPanel();
/* Displays the panel and begins its event loop with the current working (or last-selected) directory as the default starting point. */
NSModalResponse NSOpenPanel_runModal(NSOpenPanel* openPanel);


/* ============ NSCursor class ============ */
/* ====== NSCursor properties ====== */
/* The cursor’s image. */
NSImage* NSCursor_image(NSCursor* cursor);
/* The position of the cursor's hot spot. */
NSPoint NSCursor_hotSpot(NSCursor* cursor);
/* Returns the default cursor, the arrow cursor. */
NSCursor* NSCursor_arrowCursor();

/* ====== NSCursor functions ====== */
/* Initializes a cursor with the given image and hot spot. */
NSCursor* NSCursor_initWithImage(NSImage* newImage, NSPoint aPoint);
/* Makes the current cursor invisible. */
void NSCursor_hide();
/* Makes the current cursor invisible. */
void NSCursor_unhide();
/* Pops the current cursor off the top of the stack. */
void NSCursor_pop(NSCursor* cursor);
/* Puts the receiver on top of the cursor stack and makes it the current cursor. */
void NSCursor_push(NSCursor* cursor);
/* Makes the receiver the current cursor. */
void NSCursor_set(NSCursor* cursor);


/* TODO(EimaMei): Add documentation & deprecations macros for the OpenGL functions. */
NSOpenGLPixelFormat* NSOpenGLPixelFormat_initWithAttributes(const NSOpenGLPixelFormatAttribute* attribs);
NSOpenGLView* NSOpenGLView_initWithFrame(NSRect frameRect, NSOpenGLPixelFormat* format);
void NSOpenGLView_prepareOpenGL(NSOpenGLView* view);
NSOpenGLContext* NSOpenGLView_openGLContext(NSOpenGLView* view);
void NSOpenGLContext_setValues(NSOpenGLContext* context, const int* vals, NSOpenGLContextParameter param);
void NSOpenGLContext_makeCurrentContext(NSOpenGLContext* context);
void NSOpenGLContext_flushBuffer(NSOpenGLContext* context);

#undef GL_SILENCE_DEPRECATION
#ifdef __cplusplus
}
#endif