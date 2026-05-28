#include <stdio.h>

#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

RGFW_bool string_compare(const char* str, const char* str2, size_t count);
RGFW_bool string_compare(const char* str, const char* str2, size_t count) {
	size_t i = 0;
	for (i = 0; i < count && str[i] && str2[i] && str[i] == str2[i]; i++);
	return (i == (count - 1)) ? RGFW_TRUE : RGFW_FALSE;
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

	fwrite(data.data, 1, data.length, stdout);
	printf(" : ");
	fwrite(clipboard->data, 1, clipboard->length, stdout);
	printf("\n");
	assert(string_compare(clipboard->data, data.data, data.length) == RGFW_TRUE);

	assert(clipboard->data[clipboard->length - 1] == '\0');

	RGFW_free(0);

	return 0;
}

