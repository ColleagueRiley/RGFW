#include <AppKit/AppKit.h>
#include <objc/runtime.h>

#include <Silicon/mac_load.h>
#include <Silicon/macros.h>

#include <string.h>


/* NSString / char* conversion functions. */
#define char_to_NSString(text) [[NSString stringWithUTF8String:(text)] autorelease]
#define NSString_to_char(text) [text UTF8String]

/* Implementation functions*/
/* Implements the Class property. */
#define implement_property(class, type, name, uppercased_name, arg_name) \
    type class##_##name(class* arg_name) { \
        return [arg_name name]; \
    } \
    void class##_set##uppercased_name(class* arg_name, type name) { \
        [arg_name set##uppercased_name:name]; \
    }

// Implement a property for a given class that returns a C string
#define implement_str_property(class, type, name, uppercased_name, arg_name) \
    type class##_##name(class* arg_name) { \
        return NSString_to_char([arg_name name]); \
    } \
    void class##_set##uppercased_name(class* arg_name, type name) { \
        [arg_name set##uppercased_name:([char_to_NSString(name) retain])]; \
    }


typedef bool format(void* self, ...);
format* funcs[2];

/* Key stuff. */
char* NSKEYS[] = {
	"Up", "Down", "Left", "Right",
	"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
	"Delete", "Insert", "Home", "End", "PageUp", "PageDown",
	"Backspace", "Tab", "Enter", "Return",
	"Escape", "Space", "Shift", "CapsLock", "BackSpace"
};
unsigned short NSKEYI[sizeof(NSKEYS)] = {
	NSUpArrowFunctionKey, NSDownArrowFunctionKey, NSLeftArrowFunctionKey, NSRightArrowFunctionKey,
	NSF1FunctionKey, NSF2FunctionKey, NSF3FunctionKey, NSF4FunctionKey, NSF5FunctionKey, NSF6FunctionKey, NSF7FunctionKey, NSF8FunctionKey, NSF9FunctionKey, NSF10FunctionKey, NSF11FunctionKey, NSF12FunctionKey,
	NSDeleteFunctionKey, NSInsertFunctionKey, NSHomeFunctionKey, NSEndFunctionKey, NSPageUpFunctionKey, NSPageDownFunctionKey,
	NSBackspaceCharacter, NSTabCharacter, NSNewlineCharacter, NSCarriageReturnCharacter,
	0x1B, 0x20, 0x56, 0x57, 0x51
};
unsigned char NSKEYCOUNT = sizeof(NSKEYS);

@interface WindowClass : NSWindow {}
@end

@implementation WindowClass
	- (bool)windowShouldClose:(void*)sender {
		if (funcs[0] != NULL)
		   funcs[0](self, sender);

		return true;
	}
@end


@interface ViewClass : NSView {}
@end

@implementation ViewClass
	- (NSTextField*)label {
		return [NSTextField alloc];
	}
	- (void)drawRect:(NSRect)rect {
		if (funcs[1] != NULL)
		   funcs[1](self, rect);
	}
@end


/* ============ NSControl class ============ */
/* ====== NSControl properties ======*/
/* */
implement_property(NSControl, id, target, Target, control);
/* */
implement_property(NSControl, SEL, action, Action, control);
/* */
implement_property(NSControl, NSFont*, font, Font, control);

