#include "rcgfw.h"

#include <stdio.h>
#include <stdlib.h>

RcgfwErrCallback fatalErrorCallback;

void __rcgfw__set_fatal_err_callback(RcgfwErrCallback callback)
{
	fatalErrorCallback = callback;
}

void __rcgfw__fatal_error(struct rcgfw_state *state, const int code, const char *const msg)
{
	printf("[RCGFW] -> FATAL ERROR: %d -> \"%s\"\n", code, msg);

	(*fatalErrorCallback)(state);
}

void __rcgfw__fatal_assert(const unsigned char condition, struct rcgfw_state *state, const int code, const char *const msg)
{
	if(!condition)
		return;

	__rcgfw__fatal_error(state, code, msg);
}