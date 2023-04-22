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

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>


#ifndef usize
typedef size_t    usize;
typedef ptrdiff_t isize;
#endif

#ifndef si_sizeof
#define si_sizeof(type) (isize)sizeof(type)
#endif


/* Silicon array type. */
#define siArray(type) type*

/* Header for the array. */
typedef struct siArrayHeader {
	usize count;
	/* TODO(EimaMei): Add a `type_width` later on. */
} siArrayHeader;

/* Gets the header of the siArray. */
#define SI_ARRAY_HEADER(s) ((siArrayHeader*)s - 1)


/* Initializes a Silicon array. */
void* si_array_init(void* allocator, isize sizeof_element, isize count);
/* Reserves a Silicon array with the provided element count. */
void* si_array_init_reserve(isize sizeof_element, isize count);
/* Gets the element count of the array. */
#define si_array_len(array) (SI_ARRAY_HEADER(array)->count)
/* Frees the array from memory. */
void si_array_free(siArray(void) array);


#ifdef SI_ARRAY_IMPLEMENTATION
#include <stdlib.h>
#include <string.h>


void* si_array_init(void* allocator, isize sizeof_element, isize count)  {
	void* array = si_array_init_reserve(sizeof_element, count);
	memcpy(array, allocator, sizeof_element * count);

	return array;
}

void* si_array_init_reserve(isize sizeof_element, isize count) {
	void* ptr = malloc(si_sizeof(siArrayHeader) + (sizeof_element * count));
	siArray(void) array = ptr + si_sizeof(siArrayHeader);

	siArrayHeader* header = SI_ARRAY_HEADER(array);
	header->count = count;

	return array;
}


void si_array_free(siArray(void) array) {
	if (array == NULL)
		return ;

	free(SI_ARRAY_HEADER(array));
}

#endif

#ifdef __cplusplus
}
#endif