/*
	Based on: https://github.com/gammasoft71/Examples_Cocoa/blob/master/src/Applications/ApplicationWithMessageLoop/README.md
*/
#include <Silicon/silicon.h>

const char* NSEventTypeToChar(NSEventType eventType);
const char* NSEventModifierFlagsToChar(NSEventModifierFlags modifierFlags);

int main(int argc, char* argv[]) {
	NSWindow* window1 = NSWindow_init(NSMakeRect(100, 100, 300, 300), NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable, NSBackingStoreBuffered, false);
	NSWindow_setIsVisible(window1, true);

	NSApplication_sharedApplication();
	NSApp_setActivationPolicy(NSApplicationActivationPolicyRegular);
	NSApp_finishLaunching();

	while (true) {
		NSEvent* event = NSApp_nextEventMatchingMask(NSEventMaskAny, NSDate_distantFuture(), 0, true);

		printf("Event [type=%s location={%f, %f} modifierFlags={%s}]\n", NSEventTypeToChar(NSEvent_type(event)), NSEvent_locationInWindow(event).x, NSEvent_locationInWindow(event).y, NSEventModifierFlagsToChar(NSEvent_modifierFlags(event)));
		NSApp_sendEvent(event);
		NSApp_updateWindows();
  	}
}

const char* NSEventTypeToChar(NSEventType eventType) {
  	switch (eventType) {
		case NSEventTypeLeftMouseDown: return "LeftMouseDown";
		case NSEventTypeLeftMouseUp: return "LeftMouseUp";
		case NSEventTypeRightMouseDown: return "RightMouseDown";
		case NSEventTypeRightMouseUp: return "RightMouseUp";
		case NSEventTypeMouseMoved: return "MouseMoved";
		case NSEventTypeLeftMouseDragged: return "LeftMouseDragged";
		case NSEventTypeRightMouseDragged: return "RightMouseDragged";
		case NSEventTypeMouseEntered: return "MouseEntered";
		case NSEventTypeMouseExited: return "MouseExited";
		case NSEventTypeKeyDown: return "KeyDown";
		case NSEventTypeKeyUp: return "KeyUp";
		case NSEventTypeFlagsChanged: return "FlagsChanged";
		case NSEventTypeAppKitDefined: return "AppKitDefined";
		case NSEventTypeSystemDefined: return "SystemDefined";
		case NSEventTypeApplicationDefined: return "ApplicationDefined";
		case NSEventTypePeriodic: return "Periodic";
		case NSEventTypeCursorUpdate: return "CursorUpdate";
		case NSEventTypeScrollWheel: return "ScrollWheel";
		case NSEventTypeTabletPoint: return "TabletPoint";
		case NSEventTypeTabletProximity: return "TabletProximity";
		case NSEventTypeOtherMouseDown: return "OtherMouseDown";
		case NSEventTypeOtherMouseUp: return "OtherMouseUp";
		case NSEventTypeOtherMouseDragged: return "OtherMouseDragged";
		default: return "N/A";
 	}
}

const char* NSEventModifierFlagsToChar(NSEventModifierFlags modifierFlags) {
	static char result[100];
	if ((modifierFlags & NSEventModifierFlagCapsLock) == NSEventModifierFlagCapsLock) strcat(result, "CapsLock, ");
	if ((modifierFlags & NSEventModifierFlagShift) == NSEventModifierFlagShift) strcat(result, "NShift, ");
	if ((modifierFlags & NSEventModifierFlagControl) == NSEventModifierFlagControl) strcat(result, "Control, ");
	if ((modifierFlags & NSEventModifierFlagOption) == NSEventModifierFlagOption) strcat(result, "Option, ");
	if ((modifierFlags & NSEventModifierFlagCommand) == NSEventModifierFlagCommand) strcat(result, "Command, ");
	if ((modifierFlags & NSEventModifierFlagNumericPad) == NSEventModifierFlagNumericPad) strcat(result, "NumericPad, ");
	if ((modifierFlags & NSEventModifierFlagHelp) == NSEventModifierFlagHelp) strcat(result, "Help, ");
	if ((modifierFlags & NSEventModifierFlagFunction) == NSEventModifierFlagFunction) strcat(result, "Function, ");

	return result;
}