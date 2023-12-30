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

extern RcgfwUInt64 GetArraySize(void *arr, RcgfwUInt64 size);
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

	RcgfwVao vao;

	unsigned char running : 1;
};

RcgfwState *state;

static void InitEngine(const char *const title, const RcgfwUInt32 width, const RcgfwUInt32 height);
static void InitGL(void);
static void InitRenderData(void);
static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

void RcgfwInit(const char *const title, const RcgfwUInt32 width, const RcgfwUInt32 height)
{
	InitEngine(title, width, height);
	InitGL();

	glViewport(0, 0, state->wndWidth, state->wndHeight);

	glfwSetFramebufferSizeCallback(state->wnd, &FramebufferSizeCallback);

	stbi_set_flip_vertically_on_load(RCGFW_TRUE);

	InitRenderData();

	// setup orthographic viewport
	mat4 projection;
	glm_ortho(0.0f, 0.0f, (float) width, (float) height, 0.0f, 10.0f, projection);
	RcgfwSetMatrix4("projection", projection);
}

void RcgfwClose(void)
{
	state->shaderPtr = NULL;

	int i = 0;
	for(i=0; i < GetArraySize((void*)state->shaders, sizeof(state->shaders)); i++)
		glDeleteShader(state->shaders[i]);

	glDeleteVertexArrays(1, &state->vao);

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
	glBindVertexArray(state->vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

void InitEngine(const char *const title, const RcgfwUInt32 width, const RcgfwUInt32 height)
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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void InitRenderData(void)
{
	// [1:2] -> Position
	// [3:4] -> Tex Coord
	float vertices[] = {
		0.5f, 0.5f, 1.0f, 1.0f, // top-right
		0.5f, -0.5f, 1.0, 0.0f, // bottom-right
		-0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
		-0.5f, 0.5f, 0.0f, 1.0f, // top-left
	};

	RcgfwUInt32 indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	state->vao = RcgfwVaoCreate();
	RcgfwVbo vbo = RcgfwVboCreate(vertices, sizeof(vertices));
	RcgfwIbo ibo = RcgfwIboCreate(indices, sizeof(indices));
	RcgfwVaoVertexAttribArray(0, 2, 4 * sizeof(float), (void*) 0);
	RcgfwVaoVertexAttribArray(1, 2, 4 * sizeof(float), (void*) (2 * sizeof(float)));
}

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}