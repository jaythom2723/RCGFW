#include "vabo.h"

#include <stdio.h>
#include <assert.h>

#include <glad/glad.h>

extern void FatalError(const char *const msg, const RcgfwErrorCode code);

RcgfwVao RcgfwVaoCreate(void)
{
	RcgfwVao vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	return vao;	
}

RcgfwVbo RcgfwVboCreate(const float *const data, const RcgfwUInt64 size)
{
	RcgfwVbo vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	return vbo;
}

void RcgfwVaoBind(RcgfwVao vao)
{
	glBindVertexArray(vao);
}

void RcgfwVboBind(RcgfwVbo vbo)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void RcgfwVaoVertexAttribArray(const RcgfwUInt32 index, const int size, const RcgfwUInt64 stride, const void *ptr)
{
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, ptr);
	glEnableVertexAttribArray(index);
}