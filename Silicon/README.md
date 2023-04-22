# Silicon
An alternative, pure C-focused wrapper to Apple's Cocoa API for OS X app development. Requires little to no Objective-C knowledge to use.


# Why Silicon?
Because there isn't anything else like it (to my knowledge, at least). If you want to create low-level MacOS apps, you have to use and learn Objective-C, and as we all know the language is notorious for its syntax and its unique (albeit terrible) way of handling object-oriented programming. It also ruins cross-platform code as if you compile an Objective-C file as C, you get a bunch of errors (however there are at least easy work around that).

A lot of people say to "just use swift" instead of Objective-C. While Swift provides a better syntax than whatever Objective-C has, not only the other 2 problems still shine but even more problem arise from this. Swift, much like Objective-C, is still only really used for Apple development and nothing else. It's not really worth learning an even more different language to create low-level applications (and personally speaking I don't really care for Swift).

Apart from Objective-C/Swift, you can only use libraries to make applications. However they only provide very high-level abstraction and might include unneeded bloat, which is just terrible for low-level programming. There is also [hidefromkgb's mac_load](https://github.com/hidefromkgb/mac_load), which allows for actual Mac development on C. While I do like the project (and have used its source in this project), I really do not like the syntax and general way of using the library, as not only is it a bit ugly, but also still feels too much like Objective-C (like how you need define your own classes and what not). It's also not being maintained anymore.

Silicon provides a full C functional-oriented programming wrapper over Cocoa for those low-level programmers in need, as well as anyone that doesn't really want to learn Objective-C or Swift. This library provides functions, types, macros, enums, etc from the Cocoa API and translates to make C-syntax friendly library, as well as other features to make Mac OS development a bit more easier.


# Full discloser
As with any new project, Silicon is subjected to major changes (be it the source code or header) and as such massive old code changes should be expected.

Silicon is also very unfinished as an implementation of a giant library like Cocoa will take awhile. As of now Silicon will firstly focus on implementing the Cocoa essentials as well as common code examples and functions used in the API.


# Silicon on iOS (Beta)
As of Aprill 11th, it's possible to compile basic C code easily with Silicon's `Makefile`. While GUI support isn't nowhere near implemented, it's already possible to print something in the terminal with the [print.c](examples/iphone/print.c) example.

## Prerequisites
- Xcode:
    - iOS SDK.
    - iOS simulator.
- Silicon's `Makefile`.
- Setting said `Makefile`'s `TARGET_iOS` to true at line 6.

## Building
To build, install and launch the app all at once, you'll have to run the command `make iosBuild`. This'll first compile the source file, then generate an `.app` for it, install it on the currently opened iOS simulator and launch it with a console terminal.

## Other noteworthy things to mention
If you want to set the icon, you have to either run `make iosBuild ICON=<filename>.png`, or `make generateApp ICON=<filename>.png` to only generate the app with the icon.

If you only want to install or launch the app, then you can use the command `make iosInstall` and `make iosLaunch` respectively.


# Examples
To compile and run all of the examples in a row, you can use `make runExamples` to test out everything at once.
## [General](examples/general)
- [hello-world.c](examples/general/hello-world.c) - a simple application with a "Hello world" text field.
- [events.c](examples/general/events.c) - shows the use of the NSEvent type to get the required events.
- [mac-load.c](examples/general/mac-load.c) - a Silicon port of [hidefromkgb's original Obj-C/C example](https://github.com/hidefromkgb/mac_load#objective-c-gui-app-example)

## [Controls](examples/controls)
- [menu.c](examples/controls/menu.c) - shows how to create menu bars in OS X.
- [button.c](examples/controls/button.c) - shows how to create and utilize buttons using the Cocoa API.
- [checkbox.c](examples/controls/checkbox.c) - similar to the previous example from above, however instead they're checkboxes instead of regular buttons.
- [combobox.c](examples/controls/combobox.c) - shows an example on how to utilize the NSComboBox class.
- [trackbar.c](examples/controls/trackbar.c) - shows how to create & utilize a track bar and progress bar.

## [Dialogs](examples/dialogs)
- [save-file.c](examples/dialogs/save-file.c) - shows how to create a SaveFileDialog.

## [Graphics](examples/graphics)
- [opengl.c](examples/graphics/opengl.c) - shows how to setup an OpenGL environment with an event loop.

## [iPhone (Beta)](examples/iphone)
- [print.c](examples/graphics/opengl.c) - shows how to enable print debugging on iOS.


# Documentation
## Prerequisites
[todo]

# Class shenanigans
[todo]

## General tips
[todo]


# Credits
## General
- [hidefromkgb's 'mac_load' repository](https://github.com/hidefromkgb/mac_load#objective-c-gui-app-example) - the backend for some of the important parts of Silicon (such as defining Objective-C types and functions).
- Apple - all of the headers from [include/Silicon/headers](include/Silicon/headers/) have been directly copied and modified to not have any Objective-C shenanigans in them for them to be compiled in C.

## The example sources
All of the repositories that I took examples from and eithered completely ported to Silicon or modified heavilly:
- [Gammasoft's 'Cocoa Examples' repository](https://github.com/gammasoft71/Examples_Cocoa/)
- [hidefromkgb's 'mac_load' repository](https://github.com/hidefromkgb/mac_load)