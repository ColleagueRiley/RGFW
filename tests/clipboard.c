#include <stdio.h>

#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int string_compare(const char* str, const char* str2, size_t count);
int string_compare(const char* str, const char* str2, size_t count) {
	size_t i = 0;
	for (i = 0; i < count && str[i] && str2[i] && str[i] == str2[i]; i++);
	return (i == (count - 1));
}

int main(void) {
	RGFW_init();


	RGFW_dataTransfer data;
	data.data = "string";
	data.length = sizeof("string") - 1;
	data.type = RGFW_dataText;
	assert(RGFW_writeClipboard(&data) == RGFW_TRUE);


	const RGFW_dataTransfer* clipboard = RGFW_readClipboard();
	assert(clipboard);

	assert(string_compare(clipboard->data, data.data, data.length) != 0);

	assert(clipboard->data[clipboard->length - 1] == '\0');

	RGFW_free(0);

	return 0;
}

