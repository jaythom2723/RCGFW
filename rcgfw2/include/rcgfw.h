#ifndef RCGFW_H
#define RCGFW_H

#include "defs.h"
#include "util.h"

struct rcgfw_state *RcgfwInit(const char *const title, const rcgfw_uint32_t width, const rcgfw_uint32_t height);
void RcgfwClose(struct rcgfw_state *state);

char RcgfwWindowShouldClose(struct rcgfw_state *state);
void RcgfwWindowSwap(struct rcgfw_state *state);
void RcgfwWindowClearScreen(float r, float g, float b, float a);
void RcgfwWindowDraw(struct rcgfw_state *state);

#endif /* RCGFW_H */
