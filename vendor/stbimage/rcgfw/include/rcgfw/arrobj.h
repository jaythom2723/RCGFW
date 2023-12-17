#ifndef RCGFW_ARROBJ_H
#define RCGFW_ARROBJ_H

#include "defs.h"
#include "types.h"

void rcgfwCreateVertexArray(RCGFWvertexarray *vao);
void rcgfwDestroyVertexArray(RCGFWvertexarray vao);
void rcgfwBindVertexArray(RCGFWvertexarray vao);

#endif