/*
Copyright (C) 2022-2023 EimaMei/Sacode

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software
	in a product, an acknowledgment in the product documentation would be
	appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <Foundation/Foundation.h>
#include <objc/message.h>
#include <objc/runtime.h>

#include "implementation.h"
#define SI_ARRAY_IMPLEMENTATION
#include <Silicon/siArray.h>


/* Checks if the provided selector exist. */
SEL si_impl_SEL_exists(const char* name, const char* filename, int line) {
	SEL selector = sel_getUid(name);

    Class original_class = nil;
    unsigned int class_count = 0;
    Class* class_list = objc_copyClassList(&class_count);

    for (unsigned int i = 0; i < class_count; i++) {
        Class cls = class_list[i];
		if ([NSStringFromClass(cls) isEqual:(@"UINSServiceViewController")]) // For whatever reason, this class ruins everything.
			continue;

        if (class_getInstanceMethod(cls, selector)) {
            original_class = cls;
            break;
        }
    }
    free(class_list);

    if (original_class == nil) {
		printf("%s:%i: Method '%s' doesn't exist. If this is a C function, then make sure to convert it into a SEL method via 'func_to_SEL(<function>)' before this line.\n", filename, line, name);
		return nil;
	}

	return selector;
}


void si_impl_func_to_SEL_with_name(const char* class_name, const char* register_name, void* function) {
    Class selected_class;

    if (strcmp(class_name, "NSView") == 0) {
        selected_class = objc_getClass("ViewClass");
    }
    else if (strcmp(class_name, "NSWindow") == 0) {
        selected_class = objc_getClass("WindowClass");
    }
    else {
        selected_class = objc_getClass(class_name);
    }

    class_addMethod(selected_class, sel_registerName(register_name), (IMP)function, 0);
}


/* Returns the name of a class as a string. */
const char* CharFromClass(Class aClass) {
    return NSString_to_char(NSStringFromClass(aClass));
}

#ifdef __cplusplus
}
#endif