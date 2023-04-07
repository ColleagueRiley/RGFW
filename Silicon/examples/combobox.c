/*
	Based on: https://github.com/gammasoft71/Examples_Cocoa/blob/master/src/CommonControls/ComboBox/README.md
*/

#include <Silicon/silicon.h>

// The main variables for our example.
NSComboBox* comboBox1;
NSComboBox* comboBox2;


// Call this function each time the comboxBox's text field gets changed.
void OnComboBox1SelectedItemChange(id sender) {
	NSComboBox_selectItem(comboBox2, NSComboBox_indexOfSelectedItem(comboBox1));
}

// Standard close function.
bool windowShouldClose(id sender) {
	NSApplication_terminate(NSApp, sender);
	return true;
}

int main(int argc, char* argv[]) {
	funcs[0] = windowShouldClose;

	// Convert functions to C.
	func_to_SEL(OnComboBox1SelectedItemChange);

	NSApplication_sharedApplication();
	NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);

	// Init the window beforehand as we'll have to reference for later.
	NSWindow* window = NSWindow_init(NSMakeRect(100, 100, 300, 300), NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable, NSBackingStoreBuffered, false);
 	NSWindow_setTitle(window, "ComboBox Example");

	// Init our comboBoxes.
	comboBox1 = NSComboBox_init(NSMakeRect(10, 260, 121, 26));
	NSComboBox_addItem(comboBox1, "item1");
	NSComboBox_addItem(comboBox1, "item2");
	NSComboBox_addItem(comboBox1, "item3");
	NSComboBox_setTarget(comboBox1, (id)window);
	NSComboBox_setAction(comboBox1, selector(OnComboBox1SelectedItemChange));

	comboBox2 = NSComboBox_init(NSMakeRect(10, 220, 121, 26));
	NSComboBox_setEditable(comboBox2, false);
	NSComboBox_addItem(comboBox2, "item1");
	NSComboBox_addItem(comboBox2, "item2");
	NSComboBox_addItem(comboBox2, "item3");
	NSComboBox_setTarget(comboBox2, (id)window);

	// Select which item index to show for each comboBox.
	NSComboBox_selectItem(comboBox1, 1);
	NSComboBox_selectItem(comboBox2, 1);

	// Add the comboBoxes to the view.
	NSView* view = NSWindow_contentView(window);
	NSView_addSubview(view, (NSView*)comboBox1);
	NSView_addSubview(view, (NSView*)comboBox2);

	// Set the window visible and main.
	NSWindow_setIsVisible(window, true);
	NSWindow_makeMainWindow(window);

	// Run it.
	NSApplication_run(NSApp);

    return 0;
}