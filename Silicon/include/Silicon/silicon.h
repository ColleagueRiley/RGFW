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

/* Functions */
NSRect NSMakeRect(CGFloat x, CGFloat y, CGFloat w, CGFloat h);

NSWindow* NSWindow_init(NSRect contentRect, NSWindowStyleMask style, NSBackingStoreType backingStoreType, bool flag);
void NSWindow_setTitle(NSWindow* window, const char* title);
void NSWindow_setContentView(NSWindow* window, NSView* view);
NSView* NSWindow_contentView(NSWindow* window);
void NSWindow_setDelegate(NSWindow* window, id object);
void NSWindow_orderFront(NSWindow* window, NSWindow* sender);
void NSWindow_makeKeyWindow(NSWindow* window);
void NSWindow_setIsVisible(NSWindow* window, bool flag);
NSRect NSWindow_frame(NSWindow* window);
void NSWindow_center(NSWindow* window);
void NSWindow_makeMainWindow(NSWindow* window);
  
void NSWindow_setFrame(NSWindow* window, NSRect rect);

NSView* NSView_init();
NSView* NSView_initWithFrame(NSRect frameRect);
void NSView_addSubview(NSView* view, NSView* subview);
void NSView_release(NSView* view);

NSTextField* NSTextField_init(NSRect frameRect);
void NSTextField_setStringValue(NSTextField* field, const char* string);
void NSTextField_setBezeled(NSTextField* field, bool flag);
void NSTextField_setDrawsBackground(NSTextField* field, bool flag);
void NSTextField_setEditable(NSTextField* field, bool flag);
void NSTextField_setSelectable(NSTextField* field, bool flag);
void NSTextField_setTextColor(NSTextField* field, NSColor* color);
void NSTextField_setFont(NSTextField* field, NSFont* font);
NSFont* NSTextField_font(NSTextField* field);

NSFontManager* NSFontManager_sharedFontManager();
NSFont* NSFontManager_convertFont(NSFontManager* manager, NSFont* fontObj);
NSFont* NSFontManager_convertFontToHaveTrait(NSFontManager* manager, NSFont* fontObj, NSFontTraitMask trait);

NSFont* NSFont_init(const char* fontName, CGFloat fontSize);
const char* NSFont_fontName(NSFont* font);

NSButton* NSButton_init(NSRect frameRect);
void NSButton_setTitle(NSButton* button, const char* title);
void NSButton_setBezelStyle(NSButton* button, NSBezelStyle bezelStyle);
void NSButton_setTarget(NSButton* button, id target);
void NSButton_setAction(NSButton* button, SEL action);
void NSButton_setAutoresizingMask(NSButton* button, NSAutoresizingMaskOptions autoresizingMask);
void NSButton_setButtonType(NSButton* button, NSButtonType type);
void NSButton_setState(NSButton* button, NSControlStateValue value);
NSControlStateValue NSButton_state(NSButton* button);
void NSButton_setAllowsMixedState(NSButton* button, bool flag);

bool NSApp_setActivationPolicy(NSApplicationActivationPolicy activationPolicy);
void NSApp_activateIgnoringOtherApps(bool flag);
void NSApp_run();
void NSApp_finishLaunching();
void NSApp_sendEvent(NSEvent* event);
void NSApp_updateWindows();
void NSApp_terminate(id sender);
void NSApp_stop(id sender);
NSMenu* NSApp_mainMenu();
void NSApp_setMainMenu(NSMenu* mainMenu);
void NSApp_setServicesMenu(NSMenu* menu);
void NSApp_setHelpMenu(NSMenu* menu);
void NSApp_setWindowsMenu(NSMenu* menu);
NSEvent* NSApp_nextEventMatchingMask(NSEventMask mask, NSDate* expiration, int mode, bool deqFlag);


NSApplication* NSApplication_sharedApplication();
void NSApplication_run(NSApplication* sharedApplication);
void NSApplication_stop(NSApplication* application, void* view);
void NSApplication_terminate(NSApplication* application, id sender);
void NSApplication_sendEvent(NSApplication* application, NSEvent* event);
NSEvent* NSApplication_nextEventMatchingMask(NSApplication* application, NSEventMask mask, NSDate* expiration, int mode, bool deqFlag);

NSEventType NSEvent_type(NSEvent* event);
unsigned int NSEvent_keyCode(NSEvent* event);
char* NSEvent_characters(NSEvent* event);
CGFloat NSEvent_deltaY(NSEvent* event);
unsigned int NSEvent_keyCodeForChar(char* keyStr);
NSPoint NSEvent_locationInWindow(NSEvent* event);

NSEventModifierFlags NSEvent_modifierFlags(NSEvent* event);

NSMenu* NSMenu_init(const char* title);
void NSMenu_addItem(NSMenu* menu, NSMenuItem* newItem);
NSMenuItem* NSMenuItem_init(const char* title, SEL selector, char* keyEquivalent);
NSMenuItem** NSMenu_itemArray(NSMenu* menu);

NSMenu* NSMenuItem_submenu(NSMenuItem* item);
void NSMenuItem_setSubmenu(NSMenuItem* item, NSMenu* submenu);
NSMenuItem* NSMenuItem_separatorItem();
void NSMenuItem_setTitle(NSMenuItem* item, const char* title);

void NSColor_set(NSColor* color);
NSColor* NSColor_colorWithSRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha);
NSColor* NSColor_keyboardFocusIndicatorColor();


void NSBezierPath_strokeLine(NSPoint from, NSPoint to);

NSDate* NSDate_distantFuture();

NSProcessInfo* NSProcessInfo_processInfo();
const char* NSProcessInfo_processName(NSProcessInfo* processInfo);

/* deprecated. */
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
