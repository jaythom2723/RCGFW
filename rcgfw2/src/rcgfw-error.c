#include "rcgfw.h"

#include <stdio.h>
#include <stdlib.h>

void (*FatalErrorCallback)(void);
void (*WarningCallback)(void);

void SetFatalErrorCallback(void (*callback)(void))
{
	FatalErrorCallback = callback;
}

void SetWarningCallback(void (*callback)(void))
{
	WarningCallback = callback;
}

void FatalError(const char *const msg, const RcgfwErrorCode code)
{
	printf("[RCGFW] ERROR CODE (%d) -> %s\n", code, msg);
	(*FatalErrorCallback)();
}

void Warning(const char *const msg)
{
	printf("[RCGFW] WARNING -> %s\n", msg);
	(*WarningCallback)();
}