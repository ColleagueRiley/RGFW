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

/* NSString / char* conversion functions. */
/* 'const char*' to 'NSString'. */
/* TODO(EimaMei): remove this dumbass autorelease nonsense everywhere in the code. */
#define char_to_NSString(text) [NSString stringWithUTF8String:(text)]
/* 'NSString' to 'const char*'. */
#define NSString_to_char(text) [text UTF8String]


/* Implements the 'class' property. */
#define implement_property(class, type, name, set_name, arg_name)	\
	type class##_##name(class* arg_name) {				\
		return [arg_name name];					\
	}								\
	void class##_set##set_name(class* arg_name, type name) {	\
		[arg_name set##set_name:name];				\
	}


/* Implements the 'class' deprecated property. */
#define implement_deprecated_property(class, type, name, set_name, arg_name, macos_macro)	\
	implement_property(class, type, name, set_name, arg_name);


/* Implements a property for a given class that requires a C string. */
#define implement_str_property(class, type, name, set_name, arg_name)		\
	type class##_##name(class* arg_name) {					\
		return NSString_to_char([arg_name name]);			\
	}									\
	void class##_set##set_name(class* arg_name, type name) {		\
		[arg_name set##set_name:([char_to_NSString(name) retain])];	\
	}


#ifdef __cplusplus
}
#endif