#define __rcgfw__use_error_handler
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

/* ===========[ EXTERN FUNCTION DEFS ]============ */

extern void __rcgfw__set_fatal_err_callback(RcgfwErrCallback callback);
extern void __rcgfw__fatal_assert(const unsigned char condition, const int code, const char *const msg);

/* ===========[ STATIC FUNCTION DEFS ]============ */

static void RcgfwInitEngine(struct rcgfw_state *state, const char *const title, const rcgfw_uint32_t width, const rcgfw_uint32_t height);
static void RcgfwInitGL(struct rcgfw_state *state);
static void RcgfwInitRenderData(struct rcgfw_state *state);

/* ===========[ FUNCTION IMPLEMENTATIONS ]============ */

struct rcgfw_state *RcgfwInit(const char *const title, const rcgfw_uint32_t width, const rcgfw_uint32_t height)
{
	__rcgfw__set_fatal_err_callback(&RcgfwClose);

	struct rcgfw_state *state = (struct rcgfw_state*) calloc(1, sizeof(struct rcgfw_state));
	__rcgfw__fatal_assert(state == NULL, __RCGFW__ERR_MEM_ALLOC_FAILURE, "Could not allocate enough memory to initialize the RCGFW state machine!");

	RcgfwInitEngine(state, title, width, height);
	RcgfwInitGL(state);
	RcgfwInitRenderData(state);

	return state;
}

void RcgfwClose(struct rcgfw_state *state)
{
	int i = 0;
	for(; i < RCGFW_ARR_SIZE(state->shaders, rcgfw_shader_t); i++)
		glDeleteShader(state->shaders[i]);

	state->shaderptr = NULL;
	state->shaderend = NULL;
	free(state->shaders);
	state->shaders = NULL;

	glfwDestroyWindow(state->hdl_wnd);
	state->hdl_wnd = NULL;

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
	__rcgfw__fatal_assert(state->wnd_title == NULL, __RCGFW__ERR_MEM_ALLOC_FAILURE, "Could not allocate enough memory to initialize 'wnd_title'.");
	strcpy(state->wnd_title, title);

	state->shaders = (rcgfw_shader_t*) calloc(2, sizeof(rcgfw_shader_t));
	__rcgfw__fatal_assert(state->shaders == NULL, __RCGFW__ERR_MEM_ALLOC_FAILURE, "Could not allocate enough memory to initialize the RCGFW state machine!");
	state->shaderend = state->shaders + RCGFW_ARR_SIZE(state->shaders, rcgfw_shader_t);
	state->shaderptr = state->shaders;
}

void RcgfwInitGL(struct rcgfw_state *state)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	__rcgfw__fatal_assert(glfwInit() == 0, __RCGFW__ERR_MEM_ALLOC_FAILURE | __RCGFW__ERR_GLFW_INIT_FAILURE, "Could not initialize GLFW.");

	state->hdl_wnd = glfwCreateWindow(state->wnd_width, state->wnd_height, state->wnd_title, NULL, NULL);
	__rcgfw__fatal_assert(state->hdl_wnd == NULL, __RCGFW__ERR_MEM_ALLOC_FAILURE | __RCGFW__ERR_GLFW_WND_CREATE_FAILURE, "Could not create GLFW window.");
	
	glfwMakeContextCurrent(state->hdl_wnd);

	__rcgfw__fatal_assert(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress), __RCGFW__ERR_GLAD_INIT_FAILURE, "Could not initialize GLAD.");
}

void RcgfwInitRenderData(struct rcgfw_state *state)
{
	rcgfw_shader_t vertexShader, fragmentShader;

	const char *vertexSource;
	const char *fragmentSource;
	vertexSource = RcgfwReadFile(RCGFW_SHDR_DIR "vertex.glsl");
	fragmentSource = RcgfwReadFile(RCGFW_SHDR_DIR "fragment.glsl");

	RcgfwShaderCreate(state, &vertexShader, vertexSource, RCGFW_VERTEX_SHADER);
	RcgfwShaderCreate(state, &fragmentShader, fragmentSource, RCGFW_FRAGMENT_SHADER);

	RcgfwFreeFileData(vertexSource);
	RcgfwFreeFileData(fragmentSource);

	state->program = glCreateProgram();
	glAttachShader(state->program, state->shaders[0]);
	glAttachShader(state->program, state->shaders[1]);
}
