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

RcgfwIbo RcgfwIboCreate(const int *const data, const RcgfwUInt64 size)
{
	RcgfwIbo ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	return ibo;
}

void RcgfwVaoBind(RcgfwVao vao)
{
	glBindVertexArray(vao);
}

void RcgfwVboBind(RcgfwVbo vbo)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void RcgfwIboBind(RcgfwIbo ibo)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void RcgfwVaoVertexAttribArray(const RcgfwUInt32 index, const int size, const RcgfwUInt64 stride, const void *ptr)
{
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, ptr);
	glEnableVertexAttribArray(index);
}

void RcgfwVaoDelete(RcgfwVao *vao)
{
	glDeleteVertexArrays(1, vao);
}

void RcgfwVboDelete(RcgfwVbo *vbo)
{
	glDeleteBuffers(1, vbo);
}

void RcgfwIboDelete(RcgfwIbo *ibo)
{
	glDeleteBuffers(1, ibo);
}