#ifndef RCGFW_SHADER_H
#define RCGFW_SHADER_H

#include "defs.h"

#include <cglm/mat4.h>

void RcgfwShaderCreate(const char *src, RcgfwShaderType type);
void RcgfwShaderDelete(void *offset);

void RcgfwProgramAttachShader(void *offset);
void RcgfwProgramDetachShader(void *offset);
void RcgfwProgramLink(void);
void RcgfwProgramUse(void);

void RcgfwSetMatrix4(const char *const name, mat4 value);
void RcgfwSetVector3(const char *const name, vec3 value);

#endif /* RCGFW_SHADER_H */