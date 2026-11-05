#include <stdio.h>

#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

char chars[] = {
	RGFW_keyEscape,
	RGFW_keyBacktick,
	RGFW_keyMinus,
	RGFW_keyEqual,
	RGFW_keyBackSpace,
	RGFW_keyTab,
	RGFW_keySpace,
	RGFW_keyPeriod,
	RGFW_keyComma,
	RGFW_keySlash,
	RGFW_keyBracket,
    RGFW_keyCloseBracket,
    RGFW_keySemicolon,
	RGFW_keyApostrophe,
	RGFW_keyBackSlash,
	RGFW_keyReturn,
	RGFW_keyDelete
};

RGFW_bool isKeyValid(RGFW_key k);
RGFW_bool isKeyValid(RGFW_key k) {
	#ifdef RGFW_WINDOWS
	if (k == RGFW_keyWorld2 || k == RGFW_keyF25) return RGFW_FALSE;
	#endif
	#ifdef RGFW_MACOS
	if (k == RGFW_keyWorld2 || k == RGFW_keyScrollLock || (k >= RGFW_keyF13 &&  k <= RGFW_keyF25) || k == RGFW_keyPause) return RGFW_FALSE;
	#endif
	#ifdef RGFW_WASM
	if (k == RGFW_keyWorld1 || k == RGFW_keyWorld2 || k == RGFW_keyF25 || 
	 	(k == RGFW_keyShiftR || k == RGFW_keyControlR || k == RGFW_keyAltR || RGFW_keySuperR)) return RGFW_FALSE;
	#endif

    if ((k >= '0' && k <= '9') || (k >= 'a' && k <= 'z')) {
        return 1;
    }
    if (k == RGFW_keyEscape || k == '\x08' || k == '\t' || k == '\r') {
        return 1;
    }

    if (k >= RGFW_keyF1 && k < RGFW_keyCount) {
        return RGFW_TRUE;
    }

	for (size_t i = 0; i < sizeof(chars); i += 1) {
		if (chars[i] == k) return RGFW_TRUE;
	}

    return RGFW_FALSE;
}

int main(void) {
	RGFW_init("clipboard", 0);

	RGFW_bool pass = RGFW_TRUE;

	for (RGFW_key key = RGFW_keyFirst; key < RGFW_keyCount; key += 1) {
		if (isKeyValid(key) == RGFW_FALSE) continue;

		RGFW_key apiKey = RGFW_apiKeyToRGFW(RGFW_rgfwToApiKey(key));
		RGFW_bool value = (key == apiKey);
		if (value == RGFW_TRUE) continue;
		pass = value;

		if (apiKey == 0)
			printf("key: %i (%c) not is not mapped\n", key, key);
		else
			printf("key: %i (%c) is incorrectly mapped to  %i (%c)\n", key, key, apiKey, apiKey);
	}

	for (RGFW_key key = RGFW_keyFirst; key < RGFW_keyCount; key += 1) {
		if (isKeyValid(key) == RGFW_FALSE) continue;

		RGFW_key physKey = RGFW_physicalToMappedKey(key);
		RGFW_bool value = (key == physKey);
		if (value == RGFW_TRUE) continue;
		pass = value;

		if (physKey == 0)
			printf("key: %i (%c) is not mapped to a physical key\n", key, key);
		else
			printf("key: %i (%c) is incorrectly mapped to physical key %i (%c)\n", key, key, physKey, physKey);
	}

	RGFW_deinit();

	return pass ? 0 : -1;
}

