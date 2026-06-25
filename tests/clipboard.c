#include <stdio.h>

#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int main(void) {
	RGFW_init("clipboard", 0);

	for (size_t i = 0; i < 5; i++) {
		char str[] = "stringx\0";
		str[sizeof(str) - 3] = '0' + (char)i;

		RGFW_dataTransfer data;
		data.data = str;
		data.length = sizeof(str) - 1;
		data.type = RGFW_dataText;
		assert(RGFW_writeClipboard(&data) == RGFW_TRUE);

		const RGFW_dataTransfer* clipboard = RGFW_readClipboard();
		assert(clipboard);
		assert(clipboard->type == data.type);

		fwrite(data.data, 1, data.length, stdout);
		printf(" : ");
		fwrite(clipboard->data, 1, clipboard->length, stdout);
		printf("\n");
		assert(strncmp(clipboard->data, data.data, data.length) == 0);

		assert(clipboard->data[clipboard->length - 1] == '\0');
	}

	RGFW_deinit();

	return 0;
}

