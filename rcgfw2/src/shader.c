#include "shader.h"

#include "defs.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

extern void FatalError(const char *const msg, const RcgfwUInt16 code);

extern RcgfwShader GetShaderFromOffset(void *offset);
extern void AddShader(RcgfwShader shader); 
extern RcgfwShaderProgram GetShaderProgram(void);

extern RcgfwState *state;

void RcgfwShaderCreate(const char *src, RcgfwShaderType type)
{
	// create a shader and attach source code to it
	RcgfwShader shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	// check if the shader compiles successfully
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success) // if compilation not succesful, error the program.
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		FatalError(infoLog, ERR_SHDR_COMP_FAILURE);
	}

	// add the shader to the state's shader array
	AddShader(shader);

	free((char*) src);
}

void RcgfwShaderDelete(void *offset)
{
	glDeleteShader(GetShaderFromOffset(offset));
}

void RcgfwProgramAttachShader(void *offset)
{
	glAttachShader(GetShaderProgram(), GetShaderFromOffset(offset));
}

void RcgfwProgramDetachShader(void *offset)
{
	glDetachShader(GetShaderProgram(), GetShaderFromOffset(offset));
}

void RcgfwProgramLink(void)
{
	glLinkProgram(GetShaderProgram());

	int success;
	char infoLog[512];
	glGetProgramiv(GetShaderProgram(), GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(GetShaderProgram(), 512, NULL, infoLog);
		FatalError(infoLog, ERR_PGRM_LINK_FAILURE);
	}
}

void RcgfwProgramUse(void)
{
	glUseProgram(GetShaderProgram());
}