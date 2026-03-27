/*
*
*	rtime 0.1.0

	Riley Mabb (ColleagueRiley)
	
	public domain

    This is free and unencumbered software released into the public domain.
    Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
    software, either in source code form or as a compiled binary, for any purpose,
    commercial or non-commercial, and by any means.
    In jurisdictions that recognize copyright laws, the author or authors of this
    software dedicate any and all copyright interest in the software to the public
    domain. We make this dedication for the benefit of the public at large and to
    the detriment of our heirs and successors. We intend this dedication to be an
    overt act of relinquishment in perpetuity of all present and future rights to
    this software under copyright law.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
    ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*
*/

/*
	(MAKE SURE RT_IMPLEMENTATION is in exactly one header or you use -D RT_IMPLEMENTATION)
	#define RT_IMPLEMENTATION - makes it so source code is included with header
*/

/*
	#define RT_IMPLEMENTATION - (required) makes it so the source code is included

	#define RT_EXPORT - use when building RTIME
	#define RT_IMPORT - use when linking with RTIME (not as a single-header)
*/

#if defined(RT_EXPORT) ||  defined(RT_IMPORT)
	#if defined(_WIN32)
		#if defined(__TINYC__) && (defined(RT_EXPORT) ||  defined(RT_IMPORT))
			#define __declspec(x) __attribute__((x))
		#endif

		#if defined(RT_EXPORT)
			#define RT_API __declspec(dllexport)
		#else
			#define RT_API __declspec(dllimport)
		#endif
	#else
		#if defined(RT_EXPORT)
			#define RT_API __attribute__((visibility("default")))
		#endif
	#endif
    #ifndef RT_API
        #define RT_API
    #endif
#endif

#ifndef RT_API
	#define RT_API inline
#endif

#ifdef __EMSCRIPTEN__
	#define RT_WASM
#endif

#if defined(_WIN32) && !defined(RT_UNIX) && !defined(RT_WASM)
	#define RT_WINDOWS
#elif !defined(RT_UNIX) && defined(__unix__)  && !defined(RT_WASM) && !defined(__APPLE__)
	#define RT_UNIX
#elif defined(__APPLE__) && !defined(RT_UNIX)  && !defined(RT_WASM)
	#define RT_MACOS
#endif

#if defined(__cplusplus) && !defined(__EMSCRIPTEN__)
	extern "C" {
#endif

/* makes sure the header file part is only defined once by default */
#ifndef RT_HEADER

#define RT_HEADER

#include <stdint.h>

/**!
 * @brief Set starting time for getTime to use
 * @return the time in seconds
*/
RT_API void rt_setTime(double time); /*!< set timer in seconds */

/**!
 * @brief Retrieves delta time between the setTime value and the current time in seconds
 * @return the time in seconds
*/
RT_API double rt_getTime(void);

/**!
 * @brief Retrieves delta time between the setTime value and the current time in nanoseconds
 * @return the time in nanosecnds
*/
RT_API uint64_t rt_getTimeNS(void);

/**!
 * @brief sleep, pausing the thread for a given amount of time
 * @return time length of the pause in miliseconds
*/
RT_API void rt_sleep(uint64_t milisecond);

/**!
 * @brief Retrieves get source API timer value.
 * @return The source API timer value.
*/
RT_API uint64_t rt_getTimerValue(void);

/**!
 * @brief Retrieves the source api time frequency
 * @return The source API timer frequency.
*/
RT_API uint64_t rt_getTimerFreq(void);

#endif

#ifdef RT_IMPLEMENTATION

#ifdef RT_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#define OEMRESOURCE
	#include <windows.h>
#elif defined(RT_WASM)
	#include <emscripten/html5.h>
#else
	#include <time.h>
#endif

#ifdef RT_MACOS
	#include <mach/mach_time.h>
#endif

uint64_t rt_timerOffset = 0;
void rt_setTime(double time) {
    rt_timerOffset = rt_getTimerValue() - (uint64_t)(time * (double)rt_getTimerFreq());
}

double rt_getTime(void) {
	return (double) ((double)(rt_getTimerValue() - rt_timerOffset) / (double)rt_getTimerFreq());
}

uint64_t rt_getTimeNS(void) {
	return (uint64_t)(((double)((rt_getTimerValue() - rt_timerOffset)) * 1e9) / (double)rt_getTimerFreq());
}

void rt_sleep(uint64_t ms) {
#ifdef RT_WINDOWS
	Sleep((uint32_t)ms);
#elif defined(RT_WASM)
	emscripten_sleep(ms);
#else
	struct timespec time;
	time.tv_sec = 0;
	time.tv_nsec = (long int)((double)ms * 1e+6);

	nanosleep(&time, NULL);
#endif
}

uint64_t rt_getTimerFreq(void) {
#ifdef RT_WINDOWS
	static uint64_t frequency = 0;
	if (frequency == 0) QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	return frequency;
#elif defined(RT_WASM)
	return (uint64_t)1000;
#elif defined(RT_MACOS)
	static uint64_t freq = 0;
	if (freq == 0) {
		mach_timebase_info_data_t info;
		mach_timebase_info(&info);
		freq = (uint64_t)((info.denom * 1e9) / info.numer);
	}

	return freq;
#else
	return 1000000000LLU;
#endif
}

uint64_t rt_getTimerValue(void) {
#ifdef RT_WINDOWS
	uint64_t value;
	QueryPerformanceCounter((LARGE_INTEGER*)&value);
	return value;
#elif defined(RT_WASM)
	return emscripten_get_now() * 1e+6;
#elif defined(RT_MACOS)
	return (uint64_t)mach_absolute_time();
#else
	static int32_t clock = -1;
	if (clock == -1) {
		#if defined(_POSIX_MONOTONIC_CLOCK)
		struct timespec ts;
		if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
			clock = CLOCK_MONOTONIC;
		#else
			clock = CLOCK_REALTIME;
		#endif
	}

	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
    return (uint64_t)ts.tv_sec * rt_getTimerFreq() + (uint64_t)ts.tv_nsec;
#endif
}

#endif /* RT_IMPLEMENTATION */

#if defined(__cplusplus) && !defined(__EMSCRIPTEN__)
}
#endif

