
/** mac_load: create GUI apps for OS X in pure C; no ObjC knowledge required.
	Original author: hidefromkgb (hidefromkgb@gmail.com)
	_________________________________________________________________________
	This is free and unencumbered software released into the public domain.
	Anyone is free to copy, modify, publish, use, compile, sell, or
	distribute this software, either in source code form or as a compiled
	binary, for any purpose, commercial or non-commercial, and by any means.
	In jurisdictions that recognize copyright laws, the author or authors
	of this software dedicate any and all copyright interest in the
	software to the public domain. We make this dedication for the benefit
	of the public at large and to the detriment of our heirs and
	successors. We intend this dedication to be an overt act of
	relinquishment in perpetuity of all present and future rights to this
	software under copyright law.
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
	OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
	ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
	_________________________________________________________________________
**/

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>

#include <objc/message.h>
#include <objc/runtime.h>
//#include <objc/objc-runtime.h>

// c - concatenator/sequencer; f - function
#define _MAC_L(c, f, ...) c( \
c(c(_MAC_L4(c,f,0,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,__VA_ARGS__),   \
	_MAC_L4(c,f,1,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,        __VA_ARGS__)),  \
  c(_MAC_L4(c,f,2,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,                __VA_ARGS__),   \
	_MAC_L4(c,f,3,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,                        __VA_ARGS__))), \
c(c(_MAC_L4(c,f,4,,,,,,,,,,,,,,,,,,,,,,,,,                                __VA_ARGS__),   \
	_MAC_L4(c,f,5,,,,,,,,,,,,,,,,,                                        __VA_ARGS__)),  \
  c(_MAC_L4(c,f,6,,,,,,,,,                                                __VA_ARGS__),   \
	_MAC_L4(c,f,7,                                                        __VA_ARGS__))))
//               ^1      ^8      ^16     ^24     ^32     ^40     ^48     ^56
#define _MAC_L4(c, f, i, ...) c( \
c(c(_MAC_L3(f,0,i,0,,,,,,,,__VA_ARGS__), _MAC_L3(f,1,i,1,,,,,,,__VA_ARGS__)),  \
  c(_MAC_L3(f,0,i,2,,,,,,  __VA_ARGS__), _MAC_L3(f,1,i,3,,,,,  __VA_ARGS__))), \
c(c(_MAC_L3(f,0,i,4,,,,    __VA_ARGS__), _MAC_L3(f,1,i,5,,,    __VA_ARGS__)),  \
  c(_MAC_L3(f,0,i,6,,      __VA_ARGS__), _MAC_L3(f,1,i,7,      __VA_ARGS__))))

#define _MAC_L3(...) _MAC_L2(__VA_ARGS__, \
1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,  1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, \
1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,  1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, \
0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, )

// p - parity: 0 = even (0th, 2nd, ...), 1 = odd (1st, 3rd, ...)
// a00 - target argument; i##i00 - unique pseudonumeric index for a00
#define _MAC_L2(f, p, i, \
i00,i01,i02,i03, i04,i05,i06,i07, i08,i09,i0A,i0B, i0C,i0D,i0E,i0F, \
i10,i11,i12,i13, i14,i15,i16,i17, i18,i19,i1A,i1B, i1C,i1D,i1E,i1F, \
i20,i21,i22,i23, i24,i25,i26,i27, i28,i29,i2A,i2B, i2C,i2D,i2E,i2F, \
i30,i31,i32,i33, i34,i35,i36,i37, i38,i39,i3A,i3B, i3C,i3D,i3E,i3F, \
a00,a01,a02,a03, a04,a05,a06,a07, a08,a09,a0A,a0B, a0C,a0D,a0E,a0F, \
a10,a11,a12,a13, a14,a15,a16,a17, a18,a19,a1A,a1B, a1C,a1D,a1E,a1F, \
a20,a21,a22,a23, a24,a25,a26,a27, a28,a29,a2A,a2B, a2C,a2D,a2E,a2F, \
a30,a31,a32,a33, a34,a35,a36,a37, a38,a39,a3A,a3B, a3C,a3D,a3E,a3F, \
z, ...) _MAC_L##z(f, p, i##i00, a00)

#define _MAC_L1(f, p, i, a) f##p(i, a)
#define _MAC_L0(f, p, i, a)

#define _MAC_TYPE_ARG0(i, a)
#define _MAC_TYPE_ARG1(i, a) , a _##i
#define _MAC_ONLY_ARG0(i, a)
#define _MAC_ONLY_ARG1(i, a) , _##i
#define _MAC_FUNC_LEX0(i, a) a
#define _MAC_FUNC_LEX1(i, a) _
#define _MAC_FUNC_STR0(i, a) #a
#define _MAC_FUNC_STR1(i, a) ":"

