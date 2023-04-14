# The display and executable names for your app.
NAME = iHateSociety
EXE = society

# Either 'true' or 'false'. Setting the target is important for a multitude of reasons.
TARGET_iOS=false

# Building the source file configurations. Customize it to your likings
SRC = main.c
FLAGS = -O2 -std=c99 -I"include"
LIBS =-lSilicon -framework AppKit -framework Foundation -framework OpenGL -framework CoreVideo

# Change what compiler and output folder will be. Usually you don't need to change anything here.
CC = clang
OUTPUT_DIR = build

ifeq ($(TARGET_iOS),true)
CC += -isysroot $(shell xcrun --sdk iphonesimulator --show-sdk-path)
endif

# Building variables for `libSilicon.a`. If you're building `libSilicon.a`, do not change anything unless you understand what's going on.
SILICON_LIB_SRC = $(basename $(wildcard source/*.m))
SILICON_LIB_OBJ = $(addprefix $(OUTPUT_DIR)/,$(addsuffix .o,$(notdir $(SILICON_LIB_SRC))))
SILICON_LIB = $(OUTPUT_DIR)/libSilicon.a
OUTPUT_EXE = $(OUTPUT_DIR)/$(EXE)


# Compiles libSilicon.a, compiles main.c and runs it.
all: $(OUTPUT_DIR) $(SILICON_LIB) $(OUTPUT_EXE) run

run:
	./$(OUTPUT_EXE)

# Cleans the built files.
clean:
	rm $(SILICON_LIB) $(OUTPUT_EXE) $(SILICON_LIB_OBJ)

# Compiles main.c
$(OUTPUT_EXE): $(SRC)
	$(CC) $(FLAGS) -L"$(OUTPUT_DIR)" $(INCLUDE) $(SRC) $(LIBS) -o $@

# Combines all of the object files into one static library.
$(SILICON_LIB): $(SILICON_LIB_OBJ)
	$(AR) -rcs $@ $^

# Compiles all Objective-C files to object files.
$(OUTPUT_DIR)/%.o: source/%.m
	$(CC) $(FLAGS) $(INCLUDE) $^ -c -o $@

# Creates the build directory if it doesn't exist.
$(OUTPUT_DIR):
	mkdir $(OUTPUT_DIR)


# Runs and compiles every example.
runExamples:
	@for f in $(shell ls examples/**/*.c); do make SRC=$${f}; rm -rf $(OUTPUT_EXE); done

# Installs Silicon on the Mac.
install: $(SILICON_LIB)
	sudo cp -r include/Silicon /usr/local/include/Silicon
	sudo cp -r $(SILICON_LIB) /usr/local/lib/libSilicon.a

# Uninstalls Silicon (if it's even installed in the first place).
uninstall: /usr/local/include/Silicon /usr/local/lib/libSilicon.a
	sudo rm -rf $^


# App generator settings. Apart from ICON, you shouldn't change anything.
ICON=

# Changes depending on the targetted platform.
APP_ROOT_PATH=$(NAME).app/Contents
APP_EXE_PATH=/MacOS
APP_RES_PATH=/Resources

generateApp:
# Ignoring Makefile's stupid tab rules, for some reason one very apple device there are different paths for everything.
# Info.plist on MacOS has to be in `Contents`, while everywhere else it doesn't require that. Why does that exist? No clue and it bothers to me no avail.
ifeq ($(TARGET_iOS),true)
	$(eval APP_ROOT_PATH=$(NAME).app)
	$(eval APP_EXE_PATH=)
	$(eval APP_RES_PATH=)
endif
	@rm -rf $(NAME).app
	mkdir -p $(NAME).app $(APP_ROOT_PATH)/$(APP_EXE_PATH) $(APP_ROOT_PATH)$(APP_RES_PATH)
	cp $(OUTPUT_EXE) $(APP_ROOT_PATH)$(APP_EXE_PATH)/$(EXE)

ifeq ($(ICON),) # Makefile is STILL dum with tabs.
else
	sips -z 512 512   $(ICON) --out $(APP_ROOT_PATH)$(APP_RES_PATH)/app.png

#	@mkdir -p "app.iconset"
#	sips -z 512 512   $(ICON) --out app.iconset/icon_512x512.png
#	iconutil -c icns -o $(APP_ROOT_PATH)$(APP_RES_PATH)/app.icns app.iconset
#	@rm -rf app.iconset
endif
	printf '\
	<?xml version="1.0" encoding="UTF-8"?>									\n\
	<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">	\n\
	<plist version="1.0">											\n\
	<dict>													\n\
		<key>CFBundleName</key>										\n\
		<string>$(NAME)</string>									\n\
														\n\
		<key>CFBundleDisplayName</key>									\n\
		<string>$(NAME)</string>									\n\
														\n\
		<key>CFBundleExecutable</key>									\n\
		<string>$(EXE)</string>										\n\
														\n\
		<key>CFBundleIdentifier</key>									\n\
		<string>com.$(EXE).silicon</string>								\n\
														\n\
		<key>CFBundleShortVersionString</key>								\n\
		<string>1.0.0</string>										\n\
														\n\
		<key>CFBundleVersion</key>									\n\
		<string>1</string>										\n\
														\n\
		<key>CFBundleIconFile</key>									\n\
		<string>app</string>										\n\
														\n\
		<key>LSRequiresIPhoneOS</key>									\n\
		<$(TARGET_iOS)/>										\n\
	</dict>													\n\
	</plist>' > $(APP_ROOT_PATH)/Info.plist

	touch $(NAME).app


# ==================== iOS build system (beta) ====================
#	"Vardan Dievo Tėvo, ir Sūnaus, ir Šventosios Dvasios. Amen."
#		- Me after a day of trying to out figure how iOS development works.
#
# This build system assumes you'll be using Xcode's iOS simulator for testing.
# Make sure to pick the iPhone model of your choice for the simulator before compiling, as this code will
# use the most recently opened simulator model when installing and lauching the app.
#
#
# Commands:
# iosBuild - compiles the app, auto generates the .app, installs it on the simulator and launches it with a debug terminal.
# iosInstall - installs the .app on the simulator.
# iosRun - launches the installed app and opens up a debug terminal.
#
# ===============================================================
iosBuild: $(BACKEND) $(SRC)
	$(CC) -I"include" -framework Foundation -framework UIKit -framework CoreGraphics $(SRC) -o $(OUTPUT_EXE)
	make generateApp
	open -a simulator.app

	make iosInstall
	make iosRun

iosInstall: $(NAME).app
	xcrun simctl install booted $(NAME).app

iosRun: $(NAME).app
	xcrun simctl launch booted "com.$(EXE).silicon"
	xcrun simctl spawn booted log stream --predicate 'subsystem == "com.$(EXE).silicon"'
