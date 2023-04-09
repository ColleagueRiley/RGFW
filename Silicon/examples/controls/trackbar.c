/*
    Based on: https://github.com/gammasoft71/Examples_Cocoa/blob/master/src/CommonControls/TrackBar/README.md
*/

#include <Silicon/silicon.h>


NSSlider* track_bar;
NSProgressIndicator* progress_bar;
NSTextField* label;


// Each time we move the track bar, the progress bar's value becomes the same as the track bar's
void valueChanged(id sender) {
	static char buffer[11]; // Since a double will have 10 characters and we need to add a NULL at the end, the length of our string buffer becomes 11.
	sprintf(buffer, "%f", NSSlider_doubleValue(track_bar));

	NSProgressIndicator_setDoubleValue(progress_bar, NSSlider_doubleValue(track_bar));
	NSTextField_setStringValue(label, buffer);
}

bool windowShouldClose(id sender) {
	NSApplication_terminate(NSApp, sender);
	return true;
}


int main(int argc, char* argv[]) {
	funcs[0] = windowShouldClose;

	// Convert the C function to an Objective-C method.
	func_to_SEL(valueChanged);

	// Ever since MacOS 10.6, Mac applications require a 'NSApplicationActivationPolicyRegular' type policy to properly show applications on dock.
	NSApplication_sharedApplication();
	NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);

	// Init and configure the track bar.
	track_bar = NSSlider_initWithFrame(NSMakeRect(20, 215, 200, 25));
	NSSlider_setAction(track_bar, selector(valueChanged));
	NSSlider_setMaxValue(track_bar, 200);
	NSSlider_setDoubleValue(track_bar, 100);

	// Init and configure the progress bar.
	progress_bar = NSProgressIndicator_init(NSMakeRect(20, 180, 200, 20));
	NSProgressIndicator_setMaxValue(progress_bar, 200);
	NSProgressIndicator_setIndeterminate(progress_bar, false);
	NSProgressIndicator_setDoubleValue(progress_bar, 100);

	// Init and configure the text.
 	label = NSTextField_initWithFrame(NSMakeRect(20, 130, 100, 20));
	NSTextField_setStringValue(label, "100");
	NSTextField_setBezeled(label, false);
	NSTextField_setDrawsBackground(label, false);
	NSTextField_setEditable(label, false);
	NSTextField_setSelectable(label, false);

 	NSWindow* window = NSWindow_init(NSMakeRect(100, 100, 300, 300), NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable, NSBackingStoreBuffered, NO);
	NSView* view = NSWindow_contentView(window);

	NSWindow_setTitle(window, "TrackBar Example");

	// Add the track bar, progress bar and text.
	NSView_addSubview(view, (NSView*)track_bar);
	NSView_addSubview(view, (NSView*)progress_bar);
	NSView_addSubview(view, (NSView*)label);

	NSWindow_setIsVisible(window, true);
	NSWindow_makeKeyWindow(window);

	// Run it.
	NSApplication_run(NSApp);
}