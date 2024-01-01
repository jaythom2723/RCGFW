#include "rcgfw.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>
#include <cglm/mat4.h>

#include <stbimage/stb_image.h>

extern void SetFatalErrorCallback(RcgfwErrCallback callback);
extern void FatalError(const int code, const char *const msg);
extern void FatalAssert(const unsigned char condition, const int code, const char *const msg);

struct rcgfw_state *RcgfwInit(const char *const title, const rcgfw_uint32_t width, const rcgfw_uint32_t height)
{
	SetFatalErrorCallback(RcgfwClose);

	struct rcgfw_state *state = calloc(1, sizeof(struct rcgfw_state));
	FatalAssert(state == NULL, ERR_MEM_ALLOC_FAILURE, "Could not allocate enough memory to initialize the RCGFW state machine!");

	state->wnd_width = width;
	state->wnd_height = height;
	state->wnd_title = calloc(strlen(title) + 1, sizeof(char));
	FatalAssert(state->wnd_title == NULL, ERR_MEM_ALLOC_FAILURE, "Could not allocate enough memory to initialize 'wnd_title'.");
	strcpy(state->wnd_title, title);

	state->running = RCGFW_FALSE;

	return state;
}

void RcgfwClose(struct rcgfw_state *state)
{

}