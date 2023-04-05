#define GL_SILENCE_DEPRECATION
#include <Silicon/silicon.h>
#include <OpenGL/gl.h>


CVReturn displayCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *inNow, const CVTimeStamp *inOutputTime, CVOptionFlags flagsIn, CVOptionFlags *flagsOut, void *displayLinkContext) { return kCVReturnSuccess; }

bool is_running = true;

bool OnClose(void* self)  {
	is_running = false;
	return true;
}


int main() {
	funcs[0] = OnClose;

	NSWindow* win = NSWindow_init(NSMakeRect(100, 100, 512, 512), NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable, NSBackingStoreBuffered, false);
	NSWindow_setTitle(win, "trolleybus");

	NSOpenGLPixelFormatAttribute attributes[] = {
		NSOpenGLPFANoRecovery,
		NSOpenGLPFAAccelerated,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAColorSize, 24,
		NSOpenGLPFAAlphaSize, 8,
		NSOpenGLPFADepthSize, 24,
		NSOpenGLPFAStencilSize, 8,
		0
	};
	CVDisplayLinkRef displayLink;
	NSOpenGLPixelFormat* format = NSOpenGLPixelFormat_initWithAttributes(attributes);
	NSOpenGLView* view = NSOpenGLView_initWithFrame(NSMakeRect(0, 0, 512, 512), format);
	NSOpenGLView_prepareOpenGL(view);


	GLint swapInt = 1;
	NSOpenGLContext* context = NSOpenGLView_openGLContext(view);
	NSOpenGLContext_setValues(context, &swapInt, NSOpenGLContextParameterSwapInterval);

	CGDirectDisplayID displayID = CGMainDisplayID();
	CVDisplayLinkCreateWithCGDisplay(displayID, &displayLink);
	CVDisplayLinkSetOutputCallback(displayLink, displayCallback, win);
	CVDisplayLinkStart(displayLink);

	NSOpenGLContext_makeCurrentContext(context);
	NSWindow_setContentView(win, (NSView*)view);
	NSWindow_setIsVisible(win, true);
	NSWindow_makeMainWindow(win);

	NSApplication_sharedApplication();
	NSApp_setActivationPolicy(NSApplicationActivationPolicyRegular);
	NSApp_finishLaunching();

	while (is_running) {
		NSEvent* e = NSApp_nextEventMatchingMask(NSEventMaskAny, NSDate_distantFuture(), 0, true);

		NSApp_sendEvent(e);
		NSApp_updateWindows();

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		NSOpenGLContext_makeCurrentContext(context);
		NSOpenGLContext_flushBuffer(context);
	}

	CVDisplayLinkStop(displayLink);
	CVDisplayLinkRelease(displayLink);
	NSView_release((NSView*)view);
	NSApp_terminate((id)win);


	return 0;
}