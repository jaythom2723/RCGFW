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

	unsigned char running : 1;
};

RcgfwState *state;

static void InitGL(void);
static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

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

	state->running = 0;
	SetFatalErrorCallback(&RcgfwClose);

	InitGL();

	glViewport(0, 0, state->wndWidth, state->wndHeight);

	glfwSetFramebufferSizeCallback(state->wnd, &FramebufferSizeCallback);
}

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void RcgfwClose(void)
{
	state->shaderPtr = NULL;

	int i = 0;
	for(i=0; i < sizeof(state->shaders) / sizeof(state->shaders[0]); i++)
		glDeleteShader(state->shaders[i]);

	free(state->shaders);
	state->shaders = NULL;

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

void RcgfwWindowDraw(void)
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	(void) assert(glfwInit() != 0);

	state->wnd = glfwCreateWindow(state->wndWidth, state->wndHeight, state->title, NULL, NULL);
	(void) assert(state->wnd != NULL);

	glfwMakeContextCurrent(state->wnd);

	(void) assert(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress));

	state->program = glCreateProgram();

	RcgfwShaderCreate(RcgfwLoad(RCGFW_SHDR_DIR"vertex.glsl"), RCGFW_VERTEX_SHADER);
	RcgfwShaderCreate(RcgfwLoad(RCGFW_SHDR_DIR"fragment.glsl"), RCGFW_FRAGMENT_SHADER);

	glAttachShader(state->program, state->shaders[0]);
	glAttachShader(state->program, state->shaders[1]);
}