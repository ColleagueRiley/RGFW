#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#define GL_SILENCE_DEPRECATION
#include <CoreVideo/CVDisplayLink.h>
#include <ApplicationServices/ApplicationServices.h>


#include "macros.h"
#include "types.h"
#include "enums.h"
#include "mac_load.h"

/* Objective-C class methods. */
mac_function_define(Class, class);
mac_function_define(void*, init);
mac_function_define(void*, alloc);
mac_function_define(void*, release);
mac_function_define(void*, retain);
mac_function_define(void*, autorelease);


/* Linking C functions to Window and View classes. */
typedef bool format(void* self, ...);
extern format* funcs[2];

/* */
NSRect NSMakeRect(CGFloat x, CGFloat y, CGFloat w, CGFloat h);


/* ============ NSControl class ============ */
/* ====== NSControl properties ======*/
/**/
define_property(NSControl, id, target, Target, control);
/**/
define_property(NSControl, SEL, action, Action, control);
/**/
define_property(NSControl, NSFont*, font, Font, control);

/* ====== NSControl functions ======*/
/**/
NSControl* NSControl_initWithFrame(NSControl* control, NSRect frameRect);


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
/* Get/Set the frame of the window. */
define_property(NSWindow, NSRect, frame, Frame, window);
/* Get/Set the background color of the window. */
define_property(NSWindow, NSColor*, backgroundColor, BackgroundColor, window);
/* Get/set the opaque of the window. */
define_property(NSWindow, bool, isOpaque, Opaque, window);

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


/* ============ NSView class ============ */
/* ====== NSView functions ====== */
/* */
NSView* NSView_init();
/* */
define_inherented_function(NSView, initWithFrame, NSRect frameRect);
/* */
void NSView_addSubview(NSView* view, NSView* subview);
/* */
void NSView_release(NSView* view);


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
define_inherented_function(NSTextField, init, NSRect frameRect);


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
define_inherented_function(NSButton, init, NSRect frameRect);
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
define_inherented_function(NSComboBox, init, NSRect frameRect);
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
void NSApplication_setApplicationIconImage(NSApplication* application, NSImage* image);
/* */
NSEvent* NSApplication_nextEventMatchingMask(NSApplication* application, NSEventMask mask, NSDate* expiration, int mode, bool deqFlag);


/* ============ NSScreen class ============ */
/* */
NSScreen* NSScreen_mainScreen();
/* */
NSRect NSScreen_frame(NSScreen* screen);


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
NSMenuItem** NSMenu_itemArray(NSMenu* menu);
/* */
NSMenuItem* NSMenuItem_separatorItem();


/* ============ NSColor class ============ */
/* ====== NSColor functions ====== */
/* */
void NSColor_set(NSColor* color);
/* */
NSColor* NSColor_colorWithSRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha);
/* */
NSColor* NSColor_keyboardFocusIndicatorColor();


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
NSImage* NSImage_initWithData(unsigned char* bitmapData, NSUInteger length);


/* deprecated, kinda ignore it for now. */
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