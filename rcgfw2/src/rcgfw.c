#include "rcgfw.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern RcgfwUInt64 GetArraySize(void *arr);
extern void SetFatalErrorCallback(void (*callback)(void));

struct RcgfwState
{
	/* window variables */
	GLFWwindow *wnd;
	RcgfwUInt32 wndWidth, wndHeight;
	char *title;

	/* shader variables */
	RcgfwShader *shaders;
	RcgfwShader *shaderPtr;
	RcgfwShaderProgram program;

	/* buffers/arrays */
	RcgfwVbo **vbos;
	RcgfwVbo **vboPtr;

	RcgfwVao **vaos;
	RcgfwVao **vaoPtr;

	unsigned char running : 1;
};

RcgfwState *state;

static void InitGL(void);

void RcgfwInit(const char *const title, const RcgfwUInt32 width, const RcgfwUInt32 height)
{
	state = (RcgfwState*) malloc(sizeof(RcgfwState));
	(void) assert(state != NULL);

	state->title = calloc(strlen(title) + 1, sizeof(char));
	(void) assert(state->title != NULL);
	strcpy(state->title, title);

	state->wndWidth = width;
	state->wndHeight = height;

	state->shaders = calloc(2, sizeof(RcgfwShader));
	(void) assert(state->shaders != NULL);
	state->shaderPtr = state->shaders;

	state->vbos = calloc(0xF, sizeof(RcgfwVbo));
	state->vboPtr = state->vbos;

	state->vaos = calloc(0xF, sizeof(RcgfwVao));
	state->vaoPtr = state->vaos;

	state->running = 0;
	SetFatalErrorCallback(&RcgfwClose);

	InitGL();
}

void RcgfwClose(void)
{
	glfwDestroyWindow(state->wnd);

	free(state->title);
	state->title = NULL;

	free(state);
	state = NULL;
}

char RcgfwWindowShouldClose(void)
{
	return glfwWindowShouldClose(state->wnd);
}

void RcgfwWindowSwap(void)
{
	glfwSwapBuffers(state->wnd);
	glfwPollEvents();
}

void RcgfwWindowClearScreen(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/* Internal Functions */
void AddShader(RcgfwShader shader)
{
	(*state->shaderPtr) = shader;
	state->shaderPtr++;
}

RcgfwShader GetShaderFromOffset(void *offset)
{
	state->shaderPtr = (RcgfwShader*)offset;
	return (*state->shaderPtr);
}

RcgfwShaderProgram GetShaderProgram(void)
{
	return state->program;
}

void InitGL(void)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	assert(glfwInit() != 0);

	state->wnd = glfwCreateWindow(state->wndWidth, state->wndHeight, state->title, NULL, NULL);
	assert(state->wnd != NULL);

	glfwMakeContextCurrent(state->wnd);

	assert(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress));

	state->program = glCreateProgram();

	RcgfwShaderCreate(RcgfwLoad(RCGFW_SHDR_DIR"vertex.glsl"), RCGFW_VERTEX_SHADER);
	RcgfwShaderCreate(RcgfwLoad(RCGFW_SHDR_DIR"fragment.glsl"), RCGFW_FRAGMENT_SHADER);

	glAttachShader(state->program, state->shaders[0]);
	glAttachShader(state->program, state->shaders[1]);
}