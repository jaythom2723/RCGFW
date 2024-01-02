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

static void RcgfwInitEngine(struct rcgfw_state *state, const char *const title, const rcgfw_uint32_t width, const rcgfw_uint32_t height);
static void RcgfwInitGL(struct rcgfw_state *state);
static void RcgfwInitRenderData(struct rcgfw_state *state);

struct rcgfw_state *RcgfwInit(const char *const title, const rcgfw_uint32_t width, const rcgfw_uint32_t height)
{
	SetFatalErrorCallback(&RcgfwClose);

	struct rcgfw_state *state = calloc(1, sizeof(struct rcgfw_state));
	FatalAssert(state == NULL, ERR_MEM_ALLOC_FAILURE, "Could not allocate enough memory to initialize the RCGFW state machine!");

	RcgfwInitEngine(state, title, width, height);
	RcgfwInitGL(state);

	state->running = RCGFW_FALSE;

	return state;
}

void RcgfwClose(struct rcgfw_state *state)
{
	glfwDestroyWindow(state->hdl_wnd);

	free(state->wnd_title);
	state->wnd_title = NULL;

	free(state);
	state = NULL;
}

char RcgfwWindowShouldClose(struct rcgfw_state *state)
{
	return glfwWindowShouldClose(state->hdl_wnd);
}

void RcgfwWindowSwap(struct rcgfw_state *state)
{
	/* TODO: Unbind current vao */ 

	glfwSwapBuffers(state->hdl_wnd);
	glfwPollEvents();
}

void RcgfwWindowClearScreen(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RcgfwWindowDraw(struct rcgfw_state *state)
{
	glBindVertexArray(state->vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

/* ===========[ STATIC FUNCTION IMPLEMENTATIONS ]============ */

void RcgfwInitEngine(struct rcgfw_state *state, const char *const title, const rcgfw_uint32_t width, const rcgfw_uint32_t height)
{
	state->wnd_width = width;
	state->wnd_height = height;
	state->wnd_title = calloc(strlen(title) + 1, sizeof(char));
	FatalAssert(state->wnd_title == NULL, ERR_MEM_ALLOC_FAILURE, "Could not allocate enough memory to initialize 'wnd_title'.");
	strcpy(state->wnd_title, title);

	state->running = RCGFW_FALSE;
}

void RcgfwInitGL(struct rcgfw_state *state)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	FatalAssert(glfwInit() == 0, ERR_MEM_ALLOC_FAILURE | ERR_GLFW_INIT_FAILURE, "Could not initialize GLFW.");

	state->hdl_wnd = glfwCreateWindow(state->wnd_width, state->wnd_height, state->wnd_title, NULL, NULL);
	FatalAssert(state->hdl_wnd == NULL, ERR_MEM_ALLOC_FAILURE | ERR_GLFW_WND_CREATE_FAILURE, "Could not create GLFW window.");
	
	glfwMakeContextCurrent(state->hdl_wnd);

	FatalAssert(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress), ERR_GLAD_INIT_FAILURE, "Could not initialize GLAD.");
}

void RcgfwInitRenderData(struct rcgfw_state *state)
{

}

