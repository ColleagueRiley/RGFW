#include <stdio.h>

#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int main(void) {
	RGFW_init();


	RGFW_dataTransfer data;
	data.data = "string";
	data.length = sizeof("string") - 1;
	data.type = RGFW_dataText;
	assert(RGFW_writeClipboard(&data) == RGFW_TRUE);


	const RGFW_dataTransfer* clipboard = RGFW_readClipboard();
	assert(clipboard);

	assert(strncmp(clipboard->data, data.data, data.length) == 0);

	assert(clipboard->data[clipboard->length - 1] == '\0');

	RGFW_free(0);

	return 0;
}

