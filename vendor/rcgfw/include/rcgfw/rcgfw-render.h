#ifndef RCGFW_RENDER_H
#define RCGFW_RENDER_H

#include "rcgfw-defs.h"
#include "rcgfw-util.h"

void RcgfwShaderCreate(struct rcgfw_state *state, rcgfw_shader_t *shader, const char *src, const rcgfw_shader_type_t type);
void RcgfwShaderProgramLink(struct rcgfw_state *state);

#endif /* RCGFW_RENDER_H */