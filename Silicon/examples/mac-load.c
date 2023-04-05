#include <Silicon/silicon.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void OnRect(void *self, NSRect rect) {
	NSColor* color = NSColor_keyboardFocusIndicatorColor();
	NSColor_set(color);

	const int n = 12;
	for (double f = 0; f < 2 * M_PI; f += 2 * M_PI / n) {
		for (double g = 0; g < 2 * M_PI; g += 2 * M_PI / n) {
			NSPoint begin = {(sin(f) + 1) * rect.size.width * 0.5,
								 (cos(f) + 1) * rect.size.height * 0.5};
			NSPoint end = {(sin(g) + 1) * rect.size.width * 0.5,
							  (cos(g) + 1) * rect.size.height * 0.5};
			NSBezierPath_strokeLine(begin, end);
		}
	}
}


bool OnClose(void *self, NSNotification *notification)  {
	NSApplication* sharedApplication = NSApplication_sharedApplication();
	NSApplication_stop(sharedApplication, self);

	return true;
}


int main() {
	funcs[0] = OnClose;
	funcs[1] = OnRect;
	NSAutoreleasePool* myPool = malloc_class(NSAutoreleasePool);

	NSRect rect = {{100.0, 350.0}, {400.0, 400.0}};
	NSInteger mask = NSTitledWindowMask | NSClosableWindowMask
				   | NSMiniaturizableWindowMask;
	NSWindow* myWnd = NSWindow_init(rect, mask, NSBackingStoreBuffered, false);
	NSWindow_setTitle(myWnd, "ObjC Application Window");

	NSView* myView = NSView_init();
	NSWindow_setContentView(myWnd, myView);
	NSWindow_setDelegate(myWnd, myView);
	NSWindow_orderFront(myWnd, nil);
	NSWindow_makeKeyWindow(myWnd);

	NSApplication_run(NSApplication_sharedApplication());
	release(myPool);

	return 0;
}