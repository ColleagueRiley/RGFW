# important conventions
These first conventions are the most important to follow as they are here to prevent undefined behavior, API inconsistency and bugs.

* All functions that return a boolean value must either\
1) return RGFW_TRUE or RGFW_FALSE (the RGFW_BOOL() can be used to reduce an int to RGFW_TRUE or RGFW_FALSE )\
2) a boolean statement e.g. `((a == b) || (a == c))`\
3) a boolean value from the API that's guarantee 1.0 e.g.\
```c
BOOL winbool = EnumPageFilesA(pCallBackRoutine, pContext);
return winbool
```

# style conventions
Style conventions are less important and I will make changes manually if they are not followed, so contributers don't have to worry about these as much.

* Brackets are always used inline if functions definitions and statements e.g.\
```c
if (boolean) {

}

void function() {

}
```