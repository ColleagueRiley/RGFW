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
	RGFW_writeClipboard(&data);

	const RGFW_dataTransfer* clipboard = RGFW_readClipboard();
	if (clipboard) {
		printf("clipboard copy %i: '", (u32)clipboard->length);
		fwrite(clipboard->data, 1, clipboard->length, stdout);
		printf("\'\n");

		if (clipboard->data[clipboard->length - 1] != '\0') {
			printf("clipboard does not have a null terminator\n");
			return -1;
		}
	} else {
		printf("failed to read clipboard\n");
		return -1;
	}

	RGFW_free(0);

	return 0;
}

