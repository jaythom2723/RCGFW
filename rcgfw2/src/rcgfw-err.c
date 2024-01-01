#include "rcgfw.h"

#include <stdio.h>
#include <stdlib.h>

RcgfwErrCallback fatalErrorCallback;

void SetFatalErrorCallback(RcgfwErrCallback callback)
{


	fatalErrorCallback = callback;
}

void FatalError(struct rcgfw_state *state, const int code, const char *const msg)
{
	printf("[RCGFW] -> FATAL ERROR: %d -> \"%s\"\n", code, msg);

	(*fatalErrorCallback)(state);
}

void FatalAssert(const unsigned char condition, struct rcgfw_state *state, const int code, const char *const msg)
{
	if(!condition)
		return;

	FatalError(state, code, msg);
}