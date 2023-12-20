#ifndef RCGFW_VABO_H
#define RCGFW_VABO_H

#include "defs.h"

RcgfwVao RcgfwVaoCreate(void);
RcgfwVbo RcgfwVboCreate(const float *const data, const RcgfwUInt64 size);

void RcgfwVaoBind(RcgfwVao vao);
void RcgfwVboBind(RcgfwVbo vbo);

void RcgfwVaoVertexAttribArray(const RcgfwUInt32 index, const int size, const RcgfwUInt64 stride, const void *ptr);

void RcgfwVaoDelete(RcgfwVao *vao);
void RcgfwVboDelete(RcgfwVbo *vbo);

#endif /* RCGFW_VABO_H */