#define __rcgfw__use_error_handler
#include "rcgfw-render.h"

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

extern void __rcgfw__fatal_assert(const unsigned char condition, struct rcgfw_state *state, const int code, const char *const msg);

void RcgfwShaderCreate(struct rcgfw_state *state, rcgfw_shader_t *shader, const char *src, const rcgfw_shader_type_t type)
{
	*shader = glCreateShader(type);
	glShaderSource(*shader, 1, &src, NULL);
	glCompileShader(*shader);

	int success;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	char infoLog[512];
	glGetShaderInfoLog(*shader, 512, NULL, infoLog);
	__rcgfw__fatal_assert(!success, state, __RCGFW__ERR_SHDR_COMP_FAILURE, infoLog);

	if(state->shaderptr >= state->shaderend)
	{
		rcgfw_size_t arrSize = RCGFW_ARR_SIZE(state->shaders, rcgfw_shader_t);
		state->shaders = (rcgfw_shader_t*) realloc(state->shaders, (arrSize * 2) * sizeof(rcgfw_shader_t));
		__rcgfw__fatal_assert(state->shaders == NULL, state, __RCGFW__ERR_MEM_ALLOC_FAILURE, "Could not allocate enough memory for more shaders.");
	}

	*state->shaderptr = *shader;
	state->shaderptr ++;
}

void RcgfwShaderProgramLink(struct rcgfw_state *state)
{
	glLinkProgram(state->program);
	
	int success;
	glGetProgramiv(state->program, GL_LINK_STATUS, &success);
	char infoLog[512];
	glGetProgramInfoLog(state->program, 512, NULL, infoLog);
	__rcgfw__fatal_assert(!success, state, __RCGFW__ERR_PGRM_LINK_FAILURE, infoLog);

	glUseProgram(state->program);
}