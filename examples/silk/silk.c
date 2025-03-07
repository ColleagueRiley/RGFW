
#define SILK_PIXELBUFFER_WIDTH 500
#define SILK_PIXELBUFFER_HEIGHT 500
#define SILK_IMPLEMENTATION
#include "silk.h"

#include <stdint.h>
#include <stddef.h>

typedef int8_t      i8;
typedef uint16_t   u16;
typedef int16_t    i16;
typedef uint64_t   u64;
typedef int64_t    i64;


#define u8 u8
#define RGFW_IMPLEMENTATION
#define RGFW_BUFFER

#include "RGFW.h"

int main(void) {
    RGFW_window* win = RGFW_createWindow("Basic buffer example", RGFW_RECT(0, 0, 500, 500), RGFW_windowCenter | RGFW_windowTransparent | RGFW_windowNoResize);
    RGFW_window_initBufferSize(win, RGFW_AREA(500, 500));

    u32 angle = 0;
    u32 frames = 0;
    double frameStartTime = RGFW_getTime();

    i8 running = 1;
    while (running) {
        while (RGFW_window_checkEvent(win)) {
            if (win->event.type == RGFW_quit || RGFW_isPressed(win, RGFW_escape)) {
                running = 0;
                break;
            }   
        } 
        
        silkClearPixelBufferColor((pixel*)win->buffer, 0x11AA0033);

        silkDrawStar(
            (pixel*)win->buffer, 
            (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
            SILK_PIXELBUFFER_WIDTH,
            (vec2i) { (win->r.w / 2), SILK_PIXELBUFFER_CENTER_Y - 60}, 
            60,
            angle,
            5,
            0xff0000ff
        );

        const char* text = "Hello, RGFW!";
        const size_t text_size = 8;
        const i32 text_spacing = 1;

        silkDrawTextDefault(
            (pixel*)win->buffer, 
            (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
            SILK_PIXELBUFFER_WIDTH,
            text, 
            (vec2i) { 
                win->r.w / 2 - silkMeasureText(text, text_size, text_spacing).x / 2, 
                win->r.h / 2 - silkMeasureText(text, text_size, text_spacing).y / 2 + win->r.h / 4 
            }, 
            text_size, 
            text_spacing,
            0xff000000
        );
        
        angle++;

        RGFW_window_swapBuffers(win);
		RGFW_checkFPS(frameStartTime, frames, 60);
        frames++;
    }

    RGFW_window_close(win);
}