/* ====== NSControl functions ======*/
/**/
NSControl* NSControl_initWithFrame(NSControl* control, NSRect frameRect) {
	return [control initWithFrame:(frameRect)];
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
/* Get the frame of the window. */
NSRect NSWindow_frame(NSWindow* window) {
	return [window frame];
}
/* */
implement_property(NSWindow, NSColor*, backgroundColor, BackgroundColor, window);
/* Toggle opaque for the window. */
implement_property(NSWindow, bool, isOpaque, Opaque, window);

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
void NSWindow_setFrame(NSWindow* window, NSRect frame) {
	[window setFrame:(frame) display:(true) animate:(true)];
}


/* ============ NSView class ============ */
/* ====== NSView functions ====== */
/* */
NSView* NSView_init() {
	return [[ViewClass alloc] init];
}
/* */
define_inherented_function(NSView, initWithFrame, NSRect frameRect)
	implement_inherented_function(NSView, NSControl, initWithFrame, (void*)[ViewClass alloc], frameRect)
/* */
void NSView_addSubview(NSView* view, NSView* subview) {
	[view addSubview:(subview)];
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
define_inherented_function(NSTextField, init, NSRect frameRect)
	implement_inherented_function(NSTextField, NSControl, initWithFrame, (void*)[[ViewClass alloc] label], frameRect)


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
	return [NSFont fontWithName:(str) size:(fontSize)];
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
define_inherented_function(NSButton, init, NSRect frameRect)
	implement_inherented_function(NSButton, NSControl, initWithFrame, (void*)[NSButton alloc], frameRect)
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
define_inherented_function(NSComboBox, init, NSRect frameRect)
	implement_inherented_function(NSComboBox, NSControl, initWithFrame, (void*)[NSComboBox alloc], frameRect)

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
void NSApplication_setApplicationIconImage(NSApplication* application, NSImage* image){
    return [NSApp setApplicationIconImage:image];
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
NSScreen* NSScreen_mainScreen() {
	return [NSScreen mainScreen];
}
/* */ 
NSRect NSScreen_frame(NSScreen* screen) {
	return [screen frame];
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
    unsigned int i;
    for (i = 0; i < NSKEYCOUNT; i++)
        if (strcmp(keyStr, NSKEYS[i]))
            return NSKEYI[i + 1];
    NSString *keyString = char_to_NSString(keyStr);
	unichar keyChar = [keyString characterAtIndex:(0)];
	return keyChar;
}
/* */
const char* NSEvent_characters(NSEvent* event) {
    unichar keyCode = [[event charactersIgnoringModifiers] characterAtIndex:(0)];
    NSUInteger flags = [event modifierFlags] & (NSEventModifierFlagShift | NSEventModifierFlagControl | NSEventModifierFlagOption | NSEventModifierFlagCommand);

    unsigned int i;
    for (i = 0; i < NSKEYCOUNT; i++) {
        if (keyCode == NSKEYI[i])
            return NSKEYS[i];
	}

    return NSString_to_char([event characters]);
}
/* */
CGFloat NSEvent_deltaY(NSEvent* event) {
    return [event deltaY];
}


/* ============ NSMenu class ============ */
/* ====== NSMenu functions ====== */
/* */
NSMenu* NSMenu_init(const char* title) {
	return [[NSMenu alloc] initWithTitle:(char_to_NSString(title))];
}

/* ============ NSMenu class ============ */
/* ====== NSMenu functions ====== */
/* */
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
NSMenuItem** NSMenu_itemArray(NSMenu* menu) {
	NSArray* item_array = [menu itemArray];
	NSMenuItem** result = malloc(sizeof(*result) * item_array.count);

	for (size_t i = 0; i < item_array.count; i++) {
		result[i] = [item_array objectAtIndex:(i)];
		[result[i] retain];
	}

	return result;
}
/* */
NSMenuItem* NSMenuItem_separatorItem() {
	return [NSMenuItem separatorItem];
}


/* ============ NSColor class ============ */
/* ====== NSColor functions ====== */
/* */
void NSColor_set(NSColor* color) {
	[color set];
}
/* */
NSColor* NSColor_colorWithSRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha) {
	return [NSColor colorWithSRGBRed:(red) green:(green) blue:(blue) alpha:(alpha)];
}
/* */
NSColor* NSColor_keyboardFocusIndicatorColor() {
	return [NSColor keyboardFocusIndicatorColor];
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
/* */
NSImage* NSImage_initWithData(unsigned char* bitmapData, NSUInteger length) {
    return [[NSImage alloc] initWithData:([NSData dataWithBytes:(bitmapData) length:(length)])];
}