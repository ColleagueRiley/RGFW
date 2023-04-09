/*
	Based on: https://github.com/gammasoft71/Examples_Cocoa/blob/master/src/CommonControls/Button/README.md
*/

#include <Silicon/silicon.h>


NSButton* button1;
NSButton* button2;
NSTextField* label1;
NSTextField* label2;
int button1Clicked;
int button2Clicked;

// Buffer for our text.
static char buffer[30];


bool windowShouldClose(id sender) {
	NSApplication_terminate(NSApp, sender);
	return YES;
}

void OnButton1Click(id sender) {
	sprintf(buffer, "button1 clicked %d times", ++button1Clicked);
	NSTextField_setStringValue(label1, buffer);
}

void OnButton2Click(id sender) {
	sprintf(buffer, "button2 clicked %d times", ++button2Clicked);
	NSTextField_setStringValue(label2, buffer);
}


int main(int argc, char* argv[]) {
	func_to_SEL(OnButton1Click);
	func_to_SEL(OnButton2Click);

	funcs[0] = windowShouldClose;

	NSApplication_sharedApplication();
	NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);

	NSWindow* window = NSWindow_init(NSMakeRect(100, 100, 300, 300), NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable, NSBackingStoreBuffered, false);

	button1Clicked = 0;
	button2Clicked = 0;


	button1 = NSButton_initWithFrame(NSMakeRect(50, 225, 90, 25)); // [[[NSButton alloc] initWithFrame:NSMakeRect(50, 225, 90, 25)] autorelease];
	NSButton_setTitle(button1, "button1");
	NSButton_setBezelStyle(button1, NSBezelStyleRounded);
	NSButton_setTarget(button1, (id)window);
	NSButton_setAction(button1, selector(OnButton1Click));
	NSButton_setAutoresizingMask(button1, NSViewMaxXMargin | NSViewMinYMargin);

	button2 = NSButton_initWithFrame(NSMakeRect(50, 125, 200, 75));
	NSButton_setTitle(button2, "button2");
	NSButton_setBezelStyle(button2, NSBezelStyleRegularSquare);
	NSButton_setTarget(button2, (id)window);
	NSButton_setAction(button2, selector(OnButton2Click));
	NSButton_setAutoresizingMask(button2, NSViewMaxXMargin | NSViewMinYMargin);

	label1 = NSTextField_initWithFrame(NSMakeRect(50, 80, 150, 20));
	NSTextField_setStringValue(label1, "button1 clicked 0 times");
	NSTextField_setBezeled(label1, false);
	NSTextField_setDrawsBackground(label1, false);
	NSTextField_setEditable(label1, false);

  	label2 = NSTextField_initWithFrame(NSMakeRect(50, 50, 150, 20));
	NSTextField_setStringValue(label2, "button2 clicked 0 times");
	NSTextField_setBezeled(label2, false);
	NSTextField_setDrawsBackground(label2, false);
	NSTextField_setEditable(label2, false);


	NSWindow_setTitle(window, "Button example");
	NSView* view = NSWindow_contentView(window);
	NSView_addSubview(view, (NSView*)button1);
	NSView_addSubview(view, (NSView*)button2);
	NSView_addSubview(view, (NSView*)label1);
	NSView_addSubview(view, (NSView*)label2);
	NSWindow_setIsVisible(window, true);
	NSWindow_makeMainWindow(window);

	NSApplication_run(NSApp);

	return 0;
}