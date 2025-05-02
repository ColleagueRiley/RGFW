/*
 * Mesa 3-D graphics library
 * Version:  6.5
 *
 * Copyright (C) 1999-2006  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


/*
 * This file manages the OpenGL API dispatch layer.
 * The dispatch table (struct _glapi_table) is basically just a list
 * of function pointers.
 * There are functions to set/get the current dispatch table for the
 * current thread and to manage registration/dispatch of dynamically
 * added extension functions.
 *
 * NOTE: There are no dependencies on Mesa in this code.
 *
 * Versions (API changes):
 *   2000/02/23  - original version for Mesa 3.3 and XFree86 4.0
 *   2001/01/16  - added dispatch override feature for Mesa 3.5
 *   2002/06/28  - added _glapi_set_warning_func(), Mesa 4.1.
 *   2002/10/01  - _glapi_get_proc_address() will now generate new entrypoints
 *                 itself (using offset ~0).  _glapi_add_entrypoint() can be
 *                 called afterward and it'll fill in the correct dispatch
 *                 offset.  This allows DRI libGL to avoid probing for DRI
 *                 drivers!  No changes to the public glapi interface.
 */



#include "glheader.h"
#include "glapi.h"
#include "glapioffsets.h"
#include "glapitable.h"
#include "glthread.h"

/***** BEGIN NO-OP DISPATCH *****/

static GLboolean WarnFlag = GL_FALSE;
static _glapi_warning_func warning_func;

#if defined(PTHREADS)
static void init_glapi_relocs(void);
#endif

static _glapi_proc generate_entrypoint(GLuint functionOffset);
static void fill_in_entrypoint_offset(_glapi_proc entrypoint, GLuint offset);

/*
 * Enable/disable printing of warning messages.
 */
PUBLIC void
_glapi_noop_enable_warnings(GLboolean enable)
{
    WarnFlag = enable;
}

/*
 * Register a callback function for reporting errors.
 */
PUBLIC void
_glapi_set_warning_func(_glapi_warning_func func)
{
    warning_func = func;
}

static GLboolean
warn(void)
{
    if ((WarnFlag || getenv("MESA_DEBUG") || getenv("LIBGL_DEBUG"))
	&& warning_func) {
	return GL_TRUE;
    } else {
	return GL_FALSE;
    }
}


#define KEYWORD1 static
#define KEYWORD1_ALT static
#define KEYWORD2 GLAPIENTRY
#define NAME(func)  NoOp##func

#define F NULL

