#ifndef RCGFW_H
#define RCGFW_H

#include "defs.h"

#include "resource.h"
#include "shader.h"
#include "vabo.h"

void RcgfwInit(const char *const title, const RcgfwUInt32 width, const RcgfwUInt32 height);
void RcgfwClose(void);

char RcgfwWindowShouldClose(void);
void RcgfwWindowSwap(void);
void RcgfwWindowClearScreen(float r, float g, float b, float a);
void RcgfwWindowDraw(void);

#endif /* RCGFW_H */