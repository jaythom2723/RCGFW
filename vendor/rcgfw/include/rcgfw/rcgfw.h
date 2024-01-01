#ifndef RCGFW_H
#define RCGFW_H

#include "defs.h"

struct rcgfw_state *RcgfwInit(const char *const title, const rcgfw_uint32_t width, const rcgfw_uint32_t height);
void RcgfwClose(struct rcgfw_state *state);

char RcgfwWindowShouldClose(void);
void RcgfwWindowSwap(void);
void RcgfwWindowClearScreen(float r, float g, float b, float a);
void RcgfwWindowDraw(void);

#endif /* RCGFW_H */