#define DISPATCH(func, args, msg)					      \
   if (warn()) {							      \
      warning_func(NULL, "GL User Error: called without context: %s", #func); \
   }

#define RETURN_DISPATCH(func, args, msg)				      \
   if (warn()) {							      \
      warning_func(NULL, "GL User Error: called without context: %s", #func); \
   }									      \
   return 0

#define DISPATCH_TABLE_NAME __glapi_noop_table
#define UNUSED_TABLE_NAME __unused_noop_functions

#define TABLE_ENTRY(name) (_glapi_proc) NoOp##name

static GLint NoOpUnused(void)
{
    if (warn()) {
	warning_func(NULL, "GL User Error: calling extension function without a current context\n");
    }
    return 0;
}

#include "glapitemp.h"

/***** END NO-OP DISPATCH *****/



/**
 * \name Current dispatch and current context control variables
 *
 * Depending on whether or not multithreading is support, and the type of
 * support available, several variables are used to store the current context
 * pointer and the current dispatch table pointer.  In the non-threaded case,
 * the variables \c _glapi_Dispatch and \c _glapi_Context are used for this
 * purpose.
 *
 * In the "normal" threaded case, the variables \c _glapi_Dispatch and
 * \c _glapi_Context will be \c NULL if an application is detected as being
 * multithreaded.  Single-threaded applications will use \c _glapi_Dispatch
 * and \c _glapi_Context just like the case without any threading support.
 * When \c _glapi_Dispatch and \c _glapi_Context are \c NULL, the thread state
 * data \c _gl_DispatchTSD and \c ContextTSD are used.  Drivers and the
 * static dispatch functions access these variables via \c _glapi_get_dispatch
 * and \c _glapi_get_context.
 *
 * There is a race condition in setting \c _glapi_Dispatch to \c NULL.  It is
 * possible for the original thread to be setting it at the same instant a new
 * thread, perhaps running on a different processor, is clearing it.  Because
 * of that, \c ThreadSafe, which can only ever be changed to \c GL_TRUE, is
 * used to determine whether or not the application is multithreaded.
 *
 * In the TLS case, the variables \c _glapi_Dispatch and \c _glapi_Context are
 * hardcoded to \c NULL.  Instead the TLS variables \c _glapi_tls_Dispatch and
 * \c _glapi_tls_Context are used.  Having \c _glapi_Dispatch and
 * \c _glapi_Context be hardcoded to \c NULL maintains binary compatability
 * between TLS enabled loaders and non-TLS DRI drivers.
 */
/*@{*/

#if defined(THREADS)

static GLboolean ThreadSafe = GL_FALSE;  /**< In thread-safe mode? */
_glthread_TSD _gl_DispatchTSD;           /**< Per-thread dispatch pointer */
static _glthread_TSD ContextTSD;         /**< Per-thread context pointer */

#endif /* defined(THREADS) */

PUBLIC struct _glapi_table *_glapi_Dispatch =
    (struct _glapi_table *) __glapi_noop_table;
PUBLIC void *_glapi_Context = NULL;

/*@}*/


/**
 * We should call this periodically from a function such as glXMakeCurrent
 * in order to test if multiple threads are being used.
 */
void
_glapi_check_multithread(void)
{
#if defined(THREADS)
    if (!ThreadSafe) {
	static unsigned long knownID;
	static GLboolean firstCall = GL_TRUE;
	if (firstCall) {
	    knownID = _glthread_GetID();
	    firstCall = GL_FALSE;
	} else if (knownID != _glthread_GetID()) {
	    ThreadSafe = GL_TRUE;
	    _glapi_set_dispatch(NULL);
	    _glapi_set_context(NULL);
	}
    } else if (!_glapi_get_dispatch()) {
	/* make sure that this thread's dispatch pointer isn't null */
	_glapi_set_dispatch(NULL);
    }
#endif
}



/**
 * Set the current context pointer for this thread.
 * The context pointer is an opaque type which should be cast to
 * void from the real context pointer type.
 */
PUBLIC void
_glapi_set_context(void *context)
{
    (void) __unused_noop_functions; /* silence a warning */
#if   defined(THREADS)
    _glthread_SetTSD(&ContextTSD, context);
    _glapi_Context = (ThreadSafe) ? NULL : context;
#else
    _glapi_Context = context;
#endif
}



/**
 * Get the current context pointer for this thread.
 * The context pointer is an opaque type which should be cast from
 * void to the real context pointer type.
 */
PUBLIC void *
_glapi_get_context(void)
{
#if   defined(THREADS)
    if (ThreadSafe) {
	return _glthread_GetTSD(&ContextTSD);
    } else {
	return _glapi_Context;
    }
#else
    return _glapi_Context;
#endif
}



/**
 * Set the global or per-thread dispatch table pointer.
 * If the dispatch parameter is NULL we'll plug in the no-op dispatch
 * table (__glapi_noop_table).
 */
PUBLIC void
_glapi_set_dispatch(struct _glapi_table *dispatch)
{
#if defined(PTHREADS)
    static pthread_once_t once_control = PTHREAD_ONCE_INIT;
    pthread_once(& once_control, init_glapi_relocs);
#endif

    if (!dispatch) {
	/* use the no-op functions */
	dispatch = (struct _glapi_table *) __glapi_noop_table;
    }

#if   defined(THREADS)
    _glthread_SetTSD(&_gl_DispatchTSD, (void *) dispatch);
    _glapi_Dispatch = (ThreadSafe) ? NULL : dispatch;
#else /*THREADS*/
    _glapi_Dispatch = dispatch;
#endif /*THREADS*/
}



/**
 * Return pointer to current dispatch table for calling thread.
 */
PUBLIC struct _glapi_table *
_glapi_get_dispatch(void)
{
    struct _glapi_table * api;
#if   defined(THREADS)
    api = (ThreadSafe)
	  ? (struct _glapi_table *) _glthread_GetTSD(&_gl_DispatchTSD)
	  : _glapi_Dispatch;
#else
    api = _glapi_Dispatch;
#endif
    return api;
}

#if defined(PTHREADS)
/**
 * Perform platform-specific GL API entry-point fixups.
 */
static void
init_glapi_relocs(void)
{
}
#endif /* defined(PTHREADS) */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