#define _MAC_CAT0(a, b) a##b
#define _MAC_CAT(a, b) _MAC_CAT0(a, b)
#define _MAC_SEQ(a, b) a b

// this is needed to get selectors or classes by name
#define _(callable) _MAC_CAT(__, callable)()


// these are needed to declare functions
#define _MAC_F(type, retn, ...) __attribute__((unused)) static                 \
SEL _(_MAC_L(_MAC_CAT, _MAC_FUNC_LEX, __VA_ARGS__)) {                          \
	static SEL what = 0; if (!what) what = sel_registerName(                   \
		_MAC_L(_MAC_SEQ, _MAC_FUNC_STR, __VA_ARGS__)); return what;            \
} __attribute__((unused)) static inline                                        \
retn _MAC_L(_MAC_CAT, _MAC_FUNC_LEX, __VA_ARGS__)                              \
	(void *inst _MAC_L(_MAC_SEQ, _MAC_TYPE_ARG, __VA_ARGS__)) {                \
	return ((retn (*)(void*, SEL                                               \
		_MAC_L(_MAC_SEQ, _MAC_TYPE_ARG, __VA_ARGS__)))objc_msgSend##type)      \
		(inst, _(_MAC_L(_MAC_CAT, _MAC_FUNC_LEX, __VA_ARGS__))                 \
				 _MAC_L(_MAC_SEQ, _MAC_ONLY_ARG, __VA_ARGS__));                \
};

#define mac_function_define(retn, ...) _MAC_F(      , retn, __VA_ARGS__)
#define _MAC_FF(retn, ...) _MAC_F(_fpret, retn, __VA_ARGS__)
#define _MAC_FS(retn, ...) _MAC_F(_stret, retn, __VA_ARGS__)



#define mac_type_define(typename)                         \
	__attribute__((unused))                               \
	static Class _(typename) {                         \
		static Class what = 0;                            \
		if (!what)                                        \
			what = (Class)objc_getClass(#typename);       \
		return what;                                      \
	} typedef struct typename typename;                   \


static struct {
	Class uuid;
	char *name;
	long  icnt;
} *_MAC_Subclasses = 0;


__attribute__((unused))
static Class MAC_MakeClass(char *name, Class base, void **flds, void **mths) {
	Class retn = 0;
	long iter = 0;

	for (; _MAC_Subclasses && _MAC_Subclasses[iter].name; iter++)
		if (!strcmp(name, _MAC_Subclasses[iter].name)) {
			retn = _MAC_Subclasses[iter].uuid;
			if (base)
				_MAC_Subclasses[iter].icnt++;
			break;
		}
	if (!retn) {
		retn = objc_allocateClassPair(base, name, 0);
		_MAC_Subclasses = realloc(_MAC_Subclasses,
								 (iter + 2) * sizeof(*_MAC_Subclasses));
		_MAC_Subclasses[iter] =
			(__typeof__(*_MAC_Subclasses)){retn, strdup(name), 1};
		_MAC_Subclasses[iter + 1].name = 0;

		iter = -1;
		/// adding fields
		while (flds && flds[++iter])
			class_addIvar(retn, (char*)flds[iter],
						  sizeof(void*), (sizeof(void*) >= 8)? 3 : 2, 0);
		iter = -2;
		/// overloading methods
		while (mths && mths[iter += 2])
			class_addMethod(retn, (SEL)mths[iter], (IMP)mths[iter + 1], 0);

		objc_registerClassPair(retn);
	}
	return retn;
}
#define MAC_LoadClass(n) MAC_MakeClass(n, (Class)0, (void**)0, (void**)0)
#define MAC_TempArray(...) (void*[]){__VA_ARGS__, 0}



__attribute__((unused))
static void MAC_FreeClass(Class uuid) {
	long iter, size = 0;

	for (; _MAC_Subclasses && _MAC_Subclasses[size].name; size++);
	for (iter = 0; iter < size; iter++)
		if (uuid == _MAC_Subclasses[iter].uuid) {
			_MAC_Subclasses[iter].icnt--;
			if (!_MAC_Subclasses[iter].icnt) {
				objc_disposeClassPair(_MAC_Subclasses[iter].uuid);
				free(_MAC_Subclasses[iter].name);
				if (iter < --size) {
					_MAC_Subclasses[iter] = _MAC_Subclasses[size];
					iter = size;
				}
				_MAC_Subclasses[iter].name = 0;
			}
			break;
		}
	if (_MAC_Subclasses && !_MAC_Subclasses[0].name) {
		free(_MAC_Subclasses);
		_MAC_Subclasses = 0;
	}
}

#ifdef __cplusplus
}
#endif